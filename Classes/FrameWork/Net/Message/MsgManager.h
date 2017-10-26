////////////////////////////////////////////////////////////////////////
// Copyright(c) 1999-2099, TQ Digital Entertainment, All Rights Reserved
// Author��  zhu
// Created�� 2017/10/26
// Describe����Ϣ������ - ���߳̾�û��Ҫʹ��������������ģʽ��
////////////////////////////////////////////////////////////////////////

#include <google/protobuf/message.h>
#include <deque>
#include <ThreadLibMutex.h>

typedef std::shared_ptr<google::protobuf::Message> MSG_PTR;
typedef std::deque<MSG_PTR> MSG_DEQUE;
typedef std::deque<MSG_PTR>::iterator MSG_ITER;

// ��Ϣ�����������
const unsigned int MAX_DEQUE_MESSAGE_SIZE = 90000;

class CMsgManager
{
public:
	// ��ȡʵ��
	static CMsgManager & getInstance() {
		static CMsgManager instance;
		return instance;
	}

	// �жϽ�����Ϣ�����Ƿ�Ϊ��
	bool receivedMsgEmpty();

	// ����һ����Ϣ�����ն�����
	void insertReceivedMsg(MSG_PTR pMsg);

	// �ӽ��ն����л�ȡһ����Ϣ
	MSG_PTR getReceivedMsg();

private:
	CMsgManager() {
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

