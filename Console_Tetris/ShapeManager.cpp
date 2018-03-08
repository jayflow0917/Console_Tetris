#include "ShapeManager.h"
#include "StageManager.h"
#include "Stage.h"
#include "Shape.h"

CShapeManager*	CShapeManager::m_pInst = NULL;

CShapeManager::CShapeManager()	:
	m_pCurShape(NULL),
	m_pNextShape(NULL)
{
	m_pCurShape = CreateRandomShape();
	m_pNextShape = CreateRandomShape();
	m_iSpeed = 0;
}


CShapeManager::~CShapeManager()
{
	SAFE_DELETE(m_pCurShape);
	SAFE_DELETE(m_pNextShape);
}

void CShapeManager::Update()
{
	CStage*	pStage = CStageManager::GetInst()->GetCurrentStage();

	// ShapeManager�� Speed
	++m_iSpeed;

	// ����Ű(��,��,��,��) + SpaceBar
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_pCurShape->MoveLeft();
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_pCurShape->MoveRight();
	}

	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{

	}

	// �������� �Ʒ� ��ư�� ���� ������ ������ �� �ֵ��� �ϴ� ���
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pCurShape->MoveDown();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		while (!m_pCurShape->MoveDown());
	}

	// ������ ���� ������ ���� �κ�.
	// Stage�� speed�� ShapeManager�� speed�� ���ٸ�
	if (pStage->GetSpeed() == m_iSpeed)
	{
		// MoveDown()���� �� �� �Ʒ��� ������ �� �ִ��� üũ. true�� ���
		// ������ �� ���ٴ� ���̹Ƿ� stage�� �߰��ϰ�, ���������� ���絵��
		// ���� ������ش�. �� �� ���� ������ �����Ѵ�.
		if (m_pCurShape->MoveDown())
		{
			
			m_pCurShape = m_pNextShape;
			m_pCurShape -> SetPosition(4, 0);

			m_pNextShape = CreateRandomShape();
		}
		m_iSpeed = 0;
	}
}

void CShapeManager::Render()
{
	m_pCurShape->Render();

	m_pNextShape->SetPosition(13, 4);
	m_pNextShape->RenderNext();
}

void CShapeManager::CreateiType()
{
	m_iType = rand() % ST_END;
}

CShape * CShapeManager::CreateRandomShape()
{
	// � ������ ������� �������� �����Ͽ� ���� ��ȣ�� m_iType��
	// �����Ѵ�.
	CShapeManager::CreateiType();
	CShape* pShape = new CShape;

	// ���� �ʱ�ȭ�� �����ߴٸ�
	if (!pShape->Init((SHAPE_TYPE)m_iType))
	{
		SAFE_DELETE(pShape);
		return NULL;
	}
	return pShape;
}
