#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "resource.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /////////////////////////////////////////////
private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modify_clicked();

    void on_search_clicked();

private:
    Ui::MainWindow *ui;
    Resource R;
};
#endif // MAINWINDOW_H
