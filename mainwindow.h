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
#include "Socket.h"
#include "traductorcliente.h"
#include <QString>
#include <QColor>

#define DIMENSION 10

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void inicializarFrame();
    void inicializarScene();
    void inicializarView();
    void generarTablero();
    void pintarCasilla(int xPos, int yPos, int valorCasilla);
    void posicionarObstaculos(std::string obstaculos);
    void mostrarRuta(std::string ruta, bool A);
    void eliminarCasillas(std::vector<QGraphicsRectItem*> vectorWidgets);
    void colocarObstaculo(string id, int fila, int columna);
    void crearZonaObstaculo(int fila, int columna, int rango);
    void eliminarZonaObstaculos();
    ~MainWindow();

private slots:
    void generarSigIteracion();

private:
    bool Pintadas[DIMENSION][DIMENSION]={0};
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QVBoxLayout* layoutVertical;
    QFrame* frame;
    QLabel* texto;
    std::vector<QGraphicsRectItem*> rutaWidgets;
    std::vector<QGraphicsRectItem*> obstaculosWidgets;
    std::vector<QGraphicsRectItem*> zonaWidgets;
    QGraphicsRectItem* tableroWidgets[DIMENSION][DIMENSION];
    QPushButton* botonSigIteracion;
};

#endif // MAINWINDOW_H
