#ifndef _TABLE_ROOM_H
#define _TABLE_ROOM_H
#include <QtGui>
#include "TwoPersonTable.h"

class TableRoom : public QTableWidget{
    public:
        TableRoom(QWidget *parent, int x, int y, int w, int h);
};

#endif
