#include "connect_obj.h"

#include "network.h"
#include "network_buffer.h"

#include "thread_mgr.h"

#include "system_manager.h"
#include "message_system.h"
#include "message_system_help.h"
#include "component_help.h"

#include "object_pool_packet.h"
#include "network_locator.h"
#include "socket_locator.h"

ConnectObj::ConnectObj()
{
    _state = ConnectStateType::None;
    _recvBuffer = new RecvNetworkBuffer(DEFAULT_RECV_BUFFER_SIZE, this);
    _sendBuffer = new SendNetworkBuffer(DEFAULT_SEND_BUFFER_SIZE, this);
}

ConnectObj::~ConnectObj()
{
    delete _recvBuffer;
    delete _sendBuffer;
}

void ConnectObj::Awake(int socket, NetworkType networkType, TagType tagType, TagValue tagValue, ConnectStateType state)
{
    _socketKey = SocketKey(socket, networkType);

    _tagKey.Clear();
    if (tagType != TagType::None)
        _tagKey.AddTag(tagType, tagValue);

    _state = state;
}

void ConnectObj::BackToPool()
{
#ifdef LOG_TRACE_COMPONENT_OPEN
    const auto traceMsg = std::string("close.  network type:").append(GetNetworkTypeName(_socketKey.NetType));
    ComponentHelp::GetTraceComponent()->Trace(TraceType::Connector, _socketKey.Socket, traceMsg);
#endif

    // ֪ͨ�߼��㣬�����ӹر���
    MessageSystemHelp::DispatchPacket(Proto::MsgId::MI_NetworkDisconnect, this);    

    if (_socketKey.Socket != INVALID_SOCKET)
        ::close(_socketKey.Socket);

    _state = ConnectStateType::None;
    _socketKey.Clear();
    _tagKey.Clear();

    _recvBuffer->BackToPool();
    _sendBuffer->BackToPool();
}

bool ConnectObj::HasRecvData() const
{
    return _recvBuffer->HasData();
}

bool ConnectObj::Recv()
{
    if (_state == ConnectStateType::Connecting)
    {
        ChangeStateToConnected();
        return true;
    }

    bool isRs = false;
    char* pBuffer = nullptr;
    while (true)
    {
        // �ܿռ����ݲ���һ��ͷ�Ĵ�С������
        if (_recvBuffer->GetEmptySize() < (sizeof(PacketHeadS2S) + sizeof(TotalSizeType) * 2))
        {
            _recvBuffer->ReAllocBuffer();
        }

        const int emptySize = _recvBuffer->GetBuffer(pBuffer);
        const int dataSize = ::recv(_socketKey.Socket, pBuffer, emptySize, 0);
        if (dataSize > 0)
        {
            _recvBuffer->FillDate(dataSize);
            isRs = true;
        }
        else if (dataSize == 0)
        {
            break;
        }
        else
        {
            const auto socketError = errno;
            isRs = socketError != 0;
            if (!NetworkHelp::IsError(socketError))
            {
                isRs = true;
            }

            if (!isRs)
                LOG_WARN("recv size:" << dataSize << " error:" << socketError);

            break;
        }
    }

    if (isRs)
    {
        const auto pNetwork = this->GetParent<Network>();
        const auto iNetworkType = pNetwork->GetNetworkType();
        while (true)
        {
            const auto pPacket = _recvBuffer->GetPacket();
            if (pPacket == nullptr)
                break;

            const auto pTagAccount = this->_tagKey.GetTagValue(TagType::Account);
            if (pTagAccount != nullptr)
            {
                auto pSocketLocator = ComponentHelp::GetGlobalEntitySystem()->GetComponent<SocketLocator>();
                if (pSocketLocator != nullptr)
                {
                    const auto targetEntitySn = pSocketLocator->GetTargetEntitySn(pPacket->GetSocketKey()->Socket);
                    if (targetEntitySn > 0)
                    {
                        pPacket->GetTagKey()->AddTag(TagType::Entity, targetEntitySn);
                    }
                }
            }

            //const google::protobuf::EnumDescriptor* descriptor = Proto::MsgId_descriptor();
            //auto name = descriptor->FindValueByNumber(pPacket->GetMsgId())->name();
            //std::cout << "recv msg:" << name.c_str() << std::endl;

            const auto msgId = pPacket->GetMsgId();
            const bool isTcp = NetworkHelp::IsTcp(iNetworkType);
            if (!isTcp)
            {
                if (msgId == Proto::MsgId::MI_HttpRequestBad)
                {
                    // 404
                    MessageSystemHelp::SendHttpResponse404(pPacket);
                    DynamicPacketPool::GetInstance()->FreeObject(pPacket);
                    continue;
                }
            }
            else
            {
                if (msgId == Proto::MsgId::MI_Ping)
                {
                    //RecvPing();
                    continue;
                }
            }

            if (!isTcp)
            {
                if ((msgId <= Proto::MsgId::MI_HttpBegin || msgId >= Proto::MsgId::MI_HttpEnd) && msgId != Proto::MsgId::MI_HttpOuterResponse)
                {
                    // ���һ��httpЭ���ţ��Ƿ�
                    LOG_WARN("http connect recv. tcp proto");
                    DynamicPacketPool::GetInstance()->FreeObject(pPacket);
                    continue;
                }
            }

            ThreadMgr::GetInstance()->DispatchPacket(pPacket);
        }
    }

    return isRs;
}

