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
    void posicionarCasilla(int xPos, int yPos, int valorTablero);
    void pintarCasilla(QGraphicsRectItem* rItem, Qt::GlobalColor color, std::vector<QGraphicsRectItem*>* vectorWidgets);
    void posicionarObstaculos(int obstaculos[][3], int largoArray);
    void mostrarRuta(std::string ruta);
    void eliminarCasillas(std::vector<QGraphicsRectItem*> vectorWidgets);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QVBoxLayout* layoutVertical;
    std::vector<QGraphicsRectItem*> rutaWidgets;
    std::vector<QGraphicsRectItem*> obstaculosWidgets;
    std::vector<std::vector<QGraphicsRectItem*>> tableroWidgets;
};

#endif // MAINWINDOW_H
