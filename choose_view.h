#ifndef CHOOSE_VIEW_H
#define CHOOSE_VIEW_H

#include <QDialog>
#include "tt_database.h"
#include "tt_table_view.h"

class tt_table_view; // Forward Declaration

namespace Ui {
class choose_view;
}

class choose_view : public QDialog
{
    Q_OBJECT

public:
    explicit choose_view(QWidget *parent = 0);
    ~choose_view();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_radioButton_view_lab_clicked();

    void on_radioButton_view_class_clicked();

    void on_radioButton_view_teacher_clicked();

    void on_radioButton_view_master_clicked();

private:
    Ui::choose_view *ui;
    tt_table_view *tab_view;
    tt_database *con_db;
};

#endif // CHOOSE_VIEW_H
