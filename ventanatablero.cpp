#include "ventanatablero.h"
#include "ui_ventanatablero.h"
#define DIMENSION 10
#define CASILLA 50
using namespace std;
VentanaTablero::VentanaTablero(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaTablero)
{
    ui->setupUi(this);
    inicializarScene();
    inicializarView();
    generarTablero();
    int obstaculos[][3] = {{1,1,1},{5,7,2},{9,3,3}};
    int largoArray = sizeof(obstaculos)/sizeof(obstaculos[0]);
    posicionarObstaculos(obstaculos, largoArray);
    string ruta = "00-01-02-03-04-14-24-34-44-54-64-65-66-67-68-69-79-89-99";
    mostrarRuta(ruta);
    eliminarCasillas(rutaWidgets);
}

void VentanaTablero::inicializarScene(){
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,0,0);
    scene->setBackgroundBrush(QBrush(Qt::darkGreen, Qt::SolidPattern));
}

void VentanaTablero::inicializarView(){
    QGraphicsView* view = new QGraphicsView(scene);
    view->setInteractive(true);
    view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    layoutVertical = new QVBoxLayout(ui->frame);
    layoutVertical->addWidget(view);
}

void VentanaTablero::generarTablero(){
    for(int i = 0; i < DIMENSION; i++){
        for(int j = 0; j < DIMENSION; j++){
            posicionarCasilla(i*CASILLA, j*CASILLA, 0);
        }
    }
}

void VentanaTablero::posicionarCasilla(int guiYPos, int guiXPos, int valorCasilla){
    QRectF rect(0,0,CASILLA,CASILLA);
    QGraphicsRectItem* rItem = new QGraphicsRectItem(rect);
    scene->addItem(rItem);
    rItem->setPos(guiXPos, guiYPos);
    switch (valorCasilla) {
    case 0:
        rItem->setBrush(QBrush(Qt::darkRed, Qt::SolidPattern));
        break;
    case 1:
        pintarCasilla(rItem, Qt::darkCyan, obstaculosWidgets);
        break;
    case 2:
        pintarCasilla(rItem, Qt::darkGreen, obstaculosWidgets);
        break;
    case 3:
        pintarCasilla(rItem, Qt::darkMagenta, obstaculosWidgets);
        break;
    case 4:
        pintarCasilla(rItem, Qt::lightGray, rutaWidgets);
        break;
    default:
        break;
    }
}

void VentanaTablero::pintarCasilla(QGraphicsRectItem* rItem, Qt::GlobalColor color, vector<QGraphicsRectItem*> vectorWidgets){
    rItem->setBrush(QBrush(color, Qt::SolidPattern));
    vectorWidgets.push_back(rItem);
}

void VentanaTablero::posicionarObstaculos(int obstaculos[3][3], int largoArray){
    for(int indice = 0; indice < largoArray; indice++){
        int xPos = obstaculos[indice][0] * CASILLA;
        int yPos = obstaculos[indice][1] * CASILLA;
        int tipoObstaculo = obstaculos[indice][2];
        posicionarCasilla(xPos, yPos, tipoObstaculo);
    }
}

void VentanaTablero::mostrarRuta(string ruta){
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    int cantidadElementos = vectorRuta.size();
    for(int indice = 0; indice < cantidadElementos; indice++){
        int xPos = stoi(vectorRuta[indice].substr(0,1));
        int yPos = stoi(vectorRuta[indice].substr(1,1));
        posicionarCasilla(xPos*CASILLA, yPos*CASILLA, 4);
    }
}

void VentanaTablero::eliminarCasillas(vector<QGraphicsRectItem*> widgets){
    int cantidadWidgets = widgets.size();
    for(int indice = 0; indice < cantidadWidgets; indice++){
        scene->removeItem(widgets[indice]);
    }
}


//QString imagePath = QCoreApplication::applicationDirPath() + QString::fromStdString("/direccion/"+nombre+".png");
//myBrush.setTextureImage(QImage(imagePath));

VentanaTablero::~VentanaTablero()
{
    delete ui;
}
