#ifndef STATS_H
#define STATS_H

#include <QDialog>
#include <QVector>
#include <QGraphicsScene>
#include <QLabel>
#include <QColor>

namespace Ui {
class Stats;
}

class Stats : public QDialog
{
    Q_OBJECT

public:
    void plot();
    void iniciar();
    void add(int Resistencia1,int Resistencia);
    explicit Stats(QWidget *parent = nullptr);
    ~Stats();

private slots:
    void on_Ok_clicked();

private:
    int generacion=0;
    QVector<double> year, value;
    QVector<double> year2, value2;
    QWidget *parent;
    QGraphicsScene* scene;
    QPushButton* OK;
    Ui::Stats *ui;
};

#endif // STATS_H
