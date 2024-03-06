#ifndef PROJECT_H
#define PROJECT_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class Project
{
public:
    Project();
    int getNum();
    QString getTitle();
    QString getDescription();
    QString getBudget();
    QString getProgress();
    void setNum(int);
    void setTitle(QString);
    void setDescription(QString);
    void setBudget(QString);
    void setProgress(QString);
    Project(int,QString,QString,QString,QString);
    QSqlQueryModel * afficher();
    bool ajouter();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,QString);

private:
        int num;
        QString title;
        QString description;
        QString budget;
        QString progress;
};

#endif // PROJECT_H
