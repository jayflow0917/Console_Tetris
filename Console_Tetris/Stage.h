#pragma once

#include "value.h"

class CStage
{
private:
	CStage();
	~CStage();

private:
	friend class CStageManager;

private:
	char	m_Stage[STAGE_HEIGHT][STAGE_WIDTH];
	int		m_iSpeed;

public:
	int GetSpeed()	const
	{
		return m_iSpeed;
	}

public:
	bool CheckBlock(int x, int y);
	
public:
	void AddBlock(class CShape* pShape, const POSITION& tPos);

public:
	bool Init();
	void Render();
};

