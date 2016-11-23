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
                    "set sub_id = ( select sub_id from subject where sub_name='MATHS-3')) "
                    "where exists ( "
                    "   select * from maths "
                    "   where maths.day=master.day and "
                    "   maths.sem=master.sem and "
                    "   maths.sec=master.sec and "
                    "   maths.hour=master.hour )");
    qry_hrd_math.exec();
    db_shdl->connClose();
}
