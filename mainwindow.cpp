#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paricipant.h"
#include "employee.h"
#include "email.h"
#include "resource.h"
#include "project.h"
#include "qr.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QQuickItem>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <QVector>
#include <QPrinter>
#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QDateTime>
#include <QDate>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QLineEdit>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paricipant.h"
#include "employee.h"
#include "email.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QQuickItem>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <QVector>
#include <QPrinter>
#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPainter>
#include <QDateTime>
#include <QDate>
#include <QSortFilterProxyModel>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "email.h"
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QMessageBox>
#include <QRadioButton>
#include <QPushButton>
#include <QListWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts>
#include <iostream>
#include<fstream>
#include <string>
#include<QPropertyAnimation>
#include <QTextStream>
#include <QRegularExpressionValidator>
#include <QFile>
#include <QDataStream>
#include<QTextDocument>
#include<QtPrintSupport/QPrinter>
#include<QByteArray>
#include <QSqlQuery>

#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    ui->tableViewN->setModel(P.afficher());
    ui->archiveN->setModel(P.afficherarchive());
    createServicePieChartN();
    ui->tableView->setModel(R.afficher());
    createServicePieChart();
    //ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
  //     ui->quickWidget->show();

      //  auto obj = ui->quickWidget->rootObject();
      //  connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
        //connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

        //emit setCenter(34.000, 9.000);
   // emit addMarker(34.000, 9.000);
        connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);


        ui->lineEdit_nomE_2->setMaxLength(30);
            ui->lineEdit_prenomE_2->setMaxLength(20);
            ui->lineEdit_adresE_2->setMaxLength(30);
            ui->tab_employeE_2->setModel(e.afficher());

            QRegularExpression rx3("[A-Z][a-z]*",
                                   QRegularExpression::CaseInsensitiveOption);
            ui->lineEdit_prenomE_2->setValidator(new QRegularExpressionValidator(rx3, this));
            ui->lineEdit_nomE_2->setValidator(new QRegularExpressionValidator(rx3, this));
        ui->path_pictureE_2->hide();
        ui->path_picture_modifierE_2->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addN_clicked()
{
    // Check if all required fields are filled
    if (ui->lineEditajouter_idpN->text().isEmpty() || ui->lineEditajouter_nameN->text().isEmpty() || ui->lineEditajouter_lastnameN->text().isEmpty() ||
        ui->lineEditajouter_adressN->text().isEmpty() || ui->lineEditajouter_telN->text().isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Veuillez remplir tous les champs obligatoires."), QMessageBox::Cancel);
        return; // Stop further execution
    }

    // Check if phone number is a valid integer
    bool ok;
    int tel = ui->lineEditajouter_telN->text().toInt(&ok);
    if (!ok || ui->lineEditajouter_telN->text().length() != 8) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Le numéro de téléphone doit être un nombre entier de 8 chiffres."), QMessageBox::Cancel);
        return; // Stop further execution
    }
    // Validate name, last name, and address fields using regular expressions
        QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ]+(?:\\s[a-zA-ZÀ-ÿ]+)?$"); // Pattern for names (allowing accented characters and a space)
        QRegularExpressionMatch nameMatch = nameRegex.match(ui->lineEditajouter_nameN->text());
        QRegularExpressionMatch lastnameMatch = nameRegex.match(ui->lineEditajouter_lastnameN->text());
        QRegularExpression addressRegex("^[a-zA-Z0-9\\s,'-]*$"); // Pattern for address (allowing alphanumeric characters, spaces, and common special characters)
        QRegularExpressionMatch addressMatch = addressRegex.match(ui->lineEditajouter_adressN->text());

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
    int idp=ui->lineEditajouter_idpN->text().toInt();
    QString name=ui->lineEditajouter_nameN->text();
    QString lastname=ui->lineEditajouter_lastnameN->text();
    QString adress=ui->lineEditajouter_adressN->text();
    // Retrieve skill from combobox
    QString skill = ui->comboBoxajouter_role->currentText();

    // Retrieve role from radio buttons
    QString role;
    if(ui->radioButtonajouter_1N->isChecked())
        role = ui->radioButtonajouter_1N->text();
    else if(ui->radioButtonajouter_2N->isChecked())
        role = ui->radioButtonajouter_2N->text();
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
    participant P(idp,name,lastname,adress,tel,skill,role,datestart,dateend);

    // Add the participant to the database
    bool test=P.ajouter();

    if (test) {
        // Successfully added participant, update table view and clear input fields
        ui->tableViewN->setModel(P.afficher());
        QLayout* layout = ui->statistiqueLayoutN->layout();
                       if (layout) {
                           QLayoutItem* item;
                           while ((item = layout->takeAt(0)) != nullptr) {
                               delete item->widget(); // Clear the layout by deleting its widgets
                               delete item; // Delete the layout item
                           }
                       }
        createServicePieChartN();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

        // Clear input fields
        ui->lineEditajouter_idpN->clear();
        ui->lineEditajouter_nameN->clear();
        ui->lineEditajouter_lastnameN->clear();
        ui->lineEditajouter_adressN->clear();
        ui->lineEditajouter_telN->clear();
        ui->comboBoxajouter_role->setCurrentIndex(0);
        ui->radioButtonajouter_1N->setChecked(false);
        ui->radioButtonajouter_2N->setChecked(false);
        ui->dateEditajouter_1->setDate(QDate());
        ui->dateEditajouter_2->setDate(QDate());
    } else {
        // Addition failed, display error message
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}




