#ifndef EVALUATION_H
#define EVALUATION_H

#include "Define.h"

#define  STWO      1   //�߶�
#define  STHREE    2   //����
#define  SFOUR     3   //����
#define  TWO       4   //���
#define  THREE     5   //����
#define  FOUR      6   //����
#define  FIVE      7   //����
#define  DFOUR     8   //˫��
#define  FOURT     9   //����
#define  DTHREE   10   //����
#define  NOTYPE   11   //δ����
#define  ANALSISED 255  //�ѷ�������
#define  TOBEANALSIS 0  //�ѷ�������

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
	int TypeRecord[GRID_NUM][GRID_NUM][4];//������ݽṹ������¼�ĸ������ϵ����
	int TypeCount[2][20];//������ݽṹ������¼���ֲ��õ��������
};

#endif
