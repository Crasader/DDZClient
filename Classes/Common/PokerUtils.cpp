#include "PokerUtils.h"

bool CPokerUtils::IsThreeWithOne(vector<CPoker *>& vecPoker) {
	if (vecPoker[0]->getValue() == vecPoker[1]->getValue() &&
		vecPoker[0]->getValue() == vecPoker[2]->getValue())
		return true;
	else if (vecPoker[0]->getValue() == vecPoker[2]->getValue() &&
		vecPoker[0]->getValue() == vecPoker[3]->getValue())
		return true;
	else if (vecPoker[1]->getValue() == vecPoker[2]->getValue() &&
		vecPoker[1]->getValue() == vecPoker[3]->getValue())
		return true;
	else
		return false;
}

bool CPokerUtils::IsTreeWithTwo(vector<CPoker *>& vecPoker) {
	if (vecPoker[0]->getValue() == vecPoker[1]->getValue() &&
		vecPoker[0]->getValue() == vecPoker[2]->getValue() &&
		vecPoker[3]->getValue() == vecPoker[4]->getValue())
		return true;
	else if (vecPoker[2]->getValue() == vecPoker[3]->getValue() &&
		vecPoker[2]->getValue() == vecPoker[4]->getValue() &&
		vecPoker[0]->getValue() == vecPoker[1]->getValue())
		return true;

	return false;
}

bool CPokerUtils::IsSingleStraight(vector<CPoker *>& vecPoker) {
	if (vecPoker.size() > 12 || vecPoker.size() < 5)
		return false;

	// A��ֵ��12���������ֵ�Ͳ���˳��
	if (vecPoker[0]->getValue() > 12)
		return false;

	// ѭ������
	int iLastValue = vecPoker[0]->getValue();
	int iCurrentValue;
	for (int i = 1; i < vecPoker.size(); i++) {
		iCurrentValue = vecPoker[i]->getValue();
		//ֵ�������Ͳ���˳��
		if ((iCurrentValue + 1) != iLastValue)
			return false;
		iLastValue = iCurrentValue;
	}
	return true;
}

bool CPokerUtils::IsDoubleStraight(vector<CPoker *>& vecPoker) {
	int iSize = vecPoker.size();
	if (iSize < 6 || iSize % 2 != 0)
		return false;

	// A��ֵ��12���������ֵ�Ͳ�������
	if (vecPoker[0]->getValue() > 12)
		return false;

	// ѭ������
	int iLastValue = vecPoker[0]->getValue();
	int iCurrentValue;
	for (int i = 1; i < vecPoker.size(); i++) {
		iCurrentValue = vecPoker[i]->getValue();
		// i������Ҫ����һ�ű��ǲ�����ͬ��
		if ((i + 1) % 2 == 0 && iCurrentValue != iLastValue)
			return false;

		// i��ż��Ҫ�Ƚ�����һ������ֵ�ǲ������1
		if (i % 2 == 0 && (iCurrentValue + 1) != iLastValue)
			return false;

		iLastValue = iCurrentValue;
	}
	return true;
}

bool CPokerUtils::IsBoomWithSingle(vector<CPoker *>& vecPoker) {
	int	iSize = vecPoker.size();
	if (iSize != 6)
		return false;
	// �м�����һ����ͬ
	if (vecPoker[2]->getValue() != vecPoker[3]->getValue())
		return false;

	// �����������
	if ((vecPoker[0]->getValue() == vecPoker[1]->getValue() &&
		vecPoker[0]->getValue() == vecPoker[2]->getValue()) ||
		(vecPoker[1]->getValue() == vecPoker[4]->getValue() &&
			vecPoker[1]->getValue() == vecPoker[2]->getValue()) ||
			(vecPoker[4]->getValue() == vecPoker[5]->getValue() &&
				vecPoker[4]->getValue() == vecPoker[2]->getValue()))
		return true;

	return false;
}