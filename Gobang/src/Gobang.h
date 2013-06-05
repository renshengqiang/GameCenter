#ifndef _GOBANG_H
#define _GOBANG_H

#include "Define.h"
#include "Nega_Scout.h"
#include "NegaMax.h"
#include "AlphaBeta.h"
#include <QtGui>


class GobangWindow : public QWidget{
	Q_OBJECT
    public:
        GobangWindow(int x, int y);

    protected:
        virtual void paintEvent(QPaintEvent *event);
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseDoubleClickEvent(QMouseEvent *event);

    private:
        bool _IsInChequer(int x, int y);
        void _GetChessmanPos(int xpos, int ypos, int *x, int *y);

		void _EstimateTranverse(int layer,int colum,int who);
		void _EstimateErect(int layer,int colum,int who);
		void _Estimate45(int layer, int colum, int who);
		void _Estimate_45(int layer, int colum, int who);
		bool _IsGameEnded(int layer, int colum, int who);
		void _GetBestPos(int *layer, int *colum);

	private slots:
		void OnClickBegin(void);

    private:
		bool mStarted, mDoubleClicked;
        int mWidth,mHeight;
        int mStartPosX, mStartPosY, mMarginWidth, mContentWidth, mChessmanWidth;
        int mCurrentX, mCurrentY;
        QImage mBackgroundImage, mWhiteImage, mBlackImage;
        BYTE mValue[GRID_NUM][GRID_NUM];
	int mWorthToComputer[GRID_NUM][GRID_NUM][4],mWorthToPlayer[GRID_NUM][GRID_NUM][4],mWorth[GRID_NUM][GRID_NUM];
	QPushButton	*mpButton;
	CSearchEngine* m_pSE;
};

#endif
