#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "tt_database.h"
#include <QSqlQuery>
#include <QSqlDatabase>

class schedule
{
public:
    schedule();
    void schedule_hrd_math();
    void initialize_master();
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