void MainWindow::on_delete_2N_clicked()
{
    int idp=ui->lineEditdelete_idpN->text().toInt();
    bool test=P.supprimer(idp);

    if(test)
    {
        ui->tableViewN->setModel(P.afficher());
        ui->archiveN->setModel(P.afficherarchive());

        QLayout* layout = ui->statistiqueLayoutN->layout();
                       if (layout) {
                           QLayoutItem* item;
                           while ((item = layout->takeAt(0)) != nullptr) {
                               delete item->widget(); // Clear the layout by deleting its widgets
                               delete item; // Delete the layout item
                           }
                       }
        createServicePieChartN();
        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("supprimer effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEditdelete_idpN->clear(); // ID field


}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("supprimer failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }

void MainWindow::on_updateN_clicked() {
    // Check if all required fields are filled
    if (ui->lineEditupdate_idpN->text().isEmpty() || ui->lineEditupdate_nameN->text().isEmpty() || ui->lineEditupdate_lastnameN->text().isEmpty() ||
        ui->lineEditupdate_adressN->text().isEmpty() || ui->lineEditupdate_telN->text().isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Veuillez remplir tous les champs obligatoires."), QMessageBox::Cancel);

    }

    // Check if phone number is a valid
    bool ok;
    int tel = ui->lineEditupdate_telN->text().toInt(&ok);
    if (!ok || ui->lineEditupdate_telN->text().length() != 8) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Le numéro de téléphone doit être un nombre entier de 8 chiffres."), QMessageBox::Cancel);
        return;
    }
    // Validate name, last name, and address
        QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ]+(?:\\s[a-zA-ZÀ-ÿ]+)?$"); // Pattern for names
        QRegularExpressionMatch nameMatch = nameRegex.match(ui->lineEditupdate_nameN->text());
        QRegularExpressionMatch lastnameMatch = nameRegex.match(ui->lineEditupdate_lastnameN->text());
        QRegularExpression addressRegex("^[a-zA-Z0-9\\s,'-]*$"); // Pattern for address
        QRegularExpressionMatch addressMatch = addressRegex.match(ui->lineEditupdate_adressN->text());

        if (!nameMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Nom invalide. Veuillez entrer un nom valide."), QMessageBox::Cancel);
            return;
        }

        if (!lastnameMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Nom de famille invalide. Veuillez entrer un nom de famille valide."), QMessageBox::Cancel);
            return;
        }

        if (!addressMatch.hasMatch()) {
            QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                                  QObject::tr("Adresse invalide. Veuillez entrer une adresse valide."), QMessageBox::Cancel);
            return;
        }

    // Retrieve updated participant information
    int idp = ui->lineEditupdate_idpN->text().toInt(); // Assuming ID is editable for modification
    QString name = ui->lineEditupdate_nameN->text();
    QString lastname = ui->lineEditupdate_lastnameN->text();
    QString adress = ui->lineEditupdate_adressN->text();
    // Retrieve skill from combobox
    QString skill = ui->comboBoxupdate_roleN->currentText();

    // Retrieve role from radio buttons (assuming unchanged during modification)
    QString role;
    if (ui->radioButtonupdate_1N->isChecked()) {
        role = ui->radioButtonupdate_1N->text();
    } else if (ui->radioButtonupdate_2N->isChecked()) {
        role = ui->radioButtonupdate_2N->text();
    }

    QDate dateStart = ui->dateEditupdate_1N->date();
    QDate dateEnd = ui->dateEditupdate_2N->date();
    QString datestart = dateStart.toString("yyyy-MM-dd");
    QString dateend = dateEnd.toString("yyyy-MM-dd");

    participant P(idp, name, lastname, adress, tel, skill, role, datestart, dateend);

    bool test = P.modifier(idp,name,lastname,adress,tel,skill,role,datestart,dateend);

    if (test) {
        ui->tableViewN->setModel(P.afficher());
        QLayout* layout = ui->statistiqueLayoutN->layout();
                       if (layout) {
                           QLayoutItem* item;
                           while ((item = layout->takeAt(0)) != nullptr) {
                               delete item->widget(); // Clear the layout by deleting its widgets
                               delete item; // Delete the layout item
                           }
                       }
        createServicePieChartN();

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        ui->lineEditupdate_idpN->clear();
        ui->lineEditupdate_nameN->clear();
        ui->lineEditupdate_lastnameN->clear();
        ui->lineEditupdate_adressN->clear();
        ui->lineEditupdate_telN->clear();
        ui->comboBoxupdate_roleN->setCurrentIndex(0);
        ui->radioButtonupdate_1N->setChecked(false);
        ui->radioButtonupdate_2N->setChecked(false);
        ui->dateEditupdate_1N->setDate(QDate());
        ui->dateEditupdate_2N->setDate(QDate());

    } else {
        // Display error message
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("Modification non effectuée.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}


void MainWindow::on_searchN_clicked() {
    int idp = ui->lineEditupdate_idpN->text().toInt();

    QSqlQueryModel *resultModel = P.recherche(idp);

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
       // ui->lineEdit_11->setText(QString::number(foundIdp));
        ui->lineEditupdate_nameN->setText(foundName);
        ui->lineEditupdate_lastnameN->setText(foundLastname);
        ui->lineEditupdate_adressN->setText(foundAdress);
        ui->lineEditupdate_telN->setText(QString::number(foundTel));
        ui->comboBoxupdate_roleN->setCurrentText(foundRole);
        if (foundSkill == "autonome") {
            ui->radioButtonupdate_1N->setChecked(true);
        } else if (foundSkill == "ponctuel") {
            ui->radioButtonupdate_2N->setChecked(true); // Set role radio buttons
        }
        ui->dateEditupdate_1N->setDate(QDate::fromString(foundDateStart, "yyyy-MM-dd"));
        ui->dateEditupdate_1N->setDate(QDate::fromString(foundDateEnd, "yyyy-MM-dd"));

        // Display success message
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Participant trouvé."), QMessageBox::Cancel);
    } else {
        // Participant not found, display error message
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("Participant non trouvé."), QMessageBox::Cancel);
    }
}
//Tri
void MainWindow::on_sortN_clicked()
{
    // Assuming trier1() returns a QSqlQueryModel pointer
    QSqlQueryModel *model = P.trier();
    if (model) {
        // Update the table view with the sorted model
        // For example:
        ui->tableViewN->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur de tri", "Une erreur s'est produite lors du tri des clients.");
    }
}

void MainWindow::on_lineEditN_textChanged(const QString &arg1)
{
    QString ch=ui->lineEditN->text();


       {
       ui->tableViewN->setModel(P.rechercherpartici(ch));
       }

}
void MainWindow::on_sort_2N_clicked()
{
    // Assuming trier1() returns a QSqlQueryModel pointer
    QSqlQueryModel *model = P.trierarch();
    if (model) {
        // Update the table view with the sorted model
        // For example:
        ui->archiveN->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur de tri", "Une erreur s'est produite lors du tri des clients.");
    }
}

void MainWindow::on_lineEdit_2N_textChanged(const QString &arg1)
{
    QString ch=ui->lineEdit_2N->text();


       {
       ui->archiveN->setModel(P.rechercherarchive(ch));
       }

}

void MainWindow::on_closeN_clicked()
{
    this->close();
}

/*void MainWindow::on_PDF_clicked()
{

    P.pdf();
     QMessageBox::information(this, "Success", "pdf file  generer.");


}*/
void MainWindow::on_pdfN_clicked()
{
    QString filePath = "C:/Users/romdh/OneDrive/Documents/partici/ParticipantData/ParticipantData.pdf";
    QPdfWriter pdf(filePath);

    QPainter painter(&pdf); // Pass the QPdfWriter instance to the QPainter constructor

    // Check if the PDF painter is active
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Error", "Failed to paint on PDF.");
        return;
    }

    int i = 4000;
    painter.setPen(Qt::red);
    painter.setFont(QFont("Algerian", 30));
    painter.drawText(2000, 1400, "LIST OF PARTICIPANT ");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial Black", 15));
    painter.drawRect(100, 100, 9400, 2500);
    painter.drawRect(100, 3000, 9400, 500);

    painter.setFont(QFont("Cambria", 10));
    painter.drawText(500, 3300, "IDENTIFICATION");
    painter.drawText(2000, 3300, "NAME");
    painter.drawText(3000, 3300, "LASTNAME");
    painter.drawText(4000, 3300, "AdresS");
    painter.drawText(5000, 3300, "Téléphone");
    painter.drawText(6000, 3300, "Role");
    painter.drawText(7000, 3300, "Skill");
    painter.drawText(8000, 3300, "DateStart");

    painter.drawRect(100, 3000, 9400, 9000);

    QSqlQuery query;
    query.prepare("select * from participant");
    query.exec();
    while (query.next())
    {
        painter.drawText(500, i, query.value(0).toString());
        painter.drawText(2000, i, query.value(1).toString());
        painter.drawText(3000, i, query.value(2).toString());
        painter.drawText(4000, i, query.value(3).toString());
        painter.drawText(5000, i, query.value(4).toString());
        painter.drawText(6000, i, query.value(5).toString());
        painter.drawText(7000, i, query.value(6).toString());
        painter.drawText(8000, i, query.value(7).toString());

        i = i + 350;
    }

    // End painting on the PDF
    painter.end();

    // Display success message
    QMessageBox::information(this, "Success", "PDF file generated.");
}

