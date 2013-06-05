#include "NegaMax.h"
#include <string.h>

#define INFINITY (20000)
#define NOMORE_MOVE (-30000)
void NegaMaxEngine::SearchAGoodMove(BYTE position[][GRID_NUM], int Type, int &x, int &y)
{
	memcpy(CurPosition, position, GRID_COUNT);
	NegaMax(m_nSearchDepth);
	x = m_cmBestMove.StonePos.y;
	y = m_cmBestMove.StonePos.x;
	return;
}
/*
因为没有传入side参数，因此只适合计算黑子的策略
*/
int NegaMaxEngine::NegaMax(int depth)
{
	int bestScore = -INFINITY;
	int side = (m_nSearchDepth - depth)%2;
	int childNodeCount, type, score;

	if(depth <= 0)
	{
		return m_pEval->Evaluate(CurPosition, side);
	}
	childNodeCount = m_pMG->CreatePossibleMove(CurPosition, depth , side);
	if(childNodeCount <= 0) return NOMORE_MOVE;
	for(int i=0; i<childNodeCount; ++i)
	{
		MakeMove(&m_pMG->m_MoveList[depth][i], side);
		score = -NegaMax(depth  -1);
		UnMakeMove(&m_pMG->m_MoveList[depth][i]);
		if(score > bestScore)
		{
			bestScore = score;
			if(depth == m_nSearchDepth)
			{
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			}
		}
	}
	return bestScore;
}
