#ifndef NEGA_SCOUT_H
#define NEGA_SCOUT_H
#include "SearchEngine.h"
#include "TranspositionTable.h"
#include "HistoryHeuristic.h"

class CNegaScout : 
	public CTranspositionTable,
	public CHistoryHeuristic,
	public CSearchEngine
{
public:
	CNegaScout();
	virtual ~CNegaScout();

	virtual void SearchAGoodMove(BYTE position[GRID_NUM][GRID_NUM],int Type, int &x, int &y);

protected:
	int NegaScout(int depth, int alpha, int beta);
};

#endif
