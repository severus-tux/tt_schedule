#ifndef INPUT_H
#define INPUT_H

#include <QDialog>
#include "tt_database.h"
#include "choose_view.h"
#include "schedule.h"

namespace Ui {
class input;
}

class input : public QDialog
{
    Q_OBJECT

public:
    explicit input(QWidget *parent = 0);
    ~input();

private slots:
    void on_pushButton_upload_subject_clicked();

    void on_pushButton_upload_class_clicked();

    void on_pushButton_upload_teacher_clicked();

    void on_pushButton_upload_teacherinfo_clicked();

    void on_pushButton_download_subject_clicked();

    void on_pushButton_download_class_clicked();

    void on_pushButton_download_teacher_clicked();

    void on_pushButton_download_teacherinfo_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_clicked();

    void on_pushButton_upload_hrd_clicked();

    void on_pushButton_upload_maths_clicked();

    void on_pushButton_download_hrd_clicked();

    void on_pushButton_download_maths_clicked();

    void on_pushButton_upload_semester_clicked();

    void on_pushButton_download_semester_clicked();


private:
    Ui::input *ui;
    QString input_file_name1,input_file_name2,input_file_name3;
    QString input_file_name4,input_file_name5,input_file_name6,input_file_name7;
    tt_database *db_ip;
    choose_view *chview;
    schedule *sch;
};

#endif // INPUT_H
