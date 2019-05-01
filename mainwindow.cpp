#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

#define CASILLA 68
#define FONDO "#222831"
#define COLOR_RUTA_A "#ff2e63"
#define COLOR_RUTA_B "#08d9d6"
#define COLOR_RUTA_C "#6a2c70"


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("GLADIADORES");
    inicializarFrame();
    inicializarScene();
    inicializarView();
    generarTablero();
    string obstaculos = "111-572-733";
    posicionarObstaculos(obstaculos);
    string ruta = "00-01-02-03-04-14-24-34-44-54-64-65-66-67-68-69-79-89-99";
    mostrarRuta(ruta, 1);
    Muerte(1,3,0);
}

void MainWindow::inicializarFrame(){
    QLabel* L1=new QLabel(this);
    QPixmap P1(":/image/image/Fondo1.png");
    L1->resize(1200,700);
    L1->setPixmap(P1);

    frame=new QFrame(this);
    frame->setGeometry(0,0,700,700);
    texto=new QLabel(this);
    texto->setGeometry(750,50,400,500);
    texto->setStyleSheet("QLabel { background-color : white; color : blue; }");
    texto->setText("What ever text");
    botonSigIteracion = new QPushButton("Siguiente Iteracion", this);
    connect(botonSigIteracion, SIGNAL (clicked()),this, SLOT (generarSigIteracion()));
    botonSigIteracion->setGeometry(750, 600,150, 50);

    botonStats = new QPushButton("Estadísticas", this);
    connect(botonStats, SIGNAL (clicked()),this, SLOT (generarEstadisticas()));
    botonStats->setGeometry(950, 600, 150, 50);
}

void MainWindow::inicializarScene(){
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,0,0);
    scene->setBackgroundBrush(QBrush(QColor(FONDO), Qt::SolidPattern));
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
    for(int i = 0; i < DIMENSION; i++){
        for(int j = 0; j < DIMENSION; j++){
            QRectF rect(0,0,CASILLA,CASILLA);
            QGraphicsRectItem* rItem = new QGraphicsRectItem(rect);
            scene->addItem(rItem);
            tableroWidgets[i][j] = rItem;
            rItem->setPos(j*CASILLA, i*CASILLA);
            rItem->setBrush(QBrush(QColor(FONDO), Qt::SolidPattern));
        }
    }
}

void MainWindow::Muerte(int fila, int columna, bool A)
{
    QString path;
    if (A)  path=":/image/image/F1.png";
    else  path=":/image/image/F2.png";
    QGraphicsRectItem* casillaObstaculo = tableroWidgets[fila][columna];
    QBrush myBrush;
    myBrush.setTextureImage(QImage(path).scaled(CASILLA,CASILLA,Qt::KeepAspectRatio));
    casillaObstaculo->setBrush(myBrush);
}

void MainWindow::generarEstadisticas()
{
    Stats* nw=new Stats(this);
    nw->show();
    hide();
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

void MainWindow::mostrarRuta(string ruta, bool A){
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    int cantidadElementos = vectorRuta.size();
    for(int indice = 0; indice < cantidadElementos; indice++){
        int xPos = stoi(vectorRuta[indice].substr(0,1));
        int yPos = stoi(vectorRuta[indice].substr(1,1));
        QGraphicsRectItem* rItem = tableroWidgets[xPos][yPos];

        if (Pintadas[xPos][yPos]) {
            rItem->setBrush(QBrush(QColor(COLOR_RUTA_C), Qt::SolidPattern));
        }
        else if(A){
            Pintadas[xPos][yPos]=1;
            rItem->setBrush(QBrush(QColor(COLOR_RUTA_A), Qt::SolidPattern));
        }
        else{
            Pintadas[xPos][yPos]=1;
            rItem->setBrush(QBrush(QColor(COLOR_RUTA_B), Qt::SolidPattern));
        }

        rutaWidgets.push_back(rItem);
    }
}

void MainWindow::eliminarCasillas(vector<QGraphicsRectItem*> vectorWidgets){
    int cantidadWidgets = vectorWidgets.size();
    for(int indice = 0; indice < cantidadWidgets; indice++){
        vectorWidgets[indice]->setBrush(QBrush(QColor(FONDO), Qt::SolidPattern));
    }
    vectorWidgets.clear();
}

void MainWindow::colocarObstaculo(string id, int fila, int columna)
{
    QString path=":/image/image/" + QString::fromStdString(id) + ".png";
    QGraphicsRectItem* casillaObstaculo = tableroWidgets[fila][columna];
    QBrush myBrush;
    myBrush.setTextureImage(QImage(path).scaled(CASILLA,CASILLA,Qt::KeepAspectRatio));
    casillaObstaculo->setBrush(myBrush);
    obstaculosWidgets.push_back(casillaObstaculo);
    crearZonaObstaculo(fila, columna, (id == "1") ? 1:2);
}

void MainWindow::crearZonaObstaculo(int fila, int columna, int rango){
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
    }
    zonaWidgets.clear();
}

void MainWindow::generarSigIteracion(){
    eliminarCasillas(obstaculosWidgets);
    eliminarCasillas(rutaWidgets);
    eliminarZonaObstaculos();
    for(int i = 0; i < DIMENSION; i++){
        for(int j = 0; j < DIMENSION; j++){
            Pintadas[i][j] = 0;
        }
    }
    string obstaculos = "551-572-343";
    posicionarObstaculos(obstaculos);
    string ruta = "00-10-20-30-40-50-60-70-80-90-91-92-93-94-95-96-97-98-99";
    mostrarRuta(ruta,0);
}

MainWindow::~MainWindow(){
    delete ui;
}
