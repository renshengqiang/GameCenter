#include "Gobang.h"
#include <iostream>
using namespace std;

GobangWindow::GobangWindow(int x, int y):
	mStarted(false),
    mWidth(726),mHeight(544)
{
    QWidget::setGeometry(x,y,mWidth,mHeight);
	QWidget::setFixedSize(mWidth, mHeight);
	mpButton = new QPushButton("Begin", this);
	mpButton->setGeometry(mHeight, 20, mWidth-mHeight-20, mHeight-40);
	connect(mpButton, SIGNAL(clicked(bool)), this, SLOT(OnClickBegin()));
    mBackgroundImage = QImage("./res/wood_floor.jpg");
    mWhiteImage = QImage("./res/white.png"); /*mWorthToComputer*/
    mBlackImage = QImage("./res/black.png"); /*mWorthToPlayer*/
    
    for(int i = 0; i < LINE_NUM; ++i)
        for(int j = 0; j < LINE_NUM; ++j)
            mValue[i][j]=0;/*mWorthToComputer 1, mWorthToPlayer 2*/
    mCurrentX = LINE_NUM/2; mCurrentY = LINE_NUM/2;

	mMarginWidth = 20;
    mStartPosX = mMarginWidth;
    mStartPosY = mMarginWidth;
    mContentWidth = mHeight - 2*mMarginWidth;
    mChessmanWidth = mContentWidth/(LINE_NUM-1);
}
void GobangWindow::OnClickBegin(void)
{
    for(int i = 0; i < LINE_NUM; ++i)
        for(int j = 0; j < LINE_NUM; ++j)
            mValue[i][j]=0;/*mWorthToComputer 1, mWorthToPlayer 2*/
	mStarted = true;
	mpButton->setText("Rebegin");
	repaint();
}
void GobangWindow::mousePressEvent(QMouseEvent *event)
{
    if(_IsInChequer(event->x(), event->y()))
    {
        int x, y;
        _GetChessmanPos(event->x(), event->y(), &x, &y);
        mCurrentX = x;
        mCurrentY = y;
    }
    QWidget::mousePressEvent(event);
    repaint();
}
void GobangWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(mStarted && _IsInChequer(event->x(), event->y()))
    {
        int x, y;
        _GetChessmanPos(event->x(), event->y(), &x, &y);
		if(mValue[x][y] == 0)
		{
			mValue[x][y] = 2;
			if(_IsGameEnded(x, y, 2))
			{
				QMessageBox::about(NULL, "Game End", "Congratulations, you won the game ^_^");
				mStarted = false;
			}
			else
			{
				int bestX, bestY;
				_GetBestPos(&bestX, &bestY);
				mValue[bestX][bestY] = 1;
				mCurrentX = bestX;
				mCurrentY = bestY;
				if(_IsGameEnded(bestX, bestY, 1))
				{
					repaint();
					QMessageBox::about(NULL, "Game End", "Sorry, you losed -_-");
					mStarted = false;
				}
			}
			
		}
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
///////////////////////////////////////////////////////////////////////////////
void GobangWindow::_EstimateTranverse(int layer,int colum,int who)
{//横向估计
	int i,count = 0,Nblank = 1;
	
	i=colum - 1;
	while(i>=0)
	{
		if(mValue[layer][i] == 0 ) Nblank++;
		if(mValue[layer][i] != who) break;
		else count++;
		i--;
	}
	i = colum + 1;
	while(i<15)
	{
		if(mValue[layer][i] == 0 ) Nblank++;
		if(mValue[layer][i] != who) break;
		else count++;
		i++;
	}
	
	if(count == 4)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][0] = 200;
		else
			mWorthToPlayer[layer][colum][0] = 180;
	}
	
	else if(count == 3)
	{
		if(who == 1)
		{
			if(Nblank > 2)
				mWorthToComputer[layer][colum][0] = 100;
			else if(Nblank == 2)
			{
				if(mValue[layer - 1][colum] == 0 || mValue[layer + 1][colum] == 0)
					mWorthToComputer[layer][colum][0] = 15;
				else
					mWorthToComputer[layer][colum][0] = 100;			
			}
			else
				mWorthToComputer[layer][colum][0] = 0;
		}
		
		else
		{
			if(Nblank > 2)
				mWorthToPlayer[layer][colum][0] = 90;
			else if(Nblank == 2)
			{
				if(mValue[layer - 1][colum] == 0 || mValue[layer + 1][colum] == 0)
					mWorthToPlayer[layer][colum][0] = 13;
				else
					mWorthToPlayer[layer][colum][0] = 90;			
			}
			
			else
				mWorthToPlayer[layer][colum][0] = 0;
		}
	}
	else if(count == 2)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][0] = 10;
		else
			mWorthToPlayer[layer][colum][0] = 8;
	}
	else if(count == 1)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][0] = 5;
		else
			mWorthToPlayer[layer][colum][0] = 3;
	}
	else
	{
		if(who == 1)
			mWorthToComputer[layer][colum][0] = 0;
		else
			mWorthToPlayer[layer][colum][0] = -2;
	}
}

