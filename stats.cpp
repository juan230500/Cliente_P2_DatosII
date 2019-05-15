#include "stats.h"
#include "ui_stats.h"

void Stats::plot()
{
    ui->customPlot->addGraph();
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    QPen pen;
    pen.setColor(QColor("#08d9d6"));
    pen.setStyle(Qt::DashLine);
    pen.setWidthF(2.5);
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->graph()->setBrush(QBrush(QColor(8, 217, 214, 70)));
    // set graph name, will show up in legend next to icon:
    ui->customPlot->graph()->setName("Población 1 (A*)");
    // set data:


    ui->customPlot->addGraph();
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    pen.setColor(QColor("#ff2e63"));
    pen.setStyle(Qt::DashLine);
    pen.setWidthF(2.5);
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->graph()->setBrush(QBrush(QColor(255, 46, 99 ,70)));
    // set graph name, will show up in legend next to icon:
    ui->customPlot->graph()->setName("Población 2 (Backtracking)");
    // set data:

    // set title of plot:
    ui->customPlot->plotLayout()->insertRow(0);
    ui->customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot, "Resistencia de las poblaciones", QFont("sans", 12, QFont::Bold)));
    // axis configurations:
    ui->customPlot->xAxis->setLabel("Generacion");
    ui->customPlot->yAxis->setLabel("Resistencia promedio");
    ui->customPlot->xAxis2->setVisible(true);
    ui->customPlot->yAxis2->setVisible(true);
    ui->customPlot->xAxis2->setTickLabels(false);
    ui->customPlot->yAxis2->setTickLabels(false);
    ui->customPlot->xAxis2->setTicks(false);
    ui->customPlot->yAxis2->setTicks(false);
    ui->customPlot->xAxis2->setSubTicks(false);
    ui->customPlot->yAxis2->setSubTicks(false);
    ui->customPlot->xAxis->setRange(0, 20);
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
    QPixmap P1(":/image/image/Fondo1.jpg");
    L1->resize(1200,700);
    L1->setPixmap(P1);
    generacion=0;
}

void Stats::add(float Resistencia1, float Resistencia2)
{
    year<<generacion;
    value<<Resistencia1;
    year2<<generacion;
    value2<<Resistencia2;
    int tmp= (Resistencia1 > Resistencia2) ? Resistencia1+1 : Resistencia2+1;
    ui->customPlot->xAxis->setRange(0, generacion);
    ui->customPlot->yAxis->setRange(3.5, tmp );
    ui->customPlot->graph(0)->setData(year, value);
    ui->customPlot->graph(1)->setData(year2, value2);
    ui->customPlot->replot();
    ui->customPlot->update();
    generacion++;
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
