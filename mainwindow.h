#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QGraphicsRectItem>
#include <QTextStream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QTime>
#include "stats.h"
#include "Socket.h"
#include "traductorcliente.h"


#define DIMENSION 10

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void inicializarFrame();
    void inicializarScene();
    void inicializarView();
    void generarTablero();
    void Muerte(int fila, int columna, bool A);
    void DibujarInicio(int fila, int columna, bool A);
    void pintarCasilla(int xPos, int yPos, int valorCasilla);
    void posicionarObstaculos(std::string obstaculos);
    void mostrarRuta(std::string ruta, bool A);
    void eliminarCasillas(std::vector<QGraphicsRectItem*> vectorWidgets);
    void colocarObstaculo(string id, int fila, int columna);
    void crearZonaObstaculo(int fila, int columna, int rango);
    void eliminarZonaObstaculos();
    void resetWidgets();
    void obtenerJson();
    void imprimirDatos();
    void cicloParcial();
    void detenerEjecucion();
    ~MainWindow();

private slots:
    void sigIteracion();
    void generarEstadisticas();


private:
    bool Pintadas[DIMENSION][DIMENSION]={0};
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QVBoxLayout* layoutVertical;
    QFrame* frame;
    QLabel* textoA;
    QLabel* textoB;
    std::vector<QGraphicsRectItem*> rutaWidgets;
    std::vector<QGraphicsRectItem*> obstaculosWidgets;
    std::vector<QGraphicsRectItem*> zonaWidgets;
    QGraphicsRectItem* tableroWidgets[DIMENSION][DIMENSION];
    QPushButton* botonSigIteracion;
    QPushButton* botonStats;
    QLabel* Muerto1;
    QLabel* Muerto2;
    QLabel* Gladiador1;
    QLabel* Gladiador2;
    int contIteraciones;
    std::string obstaculos, rutaPathfinding, rutaBacktracking, muerte1, muerte2;
    float prom1, prom2;
    int g1[10], g2[10];
    bool finalizacion;
    int avanceGenetico;
    Stats* VentanaEstadisticas;
};

#endif // MAINWINDOW_H
