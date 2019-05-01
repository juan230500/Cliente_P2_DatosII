#ifndef STATS_H
#define STATS_H

#include <QDialog>

namespace Ui {
class Stats;
}

class Stats : public QDialog
{
    Q_OBJECT

public:
    explicit Stats(QWidget *parent = nullptr);
    ~Stats();

private slots:
    void on_Ok_clicked();

private:
    QWidget *parent;
    Ui::Stats *ui;
};

#endif // STATS_H
