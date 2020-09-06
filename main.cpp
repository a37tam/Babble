// Local Headers
#include "babble.h"

// Qt Headers
#include <QApplication>

int main( int argc, char *argv[] )
{
    QApplication a( argc, argv );

    std::shared_ptr<asio::io_context> context = std::make_shared<asio::io_context>();

    Babble w( nullptr, context );

#ifdef SERVER
    w.getSession().establishService();
#endif

#ifdef CLIENT
    w.getSession().establishConnection();
#endif

    // Show GUI
    w.show();

    // Initiate communication. Execute io_context's event loop
    std::thread t( [&w, &context]()
                   {
                       w.getSession().readMessage();
                       w.getSession().sendMessage();
                       context->run();
                   }
                 );

    // Execute application's event loop
    int status = a.exec();

    t.join();

    return EXIT_SUCCESS;
}
