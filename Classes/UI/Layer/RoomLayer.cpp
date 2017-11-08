#include "RoomLayer.h"
#include <editor-support/cocostudio/CocoStudio.h>
#include <NetManager.h>
#include <DataCenter.h>
#include <room/room.pb.h>
#include <UIManager.h>

#include "AppFunc.h"
#include "UI/Node/Poker.h"
#include "NotifacationString.h"
#include "PokerUtils.h"

USING_NS_CC;

CRoomLayer::CRoomLayer()
{
	m_landlordServerPosition = 0;
	m_noPlayFlag = 0;
	m_start = false;
}

bool CRoomLayer::init()
{
	if(!Layer::init())
		return false;

	m_layerGraphNode = CSLoader::createNode("Layer/Room.csb");
	this->addChild(m_layerGraphNode);

	m_currentCardPanel = (ui::Layout *)m_layerGraphNode->getChildByName("pannel_hand_cards");

	// �˳����䰴ť
	auto exitButton = (ui::Button *)m_layerGraphNode->getChildByName("btn_exit_room");
	exitButton->addClickEventListener(CC_CALLBACK_1(CRoomLayer::onExitRoomCallback, this));

	// ׼����ť
	m_readyButton = (ui::Button *)m_layerGraphNode->getChildByName("btn_ready");
	m_readyButton->addClickEventListener(CC_CALLBACK_1(CRoomLayer::onReadyClickListener, this));

	// �����
	auto roomId = (ui::Text *)m_layerGraphNode->getChildByName("txt_room_id");
	roomId->setString(StringUtils::format("Room Id : %d", CDataCenter::getInstance()->getCurrentRoomId()));

	// ��ʼ�������Ϣ
	initPlayer();

	// ��ʼ����������
	initCallLandlordLayer();

	// ��ʼ�����Ʋ�
	initPlayCardLayer();

	// ��ʼ��ÿ����ҵ���Ϣ
	initMsg();

	// ��ʼ��������
	initHandCardPanel();

	return true;
}

void CRoomLayer::initPlayer()
{
	m_players.push_back(m_layerGraphNode->getChildByName("panel_player_0"));
	m_players.push_back(m_layerGraphNode->getChildByName("panel_player_1"));
	m_players.push_back(m_layerGraphNode->getChildByName("panel_player_2"));

	auto name = (ui::Text *)m_players[0]->getChildByName("txt_name");
	name->setString(CDataCenter::getInstance()->getUserAccount());
}

void CRoomLayer::initMsg()
{
	char nodeName[30];
	for (int i = 1; i <= 3; i++) {
		sprintf(nodeName, "sp_player_%d_msg", i);
		//std::string nodeName = cocos2d::StringUtils::format();
		auto msgNode = m_layerGraphNode->getChildByName(nodeName);
		msgNode->setVisible(false);
		m_playerMsgs.push_back((Sprite*)msgNode);
	}
}

void CRoomLayer::initCallLandlordLayer()
{
	m_callLandlordLayer = (Layer *)m_layerGraphNode->getChildByName("file_node_call_landlord");

	// Call Button
	m_callLandlordButton = (ui::Button *)m_callLandlordLayer->getChildByName("btn_call");
	m_callLandlordButton->addClickEventListener(CC_CALLBACK_1(CRoomLayer::onCallLandlordClickListener, this));
	m_callLandlordButton->setVisible(false);
	m_callLandlordButton->setTag(zhu::table::CALL);

	// Not Call Button
	m_notCallLandlordButton = (ui::Button *)m_callLandlordLayer->getChildByName("btn_cancle");
	m_notCallLandlordButton->addClickEventListener(CC_CALLBACK_1(CRoomLayer::onNotCallLandlordClickListener, this));
	m_notCallLandlordButton->setVisible(false);
}

void CRoomLayer::initPlayCardLayer()
{
	m_playCardLayer = (Layer *)m_layerGraphNode->getChildByName("file_node_play_card");

	// Play Button
	m_playButton = (ui::Button *)m_playCardLayer->getChildByName("btn_play");
	m_playButton->addClickEventListener(CC_CALLBACK_1(CRoomLayer::onPlayClickListener, this));
	m_playButton->setVisible(false);

	// Not Play Button
	m_notPlayButton = (ui::Button *)m_playCardLayer->getChildByName("btn_not_play");
	m_notPlayButton->addClickEventListener(CC_CALLBACK_1(CRoomLayer::onNotPlayClickListener, this));
	m_notPlayButton->setVisible(false);

	// Reelect Button
	m_reelectButton = (ui::Button *)m_playCardLayer->getChildByName("btn_reelect");
	m_reelectButton->addClickEventListener(CC_CALLBACK_1(CRoomLayer::onReelectClickListener, this));
	m_reelectButton->setVisible(false);

	char nodeName[30];
	for (int i = 1; i <= 3; i++) {
		sprintf(nodeName, "panel_play_card_%d", i);
		//std::string nodeName = cocos2d::StringUtils::format();
		auto panel = m_playCardLayer->getChildByName(nodeName);
		panel->setVisible(true);
		m_playCardPanel.push_back(panel);
	}
}

