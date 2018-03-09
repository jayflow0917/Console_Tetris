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

// 경계 체크
// x는 가로, y는 세로를 의미
bool CStage::CheckBlock(int x, int y)
{
	// 바닥에 닿았을 경우 true를 리턴
	if (y >= STAGE_HEIGHT)
		return true;
	// 양옆벽을 넘어가는 경우 true를 리턴. 하지만 MoveLeft, MoveRight
	// 에서 제어를 할 것이므로 이 경우는 발생하지 않음.
	else if (x < 0 || x >= STAGE_WIDTH)
		return true;

	// 기존에 쌓여있는 도형에 닿는 경우 true 리턴.
	return ('0' <= m_Stage[y][x] && m_Stage[y][x] <='6');
}

// 다음 도형을 출력하기 전 현재 도형을 stage에 추가시키는 함수
void CStage::AddBlock(CShape * pShape, const POSITION & tPos)
{
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			// 도형이 쌓였을 때 도형의 색을 유지하려면 어떻게 해야할까?
			// 1. 도형클래스를 리스트에 추가하는 경우(기억공간 낭비 가능성)
			// 2. stage 좌표에 추가하는 경우
			// 각 도형에 0~6까지 인덱스를 부여해서 m_Stage[i][j]를
			// 0이 아닌 0~6까지로 하고 빈공간의 경우 9로.
			// 이렇게 하면 도형색을 각각 표현가능함.

			// 현재블럭의 네모칸 하나하나를 얻어온다.
			char BlockXY = pShape->GetBlock(j, i);
			if ('0' <= BlockXY && BlockXY <= '6')
			{
				// tPos.y는 바닥을 의미
				m_Stage[tPos.y - (3 - i)][tPos.x + j] = BlockXY;

				bool bLine = true;
				// 현재 줄을 체크한다.
				for (int k = 0; k < STAGE_WIDTH; ++k)
				{
					// 현재 줄이 하나라도 빈칸이라면 if문 수행
					if (m_Stage[tPos.y - (3 - i)][k] == '9')
					{
						bLine = false;
						break;
					}
				}
				// 현재 블럭이 채워진 줄이 모두 블럭이라면 한 줄 지워준다.
				// 위의 블럭들을 모두 한칸씩 내려준다.
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

// stage 틀 생성
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

// Stage의 벽과 빈공간 NextShape을 위한 공간을 만든다.(출력한다)
void CStage::Render()
{
	// Core의 while문 내에서 Render를 주기적으로 호출함으로써 매번 맵을
	// 다시 출력한다. 그러므로 도형으로 옮겨간 Cursor 위치를 맵을 출력하기
	// 위한 위치로 다시 옮겨줘야 한다.
	CCore::GetInst()->SetConsolePos(-1, 0);

	// 상하좌우 벽을 한줄 추가하는 것이므로 
	// 상수로 설정한 값들보다 +2 해주어야 한다.
	for (int i = 0; i < STAGE_HEIGHT + 1; ++i)
	{
		for (int j = 0; j < STAGE_WIDTH + 2; ++j)
		{
			if (i == 0 && (j == 0 || j == STAGE_WIDTH + 1))
				cout << "▩";
			else if (i == STAGE_HEIGHT)
				cout << "▩";
			else if(j ==0)
				cout << "▩";
			else if(j == STAGE_WIDTH +1)
				cout << "▩";
			else
			{
				if (m_Stage[i][j - 1] == '9')
					cout << "  ";
				else
				{

					// stage에 쌓인 도형들의 각각의 색을 출력한다
					CCore::GetInst()->SetColor((int)m_Stage[i][j - 1] + 8, 0);
					cout << "■";
					CCore::GetInst()->SetColor(15, 0);
				}
			}
		}

		cout << endl;
	}

	// Next Shape 를 위한 공간
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			CCore::GetInst()->SetConsolePos(11 + j, i);
			cout << "  " << endl;
		}
		CCore::GetInst()->SetConsolePos(12, 1);
		cout << "Next Shape" << endl;
	}

	// 안내사항 출력
	CCore::GetInst()->SetConsolePos(12, 8);
	cout << "  ▲   : Rotation          ESC   : Quit" << endl;
	CCore::GetInst()->SetConsolePos(12, 9);
	cout << "◀  ▶ : Left | Right       P    : Pause" << endl;
	CCore::GetInst()->SetConsolePos(12, 10);
	cout << "  ▼   : Soft Drop      SpaceBar : Hard Drop" << endl;
}
