#pragma once

// 메모리 해제 매크로
#define SAFE_DELETE(p)	if(p)	{delete p; p = NULL; }