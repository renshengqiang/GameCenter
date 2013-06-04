#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "MoveGenerator.h"
#include "Evaluation.h"
class CSearchEngine  
{
public:
	CSearchEngine();
	virtual ~CSearchEngine();
	
	virtual void SearchAGoodMove(BYTE position[][GRID_NUM], int Type, int &x, int &y)=0;
	
	virtual void SetSearchDepth(int nDepth){m_nSearchDepth = nDepth;};
	
	virtual void SetEveluator(CEvaluation *pEval){m_pEval = pEval;};

	virtual void SetMoveGenerator(CMoveGenerator *pMG){m_pMG = pMG;};

	BOOL GameOver(){return m_bGameOver;};
	void BeginGame(){m_bGameOver = FALSE;};
protected:
	virtual BYTE MakeMove(STONEMOVE* move,int type);
	virtual void UnMakeMove(STONEMOVE* move);
	virtual int IsGameOver(BYTE position[GRID_NUM][GRID_NUM], int nDepth);
	BYTE CurPosition[GRID_NUM][GRID_NUM];
	STONEMOVE m_cmBestMove;
	CMoveGenerator *m_pMG;
	CEvaluation *m_pEval;
	int m_nSearchDepth;
	int m_nMaxDepth;
	BOOL m_bGameOver;
};

#endif