void CRoomLayer::initHandCardPanel()
{
	auto pokerPanel = (ui::Layout *)m_layerGraphNode->getChildByName("pannel_hand_cards");
	pokerPanel->addTouchEventListener(CC_CALLBACK_2(CRoomLayer::handCardPanelTouchListener, this));
	pokerPanel->setSwallowTouches(false);
}

void CRoomLayer::onEnter()
{
	Layer::onEnter();
	GEventDispatch->addCustomEventListener(strPlayerEnterInRoom, CC_CALLBACK_1(CRoomLayer::onPlayerEnterInRoom, this));
	GEventDispatch->addCustomEventListener(strPlayerReady, CC_CALLBACK_1(CRoomLayer::onPlayerReady, this));
	GEventDispatch->addCustomEventListener(strAllPlayerReady, CC_CALLBACK_1(CRoomLayer::onGameStart, this));
	GEventDispatch->addCustomEventListener(strFirstDispatchPoker, CC_CALLBACK_1(CRoomLayer::onInitPoker, this)); 
	GEventDispatch->addCustomEventListener(strCallLandlordResult, CC_CALLBACK_1(CRoomLayer::onCallLandlordResult, this));
	GEventDispatch->addCustomEventListener(strShowLandlordPoker, CC_CALLBACK_1(CRoomLayer::onShowLandlordPoker, this));
	GEventDispatch->addCustomEventListener(strUpdateCurrentPoker, CC_CALLBACK_1(CRoomLayer::onUpdateCurrentPoker, this));
	GEventDispatch->addCustomEventListener(strPlayPokerSuccess, CC_CALLBACK_1(CRoomLayer::onPlaySuccess, this));
	GEventDispatch->addCustomEventListener(strShowOtherPlayerPoker, CC_CALLBACK_1(CRoomLayer::onShowOtherPlayerPoker, this));
	GEventDispatch->addCustomEventListener(strGameOver, CC_CALLBACK_1(CRoomLayer::onGameOver, this));
	GEventDispatch->addCustomEventListener(strPlayerOut, CC_CALLBACK_1(CRoomLayer::onPlayerOut, this));
	GEventDispatch->addCustomEventListener(strNoOneCallLandlord, CC_CALLBACK_1(CRoomLayer::onNoOneCallLandlord, this));
}

void CRoomLayer::onExit()
{
	GEventDispatch->removeCustomEventListeners(strPlayerEnterInRoom);
	GEventDispatch->removeCustomEventListeners(strPlayerReady);
	GEventDispatch->removeCustomEventListeners(strAllPlayerReady);
	GEventDispatch->removeCustomEventListeners(strFirstDispatchPoker);
	GEventDispatch->removeCustomEventListeners(strCallLandlordResult);
	GEventDispatch->removeCustomEventListeners(strShowLandlordPoker);
	GEventDispatch->removeCustomEventListeners(strUpdateCurrentPoker);
	GEventDispatch->removeCustomEventListeners(strPlayPokerSuccess);
	GEventDispatch->removeCustomEventListeners(strShowOtherPlayerPoker);
	GEventDispatch->removeCustomEventListeners(strGameOver);
	GEventDispatch->removeCustomEventListeners(strPlayerOut);
	GEventDispatch->removeCustomEventListeners(strNoOneCallLandlord);

	Layer::onExit();
}

void CRoomLayer::onExitRoomCallback(cocos2d::Ref * target)
{
	static zhu::room::LeaveRoomReq msg;
	msg.set_account(CDataCenter::getInstance()->getUserAccount());
	msg.set_roomid(CDataCenter::getInstance()->getCurrentRoomId());
	NetManagerIns->getGameServerSocket().send(msg);

	UIManagerIns->getTopLayer()->showLoadingCircle();
}

void CRoomLayer::onCallLandlordClickListener(cocos2d::Ref * target)
{
	auto dataCenter = CDataCenter::getInstance();
	zhu::table::RequestLandlordReq msg;
	msg.set_account(CDataCenter::getInstance()->getUserAccount());
	msg.set_roomid(dataCenter->getCurrentRoomId());
	msg.set_call(true);
	msg.set_type((zhu::table::RequestLandlordType)m_callLandlordButton->getTag());

	NetManagerIns->getGameServerSocket().send(msg);
}

