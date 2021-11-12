#pragma once
#include "mysql_connector.h"

#include "server/thread_mgr.h"

inline void InitializeComponentDBMgr(ThreadMgr* pThreadMgr)
{
    pThreadMgr->CreateComponent<MysqlConnector>(MysqlThread, true);
}
