#include "connection.h"

connexion::connexion()
{

}



bool connexion::createconnect() {
 bool test=false;

 QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
 db.setDatabaseName("projetc++"); // source de données ODBC
 db.setUserName("imen"); // Nom de l'utilisateur qui a créé la source de données
 db.setPassword("12345"); // Mot de passe de cet utilisateur

if (db.open())
    test=true;
    return  test ;
}
