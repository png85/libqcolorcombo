#include <QApplication>

#include "ExampleWindow.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    ExampleWindow w;

    w.show();

    return a.exec();
}
