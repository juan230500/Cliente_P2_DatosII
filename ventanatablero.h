#ifndef VENTANATABLERO_H
#define VENTANATABLERO_H

#include <QDialog>
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
class VentanaTablero;
}

class VentanaTablero : public QDialog
{
    Q_OBJECT

public:
    explicit VentanaTablero(QWidget *parent = 0);
    void inicializarScene();
    void inicializarView();
    void generarTablero();
    void posicionarCasilla(int xPos, int yPos, int valorTablero);
    void pintarCasilla(QGraphicsRectItem* rItem, Qt::GlobalColor color, std::vector<QGraphicsRectItem*>* vectorWidgets);
    void posicionarObstaculos(int obstaculos[][3], int largoArray);
    void mostrarRuta(std::string ruta);
    void eliminarCasillas(std::vector<QGraphicsRectItem*> vectorWidgets);
    ~VentanaTablero();

private:
    Ui::VentanaTablero* ui;
    QGraphicsScene* scene;
    QGraphicsView* view;
    QVBoxLayout* layoutVertical;
    std::vector<QGraphicsRectItem*> rutaWidgets;
    std::vector<QGraphicsRectItem*> obstaculosWidgets;
};

#endif // VENTANATABLERO_H
