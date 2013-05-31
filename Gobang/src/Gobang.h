#ifndef _GOBANG_H
#define _GOBANG_H

#include <QtGui>
#define LINE_NUM 16
class GobangWindow : public QWidget{
    public:
        GobangWindow(int x, int y);
    protected:
        virtual void paintEvent(QPaintEvent *event);
        virtual void mousePressEvent(QMouseEvent *event);
        virtual void mouseDoubleClickEvent(QMouseEvent *event);
    private:
        bool _IsInChequer(int x, int y);
        void _GetChessmanPos(int xpos, int ypos, int *x, int *y);
    private:
        int mWidth,mHeight;
        int mStartPosX, mStartPosY, mMarginWidth, mContentWidth, mChessmanWidth;
        int mCurrentX, mCurrentY;
        QImage mBackgroundImage, mWhiteImage, mBlackImage;
        int mValue[LINE_NUM][LINE_NUM];
};

#endif
