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

	// ShapeManager의 Speed
	++m_iSpeed;

	// 방향키(상,하,좌,우) + SpaceBar
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

	// 수동으로 아래 버튼을 눌러 도형이 내려올 수 있도록 하는 기능
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_pCurShape->MoveDown();
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		while (!m_pCurShape->MoveDown());
	}

	// 도형의 다음 진행을 위한 부분.
	// Stage의 speed와 ShapeManager의 speed가 같다면
	if (pStage->GetSpeed() == m_iSpeed)
	{
		// MoveDown()으로 한 줄 아래로 내려갈 수 있는지 체크. true일 경우
		// 내려갈 수 없다는 것이므로 stage에 추가하고, 다음도형을 현재도형
		// 으로 만들어준다. 그 후 다음 도형을 생성한다.
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
	// 어떤 도형을 출력할지 랜덤으로 선택하여 도형 번호를 m_iType에
	// 셋팅한다.
	CShapeManager::CreateiType();
	CShape* pShape = new CShape;

	// 만약 초기화에 실패했다면
	if (!pShape->Init((SHAPE_TYPE)m_iType))
	{
		SAFE_DELETE(pShape);
		return NULL;
	}
	return pShape;
}
