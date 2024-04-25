#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workshop.h"
#include<QFileDialog>


#include<QMessageBox>
#include<QTextDocument>
#include<QSqlQuery>
#include <QtPrintSupport/QPrinter>
#include <QTextStream>
#include <QSound>
#include<QMediaPlayer>
#include<QUrlQuery>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->afficher_Workshop_2->setModel(W.afficher());
    ui->tab1->setCurrentIndex(1);
    QString reservation = "yes";
    son=new QSound("C:/Bayou/media1.mp3");

    med = new QMediaPlayer(this);

        connect(med , &QMediaPlayer::positionChanged, [&](qint64 pos){

            ui->avancement_media->setValue(pos);

        });

        connect(med , &QMediaPlayer::durationChanged, [&](qint64 dur){

            ui->avancement_media->setMaximum(dur);

        });
}

MainWindow::~MainWindow()
{
    ui->afficher_Workshop_2->setModel(W.afficher());
    delete ui;

}


void MainWindow::on_Add_WorkShop_clicked()
{
    QString reservation;
    ui->yes_reservation_workshop->isChecked();
    if (ui->yes_reservation_workshop->isChecked()){
        reservation="yes";
    }
    else if ( ui->no_reservation_workshop->isChecked()) {
       reservation="no";
    } else {
        reservation="yes";
    };
    QString room=ui->Add_Rooms->currentText();
    QString capacity=ui->Add_Capacity->currentText();

    QString idworkshop= ui->IdWorKShop->text();
    ui->Add_Rooms->setCurrentIndex(1);
    ui->Add_Capacity->setCurrentIndex(1);

  Workshop W(idworkshop,room,capacity,reservation);

  bool test=W.ajouter();
  if(test)
{
ui->afficher_Workshop_2->setModel(W.afficher());
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
    QString reservation;
    ui->yes_reservation_workshop_edit->isChecked();
    if (ui->yes_reservation_workshop_edit->isChecked()){
        reservation="yes";
    }
    else if ( ui->no_reservation_workshop_edit->isChecked()) {
       reservation="no";
    } else {
        reservation="yes";
    };
    Workshop W(IdWorKShopEdit,room,capacity,reservation) ;
    bool test1=W.modifier(room,capacity,reservation,IdWorKShopEdit) ;

    if(test1){
        ui->afficher_Workshop_2->setModel(W.afficher());
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
               ui->afficher_Workshop_2->setModel(W.afficher());
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


void MainWindow::on_rechercherf_clicked()
{
    QString reservation;
    ui->yes_reservation_display->isChecked();
    if (ui->yes_reservation_display->isChecked()){
        reservation="yes";
    }
    else if ( ui->no_reservation_display->isChecked()) {
       reservation="no";
    } else {
        reservation="yes";
    };

    if (ui->checkBox_rooms_display->isChecked())
           { QString roomsnbr=ui->lineEdit_search_rooms->text();
               QSqlQueryModel *verif=W.search_rooms(roomsnbr);
               if (verif!=nullptr)
               {
                   ui->afficher_Workshop_2->setModel(verif);

               }
            }

         if (ui->checkBox_capacity_display->isChecked())
           { QString capacity=ui->lineEdit_search_capacity->text();
               QSqlQueryModel *verif=W.search_capacity(capacity);
               if (verif!=nullptr)
               {

                   ui->afficher_Workshop_2->setModel(verif);

               }
            }
          if (ui->checkBox_reservation_display->isChecked())
           {

               QSqlQueryModel *verif=W.search_reservation(reservation);
               if (verif!=nullptr)
               {

                   ui->afficher_Workshop_2->setModel(verif);

               }

            }
           if ((ui->checkBox_rooms_display->isChecked())&&(ui->checkBox_capacity_display->isChecked()))
           {
               QString rooms=ui->lineEdit_search_rooms->text();
               QString capacity=ui->lineEdit_search_capacity->text();

                           if (rooms!="")
                             {
                               if (capacity!="")
                                  {
                           QSqlQueryModel *verif=W.search_rooms_capacity(rooms,capacity);
                           if (verif!=nullptr)
                           {
                               ui->afficher_Workshop_2->setModel(verif);

                           }
                               } else
                                   QMessageBox::warning(this,"Error","Field rooms is Empty");
                           } else
                               QMessageBox::warning(this,"Error","Field capacity is Empty");
           }
          if ((ui->checkBox_rooms_display->isChecked())&&(ui->checkBox_reservation_display->isChecked()))
           {
               QString rooms=ui->lineEdit_search_rooms->text();
                           if (rooms!="")
                             {
                           QSqlQueryModel *verif=W.search_rooms_reservation(rooms,reservation);
                           if (verif!=nullptr)
                           {
                               ui->afficher_Workshop_2->setModel(verif);

                           }

                           } else
                               QMessageBox::warning(this,"Error","Field rooms is Empty");
           }
           if ((ui->checkBox_capacity_display->isChecked())&&(ui->checkBox_reservation_display->isChecked()))
           {
              QString capacity=ui->lineEdit_search_capacity->text();

                           if (capacity!="")
                             {
                           QSqlQueryModel *verif=W.search_capacity_reservation(capacity,reservation);
                           if (verif!=nullptr)
                           {
                               ui->afficher_Workshop_2->setModel(verif);

                           }

                           } else
                               QMessageBox::warning(this,"Error","Field capacity is Empty");
           }


        if ((ui->checkBox_rooms_display->isChecked())&&(ui->checkBox_capacity_display->isChecked())&&(ui->checkBox_reservation_display->isChecked()))
        {

            QString rooms=ui->lineEdit_search_rooms->text();
            QString capacity=ui->lineEdit_search_capacity->text();


                        if (rooms!="")
                          {
                            if (capacity!="")
                               {
                        QSqlQueryModel *verif=W.search_with_all(rooms,capacity,reservation);
                        if (verif!=nullptr)
                        {

                            ui->afficher_Workshop_2->setModel(verif);

                        }
                            } else
                                QMessageBox::warning(this,"Error","Field rooms is Empty");
                        } else
                            QMessageBox::warning(this,"Error","Field capacity is Empty");

        } //else QMessageBox::warning(this,"Error","Nothing is Checked");
}

void MainWindow::on_reafficherf_clicked()
{
    ui->afficher_Workshop_2->setModel(W.afficher());

}

void MainWindow::on_Statistics_clicked()
{

    statistics *stat=new statistics();
    stat->make();
    stat->show();
}

void MainWindow::on_ouvrir_media_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "ouvrir");

        if (filename.isEmpty())

        {

            return;

        }

        med->setMedia(QUrl::fromLocalFile(filename));

        med->setVolume(ui->volume_media->value());

        on_play_media_clicked();
}

void MainWindow::on_play_media_clicked()
{
    med->play();

}

void MainWindow::on_pause_media_clicked()
{
 med->pause();
}

void MainWindow::on_stop_media_clicked()
{
  med->stop();
}

void MainWindow::on_mute_media_clicked()
{
    if (ui->mute_media->text() == "Mute")

        {

            med->setMuted(true);

            ui->mute_media->setText("Unmute");

        }

        else {

            med->setMuted(false);

            ui->mute_media->setText("Mute");

        }
}

void MainWindow::on_volume_media_valueChanged(int value)
{
       med->setVolume(value);
}

void MainWindow::on_export2_2_clicked()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append("list_WorkShopes.pdf"); }

           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);

           QTextDocument doc;
           QSqlQuery q;
           q.prepare("SELECT * FROM workshop ");
           q.exec();
           QString pdf="<br> <h1  style='color:red'>       LISTE DES WorkShopes  <br></h1>\n <br> <table>  <tr>  <th> ID </th> <th> ROOMS </th> <th> Capacity </th> <th> Reservation  </th> </tr>" ;


           while ( q.next()) {

               pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"    </td>  <td>   " + q.value(1).toString() +"</td>  <td>" +q.value(2).toString() +"  "" " "</td>      <td>     "+q.value(3).toString()+"--------"+"</td> " ;

           }
           doc.setHtml(pdf);
           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);

}
