#include "Core.h"
#include "StageManager.h"
#include "ShapeManager.h"

CCore*	CCore::m_pInst = NULL;

CCore::CCore()	:
	m_bLoop(true),
	// �ܼ�â �ڵ� ����
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
	// �����ڿ��� �ܼ�â �ڵ� ������ �����ϴ� ���
	if (m_hConsole == INVALID_HANDLE_VALUE)
		return false;

	//Ŀ���� ���ֱ� ����.
	CursorInfo.bVisible = FALSE;
	CursorInfo.dwSize = 1;
	SetConsoleCursorInfo(m_hConsole, &CursorInfo);

	// Stagemanager �ʱ�ȭ
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
	// Tetris������ Ư�����ڸ� ����Ͽ� 1ĭ�� ǥ���ϴµ� ��ĭ�� 2����Ʈ��
	// ����Ѵ�. �׷��� ������ *2�� ���ش�. x�� +1���� ������ stage��
	// ���� �� stage�� �ѷ��ΰ� �ִ� ���� ������ ������ ����ϱ� ���ؼ�.
	COORD	pos = { (x + 1) * 2, y };
	SetConsoleCursorPosition(m_hConsole, pos);
}

void CCore::SetColor(int color, int bgcolor)
{
	color &= 0xf;
	bgcolor &= 0xf;
	SetConsoleTextAttribute(m_hConsole, (bgcolor << 4) | color);
}
