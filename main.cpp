#include "babble.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Babble w;
    w.show();
    return a.exec();
}
