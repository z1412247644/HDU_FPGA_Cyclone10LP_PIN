#include "mainwindow.h"
#include <QApplication>
#include<QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("HDU EDA Auxiliary Tool");
    QIcon icon(":/img/ico");
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
