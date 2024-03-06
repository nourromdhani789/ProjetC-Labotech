#ifndef RESOURCE_H
#define RESOURCE_H
#include <QString>
#include <iostream>

#include <QSqlQuery>
#include <QSqlQueryModel>

using namespace std;

class Resource
{
private :
    int idr;
    int price;
    QString type;
    int alloc;
    int stock;
    int storage;
    QString date_exp;
public:

    /////////////////////////////////////getters and setters

    //getters
    int getidr();
    int getprice();
    QString gettype();
    int getalloc();
    int getstock();
    int getstorage();
    QString getdate_exp();

    //setters
    void setidr(int a);
    void setprice(int a);
    void settype(QString h);
    void setalloc(int a);
    void setstock(int a);
    void setstorage(int a);
    void setdate_exp(QString h);


    /////////////////////////////////////ctor and dtor

    Resource();
    Resource(int idr,int price,QString type,int alloc,int stock,int storage,QString date_exp);
    ~Resource();

    /////////////////////////////////////CRUD

    bool ajouter();
    QSqlQueryModel * afficher();
    bool modifier(int idr,int price,QString type,int alloc,int stock,int storage,QString date_exp);
    QSqlQueryModel * recherche(int idr);
    bool supprimer(int idr);
};

#endif // RESOURCE_H
