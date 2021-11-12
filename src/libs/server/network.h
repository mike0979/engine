#pragma once

#include <map>
#include "common.h"
#include "entity.h"
#include "cache_swap.h"
#include "network_help.h"
#include "connect_obj.h"
#include "trace_component.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

#ifdef EPOLL
#include <sys/epoll.h>
#endif

#define MAX_CLIENT  5120
//#define ::close( sockfd ) ::shutdown(sockfd, SHUT_RDWR);

#ifdef EPOLL
#define RemoveConnectObj(socket) \
    _connects[socket]->ComponentBackToPool( ); \
    _connects[socket] = nullptr; \
    DeleteEvent(_epfd, socket); \
    _sockets.erase(socket); 
#else

#define RemoveConnectObj(socket) \
    _connects[socket]->ComponentBackToPool( ); \
    _connects[socket] = nullptr; \
    _sockets.erase(socket); 

#define RemoveConnectObjByItem(iter) \
    _connects[*iter]->ComponentBackToPool(); \
    _connects[*iter] = nullptr; \
    iter = _sockets.erase(iter);
#endif

class Packet;

class Network : public Entity<Network>, public INetwork
#if LOG_TRACE_COMPONENT_OPEN
    , public CheckTimeComponent
#endif
{
public:
    void BackToPool() override;
    void SendPacket(Packet*& pPacket) override;
    NetworkType GetNetworkType() const { return _networkType; }

protected:
    void SetSocketOpt(int socket);
    int CreateSocket();
    bool CheckSocket(int socket);
    bool CreateConnectObj(int socket, TagType tagType, TagValue tagValue, ConnectStateType iState);

    // packet
    void HandleDisconnect(Packet* pPacket);

#ifdef EPOLL
    void InitEpoll();
    void Epoll();
    void AddEvent(int epollfd, int fd, int flag);
    void ModifyEvent(int epollfd, int fd, int flag);
    void DeleteEvent(int epollfd, int fd);
    virtual void OnEpoll(int fd, int index) { };
#else    
    void Select();
#endif

    void OnNetworkUpdate();

protected:
    ConnectObj* _connects[MAX_CLIENT]{};
    std::set<int> _sockets;

#ifdef EPOLL
#define MAX_EVENT   5120
    struct epoll_event _events[MAX_EVENT];
    int _epfd{ -1 };
#else
    int _fdMax{ INVALID_SOCKET };
    fd_set readfds, writefds, exceptfds;
#endif

    // ∑¢ÀÕ–≠“È
    std::mutex _sendMsgMutex;
    CacheSwap<Packet> _sendMsgList;

    NetworkType _networkType{ NetworkType::TcpListen };
};
