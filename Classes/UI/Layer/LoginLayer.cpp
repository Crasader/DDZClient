#include "LoginLayer.h"
#include <editor-support/cocostudio/CocoStudio.h>
#include <ui/CocosGUI.h>
#include <NetManager.h>
#include <user/player.pb.h>
#include <Protocol/Code.h>
#include <MsgManager.h>

USING_NS_CC;

LoginLayer::LoginLayer()
{
}

bool LoginLayer::init()
{
	if (!Layer::init())
		return false;

	m_layerGraphNode = CSLoader::createNode("Layer/login.csb");
	this->addChild(m_layerGraphNode);

	ui::Button * btnLogin = (ui::Button *)m_layerGraphNode->getChildByName("btn_login");
	btnLogin->addClickEventListener(CC_CALLBACK_1(LoginLayer::loginCallback, this));

	return true;
}

void LoginLayer::loginCallback(cocos2d::Ref * target)
{
	if (!NetManagerIns->connectGameServer()) {
		// ��ʾ���ӷ�����ʧ����Ϣ
		return;
	}

	// ���������߳�
	if (!MsgManagerIns->init()) {
		// ���������߳�ʧ��
		return;
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

	if (NetManagerIns->getGameServerSocket().send(msg) > 0) {

		// ��ʾ�ջ��ȴ����������ص�¼����
	}
}
