#pragma once

enum class RobotStateType
{
    None = -1,

    Http_Connecting = 0,   // http����
    Http_Connected,		// 

    Login_Connecting,	    // �������� Login
    Login_Connected,	    // ���ӳɹ�
    Login_Logined,          // ��¼�ɹ�

    //Login_CreatePlayer,   // ������ɫ
    Login_SelectPlayer,      // ѡ���ɫ

    Game_Connecting,	    // �������� Game
    Game_Connected,	    // ���ӳɹ�
    Game_Logined,           // ��¼�ɹ�

    Space_EnterWorld,       // �����ͼ

    End,
};

const char RobotStateTypeName[][255] = {
    "[Http ] Connecting  :",
    "[Http ] Connected   :",

    "[Login] Connecting  :",
    "[Login] Connected   :",
    "[Login] Logined     :",

    //"[Login] CreatePlayer:",
    "[Login] SelectPlayer:",

    "[Game ] Connecting  :",
    "[Game ] Connected   :",
    "[Game ] Logined     :",

    "[Space] EnterWorld  :",
};

const char RobotStateTypeShortName[][255] = {
    "Http-Connecting",
    "Http-Connected",

    "Login-Connecting",
    "Login-Connected",
    "Login-Logined",
    //"Login-CreatePlayer",
    "Login-SelectPlayer",

    "Game-Connecting",
    "Game-Connected",
    "Game-Logined",

    "Space-EnterWorld",
};

inline const char* GetRobotStateTypeShortName(RobotStateType stateType)
{
    if (stateType <= RobotStateType::None || stateType >= RobotStateType::End)
    {
        return "unknown";
    }

    return RobotStateTypeShortName[(int)stateType];
}


inline const char* GetRobotStateTypeName(RobotStateType stateType)
{
    if (stateType <= RobotStateType::None || stateType >= RobotStateType::End)
    {
        return "unknown";
    }

    return RobotStateTypeName[(int)stateType];
}