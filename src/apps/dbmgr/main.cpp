#include "server/common.h"
#include "server/app_type.h"
#include "server/server_app.h"
#include "server/network_listen.h"
#include "server/component_help.h"

#include "dbmgr.h"
#include "mysql_table_update.h"
#include "server/global.h"

int main(int argc, char* argv[])
{
    mysql_library_init(0, nullptr, nullptr);

    const APP_TYPE curAppType = APP_TYPE::APP_DB_MGR;
    ServerApp app(curAppType, argc, argv);
    app.Initialize();

    auto pTableUpdateObj = MysqlTableUpdate::Instance();
    pTableUpdateObj->Check();
    pTableUpdateObj->DestroyInstance();

    auto pThreadMgr = ThreadMgr::GetInstance();
    InitializeComponentDBMgr(pThreadMgr);

    const auto pGlobal = Global::GetInstance();
    pThreadMgr->CreateComponent<NetworkListen>(ListenThread, false, (int)pGlobal->GetCurAppType(), (int)pGlobal->GetCurAppId());
    
    app.Run();
    app.Dispose();

    mysql_library_end();
    return 0;
}
