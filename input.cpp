#include "input.h"
#include "ui_input.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <string>
#include <QDir>
#include <unistd.h>
#include "tt_database.h"
#include <QFileInfo>
#include "tt_main_window.h"
#include <QDebug>

bool fileExists(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and not a directory?
    return (check_file.exists() && check_file.isFile());
}


input::input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::input)
{
    ui->setupUi(this);
    ui->status_label1->setText("No File Uploaded");
    ui->status_label2->setText("No File Uploaded");
    ui->status_label3->setText("No File Uploaded");
    ui->status_label4->setText("No File Uploaded");
    ui->status_label5->setText("No File Uploaded");
    ui->status_label6->setText("No File Uploaded");
    ui->status_label7->setText("No File Uploaded");
}

input::~input()
{
    delete ui;
}

void input::on_pushButton_upload_subject_clicked()
{
    input_file_name1 = QFileDialog::getOpenFileName(this,"Upload File",QDir::homePath(),tr("Excel Files (*.xlsx *.xls *.ods)"));
    if(!input_file_name1.isNull())
        ui->status_label1->setText(input_file_name1);
    else
        QMessageBox::information(this,"File Uploader","No File Selected");
}

void input::on_pushButton_upload_class_clicked()
{
    input_file_name2 = QFileDialog::getOpenFileName(this,"Upload File",QDir::homePath(),tr("Excel Files (*.xlsx *.xls *.ods)"));
    if(!input_file_name2.isNull())
        ui->status_label2->setText(input_file_name2);
    else
        QMessageBox::information(this,"File Uploader","No File Selected");
}

void input::on_pushButton_upload_teacher_clicked()
{
    input_file_name3 = QFileDialog::getOpenFileName(this,"Upload File",QDir::homePath(),tr("Excel Files (*.xlsx *.xls *.ods)"));
    if(!input_file_name3.isNull())
        ui->status_label3->setText(input_file_name3);
    else
        QMessageBox::information(this,"File Uploader","No File Selected");

}

void input::on_pushButton_upload_teacherinfo_clicked()
{
    input_file_name4 = QFileDialog::getOpenFileName(this,"Upload File",QDir::homePath(),tr("Excel Files (*.xlsx *.xls *.ods)"));
    if(!input_file_name4.isNull())
        ui->status_label4->setText(input_file_name4);
    else
        QMessageBox::information(this,"File Uploader","No File Selected");
}

void input::on_pushButton_download_subject_clicked()
{
    QString output_path = QFileDialog::getExistingDirectory(this,"Save templates",QDir::homePath());
    if(output_path.isNull())
        QMessageBox::critical(this,"Error","No Directory selected");
    else
    {
        QString path = "cp tt_templates/subject.xlsx "+output_path;
        bool ret = system(path.toStdString().c_str());
        if(ret)
            QMessageBox::critical(this,"Download Error","Permission Denied");
        else
            QMessageBox::information(this,"Success","Subject Template Downloaded successfully");
    }
}

void input::on_pushButton_download_class_clicked()
{
    QString output_path = QFileDialog::getExistingDirectory(this,"Save templates",QDir::homePath());
    if(output_path.isNull())
        QMessageBox::critical(this,"Error","No Directory selected");
    else
    {
        QString path = "cp tt_templates/class.xlsx "+output_path;
        bool ret = system(path.toStdString().c_str());
        if(ret)
            QMessageBox::critical(this,"Download Error","Permission Denied");
        else
            QMessageBox::information(this,"Success","Class Template Downloaded successfully");
    }
}

void input::on_pushButton_download_teacher_clicked()
{
    QString output_path = QFileDialog::getExistingDirectory(this,"Save templates",QDir::homePath());
    if(output_path.isNull())
        QMessageBox::critical(this,"Error","No Directory selected");
    else
    {
        QString path = "cp tt_templates/teachers.xlsx "+output_path;
        bool ret = system(path.toStdString().c_str());
        if(ret)
            QMessageBox::critical(this,"Download Error","Permission Denied");
        else
            QMessageBox::information(this,"Success","Teacher's Template Downloaded successfully");
    }
}

void input::on_pushButton_download_teacherinfo_clicked()
{
    QString output_path = QFileDialog::getExistingDirectory(this,"Save templates",QDir::homePath());
    if(output_path.isNull())
        QMessageBox::critical(this,"Error","No Directory selected");
    else
    {
        QString path = "cp tt_templates/teacher_info.xlsx "+output_path;
        bool ret = system(path.toStdString().c_str());
        if(ret)
            QMessageBox::critical(this,"Download Error","Permission Denied");
        else
            QMessageBox::information(this,"Success","Teacher Info Template Downloaded successfully");
    }
}

