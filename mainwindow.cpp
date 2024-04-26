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

    ui->lineEdit_nom->setMaxLength(30);
    ui->lineEdit_prenom->setMaxLength(20);
    ui->lineEdit_adres->setMaxLength(30);
    ui->tab_employe->setModel(e.afficher());

    QRegularExpression rx3("[A-Z][a-z]*",
                           QRegularExpression::CaseInsensitiveOption);
    ui->lineEdit_prenom->setValidator(new QRegularExpressionValidator(rx3, this));
    ui->lineEdit_nom->setValidator(new QRegularExpressionValidator(rx3, this));
ui->path_picture->hide();
ui->path_picture_modifier->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_ajout_clicked()
{
    int id = ui->lineEdit_id->text().toInt();
    QString prenom = ui->lineEdit_prenom->text();
    QString nom = ui->lineEdit_nom->text();
    QString adress = ui->lineEdit_adres->text();
    int phone = ui->lineEdit_phone->text().toInt();
    QString role = ui->lineEdit_role->text();
    QString image=ui->path_picture->text();
    QString skills;
    if (ui->radioButton->isChecked())
        skills = ui->radioButton->text();
    else if (ui->radioButton_2->isChecked())
        skills = ui->radioButton_2->text();
    else {
        QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                              QObject::tr("Veuillez sélectionner une compétence."), QMessageBox::Ok);
        return;
    }

    QDate date_s = ui->dateEdit->date();
    QDate date_f = ui->dateEdit_2->date();
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
            ui->tab_employe->setModel(emp.afficher());
        } else {
            QMessageBox::warning(this, "Erreur d'ajout", "L'ajout de l'employé a échoué.");
        }
    }
}

void MainWindow::on_radioButton_ID_clicked()
{
    employee *emp = new employee();
    ui->tab_employe->setModel(emp->tri_ID());
}


void MainWindow::on_radioButton_NOM_clicked()
{
    employee *emp = new employee();
    ui->tab_employe->setModel(emp->tri_nom());

}


void MainWindow::on_pushButton_MODIF_clicked()
{
    int id = ui->lineEdit_MID->text().toInt();
    QString prenom = ui->lineEdit_MPRENOM->text();
    QString nom = ui->lineEdit_MNOM->text();
    QString adress = ui->lineEdit_MADRES->text();
    int phone = ui->lineEdit_MPHONE->text().toInt();
    QString role = ui->lineEdit_MROLE->text();
QString image=ui->path_picture_modifier->text();
    QString skills;
    if (ui->radioButton_5->isChecked())
        skills = ui->radioButton_5->text();
    else if (ui->radioButton_6->isChecked())
        skills = ui->radioButton_6->text();
    else {
        QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                              QObject::tr("Veuillez sélectionner une compétence."), QMessageBox::Ok);
        return;
    }

    QDate date_s = ui->dateEdit_MDATES->date();
    QDate date_f = ui->dateEdit_MDATEF->date();
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


void MainWindow::on_pushButton_RECHERCHE_clicked()
{

    employee Sp;
    Sp.setId(ui->lineEdit_MID->text().toInt());
       int selectedId = ui->lineEdit_MID->text().toInt();
    bool test=Sp.RechercheemployeeParID(Sp.getId());
    QMessageBox msgbox;

    if (test)
    {
        msgbox.setText("ID existe");
        ui->tab_employe->setModel(Sp.afficher());
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
          ui->lineEdit_MPRENOM->setText(prenom);
          ui->lineEdit_MNOM->setText(nom);
           ui->lineEdit_MADRES->setText(adresse);
             ui->lineEdit_MPHONE->setText(phone_string);
             ui->lineEdit_MROLE->setText(role);
             /*if (ui->radioButton->isChecked())
                 skills = ui->radioButton->text();
             else if (ui->radioButton_2->isChecked())
                 skills = ui->radioButton_2->text();*/
               ui->dateEdit_MDATES->setDate(start);
                ui->dateEdit_MDATES->setDate(end);
                QPixmap imagepath(image);
                        ui->show_picture_modifier->setPixmap(imagepath.scaled(ui->show_picture_modifier->size(), Qt::KeepAspectRatio));
                        ui->path_picture_modifier->setText(image);
                        ui->path_picture_modifier->hide();

          }


    }
    else
        msgbox.setText("ID n'existe pas");
    msgbox.exec();

}


void MainWindow::on_pushButton_SUPP_clicked()
{
    employee Sp;
    Sp.setId(ui->lineEdit_SUPP->text().toInt());
    bool test=Sp.supprimer(Sp.getId());
    QMessageBox msgbox;

    if (test)
    {
        msgbox.setText("Suppression avec succes");
        ui->tab_employe->setModel(Sp.afficher());
    }
    else
        msgbox.setText("failed");
    msgbox.exec();
    ui->lineEdit_SUPP->clear();

}


void MainWindow::on_pushButton_stats_clicked()
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


void MainWindow::on_pushButton_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->tab_employe->model()->rowCount();
    const int columnCount =ui->tab_employe->model()->columnCount();


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
        if (!ui->tab_employe->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tab_employe->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";
    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tab_employe->isColumnHidden(column)) {
                QString data = ui->tab_employe->model()->data(ui->tab_employe->model()->index(row, column)).toString().simplified();
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




void MainWindow::on_chercher_textChanged(const QString &text)
{

        QSqlQueryModel* searchModel = new QSqlQueryModel();
        searchModel->setQuery("SELECT * FROM employe WHERE id LIKE '%" + text + "%'");

        if (searchModel->rowCount() > 0) {
            // If the search result is not empty
            ui->tab_employe->setModel(searchModel);
        }
        if (searchModel->rowCount() == 0) {
            // If the search result is not empty
            ui->tab_employe->setModel(searchModel);
        }


}




void MainWindow::on_to_email_clicked()
{
    ui->tab_4->hide();
    ui->tab_5->show();
}

void MainWindow::on_retour_employerr_clicked()
{
    ui->tab_5->hide();
    ui->tab_4->show();
}

void MainWindow::on_envoyer_2_clicked()
{
    mailer::sendEmail(ui->destinataireEmail_2->text(), ui->objetEmail_2->text(), ui->bodyEmail_2->text());


}

void MainWindow::on_choose_picture_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.gif)");

        if (!imagePath.isEmpty()) {
            // Load the image using QPixmap
            QPixmap image(imagePath);

            // Update the QLabel with the image
            ui->show_picture->setPixmap(image.scaled(ui->show_picture->size(), Qt::KeepAspectRatio));
            ui->path_picture->setText(imagePath);
            ui->path_picture->hide();
        }
}

void MainWindow::on_choose_picture_modifier_clicked()
{
    QString imagePath = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.jpg *.bmp *.gif)");

        if (!imagePath.isEmpty()) {
            // Load the image using QPixmap
            QPixmap image(imagePath);

            // Update the QLabel with the image
            ui->show_picture_modifier->setPixmap(image.scaled(ui->show_picture->size(), Qt::KeepAspectRatio));
            ui->path_picture_modifier->setText(imagePath);
            ui->path_picture_modifier->hide();
        }
}

void MainWindow::on_tab_employe_activated(const QModelIndex &index)
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
            ui->show_picture_tableview->setPixmap(image.scaled(ui->show_picture_modifier->size(), Qt::KeepAspectRatio));
            ui->path_picture_tableview->setText(imagePath);
            ui->path_picture_tableview->hide();
        }

}
void MainWindow::test()
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
}
