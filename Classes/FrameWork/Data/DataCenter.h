#pragma once
#ifndef _DATA_CENTER_H
#define _DATA_CENTER_H

#include "Common/Singleton.h"
#include "FrameWork/Net/Protocol/protobuf.hpp"
#include "protobuf_processor.hpp"
#include <list>
#include <memory>
#include <proto/user.pb.h>
#include <proto/base.pb.h>
#include <proto/room.pb.h>
#include <protobuf_define.hpp>
#include <card.hpp>
enum ReconnectRoomState {
	CALL = 0,
	RUSH = 1,
	PLAY = 2
};

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

struct SeatInfo {
	int8_t index;
	bool ready;
	PlayerInfo playerInfo;
};

// �Ծ���Ϣ
struct GameOverInfo {
public:
	int _landlordPosition;
};

typedef std::shared_ptr<RoomInfo> ROOM_INFO_PTR;

class CDataCenter
{
public:
	static CDataCenter * getInstance() {
		static CDataCenter instance;
		return &instance;
	}
	~CDataCenter();
public:
	std::list<ROOM_INFO_PTR> & getRoomInfoList();
	int getCurrentUserId();
	std::string & getUserAccount();
	int getCurrentRoomId();
	int getCurrentSeatPosition();

	void process(std::shared_ptr<proto::Protobuf> msg);

private:
	void dealWithLoginResponse(user::LoginResp & rsp);			// �����¼��Ӧ
	void dealWithRegisterResponse(user::RegisterResp & rsp);

	void dealWithEnterRoomResponse(room::EnterRoomResp & rsp);		// ���뷿����Ӧ
	void dealWithCreateRoomResponse(room::CreateRoomResp & rsp);		// ����������Ӧ
	void dealWithGetRoomResponse(room::GetRoomResp & rsp);			// ��ȡ������Ӧ
	void dealWithLeaveRoomResponse(room::LeaveRoomResp & rsp);		// �뿪������Ӧ
	void dealWithReadyResponse(room::ReadyResp & rsp);
	void dealWithLandlordResponse(room::LandlordResp & rsp);
	void dealWithPlayResponse(room::PlayResp & rsp);
	void dealWithGetSeatInfoResponse(room::GetSeatInfoResp & rsp);

	void dealWithGameBegin(room::GameBeginNtf & ntf);
	void dealWithPutCard(room::PutCardNtf & ntf);
	void dealWithPutLandlordCard(room::PutLandlordCardNtf & ntf);
	void dealWithPlayNtf(room::PlayNtf & ntf);
	void dealWithGameOver(room::GameOverNtf & ntf);

	void dealWithOtherEnterInRoom(room::EnterRoomNtf & ntf);			// ������ҽ��뷿��
	void dealWithOtherLeaveRoom(room::LeaveRoomNtf & ntf);
	void dealWithOtherReady(room::ReadyNtf & ntf);
	void dealWithOtherLandlord(room::LandlordNtf & ntf);

	void dealWithLostFromRoomMsg(room::LostFromRoomMsg & msg);
	void dealWithReconnectResponse(room::ReconnectResp & rsp);

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
	int m_landlord;

	std::map<int, Card> m_cards;

	ProtobufProcessor m_processor;
};

#endif


