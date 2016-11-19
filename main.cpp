#include "tt_main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tt_main_window w;
    w.show();

    return a.exec();
}
