#include "TableRoom.h"

TableRoom::TableRoom(QWidget *parent, int x, int y, int w, int h):
    QTableWidget(25, 4)
{
    QTableWidget::setGeometry(x, y, w, h);
    QTableWidget::setParent(parent);
    for(int i = 0; i < 25; i++)
    {
        QTableWidget::setRowHeight(i, 80);
        for(int j=0; j < 4; j++)
        {
            QTableWidget::setColumnWidth(j, w/4);
            TwoPersonTable *pTable = new TwoPersonTable(w/4, 80);
            QTableWidget::setCellWidget(i,j,pTable);
        }
    }
}
