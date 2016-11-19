#include "choose_view.h"
#include "ui_choose_view.h"
#include <QMessageBox>
#include "tt_table_view.h"

choose_view::choose_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::choose_view)
{
    ui->setupUi(this);

}

choose_view::~choose_view()
{
    delete ui;
}

void choose_view::on_buttonBox_rejected()
{
    QApplication::quit();
}

void choose_view::on_buttonBox_accepted()
{
    if(ui->radioButton_view_master->isChecked())
    {
        QMessageBox::information(this,"Master","Master");
    }
    else if(ui->radioButton_view_lab->isChecked())
    {
        QMessageBox::information(this,"Lab","Lab");
    }
    else if(ui->radioButton_view_class->isChecked())
    {
        tab_view = new tt_table_view();
        tab_view->show();
        tab_view->loadtable(3,ui->comboBox_class->currentText());
    }
    else if(ui->radioButton_view_teacher->isChecked())
    {
        tab_view = new tt_table_view();
        tab_view->show();
        tab_view->loadtable(4,ui->comboBox_teacher->currentText());
    }
    else
    {
        QMessageBox::critical(this,"No option selected","No options were selected!!.");
    }
}

void choose_view::on_radioButton_view_lab_clicked()
{
    ui->comboBox_class->setEnabled(false);
    ui->comboBox_lab->setEnabled(true);
    ui->comboBox_teacher->setEnabled(false);
    con_db = new tt_database();
    QSqlQueryModel *mod = new QSqlQueryModel();
    con_db->connOpen();

    QSqlQuery *get_qry = new QSqlQuery(con_db->db);
    get_qry->prepare("SELECT distinct lab_name from lab");
    get_qry->exec();

    mod->setQuery(*get_qry);
    ui->comboBox_lab->setModel(mod);

    con_db->connClose();
}

void choose_view::on_radioButton_view_class_clicked()
{
    ui->comboBox_class->setEnabled(true);
    ui->comboBox_lab->setEnabled(false);
    ui->comboBox_teacher->setEnabled(false);
    con_db = new tt_database();
    QSqlQueryModel *mod = new QSqlQueryModel();
    con_db->connOpen();

    QSqlQuery *get_qry = new QSqlQuery(con_db->db);
    get_qry->prepare("SELECT distinct class from master_class");
    get_qry->exec();

    mod->setQuery(*get_qry);
    ui->comboBox_class->setModel(mod);

    con_db->connClose();
}

void choose_view::on_radioButton_view_teacher_clicked()
{
    ui->comboBox_teacher->setEnabled(true);
    ui->comboBox_class->setEnabled(false);
    ui->comboBox_lab->setEnabled(false);
    con_db = new tt_database();
    QSqlQueryModel *mod = new QSqlQueryModel();
    con_db->connOpen();

    QSqlQuery *get_qry = new QSqlQuery(con_db->db);
    get_qry->prepare("SELECT COALESCE( distinct tid, '') || '/' || COALESCE(distinct tname, '') as info from teacher_info");
    get_qry->exec();

    mod->setQuery(*get_qry);
    ui->comboBox_teacher->setModel(mod);

    con_db->connClose();
}

void choose_view::on_radioButton_view_master_clicked()
{
    ui->comboBox_class->setEnabled(false);
    ui->comboBox_lab->setEnabled(false);
    ui->comboBox_teacher->setEnabled(false);
}
