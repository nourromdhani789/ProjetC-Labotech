#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workshop.h"

#include<QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->afficher_Workshop->setModel(W.afficher());
    ui->tab1->setCurrentIndex(1);
    QString reservation = "yes";
}

MainWindow::~MainWindow()
{
    ui->afficher_Workshop->setModel(W.afficher());
    delete ui;

}


void MainWindow::on_Add_WorkShop_clicked()
{
    ui->yes_reservation_workshop->isChecked();
    QString reservation = "yes";
    if (ui->yes_reservation_workshop->isChecked())
        QString reservation="yes";
    else QString reservation="no";
    QString room=ui->Add_Rooms->currentText();
    QString capacity=ui->Add_Capacity->currentText();

    QString idworkshop= ui->IdWorKShop->text();
    ui->Add_Rooms->setCurrentIndex(1);
    ui->Add_Capacity->setCurrentIndex(1);

  Workshop W(idworkshop,room,capacity,reservation);

  bool test=W.ajouter();
  if(test)
{
ui->afficher_Workshop->setModel(W.afficher());
QMessageBox::information(nullptr, QObject::tr("Ajouter un client"),
                  QObject::tr("Client ajouté.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);
}}

void MainWindow::on_reset_workshop_add_clicked()
{
    ui->Add_Rooms->setCurrentIndex(0);
    ui->Add_Capacity->setCurrentIndex(0);
    ui->IdWorKShop->setText("");

}


void MainWindow::on_edit_workshop_clicked()
{
    QString capacity = ui->Edit_Capacity-> currentText();
    QString room=ui->Edit_Rooms->currentText();
    QString IdWorKShopEdit = ui->IdWorKShop_2->text();

    ui->Edit_Rooms->setCurrentIndex(0);
    ui->Edit_Capacity->setCurrentIndex(0);
    ui->yes_reservation_workshop_edit->isChecked();
    QString reservation = "yes";
    if (ui->yes_reservation_workshop_edit->isChecked())
        QString reservation="yes";
    else QString reservation="no";
    Workshop W(IdWorKShopEdit,room,capacity,reservation) ;
    bool test1=W.modifier(room,capacity,reservation,IdWorKShopEdit) ;

    if(test1){
        ui->afficher_Workshop->setModel(W.afficher());
    QMessageBox::information(nullptr, QObject::tr("modification Fonction"),
                QObject::tr("Fonction modifié.\n"
                            "Click OK to exit."), QMessageBox::Cancel);
    }
}



void MainWindow::on_reset_workshop_edit_clicked()
{
    ui->Edit_Rooms->setCurrentIndex(1);
    ui->Edit_Capacity->setCurrentIndex(1);
    ui->IdWorKShop_2->setText("");

}

void MainWindow::on_delete_workshop_clicked()
{
    QString IdWorkshopDelete = ui->IdWorkshopDelete->text();


           if(W.supprimer(IdWorkshopDelete))
           {
               ui->afficher_Workshop->setModel(W.afficher());
               QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("suppression effectué.\n"
                                       "Click ok to exit."), QMessageBox::Cancel);
           }
           else
           {
               QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                           QObject::tr("suppression non effectue.\n"
                                       "Click OK to exit."), QMessageBox::Cancel);
           }

}

void MainWindow::on_reset_workshop_delete_clicked()
{
    ui->IdWorkshopDelete->setText("");

}





void MainWindow::on_yes_reservation_workshop_clicked()
{
    ui->yes_reservation_workshop->isChecked();
    QString reservation = "yes";

}

void MainWindow::on_no_reservation_workshop_clicked()
{
    ui->no_reservation_workshop->isChecked();
    QString reservation = "no";
}

void MainWindow::on_yes_reservation_workshop_edit_clicked()
{
    ui->yes_reservation_workshop_edit->isChecked();
    QString reservation = "no";
}

void MainWindow::on_no_reservation_workshop_edit_clicked()
{
    ui->no_reservation_workshop_edit->isChecked();
    QString reservation = "no";
}
