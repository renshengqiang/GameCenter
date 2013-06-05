#include "AlphaBeta.h"
#include <string.h>

//目前没有用到type，只能用来找黑子
void AlphaBetaEngine::SearchAGoodMove(BYTE position [ ] [ GRID_NUM ],int /*type*/, int & x,int & y)
{
	memcpy(CurPosition, position, GRID_COUNT);
	AlphaBeta(m_nSearchDepth, -20000, 20000);

	x = m_cmBestMove.StonePos.x;
	y = m_cmBestMove.StonePos.y;
}
int AlphaBetaEngine::AlphaBeta(int depth, int alpha, int beta)
{
	int side = (m_nSearchDepth - depth)%2;
	int childNodeCount, score;
	
	if(depth <= 0)
	{
		return m_pEval->Evaluate(CurPosition, side);
	}
	childNodeCount = m_pMG->CreatePossibleMove(CurPosition, depth , side);
	
	for(int i=0; i<childNodeCount; ++i)
	{
		MakeMove(&m_pMG->m_MoveList[depth][i], side);
		score = -AlphaBeta(depth  -1, -beta, -alpha);
		UnMakeMove(&m_pMG->m_MoveList[depth][i]);
		if(score >alpha)
		{
		
			alpha = score;
			if(depth == m_nSearchDepth)
			{
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			}
			if(alpha > beta)
				break;//cutoff
		}
	}
	return alpha;
}
