#include "global.h"
#include <sys/time.h>
#include <uuid/uuid.h>

Global::Global(APP_TYPE appType, int appId)
{
    _appType = appType;
    _appId = appId;
    std::cout << "app type:" << GetAppName(appType) << " id:" << _appId << std::endl;

    UpdateTime();
}

int Global::GetAppIdFromSN(uint64_t sn)
{
    sn = sn << 38;
    sn = sn >> 38;
    sn = sn >> 16;
    return static_cast<int>(sn);
}

uint64_t Global::GenerateSN()
{
    std::lock_guard<std::mutex> guard(_mtx);
    // (38, 10, 16)
    const uint64_t ret = ((TimeTick >> 10) << 26) + (_appId << 16) + _snTicket;
    _snTicket += 1;
    return ret;
}

APP_TYPE Global::GetCurAppType() const
{
    return _appType;
}

int Global::GetCurAppId() const
{
    return _appId;
}

void Global::UpdateTime()
{
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    TimeTick = tv.tv_sec * 1000 + tv.tv_usec * 0.001;

    //#if ENGINE_PLATFORM != PLATFORM_WIN32
    //    auto tt = std::chrono::system_clock::to_time_t(timeValue);
    //    struct tm* ptm = localtime(&tt);
    //    YearDay = ptm->tm_yday;
    //#else
    //    auto tt = std::chrono::system_clock::to_time_t(timeValue);
    //    struct tm tm;
    //    localtime_s(&tm, &tt);
    //    YearDay = tm.tm_yday;
    //#endif
}

std::string Global::GenerateUUID()
{
    uuid_t uuid;
    uuid_generate(uuid);

    char key[36];
    uuid_unparse(uuid, key);

    std::string tokenkey = key;

    return tokenkey;
}
