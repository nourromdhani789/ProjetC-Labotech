#ifndef PARTICIPANT_H
#define PARTICIPANT_H
#include <QString>
#include <iostream>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>

using namespace std;

class participant
{ 


    int idp;
    QString name;
    QString lastname;
    QString adress;
    int tel;
    QString skill;
    QString role;
    QString datestart;
    QString dateend;

public:

    //constructeur
    participant(){}
    participant(int,QString,QString,QString,int,QString,QString,QString,QString);

    //setters
    void setidp(int idp){this->idp=idp;}
    void setname(QString n){name=n;}
    void setlastname(QString ln){lastname=ln;}
    void setadress(QString a){adress=a;}
    void settel(int t){tel=t;}
    void setskill(QString s){skill=s;}
    void setrole(QString r){role=r;}
    void setdatestart(QString ds){datestart=ds;}
    void setdateend(QString de){dateend=de;}

    //getters
    int getidp(){return idp;}
    QString getname(){return name;}
    QString getlastname(){return lastname;}
    QString getadress(){return adress;}
    int gettel(){return tel;}
    QString getskill(){return skill;}
    QString getrole(){return role;}
    QString getdatestart(){return datestart;}
    QString getdateend(){return dateend;}

   //fonctionnalites de base realatives
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,int,QString,QString,QString,QString);
    QSqlQueryModel * recherche(int);
};

#endif // PARTICIPANT_H
