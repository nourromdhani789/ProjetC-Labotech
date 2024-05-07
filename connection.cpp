#include "connection.h"

connection::connection(){}

bool connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("projet");
db.setUserName("nour0");//inserer nom de l'utilisateur
db.setPassword("0000");//inserer mot de passe de cet utilisateur

if (db.open()) test=true;
return test;
}

void connection::closeConnection(){db.close();}
