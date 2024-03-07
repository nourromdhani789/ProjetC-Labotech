#include "connection.h"

Connection::Connection() {}
bool Connection::createconnection(){
  db = QSqlDatabase::addDatabase("QODBC");
  bool test=false;
  db.setDatabaseName("employé");
  db.setUserName("imen");
  db.setPassword("12345");
  if (db.open()) test=true;

    return test;
  }
void Connection::closeconnection() {
  db.close();
}
