#ifndef _TWO_PERSON_TABLE
#define _TWO_PERSON_TABLE
#include <QtGui>

class TwoPersonTable : public QWidget
{
    Q_OBJECT
    public:
        TwoPersonTable(int w, int h);
    private slots:
        void OnPushed();
    private:
        int mWidth,mHeight;
        QPushButton mButton1, mButton2;
};

#endif
