#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "project.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_number->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_number_2->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_number_3->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_budget->setValidator(new QIntValidator(0,99999999,this));
    ui->lineEdit_budget_2->setValidator(new QIntValidator(0,99999999,this));
    ui->tableView->setModel(P.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_show_clicked()
{
    // Check if all required fields are filled
    if (ui->lineEdit_number->text().isEmpty() || ui->lineEdit_title->text().isEmpty() || ui->lineEdit_description->text().isEmpty() || ui->lineEdit_budget->text().isEmpty() || ui->comboBox->currentText().isEmpty())
    {QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),QObject::tr("Veuillez remplir tous les champs obligatoires."), QMessageBox::Cancel);return;    }
    int num=ui->lineEdit_number->text().toInt();
    QString title=ui->lineEdit_title->text();
    QString description=ui->lineEdit_description->text();
    QString budget=ui->lineEdit_budget->text();
    QString progress=ui->comboBox->currentText();
    Project P(num,title,description,budget,progress);
    bool test=P.ajouter();

    if(test)
    {
        ui->tableView->setModel(P.afficher());
        ui->lineEdit_number->clear();
        ui->lineEdit_title->clear();
        ui->lineEdit_description->clear();
        ui->lineEdit_budget->clear();
        Project P(num,title,description,budget,progress);
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Ajout effectué\n""Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Ajout non effectué\n""Click Cancel to exit"),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_2_clicked()
{
    int num=ui->lineEdit_number_3->text().toInt();
    bool test=P.supprimer(num);
    if(test)
    {
        ui->tableView->setModel(P.afficher());
        ui->lineEdit_number_3->clear();
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectué\n""Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Suppression non effectué\n""Click Cancel to exit"),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_show_2_clicked()
{
    int num = ui->lineEdit_number_2->text().toInt();
        QString title = ui->lineEdit_title_2->text();
        QString description = ui->lineEdit_description_2->text();
        QString budget = ui->lineEdit_budget_2->text();
        QString progress = ui->comboBox_2->currentText();

        bool test = P.modifier(num, title, description, budget, progress);

        if(test)
        {
            ui->tableView->setModel(P.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Mise à jour effectuée\n""Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Mise à jour non effectuée\n""Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tableView->setModel(P.afficher());
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    int num=ui->lineEdit_number_3->text().toInt();
    QString res = QString::number(num);
    query.prepare("select * from Project where num=:num");
    query.bindValue(":num",res);
    if(query.exec()&&query.first())
    {
        //QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectué\n""Click Cancel to exit"),QMessageBox::Cancel);
        ui->lineEdit_title_2->setText(query.value("title").toString());
        ui->lineEdit_description_2->setText(query.value("description").toString());
        ui->lineEdit_budget_2->setText(query.value("budget").toString());
        ui->comboBox_2->setEditText(query.value("progress").toString());
    }
    /*else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Suppression non effectué\n""Click Cancel to exit"),QMessageBox::Cancel);*/
}
