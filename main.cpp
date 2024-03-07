#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include <QMessageBox>
#include "connection.h"
#include "employee.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    bool test= c.createconnection();
    MainWindow w;
    employee newemployee(int id,QString n,QString p,QString a,int pe,QString r,QString s,QString ds,QString df);
    if(test)
       {
            w.show();
            QMessageBox::information(nullptr, QObject::tr("Database is open"));
            QObject::tr("connection successful. \n""click cancel to exit");
       }
    else
        QMessageBox::information(nullptr, QObject::tr("Database is not open"));

        QObject::tr("connection failed. \n""click cancel to exit");

    if (newemployee::ajouter()) {
        qDebug() << "L'employé a été ajouté avec succès à la base de données.";
    } else {
        qDebug() << "Erreur lors de l'ajout de l'employé.";
    }
    return a.exec();
}
