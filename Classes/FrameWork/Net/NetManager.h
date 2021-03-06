#pragma once
#ifndef _NET_MANAGER_H
#define _NET_MANAGER_H

#include <Singleton.h>
#include <GameServerSocket.h>

class CNetManager
	: public CSingleTon<CNetManager>
{
	friend class CSingleTon<CNetManager>;
public:
	// 连接到游戏服务器
	bool connectGameServer();
	virtual bool init();

public:
	CGameServerSocket & getGameServerSocket();
	bool isConnected();

protected:
	CNetManager();
	~CNetManager();

private:
	CGameServerSocket m_gameServerSocket;
};

#define NetManagerIns CNetManager::getInstance()
#endif


