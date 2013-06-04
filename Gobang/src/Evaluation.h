#ifndef EVALUATION_H
#define EVALUATION_H

#include "Define.h"

#define  STWO      1   //眠二
#define  STHREE    2   //眠三
#define  SFOUR     3   //冲四
#define  TWO       4   //活二
#define  THREE     5   //活三
#define  FOUR      6   //活四
#define  FIVE      7   //五连
#define  DFOUR     8   //双四
#define  FOURT     9   //四三
#define  DTHREE   10   //三三
#define  NOTYPE   11   //未定义
#define  ANALSISED 255  //已分析过的
#define  TOBEANALSIS 0  //已分析过的

extern int PosValue[GRID_NUM][GRID_NUM];

class CEvaluation
{
public:
	CEvaluation();
	virtual ~CEvaluation();
	
	virtual int Evaluate(BYTE position[][GRID_NUM], bool bIsRedTurn);

protected:

	int AnalysisHorizon(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisVertical(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisLeft(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisRight(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisLine(BYTE *position, int GridNum, int StonePos);
	BYTE m_LineRecord[30];
	int TypeRecord[GRID_NUM][GRID_NUM][4];//这个数据结构用来记录四个方向上的棋局
	int TypeCount[2][20];//这个数据结构用来记录各种不用的棋局类型
};

#endif
