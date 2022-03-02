#include "app.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Organization");
    QApplication::setApplicationName("Snake");

    App w;

    QFile stylesheet_file("../game/stylesheet.qss");
    stylesheet_file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(stylesheet_file.readAll());
    a.setStyleSheet(stylesheet);

    w.show();
    return a.exec();
}
