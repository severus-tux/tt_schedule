#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "tt_database.h"
#include <QSqlQuery>

class schedule
{
public:
    schedule();
    void schedule_hrd_math();
private:
    tt_database *db_shdl;
};

class teacher:public schedule
{
public:
    teacher();
};

class class_room:public schedule
{

};

#endif // SCHEDULE_H