void MainWindow::on_pdf_2N_clicked()
{
    QString filePath = "C:/Users/romdh/OneDrive/Documents/partici/ParticipantData/ParticipantDataarchive.pdf";
    QPdfWriter pdf(filePath);

    QPainter painter(&pdf); // Pass the QPdfWriter instance to the QPainter constructor

    // Check if the PDF painter is active
    if (!painter.isActive()) {
        QMessageBox::critical(this, "Error", "Failed to paint on PDF.");
        return;
    }

    int i = 4000;
    painter.setPen(Qt::darkMagenta); // Purple color
    painter.setFont(QFont("Algerian", 30));
    painter.drawText(2000, 1400, "PARTICIPANT ARCHIVE ");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial Black", 15));
    painter.drawRect(100, 100, 9400, 2500);
    painter.drawRect(100, 3000, 9400, 500);

    painter.setFont(QFont("Cambria", 10));
    painter.drawText(500, 3300, "IDENTIFICATION");
    painter.drawText(2000, 3300, "NAME");
    painter.drawText(3000, 3300, "LASTNAME");
    painter.drawText(4000, 3300, "AdresS");
    painter.drawText(5000, 3300, "Téléphone");
    painter.drawText(6000, 3300, "Role");
    painter.drawText(7000, 3300, "Skill");
    painter.drawText(8000, 3300, "DateStart");

    painter.drawRect(100, 3000, 9400, 9000);

    QSqlQuery query;
    query.prepare("select * from archive");
    query.exec();
    while (query.next())
    {
        painter.setPen(Qt::darkMagenta); // Purple color
        painter.drawText(500, i, query.value(0).toString());
        painter.drawText(2000, i, query.value(1).toString());
        painter.drawText(3000, i, query.value(2).toString());
        painter.drawText(4000, i, query.value(3).toString());
        painter.drawText(5000, i, query.value(4).toString());
        painter.drawText(6000, i, query.value(5).toString());
        painter.drawText(7000, i, query.value(6).toString());
        painter.drawText(8000, i, query.value(7).toString());

        i = i + 350;
    }

    // End painting on the PDF
    painter.end();

    // Display success message
    QMessageBox::information(this, "Success", "PDF file generated.");
}




























//***************************************

void MainWindow::createServicePieChartN() {
    // Retrieve data for role statistics
    QMap<QString, int> roleCounts;
    QSqlQuery query("SELECT skill, COUNT(*) AS totalParticipants FROM participant GROUP BY skill ORDER BY totalParticipants DESC");
    int count = 0;
    while (query.next()) {
        roleCounts[query.value(0).toString()] = query.value(1).toInt();
        count++;
    }

    // Create pie series
    QtCharts::QPieSeries *series = new QtCharts::QPieSeries();
    QStringList colors = {"#8E518D", "#C86FC9", "#F79AD3"}; // Black, Purple, White
    int colorIndex = 0;
    for (const auto &role : roleCounts.keys()) {
        QtCharts::QPieSlice *slice = series->append(role, roleCounts[role]);
        slice->setBrush(QColor(colors[colorIndex]));
        colorIndex = (colorIndex + 1) % colors.size(); // Rotate through colors
    }

    // Create chart and set the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Participants by Role %");

    // Set up animation
    QtCharts::QChart::AnimationOptions options = QtCharts::QChart::AllAnimations; // Choose your animation options
    chart->setAnimationOptions(options);

    // Create chart view and set the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add chart view to the layout
    ui->statistiqueLayoutN->addWidget(chartView);
}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    // Show the QuickWidget only when switching to page 5
    if (index == 5) {
        //ui->quickWidget->show();
    } else {
        // Hide the QuickWidget when switching away from page 5
       // ui->quickWidget->hide();
    }
}

void MainWindow::on_pushButton_3N_clicked()
{
    // Retrieve information from UI elements
    QString name = ui->lineEdit_5N->text();
    QString task = ui->lineEdit_3N->text();
    QTime startTime = ui->timeEditN->time();
    QTime endTime = ui->timeEdit_2N->time();
    QDate date = ui->calendarWidgetN->selectedDate(); // Retrieve selected date from calendar

    qDebug() << "Name:" << name;
    qDebug() << "Task:" << task;
    qDebug() << "Start Time:" << startTime.toString("HH:mm:ss");
    qDebug() << "End Time:" << endTime.toString("HH:mm:ss");
    qDebug() << "Date:" << date.toString("yyyy-MM-dd");

    // Check if all required fields are filled
    if (name.isEmpty() || task.isEmpty()) {
        QMessageBox::critical(this, "Error", "Please fill in all required fields.");
        return;
    }

    // Construct the combined start-end time string
    QString timeRange = startTime.toString("HH:mm:ss") + " - " + endTime.toString("HH:mm:ss");
    qDebug() << "Time Range:" << timeRange;

    // Create an SQL INSERT query to insert the information into the database table
    QSqlQuery query;
    query.prepare("INSERT INTO calender (name, task, time, datecal) "
                  "VALUES (:name, :task, :time, TO_DATE(:datecal, 'YYYY-MM-DD'))");

    query.bindValue(":name", name);
    query.bindValue(":task", task);
    query.bindValue(":time", timeRange); // Bind the combined start-end time string
    query.bindValue(":datecal", date.toString("yyyy-MM-dd")); // Bind the date in the appropriate format

    // Execute the query
    if (query.exec()) {
        QMessageBox::information(this, "Success", "Information added to database successfully.");

    } else {
        QMessageBox::critical(this, "Error", "Failed to add information to database.");
        qDebug() << "Database Error:" << query.lastError().text();
    }
}


