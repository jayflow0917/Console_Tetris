#pragma once

// Core : 게임을 전체적으로 관리하기 위함.

#include "value.h"

class CCore
{
private:
	CCore();
	~CCore();

private:
	static CCore*	m_pInst;

public:
	static CCore* GetInst()
	{
		if (!m_pInst)
			m_pInst = new CCore;

		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	HANDLE		m_hConsole;
	// 커서를 화면상에서 없애기 위함.
	CONSOLE_CURSOR_INFO CursorInfo;
	bool		m_bLoop;

public:
	bool Init();
	void Run();
	void SetConsolePos(int x, int y);
	void SetColor(int color, int bgcolor);
	void End()
	{
		m_bLoop = false;
	}
};

