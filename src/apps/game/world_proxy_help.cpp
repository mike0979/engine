#include "world_proxy_help.h"

#include "server/message_system_help.h"

#include "player/player.h"
#include "server/thread_mgr.h"

void WorldProxyHelp::Teleport(Player* pPlayer, const uint64_t lastWorldSn, const uint64_t targetWorldSn)
{
    const uint64_t playerSn = pPlayer->GetPlayerSN();

    Proto::Teleport proto;
    proto.set_last_world_sn(lastWorldSn);
    proto.set_account(pPlayer->GetAccount().c_str());
    proto.set_player_sn(playerSn);
    pPlayer->SerializeToProto(proto.mutable_player());

    NetIdentify netIdentify;
    netIdentify.GetSocketKey()->CopyFrom(pPlayer->GetSocketKey());
    netIdentify.GetTagKey()->AddTag(TagType::Entity, targetWorldSn);
    MessageSystemHelp::DispatchPacket(Proto::MsgId::MI_Teleport, proto, &netIdentify);
}
