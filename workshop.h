#ifndef CONTRAT_H
#define CONTRAT_H


#include<QString>
#include<QSqlQueryModel>
#include <QTableView>
#include <QFileDialog>
#include <QCoreApplication>


class  Workshop
{
public:
    Workshop();
    Workshop(QString,QString,QString);
    Workshop(QString,QString,QString,QString);
    QString getidworkshop();
    QString getroom();
    QString getcapacity();
    QString getreservation();


    void setidworkshop(QString);
    void setroom(QString);
    void setcapacity(QString);
    void setreservation(QString);


    bool ajouter();
    QSqlQueryModel*afficher();
    bool supprimer(QString);
    bool modifier(QString,QString,QString,QString);
    void exporter(QTableView *table);
    QSqlQueryModel*search_rooms(QString room);
    QSqlQueryModel*search_capacity(QString capacity);
    QSqlQueryModel*search_reservation(QString capacity);
    QSqlQueryModel*search_rooms_capacity(QString room,QString capacity);
    QSqlQueryModel*search_rooms_reservation(QString room,QString reservation);
    QSqlQueryModel*search_capacity_reservation(QString capacity,QString reservation);
    QSqlQueryModel*search_with_all(QString room,QString capacity,QString reservation);


private:

    QString idworkshop,room,capacity,reservation;


};

#endif // Workshop
