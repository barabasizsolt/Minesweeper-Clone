#include "grid.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Grid w;
    //Grid w(nullptr,16,16,40);
    //Grid w(nullptr,16,30,99);
    w.show();
    return a.exec();
}
