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
    VentanaEstadisticas=new Stats(this);
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
    QPixmap P1(":/image/image/Fondo1.jpg");
    L1->resize(1200,700);
    L1->setPixmap(P1.scaled(1200,700,Qt::IgnoreAspectRatio));

    frame=new QFrame(this);
    frame->setGeometry(0,0,700,700);

    QLabel* T1=new QLabel(this);
    QPixmap PT1(":/image/image/pergamino.jpg");
    T1->setGeometry(750,50,200,500);
    T1->setPixmap(PT1.scaled(200,500,Qt::KeepAspectRatio));

    QLabel* T2=new QLabel(this);
    QPixmap PT2(":/image/image/pergamino.jpg");
    T2->setGeometry(975,50,200,500);
    T2->setPixmap(PT2.scaled(200,500,Qt::KeepAspectRatio));

    int id = QFontDatabase::addApplicationFont(":/image/image/PRAEBRG_.TTF");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);
    f.setPointSize(16);

    textoA=new QLabel(this);
    textoA->setGeometry(750,50,200,500);
    textoA->setStyleSheet("QLabel { background-color : white; color : rgba(81,6,0); }");
    textoA->setAttribute(Qt::WA_TranslucentBackground);
    textoA->setFont( f);
    textoA->setAlignment(Qt::AlignCenter);

    textoB=new QLabel(this);
    textoB->setGeometry(975,50,200,500);
    textoB->setStyleSheet("QLabel { background-color : white; color : rgba(81,6,0); }");
    textoB->setAttribute(Qt::WA_TranslucentBackground);
    textoA->setFont( f);
    textoA->setAlignment(Qt::AlignCenter);


    botonSigIteracion = new QPushButton("Iniciar Partida", this);
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
    VentanaEstadisticas->show();
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
    botonSigIteracion->setDisabled(true);
    botonSigIteracion->setText("Siguiente Generación");
    Muerto1->setVisible(false);
    Muerto2->setVisible(false);
    Gladiador1->setVisible(true);
    Gladiador2->setVisible(true);
    contIteraciones++;
    resetWidgets();
    if(contIteraciones%3 == 0){
        cicloParcial();
    }else{
        cicloCompleto();
        if(ganador>=0) declararGanador();
    }
    qDebug()<<"SALIO";
    botonSigIteracion->setDisabled(false);
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
    socket->enviar("", 8082, "192.168.100.17");
    qDebug()<<"ESCUCHANDOOOOOOOOOO";
    string json = socket->escuchar(8081);
    TraductorCliente *traductor = new TraductorCliente();
    traductor->DeserializarInfoDeSimulacion(json, &obstaculos, g1, g2, &finalizacion, &prom1, &prom2,
                                            &rutaPathfinding, &rutaBacktracking, &muerte1, &muerte2, &ganador);

}

void MainWindow::imprimirDatos()
{
    QString S1="GLADIADOR 1 \n";
    QString S2="GLADIADOR 2 \n";
    QString Palabras[10]={
        "Id",
        "Edad",
        "Prob. de supervivencia",
        "Generación final esperada",
        "Inteligencia emocional",
        "Condición física",
        "Fuerza tronco superior",
        "Fuerza tronco inferior",
        "Resistencia",
        "Tiempo (us)"
    };

    for (int i=0;i<10;i++){
        S1+=Palabras[i]+": "+QString::number(g1[i])+"\n";
        S2+=Palabras[i]+": "+QString::number(g2[i])+"\n";
    }

    textoA->setText(S1);
    textoB->setText(S2);
}

void MainWindow::cicloCompleto(){
    obtenerJson();
    imprimirDatos();
    VentanaEstadisticas->add(prom1, prom2);
    posicionarObstaculos(obstaculos);
    animacionCicloCompleto();
}

