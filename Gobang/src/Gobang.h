#ifndef _GOBANG_H
#define _GOBANG_H

#include <QtGui>
#define LINE_NUM 15
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
		bool mStarted;
        int mWidth,mHeight;
        int mStartPosX, mStartPosY, mMarginWidth, mContentWidth, mChessmanWidth;
        int mCurrentX, mCurrentY;
        QImage mBackgroundImage, mWhiteImage, mBlackImage;
        int mValue[LINE_NUM][LINE_NUM], mWorthToComputer[LINE_NUM][LINE_NUM][4],mWorthToPlayer[LINE_NUM][LINE_NUM][4],mWorth[LINE_NUM][LINE_NUM];
		QPushButton	*mpButton;
};

#endif
