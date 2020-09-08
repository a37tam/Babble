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

    // Initiate client/server communication
    std::thread t( [&]()
                   {
#ifdef SERVER
                       w.establishService();
#endif

#ifdef CLIENT
                       w.establishConnection();
#endif
                       // Asynchronously read messages
                       w.readMessage();

                       // Run io_context's event loop
                       context->run();
                   }
                 );

    w.show();

    // Run application's event loop
    a.exec();

    t.join();

    return EXIT_SUCCESS;
}
