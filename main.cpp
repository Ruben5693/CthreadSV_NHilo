#include <QtGui/QApplication>
#include "hebras.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    hebras foo;
    foo.show();
    return app.exec();
    
}
