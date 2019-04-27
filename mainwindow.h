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
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void inicializarScene();
    void inicializarView();
    void generarTablero();
    void pintarCasilla(int xPos, int yPos, int valorCasilla);
    void agregarAVector(QGraphicsRectItem* rItem, Qt::GlobalColor color, std::vector<QGraphicsRectItem*>* vectorWidgets);
    void posicionarObstaculos(std::string obstaculos);
    void mostrarRuta(std::string ruta);
    void eliminarCasillas(std::vector<QGraphicsRectItem*> vectorWidgets);
    void ColocarObstaculo(char id, int fila, int columna);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QVBoxLayout* layoutVertical;
    QFrame* Frame;
    std::vector<QGraphicsRectItem*> rutaWidgets;
    std::vector<QGraphicsRectItem*> obstaculosWidgets;
    QGraphicsRectItem* tableroWidgets[10][10];
};

#endif // MAINWINDOW_H
