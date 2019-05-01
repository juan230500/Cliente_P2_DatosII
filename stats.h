#ifndef STATS_H
#define STATS_H

#include <QDialog>
#include <QVector>
#include <QGraphicsScene>
#include <QLabel>

namespace Ui {
class Stats;
}

class Stats : public QDialog
{
    Q_OBJECT

public:
    void plot();
    void iniciar();
    explicit Stats(QWidget *parent = nullptr);
    ~Stats();

private slots:
    void on_Ok_clicked();

private:
    QWidget *parent;
    QGraphicsScene* scene;
    QPushButton* OK;
    Ui::Stats *ui;
};

#endif // STATS_H
