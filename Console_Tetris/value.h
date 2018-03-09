// 프로젝트에 필요한 각종 상수값 및 라이브러리들을 모아놓은 파일
// 다같이 공유할 헤더파일

#pragma once

#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

#include "Macro.h"
#include "Flags.h"


#define STAGE_WIDTH		10
#define STAGE_HEIGHT	25

typedef struct _tagPosition
{
	int		x;
	int		y;

	_tagPosition() :
		x(0),
		y(0)
	{
	}
}POSITION, *PPOSITION;