void input::on_pushButton_ok_clicked()
{
    if(input_file_name1.isNull() || input_file_name2.isNull() || input_file_name3.isNull() || input_file_name4.isNull() || input_file_name5.isNull() || input_file_name6.isNull() || input_file_name7.isNull())
        QMessageBox::critical(this,"Error","All specified files are not uploaded");
    else
    {
        hide();
        QString command = "libreoffice --convert-to csv --outdir tt_csv/ \""+input_file_name1+"\" \""+input_file_name2+"\" \""+input_file_name3+"\" \""+input_file_name4+"\" \""+input_file_name5+"\" \""+input_file_name6+"\" \""+input_file_name7+"\"";
        bool ret = system(command.toStdString().c_str());
        if(ret)
            QMessageBox::critical(this,"Error","Failed to process the uploaded files.");
        else
        {

            if ( fileExists("tt_csv/class.csv") &&
                 fileExists("tt_csv/subject.csv") &&
                 fileExists("tt_csv/semester.csv") &&
                 fileExists("tt_csv/teacher_info.csv") &&
                 fileExists("tt_csv/teachers.csv") &&
                 fileExists("tt_csv/hrd.csv") &&
                 fileExists("tt_csv/maths.csv") )
            {
                system("for file in tt_csv/*; do sed '1,2d' $file >tmp ; mv tmp $file; done");
                db_ip = new tt_database();
                db_ip->input_db("tt_csv/class.csv","class");
                db_ip->input_db("tt_csv/subject.csv","subject");
                db_ip->input_db("tt_csv/semester.csv","semester");
                db_ip->input_db("tt_csv/teacher_info.csv","teacher_info");
                db_ip->input_db("tt_csv/teachers.csv","teachers");
                db_ip->input_db("tt_csv/hrd.csv","hrd");
                db_ip->input_db("tt_csv/maths.csv","maths");

                sch = new schedule();
                sch->initialize_master();
                sch->schedule_hrd_math();

                chview = new choose_view();
                chview->show();
            }
            else
            {
                QMessageBox::critical(this,"Error!","Some files could not be uploaded!\n"
                                                    "Please make sure the files are in proper"
                                                    " format");
            }
        }
    }

}

void input::on_pushButton_clicked()
{
    QApplication::quit();
}

void input::on_pushButton_upload_hrd_clicked()
{
    input_file_name5 = QFileDialog::getOpenFileName(this,"Upload File",QDir::homePath(),tr("Excel Files (*.xlsx *.xls *.ods)"));
    if(!input_file_name5.isNull())
        ui->status_label5->setText(input_file_name5);
    else
        QMessageBox::information(this,"File Uploader","No File Selected");
}

void input::on_pushButton_upload_maths_clicked()
{
    input_file_name6 = QFileDialog::getOpenFileName(this,"Upload File",QDir::homePath(),tr("Excel Files (*.xlsx *.xls *.ods)"));
    if(!input_file_name6.isNull())
        ui->status_label6->setText(input_file_name6);
    else
        QMessageBox::information(this,"File Uploader","No File Selected");
}

void input::on_pushButton_download_hrd_clicked()
{
    QString output_path = QFileDialog::getExistingDirectory(this,"Save templates",QDir::homePath());
    if(output_path.isNull())
        QMessageBox::critical(this,"Error","No Directory selected");
    else
    {
        QString path = "cp tt_templates/hrd.xlsx "+output_path;
        bool ret = system(path.toStdString().c_str());
        if(ret)
            QMessageBox::critical(this,"Download Error","Permission Denied");
        else
            QMessageBox::information(this,"Success","HRD Template Downloaded successfully");
    }
}

void input::on_pushButton_download_maths_clicked()
{
    QString output_path = QFileDialog::getExistingDirectory(this,"Save templates",QDir::homePath());
    if(output_path.isNull())
        QMessageBox::critical(this,"Error","No Directory selected");
    else
    {
        QString path = "cp tt_templates/maths.xlsx "+output_path;
        bool ret = system(path.toStdString().c_str());
        if(ret)
            QMessageBox::critical(this,"Download Error","Permission Denied");
        else
            QMessageBox::information(this,"Success","MATHS Template Downloaded successfully");
    }
}

void input::on_pushButton_upload_semester_clicked()
{
    input_file_name7 = QFileDialog::getOpenFileName(this,"Upload File",QDir::homePath(),tr("Excel Files (*.xlsx *.xls *.ods)"));
    if(!input_file_name7.isNull())
        ui->status_label7->setText(input_file_name7);
    else
        QMessageBox::information(this,"File Uploader","No File Selected");
}

void input::on_pushButton_download_semester_clicked()
{
    QString output_path = QFileDialog::getExistingDirectory(this,"Save templates",QDir::homePath());
    if(output_path.isNull())
        QMessageBox::critical(this,"Error","No Directory selected");
    else
    {
        QString path = "cp tt_templates/semester.xlsx "+output_path;
        bool ret = system(path.toStdString().c_str());
        if(ret)
            QMessageBox::critical(this,"Download Error","Permission Denied");
        else
            QMessageBox::information(this,"Success","SEMESTER Template Downloaded successfully");
    }
}
