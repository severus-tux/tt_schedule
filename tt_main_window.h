#ifndef TT_MAIN_WINDOW_H
#define TT_MAIN_WINDOW_H

#include <QMainWindow>
#include <choose_view.h>
#include <input.h>
#include <tt_database.h>
#include <tt_table_view.h>

namespace Ui {
class tt_main_window;
}

class tt_main_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit tt_main_window(QWidget *parent = 0);
    QString db_path;
    ~tt_main_window();


private slots:

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::tt_main_window *ui;
    choose_view *chooseview;
    input *input_data;
    tt_database *db_create;

};

#endif // TT_MAIN_WINDOW_H
