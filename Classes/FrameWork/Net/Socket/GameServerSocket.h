#pragma once
#ifndef _GAME_SERVER_SOCKET_H
#define _GAME_SERVER_SOCKET_H

#include "SocketLibSocket.h"
#include <string>
#include <google/protobuf/message.h>

class CGameServerSocket 
	: public SocketLib::DataSocket
{
public:
	// ���ӵ�������
	bool connectServer(std::string strAddress, int iPort = 9876);

	// ֻ�ǽ�m_closed����Ϊture
	inline void close() {
		m_closed = true;
	}

	// �Ƿ����ӹر�
	inline bool closed() {
		return m_closed;
	}

	// �ر�����
	inline void closeSocket() {
		DataSocket::Close();
	}

	// ��������
	virtual void receive();

	// ��������
	virtual int send(int32_t id, const google::protobuf::Message & message);
	
protected:
	// ��ʼ��
	void initialize();

public:
	CGameServerSocket();
	~CGameServerSocket();

protected:
	// �����Ƿ�ر�
	bool m_closed;

	// ��������ͷ������
	char headerBuf[4];
};

#endif