void CRoomLayer::onNotCallLandlordClickListener(cocos2d::Ref * target)
{
	auto dataCenter = CDataCenter::getInstance();
	zhu::table::RequestLandlordReq msg;
	msg.set_account(CDataCenter::getInstance()->getUserAccount());
	msg.set_roomid(dataCenter->getCurrentRoomId());
	msg.set_call(false);
	msg.set_type((zhu::table::RequestLandlordType)m_callLandlordButton->getTag());

	NetManagerIns->getGameServerSocket().send(msg);
}

void CRoomLayer::onPlayClickListener(cocos2d::Ref * target)
{
	auto dataCenter = CDataCenter::getInstance();
	zhu::table::PlayReq pMsg;
	pMsg.set_account(dataCenter->getUserAccount());
	pMsg.set_roomid(dataCenter->getCurrentRoomId());

	std::vector<CPoker *> vecPoker;
	bool bCorrect = true;

	for (auto it = m_currentPokers.begin(); it != m_currentPokers.end(); it++) {
		auto poker = (CPoker *)*it;
		if (poker->getChoose()) {
			vecPoker.push_back(poker);
		}
	}

	// һ����
	if (vecPoker.size() == 1) {
		pMsg.set_type(zhu::table::PLAY_TYPE::SINGLE);
	}
	// ����
	else if (vecPoker.size() == 2) {
		// ����
		if (vecPoker[0]->getValue() == vecPoker[1]->getValue())
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_SAME);
		// ��ը
		else if ((vecPoker[0]->getSuit() == zhu::table::POKER_SUIT::BIG_JACKER &&
			vecPoker[1]->getSuit() == zhu::table::POKER_SUIT::SMALL_JACKER) ||
			(vecPoker[0]->getSuit() == zhu::table::POKER_SUIT::SMALL_JACKER &&
				vecPoker[1]->getSuit() == zhu::table::POKER_SUIT::BIG_JACKER))
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_JOCKER);
		else
			bCorrect = false;
	}
	// ������
	else if (vecPoker.size() == 3) {
		if (vecPoker[0]->getValue() == vecPoker[1]->getValue() &&
			vecPoker[0]->getValue() == vecPoker[2]->getValue())
			pMsg.set_type(zhu::table::PLAY_TYPE::THREE_SAME);
		else
			bCorrect = false;
	}
	// �ж�������
	else if (vecPoker.size() == 4) {
		// ը��
		if (vecPoker[0]->getValue() == vecPoker[1]->getValue() &&
			vecPoker[0]->getValue() == vecPoker[2]->getValue() &&
			vecPoker[0]->getValue() == vecPoker[3]->getValue())
			pMsg.set_type(zhu::table::PLAY_TYPE::BOMB);
		// ����һ
		else if (CPokerUtils::IsThreeWithOne(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::THREE_SAME_WITH_ONE);
		}
		else
			bCorrect = false;
	}
	// �ж�������
	else if (vecPoker.size() == 5) {
		// ������
		if (CPokerUtils::IsTreeWithTwo(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::THREE_SAME_WITH_TWO);
		}
		// ˳��
		else if (CPokerUtils::IsSingleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::SINGLE_STRAIGHT);
		}
		else
			bCorrect = false;
	}
	// �ж�6����
	else if (vecPoker.size() == 6) {
		// �Ĵ�2��
		if (CPokerUtils::IsBoomWithSingle(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::BOMB_WIHT_SINGLE);
		}
		// ˳��
		else if (CPokerUtils::IsSingleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::SINGLE_STRAIGHT);
		}
		// ����
		else if (CPokerUtils::IsDoubleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_STRAIGHT);
		}
		// �����ɻ�����
		else if (CPokerUtils::IsTwoPlane(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_THREE_SAME);
		}
		else
			bCorrect = false;
	}
	// �жϰ�����
	else if (vecPoker.size() == 8) {
		// �ɻ�������
		if (CPokerUtils::IsTwoPlaneWithSingle(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_THREE_SAME_WITH_SINGLE);
		}
		// ˳��
		else if (CPokerUtils::IsSingleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::SINGLE_STRAIGHT);
		}
		// �Ĵ�����
		else if (CPokerUtils::IsBoomWithDouble(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::BOMB_WIHT_DOUBLE);
		}
		// ����
		else if (CPokerUtils::IsDoubleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_STRAIGHT);
		}
		else
			bCorrect = false;
	}
	// �ж�9����
	else if (vecPoker.size() == 9) {
		// �����ɻ�����
		if (CPokerUtils::IsThreePlane(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::THREE_THREE_SAME);
		}
		// ˳��
		else if (CPokerUtils::IsSingleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::SINGLE_STRAIGHT);
		}
		else
			bCorrect = false;
	}
	// �ж�10����
	else if (vecPoker.size() == 10) {
		// �����ɻ�������
		if (CPokerUtils::IsTwoPlaneWithDouble(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_THREE_SAME_WITH_DOUBLE);
		}
		// ˳��
		else if (CPokerUtils::IsSingleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::SINGLE_STRAIGHT);
		}
		// ����
		else if (CPokerUtils::IsDoubleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_STRAIGHT);
		}
		else
			bCorrect = false;
	}
	// �ж�ʮ������
	else if (vecPoker.size() == 12) {
		// ���ɻ�����
		if (CPokerUtils::IsThreePlaneWithSingle(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::THREE_THREE_SAME_WITH_SINGLE);
		}
		// ˳��
		else if (CPokerUtils::IsSingleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::SINGLE_STRAIGHT);
		}
		// ����
		else if (CPokerUtils::IsDoubleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_STRAIGHT);
		}
		// �ķɻ�����
		else if (CPokerUtils::IsFourPlane(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::FOUR_THREE_SAME);
		}
		else
			bCorrect = false;
	}
	// �ж�15����
	else if (vecPoker.size() == 15) {
		// ���ɻ�����
		if (CPokerUtils::IsThreePlaneWithDouble(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::THREE_THREE_SAME_WITH_DOUBLE);
		}
		// ��ɻ�����
		else if (CPokerUtils::IsFivePlane(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::FIVE_THREE_SAME);
		}
		else
			bCorrect = false;
	}
	// �ж�16����
	else if (vecPoker.size() == 16) {
		// �ķɻ�����
		if (CPokerUtils::IsFourPlaneWithSingle(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::FOUR_THREE_SAME_WITH_SINGLE);
		}
		// ����
		else if (CPokerUtils::IsDoubleStraight(vecPoker)) {
			pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_STRAIGHT);
		}
		else
			bCorrect = false;
	}
	// ˳��
	else if (CPokerUtils::IsSingleStraight(vecPoker)) {
		pMsg.set_type(zhu::table::PLAY_TYPE::SINGLE_STRAIGHT);
	}
	// ����
	else if (CPokerUtils::IsDoubleStraight(vecPoker)) {
		pMsg.set_type(zhu::table::PLAY_TYPE::DOUBLE_STRAIGHT);
	}
	else
		bCorrect = false;

	// ѡ�����Ͳ���ȷ
	if (!bCorrect) {
		UIManagerIns->getTopLayer()->showDialog("error", "choose card error. please reelect");
		
		reelectPoker();
		return;
	}

	// ������
	for (auto p : vecPoker) {
		auto pPoker = pMsg.add_pokers();
		pPoker->set_number(p->getNumber());
		pPoker->set_suit((zhu::table::POKER_SUIT)p->getSuit());
		pPoker->set_value(p->getValue());
	}

	NetManagerIns->getGameServerSocket().send(pMsg);
}

