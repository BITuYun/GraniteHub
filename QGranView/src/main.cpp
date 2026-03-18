#include <QApplication>
#include "qgranview_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGranViewWindow window;
    window.show();

    return app.exec();
}