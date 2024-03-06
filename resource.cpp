#include "resource.h"
#include <QString>
#include <iostream>
#include <QDebug>
#include <QSqlError>

using namespace std;

////////////////////////////////////////////////Ctor & Dtor
Resource::Resource()
{
    //manque id;
    price=0;
    type="unkown";
    alloc=0;
    stock=1;
    storage=1;
    date_exp="0";
}


Resource::Resource(int idr,int price,QString type,int alloc,int stock,int storage,QString date_exp)
{

    this->idr=idr;
    this->price=price;
    this->type=type;
    this->alloc=alloc;
    this->stock=stock;
    this->storage=storage;
    this->date_exp=date_exp;

}

Resource::~Resource(){
    cout<<"Resource deleted"<<endl;
}
/////////////////////////////////////////////////Getters
int Resource::getidr(){
    return idr;
}
int Resource::getprice(){
    return price;
}
QString Resource::gettype(){
    return type;
}
int Resource::getalloc(){
    return alloc;
}
int Resource::getstock(){
    return stock;
}
int Resource::getstorage(){
    return storage;
}
QString Resource::getdate_exp(){
    return date_exp;
}
/////////////////////////////////////////////////Setters
void Resource::setidr(int a){
    idr=a;
}
void Resource::setprice(int a){
    price=a;
}
void Resource::settype(QString h){
    type=h;
}
void Resource::setalloc(int a){
    alloc=a;
}
void Resource::setstock(int a){
    stock=a;
}
void Resource::setstorage(int a){
    storage=a;
}
void Resource::setdate_exp(QString h){
    date_exp=h;
}

/////////////////////////////////////////////////CRUD

bool Resource::ajouter(){

    QSqlQuery query;

    QString res1 = QString::number(idr);
    QString res2 = QString::number(price);
    QString res3 = QString::number(alloc);
    QString res4 = QString::number(stock);
    QString res5 = QString::number(storage);

    query.prepare("insert into RESOURCE_DB ( idr, price, type, alloc, stock, storage, date_exp)" "values (:idr, :price, :type, :alloc, :stock, :storage, :date_exp)");

    query.bindValue(":idr",res1);
    query.bindValue(":price",res2);
    query.bindValue(":type",type);
    query.bindValue(":alloc",res3);
    query.bindValue(":stock",res4);
    query.bindValue(":storage",res5);
    query.bindValue(":date_exp",date_exp);
    return query.exec();
}


QSqlQueryModel * Resource::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("select * from RESOURCE_DB");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("idr"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("price"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("alloc"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("stock"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("storage"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("date_exp"));

        return model;
}

bool Resource::modifier(int idr,int price,QString type,int alloc,int stock,int storage,QString date_exp)
{

    QSqlQuery query;

    QString res1 = QString::number(idr);
    QString res2 = QString::number(price);
    QString res3 = QString::number(alloc);
    QString res4 = QString::number(stock);
    QString res5 = QString::number(storage);


    query.prepare("update RESOURCE_DB set idr=:idr, price=:price, type=:type, alloc=:alloc, stock=:stock,storage=:storage,date_exp=:date_exp where idr=:idr");

    query.bindValue(":idr",res1);
    query.bindValue(":price",res2);
    query.bindValue(":type",type);
    query.bindValue(":alloc",res3);
    query.bindValue(":stock",res4);
    query.bindValue(":storage",res5);
    query.bindValue(":date_exp",date_exp);

    return query.exec();
}

QSqlQueryModel * Resource::recherche(int idr)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM RESOURCE_DB WHERE idr=:idr");
    query.bindValue(":idr", idr);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("idr"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("price"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("type"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("alloc"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("stock"));
        model->setHeaderData(5, Qt::Horizontal,QObject::tr("storage"));
        model->setHeaderData(6, Qt::Horizontal,QObject::tr("date_exp"));

    } else {
        // Query execution failed, handle error
        qDebug() << "search execution failed:" << query.lastError().text();
    }

    return model;
}


bool Resource::supprimer(int idr){
    QSqlQuery query;
    QString res=QString::number(idr);
    query.prepare("Delete from RESOURCE_DB where idr = :idr");
    query.bindValue(":idr",res);

    return query.exec();
}

