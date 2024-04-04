#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "resource.h"
#include "connection.h"
#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QQuickItem>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSlice>
#include <QtCharts/QPieSeries>
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
    ui->tableView->setModel(R.afficher());
    createServicePieChart();
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
