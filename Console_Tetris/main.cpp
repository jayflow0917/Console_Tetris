#include "Core.h"

int main()
{
	// Core �ʱ�ȭ
	if (!CCore::GetInst()->Init())
	{
		CCore::DestroyInst();
		return 0;
	}

	// Core �ʱ�ȭ �����ϸ� Run.
	CCore::GetInst()->Run();

	CCore::DestroyInst();

	return 0;
}