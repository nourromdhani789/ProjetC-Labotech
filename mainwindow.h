#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "workshop.h"
#include <QtWidgets/QLineEdit>

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

        void on_Add_WorkShop_clicked();

        void on_edit_workshop_clicked();

        void on_reset_workshop_edit_clicked();

        void on_delete_workshop_clicked();

        void on_reset_workshop_delete_clicked();


        void on_reset_workshop_add_clicked();

        void on_yes_reservation_workshop_clicked();

        void on_no_reservation_workshop_clicked();

        void on_yes_reservation_workshop_edit_clicked();

        void on_no_reservation_workshop_edit_clicked();

private:
    Ui::MainWindow *ui;
    Workshop W;
};
#endif // MAINWINDOW_H