void CRoomLayer::onNotPlayClickListener(cocos2d::Ref * target)
{
	auto dataCenter = CDataCenter::getInstance();
	zhu::table::PlayReq pMsg;
	pMsg.set_roomid(dataCenter->getCurrentRoomId());
	pMsg.set_account(dataCenter->getUserAccount());
	pMsg.set_type(zhu::table::PLAY_TYPE::NO_PLAYER);

	NetManagerIns->getGameServerSocket().send(pMsg);
}

void CRoomLayer::onReelectClickListener(cocos2d::Ref * target)
{
	reelectPoker();
}

void CRoomLayer::onPlayerEnterInRoom(cocos2d::EventCustom * event)
{
	zhu::room::Seat * seat = (zhu::room::Seat *)event->getUserData();
	int serverPosition = seat->position();
	int clientPos = computeClientPosition(serverPosition);

	auto player = m_players[clientPos - 1];
	auto name = (ui::Text *)player->getChildByName("txt_name");
	auto spHead = player->getChildByName("sp_head"); 
	auto spReady = player->getChildByName("sp_ready");
	
	switch (seat->statu())
	{
	case zhu::room::Seat::UNREADY:
		name->setString(seat->playeraccount());
		spHead->setVisible(true);
		spReady->setVisible(false);
		break;
	case zhu::room::Seat::READY:
		name->setString(seat->playeraccount());
		spHead->setVisible(true);
		spReady->setVisible(true);
		break;
	case zhu::room::Seat::NO_PLAYER:
		name->setString("waiting");
		spHead->setVisible(false);
		spReady->setVisible(false);
		break;
	default:
		break;
	}
}

void CRoomLayer::onPlayerReady(cocos2d::EventCustom * event)
{
	zhu::room::ReadyResp * ready = (zhu::room::ReadyResp *)event->getUserData();
	int clientPos = computeClientPosition(ready->position());

	m_players[clientPos - 1]->getChildByName("sp_ready")->setVisible(ready->ready());
}

