#include "Stage.h"
#include "Core.h"
#include "Shape.h"

CStage::CStage()	:
	m_iSpeed(5)
{
}

CStage::~CStage()
{
}

// ��� üũ
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
	return ('0' <= m_Stage[y][x] && m_Stage[y][x] <='6');
}

// ���� ������ ����ϱ� �� ���� ������ stage�� �߰���Ű�� �Լ�
void CStage::AddBlock(CShape * pShape, const POSITION & tPos)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			// ������ �׿��� �� ������ ���� �����Ϸ��� ��� �ؾ��ұ�?
			// 1. ����Ŭ������ ����Ʈ�� �߰��ϴ� ���(������ ���� ���ɼ�)
			// 2. stage ��ǥ�� �߰��ϴ� ���
			// �� ������ 0~6���� �ε����� �ο��ؼ� m_Stage[i][j]��
			// 0�� �ƴ� 0~6������ �ϰ� ������� ��� 9��.
			// �̷��� �ϸ� �������� ���� ǥ��������.

			// ������� �׸�ĭ �ϳ��ϳ��� ���´�.
			char BlockXY = pShape->GetBlock(j, i);
			if ('0' <= BlockXY && BlockXY <= '6')
			{
				// tPos.y�� �ٴ��� �ǹ�
				m_Stage[tPos.y - (3 - i)][tPos.x + j] = BlockXY;

				bool bLine = true;
				// ���� ���� üũ�Ѵ�.
				for (int k = 0; k < STAGE_WIDTH; ++k)
				{
					// ���� ���� �ϳ��� ��ĭ�̶�� if�� ����
					if (m_Stage[tPos.y - (3 - i)][k] == '9')
					{
						bLine = false;
						break;
					}
				}
				// ���� ���� ä���� ���� ��� ���̶�� �� �� �����ش�.
				// ���� ������ ��� ��ĭ�� �����ش�.
				if (bLine)
				{
					for (int k = tPos.y - (3 - i); k > 0; --k)
					{
						for (int l = 0; l < STAGE_WIDTH; ++l)
						{
							m_Stage[k][l] = m_Stage[k - 1][l];
						}
					}
				}
			}
		}
	}
}

// stage Ʋ ����
bool CStage::Init()
{
	for (int i = 0; i < STAGE_HEIGHT; ++i)
	{
		for (int j = 0; j < STAGE_WIDTH; ++j)
		{
			m_Stage[i][j] = '9';
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

	// �����¿� ���� ���� �߰��ϴ� ���̹Ƿ� 
	// ����� ������ ���麸�� +2 ���־�� �Ѵ�.
	for (int i = 0; i < STAGE_HEIGHT + 1; ++i)
	{
		for (int j = 0; j < STAGE_WIDTH + 2; ++j)
		{
			if (i == 0 && (j == 0 || j == STAGE_WIDTH + 1))
				cout << "��";
			else if (i == STAGE_HEIGHT)
				cout << "��";
			else if(j ==0)
				cout << "��";
			else if(j == STAGE_WIDTH +1)
				cout << "��";
			else
			{
				if (m_Stage[i][j - 1] == '9')
					cout << "  ";
				else
				{

					// stage�� ���� �������� ������ ���� ����Ѵ�
					CCore::GetInst()->SetColor((int)m_Stage[i][j - 1] + 8, 0);
					cout << "��";
					CCore::GetInst()->SetColor(15, 0);
				}
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

	// �ȳ����� ���
	CCore::GetInst()->SetConsolePos(12, 8);
	cout << "  ��   : Rotation          ESC   : Quit" << endl;
	CCore::GetInst()->SetConsolePos(12, 9);
	cout << "��  �� : Left | Right       P    : Pause" << endl;
	CCore::GetInst()->SetConsolePos(12, 10);
	cout << "  ��   : Soft Drop      SpaceBar : Hard Drop" << endl;
}
