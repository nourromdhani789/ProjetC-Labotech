#ifndef STATISTICS_H
#define STATISTICS_H
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QWidget>>

namespace Ui {
class statistics;
}

class statistics : public QWidget
{
    Q_OBJECT

public:
    explicit statistics(QWidget *parent = nullptr);
    void make();
    ~statistics();

private:
    Ui::statistics *ui;
};

#endif // STATISTICS_H