void CRoomLayer::onGameStart(cocos2d::EventCustom * event)
{
	m_start = true;
	m_callLandlordLayer->setVisible(true);

	for (int i = 1; i <= 3; i++) {
		updatePlayerPokerNumber(i, 17);
		m_players[i - 1]->getChildByName("sp_ready")->setVisible(false);
	}
}

void CRoomLayer::onInitPoker(cocos2d::EventCustom * event)
{
	auto msg = (zhu::table::DispatchPoker *)event->getUserData();

	// �Ƿ����
	if (msg->landlordaccount() == CDataCenter::getInstance()->getUserAccount()) {
		updateCallLandlordButton(true);
	}
	else {
		updateCallLandlordButton(false, false);
		int landlordPosition = computeClientPosition(msg->position());
		m_players[landlordPosition - 1]->getChildByName("img_wait")->setVisible(true);
	}

	// ������ʾ����
	updateCurrentPoker(msg->pockers());
}

void CRoomLayer::onCallLandlordResult(cocos2d::EventCustom * event)
{
	auto msg = (zhu::table::RequestLandlordResp *)event->getUserData();
	std::string & currentAccount = CDataCenter::getInstance()->getUserAccount();

	// δѡ������
	if (msg->calllandlordresult() == zhu::table::ERROR_CODE::NOT_SELECTED_LANDLORD) {
		zhu::table::RequestLandlordType type = msg->type();
		zhu::table::RequestLandlordType nextType = msg->nexttype();
		bool bCall = msg->call();
		std::string strNextAccount = msg->next();
		
		//// ��ǰ����
		if (msg->account() != currentAccount) {
			// �������˵ĵ���ʱ
			showTimeClock(msg->currentposition(), false);			
		}
		else {
			// �����Լ��Ŀ��
			updateCallLandlordButton(false, false);
		}
		// ��ʾ��Ϣ
		updateCallLandlordMsg(msg->currentposition(), type, bCall);
		
		//// ��һ����
		// ��һλ�û����Լ��Ļ�����ʾ
		if (strNextAccount == currentAccount) {
			updateCallLandlordButton(nextType == zhu::table::RequestLandlordType::CALL);
		}
		// ������ʾ���˵ĵ���ʱ
		else {
			showTimeClock(msg->nextposition(), true);
		}
		// ���ص�ǰ������ҵ���Ϣ
		updateCallLandlordMsg(msg->nextposition(), type, bCall, false);
	}
	// ���˽е���
	else if (msg->calllandlordresult() == zhu::table::ERROR_CODE::NO_ONE_CALL_LANDLORD) {
		
	}
	// ѡ������
	else if (msg->calllandlordresult() == zhu::table::ERROR_CODE::SELECTED_LANDLORD) {
		std::string strNextAccount = msg->next();
		m_landlordServerPosition = msg->nextposition();

		// ���ص����İ�ť
		updateCallLandlordButton(false, false);

		// ����������Ϣ��
		hideAllMsg();

		// �������е���ʱ
		hideAllClock();

		m_playCardLayer->setVisible(true);
		// ��ǰ�û�Ϊ����
		if (strNextAccount == currentAccount) {					
			// ��ʾ���ư�ť
			showPlayButton(true);
		}
		// �ȴ���������
		else {
			// ��ʾ��������ʱ
			showTimeClock(m_landlordServerPosition, true);
			// ��������+3
			updatePlayerPokerNumber(m_landlordServerPosition, 20);
		}

		// ����ͷ��
		updateHead();
	}
}

void CRoomLayer::onShowLandlordPoker(cocos2d::EventCustom * event)
{
	auto msg = (zhu::table::DispatchPoker *)event->getUserData();
	auto pokers = msg->pockers();
	auto panelLandlordCard = m_callLandlordLayer->getChildByName("panel_card");

	char buf[20];
	for (int i = 0; i < 3; i++) {
		sprintf(buf, "sp_handlord_card_%d", i + 1);
		auto spCard = (Sprite *)panelLandlordCard->getChildByName(buf);
		spCard->setDisplayFrame(
			GSpriteFrameCache->getSpriteFrameByName(
				CPoker::getPokerFileName(pokers[i].number(), (PokerSuit)pokers[i].suit())));
		spCard->setScale(0.7f);
	}
	
}

void CRoomLayer::onUpdateCurrentPoker(cocos2d::EventCustom * event)
{
	auto msg = (zhu::table::DispatchPoker *)event->getUserData();

	// ��ǰ����û�б仯�򲻸���
	if (msg->pockers().size() == m_currentPokers.size())
		return;

	// ������ʾ����
	updateCurrentPoker(msg->pockers());
}