void MainWindow::displayEventsOnCalendar() {
    // Query the database for events within a specific date range (e.g., current month)
    QDate currentDate = QDate::currentDate();
    QDate startDate = currentDate.addDays(-currentDate.day() + 1); // Start of the current month
    QDate endDate = startDate.addDays(startDate.daysInMonth() - 1); // End of the current month

    QSqlQuery query;
    query.prepare("SELECT DISTINCT datecal FROM calender WHERE datecal BETWEEN :startDate AND :endDate");
    query.bindValue(":startDate", startDate);
    query.bindValue(":endDate", endDate);

    if (query.exec()) {
        // Retrieve the dates with events
        QVector<QDate> eventDates;
        while (query.next()) {
            QDate eventDate = query.value(0).toDate();
            eventDates.append(eventDate);
        }

        // Highlight the dates with events on the calendar widget
        QTextCharFormat format;
        format.setBackground(Qt::yellow); // Set the background color to indicate events
        for (const QDate& date : eventDates) {
            ui->calendarWidgetN->setDateTextFormat(date, format);
        }
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
}

void MainWindow::on_pushButton_6N_clicked() {
    // Call the function to display events on the calendar widget
    displayEventsOnCalendar();
}

/*void MainWindow::hideEventsOnCalendar() {
    ui->calendarWidget->setHidden(true);
}

void MainWindow::on_pushButton_7N_clicked() {
    hideEventsOnCalendar();
}
*/

void MainWindow::on_calendarWidgetN_clicked(const QDate &date)
{
    // Clear the QTextEdit before displaying new data
    ui->textEditN->clear();

    // Construct the query to fetch data for the selected date
    QSqlQuery query;
    query.prepare("SELECT * FROM calender WHERE datecal = TO_DATE(:datecal, 'YYYY-MM-DD')");
    query.bindValue(":datecal", date.toString("yyyy-MM-dd"));

    // Print out the constructed query for debugging
    qDebug() << "Query:" << query.lastQuery();

    // Execute the query
    if (query.exec()) {
        // Iterate over the result set and populate the QTextEdit
        while (query.next()) {
            QString name = query.value(0).toString();
            QString task = query.value(1).toString();
            QString time = query.value(2).toString();
            QString date = query.value(3).toDate().toString("yyyy-MM-dd");

            // Append the fetched data to the QTextEdit
            ui->textEditN->append(QString("Name: %1\nTask: %2\nTime: %3\nDate: %4\n")
                                 .arg(name).arg(task).arg(time).arg(date));
        }
    } else {
        // Display error message if the query execution fails
        QMessageBox::critical(this, "Error", "Failed to fetch data from database.");
        qDebug() << "Database Error:" << query.lastError().text();
    }
}


void MainWindow::on_pushButton_4N_clicked() {
    QString name = ui->lineEdit_7N->text();

    QSqlQueryModel *resultModel = P.rechercheCalender(name);

    // Check if the result model has any rows
    if (resultModel->rowCount() > 0) {
        // Display the name in the QTextEdit
        ui->textEditN->clear(); // Clear existing content
        ui->textEditN->append("Name: " + name); // Append the name

        // Display the retrieved data in the QTextEdit
        for (int row = 0; row < resultModel->rowCount(); ++row) {
            QString task = resultModel->index(row, 1).data().toString();
            QString time = resultModel->index(row, 2).data().toString();
            QString date = resultModel->index(row, 3).data().toString();

            // Append the data to the QTextEdit
            ui->textEditN->append(QString("Task: %1\nTime: %2\nDate: %3\n")
                                         .arg(task).arg(time).arg(date));
        }
    } else {
        // No data found for the selected name, display a message
        QMessageBox::information(nullptr, QObject::tr("No Data"),
                                 QObject::tr("No calendar data found for the specified name."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_5N_clicked() {
    QString name = ui->lineEdit_7N->text(); // Assuming lineEdit_7 contains the name to delete
    P.deleteCalendarData(name);
}




void MainWindow::on_resetN_clicked()
{
    ui->lineEdit_7N->clear();
    ui->textEditN->clear();
}


void MainWindow::on_restoreN_clicked()
{
    // Retrieve participant ID from LineEdit_2
    int idp = ui->lineEdit_2N->text().toInt();

    // Query the archive table to find the participant data
    QSqlQuery query;
    query.prepare("SELECT * FROM archive WHERE idp = :idp");
    query.bindValue(":idp", idp);

    if(query.exec() && query.next()) {
        // Retrieve participant data from the archive
        QString name = query.value(1).toString();
        QString lastname = query.value(2).toString();
        QString adress = query.value(3).toString();
        int tel = query.value(4).toInt();
        QString skill = query.value(5).toString();
        QString role = query.value(6).toString();
        QString datestart = query.value(7).toString();
        QString dateend = query.value(8).toString();

        // Insert the participant data back into the participant table
        participant P(idp, name, lastname, adress, tel, skill, role, datestart, dateend);
        bool success = P.ajouter();

        if(success) {
            // Participant successfully restored, now delete from archive
            bool deleteSuccess = P.supprimerarchive(idp); // Declare deleteSuccess here
            if(deleteSuccess) {
                QMessageBox::information(this, "Success", "Participant restored from archive and deleted from archive table.");
            } else {
                QMessageBox::warning(this, "Warning", "Failed to delete participant from archive table.");
            }
        } else {
            QMessageBox::warning(this, "Warning", "Failed to restore participant from archive.");
        }

        // Update table views
        ui->tableViewN->setModel(P.afficher());
        ui->archiveN->setModel(P.afficherarchive());
    } else {
        // Participant not found in archive
        QMessageBox::warning(this, "Warning", "Participant not found in archive.");
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////IMEN///////////////////////////////////////////////////////////////////////////
///
void MainWindow::on_pushButton_ajoutE_2_clicked()
{
    int id = ui->lineEdit_idE_2->text().toInt();
    QString prenom = ui->lineEdit_prenomE_2->text();
    QString nom = ui->lineEdit_nomE_2->text();
    QString adress = ui->lineEdit_adresE_2->text();
    int phone = ui->lineEdit_phoneE_2->text().toInt();
    QString role = ui->lineEdit_roleE_2->text();
    QString image=ui->path_pictureE_2->text();
    QString skills;
    if (ui->radioButtonE_2->isChecked())
        skills = ui->radioButtonE_2->text();
    else if (ui->radioButton_2E_2->isChecked())
        skills = ui->radioButton_2E_2->text();
    else {
        QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                              QObject::tr("Veuillez sélectionner une compétence."), QMessageBox::Ok);
        return;
    }

    QDate date_s = ui->dateEditE_2->date();
    QDate date_f = ui->dateEdit_2E_2->date();
    int x = 0;
    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                              QObject::tr("Le nom ne peut pas être vide."), QMessageBox::Ok);
        x++;
    } else if (x == 0) {
        employee emp(id, prenom, nom, adress, phone, role, skills, date_s, date_f,image);
        bool success = emp.ajouter();
        if (success) {
            QMessageBox::information(this, "Ajout réussi", "L'employé a été ajouté avec succès.");
            // Rafraîchir l'affichage après l'ajout
            ui->tab_employeE_2->setModel(emp.afficher());
        } else {
            QMessageBox::warning(this, "Erreur d'ajout", "L'ajout de l'employé a échoué.");
        }
    }
}

void MainWindow::on_radioButton_IDE_2_clicked()
{
    employee *emp = new employee();
    ui->tab_employeE_2->setModel(emp->tri_ID());
}


void MainWindow::on_radioButton_NOME_2_clicked()
{
    employee *emp = new employee();
    ui->tab_employeE_2->setModel(emp->tri_nom());

}


void MainWindow::on_pushButton_MODIFE_2_clicked()
{
    int id = ui->lineEdit_MIDE_2->text().toInt();
    QString prenom = ui->lineEdit_MPRENOME_2->text();
    QString nom = ui->lineEdit_MNOME_2->text();
    QString adress = ui->lineEdit_MADRESE_2->text();
    int phone = ui->lineEdit_MPHONEE_2->text().toInt();
    QString role = ui->lineEdit_MROLEE_2->text();
QString image=ui->path_picture_modifierE_2->text();
    QString skills;
    if (ui->radioButton_5E_2->isChecked())
        skills = ui->radioButton_5E_2->text();
    else if (ui->radioButton_6E_2->isChecked())
        skills = ui->radioButton_6E_2->text();
    else {
        QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                              QObject::tr("Veuillez sélectionner une compétence."), QMessageBox::Ok);
        return;
    }

    QDate date_s = ui->dateEdit_MDATESE_2->date();
    QDate date_f = ui->dateEdit_MDATEFE_2->date();
    int x = 0;
    if (nom.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                              QObject::tr("Le nom ne peut pas être vide."), QMessageBox::Ok);
        x++;
    } else if (x == 0) {
        employee emp(id, prenom, nom, adress, phone, role, skills, date_s, date_f,image);
        bool toTest = emp.modifier();
        if (toTest) {
            QMessageBox::information(nullptr, QObject::tr("Modification d'employé"),
                                     QObject::tr("Employé modifié avec succès."), QMessageBox::Ok);
        }
    }
}


void MainWindow::on_pushButton_RECHERCHEE_2_clicked()
{

    employee Sp;
    Sp.setId(ui->lineEdit_MIDE_2->text().toInt());
       int selectedId = ui->lineEdit_MIDE_2->text().toInt();
    bool test=Sp.RechercheemployeeParID(Sp.getId());
    QMessageBox msgbox;

    if (test)
    {
        msgbox.setText("ID existe");
        ui->tab_employeE_2->setModel(Sp.afficher());
         QSqlQuery query;
         query.prepare("SELECT * FROM employe WHERE id = :id");
         query.bindValue(":id", selectedId);
          if (query.exec() && query.next()) {
              QString prenom = query.value(1).toString();
              QString  nom= query.value(2).toString();
              QString adresse = query.value(3).toString();
                  int phone = query.value(4).toInt();
        QString role = query.value(5).toString();
        QString skills = query.value(6).toString();
         QDate start = query.value(7).toDate();
          QDate end = query.value(8).toDate();
          QString image=query.value(9).toString();


          QString phone_string=QString::number(phone);
          ui->lineEdit_MPRENOME_2->setText(prenom);
          ui->lineEdit_MNOME_2->setText(nom);
           ui->lineEdit_MADRESE_2->setText(adresse);
             ui->lineEdit_MPHONEE_2->setText(phone_string);
             ui->lineEdit_MROLEE_2->setText(role);
             /*if (ui->radioButton->isChecked())
                 skills = ui->radioButton->text();
             else if (ui->radioButton_2->isChecked())
                 skills = ui->radioButton_2->text();*/
               ui->dateEdit_MDATESE_2->setDate(start);
                ui->dateEdit_MDATESE_2->setDate(end);
                QPixmap imagepath(image);
                        ui->show_picture_modifierE_2->setPixmap(imagepath.scaled(ui->show_picture_modifierE_2->size(), Qt::KeepAspectRatio));
                        ui->path_picture_modifierE_2->setText(image);
                        ui->path_picture_modifierE_2->hide();

          }


    }
    else
        msgbox.setText("ID n'existe pas");
    msgbox.exec();

}


void MainWindow::on_pushButton_SUPPE_2_clicked()
{
    employee Sp;
    Sp.setId(ui->lineEdit_SUPPE_2->text().toInt());
    bool test=Sp.supprimer(Sp.getId());
    QMessageBox msgbox;

    if (test)
    {
        msgbox.setText("Suppression avec succes");
        ui->tab_employeE_2->setModel(Sp.afficher());
    }
    else
        msgbox.setText("failed");
    msgbox.exec();
    ui->lineEdit_SUPPE_2->clear();

}


void MainWindow::on_pushButton_statsE_2_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from employe where id < 10 ");
    float tarif1=model->rowCount();
    model->setQuery("select * from employe where id  between 10 and 15 ");
    float tarif2=model->rowCount();
    model->setQuery("select * from employe where id >15 ");
    float tarif3=model->rowCount();
    float total=tarif1+tarif2+tarif3;
    QString a=QString("moins de 10 employe "+QString::number((tarif1*100)/total,'f',2)+"%" );
    QString b=QString("entre 10 et 15 employe "+QString::number((tarif2*100)/total,'f',2)+"%" );
    QString c=QString("+15 employe "+QString::number((tarif3*100)/total,'f',2)+"%" );
    QPieSeries *series = new QPieSeries();
    series->append(a,tarif1);
    series->append(b,tarif2);
    series->append(c,tarif3);
    if (tarif1!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( tarif2!=0)
    {
        // Add label, explode and define brush for 2nd slice
        QPieSlice *slice1 = series->slices().at(1);
        //slice1->setExploded();
        slice1->setLabelVisible();
    }
    if(tarif3!=0)
    {
        // Add labels to rest of slices
        QPieSlice *slice2 = series->slices().at(2);
        //slice1->setExploded();
        slice2->setLabelVisible();
    }
    // Create the chart widget
    QChart *chart = new QChart();
    // Add data to chart with title and hide legend
    chart->addSeries(series);
    chart->setTitle("Pourcentage Par employe :Nombre Des employes "+ QString::number(total));
    chart->legend()->hide();
    // Used to display the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();


    //end statistique
}


void MainWindow::on_pushButton_pdfE_2_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tab_employeE_2->model()->rowCount();
    const int columnCount =ui->tab_employeE_2->model()->columnCount();


    out <<  "<html>\n"
           "<head>\n"
           "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("eleve")
        <<  "</head>\n"
           "<body bgcolor= #fffde0  link=#fffde0>\n"

           "<h1 >Liste des EMPLOYE</h1> <br></br> <br> </br>  "

           "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#fffde0>";
    for (int column = 0; column < columnCount; column++)
        if (!ui->tab_employeE_2->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_employeE_2->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tab_employeE_2->isColumnHidden(column)) {
                QString data = ui->tab_employeE_2->model()->data(ui->tab_employeE_2->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
           "</body>\n"
           "</html>\n";



    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);


    //QTextDocument document;
    //document.setHtml(html);
    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("mypdffile.pdf");
    document->print(&printer);
}




void MainWindow::on_chercherE_2_textChanged(const QString &text)
{

        QSqlQueryModel* searchModel = new QSqlQueryModel();
        searchModel->setQuery("SELECT * FROM employe WHERE id LIKE '%" + text + "%'");

        if (searchModel->rowCount() > 0) {
            // If the search result is not empty
            ui->tab_employeE_2->setModel(searchModel);
        }
        if (searchModel->rowCount() == 0) {
            // If the search result is not empty
            ui->tab_employeE_2->setModel(searchModel);
        }


}




void MainWindow::on_to_emailE_2_clicked()
{
    ui->tab_4->hide();
    ui->tab_5->show();
}

void MainWindow::on_retour_employerrE_2_clicked()
{
    ui->tab_5->hide();
    ui->tab_4->show();
}

void MainWindow::on_envoyer_2E_2_clicked()
{
    mailer::sendEmail(ui->destinataireEmail_2E_2->text(), ui->objetEmail_2E_2->text(), ui->bodyEmail_2E_2->text());


}

void MainWindow::on_choose_pictureE_2_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.gif)");

        if (!imagePath.isEmpty()) {
            // Load the image using QPixmap
            QPixmap image(imagePath);

            // Update the QLabel with the image
            ui->show_pictureE_2->setPixmap(image.scaled(ui->show_pictureE_2->size(), Qt::KeepAspectRatio));
            ui->path_pictureE_2->setText(imagePath);
            ui->path_pictureE_2->hide();
        }
}

