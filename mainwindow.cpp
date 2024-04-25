#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "project.h"
#include "qr.h"
#include <QMessageBox>
#include <QDebug>
#include <QtCharts>
#include <QPieSeries>

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
    int num = ui->lineEdit_number_2->text().toInt();

    QSqlQueryModel *resultModel = P.rechercher(num);

    // Vérifier si le modèle de résultat a des lignes (c'est-à-dire si le projet avec le numéro donné est trouvé)
    if (resultModel->rowCount() > 0) {
        // Récupérer les données du modèle (en supposant qu'une seule ligne est renvoyée)
        QString foundTitle = resultModel->index(0, 1).data().toString();
        QString foundDescription = resultModel->index(0, 2).data().toString();
        QString foundBudget = resultModel->index(0, 3).data().toString();
        QString foundProgress = resultModel->index(0, 4).data().toString();

        // Afficher les données récupérées dans les éléments de l'interface utilisateur
        ui->lineEdit_title_2->setText(foundTitle);
        ui->lineEdit_description_2->setText(foundDescription);
        ui->lineEdit_budget_2->setText(foundBudget);
        ui->comboBox_2->setCurrentText(foundProgress);

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
void MainWindow::on_pushButton_5_clicked()
{
    // Assuming trier1() returns a QSqlQueryModel pointer
    Project p;
    QSqlQueryModel *model = p.trier();
    if (model) {
        // Update the table view with the sorted model
        // For example:
        ui->tableView->setModel(model);
    } else {
        QMessageBox::warning(this, "Erreur de tri", "Une erreur s'est produite lors du tri des clients.");
    }
}

void MainWindow::on_pushButton_6_clicked()
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

void MainWindow::on_pushButton_7_clicked()
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

void MainWindow::on_pushButton_8_clicked()
{
       QString num = ui->lineEdit->text(); // Assuming you have a line edit named lineEdit_cin for input

        Project c;
    Project *ptr_c = &c;

    if (!ptr_c->existance(num)) {
        // Récupérer les détails du client sélectionné dans le TableView
        QString cin = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 0)).toString();
        QString prenom = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 1)).toString();
        QString nom = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 2)).toString();
        QString adresse = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 3)).toString();
        QString num_tel = ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(), 4)).toString();
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
    QString ch=ui->lineEdit->text();

    //Project p(int a,QString b,QString c,QString d,QString e);
    Project p;
       if(ch !="")
       {
       ui->tableView->setModel(p.rechercherProject(ch));
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
