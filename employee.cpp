#include "employee.h"
QString select = "SELECT login from account where login='"+  lelogin->text()+"' and password='"+lepassword->text()+"'";
employee::employee(int id,QString nom,QString prenom,QString adress,int phone,QString role,QString skill,QString date_s,QString date_f)
{
    this->id = id;
    this->nom = nom;
    this->prenom = prenom;
    this->adress = adress;
    this->phone = phone;
    this->role = role;
    this->skill = skill;
    this->date_s = date_s;
    this->date_f = date_f;
}
bool employee::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employee (id, nom, prenom, adress, phone, role, skill, date_s, date_f) ""VALUES (:id, :nom, :prenom, :adress, :phone, :role, :skill, :date_s, :date_f)");
    query.bindValue(":id", id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adress", adress);
    query.bindValue(":phone", phone);
    query.bindValue(":role", role);
    query.bindValue(":skill", skill);
    query.bindValue(":date_s", date_s);
    query.bindValue(":date_f", date_f);
    if (query.exec()) {
       return true;
   } else {
      qDebug() << "Erreur lors de l'ajout de l'employé:" << query.lastError();
      return false;
     }
}
bool employee::modifier(int id)
{
    QSqlQuery query;

    // Vérifier si l'employé avec l'ID donné existe dans la base de données
    query.prepare("SELECT id FROM employee WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Erreur lors de la vérification de l'existence de l'employé:" << query.lastError();
        return false;
    }

    if (query.next()) {
        // L'employé avec l'ID donné existe, permettre la modification

        query.prepare("UPDATE employee SET nom = :nom, prenom = :prenom, adress = :adress, phone = :phone, role = :role, skill = :skill, date_s = :date_s, date_f = :date_f WHERE id = :id");
        query.bindValue(":id", id);
        query.bindValue(":nom", nom);
        query.bindValue(":prenom", prenom);
        query.bindValue(":adress", adress);
        query.bindValue(":phone", phone);
        query.bindValue(":role", role);
        query.bindValue(":skill", skill);
        query.bindValue(":date_s", date_s);
        query.bindValue(":date_f", date_f);

        if (query.exec()) {
            qDebug() << "L'employé a été modifié avec succès.";
            return true;
        } else {
            qDebug() << "Erreur lors de la modification de l'employé:" << query.lastError();
            return false;
        }
    } else {
        // L'employé avec l'ID donné n'existe pas
        qDebug() << "L'employé avec l'ID" << id << "n'existe pas.";
        return false;
    }
}
QSqlQueryModel* employee::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT id, nom, prenom, adress, phone, role, skill, date_s, date_f FROM employee");

    if (!query.exec()) {
        qDebug() << "Erreur lors de la récupération de la liste des employés:" << query.lastError().text();
        delete model; // Supprimer le modèle en cas d'échec
        return nullptr;
    }

    model->setQuery(query);
    return model;
}

bool employee::supprimer(int)
{

}
