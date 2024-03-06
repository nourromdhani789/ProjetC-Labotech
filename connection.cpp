#include "connection.h"

Connection::Connection(){}

bool Connection::createConnection(){

    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("projetc++");
    db.setUserName("BALIGH3");//inserer nom de l'utilisateur
    db.setPassword("azerty");//inserer mot de passe de cet utilisateur

    if (db.open()) test=true;
    return test;
}

void Connection::closeConnection(){db.close();}
