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
          query.prepare("DELETE FROM workshop WHERE idworkshop=:idworkshop");
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

void Workshop::exporter(QTableView *table)
{

    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                                    filters, &defaultFilter);
    QFile file(fileName);
    QAbstractItemModel *model =  table->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++)
        {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(";") << "\n";
        for (int i = 0; i < model->rowCount(); i++)
        {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++)
            {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(";") + "\n";
        }
        file.close();
    }
}

QSqlQueryModel * Workshop::search_rooms(QString room)
{
    QSqlQuery qry;
    qry.prepare("select * from workshop where room=:room");
    qry.bindValue(":room",room);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


   return model;


}

QSqlQueryModel * Workshop::search_capacity(QString capacity)
{
    QSqlQuery qry;
    qry.prepare("select * from workshop where capacity=:capacity");
    qry.bindValue(":capacity",capacity);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


   return model;


}

QSqlQueryModel * Workshop::search_reservation(QString reservation)
{
    QSqlQuery qry;
    qry.prepare("select * from workshop where reservation=:reservation");
    qry.bindValue(":reservation",reservation);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


   return model;


}
QSqlQueryModel * Workshop::search_rooms_capacity(QString room,QString capacity)
{
    QSqlQuery qry;
    qry.prepare("select * from workshop where room=:salaire and capacity=:capacity ");
    qry.bindValue(":room",room);
    qry.bindValue(":capacity",capacity);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


   return model;


}
QSqlQueryModel * Workshop::search_rooms_reservation(QString room,QString reservation)
{
    QSqlQuery qry;
    qry.prepare("select * from workshop where room=:room and reservation=:reservation ");
    qry.bindValue(":room",room);
    qry.bindValue(":reservation",reservation);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


   return model;


}
QSqlQueryModel * Workshop::search_capacity_reservation(QString capacity,QString reservation)
{
    QSqlQuery qry;
    qry.prepare("select * from workshop where capacity=:capacity and reservation=:reservation ");
    qry.bindValue(":capacity",capacity);
    qry.bindValue(":reservation",reservation);
    qry.exec();

    QSqlQueryModel *model= new QSqlQueryModel;
    model->setQuery(qry);


   return model;


}





QSqlQueryModel * Workshop::search_with_all(QString room,QString capacity,QString reservation)
{
   QSqlQuery *qry= new QSqlQuery();
   qry->prepare("select * from workshop where room=:room and capacity=:capacity and reservation=:reservation");
   qry->bindValue(":room",room);
   qry->bindValue(":capacity",capacity);
   qry->bindValue(":reservation",reservation);
   qry->exec();

      QSqlQueryModel *model = new QSqlQueryModel();
      model->setQuery(*qry);
       return model;

}