void GobangWindow::_EstimateErect(int layer,int colum,int who)
{//纵向估计
	int i,count = 0,Nblank = 1;
	
	i=layer - 1;
	while(i>=0)
	{
		if(mValue[i][colum] == 0) Nblank++;
		if(mValue[i][colum] != who) break;
		else count++;
		i--;
	}
	i = layer + 1;
	while(i<15)
	{
		if(mValue[i][colum] == 0) Nblank++;
		if(mValue[i][colum] != who) break;
		else count++;
		i++;
	}
	
	if(count == 4)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][1] = 200;
		else
			mWorthToPlayer[layer][colum][1] = 180;
	}
	
	else if(count == 3)
	{
		if(who == 1)
		{
			if(Nblank > 2)
				mWorthToComputer[layer][colum][1] = 100;
			else if(Nblank == 2)
			{
				if(mValue[layer][colum-1]==0||mValue[layer][colum+1]==0)
					mWorthToComputer[layer][colum][1] = 15;
				else 
					mWorthToComputer[layer][colum][1] = 100;
			}
			else
				mWorthToComputer[layer][colum][1] = 0;
		}
		else
		{
			if(Nblank > 2)
				mWorthToPlayer[layer][colum][0] = 90;
			else if(Nblank == 2)
			{
				if(mValue[layer - 1][colum] == 0 || mValue[layer + 1][colum] == 0)
					mWorthToPlayer[layer][colum][0] = 13;
				else
					mWorthToPlayer[layer][colum][0] = 90;			
			}
			else
				mWorthToPlayer[layer][colum][0] = 0;
		}
	}
	else if(count == 2)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][1] = 10;
		else
			mWorthToPlayer[layer][colum][1] = 8;
	}
	else if(count == 1)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][1] = 5;
		else
			mWorthToPlayer[layer][colum][1] = 3;
	}
	else
	{
		if(who == 1)
			mWorthToComputer[layer][colum][1] = 0;
		else
			mWorthToPlayer[layer][colum][1] = -2;
	}
}
void GobangWindow::_Estimate45(int layer, int colum, int who)
{//主对角线上估计
	int i,j,count = 0,Nblank = 1;
	
	i = layer - 1;
	j = colum - 1;
	while(i>=0 && j>=0)
	{
		if(mValue[i][j] == 0) Nblank++;
		if(mValue[i][j] != who) break;
		else count++;
		i--;
		j--;
	}
	i = layer + 1;
	j = colum + 1;
	while(i<15 && j< 15)
	{
		if(mValue[i][j] == 0) Nblank++;
		if(mValue[i][j] != who) break;
		else
			count++;
		i++;
		j++;
	}
	if(count == 4)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][2] = 200;
		else
			mWorthToPlayer[layer][colum][2] = 180;
	}
	
	else if(count == 3)
	{
		if(who == 1)
		{
			if(Nblank > 2)
				mWorthToComputer[layer][colum][2] = 100;
			else if(Nblank == 2)
			{
				if(mValue[layer-1][colum -1]==0||mValue[layer+1][colum+1]==0)
					mWorthToComputer[layer][colum][2] = 15;
				else
					mWorthToComputer[layer][colum][2] = 100;
			}
			else
				mWorthToComputer[layer][colum][2] = 0;
		}
		else
		{
			if(Nblank > 2)
				mWorthToPlayer[layer][colum][2] = 90;
			else if(Nblank == 2)
			{
				if(mValue[layer-1][colum -1]==0||mValue[layer+1][colum+1]==0)
					mWorthToPlayer[layer][colum][2] = 13;
				else
					mWorthToPlayer[layer][colum][2] = 90;
			}
			else
				mWorthToPlayer[layer][colum][2] = 0;
		}
	}
	else if(count == 2)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][2] = 10;
		else
			mWorthToPlayer[layer][colum][2] = 8;
	}
	else if(count == 1)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][2] = 5;
		else
			mWorthToPlayer[layer][colum][2] = 3;
	}
	else
	{
		if(who == 1)
			mWorthToComputer[layer][colum][2] = 0;
		else
			mWorthToPlayer[layer][colum][2] = -2;
	}
}
void GobangWindow::_Estimate_45(int layer, int colum, int who)
{//副对角线上估计
	int i,j,count = 0,Nblank = 1;
	
	i = layer - 1;
	j = colum + 1;
	while(i>=0 && j<15)
	{//先往右上角，后往左下角
        if(mValue[i][j] == 0) Nblank++;
		if(mValue[i][j] != who) break;
		else count++;
		i--;
		j++;
	}
	i = layer + 1;
	j = colum - 1;
	while(i<15 && j>=0)
	{
		if(mValue[i][j] == 0) Nblank++;
		if(mValue[i][j] != who) break;
		else count++;
		i++;
		j--;
	}
	if(count == 4)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][3] = 200;
		else
			mWorthToPlayer[layer][colum][3] = 180;
	}
	
	else if(count == 3)
	{
		if(who == 1)
		{
			if(Nblank > 2)
				mWorthToComputer[layer][colum][3] = 100;
			else if(Nblank == 2)
			{
				if(mValue[layer-1][colum+1]==0||mValue[layer+1][colum-1]==0)
					mWorthToComputer[layer][colum][3] = 15;
				else
					mWorthToComputer[layer][colum][3] = 100;
			}
			else
				mWorthToComputer[layer][colum][3] = 0;
		}
		else
		{
			if(Nblank > 2)
				mWorthToPlayer[layer][colum][3] = 90;
			else if(Nblank == 2)
			{
				if(mValue[layer-1][colum+1]==0||mValue[layer+1][colum-1]==0)
					mWorthToPlayer[layer][colum][3] = 13;
				else
					mWorthToPlayer[layer][colum][3] = 90;
			}
			else
				mWorthToPlayer[layer][colum][3] = 0;
		}
	}
	else if(count == 2)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][3] = 10;
		else
			mWorthToPlayer[layer][colum][3] = 8;
	}
	else if(count == 1)
	{
		if(who == 1)
			mWorthToComputer[layer][colum][3] = 5;
		else
			mWorthToPlayer[layer][colum][3] = 3;
	}
	else
	{
		if(who == 1)
			mWorthToComputer[layer][colum][3] = 0;
		else
			mWorthToPlayer[layer][colum][3] = -2;
	}
}
bool GobangWindow::_IsGameEnded(int layer, int colum,int who)
{//判断刚才在i,j处的落子是否导致一方已经胜出
	int i, j, count;
	
	i = colum - 1;
	count = 1;
	while(i>=0)
	{
		if(mValue[layer][i] != who) break;
		if(mValue[layer][i] == who) count++;
		i--;
	}
	i = colum + 1;
	while(i<15)
	{
		if(mValue[layer][i] != who) break;
		if(mValue[layer][i] == who) count++;
		i++;
	}
	if(count >= 5)
		return true;
	
	i = layer - 1;
	count = 1;
	while(i>=0)
	{
		if(mValue[i][colum] != who) break;
		else count++;
		i--;
	}
	i = layer + 1;
	while(i<15)
	{
		if(mValue[i][colum] != who) break;
		else count++;
		i++;
	}
	if(count >= 5)
		return true;
	
	i = layer - 1;
	j = colum - 1;
	count = 1;
	while(i>=0 && j>=0)
	{
		if(mValue[i][j] != who) break;
		else count++;
		i--;
		j--;
	}
	i = layer + 1;
	j = colum + 1;
	while(i<15 && j< 15)
	{
		if(mValue[i][j] != who) break;
		else
			count++;
		i++;
		j++;
	}
	if(count >= 5)
		return true;
	
	i = layer - 1;
	j = colum + 1;
	count = 1;
	while(i>=0 && j<15)
	{//先往右上角，后往左下角
		if(mValue[i][j] != who) break;
		else count++;
		i--;
		j++;	
	}
	i = layer + 1;
	j = colum - 1;
	while(i<15 && j>=0)
	{
		if(mValue[i][j] != who) break;
		else count++;
		i++;
		j--;
	}
	if(count >= 5)
		return true;
	
	return false;
}
void GobangWindow::_GetBestPos(int *layer, int *colum)
{//选取分数最高的点
	//有待改进，因为每次都是选取最前面的那个分数最高的点，容易暴露自己的想法
	int max = -100;
	int i,j;

	for(i = 0; i < 15; i++)
		for(j = 0; j < 15; j++)
		{
			if(mValue[i][j] == 0)
			{
				_EstimateTranverse(i, j, 1);
				_EstimateErect(i, j, 1);
				_Estimate45(i, j, 1);
				_Estimate_45(i, j, 1);
				
				_EstimateTranverse(i, j, 2);
				_EstimateErect(i, j, 2);
				_Estimate45(i, j, 2);
				_Estimate_45(i, j, 2);
			}
		}
		
		for(i = 0; i < 15; i++)
			for(j = 0; j < 15; j++)
			{
				mWorth[i][j] = mWorthToComputer[i][j][0] + mWorthToComputer[i][j][1] +mWorthToComputer[i][j][2] + mWorthToComputer[i][j][3] +
				mWorthToPlayer[i][j][0] + mWorthToPlayer[i][j][1] + mWorthToPlayer[i][j][2] + mWorthToPlayer[i][j][3];
			}
			
	for(i=0; i<15; i++)
		for(j=0; j<15; j++)
			if(mValue[i][j] == 0 && max < mWorth[i][j])
			{
				max = mWorth[i][j];
				*layer = i;
				*colum = j;
			}
}
