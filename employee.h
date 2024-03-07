#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
class employee
{
    QString nom,prenom,adress,role,skill,date_s,date_f;
    int id,phone;
public:
    employee(){}
    employee(int, QString , QString , QString , int , QString , QString , QString , QString );


    int getId(){ return id; }
    void setId(int id) { this->id = id; }

    QString getNom() { return nom; }
    void setNom(QString n) { nom = n; }

    QString getPrenom() { return prenom; }
    void setPrenom(QString p) {prenom = p; }

    QString getAdress() { return adress; }
    void setAdresse(QString a) {adress = a; }

    int getPhone() { return phone; }
    void setTelephone(int pe) { this->phone = pe; }

    QString getRole(){ return role; }
    void setRole(QString r) { role = r; }

    QString getSkill(){ return skill; }
    void setSkill(QString s) {skill = s; }

    QString getDate_s(){ return date_s; }
    void setDateDebut(QString ds) {date_s = ds; }

    QString getDate_f() { return date_f; }
    void setDate_f(QString df) { date_f = df; }


    bool ajouter();
    QSqlQueryModel*modifier(int);
    QSqlQueryModel*afficher();
    bool supprimer(int);


};

#endif // EMPLOYEE_H
