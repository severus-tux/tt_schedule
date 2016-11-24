#include "tt_main_window.h"
#include "ui_tt_main_window.h"
#include <QMessageBox>
#include <QFileInfo>

bool dbExists(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    return (check_file.exists() && check_file.isFile());
}


tt_main_window::tt_main_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tt_main_window)
{
    ui->setupUi(this);
    db_path="tt_databases/time_table.db";
}

tt_main_window::~tt_main_window()
{
    delete ui;
}

void tt_main_window::on_buttonBox_rejected()
{
    QApplication::quit();
}

void tt_main_window::on_buttonBox_accepted()
{
    if(ui->radioButton_view_tt->isChecked())
    {
        if(dbExists(tt_main_window::db_path))
        {
            hide();
            chooseview = new choose_view(this);
            chooseview->show();
        }
        else
        {
            QMessageBox::critical(this,"Database not found!","Sorry! The database is missing!\nYou might want to generate a new one.");
        }
    }
    else if(ui->radioButton_generate_tt->isChecked())
    {

        QMessageBox::StandardButton reply = QMessageBox::Ok;
        if(dbExists(tt_main_window::db_path))
        {
            reply =  QMessageBox::warning(this,"Warning",
                                  "All previous timetable will be lost. Proceed carefully!",
                                  QMessageBox::Ok | QMessageBox:: Cancel);
        }
        if(reply == QMessageBox::Ok)
        {
            hide();
            input_data = new input(this);
            input_data->show();
            db_create = new tt_database();
            db_create ->tt_create_new_db();
        }
    }
    else
    {
        QMessageBox::critical(this,"No option selected","No options were selected!!.");
    }
}
