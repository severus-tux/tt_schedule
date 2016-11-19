#include "tt_table_view.h"
#include "ui_tt_table_view.h"

tt_table_view::tt_table_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tt_table_view)
{
    ui->setupUi(this);
}

tt_table_view::~tt_table_view()
{
    delete ui;
}

void tt_table_view::on_pushButton_exit_clicked()
{
    QApplication::quit();
}

void tt_table_view::loadtable(int table_no, QString condition)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.db);

    switch (table_no)
    {
        case 3 :


            qry->prepare("select day, "
                         "group_concat( case when hour =1 then sub_name end ) as 'hour-1', "
                         "group_concat( case when hour =2 then sub_name end ) as 'hour-2', "
                         "group_concat( case when hour =4 then sub_name end ) as 'hour-4', "
                         "group_concat( case when hour =5 then sub_name end ) as 'hour-5', "
                         "group_concat( case when hour =6 then sub_name end ) as 'hour-6', "
                         "group_concat( case when hour =7 then sub_name end ) as 'hour-7' "
                         "from master_class "
                         "where class='"+condition+"' "
                         "group by day "
                         "order by day_num;"
                         );
            qry->exec();
            modal->setQuery(*qry);
            tt_table_view::ui->tableView->setModel(modal);
            ui->table_title->setText("Class timetable : "+condition+" ");
            ui->table_title->setStyleSheet("QLabel {  font-size:16px; font-weight: bold; color : blue; }");
        break;

        case 4 :
            QStringList lst = condition.split('/');
            qry->prepare("select day, "
                         "group_concat( case when hour = 1 then class end ) as hr1, "
                         "group_concat( case when hour = 2 then class end ) as hr2, "
                         "group_concat( case when hour = 3 then class end ) as hr3, "
                         "group_concat( case when hour = 4 then class end ) as hr4, "
                         "group_concat( case when hour = 5 then class end ) as hr5, "
                         "group_concat( case when hour = 6 then class end ) as hr6, "
                         "group_concat( case when hour = 7 then class end ) as hr7  "
                         "from complete "
                         "where "
                         "tid="+QString(lst.at(0))+" "
                         "group by day "
                         "order by day_num;"
                         );
            qry->exec();
            modal->setQuery(*qry);
            tt_table_view::ui->tableView->setModel(modal);
            ui->table_title->setText("Teacher's Timetable : "+condition+" ");
            ui->table_title->setStyleSheet("QLabel {  font-size:16px; font-weight: bold; color : blue; }");
        break;
    }
    conn.connClose();
}

void tt_table_view::on_pushButton_print_clicked()
{

}

void tt_table_view::on_pushButton_back_clicked()
{
    hide();
    close();
}
