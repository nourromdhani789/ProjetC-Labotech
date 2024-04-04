#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paricipant.h"
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(P.afficher());
    ui->archive->setModel(P.afficherarchive());
    createServicePieChart();
    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
  //     ui->quickWidget->show();

        auto obj = ui->quickWidget->rootObject();
        connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
        connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

        emit setCenter(34.000, 9.000);
   // emit addMarker(34.000, 9.000);
        connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);




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
    participant P(idp,name,lastname,adress,tel,skill,role,datestart,dateend);

    // Add the participant to the database
    bool test=P.ajouter();

    if (test) {
        // Successfully added participant, update table view and clear input fields
        ui->tableView->setModel(P.afficher());
        QLayout* layout = ui->statistiqueLayout->layout();
                       if (layout) {
                           QLayoutItem* item;
                           while ((item = layout->takeAt(0)) != nullptr) {
                               delete item->widget(); // Clear the layout by deleting its widgets
                               delete item; // Delete the layout item
                           }
                       }
        createServicePieChart();
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);

        // Clear input fields
        ui->lineEditajouter_idp->clear();
        ui->lineEditajouter_name->clear();
        ui->lineEditajouter_lastname->clear();
        ui->lineEditajouter_adress->clear();
        ui->lineEditajouter_tel->clear();
        ui->comboBoxajouter_role->setCurrentIndex(0);
        ui->radioButtonajouter_1->setChecked(false);
        ui->radioButtonajouter_2->setChecked(false);
        ui->dateEditajouter_1->setDate(QDate());
        ui->dateEditajouter_2->setDate(QDate());
    } else {
        // Addition failed, display error message
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué.\nCliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}




void MainWindow::on_delete_2_clicked()
{
    int idp=ui->lineEditdelete_idp->text().toInt();
    bool test=P.supprimer(idp);

    if(test)
    {
        ui->tableView->setModel(P.afficher());
        ui->archive->setModel(P.afficherarchive());

        QLayout* layout = ui->statistiqueLayout->layout();
                       if (layout) {
                           QLayoutItem* item;
                           while ((item = layout->takeAt(0)) != nullptr) {
                               delete item->widget(); // Clear the layout by deleting its widgets
                               delete item; // Delete the layout item
                           }
                       }
        createServicePieChart();
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

    }

    // Check if phone number is a valid
    bool ok;
    int tel = ui->lineEditupdate_tel->text().toInt(&ok);
    if (!ok || ui->lineEditupdate_tel->text().length() != 8) {
        QMessageBox::critical(nullptr, QObject::tr("Erreur de saisie"),
                              QObject::tr("Le numéro de téléphone doit être un nombre entier de 8 chiffres."), QMessageBox::Cancel);
        return;
    }
    // Validate name, last name, and address
        QRegularExpression nameRegex("^[a-zA-ZÀ-ÿ]+(?:\\s[a-zA-ZÀ-ÿ]+)?$"); // Pattern for names
        QRegularExpressionMatch nameMatch = nameRegex.match(ui->lineEditupdate_name->text());
        QRegularExpressionMatch lastnameMatch = nameRegex.match(ui->lineEditupdate_lastname->text());
        QRegularExpression addressRegex("^[a-zA-Z0-9\\s,'-]*$"); // Pattern for address
        QRegularExpressionMatch addressMatch = addressRegex.match(ui->lineEditupdate_adress->text());

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
    }

    QDate dateStart = ui->dateEditupdate_1->date();
    QDate dateEnd = ui->dateEditupdate_2->date();
    QString datestart = dateStart.toString("yyyy-MM-dd");
    QString dateend = dateEnd.toString("yyyy-MM-dd");

    participant P(idp, name, lastname, adress, tel, skill, role, datestart, dateend);

    bool test = P.modifier(idp,name,lastname,adress,tel,skill,role,datestart,dateend);

    if (test) {
        ui->tableView->setModel(P.afficher());
        QLayout* layout = ui->statistiqueLayout->layout();
                       if (layout) {
                           QLayoutItem* item;
                           while ((item = layout->takeAt(0)) != nullptr) {
                               delete item->widget(); // Clear the layout by deleting its widgets
                               delete item; // Delete the layout item
                           }
                       }
        createServicePieChart();

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        ui->lineEditupdate_idp->clear();
        ui->lineEditupdate_name->clear();
        ui->lineEditupdate_lastname->clear();
        ui->lineEditupdate_adress->clear();
        ui->lineEditupdate_tel->clear();
        ui->comboBoxupdate_role->setCurrentIndex(0);
        ui->radioButtonupdate_1->setChecked(false);
        ui->radioButtonupdate_2->setChecked(false);
        ui->dateEditupdate_1->setDate(QDate());
        ui->dateEditupdate_2->setDate(QDate());

    } else {
        // Display error message
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                 QObject::tr("Modification non effectuée.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
    }
}