void MainWindow::on_choose_picture_modifierE_2_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.gif)");

        if (!imagePath.isEmpty()) {
            // Load the image using QPixmap
            QPixmap image(imagePath);

            // Update the QLabel with the image
            ui->show_picture_modifierE_2->setPixmap(image.scaled(ui->show_pictureE_2->size(), Qt::KeepAspectRatio));
            ui->path_picture_modifierE_2->setText(imagePath);
            ui->path_picture_modifierE_2->hide();
        }
}

void MainWindow::on_tab_employeE_2_activated(const QModelIndex &index)
{
      // Get the selected row index
        int row = index.row();

        // Get the ID from the selected index
        QModelIndex idIndex = index.sibling(row, 0);
        int selectedID = idIndex.data().toInt();

        // Execute a SQL query to retrieve the image path based on the selected ID
        QSqlQuery query;
        query.prepare("SELECT IMAGE FROM employe WHERE id = :id");
        query.bindValue(":id", selectedID);
        if (query.exec() && query.next()) {
            // Retrieve the image path from the query result
            QString imagePath = query.value(0).toString();

            // Load the image from the file path
            QPixmap image(imagePath);
            ui->show_picture_tableviewE_2->setPixmap(image.scaled(ui->show_picture_modifierE_2->size(), Qt::KeepAspectRatio));
            ui->path_picture_tableviewE_2->setText(imagePath);
            ui->path_picture_tableviewE_2->hide();
        }

}
/*void MainWindow::test()
{
         enteredID =a.read_from_arduino() ;
          QString ID=enteredID.left(enteredID.length()-2);
        qDebug() << ID;
    if (ID !=""){
         ui->lineEdit_id->setText(ID);
              QSqlQuery query;
              query.prepare("SELECT id FROM emplye WHERE id= :ID");
              query.bindValue(":ID", ID);
              if (query.exec() && query.next()) {
                  a.write_to_arduino("1");
                   ui->lineEdit_id->clear();
                   ID="";

              } else
              {
                  a.write_to_arduino("0");
                  ui->lineEdit_id->clear();
                  ID="";
              }}
}*/



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////BALIGH


