#include "connexion.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projetc++");//inserer le nom de la source de données ODBC
db.setUserName("beya1");//inserer nom de l'utilisateur
db.setPassword("azerty");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
