#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

#define DIMENSION 10
#define CASILLA 68

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inicializarScene();
    inicializarView();
    generarTablero();
    string obstaculos = "111-572-733";
    posicionarObstaculos(obstaculos);
    string ruta = "00-01-02-03-04-14-24-34-44-54-64-65-66-67-68-69-79-89-99";
    mostrarRuta(ruta);
//    eliminarCasillas(obstaculosWidgets);
//    eliminarCasillas(rutaWidgets);
//    eliminarZonaObstaculos();
}

void MainWindow::inicializarScene(){
    this->setWindowTitle("GLADIADORES");

    QLabel* L1=new QLabel(this);
    QPixmap P1(":/image/image/Fondo1.png");
    L1->resize(1200,700);
    L1->setPixmap(P1);

    frame=new QFrame(this);
    frame->setGeometry(0,0,700,700);

    texto=new QLabel(this);
    texto->setGeometry(750,50,400,600);
    texto->setStyleSheet("QLabel { background-color : white; color : blue; }");
    texto->setText("What ever text");

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,0,0);
    scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
}

void MainWindow::inicializarView(){
    QGraphicsView* view = new QGraphicsView(scene);
    view->setInteractive(true);
    view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    layoutVertical = new QVBoxLayout(frame);
    layoutVertical->addWidget(view);
}

void MainWindow::generarTablero(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            QRectF rect(0,0,CASILLA,CASILLA);
            QGraphicsRectItem* rItem = new QGraphicsRectItem(rect);
            scene->addItem(rItem);
            tableroWidgets[i][j] = rItem;
            rItem->setPos(j*CASILLA, i*CASILLA);
            rItem->setBrush(QBrush(Qt::darkRed, Qt::SolidPattern));
        }
    }
}

void MainWindow::agregarAVector(QGraphicsRectItem* rItem, Qt::GlobalColor color, vector<QGraphicsRectItem*>* vectorWidgets){
    rItem->setBrush(QBrush(color, Qt::SolidPattern));
    vectorWidgets->push_back(rItem);
}

void MainWindow::posicionarObstaculos(string obstaculos){
    vector<string> vectorObstaculos;
    boost::split(vectorObstaculos, obstaculos, boost::is_any_of("-"));
    for(int indice = 0; indice < vectorObstaculos.size(); indice++){
        int xPos = stoi(vectorObstaculos[indice].substr(0,1));
        int yPos = stoi(vectorObstaculos[indice].substr(1,1));
        string tipoObstaculo = vectorObstaculos[indice].substr(2,1).c_str();
        colocarObstaculo(tipoObstaculo, xPos, yPos);
    }
}

void MainWindow::mostrarRuta(string ruta){
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    int cantidadElementos = vectorRuta.size();
    for(int indice = 0; indice < cantidadElementos; indice++){
        int xPos = stoi(vectorRuta[indice].substr(0,1));
        int yPos = stoi(vectorRuta[indice].substr(1,1));
        QGraphicsRectItem* rItem = tableroWidgets[xPos][yPos];
        rItem->setBrush(QBrush(Qt::lightGray, Qt::SolidPattern));
        rutaWidgets.push_back(rItem);
    }
}

void MainWindow::eliminarCasillas(vector<QGraphicsRectItem*> vectorWidgets){
    int cantidadWidgets = vectorWidgets.size();
    for(int indice = 0; indice < cantidadWidgets; indice++){
        vectorWidgets[indice]->setBrush(QBrush(Qt::darkRed, Qt::SolidPattern));
    }
    vectorWidgets.clear();
}

void MainWindow::colocarObstaculo(string id, int fila, int columna)
{
    QString path=":/image/image/";
    path+=QString::fromStdString(id);
    path+=".png";
    qDebug()<<path;

    QGraphicsRectItem* casillaObstaculo = tableroWidgets[fila][columna];
    QBrush myBrush;
    myBrush.setTextureImage(QImage(path).scaled(CASILLA,CASILLA,Qt::KeepAspectRatio));
    casillaObstaculo->setBrush(myBrush);
    obstaculosWidgets.push_back(casillaObstaculo);

    int rango = (id == "1") ? 1:2;
    crearZonaObstaculo(fila, columna, rango);
}

void MainWindow::crearZonaObstaculo(int fila, int columna, int rango){
    qDebug()<<QString::number(rango);
    int zona = (rango == 1) ? 3:5;
    QRectF rect(0,0,CASILLA*zona,CASILLA*zona);
    QGraphicsRectItem* rItem = new QGraphicsRectItem(rect);
    scene->addItem(rItem);
    QPen pen(Qt::yellow);
    pen.setWidth(3);
    rItem->setPen(pen);
    rItem->setPos((columna-rango)*CASILLA, (fila-rango)*CASILLA);
    zonaWidgets.push_back(rItem);
}

void MainWindow::eliminarZonaObstaculos(){
    for(int i = 0; i < zonaWidgets.size(); i++){
        QGraphicsRectItem* zona = zonaWidgets[i];
        scene->removeItem(zona);
        delete zona;
    }zonaWidgets.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}
