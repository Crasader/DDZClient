#ifndef _POKER_UTILS_H
#define _POKER_UTILS_H

#include <vector>
#include <UI/Node/Poker.h>

using namespace std;

class CPokerUtils {
public:
	// ����1
	static bool IsThreeWithOne(vector<CPoker *>& vecPoker);

	// ����2
	static bool IsTreeWithTwo(vector<CPoker *>& vecPoker);

	// ˳��
	static bool IsSingleStraight(vector<CPoker *>& vecPoker);

	// ����
	static bool IsDoubleStraight(vector<CPoker *>& vecPoker);

	// ը��������
	static bool IsBoomWithSingle(vector<CPoker *>& vecPoker);

	// ը��������
	static bool IsBoomWithDouble(vector<CPoker *>& vecPoker) {
		int iSize = vecPoker.size();
		if (iSize != 8)
			return false;
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 6; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 2; i < 8; i++)
			temp2.push_back(vecPoker[i]);;

		if (IsBoomWithSingle(temp1)) {
			if (vecPoker[7]->getValue() != vecPoker[6]->getValue())
				return false;
			if (vecPoker[0]->getValue() != vecPoker[1]->getValue() &&
				vecPoker[4]->getValue() != vecPoker[5]->getValue())
				return false;
		}
		else if (IsBoomWithSingle(temp2)) {
			if (vecPoker[0]->getValue() != vecPoker[1]->getValue())
				return false;
			if (vecPoker[2]->getValue() != vecPoker[3]->getValue() &&
				vecPoker[6]->getValue() != vecPoker[7]->getValue())
				return false;
		}

		return true;
	}

	// ���ɻ�����
	static bool IsTwoPlane(vector<CPoker *>& vecPoker) {
		int iSize = vecPoker.size();

		//ͷβ���Ŷ���ͬ��
		if (vecPoker[0]->getValue() == vecPoker[1]->getValue() &&
			vecPoker[0]->getValue() == vecPoker[2]->getValue() &&
			vecPoker[3]->getValue() == vecPoker[4]->getValue() &&
			vecPoker[3]->getValue() == vecPoker[5]->getValue())
			return true;

		return false;
	}

	// ���ɻ����� 9
	static bool IsThreePlane(vector<CPoker *>& vecPoker) {
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 6; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 3; i < 9; i++)
			temp2.push_back(vecPoker[i]);;
		// ͷβ����˫�ɻ�
		if (IsTwoPlane(temp1) && IsTwoPlane(temp2))
			return true;
		return false;
	}

	// �ķɻ����� 12
	static bool IsFourPlane(vector<CPoker *>& vecPoker) {
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 9; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 3; i < 12; i++)
			temp2.push_back(vecPoker[i]);;
		// ͷβ�������ɻ�
		if (IsThreePlane(temp1) && IsThreePlane(temp2))
			return true;
		return false;
	}

	// ��ɻ����� 15
	static bool IsFivePlane(vector<CPoker *>& vecPoker) {
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 12; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 3; i < 15; i++)
			temp2.push_back(vecPoker[i]);;
		// ͷβ�����ķɻ�
		if (IsFourPlane(temp1) && IsFourPlane(temp2))
			return true;
		return false;
	}

	// ���ɻ����� 8
	static bool IsTwoPlaneWithSingle(vector<CPoker *>& vecPoker) {
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 6; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 2; i < 8; i++)
			temp2.push_back(vecPoker[i]);;
		if (IsTwoPlane(temp1) &&
			vecPoker[6]->getValue() != vecPoker[7]->getValue())
			return true;
		else if (IsTwoPlane(temp2) &&
			vecPoker[0]->getValue() != vecPoker[1]->getValue())
			return true;

		return false;
	}

	// ���ɻ����� 10
	static bool IsTwoPlaneWithDouble(vector<CPoker *>& vecPoker) {
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 6; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 4; i < 9; i++)
			temp2.push_back(vecPoker[i]);;
		if (IsTwoPlane(temp1) &&
			vecPoker[6]->getValue() == vecPoker[7]->getValue() &&
			vecPoker[8]->getValue() == vecPoker[9]->getValue())
			return true;
		else if (IsTwoPlane(temp2) &&
			vecPoker[0]->getValue() == vecPoker[1]->getValue() &&
			vecPoker[2]->getValue() == vecPoker[3]->getValue())
			return true;

		return false;
	}

	// ���ɻ����� 12
	static bool IsThreePlaneWithSingle(vector<CPoker *>& vecPoker) {
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 9; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 3; i < 12; i++)
			temp2.push_back(vecPoker[i]);;
		if (IsThreePlane(temp1) &&
			vecPoker[9]->getValue() != vecPoker[10]->getValue() &&
			vecPoker[9]->getValue() != vecPoker[11]->getValue() &&
			vecPoker[10]->getValue() != vecPoker[11]->getValue())
			return true;
		else if (IsThreePlane(temp2) &&
			vecPoker[0]->getValue() != vecPoker[1]->getValue() &&
			vecPoker[0]->getValue() != vecPoker[2]->getValue() &&
			vecPoker[1]->getValue() != vecPoker[2]->getValue())
			return true;

		return false;
	}

	// ���ɻ����� 15
	static bool IsThreePlaneWithDouble(vector<CPoker *>& vecPoker) {
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 9; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 6; i < 15; i++)
			temp2.push_back(vecPoker[i]);;
		if (IsThreePlane(temp1)) {
			// �ж��������ǲ��Ƕ���
			int iLastValue = vecPoker[9]->getValue();
			int iCurrentValue;
			for (int i = 10; i < 15; i++) {
				iCurrentValue = vecPoker[i]->getValue();
				// i��ż��Ҫ����һ�ű��ǲ�����ͬ��
				if (i % 2 == 0 && iCurrentValue != iLastValue)
					return false;

				iLastValue = iCurrentValue;
			}
			return true;
		}
		else if (IsThreePlane(temp2)) {
			// �ж��������ǲ��Ƕ���
			int iLastValue = vecPoker[0]->getValue();
			int iCurrentValue;
			for (int i = 1; i < 6; i++) {
				iCurrentValue = vecPoker[i]->getValue();
				// i��ż��Ҫ����һ�ű��ǲ�����ͬ��
				if ((i + 1) % 2 == 0 && iCurrentValue != iLastValue)
					return false;

				iLastValue = iCurrentValue;
			}
			return true;
		}

		return true;
	}

	// �ķɻ����� 16
	static bool IsFourPlaneWithSingle(vector<CPoker *>& vecPoker) {
		vector<CPoker *> temp1;
		vector<CPoker *> temp2;
		for (int i = 0; i < 12; i++)
			temp1.push_back(vecPoker[i]);;
		for (int i = 4; i < 16; i++)
			temp2.push_back(vecPoker[i]);;
		if (IsFourPlane(temp1)) {
			// �ж�ʣ�����ǲ��ǵ���
			for (int i = 12; i < 16; i++) {
				for (int j = i + 1; j < 16; j++) {
					if (vecPoker[i]->getValue() == vecPoker[j]->getValue())
						return false;
				}
			}
			return true;
		}
		else if (IsFourPlane(temp2)) {
			// �ж�ʣ�����ǲ��ǵ���
			for (int i = 0; i < 4; i++) {
				for (int j = i + 1; j < 4; j++) {
					if (vecPoker[i]->getValue() == vecPoker[j]->getValue())
						return false;
				}
			}
			return true;
		}

		return false;
	}
};

#endif