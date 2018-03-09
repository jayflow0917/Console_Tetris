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