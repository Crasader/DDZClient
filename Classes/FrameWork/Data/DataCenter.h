#pragma once
#ifndef _DATA_CENTER_H
#define _DATA_CENTER_H

#include "Common/Singleton.h"
#include "IModule.h"
#include "FrameWork/Net/Protocol/Code.h"
#include <list>
#include <memory>

// ������Ϣ
struct RoomInfo {
public:
	RoomInfo()
	{
		_roomID = 0;
		_roomName = "";
		_sitUserNum = 0;
		_statu = 0;

	}
	~RoomInfo() = default;
public:
	int									_roomID;
	short								_sitUserNum;			
	std::string							_roomName;				
	short								_statu;
};

// �����Ϣ
struct PlayerInfo {
	int _userId;
	std::string _userName;
	std::string _userHead;
};

// �Ծ���Ϣ
struct GameOverInfo {
public:
	int _landlordPosition;
};

typedef std::shared_ptr<RoomInfo> ROOM_INFO_PTR;

class CDataCenter
	: public IModule
{
public:
	static CDataCenter * getInstance() {
		static CDataCenter instance;
		return &instance;
	}
	virtual bool init();
	virtual void handle(std::shared_ptr<zhu::SelfDescribingMessage> pTmpMsg);
	~CDataCenter();

public:
	void dealWithLoginResponse(MessagePtr pMsg);			// �����¼��Ӧ

	void dealWithEnterRoomResponse(MessagePtr pMsg);		// ���뷿����Ӧ
	void dealWithCreateRoomResponse(MessagePtr pMsg);		// ����������Ӧ
	void dealWithGetRoomResponse(MessagePtr pMsg);			// ��ȡ������Ӧ
	void dealWithLeaveRoomResponse(MessagePtr pMsg);		// �뿪������Ӧ
	void dealWithOtherEnterInRoom(MessagePtr pMsg);			// ������ҽ��뷿��
	void dealWithPlayerReadyMsg(MessagePtr pMsg);			// ���׼����Ϣ
	void dealWithRoomStatuChangeMsg(MessagePtr pMsg);		// ����״̬�ı�
	void dealWithDispatchPokerMsg(MessagePtr pMsg);			// ����
	void dealWithCallLandlordMsg(MessagePtr pMsg);			// �������
	void dealWithPlayResponse(MessagePtr pMsg);				// ������Ӧ

public:
	std::list<ROOM_INFO_PTR> & getRoomInfoList();
	int getCurrentUserId();
	std::string & getUserAccount();
	int getCurrentRoomId();
	int getCurrentSeatPosition();

private:
	CDataCenter();
	
private:
	// ������Ϣ
	int m_userId;
	std::string m_userAccount;
	int m_currentRoomId;

	// �����б�
	std::list<ROOM_INFO_PTR> m_roomInfoList;
	int m_currentSeatPosition;
};

#endif


