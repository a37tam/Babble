// Local Headers
#include "babble.h"

// Qt Headers
#include <QApplication>

// Network Programming Headers
#include <asio.hpp>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    std::shared_ptr<asio::io_context> context = std::make_shared<asio::io_context>();

    Babble w( nullptr, context );
    w.show();

    return a.exec();
}
