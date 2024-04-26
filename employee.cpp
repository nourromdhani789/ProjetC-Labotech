#include "employee.h"
#include  <QSqlQueryModel>
#include <QSqlQuery>
#include <QMessageBox>
#include <QtDebug>
#include <QSystemTrayIcon>
#include <QMessageBox>
#include <QSqlQuery>
#include <QObject>
#include<QSqlRecord>
#include <QSqlError>

employee::employee(int id,QString prenom,QString nom,QString adress,int phone,QString role,QString skills,QDate date_s,QDate date_f,QString image)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->adress = adress;
    this->phone = phone;
    this->role = role;
    this->skills = skills;
    this->date_s = date_s;
    this->date_f = date_f;
     this->image = image;
}
int employee::getId() {
    return id;
}
void employee::setId(int id) {
    this->id = id;
}

// Getter and setter for nom
QString employee::getNom() {
    return nom;
}
void employee::setNom(QString n) {
    nom = n;
}

// Getter and setter for prenom
QString employee::getPrenom() {
    return prenom;
}
void employee::setPrenom(QString p) {
    prenom = p;
}

// Getter and setter for adress
QString employee::getAdress() {
    return adress;
}
void employee::setAdresse(QString a) {
    adress = a;
}

// Getter and setter for phone
int employee::getPhone() {
    return phone;
}
void employee::setTelephone(int pe) {
    phone = pe;
}

// Getter and setter for role
QString employee::getRole() {
    return role;
}
void employee::setRole(QString r) {
    role = r;
}

// Getter and setter for skill
QString employee::getSkill() {
    return skills;
}
void employee::setSkill(QString s) {
    skills = s;
}

// Getter and setter for date_s
QDate employee::getDate_s() {
    return date_s;
}
void employee::setDateDebut(QDate ds) {
    date_s = ds;
}

// Getter and setter for date_f
QDate employee::getDate_f() {
    return date_f;
}
void employee::setDate_f(QDate df) {
    date_f = df;
}
bool employee::ajouter()
{
    QSqlQuery query;
    QString id_string = QString::number(id);
    query.prepare("INSERT INTO employe (id, prenom, nom, adress, phone, role, skills, date_s, date_f,image) ""VALUES (:id, :prenom, :nom, :adress, :phone, :role, :skills, :date_s, :date_f,:image)");
    query.bindValue(":id", id_string);
    query.bindValue(":prenom", prenom);
    query.bindValue(":nom", nom);

    query.bindValue(":adress", adress);
    query.bindValue(":phone", phone);
    query.bindValue(":role", role);
    query.bindValue(":skills", skills);
    query.bindValue(":date_s", date_s);
    query.bindValue(":date_f", date_f);
    query.bindValue(":image", image);
      return query.exec();
}
bool employee::RechercheemployeeParID(int IDrecherche)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM employe WHERE id=:IDrecherche");
    query.bindValue(":IDrecherche",IDrecherche);
    query.exec();
    if (!query.first()){
        return false;
    }
    else
    {
        int nID = query.record().indexOf("id");
        int nPrenom=query.record().indexOf("prenom");
        int nNom=query.record().indexOf("nom");
        int nAdress=query.record().indexOf("adress");
        int nPhone=query.record().indexOf("phone");
        int nRole=query.record().indexOf("role");
        int nSkills=query.record().indexOf("skills");
        int nDate_s=query.record().indexOf("date_s");
        int nDate_f=query.record().indexOf("date_f");

        id=query.value(nID).toInt();
        prenom=query.value(nPrenom).toString();
        nom=query.value(nNom).toString();
        adress=query.value(nAdress).toString();
        role=query.value(nRole).toString();
        phone=query.value(nPhone).toInt();
        skills=query.value(nSkills).toString();
        date_s=query.value(nDate_s).toDate();
        date_f=query.value(nDate_f).toDate();

        return true;
    }

}

QSqlQueryModel * employee::tri_ID()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from employe order by id  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * employee::tri_nom()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from employe order by nom  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}
bool employee::modifier()
{
    QSqlQuery query;
    QString id_string= QString::number(id);
        query.prepare("UPDATE employe SET prenom = :prenom, nom = :nom, adress = :adress, phone = :phone, role = :role, skills = :skills, date_s = :date_s, date_f = :date_f,image =:image WHERE id = :id");
        query.bindValue(":id", id_string);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":adress", adress);
        query.bindValue(":phone", phone);
        query.bindValue(":role", role);
        query.bindValue(":skills", skills);
        query.bindValue(":date_s", date_s);
        query.bindValue(":date_f", date_f);
           query.bindValue(":image", image);
        return query.exec();
}
QSqlQueryModel* employee::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
   model->setQuery("select * from employe");

   model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("NOM"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("ADRESS"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("PHONE"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("ROLE"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("SKILLS"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("DATE_S"));
   model->setHeaderData(8,Qt::Horizontal,QObject::tr("DATE_F"));

    return model;
}

bool employee::supprimer(int id)
    {
        QSqlQuery query;

        query.prepare("DELETE FROM employe WHERE id = :id");
        query.bindValue(":id", id);

        if (query.exec()) {
            // Vérifier si des lignes ont été affectées par la suppression
            if (query.numRowsAffected() > 0) {
                // Au moins une ligne a été supprimée avec succès
                return true;
            } else {
                // Aucune ligne n'a été affectée, ce qui signifie que l'ID n'existe pas
                return false;
            }
        } else {
            // La requête a échoué
            qDebug() << "Erreur lors de la suppression :" << query.lastError().text();
            return false;
        }
    }
