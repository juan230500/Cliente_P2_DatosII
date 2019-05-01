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

//    Socket  *socket= &Socket::getInstance();
//    string json = socket->escuchar(8081);
//    string obstaculos;
//    string ruta;
//    int g1[9];
//    int g2[9];
//    bool finalizacion;
//    int avanceGenetico;
//    TraductorCliente *traductor = new TraductorCliente();
//    traductor->DeserializarInfoDeSimulacion(json, &obstaculos, g1, g2, &finalizacion, &avanceGenetico, &ruta);
//    posicionarObstaculos(obstaculos);
//    mostrarRuta(ruta);
//    texto->setText(QString::fromStdString(json));
////    socket->enviar("holi:3",8080,"192.168.100.18");

    w.show();

    return a.exec();
}
