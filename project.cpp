#include "project.h"

Project::Project()
{

}

int Project::getNum()
{
    return num;
}

QString Project::getTitle()
{
    return title;
}

QString Project::getDescription()
{
    return description;
}

QString Project::getBudget()
{
    return budget;
}

QString Project::getProgress()
{
    return progress;
}

void Project::setNum(int a)
{
    num=a;
}

void Project::setTitle(QString b)
{
   title=b;
}

void Project::setDescription(QString c)
{
    description=c;
}

void Project::setBudget(QString d)
{
    budget=d;
}

void Project::setProgress(QString e)
{
    progress=e;
}

Project::Project(int a,QString b,QString c,QString d,QString e)
{
    num=a;
    title=b;
    description=c;
    budget=d;
    progress=e;
}

QSqlQueryModel * Project::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Project");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("title"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("budget"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("progress"));
    return model;
}
bool Project::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(num);
    query.prepare("insert into Project (num,title,description,budget,progress) values (:num,:title,:description,:budget,:progress)");
    query.bindValue(":num",num);
    query.bindValue(":title",title);
    query.bindValue(":description",description);
    query.bindValue(":budget",budget);
    query.bindValue(":progress",progress);
    return query.exec();
}
bool Project::supprimer(int num)
{
    QSqlQuery query;
    QString res = QString::number(num);
    query.prepare("delete from Project where num=:num");
    query.bindValue(":num",num);
    return query.exec();
}

bool Project::modifier(int num, QString title, QString description, QString budget, QString progress)
{
    QSqlQuery query;
    QString res = QString::number(num);
    query.prepare("update Project set title=:title, description=:description, budget=:budget, progress=:progress where num=:num");
    query.bindValue(":num", num);
    query.bindValue(":title", title);
    query.bindValue(":description", description);
    query.bindValue(":budget", budget);
    query.bindValue(":progress", progress);
    return query.exec();
}
