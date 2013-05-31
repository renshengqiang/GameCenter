#include "TwoPersonTable.h"
#include <QProcess>

TwoPersonTable::TwoPersonTable(int w, int h):
    mWidth(w), mHeight(h)
{
    mButton1.setParent(this);
    mButton2.setParent(this);
    mButton1.setGeometry(0, 0, w/3, h);
    mButton2.setGeometry(2*w/3, 0, w/3, h);

    mButton1.setText(tr("点击进入"));
    mButton2.setText(tr("点击进入"));
    connect(&mButton1, SIGNAL(clicked(bool)), this, SLOT(OnPushed()));
}
void TwoPersonTable::OnPushed()
{
    QProcess *pProcess = new QProcess(this);
    pProcess->start("./Gobang");
}
