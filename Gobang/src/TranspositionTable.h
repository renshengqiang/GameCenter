#ifndef _TRANSPOSITION_TABLE_H
#define _TRANSPOSITION_TABLE_H
#include "Define.h"

enum ENTRY_TYPE{ exact , lower_bound, upper_bound}; 

typedef struct HASHITEM{
     long long checksum;	// or long long might be even better
	ENTRY_TYPE  entry_type;
    short depth;
    short eval;
}HashItem;

class CTranspositionTable  
{
public:
	CTranspositionTable();
	virtual ~CTranspositionTable();

	void CalculateInitHashKey(BYTE CurPosition[GRID_NUM][GRID_NUM]);
	void Hash_MakeMove(STONEMOVE* move,BYTE CurPosition[GRID_NUM][GRID_NUM]);
	void Hash_UnMakeMove(STONEMOVE* move,BYTE CurPosition[GRID_NUM][GRID_NUM]);

	int LookUpHashTable(int alpha, int beta, int depth,int TableNo);
	void EnterHashTable(ENTRY_TYPE entry_type, short eval, short depth,int TableNo);

	UINT m_nHashKey32[2][GRID_NUM][GRID_NUM];
	unsigned long long m_ulHashKey64[2][GRID_NUM][GRID_NUM];
	HashItem *m_pTT[2];
	void InitializeHashKey();
	UINT m_HashKey32;
	long long m_HashKey64;
};

#endif
