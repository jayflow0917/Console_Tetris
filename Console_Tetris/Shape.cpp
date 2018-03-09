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
			m_cShape[i][j] = '9';
			m_cNextShape[i][j] = '9';
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
	m_iNowType = (int)eType;

	// eType�� ���� m_iDir�� �޸����� ��.

	// ���� : O J L I S T Z
	// ���� : U L R R R U R
	if (eType == ST_O || eType == ST_T) {}
	else if (eType == ST_J)
		m_iDir = RD_LEFT;
	else
		m_iDir = RD_RIGHT;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			// �ʱ� Rotation ����
			m_cShape[i][j] = m_cBlocks[m_iNowType][m_iDir][i][j];
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

			if (m_cShape[i][j] != '9')
			{
				// �ܼ�â�� ����� ��ǥ�� ������ �Ŀ� ����Ѵ�.
				CCore::GetInst()->SetConsolePos(iXIndex, iYIndex);
				CCore::GetInst()->SetColor((int)m_cShape[i][j] + 8, 0);
				cout << "��";
				CCore::GetInst()->SetColor(15, 0);
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

			if (m_cShape[i][j] != '9')
			{
				CCore::GetInst()->SetConsolePos(iXIndex, iYIndex);
				CCore::GetInst()->SetColor((int)m_cShape[i][j] + 8, 0);
				cout << "��";
				CCore::GetInst()->SetColor(15, 0);
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
			if (m_cShape[i][j] != '9')
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
							if (m_cShape[k][l] != '9')
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
	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_cShape[i][j] != '9')
			{
				if (pStage->CheckBlock(m_tPos.x + j - 1, m_tPos.y - (3 - i)))
				{
					return;
				}
			}
		}
	}

	--m_tPos.x;
}

void CShape::MoveRight()
{
	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_cShape[i][j] != '9')
			{
				if (pStage->CheckBlock(m_tPos.x + j + 1, m_tPos.y - (3 - i)))
				{
					return;
				}
			}
		}
	}

	++m_tPos.x;
}

void CShape::Rotation()
{
	CStage* pStage = CStageManager::GetInst()->GetCurrentStage();

	// ������ Rotation�ߴٰ� �������� ���� 4*4 ������ ��ġ�� stage�� 
	// ���ؼ� ���ɿ��θ� �Ǵ��Ѵ�.
	++m_iDir;
	m_iDir %= RD_END;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m_cNextShape[i][j] = m_cBlocks[m_iNowType][m_iDir][i][j];
			if (m_cNextShape[i][j] != '9') {
				if (pStage->CheckBlock(m_tPos.x + j, m_tPos.y - (3 - i)))
				{
					// ������ m_iDir�� RD_END�� �������Ƿ� 0~3����
					// ���� �����Ƿ� -1�� �� ���� ó���� ����� �Ѵ�.
					if ((--m_iDir) == -1)
						m_iDir = 3;
					return;
				}

			}
		}
	}

	// ���� ȸ�� �������� �ٲ��ش�.
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			m_cShape[i][j] = m_cNextShape[i][j];
		}
	}
}
