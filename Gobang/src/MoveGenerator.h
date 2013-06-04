#ifndef MOVE_GENERATOR
#define MOVE_GENERATOR
#include "Define.h"

class CMoveGenerator  
{
public:
	CMoveGenerator();
	virtual ~CMoveGenerator();
	int CreatePossibleMove(BYTE position[GRID_NUM][GRID_NUM], int nPly,int nSide);

	STONEMOVE m_MoveList[10][225];
protected:
	int AddMove(int nFromX,int nToX,int nPly);
	int m_nMoveCount;
};

#endif
