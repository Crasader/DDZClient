////////////////////////////////////////////////////////////////////////
// Copyright(c) 1999-2099, TQ Digital Entertainment, All Rights Reserved
// Author��  zhu
// Created�� 2017/10/26
// Describe����Ϣ������ - ���߳̾�û��Ҫʹ��������������ģʽ��
////////////////////////////////////////////////////////////////////////
#ifndef _MSG_MANAGER_H
#define _MSG_MANAGER_H

#include "Protocol/protobuf.hpp"
#include <google/protobuf/message.h>
#include <deque>
#include <ThreadLib.h>
#include <Singleton.h>

typedef std::shared_ptr<proto::Protobuf> MSG_PTR;
typedef std::deque<MSG_PTR> MSG_DEQUE;
typedef std::deque<MSG_PTR>::iterator MSG_ITER;

// ��Ϣ�����������
const unsigned int MAX_DEQUE_MESSAGE_SIZE = 90000;

// ========================================================================
// Type:        CMsgLooper
// Purpose:     ��Ϣѭ��
// ========================================================================
class CMsgLooper {
public:

	// ��cocos2dx Scheduler����ʵ������Ϸ֡����ͬ�Ļص�����������Ϸͬ�߳�
	void update(float dt);

	// ����һ�����߳�������������
	void beginReceiveThread();

	// ���������߳�
	void endReceiveThread();

	// �����̴߳�����
	static void handleReceiveThread(void * pData);

public:
	CMsgLooper();
	~CMsgLooper();

private:
	static bool m_flag;								//�߳̽�����־
	static ThreadLib::ThreadID m_receiveThread;		//�����߳�id
};

class CMsgManager 
	: public CSingleTon<CMsgManager>
{
public:
	virtual bool init();

private:
	CMsgLooper m_looper;
};

// ========================================================================
// Type:        CMsgDeque
// Purpose:     ��Ϣ����
// ========================================================================
class CMsgDeque
{
public:
	static CMsgDeque & getInstance() {
		static CMsgDeque instance;
		return instance;
	}

	// �жϽ�����Ϣ�����Ƿ�Ϊ��
	bool receivedMsgEmpty();

	// ����һ����Ϣ�����ն�����
	void insertReceivedMsg(MSG_PTR pMsg);

	// �ӽ��ն����л�ȡһ����Ϣ
	MSG_PTR getReceivedMsg();

private:
	CMsgDeque() {
		init();
	}

	// ��ʼ����Ϣ����
	void init();

protected:

	MSG_DEQUE m_receiveDeq;						  // ������Ϣ����

	ThreadLib::Mutex	 m_csReceive;			  // �����ٽ���

#ifdef WIN32
	HANDLE               m_hRecDeqFullSemaphore;  // ��Ϣ���ܶ������ź���
	HANDLE               m_hRecDeqEmptySemphore;  // ��Ϣ���ܶ��п��ź���
#endif // WIN32
};

#define MsgManagerIns CMsgManager::getInstance()
#endif // !_MSG_MANAGER_H