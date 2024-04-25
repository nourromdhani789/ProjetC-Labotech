#include "statistics.h"
#include "ui_statistics.h"
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QWidget>
#include<QSqlQuery>
#include<workshop.h>

statistics::statistics(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statistics)
{
    ui->setupUi(this);
}

statistics::~statistics()
{
    delete ui;
}
void statistics::make()
{
        int yesnbr;
        int nonbr;
        int total;
        QString Numb;
        QString Etat;
        QSqlQuery q;

        q.prepare("SELECT COUNT(idworkshop) FROM workshop where reservation ='yes' ");
        q.exec();
        q.first() ;
        yesnbr=(q.value(0).toInt());

        q.prepare("SELECT COUNT(idworkshop) FROM workshop where reservation ='no' ");
        q.exec();
        q.first() ;
        nonbr=(q.value(0).toInt());
        q.prepare("SELECT COUNT(idworkshop) FROM workshop ");
        q.exec();
        q.first() ;
        total=(q.value(0).toInt());
        yesnbr=((double)yesnbr/(double)total)*100;
        nonbr=100-yesnbr;

        Numb=QString::number(yesnbr);
        Etat=QString::number(nonbr);
        QPieSeries *series;
         series= new  QPieSeries();
         series->append("With Reservation"+Numb+"%",yesnbr);
         series->append("No Reservation"+Etat+"%",nonbr);
         QPieSlice *slice0 = series->slices().at(0);
          slice0->setLabelVisible();

          QPieSlice *slice1 = series->slices().at(1);
             slice1->setExploded();
             slice1->setLabelVisible();
             slice1->setPen(QPen(Qt::darkRed, 2));
             slice1->setBrush(Qt::black);

              QChart *chart = new QChart();
              chart->addSeries(series);
              chart->setTitle("Statistics of Reservation's States ");
              chart->legend()->show();
              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);
              ui->verticalLayout->addWidget(chartView);

}
