#include "mainwindow.h"
#include <QMessageBox>
#include "connexion.h"
#include <QApplication>
#include <QWidget>
#include <QLayout>
#include <QDebug>
#include <QTranslator>
#include <QSplashScreen>
#include <QTimer>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    Connection c;
        bool test=c.createconnect();
        MainWindow w;
        if(test)
        {w.show();
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful."
                                                 ), QMessageBox::Cancel);

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);



        return a.exec();
    }
