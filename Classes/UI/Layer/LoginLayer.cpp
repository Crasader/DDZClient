#include "LoginLayer.h"
#include <editor-support/cocostudio/CocoStudio.h>
#include <ui/CocosGUI.h>
#include <NetManager.h>
#include <user/player.pb.h>
#include <Protocol/Code.h>
#include <MsgManager.h>
#include <TopLayer.h>
#include <UIManager.h>

USING_NS_CC;

CLoginLayer::CLoginLayer()
{
}

bool CLoginLayer::init()
{
	if (!Layer::init())
		return false;

	m_layerGraphNode = CSLoader::createNode("Layer/Login.csb");
	this->addChild(m_layerGraphNode);

	ui::Button * btnLogin = (ui::Button *)m_layerGraphNode->getChildByName("btn_login");
	btnLogin->addClickEventListener(CC_CALLBACK_1(CLoginLayer::loginCallback, this));


	// poker test
#if 0
	for (int i = 1; i <= 13; i++) {
		auto poker = CPoker::create(i, 12, PokerSuit::SUIT_DIAMOND);
		poker->setPosition(GWinSize.width / 4 + poker->getContentSize().width / 4 * i, GWinSize.height / 2);
		this->addChild(poker);
	}
	auto sj = CPoker::create(14, 14, PokerSuit::SUIT_SMALL_JACKER);
	sj->setPosition(GWinSize.width / 4 + sj->getContentSize().width / 4 * 14, GWinSize.height / 2);
	this->addChild(sj);

	auto bj = CPoker::create(15, 15, PokerSuit::SUIT_BIG_JACKER);
	bj->setPosition(GWinSize.width / 4 + sj->getContentSize().width / 4 * 15, GWinSize.height / 2);
	this->addChild(bj);
#endif

	return true;
}

void CLoginLayer::loginCallback(cocos2d::Ref * target)
{
	// ��ʾ�ջ��ȴ����������ص�¼����
	UIManagerIns->getTopLayer()->showLoadingCircle();

	if (!NetManagerIns->isConnected()) {
		// ���ӷ�����
		if (!NetManagerIns->connectGameServer()) {
			UIManagerIns->getTopLayer()->hideLoadingCircle();
			UIManagerIns->getTopLayer()->showDialog("error", "can not connect to server");
			return;
		}

		// ���������߳�
		if (!MsgManagerIns->init()) {
			UIManagerIns->getTopLayer()->hideLoadingCircle();
			UIManagerIns->getTopLayer()->showDialog("error", "create receive thread failed");
			return;
		}
	}
	
		
	// �˺�
	ui::TextField * txtAccount = (ui::TextField *)m_layerGraphNode->getChildByName("img_account")->getChildByName("txt_account");
	std::string strAccount = txtAccount->getString();

	// ����
	ui::TextField * txtPassword = (ui::TextField *)m_layerGraphNode->getChildByName("img_password")->getChildByName("txt_password");
	std::string strPassword = txtPassword->getString();

	// ���͵�¼
	log("login account: %s password: %s", strAccount.c_str(), strPassword.c_str());
	zhu::user::LoginReq msg;
	msg.set_account(strAccount.c_str());
	msg.set_password(strPassword.c_str());

	if (!NetManagerIns->getGameServerSocket().send(msg) > 0) {
		// ��ʾ���͵�¼����ʧ����Ϣ
		UIManagerIns->getTopLayer()->showDialog("error", "send login request error");
		UIManagerIns->getTopLayer()->hideLoadingCircle();
	}

}
