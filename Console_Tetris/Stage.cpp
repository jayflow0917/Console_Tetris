#include "Stage.h"
#include "Core.h"



CStage::CStage()	:
	m_iSpeed(5)
{
}


CStage::~CStage()
{
}

// x�� ����, y�� ���θ� �ǹ�
bool CStage::CheckBlock(int x, int y)
{
	// �ٴڿ� ����� ��� true�� ����
	if (y >= STAGE_HEIGHT)
		return true;
	// �翷���� �Ѿ�� ��� true�� ����. ������ MoveLeft, MoveRight
	// ���� ��� �� ���̹Ƿ� �� ���� �߻����� ����.
	else if (x < 0 || x >= STAGE_WIDTH)
		return true;

	// ������ �׿��ִ� ������ ��� ��� true ����.
	return m_Stage[y][x] == '0';
}

// ���� ������ ����ϱ� �� ���� ������ stage�� �߰���Ű�� �Լ�
void CStage::AddBlock(CShape * pShape, const POSITION & tPos)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			// ������ �׿��� �� ������ ���� �����Ϸ��� ��� �ؾ��ұ�?
			// ����Ŭ������ ����Ʈ�� �߰��ϴ� ���(������ ���� ���ɼ�)
			// stage ��ǥ�� �߰��ϴ� ���.... ��
			// �� ������ 0~7���� �ε����� �ο��ؼ� m_Stage[i][j]��
			// 0�� �ƴ� 0~7������ �ϰ� ������� ��� -1��.
			// �̷��� �ϸ� �������� ���� ǥ��������.
		}
	}
}

bool CStage::Init()
{
	for (int i = 0; i < STAGE_HEIGHT; ++i)
	{
		for (int j = 0; j < STAGE_WIDTH; ++j)
		{
			m_Stage[i][j] = '1';
		}
	}
	return true;
}

// Stage�� ���� ����� NextShape�� ���� ������ �����.(����Ѵ�)
void CStage::Render()
{
	// Core�� while�� ������ Render�� �ֱ������� ȣ�������ν� �Ź� ����
	// �ٽ� ����Ѵ�. �׷��Ƿ� �������� �Űܰ� Cursor ��ġ�� ���� ����ϱ�
	// ���� ��ġ�� �ٽ� �Ű���� �Ѵ�.
	CCore::GetInst()->SetConsolePos(-1, 0);

	for (int i = 0; i < STAGE_HEIGHT + 1; ++i)
	{
		for (int j = 0; j < STAGE_WIDTH + 2; ++j)
		{
			if (i == 0 && (j == 0 || j == STAGE_HEIGHT + 1))
				cout << "��";
			else if (i == STAGE_HEIGHT)
				cout << "��";
			else if(j ==0)
				cout << "��";
			else if(j == STAGE_WIDTH +1)
				cout << "��";
			else
			{
				if (m_Stage[i][j - 1] == '1')
					cout << "  ";
				else
					cout << "��";
			}
		}

		cout << endl;
	}

	// Next Shape �� ���� ����
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			CCore::GetInst()->SetConsolePos(11 + j, i);
			cout << "  " << endl;
		}
		CCore::GetInst()->SetConsolePos(12, 1);
		cout << "Next Shape" << endl;
	}
}
