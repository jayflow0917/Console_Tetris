#include "Shape.h"
#include "Core.h"
#include "Stage.h"
#include "StageManager.h"



CShape::CShape()
{
	m_iDir = RD_UP;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_cShape[i][j] = '1';
		}
	}
}


CShape::~CShape()
{
}

bool CShape::Init(SHAPE_TYPE eType)
{
	m_tPos.x = 4;
	m_tPos.y = 0;

	// �ʱ� Rotation ����
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m_cShape[i][j] = m_cBlocks[eType][0][i][j];
		}
	}

	return true;
}

void CShape::Render()
{
	for (int i = 0; i < 4; ++i)
	{
		int iYIndex = m_tPos.y - (3 - i);
		if (iYIndex < 0)
			continue;

		for (int j = 0; j < 4; ++j)
		{
			int iXIndex = m_tPos.x + j;
			//if (iXIndex >= STAGE_WIDTH)
			//	continue;

			if (m_cShape[i][j] == '0')
			{
				// �ܼ�â�� ����� ��ǥ�� ������ �Ŀ� ����Ѵ�.
				CCore::GetInst()->SetConsolePos(iXIndex, iYIndex);
				cout << "��";
			}
		}
		cout << endl;
	}
}

void CShape::RenderNext()
{
	for (int i = 0; i < 4; ++i)
	{
		int iYIndex = m_tPos.y - (3 - i);
		
		for (int j = 0; j < 4; ++j)
		{
			int iXIndex = m_tPos.x + j;

			if (m_cShape[i][j] == '0')
			{
				CCore::GetInst()->SetConsolePos(iXIndex, iYIndex);
				cout << "��";
			}
		}
		cout << endl;
	}
}

// ������ ������ �� �ִ� ��� false�� ������ �� ���� ���(�ٴڿ� ��Ұų�)
// true�� �����Ѵ�.
bool CShape::MoveDown()
{
	CStage*	pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_cShape[i][j] == '0')
			{
				// (3-i)�� �ƴ� (2-i)�� üũ�ϴ� ������ �����ٷ� ������ 
				// �������ٰ� �����ϰ� ������ �������� üũ�ϱ� ����.
				// �����ٷ� ������ �� ���� ��� true�� ����.
				if (pStage->CheckBlock(m_tPos.x + j, m_tPos.y - (2 - i)))
				{
					// �ٴڿ� ���� �Ŀ� ���� ������ ���� �κ��� �ϳ���
					// ��ǥ�� 0���� �۴ٸ� ����
					for (int k = 0; k < 4; ++k)
					{
						for (int l = 0; l < 4; ++l)
						{
							if (m_cShape[k][l] == '0')
							{
								if (m_tPos.y - (3 - k) < 0)
								{
									CCore::GetInst()->End();
									break;
								}
							}
						}
					}

					// ���� ���� ��Ұų� �ؼ� ���̻� movedown�� �� 
					// ���� ��� true�� ����.
					return true;
				}
			}
		}
	}

	// ���� ������ movedown�� �� ������ y���� +1 �ѵ� false�� �����Ѵ�.
	++m_tPos.y;

	return false;
}

void CShape::MoveLeft()
{
	// ���ʺ��� ���� ���̻� ������ �� ���� ���
	if (m_tPos.x == 0)
		return;

	// ���� �ƴ� �׿��ִ� ���鿡 ���� ���̻� ������ �� ���� ���

	--m_tPos.x;
}

void CShape::MoveRight()
{
	++m_tPos.x;
}

void CShape::Rotation()
{
}
