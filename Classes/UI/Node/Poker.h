#ifndef _POKER_H
#define _POKER_H

#include <cocos2d.h>

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
	CPoker();
	static cocos2d::Node * create(int number, int value, PokerSuit suit);
	bool init(int number, int value, PokerSuit suit);
	void initPoker();

private:
	cocos2d::Sprite * m_spPoker;		// �˿˾���
	int m_pokerNumber;					// ������
	int m_value;						// ��ֵ
	PokerSuit m_suit;					// ��ɫ
};


#endif