void CRoomLayer::onPlaySuccess(cocos2d::EventCustom * event)
{
	auto msg = (zhu::table::PlayResp *)event->getUserData();
	auto currentAccount = CDataCenter::getInstance()->getUserAccount();

	// ��һλ������Լ��Ļ�Ҫ����֮ǰ���е���ʾ����ʾ��ť
	if (msg->next() == currentAccount) {
		showTimeClock(msg->nextposition(), false);
		showNoPlay(msg->nextposition(), false);
		showPlayButton(true);
	}
	//������Ҫ��ʾ��һλ��ҵĵ���ʱ�Լ�������һλ��ҵ���ʾ
	else {
		showTimeClock(msg->nextposition(), true);
		showNoPlay(msg->nextposition(), false);
		showPlayButton(false);
	}

	// �����һλ��ҳ�����
	clearPlayPoker(msg->nextposition());

	// ����Ҳ�����Ҫ��ʾ������ť
	if (msg->playresult() == zhu::table::ERROR_CODE::NO_PLAY) {
		showNoPlay(msg->currentposition(), true);
		showTimeClock(msg->currentposition(), false);
		
		// ���β�����Ҫ��������ϵ���
		if (m_noPlayFlag == 1) {
			clearAllPlayPoker();
			m_noPlayFlag = 0;
		}
		else {
			m_noPlayFlag++;
		}
	}
	// ����Ҫ���ظ���ҵ�������Ϣ
	else {
		showTimeClock(msg->currentposition(), false);
		showNoPlay(msg->currentposition(), false);
		m_noPlayFlag = 0;
	}

	// ����Ҳ����Լ��Ļ�Ҫ��������
	if(msg->account() != currentAccount){
		updatePlayerPokerNumber(msg->currentposition(), msg->number());
	}
}

void CRoomLayer::onShowOtherPlayerPoker(cocos2d::EventCustom * event)
{
	auto msg = (zhu::table::DispatchPoker *)event->getUserData();

	updatePlayPoker(msg->pockers(), msg->position());
}

void CRoomLayer::onGameOver(cocos2d::EventCustom * event)
{
	bool landlordWin = *(bool *)event->getUserData();
	int landlordClientPosition = computeClientPosition(m_landlordServerPosition);
	auto spGameOverMsg = (Sprite *)m_playCardLayer->getChildByName("sp_game_over_msg");
	spGameOverMsg->setVisible(true);

	hideAllMsg();
	hideAllClock();
	showPlayButton(false);

	if (landlordWin) {
		// ����Լ��ǵ���
		if (landlordClientPosition == 1) {
			// ��ʾ����ʤ��
			spGameOverMsg->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/text_1.png"));
		}
		// �����Լ���ũ��
		else {
			// ��ʾũ��ʧ��
			spGameOverMsg->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/text_2.png")); 
		}
	}
	else {
		// ����Լ��ǵ���
		if (landlordClientPosition == 1) {
			// ��ʾ����ʧ��
			spGameOverMsg->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/text_0.png"));
		}
		// �����Լ���ũ��
		else {
			// ��ʾũ��ʤ��
			spGameOverMsg->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/text_3.png"));
		}
	}

	reinit();
}

void CRoomLayer::onPlayerOut(cocos2d::EventCustom * event)
{
	std::string account = *(string *)event->getUserData();
	char msgBuf[100];
	sprintf(msgBuf, "%s leave room, game restart", account.c_str());
	UIManagerIns->getTopLayer()->
		showDialog("hint", msgBuf);

	reinit();
}

void CRoomLayer::onNoOneCallLandlord(cocos2d::EventCustom * event)
{
	UIManagerIns->getTopLayer()->showDialog("hint", "No one call, Restart!");
	hideAllMsg();
	hideAllClock();
}

void CRoomLayer::handCardPanelTouchListener(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
	auto pokerPanel = (ui::Layout *)ref;
	auto pokers = pokerPanel->getChildren();

	auto beginPosition = pokerPanel->convertToNodeSpace(pokerPanel->getTouchBeganPosition());
	auto endPosition = pokerPanel->convertToNodeSpace(pokerPanel->getTouchEndPosition());
	auto movePosition = pokerPanel->convertToNodeSpace(pokerPanel->getTouchMovePosition());

	Rect rect;

	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		for (auto & temp : pokers) {
			auto poker = (CPoker *)temp;

			if (poker->getTouchFlag() == true) {
				poker->click();
				poker->setTouchFlag(false);
				poker->updateColor();
			}
		}
	}
	else if (type == cocos2d::ui::Widget::TouchEventType::MOVED) {
		for (auto & temp : pokers) {
			auto poker = (CPoker *)temp;
			if (poker->getTouchFlag() == false) {
				rect.setRect(poker->getPositionX(), poker->getPositionY(), poker->getBoundingBox().size.width / 4, poker->getBoundingBox().size.height);
				if (rect.containsPoint(movePosition)) {
					poker->setTouchFlag(true);
					poker->updateColor();
				}
			}	
		}
	}
	else if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
		for (auto & temp : pokers) {
			auto poker = (CPoker *)temp;
			rect.setRect(poker->getPositionX(), poker->getPositionY(), poker->getBoundingBox().size.width / 4, poker->getBoundingBox().size.height);
			if (rect.containsPoint(beginPosition)) {
				poker->setTouchFlag(true);
				poker->updateColor();
			}
		}
	}
}