bool ConnectObj::HasSendData() const
{
    if (_state == ConnectStateType::Connecting)
        return true;

    return _sendBuffer->HasData();
}

void ConnectObj::SendPacket(Packet* pPacket) const
{
    //const google::protobuf::EnumDescriptor* descriptor = Proto::MsgId_descriptor();
    //auto name = descriptor->FindValueByNumber(pPacket->GetMsgId())->name();
    //std::cout << "send msg:" << name.c_str() << std::endl;

    _sendBuffer->AddPacket(pPacket);
    DynamicPacketPool::GetInstance()->FreeObject(pPacket);
}

bool ConnectObj::Send()
{
    if (_state == ConnectStateType::Connecting)
    {
        ChangeStateToConnected();
        return true;
    }

    while (true) {
        char* pBuffer = nullptr;
        const int needSendSize = _sendBuffer->GetBuffer(pBuffer);

        // û�����ݿɷ���
        if (needSendSize <= 0)
        {
            return true;
        }

        const int size = ::send(_socketKey.Socket, pBuffer, needSendSize, 0);
        if (size > 0)
        {
            _sendBuffer->RemoveDate(size);

            // ��һ֡�ٷ���
            if (size < needSendSize)
            {
                return true;
            }
        }

        if (size <= 0)
        {
            const auto socketError = errno;
            std::cout << "needSendSize:" << needSendSize << " error:" << socketError << std::endl;
            return false;
        }
    }
}

void ConnectObj::Close()
{
    // ConnectoObj һ����Network��ͬһ���߳��еģ����ֻ��ҪҪ���̷߳������ݼ���
    const auto pPacketDis = MessageSystemHelp::CreatePacket(Proto::MsgId::MI_NetworkRequestDisconnect, this);
    GetSystemManager()->GetMessageSystem()->AddPacketToList(pPacketDis);
    pPacketDis->OpenRef();
}

ConnectStateType ConnectObj::GetState() const
{
    return _state;
}

void ConnectObj::ChangeStateToConnected()
{
    _state = ConnectStateType::Connected;
    const auto pTagValue = _tagKey.GetTagValue(TagType::App);
    if (pTagValue != nullptr)
    {
        auto pLocator = ThreadMgr::GetInstance()->GetEntitySystem()->GetComponent<NetworkLocator>();
        pLocator->AddNetworkIdentify(&_socketKey, pTagValue->KeyInt64);
    }
    else
    {
        // ֪ͨ�߼��㣬���������ӳɹ���
        MessageSystemHelp::DispatchPacket(Proto::MsgId::MI_NetworkConnected, this);
    }
}
