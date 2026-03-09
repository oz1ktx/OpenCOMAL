#include "main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("OpenCOMAL IDE");
    app.setOrganizationName("OpenCOMAL");

    MainWindow window;
    window.show();

    return app.exec();
}
