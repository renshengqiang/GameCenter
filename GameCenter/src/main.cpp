#include "TableRoom.h"
#include <qapplication.h>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    /*
    QTextCodec *local_codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(local_codec);
    QTextCodec::setCodecForCStrings(local_codec);
    QTextCodec::setCodecForTr(local_codec);
    */
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());  
        QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QWidget *window = new QWidget();
    window->setGeometry(200, 200, 1024, 768);
    TableRoom *pRoom = new TableRoom(window, 0,0, 1024, 768);
    window->show();
    return app.exec();
}
