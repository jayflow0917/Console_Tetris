#pragma once

// �޸� ���� ��ũ��
#define SAFE_DELETE(p)	if(p)	{delete p; p = NULL; }