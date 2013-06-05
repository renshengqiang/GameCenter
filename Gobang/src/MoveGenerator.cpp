#include "MoveGenerator.h"
#include "HistoryHeuristic.h"
#include "Evaluation.h"

CMoveGenerator::CMoveGenerator()
{	
}
CMoveGenerator::~CMoveGenerator()
{	
}
int CMoveGenerator::AddMove(int nToX, int nToY,int nPly)
{
	m_MoveList[nPly][m_nMoveCount].StonePos.x = nToX;
	m_MoveList[nPly][m_nMoveCount].StonePos.y = nToY;
	m_nMoveCount++;
	m_MoveList[nPly][m_nMoveCount].Score = PosValue[nToY][nToX];
	return m_nMoveCount;
}

int CMoveGenerator::CreatePossibleMove(BYTE position[GRID_NUM][GRID_NUM], int nPly, int nSide)
{
	int i,j;
	m_nMoveCount = 0;
	for (i = 0; i < GRID_NUM; i++)
		for (j = 0; j < GRID_NUM; j++)
		{
			if (position[i][j] == (BYTE)NOSTONE)
			{
				AddMove(j, i, nPly);
			}
		}

	CHistoryHeuristic::MergeSort(m_MoveList[nPly], m_nMoveCount, nSide);
	return m_nMoveCount;
}
