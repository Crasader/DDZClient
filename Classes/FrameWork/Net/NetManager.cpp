#include "NetManager.h"
#include "SocketLibTypes.h"
#include <cocos2d.h>

using namespace SocketLib;

bool CNetManager::connectGameServer()
{
	return m_gameServerSocket.connectServer("127.0.0.1");
}

CGameServerSocket & CNetManager::getGameServerSocket()
{
	// TODO: �ڴ˴����� return ���
	return m_gameServerSocket;
}

bool CNetManager::init()
{
	return true;
	//return connectGameServer();
}

CNetManager::CNetManager()
{
	
}


CNetManager::~CNetManager()
{
}