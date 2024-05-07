#include "paricipant.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>

participant::participant(int idp,QString name,QString lastname,QString adress,int tel,QString skill,QString role,QString datestart,QString dateend)
{
    this->idp=idp;
    this->name=name;
    this->lastname=lastname;
    this->adress=adress;
    this->tel=tel;
    this->skill=skill;
    this->role=role;
    this->datestart=datestart;
    this->dateend=dateend;
}


bool participant::ajouter()
{
    QSqlQuery query;

    QString res = QString::number(idp);
    QString res2 = QString::number(tel);


    query.prepare("insert into participant(idp, name, lastname, adress, tel, skill, role, datestart, dateend)" "values(:idp, :name, :lastname, :adress, :tel, :skill, :role, :datestart, :dateend)");

    query.bindValue(":idp",res);
    query.bindValue(":name",name);
    query.bindValue(":lastname",lastname);
    query.bindValue(":adress",adress);
    query.bindValue(":tel",res2);
    query.bindValue(":skill",skill);
    query.bindValue(":role",role);
    query.bindValue(":datestart",datestart);
    query.bindValue(":dateend",dateend);

    return query.exec();

}

bool participant::supprimer(int idp)
{
    QSqlQuery query;
    QString res = QString::number(idp);

    // First, fetch the entry that is being deleted
    QSqlQuery fetchQuery;
    fetchQuery.prepare("SELECT * FROM participant WHERE idp = :idp");
    fetchQuery.bindValue(":idp", res);
    if (!fetchQuery.exec()) {
        qDebug() << "Failed to fetch participant for deletion:" << fetchQuery.lastError().text();
        return false;
    }

    if (!fetchQuery.next()) {
        qDebug() << "No participant found for deletion.";
        return false;
    }

    // Insert the fetched entry into the archive table
    QSqlRecord record = fetchQuery.record();
    if (!record.isEmpty()) {
        QSqlQuery archiveQuery;
        archiveQuery.prepare("INSERT INTO archive (idp, name, lastname, adress, tel, skill, role, datestart, dateend) "
                             "VALUES (:idp, :name, :lastname, :adress, :tel, :skill, :role, :datestart, :dateend)");
        archiveQuery.bindValue(":idp", record.value("idp"));
        archiveQuery.bindValue(":name", record.value("name"));
        archiveQuery.bindValue(":lastname", record.value("lastname"));
        archiveQuery.bindValue(":adress", record.value("adress"));
        archiveQuery.bindValue(":tel", record.value("tel"));
        archiveQuery.bindValue(":skill", record.value("skill"));
        archiveQuery.bindValue(":role", record.value("role"));
        archiveQuery.bindValue(":datestart", record.value("datestart"));
        archiveQuery.bindValue(":dateend", record.value("dateend"));
        if (!archiveQuery.exec()) {
            qDebug() << "Failed to insert into archive table:" << archiveQuery.lastError().text();
            return false;
        }
    } else {
        qDebug() << "Record is empty.";
        return false;
    }

    // Now delete the entry from the participant table
    query.prepare("DELETE FROM participant WHERE idp = :idp");
    query.bindValue(":idp", res);

    return query.exec();
}



QSqlQueryModel * participant::afficher()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from participant");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("idp"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("lastname"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("adress"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("skill"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("role"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("datestart"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("dateend"));

    return model;
}
QSqlQueryModel * participant::afficherarchive()
{

    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from archive");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("idp"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("lastname"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("adress"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("skill"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("role"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("datestart"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("dateend"));

    return model;
}

bool participant::modifier(int idp,QString name,QString lastname,QString adress,int tel,QString skill,QString role,QString datestart,QString dateend)
{
    QSqlQuery query;


    query.prepare("update participant set name=:name, lastname=:lastname, adress=:adress,  tel=:tel, skill=:skill, role=:role, datestart=:datestart, dateend=:dateend  where idp=:idp");

    query.bindValue(":idp", idp);
    query.bindValue(":name", name);
    query.bindValue(":lastname", lastname);
    query.bindValue(":adress", adress);
    query.bindValue(":tel", tel);
    query.bindValue(":skill", skill);
    query.bindValue(":role", role);
    query.bindValue(":datestart", datestart);
    query.bindValue(":dateend", dateend);

    return query.exec();
}

