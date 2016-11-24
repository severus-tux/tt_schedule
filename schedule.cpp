#include "schedule.h"

schedule::schedule()
{
	//constructor
}

void schedule::schedule_hrd_math()
{
    db_shdl = new tt_database();
    db_shdl->connOpen();
    QSqlQuery qry_hrd_math;
    qry_hrd_math.prepare("update master  "
                    "set sub_id = 'HRD' "
                    "where exists ( "
                    "   select * from hrd "
                    "   where hrd.day=master.day and "
                    "   hrd.sem=master.sem and "
                    "   hrd.sec=master.sec and "
                    "   (hrd.hour=master.hour or hrd.hour=master.hour-1) )");
    qry_hrd_math.exec();

    qry_hrd_math.prepare("update master  "
                    "set sub_id = ( select sub_id from subject where sub_name='MATHS-3') "
                    "where exists ( "
                    "   select * from maths "
                    "   where maths.day=master.day and "
                    "   maths.sem=master.sem and "
                    "   maths.sec=master.sec and "
                    "   maths.hour=master.hour )");
    qry_hrd_math.exec();
    db_shdl->connClose();
}
void schedule::initialize_master()
{
    db_shdl = new tt_database();
    db_shdl->connOpen();

    //initializing master with default values
    QStringList days,hours;
    days << "MON" << "TUE" << "WED" << "THU" << "FRI" << "SAT";
    hours << "1" << "2" << "3" << "4" << "5" << "6" << "7"; //hours in string list beacuse of error cannot
                                                            //convert int to char while preparing query
    QSqlQuery qry("select * from class;");
    QVector<QString> sem_sec;
    while(qry.next())
    {
        QString tmp;
        QSqlRecord record = qry.record();
        for (int i=0;i<record.count();i++)
        {
            tmp.append(record.value(i).toString());
            tmp.append(",'");
        }
        tmp.chop(2);
        sem_sec.append(tmp);
    }
    db_shdl->db.transaction();
    for(int day = 0 ; day < 6 ; day++) //days
    {
        for(int i = 0 ; i < sem_sec.length() ; i++) //for existing sem and sec
        {
            for(int hour = 0 ; hour < 7 ; hour++) //hours
            {
                QString insert_qry;
                insert_qry = "INSERT INTO MASTER VALUES ('"+days.at(day)+"',"+sem_sec.at(i)+"',"+hours.at(hour)+",NULL)";
                QSqlQuery final_qry;
                final_qry.exec(insert_qry);
                //qDebug() << insert_qry;
            }

        }

    }
    db_shdl->db.commit();
    QSqlQuery delete_qry;
    delete_qry.prepare("delete from master where day='SAT' and hour >= 5");
    delete_qry.exec();
    db_shdl->connClose();
}
