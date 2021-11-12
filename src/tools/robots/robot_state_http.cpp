#include "robot_state_http.h"
#include "robot.h"
#include "server/message_system_help.h"
#include "server/component_help.h"

void RobotStateHttpConnecting::OnEnterState()
{
    const auto pYaml = ComponentHelp::GetYaml();
    const auto pCommonConfig = dynamic_cast<CommonConfig*>(pYaml->GetConfig(APP_APPMGR));

    TagValue tagValue { _pParentObj->GetAccount(), 0 };
    MessageSystemHelp::CreateConnect(NetworkType::HttpConnector, TagType::Account, tagValue, pCommonConfig->Ip, pCommonConfig->HttpPort);
}

RobotStateType RobotStateHttpConnecting::OnUpdate()
{
    const auto socketKey = _pParentObj->GetSocketKey();
    if (socketKey->Socket != INVALID_SOCKET && socketKey->NetType == NetworkType::HttpConnector)
    {
        return RobotStateType::Http_Connected;
    }

    return GetState();
}

void RobotStateHttpConnected::OnEnterState()
{
#ifdef LOG_TRACE_COMPONENT_OPEN
    std::stringstream traceMsg;
    traceMsg << "http connected.";
    traceMsg << " account:" << _pParentObj->GetAccount();
    traceMsg << " socket:" << _pParentObj->GetSocketKey()->Socket;

    ComponentHelp::GetTraceComponent()->TraceAccount(_pParentObj->GetAccount(), _pParentObj->GetSocketKey()->Socket);
    ComponentHelp::GetTraceComponent()->Trace(TraceType::Player, _pParentObj->GetSocketKey()->Socket, traceMsg.str());
#endif

    const auto pYaml = ComponentHelp::GetYaml();
    const auto pCommonConfig = dynamic_cast<CommonConfig*>(pYaml->GetConfig(APP_APPMGR));

    MessageSystemHelp::SendHttpRequest(_pParentObj, pCommonConfig->Ip, pCommonConfig->HttpPort, "/login", nullptr);
}

RobotStateType RobotStateHttpConnected::OnUpdate()
{
    return GetState();
}
