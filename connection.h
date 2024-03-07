#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>

class Connection
{
public:
    QSqlDatabase db;

    Connection();
    bool createconnection();
    void closeconnection();
};

#endif // CONNECTION_H
