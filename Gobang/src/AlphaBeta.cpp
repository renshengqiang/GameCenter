#include "AlphaBeta.h"
#include <string.h>
#include <stdlib.h>
#ifdef _DEBUG_NUM
#include <stdio.h>
#endif

STONEMOVE AlphaBetaEngine::m_TargetBuff[225];

//目前没有用到type，只能用来找黑子
void AlphaBetaEngine::SearchAGoodMove(BYTE position [ ] [ GRID_NUM ],int /*type*/, int & x,int & y)
{
#ifdef _DEBUG_NUM
	branchNum = cutoffNum = 0;
#endif
	memcpy(CurPosition, position, GRID_COUNT);
	AlphaBeta(m_nSearchDepth, -20000, 20000);
#ifdef _DEBUG_NUM
	printf("branchNum %d cutoffNum %d\n", branchNum, cutoffNum);
#endif
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
#ifdef _DEBUG_NUM
	branchNum += childNodeCount;
#endif
	for (int i=0; i<childNodeCount; i++) 
	{
		m_pMG->m_MoveList[depth][i].Score = 
			7 -abs(m_pMG->m_MoveList[depth][i].StonePos.x-m_pMG->m_MoveList[depth][i].StonePos.y);
	}
	MergeSort(m_pMG->m_MoveList[depth], childNodeCount);
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
			{
#ifdef _DEBUG_NUM
				cutoffNum += (childNodeCount -i);
#endif
				break;//cutoff
			}
		}
	}
	return alpha;
}
void AlphaBetaEngine::MergeSort(STONEMOVE *source, int n)
{//降序排序
	int s = 1;
	while(s < n)
	{
		MergePass(source, m_TargetBuff, s, n);
		s += s;
		MergePass(m_TargetBuff, source, s, n);
		s += s;
	}
}
void AlphaBetaEngine::MergePass(STONEMOVE *source, STONEMOVE *target, const  int s, const  int n)
{
	int i = 0;
	
	while(i <= n - 2 * s)
	{
		//合并大小为s的相邻二段子数组
		Merge(source, target, i, i + s - 1, i + 2 * s - 1);
		i=i+2*s;
	}
	
	if (i + s < n) //剩余的元素个数小於2s
	{
		Merge(source, target, i, i + s - 1, n - 1);
	}
	else
		for (int j = i; j <= n - 1; j++)
			target[j] = source[j];
}
void AlphaBetaEngine::Merge(STONEMOVE *source, STONEMOVE *target, int l,int m, int r)
{//从大到小排序
	int i = l;
	int j = m + 1;
	int k = l;
	
	while((i <= m) && (j <= r))
		if (source[i].Score >= source[j].Score)
			target[k++] = source[i++];
		else
			target[k++] = source[j++];
		
	if(i > m)
		for (int q = j; q <= r; q++)
			target[k++] = source[q];
	else
		for(int q = i; q <= m; q++)
			target[k++] = source[q];
}