void MainWindow::on_search_clicked() {
    int idp = ui->lineEditupdate_idp->text().toInt();

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
        ui->lineEditupdate_name->setText(foundName);
        ui->lineEditupdate_lastname->setText(foundLastname);
        ui->lineEditupdate_adress->setText(foundAdress);
        ui->lineEditupdate_tel->setText(QString::number(foundTel));
        ui->comboBoxupdate_role->setCurrentText(foundRole);
        if (foundSkill == "autonome") {
            ui->radioButtonupdate_1->setChecked(true);
        } else if (foundSkill == "ponctuel") {
            ui->radioButtonupdate_2->setChecked(true); // Set role radio buttons
        }
        ui->dateEditupdate_1->setDate(QDate::fromString(foundDateStart, "yyyy-MM-dd"));
        ui->dateEditupdate_1->setDate(QDate::fromString(foundDateEnd, "yyyy-MM-dd"));

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
void MainWindow::on_sort_clicked()
{
    // Assuming trier1() returns a QSqlQueryModel pointer
    QSqlQueryModel *model = P.trier();
    if (model) {
        // Update the table view with the sorted model
        // For example:
        ui->tableView->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur de tri", "Une erreur s'est produite lors du tri des clients.");
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString ch=ui->lineEdit->text();


       {
       ui->tableView->setModel(P.rechercherpartici(ch));
       }

}
void MainWindow::on_sort_2_clicked()
{
    // Assuming trier1() returns a QSqlQueryModel pointer
    QSqlQueryModel *model = P.trierarch();
    if (model) {
        // Update the table view with the sorted model
        // For example:
        ui->archive->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur de tri", "Une erreur s'est produite lors du tri des clients.");
    }
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QString ch=ui->lineEdit_2->text();


       {
       ui->archive->setModel(P.rechercherarchive(ch));
       }

}

void MainWindow::on_close_clicked()
{
    this->close();
}

/*void MainWindow::on_PDF_clicked()
{

    P.pdf();
     QMessageBox::information(this, "Success", "pdf file  generer.");


}*/
void MainWindow::on_pdf_clicked()
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

void MainWindow::on_pdf_2_clicked()
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

void MainWindow::createServicePieChart() {
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
    ui->statistiqueLayout->addWidget(chartView);
}



void MainWindow::on_tabWidget_currentChanged(int index)
{
    // Show the QuickWidget only when switching to page 5
    if (index == 5) {
        ui->quickWidget->show();
    } else {
        // Hide the QuickWidget when switching away from page 5
        ui->quickWidget->hide();
    }
}

void MainWindow::on_pushButton_clicked()
{
    // Switch to the tab containing the QuickWidget
    ui->tabWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_2_clicked()
{
    // Switch to another tab (not containing the QuickWidget)
    ui->tabWidget->setCurrentIndex(0);
}

/*void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

}*/

void MainWindow::on_pushButton_3_clicked()
{
    // Retrieve information from UI elements
    QString name = ui->lineEdit_5->text();
    QString task = ui->lineEdit_3->text();
    QTime startTime = ui->timeEdit->time();
    QTime endTime = ui->timeEdit_2->time();
    QDate date = ui->calendarWidget->selectedDate(); // Retrieve selected date from calendar

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

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    // Clear the QTextEdit before displaying new data
    ui->textEdit->clear();

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
            ui->textEdit->append(QString("Name: %1\nTask: %2\nTime: %3\nDate: %4\n")
                                 .arg(name).arg(task).arg(time).arg(date));
        }
    } else {
        // Display error message if the query execution fails
        QMessageBox::critical(this, "Error", "Failed to fetch data from database.");
        qDebug() << "Database Error:" << query.lastError().text();
    }
}

void MainWindow::on_pushButton_4_clicked() {
    QString name = ui->lineEdit_7->text();

    QSqlQueryModel *resultModel = P.rechercheCalender(name);

    // Check if the result model has any rows
    if (resultModel->rowCount() > 0) {
        // Display the name in the QTextEdit
        ui->textEdit->clear(); // Clear existing content
        ui->textEdit->append("Name: " + name); // Append the name

        // Display the retrieved data in the QTextEdit
        for (int row = 0; row < resultModel->rowCount(); ++row) {
            QString task = resultModel->index(row, 1).data().toString();
            QString time = resultModel->index(row, 2).data().toString();
            QString date = resultModel->index(row, 3).data().toString();

            // Append the data to the QTextEdit
            ui->textEdit->append(QString("Task: %1\nTime: %2\nDate: %3\n")
                                         .arg(task).arg(time).arg(date));
        }
    } else {
        // No data found for the selected name, display a message
        QMessageBox::information(nullptr, QObject::tr("No Data"),
                                 QObject::tr("No calendar data found for the specified name."), QMessageBox::Cancel);
    }
}
void MainWindow::on_pushButton_5_clicked() {
    QString name = ui->lineEdit_7->text(); // Assuming lineEdit_7 contains the name to delete
    P.deleteCalendarData(name);
}




void MainWindow::on_reset_clicked()
{
    ui->lineEdit_7->clear();
    ui->textEdit->clear();
}

void MainWindow::on_restore_clicked()
{
    // Retrieve participant ID from LineEdit_2
    int idp = ui->lineEdit_2->text().toInt();

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
        ui->tableView->setModel(P.afficher());
        ui->archive->setModel(P.afficherarchive());
    } else {
        // Participant not found in archive
        QMessageBox::warning(this, "Warning", "Participant not found in archive.");
    }
}

