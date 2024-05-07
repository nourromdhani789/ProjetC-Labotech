#include "project.h"
#include <QDebug>
#include <QSqlError>

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

QSqlQueryModel* Project::rechercher(int num)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM Project WHERE num=:num");
    query.bindValue(":num", num);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("num"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("title"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("description"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("budget"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("progress"));
    } else {
        // La requête a échoué, gérez l'erreur
        qDebug() << "Échec de l'exécution de la requête :" << query.lastError().text();
    }

    return model;
}

QSqlQueryModel* Project::trier()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJECT ORDER BY NUM ASC");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("num"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("title"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("description"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("budget"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("progress"));
    return model;
}

QSqlQueryModel * Project::rechercherProject(QString chaine)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM PROJECT WHERE (num LIKE '%" + chaine + "%')");
    return model;
}

bool Project::existance(QString cin)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM project WHERE num = ?");
    query.addBindValue(cin);
    if(query.exec())
    {
        if(query.next())
        {
            // QMessageBox::information(this,  "CIN existe", "CIN déjà existant.");
            return false;
        }
    }
    return true;
}
