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
	// ���� ���� ǥ��
	class CShape*	m_pCurShape;
	// ���� ���� ǥ��
	class CShape*	m_pNextShape;

	// ������ ������ ƽ�� ���Ѵ�.
	int			m_iSpeed;
	int			m_iType;

public:
	void Update();
	void Render();
	void CreateiType();
	class CShape* CreateRandomShape();
};

