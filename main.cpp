#include "mainwindow.h"
#include "mainwindow.h"
#include <connection.h>
#include <QApplication>
#include <QMessageBox>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connexion c;
    bool test =c.createconnect();
      MainWindow w;
    if(test){  w.show();

        QMessageBox::information(nullptr, QObject::tr("Base de données ouverte"),
                                 QObject::tr("Connexion réussie\n"
                                             "Cliquez sur Cancel pour quitter"),
                                 QMessageBox::Cancel);

    }
    else {

        QMessageBox::information(nullptr,QObject::tr("base de données n'est pas ouvert "),
                       QObject::tr("la connexion a échoué\n "
                                   "Cliquez sur Cancel pour quitter"),QMessageBox::Cancel);
    }

    return a.exec();
}
