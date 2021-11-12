#pragma once

#include <climits>
#include "protobuf/proto_id.pb.h"
#include "protobuf/db.pb.h"
#include "protobuf/msg.pb.h"

#ifndef PATH_MAX  
#define PATH_MAX 1024  
#endif  

#define INVALID_ID (-1)

//#define SOCKET int
#define INVALID_SOCKET -1

#include <string.h>
#include <stdint.h>
#define engine_stricmp strcasecmp
#define engine_access access
#define engine_strncpy(dest, destsz, src, srcsz) strncpy(dest, src, srcsz)

#define BindFunP4(_self, _f) std::bind ( _f, _self, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4 )
#define BindFunP3(_self, _f) std::bind ( _f, _self, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 )
#define BindFunP2(_self, _f) std::bind ( _f, _self, std::placeholders::_1, std::placeholders::_2 )
#define BindFunP1(_self, _f) std::bind ( _f, _self, std::placeholders::_1 )
#define BindFunP0(_self, _f) std::bind ( _f, _self)


// 打开跟踪数据
#if false
#define LOG_TRACE_COMPONENT_OPEN 1
#endif

// 打开效率测试
#if true
#define LOG_EFFICIENCY_COMPONENT_OPEN 1
#endif
