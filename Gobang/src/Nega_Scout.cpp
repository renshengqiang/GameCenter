#include "Nega_Scout.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNegaScout::CNegaScout()
{
	ResetHistoryTable();
	m_bGameOver = FALSE;
}
CNegaScout::~CNegaScout()
{
	
}
void CNegaScout::SearchAGoodMove(BYTE position[GRID_NUM][GRID_NUM], int Type, int &x, int &y)
{
	memcpy(CurPosition, position, GRID_COUNT);
	m_nMaxDepth = m_nSearchDepth;
	CalculateInitHashKey(CurPosition);
	ResetHistoryTable();
	NegaScout(m_nMaxDepth, -20000, 20000);

	x = m_cmBestMove.StonePos.x;
	y = m_cmBestMove.StonePos.y;
}
int CNegaScout::NegaScout(int depth, int alpha, int beta)
{
	int Count,i;
	BYTE type;
	int a,b,t;
	int side;
	int score;

	side = (m_nMaxDepth-depth)%2;
	
	score = LookUpHashTable(alpha, beta, depth, side); 
	if (score != 66666)
		return score;

	if (depth <= 0)
	{
		score = m_pEval->Evaluate(CurPosition, side );
		EnterHashTable(exact, score, depth, side );
		return score;
	}
	
	Count = m_pMG->CreatePossibleMove(CurPosition, depth, side);
	
	for (i=0;i<Count;i++) 
	{
		m_pMG->m_MoveList[depth][i].Score = 
			GetHistoryScore(&m_pMG->m_MoveList[depth][i]);
	}
	MergeSort(m_pMG->m_MoveList[depth], Count, 0);
	
	int bestmove=-1;

	a = alpha;
	b = beta;
	int eval_is_exact = 0;
	for ( i = 0; i < Count; i++) 
	{
		type = MakeMove(&m_pMG->m_MoveList[depth][i], side);
		Hash_MakeMove(&m_pMG->m_MoveList[depth][i], CurPosition);
		
		t = -NegaScout(depth-1 , -b, -a );
		
		if (t > a && t < beta && i > 0) 
		{
			a = -NegaScout (depth-1, -beta, -t );     /* re-search */
			eval_is_exact = 1;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
			bestmove = i;
		}
		Hash_UnMakeMove(&m_pMG->m_MoveList[depth][i], CurPosition); 
		UnMakeMove(&m_pMG->m_MoveList[depth][i]); 
		if (a < t)
		{
			eval_is_exact = 1;
			a=t;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->m_MoveList[depth][i];
		}
		if ( a >= beta ) 
		{
			EnterHashTable(lower_bound, a, depth,side);
			EnterHistoryScore(&m_pMG->m_MoveList[depth][i], depth);
			return a;
		}
		b = a + 1;                      /* set new null window */
	}
	if (bestmove != -1)
	EnterHistoryScore(&m_pMG->m_MoveList[depth][bestmove], depth);
	if (eval_is_exact) 
		EnterHashTable(exact, a, depth,side);
	else 
		EnterHashTable(upper_bound, a, depth,side);
	return a;
}