void MainWindow::on_pushButton_3_clicked()
{
    int idr=ui->lineEdit_idr->text().toInt();
    int price=ui->lineEdit_price->text().toInt();
    QString type = ui->comboBox_type->currentText();
    int alloc=ui->lineEdit_alloc->text().toInt();
    int stock=ui->lineEdit_stock->text().toInt();
    int storage = ui->comboBox_storage->currentText().toInt();

    QString date_exp=ui->lineEdit_date_exp->text();



    Resource R(idr,price,type,alloc,stock,storage,date_exp);
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

void MainWindow::on_pushButton_tri_clicked()
{
    // Assuming trier1() returns a QSqlQueryModel pointer
        Resource R;
        QSqlQueryModel *model = R.trier();
        if (model) {
            // Update the table view with the sorted model
            // For example:
            ui->tableView->setModel(model);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                     QObject::tr("can't sort."), QMessageBox::Cancel);
        }

}




void MainWindow::on_lineEdit_rec_textChanged(const QString &arg1)
{
    QString ch=ui->lineEdit_rec->text();


    Resource R;
       if(ch !="")
       {
       ui->tableView->setModel(R.rechercherResource(ch));
       }

}

void MainWindow::createServicePieChart() {


}


void MainWindow::on_PDF_clicked()
{
    QString filePath = "C:/Users/LENOVO/Desktop/9raya/°2EME ESPRIT/projet c++/pdf extraction folder/ResourcesDataarchive.pdf";
        QPdfWriter pdf(filePath);

        QPainter painter(&pdf); // Pass the QPdfWriter instance to the QPainter constructor

        // Check if the PDF painter is active
        if (!painter.isActive()) {
            QMessageBox::critical(this, "Error", "Failed to paint on PDF.");
            return;
        }

        int i = 4000;
        painter.setPen(Qt::darkMagenta); // Purple color
        painter.setFont(QFont("Algerian", 30));
        painter.drawText(2000, 1400, "RESOURCE ARCHIVE ");

        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial Black", 15));
        painter.drawRect(100, 100, 9400, 2500);
        painter.drawRect(100, 3000, 9400, 500);

        painter.setFont(QFont("Cambria", 10));
        painter.drawText(500, 3300, "ID");
        painter.drawText(2000, 3300, "Price");
        painter.drawText(3000, 3300, "Type");
        painter.drawText(4000, 3300, "Allocation");
        painter.drawText(5000, 3300, "Stock");
        painter.drawText(6000, 3300, "Storage");
        painter.drawText(7000, 3300, "Date expiration");


        painter.drawRect(100, 3000, 9400, 9000);

        QSqlQuery query;
        query.prepare("select * from RESOURCE_DB");
        query.exec();
        while (query.next())
        {
            painter.setPen(Qt::darkMagenta); // Purple color
            painter.drawText(500, i, query.value(0).toString());
            painter.drawText(2000, i, query.value(1).toString());
            painter.drawText(3000, i, query.value(2).toString());
            painter.drawText(4000, i, query.value(3).toString());
            painter.drawText(5000, i, query.value(4).toString());
            painter.drawText(6000, i, query.value(5).toString());
            painter.drawText(7000, i, query.value(6).toString());


            i = i + 350;
        }

        // End painting on the PDF
        painter.end();

        // Display success message
        QMessageBox::information(this, "Success", "PDF file generated.");
}

///////////////////////////////////////////////////metier1
///
QStringList MainWindow::determineProjects(int teamID) {

    QSet<QString> projects;
    QMap<QString, int> totalStock; // Use a map to store total stock quantity for each resource name

    // Prepare a query to retrieve allocated resources for the specified team from the database
    QSqlQuery query;
    query.prepare("SELECT * FROM RESOURCE_DB WHERE Alloc = :teamID");
    query.bindValue(":teamID", teamID);
    if (!query.exec()) {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),QObject::tr("exec failed\n click cancel to exit."), QMessageBox::Cancel);
        return QStringList();
    }

    // Loop through the allocated resources and calculate the total stock quantity for each resource name
       while (query.next()) {
           QString resourceName = query.value("Type").toString();
           int quantity = query.value("Stock").toInt();

           // Add the stock quantity to the total for the current resource name
           totalStock[resourceName] += quantity;
       }

       // Determine projects based on the total stock quantity of each resource
       for (auto it = totalStock.constBegin(); it != totalStock.constEnd(); ++it) {
           const QString& resourceName = it.key();
           int totalQuantity = it.value();

           // Check if the necessary resources for each project are available
           if (resourceName == "plastic wheel" && totalQuantity >= 4) {
               projects.insert("RC Car");
           }
           if (resourceName == "drone parts" && totalQuantity >= 1) {
               projects.insert("mini drone");
           }
           if (resourceName == "motherboard" && totalQuantity >= 1) {
               projects.insert("controller");
           }

       }

       return projects.toList(); // Convert the set to a list and return
}


void MainWindow::on_metier1_clicked()
{
    // Get the team ID entered by the user
       int teamID = ui->lineEdit_teamID->text().toInt();

       // Determine projects that can be created based on allocated resources for the specified team
       QStringList projects = determineProjects(teamID);

       // Clear the existing items in the listWidget_projects
       ui->listWidget_projects->clear();

       // Display the projects in the listWidget_projects
       if (projects.isEmpty()) {
           ui->listWidget_projects->addItem("No projects can be created with the allocated resources for team " + QString::number(teamID));
       } else {
           for (const QString& project : projects) {
               ui->listWidget_projects->addItem("Project: " + project);
           }
       }
}

////////////////////////////////////////////////////////////////metier2
///
QList<QPair<int, QString>> MainWindow::determineLowResources() {
    QList<QPair<int, QString>> lowResources; // Use a list to store low quantity resources

    // Prepare a query to retrieve all resources from the database
    QSqlQuery query;
    query.exec("SELECT Type, SUM(Stock) AS total_stock FROM RESOURCE_DB GROUP BY Type");

    // Loop through all resources and determine low quantity resources
    while (query.next()) {
        QString resourceName = query.value("Type").toString();
        int quantity = query.value("total_stock").toInt();

        // Check if the quantity is low (less than or equal to 50)
        if (quantity <= 500) {
            lowResources.append(qMakePair(quantity, resourceName));
        }
    }

    // Sort the lowResources list by quantity in ascending order
    std::sort(lowResources.begin(), lowResources.end());

    // Return the sorted low quantity resources list
    return lowResources;
}

void MainWindow::updateLowResourcesList() {




    // Determine low quantity resources
    QList<QPair<int, QString>> lowResources = determineLowResources();

    // Clear the existing items in the listWidget_lowResources
    ui->listWidget_lowResources->clear();

    // Display the low quantity resources in the listWidget_lowResources
    if (lowResources.isEmpty()) {
        ui->listWidget_lowResources->addItem("No resources are running low.");
    } else {
        for (const auto& resource : lowResources) {
            int quantity = resource.first;
            const QString& resourceName = resource.second;

            // Create a new item with the resource name and quantity
            QListWidgetItem* item = new QListWidgetItem("Resource: " + resourceName + " (Quantity: " + QString::number(quantity) + ")");

            // Add the item to the listWidget_lowResources
            ui->listWidget_lowResources->addItem(item);
        }
    }
}

