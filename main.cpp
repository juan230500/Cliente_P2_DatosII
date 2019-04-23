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

//    QPixmap P1(":/image/image/Tablero.png");
//    QPixmap P2(":/image/image/Gladiador.jpg");

//    QLabel* L=new QLabel(&w);
//    L->resize(1200,700);
//    L->setPixmap(P1);

//    QLabel* L2=new QLabel(&w);
//    L2->resize(70,70);
//    L2->setPixmap(P2);
//    colocar(L2,1,2);

    w.show();

    return a.exec();
}