QSqlQueryModel * participant::recherche(int idp)
{
    QSqlQueryModel * model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM participant WHERE idp=:idp");
    query.bindValue(":idp", idp);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("idp"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("name"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("lastname"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("adress"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("tel"));
        model->setHeaderData(5, Qt::Horizontal,QObject::tr("skill"));
        model->setHeaderData(6, Qt::Horizontal,QObject::tr("role"));
        model->setHeaderData(7, Qt::Horizontal,QObject::tr("datestart"));
        model->setHeaderData(8, Qt::Horizontal,QObject::tr("dateend"));
    } else {
        // Query execution failed, handle error
        qDebug() << "Query execution failed:" << query.lastError().text();
    }

    return model;
}
QSqlQueryModel* participant::trier()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM participant ORDER BY idp ASC");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("idp"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("lastname"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("adress"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("skill"));
    model->setHeaderData(6, Qt::Horizontal,QObject::tr("role"));
    model->setHeaderData(7, Qt::Horizontal,QObject::tr("datestart"));
    model->setHeaderData(8, Qt::Horizontal,QObject::tr("dateend"));
    return model;
}

QSqlQueryModel * participant::rechercherpartici(QString chaine)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM participant WHERE (idp LIKE '%" + chaine + "%')");
    return model;
}
QSqlQueryModel* participant::trierarch()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM archive ORDER BY idp ASC");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("idp"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("name"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("lastname"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("adress"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("tel"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("skill"));
    model->setHeaderData(6, Qt::Horizontal,QObject::tr("role"));
    model->setHeaderData(7, Qt::Horizontal,QObject::tr("datestart"));
    model->setHeaderData(8, Qt::Horizontal,QObject::tr("dateend"));
    return model;
}

QSqlQueryModel * participant::rechercherarchive(QString chaine)
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM archive WHERE (idp LIKE '%" + chaine + "%')");
    return model;
}

/*void participant::pdf()
{
    QString fileName = QCoreApplication::applicationDirPath() + "/ParticipantData.pdf";

    // Create QTextDocument to hold the content
    QTextDocument doc;

    // Set up the HTML content for the table
    QString htmlContent = "<html><body>";

    // Add the image
    //htmlContent += "<img src='file:///C:/Users/ADMIN/Documents/crud_patient/logo%20application.png' width='200' height='200'><br>";

    // Add the title
    htmlContent += "<h1 style='text-align:center;'>Participant List</h1>";

    // Create the table
    htmlContent += "<table border='1' cellpadding='5' align='center'><tr>";

    // Define column names
    QStringList columnNames = { "Identification", "Name", "LastName", "Adres", "Téléphone", "Role", "Skill", "DateStart" };

    // Add column names to HTML content
    foreach(QString columnName, columnNames) {
        htmlContent += "<th>" + columnName + "</th>";
    }
    htmlContent += "</tr>";

    // Fetch data from the database
    QSqlQueryModel *model = afficher();

    // Add data rows to HTML content
    for (int row = 0; row < model->rowCount(); ++row) {
        htmlContent += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            htmlContent += "<td>" + model->index(row, col).data().toString() + "</td>";
        }
        htmlContent += "</tr>";
    }

    // Close HTML content
    htmlContent += "</table>";

    // Add the current date at the bottom
    QString currentDate = QDate::currentDate().toString("dd/MM/yyyy");
    htmlContent += "<p style='text-align:center;'>Date: " + currentDate + "</p>";

    htmlContent += "</body></html>";

    // Set the HTML content to the QTextDocument
    doc.setHtml(htmlContent);

    // Save the QTextDocument as PDF
    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    pdfWriter.setPageMargins(QMarginsF(30, 30, 30, 30)); // Adjust margins as needed

    if (pdfWriter.resolution() != -1) {
        doc.print(&pdfWriter);
        QMessageBox::information(nullptr, "Success", "PDF file generated successfully.");
    } else {
        QMessageBox::critical(nullptr, "Error", "Failed to create PDF writer.");
    }

    // Delete the model
    delete model;
}*/
QSqlQueryModel * participant::rechercheCalender(const QString &name) {
    QSqlQueryModel * model = new QSqlQueryModel();

    QSqlQuery query;
    query.prepare("SELECT * FROM calender WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec()) {
        model->setQuery(query);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Name"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Task"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Time"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    } else {
        // Query execution failed, handle error
        qDebug() << "Query execution failed:" << query.lastError().text();
    }

    return model;
}
void participant::deleteCalendarData(const QString &name) {
    QSqlQuery query;
    query.prepare("DELETE FROM calender WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec()) {
        qDebug() << "Calender data for" << name << "deleted successfully.";
    } else {
        qDebug() << "Failed to delete calender data for" << name << ":" << query.lastError().text();
    }
}

bool participant::supprimerarchive(int idp) {
    // Construct the SQL query to delete data from the archive table based on participant ID
    QSqlQuery query;
    query.prepare("DELETE FROM archive WHERE idp = :idp");
    query.bindValue(":idp", idp);

    // Execute the query
    if(query.exec()) {
        qDebug() << "Data deleted from archive successfully.";
    } else {
        qDebug() << "Failed to delete data from archive:" << query.lastError().text();
    }
}