void MainWindow::on_PDF_2_clicked()
{
    // Effectuer les requêtes SQL pour récupérer les données
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery("SELECT COUNT(*) FROM RESOURCE_DB WHERE Storage = 1");
        int age = model->data(model->index(0, 0)).toInt();
        model->setQuery("SELECT COUNT(*) FROM RESOURCE_DB WHERE Storage = 2");
        int age1 = model->data(model->index(0, 0)).toInt();
        model->setQuery("SELECT COUNT(*) FROM RESOURCE_DB WHERE Storage = 3");
        int age2 = model->data(model->index(0, 0)).toInt();
        model->setQuery("SELECT COUNT(*) FROM RESOURCE_DB WHERE Storage = 4");
        int age3 = model->data(model->index(0, 0)).toInt();

        int total = age + age1+age2+age3;

        // Créer les étiquettes avec les pourcentages
        QString label1 = QString("storage1").arg(QString::number((age * 100) / total, 'f', 2));
        QString label2 = QString("storage2").arg(QString::number((age1 * 100) / total, 'f', 2));
        QString label3 = QString("storage3").arg(QString::number((age2 * 100) / total, 'f', 2));
        QString label4 = QString("storage4").arg(QString::number((age3 * 100) / total, 'f', 2));

        //QString label3 = QString("-25\n%1%").arg(QString::number((age2 * 100) / total, 'f', 2));

        // Créer la série de données pour le graphique
        QPieSeries *series = new QPieSeries();
        if (age > 0)
            series->append(label1, age);
        if (age1 > 0)
            series->append(label2, age1);
        if (age2 > 0)
            series->append(label3, age2);
        if (age3 > 0)
            series->append(label4, age3);

        // Créer le graphique en camembert
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("");
        chart->setBackgroundVisible(false);
        chart->legend()->setAlignment(Qt::AlignBottom);

        // Afficher le graphique dans QChartView
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setMinimumSize(681, 381); // Définir la taille minimale
        //chartView->setParent(ui->labelStat); // Définir le parent de QChartView
        chartView->show();
}

/*void MainWindow::on_checkButton_clicked()
{
    int idr = ui->lineEditcheck->text().toInt();

        // Create an instance of the Arduino class
        Arduino arduino;

        // Read sensor data to get the current digit appearing on the 7-segment display
        int currentDigit = arduino.getCurrentDisplayedDigit();

        // Update the database attribute storage_state with the current digit
        QString query = "UPDATE resource_db SET storage_state = '" + QString::number(currentDigit) + "' WHERE IDR = :idr";

        // Prepare the query
        QSqlQuery sqlQuery;
        sqlQuery.prepare(query);
        sqlQuery.bindValue(":idr", idr);

        // Execute the query using your database connection object
        bool success = sqlQuery.exec();

        if (success) {
            QMessageBox::information(this, "Success", "Storage state updated successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Failed to update storage state.");
        }
}
*/

///////////////AZOUZ////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////AZOUZ



