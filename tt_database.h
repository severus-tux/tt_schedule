#ifndef TT_DATABASE_H
#define TT_DATABASE_H

#include <QtSql>
#include <QFileInfo>
#include <QSqlQuery>
#include <QFile>
#include <QIODevice>
#include <QStringList>
#include <QTextStream>

class tt_database
{
public:
    QSqlDatabase db;
    QString path;
    tt_database();
    void tt_create_new_db();
    void tt_view_db(int);// master  => 1
                         // lab     => 2
                         // class   => 3
                         // teacher => 4
    void connOpen();
    void connClose();
    void input_db(QString path,QString table);


};

#endif // TT_DATABASE_H

//end
