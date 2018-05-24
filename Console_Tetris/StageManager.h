// stage ���踦 ���� stage�������̴�.

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
	 Ŭ���� ���漱���̶�?
	 ������Ͽ��� ��������� ���Խ�Ű�� ������ ������ �ð��� 
	 ������Ű�� ������ �̸� ���� ���� ������ ��ü�� ������ ������ 
	 Ŭ���� ���� ���� �ʿ��� Ŭ������ ����Ͽ� ��������� �ߺ��� 
	 ���� �� �ִ�.
	 �� ��������� �������� �ʾ�, Ŭ������ ���� ������ ���� ������ 
	 ������ ��ü�� ��� �����ϴ�.

	 StageManager���� Stage�� �����ϱ� ���ؼ��� stage������ �ʿ��ѵ�
	 include�� �Ǿ����� ������ class�� �տ��Ἥ ���漱���� ���ش�.
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

