#pragma once

#include "value.h"

class CShapeManager
{
public:
	CShapeManager();
	~CShapeManager();

private:
	static CShapeManager*	m_pInst;

public:
	static CShapeManager*	GetInst()
	{
		if (!m_pInst)
			m_pInst = new CShapeManager;
		return m_pInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(m_pInst);
	}

private:
	// 현재 도형 표시
	class CShape*	m_pCurShape;
	// 다음 도형 표시
	class CShape*	m_pNextShape;

	// 도형을 움직일 틱을 정한다.
	int			m_iSpeed;
	int			m_iType;

public:
	void Update();
	void Render();
	void CreateiType();
	class CShape* CreateRandomShape();
};

