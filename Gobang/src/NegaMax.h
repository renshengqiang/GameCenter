#ifndef _NEGA_MAX_EIGINE
#define _NEGA_MAX_ENGINE

#include "SearchEngine.h"

class NegaMaxEngine: public CSearchEngine{
public:
	virtual void SearchAGoodMove(BYTE position[][GRID_NUM], int Type, int &x, int &y);
	int NegaMax(int depth);
};

#endif
