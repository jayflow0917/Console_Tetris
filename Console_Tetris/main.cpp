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
- space 기능 (o)
- 아래버튼 기능 (o)
- 화면 반짝이는 거 없애기(cls 없애기)  (o)
- 커서 없애기 (o)
- 오른쪽 벽에 붙어서 회전할 수 없을 경우 도형 회전 금지(o)
- 쌓인 도형들 내에서 현재 도형 회전 금지(도형이 쌓인 stage를 좌표로 관리해야 할듯. 좌표 전환 필요) (o)
- 블록 색깔(쌓인 블록마다 색을 달리 표현하기 위해서라도 stage를 좌표로 관리해야 함.) (o)
- stage UI 꾸미기 (o)
- p누르면 화면 지우기 + 일시정지 ★
- 점수 추가
- 가이드선 추가
*/