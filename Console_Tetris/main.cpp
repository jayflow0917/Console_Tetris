#include "Core.h"

int main()
{
	// Core �ʱ�ȭ
	if (!CCore::GetInst()->Init())
	{
		// �ʱ�ȭ���� ���� ��� // �޸� ����
		CCore::DestroyInst();
		return 0;
	}

	// Core �ʱ�ȭ �����ϸ� Run.
	CCore::GetInst()->Run();

	CCore::DestroyInst();

	return 0;
}