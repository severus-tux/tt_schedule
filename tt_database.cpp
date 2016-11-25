#include "tt_database.h"
#include <QDebug>

tt_database::tt_database()
{

}

void tt_database::tt_create_new_db()
{
    connOpen();
    QSqlQuery query;
    query.prepare("CREATE TABLE class (sem int , sec char(1) ,"
               " primary key(sem,sec))");
    query.exec();
    query.prepare("CREATE TABLE subject (sub_id varchar(10) primary key , sub_name varchar(50))");
    query.exec();
    query.prepare("CREATE TABLE semester (sem int , sub_id varchar(10) ,"
               " foreign key(sem) references class(sem) ,"
               " foreign key(sub_id) references subject(sub_id))");
    query.exec();
    query.prepare("CREATE TABLE teacher_info (tid varchar(20) primary key ,"
               " tname varchar(30) , initials varchar(5) )");
    query.exec();
    query.prepare("CREATE TABLE teachers (tid varchar(20) , sem int , sec char(1) ,sub_id varchar(10) ,"
               " foreign key(tid) references teacher_info(tid) ,"
               " foreign key(sem) references class(sem) ,"
               " foreign key(sec) references class(sec) ,"
               " foreign key(sub_id) references subject(sub_id))");
    query.exec();
    query.prepare("CREATE TABLE hrd ( day varchar(20) , sem int , sec char(1) , hour int ,"
               " foreign key(sem) references class(sem) ,"
               " foreign key(sec) references class(sec))");
    query.exec();
    query.prepare("CREATE TABLE master ( day varchar(20) , sem int , sec char(1) , hour int ,sub_id varchar(10),"
               " foreign key(sem) references class(sem) ,"
               " foreign key(sec) references class(sec),"
               " foreign key(sub_id) references subject(sub_id))");
    query.exec();
    query.prepare("CREATE TABLE maths ( day varchar(20) , sem int , sec char(1) , hour int ,"
               " foreign key(sem) references class(sem) ,"
               " foreign key(sec) references class(sec))");
    query.exec();
    query.prepare("CREATE TABLE lab(day varchar(20),sem int,sec char(1),lab_name varchar(20),"
               " sub_id varchar(10),tid1 int,tid2 int,batch varchar(2),"
               " foreign key(sem) references class(sem),"
               " foreign key(sec) references class(sec),"
               " foreign key(sub_id) references subject(sub_id),"
               " foreign key(tid1) references teacher_info(tid),"
               " foreign key(tid2) references teacher_info(tid))");
    query.exec();

    //Creating all required views :

    query.prepare("create view master_class as "
                  "select m.day,m.sem,m.sec, "
                  "COALESCE(m.sem, '') || '-' || COALESCE(m.sec, '') as class, "
                  "m.hour,m.sub_id,s.sub_name, "
                  "( "
                  "case "
                  "    when day='MON' then 1 "
                  "    when day='TUE' then 2 "
                  "    when day='WED' then 3 "
                  "    when day='THU' then 4 "
                  "    when day='FRI' then 5 "
                  "    when day='SAT' then 6 "
                  "end "
                  ") as day_num "
                  "from master m, subject s "
                  "where m.sub_id=s.sub_id;");
    query.exec();
    query.prepare("create view master_lab as "
                  "select l.day,l.sem,l.sec,l.lab_name,l.tid1,l.tid2,l.batch, "
                  "COALESCE (l.sem,'') || COALESCE (l.sec,'') || '-' || COALESCE (l.batch,'') as class, "
                  "m.hour, "
                  "( "
                  "case "
                  "    when day='MON' then 1 "
                  "    when day='TUE' then 2 "
                  "    when day='WED' then 3 "
                  "    when day='THU' then 4 "
                  "    when day='FRI' then 5 "
                  "    when day='SAT' then 6 "
                  "end "
                  ") as day_num "
                  "from master m , lab l "
                  "where "
                  "m.day=l.day and "
                  "m.sem=l.sem and "
                  "m.sec=l.sec and "
                  "m.sub_id=l.sub_id;");
    query.exec();
    query.prepare("CREATE VIEW complete as "
                  "select m.day,m.sem,m.sec, "
                  "COALESCE(m.sem, '') || '-' || COALESCE(m.sec, '') as class, "
                  "m.hour,m.sub_id,s.sub_name,t.tid,ti.tname,ti.initials, "
                  "( "
                  "case "
                  "     when day='MON' then 1 "
                  "     when day='TUE' then 2 "
                  "     when day='WED' then 3 "
                  "     when day='THU' then 4 "
                  "     when day='FRI' then 5 "
                  "     when day='SAT' then 6 "
                  "end "
                  ") as day_num "
                  "from master m, subject s, teachers t, teacher_info ti "
                  "where "
                  "m.sub_id=s.sub_id and "
                  "m.sem=t.sem and "
                  "m.sec=t.sec and "
                  "m.sub_id=t.sub_id and "
                  "t.tid=ti.tid");
    query.exec();
    connClose();
}


void tt_database::connOpen()
{
    QString path = "tt_databases/time_table.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
}

void tt_database::connClose()
{
    db.close();
    db.removeDatabase("QSQLITE");
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

void tt_database::input_db(QString path, QString table)
{
    connOpen();

    //Open the ".csv" file
    QFile file(path);
    if(file.open (QIODevice::ReadOnly))
    {
        QSqlQuery qry;
        QTextStream ts (&file);

        //Travel through the csv file "excel.csv"
        db.transaction();
        while(!ts.atEnd())
        {
            QString qr = "INSERT INTO "+table+" VALUES( '";
            // split every lines on comma
            QStringList line = ts.readLine().split(',');
            /*for every values on a line,
                append it to the INSERT request*/
            for(int i=0; i<line.length ();++i)
            {
                qr.append(line.at(i));
                qr.append("', '");
            }
            qr.chop(3); // remove the trailing comma ,space and '
            qr.append("); "); // close the "VALUES([...]" with a ");"
            qry.exec(qr);
        }
        db.commit();
        file.close ();
    }
    connClose();
}

