#include <QApplication>
#include <QTableView>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("person.db");
    if(!db.open())  return false;

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS person(id INTEGER Primary Key,"
               "firstname VARCHAR(20) NOT NULL, lastname VARCHAR(20));");
    query.exec("INSERT INTO person VALUES(101, 'Youngsu', 'Kang');");
    query.exec("INSERT INTO person(firstname, lastname) VALUES('Soomi', 'Kim')");
    query.exec("INSERT INTO person(firstname, lastname) VALUES "
               "('Hanmi', 'Lee'), ('YoungJin', 'Suh'), ('YoungHwa', 'Ryu');");

    return true;
}

int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);

    if(!createConnection()) return 1;

//    QSqlQueryModel queryModel;
//    queryModel.setQuery("select * from person");
//    queryModel.setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
//    queryModel.setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
//    queryModel.setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));
    QSqlTableModel queryModel;
    queryModel.setTable("person");
//    queryModel.setEditStrategy(QSqlTableModel::OnManualSubmit);               //저장 여부를 수동 명령으로 사용.
    queryModel.select();

    queryModel.setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    queryModel.setHeaderData(1, Qt::Horizontal, QObject::tr("First name"));
    queryModel.setHeaderData(2, Qt::Horizontal, QObject::tr("Last name"));

    QTableView *tableView = new QTableView;
    tableView->setModel(&queryModel);
    tableView->setWindowTitle(QObject::tr("Query Model"));
    tableView->show();

    return a.exec();
}
