#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employee.h"
#include "paricipant.h"
#include "resource.h"
#include"project.h"
#include <QMainWindow>
#include <QVariant>
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
    void on_addN_clicked();
    void on_delete_2N_clicked();
    void on_updateN_clicked();
    void on_searchN_clicked();
    void on_closeN_clicked();
    void on_sortN_clicked();
    void on_lineEditN_textChanged(const QString &arg1);
    void on_pdfN_clicked();

void createServicePieChartN() ;
void on_pushButton_3_clicked();

void on_pushButton_supprimer_clicked();

void on_pushButton_modify_clicked();

void on_search_clicked();

void on_pushButton_tri_clicked();

void on_lineEdit_rec_textChanged(const QString &arg1);

void createServicePieChart();

void on_PDF_clicked();

void on_metier1_clicked();

QStringList determineProjects(int teamID);

QList<QPair<int, QString>>determineLowResources();
//void on_checkButton_clicked();



//void on_pushButton_2N_clicked();

void on_tabWidget_currentChanged(int index);

void on_sort_2N_clicked();
void on_lineEdit_2N_textChanged(const QString &arg1);
void on_pdf_2N_clicked();

//void on_calendarWidget_clicked(const QDate &date);

void on_pushButton_3N_clicked();
void on_calendarWidgetN_clicked(const QDate &date);
void on_pushButton_4N_clicked();
void on_pushButton_5N_clicked() ;

void displayEventsOnCalendar();
void on_pushButton_6N_clicked();
void on_resetN_clicked();

void on_restoreN_clicked();
///////////////////////IMEN
void on_pushButton_ajoutE_2_clicked();

   void on_radioButton_IDE_2_clicked();

   void on_radioButton_NOME_2_clicked();

   void on_pushButton_MODIFE_2_clicked();

   void on_pushButton_RECHERCHEE_2_clicked();

   void on_pushButton_SUPPE_2_clicked();

   void on_pushButton_statsE_2_clicked();

   void on_pushButton_pdfE_2_clicked();

   void on_chercherE_2_textChanged(const QString &arg1);

   void on_to_emailE_2_clicked();

   void on_retour_employerrE_2_clicked();

   void on_envoyer_2E_2_clicked();

   void on_choose_pictureE_2_clicked();

   void on_choose_picture_modifierE_2_clicked();

   void on_tab_employeE_2_activated(const QModelIndex &index);
   //void test();
   void on_pushButton_15_clicked();

   void on_pushButton_14_clicked();

   void on_pushButton_13_clicked();

   //////////////////AZOUZ
   void on_pushButton_showA_clicked();

   void on_pushButton_2A_clicked();

   void on_pushButton_show_2A_clicked();

   void on_pushButton_3A_clicked();

   void on_pushButtonA_clicked();

   void on_pushButton_5A_clicked();

   void on_lineEdit_textChanged(const QString &arg1);

   void on_pushButton_6A_clicked();

   void on_pushButton_7A_clicked();

   void on_pushButton_8A_clicked();

   //void on_pushButton_9_clicked();


  // void on_pushButton_2_A_clicked();

   void on_pushButton_16_clicked();

public:
    void updateLowResourcesList();

    void on_PDF_2_clicked();
signals:
  /*  void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);
*/
private:
    Ui::MainWindow *ui;

    participant P;
    employee e;
    Resource R;
    Project Pr;

      // Arduino a;
       // QByteArray enteredID,key;
};
#endif // MAINWINDOW_H
