#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paricipant.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_add_clicked()
{
    // Check if all required fields are filled
    if (ui->lineEditajouter_idp->text().isEmpty() || ui->lineEditajouter_name->text().isEmpty() || ui->lineEditajouter_lastname->text().isEmpty() ||
        ui->lineEditajouter_adress->text().isEmpty() || ui->lineEditajouter_tel->text().isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Veuillez remplir tous les champs obligatoires."), QMessageBox::Cancel);
        return; // Stop further execution
    }

    // Check if phone number is a valid integer
    bool ok;
    int tel = ui->lineEditajouter_tel->text().toInt(&ok);
    if (!ok || ui->lineEditajouter_tel->text().length() != 8) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Le numéro de téléphone doit être un nombre entier de 8 chiffres."), QMessageBox::Cancel);
        return; // Stop further execution
    }
    // Validate name, last name, and address fields using regular expressions
        QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ]+(?:\\s[a-zA-ZÀ-ÿ]+)?$"); // Pattern for names (allowing accented characters and a space)
        QRegularExpressionMatch nameMatch = nameRegex.match(ui->lineEditajouter_name->text());
        QRegularExpressionMatch lastnameMatch = nameRegex.match(ui->lineEditajouter_lastname->text());
        QRegularExpression addressRegex("^[a-zA-Z0-9\\s,'-]*$"); // Pattern for address (allowing alphanumeric characters, spaces, and common special characters)
        QRegularExpressionMatch addressMatch = addressRegex.match(ui->lineEditajouter_adress->text());

        if (!nameMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Nom invalide. Veuillez entrer un nom valide."), QMessageBox::Cancel);
            return; // Stop further execution
        }

        if (!lastnameMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Nom de famille invalide. Veuillez entrer un nom de famille valide."), QMessageBox::Cancel);
            return; // Stop further execution
        }

        if (!addressMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Adresse invalide. Veuillez entrer une adresse valide."), QMessageBox::Cancel);
            return; // Stop further execution
        }

    //recupiration des informations saisies
    int idp=ui->lineEditajouter_idp->text().toInt();
    QString name=ui->lineEditajouter_name->text();
    QString lastname=ui->lineEditajouter_lastname->text();
    QString adress=ui->lineEditajouter_adress->text();
    // Retrieve skill from combobox
    QString skill = ui->comboBoxajouter_role->currentText();

    // Retrieve role from radio buttons
    QString role;
    if(ui->radioButtonajouter_1->isChecked())
        role = ui->radioButtonajouter_1->text();
    else if(ui->radioButtonajouter_2->isChecked())
        role = ui->radioButtonajouter_2->text();
    else {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Veuillez sélectionner un rôle."), QMessageBox::Cancel);
        return; // Stop further execution
    }

    // Retrieve dates from date edits
    QDate dateStart = ui->dateEditajouter_1->date();
    QDate dateEnd = ui->dateEditajouter_2->date();
    QString datestart = dateStart.toString("yyyy-MM-dd");
    QString dateend = dateEnd.toString("yyyy-MM-dd");

    // Create a participant object with the retrieved information
    participant etmp(idp,name,lastname,adress,tel,skill,role,datestart,dateend);

    // Add the participant to the database
    bool test=etmp.ajouter();

    if (test) {
        // Successfully added participant, update table view and clear input fields
        ui->tableView->setModel(etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

        // Clear input fields
        ui->lineEditajouter_idp->clear(); // ID field
        ui->lineEditajouter_name->clear(); // Name field
        ui->lineEditajouter_lastname->clear(); // Last name field
        ui->lineEditajouter_adress->clear(); // Address field
        ui->lineEditajouter_tel->clear(); // Phone number field
        ui->comboBoxajouter_role->setCurrentIndex(0); // Set combobox to first item (skill)
        ui->radioButtonajouter_1->setChecked(false); // Uncheck role radio button 1
        ui->radioButtonajouter_2->setChecked(false); // Uncheck role radio button 2
        ui->dateEditajouter_1->setDate(QDate()); // Set date edit to today's date
        ui->dateEditajouter_2->setDate(QDate()); // Set date edit to today's date
    } else {
        // Addition failed, display error message
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}




void MainWindow::on_delete_2_clicked()
{
    int idp=ui->lineEditdelete_idp->text().toInt();
    bool test=etmp.supprimer(idp);

    if(test)
    {
        ui->tableView->setModel(etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("supprimer effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEditdelete_idp->clear(); // ID field


}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("supprimer failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

void MainWindow::on_update_clicked() {
    // Check if all required fields are filled
    if (ui->lineEditupdate_idp->text().isEmpty() || ui->lineEditupdate_name->text().isEmpty() || ui->lineEditupdate_lastname->text().isEmpty() ||
        ui->lineEditupdate_adress->text().isEmpty() || ui->lineEditupdate_tel->text().isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Veuillez remplir tous les champs obligatoires."), QMessageBox::Cancel);
        return; // Stop further execution
    }

    // Check if phone number is a valid integer
    bool ok;
    int tel = ui->lineEditupdate_tel->text().toInt(&ok);
    if (!ok || ui->lineEditupdate_tel->text().length() != 8) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Le numéro de téléphone doit être un nombre entier de 8 chiffres."), QMessageBox::Cancel);
        return; // Stop further execution
    }
    // Validate name, last name, and address fields using regular expressions
        QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ]+(?:\\s[a-zA-ZÀ-ÿ]+)?$"); // Pattern for names (allowing accented characters and a space)
        QRegularExpressionMatch nameMatch = nameRegex.match(ui->lineEditupdate_name->text());
        QRegularExpressionMatch lastnameMatch = nameRegex.match(ui->lineEditupdate_lastname->text());
        QRegularExpression addressRegex("^[a-zA-Z0-9\\s,'-]*$"); // Pattern for address (allowing alphanumeric characters, spaces, and common special characters)
        QRegularExpressionMatch addressMatch = addressRegex.match(ui->lineEditupdate_adress->text());

        if (!nameMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Nom invalide. Veuillez entrer un nom valide."), QMessageBox::Cancel);
            return; // Stop further execution
        }

        if (!lastnameMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Nom de famille invalide. Veuillez entrer un nom de famille valide."), QMessageBox::Cancel);
            return; // Stop further execution
        }

        if (!addressMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Adresse invalide. Veuillez entrer une adresse valide."), QMessageBox::Cancel);
            return; // Stop further execution
        }

    // Retrieve updated participant information
    int idp = ui->lineEditupdate_idp->text().toInt(); // Assuming ID is editable for modification
    QString name = ui->lineEditupdate_name->text();
    QString lastname = ui->lineEditupdate_lastname->text();
    QString adress = ui->lineEditupdate_adress->text();
    // Retrieve skill from combobox
    QString skill = ui->comboBoxupdate_role->currentText();

    // Retrieve role from radio buttons (assuming unchanged during modification)
    QString role;
    if (ui->radioButtonupdate_1->isChecked()) {
        role = ui->radioButtonupdate_1->text();
    } else if (ui->radioButtonupdate_2->isChecked()) {
        role = ui->radioButtonupdate_2->text();
    } // No need for the else block if role is not editable

    // Retrieve dates from date edits (assuming unchanged during modification)
    QDate dateStart = ui->dateEditupdate_1->date();
    QDate dateEnd = ui->dateEditupdate_2->date();
    QString datestart = dateStart.toString("yyyy-MM-dd");
    QString dateend = dateEnd.toString("yyyy-MM-dd");

    // Create a participant object with updated information
    participant etmp(idp, name, lastname, adress, tel, skill, role, datestart, dateend);

    // Call the modifier function to update the participant in the database
    bool test = etmp.modifier(idp,name,lastname,adress,tel,skill,role,datestart,dateend);

    if (test) {
        // Display success message and update displayed participant data (if applicable)
        ui->tableView->setModel(etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        ui->lineEditupdate_idp->clear(); // ID field
        ui->lineEditupdate_name->clear(); // Name field
        ui->lineEditupdate_lastname->clear(); // Last name field
        ui->lineEditupdate_adress->clear(); // Address field
        ui->lineEditupdate_tel->clear(); // Phone number field
        ui->comboBoxupdate_role->setCurrentIndex(0); // Set combobox to first item (skill)
        ui->radioButtonupdate_1->setChecked(false); // Uncheck role radio button 1
        ui->radioButtonupdate_2->setChecked(false); // Uncheck role radio button 2
        ui->dateEditupdate_1->setDate(QDate::currentDate()); // Set date edit to today's date
        ui->dateEditupdate_2->setDate(QDate::currentDate()); // Set date edit to today's date
        // Potentially update the displayed participant data in the table or other UI elements
        // based on your specific use case and data management approach
    } else {
        // Display error message
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("Modification non effectuée.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}


void MainWindow::on_search_clicked() {
    // Get the idp from the line edit
    int idp = ui->lineEditupdate_idp->text().toInt();

    // Call the recherche function to search for the participant with the given ID
    QSqlQueryModel *resultModel = etmp.recherche(idp);

    // Check if the result model has any rows (i.e., if participant with given ID is found)
    if (resultModel->rowCount() > 0) {
        // Retrieve the data from the model (assuming only one row is returned)
        //int foundIdp = resultModel->index(0, 0).data().toInt();
        QString foundName = resultModel->index(0, 1).data().toString();
        QString foundLastname = resultModel->index(0, 2).data().toString();
        QString foundAdress = resultModel->index(0, 3).data().toString();
        int foundTel = resultModel->index(0, 4).data().toInt();
        QString foundRole = resultModel->index(0, 5).data().toString();
        QString foundSkill = resultModel->index(0, 6).data().toString();
        QString foundDateStart = resultModel->index(0, 7).data().toString();
        QString foundDateEnd = resultModel->index(0, 8).data().toString();

        // Display the retrieved data in UI elements
       // ui->lineEdit_11->setText(QString::number(foundIdp)); // ID
        ui->lineEditupdate_name->setText(foundName); // Name
        ui->lineEditupdate_lastname->setText(foundLastname); // Last name
        ui->lineEditupdate_adress->setText(foundAdress); // Address
        ui->lineEditupdate_tel->setText(QString::number(foundTel)); // Phone number
        ui->comboBoxupdate_role->setCurrentText(foundRole); // Skill
        if (foundSkill == "autonome") {
            ui->radioButtonupdate_1->setChecked(true); // Set role radio buttons
        } else if (foundSkill == "ponctuel") {
            ui->radioButtonupdate_2->setChecked(true); // Set role radio buttons
        }
        ui->dateEditupdate_1->setDate(QDate::fromString(foundDateStart, "yyyy-MM-dd")); // Start date
        ui->dateEditupdate_1->setDate(QDate::fromString(foundDateEnd, "yyyy-MM-dd")); // End date

        // Display success message
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Participant trouvé."), QMessageBox::Cancel);
    } else {
        // Participant not found, display error message
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("Participant non trouvé."), QMessageBox::Cancel);
    }
}



