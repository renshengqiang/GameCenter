#ifndef _ALPHA_BETA_H
#define _ALPHA_BETA_H

#include "SearchEngine.h"

class AlphaBetaEngine: public CSearchEngine{
public:
	virtual void SearchAGoodMove(BYTE position[][GRID_NUM], int Type, int &x, int &y);
	int AlphaBeta(int depth, int alpha, int beta);
};

#endif
