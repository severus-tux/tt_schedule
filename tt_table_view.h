#ifndef TT_TABLE_VIEW_H
#define TT_TABLE_VIEW_H

#include <QDialog>
#include <tt_database.h>
//#include <QtPrintSupport/QPrintDialog>
//#include <QtPrintSupport/QPrinter>
//#include <QTextDocument>
//#include <QString>
//#include <QtCore>
//#include <QtGui>

namespace Ui {
class tt_table_view;
}

class tt_table_view : public QDialog
{
    Q_OBJECT

public:
    explicit tt_table_view(QWidget *parent = 0);
    ~tt_table_view();
    void loadtable(int,QString);
    tt_database conn;

private slots:


    void on_pushButton_exit_clicked();

    void on_pushButton_print_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::tt_table_view *ui;
};

#endif // TT_TABLE_VIEW_H