void MainWindow::animacionCicloCompleto(){
    mostrarRuta(rutaPathfinding, 0);
    mostrarRuta(rutaBacktracking, 1);
    detenerEjecucion();
    bool continuarRuta1 = true, continuarRuta2 = true;
    while(continuarRuta1 || continuarRuta2){
        resetWidgets();
        posicionarObstaculos(obstaculos);
        qDebug()<<rutaPathfinding.c_str()<<to_string(rutaPathfinding.size()).c_str();
        qDebug()<<rutaBacktracking.c_str()<<to_string(rutaBacktracking.size()).c_str();

        if(rutaPathfinding.size() > 2){
           if(continuarRuta1) rutaPathfinding = rutaPathfinding.substr(3, rutaPathfinding.size()-3);
        }else{
           qDebug()<<"ENTRA1";
           continuarRuta1 = false;
        }
        mostrarRuta(rutaPathfinding, 0);

        if(rutaBacktracking.size() > 2){
            if(continuarRuta2) rutaBacktracking = rutaBacktracking.substr(3, rutaBacktracking.size()-3);
        }else{
            qDebug()<<"ENTRA2";
            continuarRuta2 = false;
        }
        mostrarRuta(rutaBacktracking, 1);

        if(rutaPathfinding.substr(0, 2) == muerte1 && continuarRuta1){
            qDebug()<<"MUERTE1";
            Muerte(stoi(muerte1.substr(0,1)), stoi(muerte1.substr(1,1)), 1);
            Muerto1->setVisible(true);
            continuarRuta1 = false;
        }
        if(rutaBacktracking.substr(0, 2) == muerte2 && continuarRuta2){
            qDebug()<<"MUERTE2";
            Muerte(stoi(muerte2.substr(0,1)), stoi(muerte2.substr(1,1)), 0);
            Muerto2->setVisible(true);
            continuarRuta2 = false;
        }
        if(continuarRuta1 || continuarRuta2) detenerEjecucion();
    }
}

void MainWindow::cicloParcial(){
    bool terminoJ1 = false, terminoJ2 = false, primerCiclo = true;
    muerte1 = ""; muerte2 = "";
    while(muerte1 == "" || muerte2 == ""){
        obtenerJson();
        imprimirDatos();
        if(primerCiclo){
            VentanaEstadisticas->add(prom1, prom2);
            primerCiclo = false;
        }
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
        detenerEjecucion();
        if((rutaBacktracking == "99" && terminoJ1) || (rutaPathfinding == "99" && terminoJ2)){
            if(ganador >= 0){
                declararGanador();
                break;
            }
        }
    }
}

void MainWindow::declararGanador(){
    string msgGanador;
    if(ganador == 2) msgGanador = "El límite de generaciones (15) se ha alcanzado. Ningún gladiador es digno!";
    else msgGanador = (ganador == 0) ? "El Gladiador 1 (A Star) ha sido el ganador!":
                                         "El Gladiador 2 (Backtracking) ha sido el ganador!";
    botonSigIteracion->setText("Nueva Partida");
    QMessageBox msgBox;
    msgBox.setText(msgGanador.c_str());
    msgBox.setWindowTitle("Partida terminada");
    msgBox.exec();
    botonSigIteracion->disconnect();
    connect(botonSigIteracion, SIGNAL (clicked()),this, SLOT (nuevaPartida()));
}

void MainWindow::nuevaPartida(){
    contIteraciones = 0;
    resetWidgets();
    Muerto1->setVisible(false);
    Muerto2->setVisible(false);
    Gladiador1->setVisible(false);
    Gladiador2->setVisible(false);
    botonSigIteracion->setText("Iniciar Partida");
    botonSigIteracion->disconnect();
    connect(botonSigIteracion, SIGNAL (clicked()),this, SLOT (sigIteracion()));
    Socket  *socket= &Socket::getInstance();
    socket->enviar("", 8082, "192.168.100.17");
}

void MainWindow::detenerEjecucion(){
    QTime dieTime= QTime::currentTime().addSecs(1);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::~MainWindow(){
    delete ui;
}
