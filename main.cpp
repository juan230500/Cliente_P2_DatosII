#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPixmap>

void colocar(QLabel* L,int fila,int columna){
    L->setGeometry(columna*70,fila*70,L->width(),L->height());
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
