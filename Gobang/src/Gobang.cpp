#include "Gobang.h"
#include <iostream>
using namespace std;

GobangWindow::GobangWindow(int x, int y):
    mWidth(720),mHeight(580)
{
    QWidget::setGeometry(x,y,mWidth,mHeight);
    mMarginWidth = 20;
    mStartPosX = mMarginWidth;
    mStartPosY = mMarginWidth;
    mContentWidth = mHeight - 2*mMarginWidth;
    mChessmanWidth = mContentWidth/(LINE_NUM-1);
    mBackgroundImage = QImage("./res/wood_floor.jpg");
    mWhiteImage = QImage("./res/white.png");
    mBlackImage = QImage("./res/black.png");
    for(int i = 0; i < LINE_NUM; ++i)
        for(int j = 0; j < LINE_NUM; ++j)
            mValue[i][j]=0;
    mCurrentX = 7; mCurrentY = 7;
    mValue[0][0] = 2;
    mValue[5][3] = 1;
    mValue[15][15] = 1;
}
void GobangWindow::mousePressEvent(QMouseEvent *event)
{
    if(_IsInChequer(event->x(), event->y()))
    {
        int x, y;
        _GetChessmanPos(event->x(), event->y(), &x, &y);
        if(mValue[x][y]==0)
        {
            mCurrentX = x;
            mCurrentY = y;
        }
    }
    QWidget::mousePressEvent(event);
}
void GobangWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(_IsInChequer(event->x(), event->y()))
    {
        int x, y;
        _GetChessmanPos(event->x(), event->y(), &x, &y);
        mValue[x][y]=1;
    }
    QWidget::mouseDoubleClickEvent(event);
    repaint();
}
void GobangWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen    pen;
    int x, y;
  
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawImage(QRect(mStartPosX, mStartPosY, mContentWidth, mContentWidth), mBackgroundImage);
    painter.drawRect(mStartPosX, mStartPosY, mContentWidth, mContentWidth);
    x = mStartPosX;
    y = mStartPosY;
    for(int i=1; i < LINE_NUM -1; ++i)
    {
        y += mChessmanWidth;
        painter.drawLine(x, y, x + mContentWidth, y);
    }
    x = mStartPosX;
    y = mStartPosY;
    for(int i=1; i< LINE_NUM -1; ++i)
    {
        x += mChessmanWidth;
        painter.drawLine(x, y, x, y + mContentWidth);
    }
    for(int i=0; i<LINE_NUM; ++i)
    {
        for(int j=0; j<LINE_NUM; ++j)
        {
            if(mValue[i][j] == 1)
            {
                painter.drawImage(QRect(mStartPosX + (i-0.5)*mChessmanWidth,
                                        mStartPosY + (j-0.5)*mChessmanWidth,
                                        mChessmanWidth, mChessmanWidth), mBlackImage);
            }
            else if(mValue[i][j] == 2)
            {
                painter.drawImage(QRect(mStartPosX + (i-0.5)*mChessmanWidth,
                                        mStartPosY + (j-0.5)*mChessmanWidth,
                                        mChessmanWidth, mChessmanWidth), mWhiteImage);
            }
        }
    }
    painter.setPen(QColor(0, 255, 255));
    painter.drawRect(mStartPosX + (mCurrentX - 0.5)*mChessmanWidth, 
                     mStartPosY + (mCurrentY - 0.5)*mChessmanWidth,
                     mChessmanWidth, mChessmanWidth);
    QWidget::paintEvent(event);
}
bool GobangWindow::_IsInChequer(int x, int y)
{
    if(x > mStartPosX && x < mStartPosX + mContentWidth &&
        y > mStartPosY && y < mStartPosY + mContentWidth)
        return true;
    return false;
}
void GobangWindow::_GetChessmanPos(int xpos, int ypos, int *x, int *y)
{
    *x = (xpos - mStartPosX)/mChessmanWidth;
    *y = (ypos - mStartPosY)/mChessmanWidth;
    if( (xpos - mStartPosX)%mChessmanWidth >= mChessmanWidth/2)
        ++*x;
    if( (ypos - mStartPosY)%mChessmanWidth >= mChessmanWidth/2)
        ++*y;
}
