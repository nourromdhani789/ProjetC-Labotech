#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QSqlQueryModel>
class employee
{
    QString nom,prenom,adress,role,skills,image;
    QDate date_s,date_f;
    int id,phone;
public:
    employee(){}
    employee(int, QString , QString , QString , int , QString , QString , QDate , QDate ,QString);


    int getId();
    QString getNom();
    QString getPrenom();
    QString getAdress();
    int getPhone();
    QString getRole();
    QString getSkill();
    QDate getDate_s();
    QDate getDate_f();
    QString getImage();
    void setId(int);
    void setNom(QString);
    void setPrenom(QString);
    void setAdresse(QString);
    void setTelephone(int);
    void setRole(QString);
    void setTelephone(QString);
    void setSkill(QString);
    void setDateDebut(QDate);
    void setDate_f(QDate);
    void setImage(QString);


    bool ajouter();
    bool modifier();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool RechercheemployeeParID(int IDrecherche);
    QSqlQueryModel *tri_ID();
    QSqlQueryModel *tri_nom();


};

#endif // EMPLOYEE_H
