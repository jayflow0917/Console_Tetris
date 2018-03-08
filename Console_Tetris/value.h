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