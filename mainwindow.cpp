#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resource.h"
#include "connection.h"
#include <QString>
#include <iostream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(R.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_3_clicked()
{
    int idr=ui->lineEdit_idr->text().toInt();
    int price=ui->lineEdit_price->text().toInt();
    QString type = ui->comboBox_type->currentText();
    int alloc=ui->lineEdit_alloc->text().toInt();
    int storage = ui->comboBox_storage->currentText().toInt();

    QString date_exp=ui->lineEdit_date_exp->text();



    Resource R(idr,price,type,alloc,100,storage,date_exp);
    bool test = R.ajouter();

    if(test){
         ui->tableView->setModel(R.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),QObject::tr("ajout effectué\n click cancel to exit."), QMessageBox::Cancel);

        ui->lineEdit_idr->clear();
        ui->lineEdit_price->clear();
        ui->comboBox_type->setCurrentIndex(0);
        ui->lineEdit_alloc->clear();
        ui->comboBox_storage->setCurrentIndex(0);
        ui->lineEdit_date_exp->clear();

    }
    else QMessageBox::critical(nullptr, QObject::tr("NOT OK"),QObject::tr("l'ajout est echoué\n click cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int idr=ui->lineEdit_13->text().toInt();
        bool test=R.supprimer(idr);
        if(test)
        {
            ui->tableView->setModel(R.afficher());
            QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectué\n""Click Cancel to exit"),QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Suppression non effectué\n""Click Cancel to exit"),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_modify_clicked()
{
    int idr = ui->lineEdit_4->text().toInt();
    int price = ui->lineEdit_11->text().toInt();
    QString type = ui->comboBox_6->currentText();
    int alloc = ui->lineEdit_10->text().toInt();
    int stock = ui->lineEdit_14->text().toInt();
    int storage = ui->comboBox_8->currentText().toInt();
    QString date_exp = ui->lineEdit_12->text();

    bool test = R.modifier(idr, price, type, alloc, stock,storage,date_exp);

    if(test)
    {
                ui->tableView->setModel(R.afficher());
                QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Mise à jour effectuée\n""Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);
                ui->lineEdit_4->clear();
                ui->lineEdit_11->clear();
                ui->comboBox_6->setCurrentIndex(0);
                ui->lineEdit_10->clear();
                ui->lineEdit_14->clear();
                ui->comboBox_8->setCurrentIndex(0);
                ui->lineEdit_12->clear();

    }
            else
                QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Mise à jour non effectuée\n""Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);
    }



void MainWindow::on_search_clicked()
{
    // Get the idp from the line edit
        int idr = ui->lineEdit_4->text().toInt();

        // Call the recherche function to search for the participant with the given ID
        QSqlQueryModel *resultModel = R.recherche(idr);

        // Check if the result model has any rows (i.e., if participant with given ID is found)
        if (resultModel->rowCount() > 0) {
            // Retrieve the data from the model (assuming only one row is returned)
            //int foundIdr = resultModel->index(0, 0).data().toInt();
            QString foundPrice = resultModel->index(0, 1).data().toString();
            QString foundType = resultModel->index(0, 2).data().toString();
            QString foundAlloc = resultModel->index(0, 3).data().toString();
            QString foundStock = resultModel->index(0, 4).data().toString();
            QString foundStorage = resultModel->index(0, 5).data().toString();
            QString foundDate_exp = resultModel->index(0, 6).data().toString();


            // Display the retrieved data in UI elements
           // ui->lineEdit_11->setText(QString::number(foundIdp)); // ID              // conversion exemple QString::number(foundTel)
            ui->lineEdit_11->setText(foundPrice);
            ui->comboBox_6->setCurrentText(foundType);
            ui->lineEdit_10->setText(foundAlloc);
            ui->lineEdit_14->setText(foundStock);
            ui->comboBox_8->setCurrentText(foundStorage);
            ui->lineEdit_12->setText(foundDate_exp);


            // Display success message
            QMessageBox::information(nullptr, QObject::tr("OK"),
                                     QObject::tr("Resource trouvé."), QMessageBox::Cancel);
        } else {
            // Participant not found, display error message
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                     QObject::tr("Resource non trouvé."), QMessageBox::Cancel);
        }
}
