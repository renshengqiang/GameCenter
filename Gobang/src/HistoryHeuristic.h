#ifndef HISTORY_HEURISTIC_H
#define HISTORY_HEURISTIC_H
#include "Define.h"

class CHistoryHeuristic  
{
public:
	CHistoryHeuristic();
	virtual ~CHistoryHeuristic();
	
	void ResetHistoryTable();
	int GetHistoryScore(STONEMOVE *move);
	void EnterHistoryScore(STONEMOVE *move,int depth);
	static void MergeSort(STONEMOVE *source, int n, BOOL direction);
protected:
	static void Merge(STONEMOVE *source, STONEMOVE *target, int l,int m, int r);
	static void MergePass(STONEMOVE *source, STONEMOVE *target, const  int s, const  int n, const BOOL direction);
	static void Merge_A(STONEMOVE *source, STONEMOVE *target, int l,int m, int r);
	static STONEMOVE m_TargetBuff[225]; 
	int m_HistoryTable[GRID_NUM][GRID_NUM];

};

#endif