int CRoomLayer::computeClientPosition(int serverPosition)
{
	if (serverPosition == CDataCenter::getInstance()->getCurrentSeatPosition())
		return 1;

	int clientPos = 0;

	if (CDataCenter::getInstance()->getCurrentSeatPosition() == 1)
		clientPos = serverPosition;
	else if (CDataCenter::getInstance()->getCurrentSeatPosition() == 2)
		clientPos = serverPosition % 3 + 2;
	else if (CDataCenter::getInstance()->getCurrentSeatPosition() == 3)
		clientPos = serverPosition % 3 + 1;
	return clientPos;
}

void CRoomLayer::updateCallLandlordMsg(int serverPosition, int msg, bool call, bool show)
{
	int clientIndex = computeClientPosition(serverPosition) - 1;
	auto player = m_players[clientIndex];
	auto msgSprite = m_playerMsgs[clientIndex];

	msgSprite->setVisible(show);

	switch (msg) {
	case zhu::table::RequestLandlordType::CALL:
		if (call) {
			// ��
			msgSprite->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/message1.png"));
		}
		else {
			// ����
			msgSprite->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/message0.png"));
		}
		break;
	case zhu::table::RequestLandlordType::RUSH:
		if (call) {
			// ��
			msgSprite->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/message3.png"));
		}
		else {
			// ����
			msgSprite->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/message2.png"));
		}
		break;
	default:
		break;
	}
}

void CRoomLayer::showNoPlay(int serverPosition, bool show)
{
	int clientIndex = computeClientPosition(serverPosition) - 1;
	auto player = m_players[clientIndex];
	auto msgSprite = m_playerMsgs[clientIndex];

	msgSprite->setVisible(show);

	msgSprite->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/buchu.png"));
}

void CRoomLayer::updateCallLandlordButton(bool isCall, bool show)
{

	m_callLandlordButton->setVisible(show);
	m_notCallLandlordButton->setVisible(show);

	if (isCall) {
		m_callLandlordButton->setTag(zhu::table::CALL);
		m_callLandlordButton->loadTextures("UITest/pic/message_jiao.png", "UITest/pic/message_jiao.png", 
			"UITest/pic/message_jiao.png", ui::Widget::TextureResType::PLIST);
		m_notCallLandlordButton->loadTextures("UITest/pic/message_bu.png", "UITest/pic/message_bu.png",
			"UITest/pic/message_bu.png", ui::Widget::TextureResType::PLIST);
	}
	else {
		m_callLandlordButton->setTag(zhu::table::RUSH);
		m_callLandlordButton->loadTextures("UITest/pic/message_qiang.png", "UITest/pic/message_qiang.png",
			"UITest/pic/message_qiang.png", ui::Widget::TextureResType::PLIST);
		m_notCallLandlordButton->loadTextures("UITest/pic/message_buQiang.png", "UITest/pic/message_buQiang.png",
			"UITest/pic/message_buQiang.png", ui::Widget::TextureResType::PLIST);
	}
}

void CRoomLayer::showTimeClock(int serverPosition, bool show)
{
	int landlordPosition = computeClientPosition(serverPosition);
	m_players[landlordPosition - 1]->getChildByName("img_wait")->setVisible(show);
}

void CRoomLayer::showPlayButton(bool show)
{
	m_playButton->setVisible(show);
	m_notPlayButton->setVisible(show);
	m_reelectButton->setVisible(show);
}

void CRoomLayer::updateCurrentPoker(const ::google::protobuf::RepeatedPtrField<zhu::table::Poker>& pokers)
{
	clearAllHandPoker();

	auto pokerPanel = m_layerGraphNode->getChildByName("pannel_hand_cards");

	const float pokerWidth = CPoker::create(1, 1, PokerSuit::SUIT_CLUB)->getContentSize().width;
	int pokerSize = pokers.size();
	const float TOTAL_WIDTH = 1 + (pokerSize - 1) / 4 + (pokerSize - 1) % 4 * 0.25f;

	int iPosition = 0;

	for (auto & poker : pokers) {
		auto createPoker = CPoker::create(poker.number(), poker.value(), (PokerSuit)poker.suit());
		createPoker->setPosition(
			pokerPanel->getContentSize().width / 2 - (pokerWidth * TOTAL_WIDTH / 2 - pokerWidth / 4 * iPosition),
			0);
		pokerPanel->addChild(createPoker);
		m_currentPokers.push_back(createPoker);
		iPosition++;
	}
}

