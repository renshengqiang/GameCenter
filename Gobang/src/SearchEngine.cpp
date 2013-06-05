#include "SearchEngine.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSearchEngine::CSearchEngine()
{
}

CSearchEngine::~CSearchEngine()
{
	delete m_pMG;
	delete m_pEval;
}

BYTE CSearchEngine::MakeMove(STONEMOVE* move, int type)
{
	CurPosition[move->StonePos.x][move->StonePos.y] = type;
	return 0;
}

void CSearchEngine::UnMakeMove(STONEMOVE* move)
{
	CurPosition[move->StonePos.x][move->StonePos.y] = NOSTONE;
}


int CSearchEngine::IsGameOver(BYTE position[][GRID_NUM], int nDepth)
{
	int score, i;
	i = (m_nMaxDepth - nDepth ) % 2;
	score = m_pEval->Evaluate(position, i);
	
	if (abs(score) > 8000)
		return score; 
	return 0;
}
