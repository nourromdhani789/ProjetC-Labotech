#ifndef CONTRAT_H
#define CONTRAT_H


#include<QString>
#include<QSqlQueryModel>
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

private:

    QString idworkshop,room,capacity,reservation;


};

#endif // Workshop
