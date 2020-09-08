// Local Headers
#include "babble.h"

// Qt Generated Header for GUI. Located in build directory
#include "./ui_babble.h"

// Standard Library Headers
#include <algorithm>
#include <cstdio>
#include <cstdlib>

Babble::Babble( QWidget *parent, std::shared_ptr<asio::io_context> context )
    : QWidget( parent ),
      mUi( new Ui::Babble ),
      mModel( new QStringListModel( this ) ),
      mContext( context ),
      mSocket{ *context },
      mAcceptor{ *context }
{
    mUi->setupUi( this );

    // Glue model and view together
    mUi->listView->setModel( mModel );

    // Prevent displayed messages from being edited
    mUi->listView->setEditTriggers( QAbstractItemView::NoEditTriggers );

    // Give QLineEdit focus on startup
    mUi->lineEdit->setFocus();

    // Disable QPushButton on startup
    mUi->sendButton->setEnabled( false );

    // Resolves "bind: Address already in use" error
    // Allows another socket to bind to the same local endpoint without 
    // having to wait for the OS to fully close the previously bound socket
    asio::socket_base::reuse_address option{ true };

#ifdef SERVER
    mAcceptor.open( asio::ip::tcp::v4() );
    mAcceptor.set_option( option );
#endif

#ifdef CLIENT
    mSocket.open( asio::ip::tcp::v4() );
    mSocket.set_option( option );
#endif
}

Babble::~Babble()
{
    delete mModel;
    delete mUi;
}

void Babble::establishService()
{
        // Construct local endpoint
        asio::ip::tcp::endpoint localEndpoint{ asio::ip::tcp::v4(), defaults::port };

        // Bind acceptor socket to a local endpoint
        mAcceptor.bind( localEndpoint );

        // Listen for incoming connection requests
        // When a request is accepted, pop it off the queue
        mAcceptor.listen( asio::socket_base::max_listen_connections );

        // Establish connection with the client
        mAcceptor.accept( mSocket );
}

void Babble::establishConnection()
{
        // Resolve DNS name
        asio::ip::tcp::resolver resolver( *mContext );
        asio::ip::tcp::resolver::query resolver_query( defaults::server, defaults::service );
        asio::ip::tcp::resolver::iterator endpoints = resolver.resolve( resolver_query );

        // Connect client to the server using any one of the available interfaces
        asio::connect( mSocket, endpoints );
}

void Babble::readMessage()
{
    asio::async_read_until( mSocket,
                            mBuffer,
                            '\n',
                            [&]( const asio::error_code & e, const std::size_t bytes_transferred )
                            {
                                if( e )
                                {
                                    // One side of the connection is terminated
                                    if( e == asio::error::eof )
                                    {
                                        std::printf( "Partner has left the chat.\n" );
                                        
                                        // Invoke QCloseEvent handler (Babble::closeEvent)
                                        close();

                                        return;
                                    }
                                    else if( e == asio::error::operation_aborted )
                                    {
                                        std::printf( "Cancelling async_read_until.\n" );
                                        return;
                                    }
                                    else
                                    {
                                        std::printf( "[Error: %d] %s\n", e.value(), e.message().c_str() );
                                        exit( EXIT_FAILURE );
                                    }
                                }
                                else
                                {
                                    // Extract message from buffer
                                    auto bufs = mBuffer.data();
                                    std::string message( asio::buffers_begin( bufs ),
                                                         asio::buffers_begin( bufs ) + mBuffer.size() );

                                    // Remove trailing newline character
                                    message.erase(std::remove(message.begin(), message.end(), '\n'), message.end());

                                    QString m = QString::fromStdString( message );
                                    displayMessage( m );

                                    // Clear buffer
                                    mBuffer.consume( bytes_transferred );

                                    readMessage();
                                }
                            }
                         );
}

void Babble::sendMessage()
{
    asio::async_write( mSocket,
                       asio::buffer( mMessage + "\n" ),
                       [&]( const asio::error_code & e, const std::size_t bytes_transferred )
                       {
                           if( e )
                           {
                               // All asynchronous operations are cancelled
                               if( e == asio::error::operation_aborted )
                               {
                                    std::printf( "Cancelling async_write call.\n" );
                                    return;
                               }
                               else
                               {
                                   std::printf( "[Error: %d] %s\n", e.value(), e.message().c_str() );
                                   exit( EXIT_FAILURE );
                               }
                           }
                       }
                     );
}

void Babble::displayMessage( const QString & message )
{
    mModel->insertRow( mModel->rowCount() );
    QModelIndex index = mModel->index( mModel->rowCount() - 1, 0 );
    mModel->setData( index, message );
}

void Babble::writeMessage( const QString & message )
{
    mMessage = message.toStdString();
    sendMessage();
}

void Babble::closeEvent( QCloseEvent *event )
{
    // Cancel all asynchronous operations
    mSocket.cancel();

    event->accept();
}

void Babble::on_lineEdit_textChanged( const QString &text )
{
    if( text.isEmpty() )
    {
        mUi->sendButton->setEnabled( false );
    }
    else
    {
        mUi->sendButton->setEnabled( true );
    }
}

void Babble::on_sendButton_clicked()
{
    QString message = mUi->lineEdit->text();

    writeMessage( message );
    displayMessage( message );

    mUi->lineEdit->clear();
}

void Babble::on_lineEdit_returnPressed()
{
    on_sendButton_clicked();
}
