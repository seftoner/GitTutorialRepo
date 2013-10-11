#include <QApplication>
#include "Core/ProgramInit.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    app.setApplicationName("GetInfo");
    app.setOrganizationName("Eleks");
    app.setOrganizationDomain("eleks.com");

    ProgramInit program;

    if(!program.execute())
    {
        return 1;
    }

    return app.exec();

}
