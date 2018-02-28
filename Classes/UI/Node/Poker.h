#ifndef _POKER_H
#define _POKER_H

#include <cocos2d.h>
#include <string>
#include <card.hpp>

class CPoker
	: public cocos2d::Node
{
public:
	static std::string getPokerFileName( int number, Suit suit);

public:
	CPoker();
	static cocos2d::Node * create(int id, int number, int value, Suit suit);
	bool init(int id, int number, int value, Suit suit);
	void initPoker();

public:
	void updatePositionY();
	bool getChoose();
	void setChoose(bool isChoose);
	int getValue();
	int getSuit();
	int getNumber();
	void click();
	int getCid() { return m_id; }
	
	bool getTouchFlag();
	void setTouchFlag(bool touch);
	void updateColor();
	
private:
	cocos2d::Sprite * m_spPoker;		// �˿˾���
	int m_pokerNumber;					// ������
	int m_value;						// ��ֵ
	Suit m_suit;					// ��ɫ
	bool m_choose;						// �Ƿ�ѡ��
	bool m_touchFlag;					// �������
	int m_id;
};


#endif