#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

#define FONDO "#222831"
#define COLOR_RUTA_A "#ff2e63"
#define COLOR_RUTA_B "#08d9d6"
#define COLOR_RUTA_C "#6a2c70"

const int CASILLA = 68*10/DIMENSION;

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
    contIteraciones=0;

//    string obstaculos = "111-572-733";
//    posicionarObstaculos(obstaculos);
//    string ruta = "00-01-02-03-04-14-24-34-44-54-64-65-66-67-68-69-79-89-99";
//    mostrarRuta(ruta, 1);
}

void MainWindow::inicializarFrame(){
    QLabel* L1=new QLabel(this);
    QPixmap P1(":/image/image/Fondo1.png");
    L1->resize(1200,700);
    L1->setPixmap(P1);

    frame=new QFrame(this);
    frame->setGeometry(0,0,700,700);

    textoA=new QLabel(this);
    textoA->setGeometry(750,50,200,500);
    textoA->setStyleSheet("QLabel { background-color : white; color : blue; }");
    textoA->setText("What ever text");

    textoB=new QLabel(this);
    textoB->setGeometry(975,50,200,500);
    textoB->setStyleSheet("QLabel { background-color : white; color : blue; }");
    textoB->setText("What ever text");

    botonSigIteracion = new QPushButton("Siguiente Iteracion", this);
    connect(botonSigIteracion, SIGNAL (clicked()),this, SLOT (sigIteracion()));
    botonSigIteracion->setGeometry(750, 600,150, 50);

    botonStats = new QPushButton("Estadísticas", this);
    connect(botonStats, SIGNAL (clicked()),this, SLOT (generarEstadisticas()));
    botonStats->setGeometry(950, 600, 150, 50);

    Gladiador1=new QLabel(this);
    QPixmap Pg1(":/image/image/Gladiador.jpg");
    Gladiador1->setGeometry(700,700,CASILLA,CASILLA);
    Gladiador1->setPixmap(Pg1.scaled(CASILLA,CASILLA,Qt::KeepAspectRatio));
    Gladiador2=new QLabel(this);
    QPixmap Pg2(":/image/image/Gladiador.jpg");
    Gladiador2->setGeometry(700,700,CASILLA,CASILLA);
    Gladiador2->setPixmap(Pg2.scaled(CASILLA,CASILLA,Qt::KeepAspectRatio));

    Muerto1=new QLabel(this);
    QPixmap Pi1(":/image/image/F1.png");
    Muerto1->setGeometry(700,700,CASILLA,CASILLA);
    Muerto1->setPixmap(Pi1.scaled(CASILLA,CASILLA,Qt::KeepAspectRatio));
    Muerto2=new QLabel(this);
    QPixmap Pi2(":/image/image/F2.png");
    Muerto2->setGeometry(700,700,CASILLA,CASILLA);
    Muerto2->setPixmap(Pi2.scaled(CASILLA,CASILLA,Qt::KeepAspectRatio));
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
    if (A){
        Muerto1->setGeometry(10+68*columna,10+68*fila,CASILLA,CASILLA);
    }
    else{
        Muerto2->setGeometry(10+68*columna,10+68*fila,CASILLA,CASILLA);
    }

}

void MainWindow::DibujarInicio(int fila, int columna, bool A)
{
    if (A){
        Gladiador1->setGeometry(10+68*columna,10+68*fila,CASILLA,CASILLA);
    }
    else{
        Gladiador2->setGeometry(10+68*columna,10+68*fila,CASILLA,CASILLA);
    }
}

void MainWindow::generarEstadisticas()
{
    Stats* nw=new Stats(this);
    nw->show();
    hide();
}

void MainWindow::posicionarObstaculos(string obstaculos){
    if(obstaculos == "") return;
    obstaculos = obstaculos.substr(0, obstaculos.size()-1);
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
    ruta = ruta.substr(0, ruta.size()-1);
    vector<string> vectorRuta;
    boost::split(vectorRuta, ruta, boost::is_any_of("-"));
    int cantidadElementos = vectorRuta.size();
    for(int indice = 0; indice < cantidadElementos; indice++){
        int xPos = stoi(vectorRuta[indice].substr(0,1));
        int yPos = stoi(vectorRuta[indice].substr(1,1));
        if (indice==0){
            if (A){
                DibujarInicio(xPos,yPos,0);
            }
            else{
                DibujarInicio(xPos,yPos,1);
            }
        }
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

void MainWindow::sigIteracion(){
    contIteraciones++;
    resetWidgets();
    obtenerJson();
    if(contIteraciones%3 == 0){
        cicloParcial();
    }else{
        mostrarRuta(rutaPathfinding, 0);
        mostrarRuta(rutaBacktracking, 1);
        posicionarObstaculos(obstaculos);
        if(muerte1 != "") Muerte(stoi(muerte1.substr(0,1)), stoi(muerte1.substr(1,1)), 1);
        if(muerte2 != "") Muerte(stoi(muerte2.substr(0,1)), stoi(muerte2.substr(1,1)), 0);
    }
}

void MainWindow::resetWidgets(){
    eliminarCasillas(obstaculosWidgets);
    eliminarCasillas(rutaWidgets);
    eliminarZonaObstaculos();
    for(int i = 0; i < DIMENSION; i++){
        for(int j = 0; j < DIMENSION; j++){
            Pintadas[i][j] = 0;
        }
    }
}

void MainWindow::obtenerJson(){
    Socket  *socket= &Socket::getInstance();
    socket->enviar("", 8082, "172.18.184.24");
    string json = socket->escuchar(8081);
    TraductorCliente *traductor = new TraductorCliente();
    traductor->DeserializarInfoDeSimulacion(json, &obstaculos, g1, g2, &finalizacion, &avanceGenetico,
                                            &rutaPathfinding, &rutaBacktracking, &muerte1, &muerte2);
}

void MainWindow::cicloParcial(){
    botonSigIteracion->setDisabled(true);
    Muerto1->setVisible(false);
    Muerto2->setVisible(false);
    bool terminoJ1 = false, terminoJ2 = false;
    while(muerte1 == "" || muerte2 == ""){
        resetWidgets();
        if(muerte1 != "" && !terminoJ1){
            terminoJ1 = true;
            Muerto1->setVisible(true);
            Gladiador1->setVisible(false);
            Muerte(stoi(muerte1.substr(0,1)), stoi(muerte1.substr(1,1)), 1);
        }
        if(muerte2 != "" && !terminoJ2){
            terminoJ2 = true;
            Muerto2->setVisible(true);
            Gladiador2->setVisible(false);
            Muerte(stoi(muerte2.substr(0,1)), stoi(muerte2.substr(1,1)), 0);
        }
        if(!terminoJ1) mostrarRuta(rutaPathfinding, 0);
        if(!terminoJ2) mostrarRuta(rutaBacktracking, 1);
        posicionarObstaculos(obstaculos);
        obtenerJson();
        detenerEjecucion();
    }
    botonSigIteracion->setDisabled(false);
}

void MainWindow::detenerEjecucion(){
    QTime dieTime= QTime::currentTime().addSecs(2);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::~MainWindow(){
    delete ui;
}
