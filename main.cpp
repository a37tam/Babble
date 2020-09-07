// Local Headers
#include "babble.h"

// Qt Headers
#include <QApplication>

// Standard Library Headers
#include <thread>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    std::shared_ptr<asio::io_context> context = std::make_shared<asio::io_context>();

    Babble w( nullptr, context );

    std::thread t( [&w, &context]()
                   {
#ifdef SERVER
                       w.establishService();
#endif

#ifdef CLIENT
                       w.establishConnection();
#endif

                       w.readMessage();
                       w.sendMessage();
                       context->run();
                   }
                 );

    w.show();

    int status = a.exec();

    t.join();

    return EXIT_SUCCESS;
}
