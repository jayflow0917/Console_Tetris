#include "Core.h"

int main()
{
	// Core 초기화
	if (!CCore::GetInst()->Init())
	{
		// 초기화하지 못할 경우 // 메모리 해제
		CCore::DestroyInst();
		return 0;
	}

	// Core 초기화 성공하면 Run.
	CCore::GetInst()->Run();

	CCore::DestroyInst();

	return 0;
}

/*
수정사항
- Hard Drop 기능(Space Bar) (o)
- Soft Drop 기능(↓) (o)
- 화면 깜빡임 현상 제거(cls 제거) (o)
- cmd상의 커서 제거 (o)
- 도형이 양 옆 벽에 붙어서 회전할 수 없을 경우 도형 회전 금지 (o)
- 기존에 쌓인 도형들 사이에서 현재 도형 회전 금지 (o)
- 도형마다 고유의 색 부여 (o)
- stage UI 변경 (o)
- p누르면 화면 지우기 + 일시정지 ★
- 점수 추가
- 가이드선 추가

(★은 현재 진행중인 사항을 의미)
*/