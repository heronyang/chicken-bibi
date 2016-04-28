#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setWindowIcon(QIcon(":/icon"));
    a.setApplicationName("Bibi");
    a.setOrganizationDomain("heron.me");
    w.show();

    return a.exec();
}
