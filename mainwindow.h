#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "paricipant.h"
#include <QMainWindow>
#include <QVariant>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_add_clicked();
    void on_delete_2_clicked();
    void on_update_clicked();
    void on_search_clicked();
    void on_close_clicked();
    void on_sort_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_pdf_clicked();

void createServicePieChart() ;


void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_tabWidget_currentChanged(int index);

void on_sort_2_clicked();
void on_lineEdit_2_textChanged(const QString &arg1);
void on_pdf_2_clicked();

//void on_calendarWidget_clicked(const QDate &date);

void on_pushButton_3_clicked();
void on_calendarWidget_clicked(const QDate &date);
void on_pushButton_4_clicked();
void on_pushButton_5_clicked() ;

void on_reset_clicked();

void on_restore_clicked();

signals:
    void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);

private:
    Ui::MainWindow *ui;

    participant P;
};
#endif // MAINWINDOW_H