void CRoomLayer::updatePlayPoker(const::google::protobuf::RepeatedPtrField<zhu::table::Poker>& pokers, int position)
{
	int currentIndex = computeClientPosition(position) - 1;
	auto pokerPanel = m_playCardPanel[currentIndex];
	pokerPanel->removeAllChildrenWithCleanup(true);

	const float pokerWidth = CPoker::create(1, 1, PokerSuit::SUIT_CLUB)->getContentSize().width;
	int pokerSize = pokers.size();
	const float TOTAL_WIDTH = 1 + (pokerSize - 1) / 4 + (pokerSize - 1) % 4 * 0.25f;

	int iPosition = 0;

	for (auto & poker : pokers) {
		auto createPoker = CPoker::create(poker.number(), poker.value(), (PokerSuit)poker.suit());
		createPoker->setPosition(
			pokerPanel->getContentSize().width / 2 - (pokerWidth * TOTAL_WIDTH / 2 - pokerWidth / 4 * iPosition),
			0);
		pokerPanel->addChild(createPoker);
		iPosition++;
	}
}

void CRoomLayer::updatePlayerPokerNumber(int serverPosition, int number)
{
	int clientIndex = computeClientPosition(serverPosition) - 1;
	auto player = m_players[clientIndex];
	auto pokerNumber = (ui::TextBMFont *)player->getChildByName("txt_surplus_card_number");
	if (pokerNumber != NULL)
		pokerNumber->setString(StringUtils::toString(number));
}

void CRoomLayer::reelectPoker()
{
	for (auto it = m_currentPokers.begin(); it != m_currentPokers.end(); it++) {
		auto poker = (CPoker *)*it;
		poker->setChoose(false);
		poker->updatePositionY();
	}
}

void CRoomLayer::updateHead()
{
	int landlordClientPosition = computeClientPosition(m_landlordServerPosition);
	for (int i = 0; i < m_players.size(); i++) {
		auto spHead = (Sprite *)m_players[i]->getChildByName("sp_head");

		if (m_start) {
			if (landlordClientPosition == i + 1) {
				// ����Ϊ������ͷ��
				spHead->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/logo_dizhu.png"));
			}
			else {
				// ����Ϊũ���ͷ��
				spHead->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/logo_nongmin.png"));
			}
		}
		else {
			// ����Ϊ������ͷ��
			spHead->setDisplayFrame(GSpriteFrameCache->getSpriteFrameByName("UITest/pic/logo_unknown.png"));
		}	
	}
	
}

void CRoomLayer::hideAllMsg()
{
	showNoPlay(1, false);
	showNoPlay(2, false);
	showNoPlay(3, false);
}

void CRoomLayer::hideAllClock()
{
	showTimeClock(1, false);
	showTimeClock(2, false);
	showTimeClock(3, false);
}

void CRoomLayer::clearPlayPoker(int position)
{
	int currentIndex = computeClientPosition(position) - 1;
	auto pokerPanel = m_playCardPanel[currentIndex];
	pokerPanel->removeAllChildrenWithCleanup(true);
}

void CRoomLayer::clearAllPlayPoker()
{
	for (auto panel : m_playCardPanel) {
		panel->removeAllChildrenWithCleanup(true);
	}
}

void CRoomLayer::reinit()
{
	m_start = false;

	// ��ʾ׼����ť
	m_readyButton->setVisible(true);

	updateHead();
	hideAllClock();
	hideAllMsg();
	clearAllPlayPoker();
	m_callLandlordLayer->setVisible(false);
	m_playCardLayer->setVisible(false);

	updateCallLandlordButton(false, false);
	showPlayButton(false);

	for (int i = 1; i <= 3; i++) {
		updatePlayerPokerNumber(i, 0);
	}

	clearAllHandPoker();

	m_landlordServerPosition = 0;
	m_noPlayFlag = 0;
}

void CRoomLayer::clearAllHandPoker()
{
	auto pokerPanel = m_layerGraphNode->getChildByName("pannel_hand_cards");
	m_currentPokers.clear();
	pokerPanel->removeAllChildrenWithCleanup(true);
}

void CRoomLayer::onReadyClickListener(cocos2d::Ref * target)
{
	m_readyButton->setVisible(false);

	static zhu::room::ReadyReq msg;
	msg.set_account(CDataCenter::getInstance()->getUserAccount());
	msg.set_ready(true);
	msg.set_roomid(CDataCenter::getInstance()->getCurrentRoomId());

	NetManagerIns->getGameServerSocket().send(msg);
}

