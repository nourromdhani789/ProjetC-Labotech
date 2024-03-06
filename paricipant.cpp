#include "paricipant.h"
#include <QDebug>
#include <QSqlError>

participant::participant(int idp,QString name,QString lastname,QString adress,int tel,QString skill,QString role,QString datestart,QString dateend)
{
    this->idp=idp;
    this->name=name;
    this->lastname=lastname;
    this->adress=adress;
    this->tel=tel;
    this->skill=skill;
    this->role=role;
    this->datestart=datestart;
    this->dateend=dateend;
}


bool participant::ajouter()
{
    QSqlQuery query;

    QString res = QString::number(idp);
    QString res2 = QString::number(tel);


    query.prepare("insert into participant(idp, name, lastname, adress, tel, skill, role, datestart, dateend)" "values(:idp, :name, :lastname, :adress, :tel, :skill, :role, :datestart, :dateend)");

    query.bindValue(":idp",res);
    query.bindValue(":name",name);
    query.bindValue(":lastname",lastname);
    query.bindValue(":adress",adress);
    query.bindValue(":tel",res2);
    query.bindValue(":skill",skill);
    query.bindValue(":role",role);
    query.bindValue(":datestart",datestart);
    query.bindValue(":dateend",dateend);

    return query.exec();

}

bool participant::supprimer(int idp)
{
    QSqlQuery query;
    QString res=QString::number(idp);

    query.prepare("delete from participant where idp= :idp");
    query.bindValue(":idp",res);

    return query.exec();
}

QSqlQueryModel * participant::afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from participant");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("idp"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("lastname"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("adress"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("skill"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("role"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("datestart"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("dateend"));

    return model;
}

bool participant::modifier(int idp,QString name,QString lastname,QString adress,int tel,QString skill,QString role,QString datestart,QString dateend)
{
    QSqlQuery query;


    query.prepare("update participant set name=:name, lastname=:lastname, adress=:adress,  tel=:tel, skill=:skill, role=:role, datestart=:datestart, dateend=:dateend  where idp=:idp");

    query.bindValue(":idp", idp);
    query.bindValue(":name", name);
    query.bindValue(":lastname", lastname);
    query.bindValue(":adress", adress);
    query.bindValue(":tel", tel);
    query.bindValue(":skill", skill);
    query.bindValue(":role", role);
    query.bindValue(":datestart", datestart);
    query.bindValue(":dateend", dateend);

    return query.exec();
}

QSqlQueryModel * participant::recherche(int idp)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM participant WHERE idp=:idp");
    query.bindValue(":idp", idp);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("idp"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("name"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("lastname"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("adress"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("tel"));
        model->setHeaderData(5, Qt::Horizontal,QObject::tr("skill"));
        model->setHeaderData(6, Qt::Horizontal,QObject::tr("role"));
        model->setHeaderData(7, Qt::Horizontal,QObject::tr("datestart"));
        model->setHeaderData(8, Qt::Horizontal,QObject::tr("dateend"));
    } else {
        // Query execution failed, handle error
        qDebug() << "Query execution failed:" << query.lastError().text();
    }

    return model;
}





