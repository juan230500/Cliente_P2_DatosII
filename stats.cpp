#include "stats.h"
#include "ui_stats.h"

void Stats::plot()
{
    ui->customPlot->axisRect()->setBackground(QPixmap("./solarpanels.jpg"));
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(QColor(255, 200, 20, 200));
    pen.setStyle(Qt::DashLine);
    pen.setWidthF(2.5);
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setBrush(QBrush(QColor(255,200,20,70)));
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QPixmap("./sun.png")));
    // set graph name, will show up in legend next to icon:
    ui->customPlot->graph()->setName("Data from Photovoltaic\nenergy barometer 2011");
    // set data:
    QVector<double> year, value;
    year  << 2005 << 2006 << 2007 << 2008  << 2009  << 2010 << 2021;
    value << 2.17 << 3.42 << 4.94 << 10.38 << 15.86 << 29.33 << 52.1;
    ui->customPlot->graph()->setData(year, value);

    // set title of plot:
    ui->customPlot->plotLayout()->insertRow(0);
    ui->customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot, "Regenerative Energies", QFont("sans", 12, QFont::Bold)));
    // axis configurations:
    ui->customPlot->xAxis->setLabel("Year");
    ui->customPlot->yAxis->setLabel("Installed Gigawatts of\nphotovoltaic in the European Union");
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setTickLabels(false);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->xAxis2->setSubTicks(false);
    ui->customPlot->yAxis2->setSubTicks(false);
    ui->customPlot->xAxis->setRange(2004.5, 2031.5);
    ui->customPlot->yAxis->setRange(0, 52);
    // setup legend:
    ui->customPlot->legend->setFont(QFont(font().family(), 7));
    ui->customPlot->legend->setIconSize(50, 20);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);
}

void Stats::iniciar()
{
    QLabel* L1=new QLabel(this);
    QPixmap P1(":/image/image/Fondo1.png");
    L1->resize(1200,700);
    L1->setPixmap(P1);
}

Stats::Stats(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Stats)
{
    this->parent=parent;
    iniciar();
    ui->setupUi(this);
    plot();
}

Stats::~Stats()
{
    delete ui;
}

void Stats::on_Ok_clicked()
{
    parent->show();
    hide();
}
