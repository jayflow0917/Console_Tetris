// stage 설계를 위한 stage관리자이다.

#pragma once

#include "value.h"

class CStageManager
{
private:
	CStageManager();
	~CStageManager();

private:
	static CStageManager*	m_pInst;

public:
	static CStageManager*	GetInst()
	{
		if (!m_pInst)
			m_pInst = new CStageManager;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	/*
	 클래스 전방선언이란?
	 헤더파일에서 헤더파일을 포함시키는 행위가 컴파일 시간을 
	 증가시키기 때문에 이를 막기 위해 포인터 객체를 선언할 때에는 
	 클래스 선언 전에 필요한 클래스를 명시하여 헤더파일의 중복을 
	 막을 수 있다.
	 단 헤더파일을 포함하지 않아, 클래스에 대한 정보가 없기 때문에 
	 포인터 객체만 사용 가능하다.

	 StageManager에서 Stage를 관리하기 위해서는 stage정보가 필요한데
	 include가 되어있지 않으니 class를 앞에써서 전방선언을 해준다.
	*/
	class CStage*		m_pCurStage;

public:
	class CStage*	GetCurrentStage() const
	{
		return m_pCurStage;
	}

public:
	bool Init();
	void Run();
	
};

