#include "Gobang.h"
#include <qapplication.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GobangWindow mainWnd(200, 200);
    mainWnd.show(); 
    return a.exec();
}
