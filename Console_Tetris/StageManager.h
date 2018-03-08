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
	// StageManager에서 Stage를 관리하기 위해서는 stage정보가 필요한데
	// include가 되어있지 않으니 class를 앞에써서 전방선언을 해준다.
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

