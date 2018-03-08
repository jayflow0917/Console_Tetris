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

	// 초기 Rotation 설정
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
				// 콘솔창에 출력할 좌표를 설정한 후에 출력한다.
				CCore::GetInst()->SetConsolePos(iXIndex, iYIndex);
				cout << "■";
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
				cout << "■";
			}
		}
		cout << endl;
	}
}

// 도형이 내려갈 수 있는 경우 false를 내려갈 수 없는 경우(바닥에 닿았거나)
// true를 리턴한다.
bool CShape::MoveDown()
{
	CStage*	pStage = CStageManager::GetInst()->GetCurrentStage();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (m_cShape[i][j] == '0')
			{
				// (3-i)가 아닌 (2-i)를 체크하는 이유는 다음줄로 도형이 
				// 내려갔다고 가정하고 가능한 것인지를 체크하기 위함.
				// 다음줄로 내려갈 수 없는 경우 true를 리턴.
				if (pStage->CheckBlock(m_tPos.x + j, m_tPos.y - (2 - i)))
				{
					// 바닥에 닿은 후에 현재 도형의 블럭인 부분이 하나라도
					// 좌표가 0보다 작다면 종료
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

					// 블럭이 땅에 닿았거나 해서 더이상 movedown할 수 
					// 없는 경우 true를 리턴.
					return true;
				}
			}
		}
	}

	// 현재 도형이 movedown할 수 있으면 y값을 +1 한뒤 false를 리턴한다.
	++m_tPos.y;

	return false;
}

void CShape::MoveLeft()
{
	// 왼쪽벽에 막혀 더이상 진행할 수 없는 경우
	if (m_tPos.x == 0)
		return;

	// 벽이 아닌 쌓여있는 블럭들에 막혀 더이상 진행할 수 없는 경우

	--m_tPos.x;
}

void CShape::MoveRight()
{
	++m_tPos.x;
}

void CShape::Rotation()
{
}
