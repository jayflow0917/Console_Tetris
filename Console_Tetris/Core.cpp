#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

CCore*	CCore::m_pInst = NULL;

CCore::CCore()	:
	m_bLoop(true),
	// 콘솔창 핸들 생성
	m_hConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{
	srand((unsigned int)time(0));
}


CCore::~CCore()
{
	CShapeManager::DestroyInst();
	CStageManager::DestroyInst();
}

bool CCore::Init()
{
	// 생성자에서 콘솔창 핸들 생성이 실패하는 경우
	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	//커서를 없애기 위함.
	CursorInfo.bVisible = FALSE;
	CursorInfo.dwSize = 1;
	SetConsoleCursorInfo(m_hConsole, &CursorInfo);

	// Stagemanager 초기화
	if (!CStageManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	while (m_bLoop)
	{
		CShapeManager::GetInst()->Update();

		CStageManager::GetInst()->Run();
		CShapeManager::GetInst()->Render();

		Sleep(100);
	}
}

void CCore::SetConsolePos(int x, int y)
{
	// Tetris에서는 특수문자를 사용하여 1칸을 표현하는데 한칸은 2바이트를
	// 사용한다. 그렇기 때문에 *2를 해준다. x에 +1해준 이유는 stage를
	// 만들 때 stage를 둘러싸고 있는 벽을 제외한 공간을 사용하기 위해서.
	COORD	pos = { (x + 1) * 2, y };
	SetConsoleCursorPosition(m_hConsole, pos);
}

void CCore::SetColor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(m_hConsole, (bgcolor << 4) | color);
}
