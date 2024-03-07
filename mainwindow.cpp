#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError> // Ajout de cette directive pour gérer les erreurs SQL
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked() {
  // Get user input
  int id = ui->lineEdit_ID->text().toInt(); // Assuming ID is an integer
  QString nom = ui->lineEdit_nom->text();
  QString prenom = ui->lineEdit_prenom->text();
  QString adresse = ui->lineEdit_adresse->text(); // Assuming address field is lineEdit_6
  int phone = ui->lineEdit_telephone->text().toInt(); // Assuming phone field is lineEdit_3

  // Validate input (example)
  if (id <= 0 || nom.isEmpty() || prenom.isEmpty() || adresse.isEmpty() || phone <= 0) {
    QMessageBox::critical(this, "Erreur", "ID invalide ou champs vides!");
    return;
  }

  // Get values from ComboBox and RadioButtons
  QString role = ui->comboBox_5->currentText();
  QString skill;
  if (ui->radioButton->isChecked()) {
    skill = ui->radioButton->text(); // Assuming text reflects skill
  } else {
    skill = ui->radioButton_2->text(); // Assuming text reflects skill
  }

  // Get dates from DateEdits
  QString date_s = ui->dateEdit->date().toString("yyyy-MM-dd"); // Assuming format
  QString date_f = ui->dateEdit_2->date().toString("yyyy-MM-dd"); // Assuming format

  // Connect to database (assuming a connection named "myconnection")
  QSqlDatabase db = QSqlDatabase::database("myconnection");
  if (!db.isOpen()) {
    QMessageBox::critical(this, "Erreur", "Connexion à la base de données impossible!");
    return;
  }

  // Prepare a query with placeholders
  QString query = "INSERT INTO etudiant (id, nom, prenom, adresse, telephone, role, skill, date_s, date_f) VALUES (:id, :nom, :prenom, :adresse, :telephone, :role, :skill, :date_s, :date_f)";
  QSqlQuery sqlQuery(db);
  sqlQuery.prepare(query);

  // Bind values to placeholders
  sqlQuery.bindValue(":id", id);
  sqlQuery.bindValue(":nom", nom);
  sqlQuery.bindValue(":prenom", prenom);
  sqlQuery.bindValue(":adresse", adresse);
  sqlQuery.bindValue(":telephone", phone);
  sqlQuery.bindValue(":role", role);
  sqlQuery.bindValue(":skill", skill);
  sqlQuery.bindValue(":date_s", date_s);
  sqlQuery.bindValue(":date_f", date_f);

  // Execute the query
  if (!sqlQuery.exec()) {
    QMessageBox::critical(this, "Erreur", "Echec de l'ajout de l'étudiant!");
    QDebug << sqlQuery.lastError().text();
  }

  QMessageBox::information(this, "Succès", "Étudiant ajouté avec succès!");
}

