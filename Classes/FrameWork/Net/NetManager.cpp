#include "NetManager.h"
#include "SocketLibTypes.h"
#include <cocos2d.h>

using namespace SocketLib;

bool CNetManager::connectGameServer()
{
	return m_gameServerSocket.connectServer("120.78.219.164", 9999);
}

CGameServerSocket & CNetManager::getGameServerSocket()
{
	// TODO: �ڴ˴����� return ���
	return m_gameServerSocket;
}

bool CNetManager::isConnected()
{
	return m_gameServerSocket.IsConnected();
}

bool CNetManager::init()
{

	return true;
}

CNetManager::CNetManager()
{
	
}


CNetManager::~CNetManager()
{
}