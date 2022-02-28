#include "app.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Organization");
    QApplication::setApplicationName("Snake");
    App w;
    w.show();
    return a.exec();
}
