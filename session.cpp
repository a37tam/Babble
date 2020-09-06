// Standard Library Headers
#include <cstdio>
#include <cstdlib>

// Local Headers
#include "session.h"

using asio::ip::tcp;

Session::Session( std::shared_ptr<asio::io_context> context )
    : mSocket( *context ),
      mAcceptor( *context ),
      mContext( context )
{
    // Resolves "bind: Address already in use" error
    asio::socket_base::reuse_address option{ true };

#ifdef CLIENT
    mSocket.open( tcp::v4() );
    mSocket.set_option( option );
#endif

#ifdef SERVER
    mAcceptor.open( tcp::v4() );
    mAcceptor.set_option( option );
#endif
}

void Session::establishConnection()
{
        // Resolve DNS name
        tcp::resolver resolver( *mContext );
        tcp::resolver::query resolver_query( defaults::server, defaults::service );
        tcp::resolver::iterator endpoints = resolver.resolve( resolver_query );

        // Connect to the server using any one of the available interfaces
        asio::connect( mSocket, endpoints );
}

void Session::establishService()
{
        // Construct local endpoint
        tcp::endpoint localEndpoint{ tcp::v4(), defaults::port };

        // Bind acceptor socket to a local endpoint
        mAcceptor.bind( localEndpoint );

        // Listen for incoming connection requests
        // When a request is accepted, pop it off the queue
        mAcceptor.listen( asio::socket_base::max_listen_connections );

        // Establish connection with the client
        mAcceptor.accept( mSocket );
}

void Session::readMessage()
{
    asio::async_read_until( mSocket,
                            mBuffer,
                            '\n',
                            [&]( const asio::error_code & e, const std::size_t bytes_transferred )
                            {
                                if( e )
                                {
                                    if( e == asio::error::eof )
                                    {
                                        std::printf( "Partner has left the chat.\n" );
                                        return;
                                    }
                                    else
                                    {
                                        std::printf( "[Error: %d] %s\n", e.value(), e.message() );
                                        exit( EXIT_FAILURE );
                                    }
                                }
                                else
                                {
                                    // Extract message from buffer
                                    auto bufs = mBuffer.data();
                                    std::string message( asio::buffers_begin( bufs ),
                                                         asio::buffers_begin( bufs ) + mBuffer.size() );

                                    std::printf( "%s\n", message );

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
                               std::printf( "[Error: %d] %s\n", e.value(), e.message() );
                               exit( EXIT_FAILURE );
                           }
                           else
                           {
                               sendMessage();
                           }
                       }
                     );
}
