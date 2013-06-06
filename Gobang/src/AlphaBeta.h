#ifndef _ALPHA_BETA_H
#define _ALPHA_BETA_H

#include "SearchEngine.h"

class AlphaBetaEngine: public CSearchEngine{
public:
	virtual void SearchAGoodMove(BYTE position[][GRID_NUM], int Type, int &x, int &y);
	int AlphaBeta(int depth, int alpha, int beta);
protected:
	void MergeSort(STONEMOVE *source, int n);
	void MergePass(STONEMOVE *source, STONEMOVE *target, const  int s, const  int n);
	void Merge(STONEMOVE *source, STONEMOVE *target, int l,int m, int r);
private:
	static STONEMOVE m_TargetBuff[225]; /*ÅÅÐòÓÃµÄ¸¨Öú»º´æ*/
	int branchNum, cutoffNum;
};

#endif
