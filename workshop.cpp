#include "workshop.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>
#include<QObject>
Workshop::Workshop()
{

}

Workshop:: Workshop(QString idworkshop,QString room,QString capacity,QString reservation)
{this->idworkshop=idworkshop; this->room=room; this->capacity=capacity;this->reservation=reservation;}
QString Workshop:: getidworkshop(){return idworkshop;}
QString Workshop:: getroom(){return room;}
QString Workshop:: getcapacity(){return capacity;}
QString Workshop:: getreservation(){return reservation;}
void Workshop:: setidworkshop(QString idworkshop){this->idworkshop=idworkshop;}
void Workshop::setroom(QString room){this->room=room;}
void Workshop:: setcapacity(QString capacity){this->capacity=capacity;}
void Workshop:: setreservation(QString reservation){this->reservation=reservation;}


bool Workshop::ajouter()
{

    QSqlQuery query;


          query.prepare("INSERT INTO workshop(idworkshop,room,capacity,reservation) "
                        "VALUES (:idworkshop ,:room ,:capacity ,:reservation)");
          query.bindValue(":idworkshop", idworkshop);
          query.bindValue(":room", room);
          query.bindValue(":capacity", capacity);
          query.bindValue(":reservation", reservation);

    return  query.exec();
}
bool Workshop::supprimer(QString idworkshop)
{
    QSqlQuery query;
    QString C=idworkshop;
          query.prepare("Delete from workshop WHERE idworkshop:=idworkshop");
          query.bindValue(":idworkshop", idworkshop);
         return  query.exec();

}
bool Workshop::modifier(QString room,QString capacity,QString reservation,QString idworkshop)
 {
     QSqlQuery query;
     query.prepare("UPDATE workshop SET room=:room, capacity=:capacity, reservation=:reservation WHERE idworkshop=:idworkshop");
     query.bindValue(":idworkshop",idworkshop);
     query.bindValue(":room", room);
     query.bindValue(":capacity",capacity);
     query.bindValue(":reservation",reservation);
     return query.exec();
 }
QSqlQueryModel* Workshop::afficher()
{
QSqlQueryModel* model=new QSqlQueryModel();

model->setQuery("SELECT* FROM workshop");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("idworkshop"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("room"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("capacity"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("reservation"));

return model;
}







