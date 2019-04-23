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
    string obstaculos = "111-572-933";
    posicionarObstaculos(obstaculos);
    string ruta = "00-01-02-03-04-14-24-34-44-54-64-65-66-67-68-69-79-89-99";
    mostrarRuta(ruta);
    //eliminarCasillas(obstaculosWidgets);
    Socket  *socket= &Socket::getInstance();
    socket->escuchar(8081);
    socket->enviar("holi:3",8080,"192.168.100.18");
}

void MainWindow::inicializarScene(){
    this->setWindowTitle("GLADIADORES");

    QLabel* L1=new QLabel(this);
    QPixmap P1(":/image/image/Fondo1.png");
    L1->resize(1200,700);
    L1->setPixmap(P1);

    Frame=new QFrame(this);
    Frame->setGeometry(0,0,700,700);

    QLabel* L2=new QLabel(this);
    L2->setGeometry(750,50,400,600);
    L2->setStyleSheet("QLabel { background-color : white; color : blue; }");
    L2->setText("What ever text");

    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,0,0);
    scene->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
}

void MainWindow::inicializarView(){
    QGraphicsView* view = new QGraphicsView(scene);
    view->setInteractive(true);
    view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    layoutVertical = new QVBoxLayout(Frame);
    layoutVertical->addWidget(view);
}

void MainWindow::generarTablero(){
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            QRectF rect(0,0,CASILLA,CASILLA);
            QGraphicsRectItem* rItem = new QGraphicsRectItem(rect);
            scene->addItem(rItem);
            tableroWidgets[i][j] = rItem;
            pintarCasilla(i, j, 0);
            rItem->setPos(j*CASILLA, i*CASILLA);
        }
    }
}

void MainWindow::pintarCasilla(int xPos, int yPos, int valorCasilla){
    QGraphicsRectItem* rItem = tableroWidgets[xPos][yPos];
    switch (valorCasilla) {
        case 0:
            rItem->setBrush(QBrush(Qt::darkRed, Qt::SolidPattern));
            break;
        case 1:
            agregarAVector(rItem, Qt::darkCyan, &obstaculosWidgets);
            break;
        case 2:
            agregarAVector(rItem, Qt::darkGreen, &obstaculosWidgets);
            break;
        case 3:
            agregarAVector(rItem, Qt::darkMagenta, &obstaculosWidgets);
            break;
        case 4:
            agregarAVector(rItem, Qt::lightGray, &rutaWidgets);
            break;
        default:
            break;
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
        int tipoObstaculo = stoi(vectorObstaculos[indice].substr(2,1));
        pintarCasilla(xPos, yPos, tipoObstaculo);
    }
}

void MainWindow::mostrarRuta(string ruta){
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    int cantidadElementos = vectorRuta.size();
    for(int indice = 0; indice < cantidadElementos; indice++){
        int xPos = stoi(vectorRuta[indice].substr(0,1));
        int yPos = stoi(vectorRuta[indice].substr(1,1));
        pintarCasilla(xPos, yPos, 4);
    }
}

void MainWindow::eliminarCasillas(vector<QGraphicsRectItem*> vectorWidgets){
    int cantidadWidgets = vectorWidgets.size();
    for(int indice = 0; indice < cantidadWidgets; indice++){
        vectorWidgets[indice]->setBrush(QBrush(Qt::darkRed, Qt::SolidPattern));
    }
    vectorWidgets.clear();
}


//QString imagePath = QCoreApplication::applicationDirPath() + QString::fromStdString("/direccion/"+nombre+".png");
//myBrush.setTextureImage(QImage(imagePath));

MainWindow::~MainWindow()
{
    delete ui;
}
