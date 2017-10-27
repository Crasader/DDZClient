#include "MsgManager.h"
#include <NetManager.h>
#include <AppFunc.h>
#include <ModuleManager.h>
#include <cocos2d.h>

bool CMsgLooper::m_flag = false;
ThreadLib::ThreadID CMsgLooper::m_receiveThread = 0;

void CMsgLooper::update(float dt)
{
	// �ַ�������Ϣ
	CModuleManager::getInstance()->dispatchMsg();
}

void CMsgLooper::beginReceiveThread()
{
	m_flag = false;
	try {
		m_receiveThread = ThreadLib::Create(CMsgLooper::handleReceiveThread, NULL);
	}
	catch (ThreadLib::Exception e) {
		// ���������߳�ʧ��
		assert(0);
	}
}

void CMsgLooper::endReceiveThread()
{
	m_flag = true;
}

void CMsgLooper::handleReceiveThread(void * pData)
{
	cocos2d::log("begin receive thread");
	while (!m_flag) {
		NetManagerIns->getGameServerSocket().receive();
	}
	ThreadLib::Kill(m_receiveThread);
	cocos2d::log("end receive thread");
}

CMsgLooper::CMsgLooper()
{
	GDirector->getScheduler()->scheduleUpdate(this, 0, false);//����Ϸ֡����ͬ�Ļص�����
}

CMsgLooper::~CMsgLooper()
{
	GDirector->getScheduler()->unscheduleUpdate(this);
	endReceiveThread();
}

bool CMsgDeque::receivedMsgEmpty()
{
	bool bFlag = false;

	// ���ٽ���Դ���з����ǻ����
	m_csReceive.Lock();

	if (m_receiveDeq.empty())
		bFlag = true;

	m_csReceive.Unlock();

	return bFlag;
}

void CMsgDeque::insertReceivedMsg(MSG_PTR pMsg)
{
	// ��Ϣ����ȴ�
	WaitForSingleObject(m_hRecDeqEmptySemphore, INFINITE);

	m_csReceive.Lock();
	m_receiveDeq.emplace_back(pMsg);
	m_csReceive.Unlock();

	// ���ź���+1
	ReleaseSemaphore(m_hRecDeqFullSemaphore, 1, NULL);
}

MSG_PTR CMsgDeque::getReceivedMsg()
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

void CMsgDeque::init()
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

bool CMsgManager::init()
{
	m_looper.beginReceiveThread();
	return true;
}
