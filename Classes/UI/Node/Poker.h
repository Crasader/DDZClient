#ifndef _POKER_H
#define _POKER_H

#include <cocos2d.h>
#include <string>

enum PokerSuit
{
	SUIT_SPADE,				// ����
	SUIT_HEART,				// ����
	SUIT_DIAMOND,			// ����
	SUIT_CLUB,				// ÷��
	SUIT_SMALL_JACKER,		// С��
	SUIT_BIG_JACKER,		// ���� 
};

class CPoker
	: public cocos2d::Node
{
public:
	static std::string getPokerFileName(int number, PokerSuit suit);

public:
	CPoker();
	static cocos2d::Node * create(int number, int value, PokerSuit suit);
	bool init(int number, int value, PokerSuit suit);
	void initPoker();
	virtual void onEnter();
	virtual void onExit();
	bool onTouchBegin(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event);
	void onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * event);

public:
	void updatePositionY();
	bool getChoose();
	void setChoose(bool isChoose);
	int getValue();
	int getSuit();
	int getNumber();

private:
	cocos2d::Sprite * m_spPoker;		// �˿˾���
	int m_pokerNumber;					// ������
	int m_value;						// ��ֵ
	PokerSuit m_suit;					// ��ɫ
	bool m_choose;						// �Ƿ�ѡ��
};


#endif