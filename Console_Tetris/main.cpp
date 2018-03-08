#include "Core.h"

int main()
{
	// Core 초기화
	if (!CCore::GetInst()->Init())
	{
		CCore::DestroyInst();
		return 0;
	}

	// Core 초기화 성공하면 Run.
	CCore::GetInst()->Run();

	CCore::DestroyInst();

	return 0;
}