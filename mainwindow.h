#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employee.h"
#include "arduino.h"
#include <QMainWindow>
#include<QFileDialog>
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

    void on_pushButton_ajout_clicked();

    void on_radioButton_ID_clicked();

    void on_radioButton_NOM_clicked();

    void on_pushButton_MODIF_clicked();

    void on_pushButton_RECHERCHE_clicked();

    void on_pushButton_SUPP_clicked();

    void on_pushButton_stats_clicked();

    void on_pushButton_pdf_clicked();

    void on_chercher_textChanged(const QString &arg1);

    void on_to_email_clicked();

    void on_retour_employerr_clicked();

    void on_envoyer_2_clicked();

    void on_choose_picture_clicked();

    void on_choose_picture_modifier_clicked();

    void on_tab_employe_activated(const QModelIndex &index);
    void test();
private:
    Ui::MainWindow *ui;
    employee e;
    Arduino a;
     QByteArray enteredID,key;
};
#endif // MAINWINDOW_H
