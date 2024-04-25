#include "statis.h"
#include "ui_statis.h"
#include<QSqlQuery>
#include<workshop.h>

statis::statis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::statis)
{
    ui->setupUi(this);
}

statis::~statis()
{
    delete ui;
}
void statis::make()
{
        int numb;
        int etat;
        int total;
        QString Numb;
        QString Etat;
        QSqlQuery q;

        q.prepare("SELECT COUNT(id_ab) FROM blocs where etat ='Numb' ");
        q.exec();
        q.first() ;
        Numb=(q.value(0).toInt());

        q.prepare("SELECT COUNT(id_ab) FROM blocs where etat ='Etat' ");
        q.exec();
        q.first() ;
        etat=(q.value(0).toInt());
        q.prepare("SELECT COUNT(id_ab) FROM blocs ");
        q.exec();
        q.first() ;
        total=(q.value(0).toInt());
        numb=((double)numb/(double)total)*100;
        etat=100-numb;

        Numb=QString::number(numb);
        Etat=QString::number(etat);
        QPieSeries *series;
         series= new  QPieSeries();
         series->append("NUMB"+Numb+"%",numb);
         series->append("ETAT"+Etat+"%",etat);
         QPieSlice *slice0 = series->slices().at(0);
          slice0->setLabelVisible();

          QPieSlice *slice1 = series->slices().at(1);
             slice1->setExploded();
             slice1->setLabelVisible();
             slice1->setPen(QPen(Qt::darkRed, 2));
             slice1->setBrush(Qt::black);

              QChart *chart = new QChart();
              chart->addSeries(series);
              chart->setTitle("Statistiques sur les etat et les bloc  ");
              chart->legend()->show();
              QChartView *chartView = new QChartView(chart);
              chartView->setRenderHint(QPainter::Antialiasing);
              ui->verticalLayout->addWidget(chartView);

}
