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

/*
��������
- Hard Drop ���(Space Bar) (o)
- Soft Drop ���(��) (o)
- ȭ�� ������ ���� ����(cls ����) (o)
- cmd���� Ŀ�� ���� (o)
- ������ �� �� ���� �پ ȸ���� �� ���� ��� ���� ȸ�� ���� (o)
- ������ ���� ������ ���̿��� ���� ���� ȸ�� ���� (o)
- �������� ������ �� �ο� (o)
- stage UI ���� (o)
- p������ ȭ�� ����� + �Ͻ����� ��
- ���� �߰�
- ���̵弱 �߰�

(���� ���� �������� ������ �ǹ�)
*/