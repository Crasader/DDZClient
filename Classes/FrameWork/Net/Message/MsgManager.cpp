#include "MsgManager.h"

bool CMsgManager::receivedMsgEmpty()
{
	bool bFlag = false;

	// ���ٽ���Դ���з����ǻ����
	m_csReceive.Lock();

	if (m_receiveDeq.empty())
		bFlag = true;

	m_csReceive.Unlock();

	return bFlag;
}

void CMsgManager::insertReceivedMsg(MSG_PTR pMsg)
{
	// ��Ϣ����ȴ�
	WaitForSingleObject(m_hRecDeqEmptySemphore, INFINITE);

	m_csReceive.Lock();
	m_receiveDeq.emplace_back(pMsg);
	m_csReceive.Unlock();

	// ���ź���+1
	ReleaseSemaphore(m_hRecDeqFullSemaphore, 1, NULL);
}

MSG_PTR CMsgManager::getReceivedMsg()
{
	// û����Ϣ��ȴ�
	WaitForSingleObject(m_hRecDeqFullSemaphore, INFINITE);
	MSG_PTR msg = NULL;

	m_csReceive.Lock();
	// ȡ����Ϣ���е�һ����Ϣ
	if (!m_receiveDeq.empty()) {
		MSG_ITER it = m_receiveDeq.begin();
		msg = *it;
		m_receiveDeq.pop_front();
	}
	m_csReceive.Unlock();

	// ���ź���+1
	ReleaseSemaphore(m_hRecDeqEmptySemphore, 1, NULL);

	return msg;
}

void CMsgManager::init()
{
	// �������ն����ź���
	m_hRecDeqEmptySemphore = CreateSemaphore(NULL, MAX_DEQUE_MESSAGE_SIZE, MAX_DEQUE_MESSAGE_SIZE, NULL);
	m_hRecDeqFullSemaphore = CreateSemaphore(NULL, 0, MAX_DEQUE_MESSAGE_SIZE, NULL);

	if (NULL == m_hRecDeqEmptySemphore || NULL == m_hRecDeqFullSemaphore)
	{
		//cocos2d::log("semaphore create failed!");
		assert(0);
	}
}