void MainWindow::on_pushButton_showA_clicked()
{
    // Check if all required fields are filled
    if (ui->lineEdit_numberA->text().isEmpty() || ui->lineEdit_titleA->text().isEmpty() || ui->lineEdit_descriptionA->text().isEmpty() || ui->lineEdit_budgetA->text().isEmpty() || ui->comboBoxA->currentText().isEmpty())
    {QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),QObject::tr("Veuillez remplir tous les champs obligatoires."), QMessageBox::Cancel);return;    }
    int num=ui->lineEdit_numberA->text().toInt();
    QString title=ui->lineEdit_titleA->text();
    QString description=ui->lineEdit_descriptionA->text();
    QString budget=ui->lineEdit_budgetA->text();
    QString progress=ui->comboBoxA->currentText();
    Project P(num,title,description,budget,progress);
    bool test=Pr.ajouter();

    if(test)
    {
        ui->tableViewA->setModel(P.afficher());
        ui->lineEdit_numberA->clear();
        ui->lineEdit_titleA->clear();
        ui->lineEdit_descriptionA->clear();
        ui->lineEdit_budgetA->clear();
        Project Pr(num,title,description,budget,progress);
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Ajout effectué\n""Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Ajout non effectué\n""Click Cancel to exit"),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_2A_clicked()
{
    int num=ui->lineEdit_number_3A->text().toInt();
    bool test=Pr.supprimer(num);
    if(test)
    {
        ui->tableViewA->setModel(P.afficher());
        ui->lineEdit_number_3A->clear();
        QMessageBox::information(nullptr,QObject::tr("OK"),QObject::tr("Suppression effectué\n""Click Cancel to exit"),QMessageBox::Cancel);
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),QObject::tr("Suppression non effectué\n""Click Cancel to exit"),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_show_2A_clicked()
{
    int num = ui->lineEdit_number_2A->text().toInt();
        QString title = ui->lineEdit_title_2A->text();
        QString description = ui->lineEdit_description_2A->text();
        QString budget = ui->lineEdit_budget_2A->text();
        QString progress = ui->comboBox_2A->currentText();

        bool test = Pr.modifier(num, title, description, budget, progress);

        if(test)
        {
            ui->tableViewA->setModel(P.afficher());
            QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Mise à jour effectuée\n""Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Mise à jour non effectuée\n""Cliquez sur Annuler pour quitter"), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_3A_clicked()
{
    ui->tableViewA->setModel(Pr.afficher());
}


void MainWindow::on_pushButtonA_clicked()
{
    int num = ui->lineEdit_number_2A->text().toInt();

    QSqlQueryModel *resultModel = Pr.rechercher(num);

    // Vérifier si le modèle de résultat a des lignes (c'est-à-dire si le projet avec le numéro donné est trouvé)
    if (resultModel->rowCount() > 0) {
        // Récupérer les données du modèle (en supposant qu'une seule ligne est renvoyée)
        QString foundTitle = resultModel->index(0, 1).data().toString();
        QString foundDescription = resultModel->index(0, 2).data().toString();
        QString foundBudget = resultModel->index(0, 3).data().toString();
        QString foundProgress = resultModel->index(0, 4).data().toString();

        // Afficher les données récupérées dans les éléments de l'interface utilisateur
        ui->lineEdit_title_2A->setText(foundTitle);
        ui->lineEdit_description_2A->setText(foundDescription);
        ui->lineEdit_budget_2A->setText(foundBudget);
        ui->comboBox_2A->setCurrentText(foundProgress);

        // Afficher un message de réussite
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Projet trouvé."), QMessageBox::Cancel);
    } else {
        // Projet non trouvé, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("Projet non trouvé."), QMessageBox::Cancel);
    }
}

//Tri
void MainWindow::on_pushButton_5A_clicked()
{
    // Assuming trier1() returns a QSqlQueryModel pointer
    Project pr;
    QSqlQueryModel *model = pr.trier();
    if (model) {
        // Update the table view with the sorted model
        // For example:
        ui->tableViewA->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur de tri", "Une erreur s'est produite lors du tri des clients.");
    }
}

void MainWindow::on_pushButton_6A_clicked()
{
    // Effectuer les requêtes SQL pour récupérer les données
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT COUNT(*) FROM project WHERE progress = 'finished'");
    int age = model->data(model->index(0, 0)).toInt();
    model->setQuery("SELECT COUNT(*) FROM project WHERE progress = 'in progress'");
    int age1 = model->data(model->index(0, 0)).toInt();
    /*model->setQuery("SELECT COUNT(*) FROM client WHERE age  <25");
    int age2 = model->data(model->index(0, 0)).toInt();*/
    int total = age + age1;

    // Créer les étiquettes avec les pourcentages
    QString label1 = QString("finished").arg(QString::number((age * 100) / total, 'f', 2));
    QString label2 = QString("in progress").arg(QString::number((age1 * 100) / total, 'f', 2));
    //QString label3 = QString("-25\n%1%").arg(QString::number((age2 * 100) / total, 'f', 2));

    // Créer la série de données pour le graphique
    QPieSeries *series = new QPieSeries();
    if (age > 0)
        series->append(label1, age);
    if (age1 > 0)
        series->append(label2, age1);
    /*if (age2 > 0)
        series->append(label3, age2);*/

    // Créer le graphique en camembert
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->setBackgroundVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // Afficher le graphique dans QChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(681, 381); // Définir la taille minimale
    //chartView->setParent(ui->labelStat); // Définir le parent de QChartView
    chartView->show();
}

void MainWindow::on_pushButton_7A_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le PDF", "", "PDF (*.pdf)");

    if (!filePath.isEmpty()) {
        QPdfWriter pdf(filePath);
        pdf.setPageSize(QPageSize(QPageSize::A4));

        QPainter painter(&pdf);
        const QImage image(":/new/icons/icons/logo.png");
        const QPoint imageCoordinates(155, 0);
        int width1 = 1600;
        int height1 = 1600;
        QImage img = image.scaled(width1, height1);

        // Dessiner les éléments communs aux deux pages
        painter.drawImage(imageCoordinates, img);
        painter.setFont(QFont("Montserrat SemiBold", 11));
        QDate cd = QDate::currentDate();
        painter.drawText(8400, 250, cd.toString("Tunis"));
        painter.drawText(8100, 500, cd.toString("dd/MM/yyyy"));
        painter.setFont(QFont("Montserrat SemiBold", 25));
        painter.drawText(3000, 2700, "List of Projects");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Time New Roman", 15));
        painter.drawRect(100, 3300, 9400, 500);
        painter.setFont(QFont("Montserrat SemiBold", 10));
        painter.drawText(500, 3600, "num");
        painter.drawText(2000, 3600, "title");
        painter.drawText(3300, 3600, "description");
        painter.drawText(4500, 3600, "budget");
        painter.drawText(5500, 3600, "progress");
        /*painter.drawText(6600, 3600, "num_tel");
        painter.drawText(8000, 3600, "age");*/
        painter.setFont(QFont("Montserrat", 10));
        painter.drawRect(100, 3300, 9400, 9000);

        // Boucle pour parcourir les résultats de la requête
        QSqlQuery query;
        query.prepare("select * from project");
        query.exec();

        int y = 4300;
        int spacing = 500; // Espacement vertical entre chaque ligne de données
        int i = 4100;

        while (query.next()) {
            // Vérifier si l'ajout du client actuel dépasse la limite de la page
            if (y > pdf.height() - 100) {
                pdf.newPage(); // Ajouter une nouvelle page
                y = 200; // Réinitialiser la position verticale
                i = 4100; // Réinitialiser la position horizontale

                // Dessiner les éléments communs aux deux pages
                painter.drawImage(imageCoordinates, img);
                painter.setFont(QFont("Montserrat SemiBold", 11));
                QDate cd = QDate::currentDate();
                painter.drawText(8400, 250, cd.toString("Tunis"));
                painter.drawText(8100, 500, cd.toString("dd/MM/yyyy"));
                painter.setFont(QFont("Montserrat SemiBold", 25));
                painter.drawText(3000, 2700, "Liste des Client");
                painter.setPen(Qt::black);
                painter.setFont(QFont("Time New Roman", 15));
                painter.drawRect(100, 3300, 9400, 500);
                painter.setFont(QFont("Montserrat SemiBold", 10));
                painter.drawText(500, 3600, "num");
                /*painter.drawText(2000, 3600, "prenom");
                painter.drawText(3300, 3600, "nom");
                painter.drawText(4500, 3600, "adresse");
                painter.drawText(5500, 3600, "email");
                painter.drawText(6600, 3600, "num_tel");
                painter.drawText(8000, 3600, "age");*/
                painter.setFont(QFont("Montserrat", 10));
                painter.drawRect(100, 3300, 9400, 9000);
            }

            // Affichage des données du client
            painter.drawLine(100, y, 9490, y);
            painter.drawText(500, i, query.value(0).toString());
            painter.drawText(2000, i, query.value(1).toString());
            painter.drawText(3300, i, query.value(2).toString());
            painter.drawText(4500, i, query.value(3).toString());
            painter.drawText(5500, i, query.value(4).toString());
            /*painter.drawText(6600, i, query.value(5).toString());
            painter.drawText(8000, i, query.value(6).toString());*/

            y += spacing;
            i += spacing;
        }

        QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
            QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_8A_clicked()
{
       QString num = ui->lineEditA->text(); // Assuming you have a line edit named lineEdit_cin for input

        Project c;
    Project *ptr_c = &c;

    if (!ptr_c->existance(num)) {
        // Récupérer les détails du client sélectionné dans le TableView
        QString cin = ui->tableViewA->model()->data(ui->tableViewA->model()->index(ui->tableViewA->currentIndex().row(), 0)).toString();
        QString prenom = ui->tableViewA->model()->data(ui->tableViewA->model()->index(ui->tableViewA->currentIndex().row(), 1)).toString();
        QString nom = ui->tableViewA->model()->data(ui->tableViewA->model()->index(ui->tableViewA->currentIndex().row(), 2)).toString();
        QString adresse = ui->tableViewA->model()->data(ui->tableViewA->model()->index(ui->tableViewA->currentIndex().row(), 3)).toString();
        QString num_tel = ui->tableViewA->model()->data(ui->tableViewA->model()->index(ui->tableViewA->currentIndex().row(), 4)).toString();
        /*QString email = ui->tabfour->model()->data(ui->tabfour->model()->index(ui->tabfour->currentIndex().row(), 5)).toString();
        QString age = ui->tabfour->model()->data(ui->tabfour->model()->index(ui->tabfour->currentIndex().row(), 6)).toString();*/

        // Construire le texte à encoder dans le code QR
        //QString clientDetails = "Client details: " + cin + " " + prenom + " " + nom + " " + adresse + " " + num_tel + " " + email + " " + age;
        QString clientDetails = "Project details: " + cin + " " + prenom + " " + nom + " " + adresse + " " + num_tel;

        // Générer le code QR à partir des détails du client
        using namespace qrcodegen;
        QrCode qr = QrCode::encodeText(clientDetails.toUtf8().data(), QrCode::Ecc::MEDIUM);
        qint32 qrSize = qr.getSize();
        QImage qrImage(qrSize, qrSize, QImage::Format_RGB32);
        QRgb black = qRgb(0, 0, 0);
        QRgb white = qRgb(255, 255, 255);
        for (int y = 0; y < qrSize; ++y) {
            for (int x = 0; x < qrSize; ++x) {
                qrImage.setPixel(x, y, qr.getModule(x, y) ? black : white);
            }
        }

        // Afficher le code QR dans une boîte de dialogue
        QMessageBox qrDialog;
        qrDialog.setWindowTitle("QR Code");
        qrDialog.setIconPixmap(QPixmap::fromImage(qrImage.scaled(256, 256, Qt::KeepAspectRatio, Qt::FastTransformation), Qt::MonoOnly));
        qrDialog.exec();
    }
    else
    {
         QMessageBox::warning(this, "Champ invalide", "does not exist.");
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString ch=ui->lineEditA->text();

    //Project p(int a,QString b,QString c,QString d,QString e);
    Project pr;
       if(ch !="")
       {
       ui->tableViewA->setModel(pr.rechercherProject(ch));
       }

}

/*void MainWindow::on_pushButton_9_clicked()
{
    QString ch=ui->lineEdit->text();

    //Project p(int a,QString b,QString c,QString d,QString e);
    Project p;
       if(ch !="")
       {
       ui->tableView->setModel(p.rechercherProject(ch));
       }
}*/



////////////////////////////////MENU//////////////////////////////////MENU////////////////////////////////////////////////
void MainWindow::on_pushButton_15_clicked()
{
    ui->tab1->hide();
   ui->tabWidget_affiche->show();
   ui->tabWidget->hide();
   ui->tabWidget_2->hide();
}

void MainWindow::on_pushButton_14_clicked()
{
    ui->tab1->hide();
    ui->tabWidget_affiche->hide();
    ui->tabWidget->show();
    ui->tabWidget_2->hide();
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->tab1->show();
    ui->tabWidget_affiche->hide();
    ui->tabWidget->hide();
    ui->tabWidget_2->hide();
}

void MainWindow::on_pushButton_16_clicked()
{
    ui->tab1->hide();
    ui->tabWidget_affiche->hide();
    ui->tabWidget->hide();
    ui->tabWidget_2->show();
}
