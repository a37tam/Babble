#ifndef SESSION_H
#define SESSION_H

// Network Programming Headers
#include <asio.hpp>

// Standard Library Headers
#include <memory>
#include <string>

namespace defaults
{
    constexpr short unsigned int port{ 9999 };
    constexpr char service[]{ "Babble" };
    constexpr char server[]{ "localhost" };
}

class Session
{
    public:
        Session( std::shared_ptr<asio::io_context> context );
        void establishConnection();
        void establishService();
        void readMessage();
        void sendMessage();

    private:
        asio::ip::tcp::socket mSocket;
        asio::ip::tcp::acceptor mAcceptor;
        std::shared_ptr<asio::io_context> mContext;
        asio::streambuf mBuffer;
        std::string mMessage;
};

#endif // SESSION_H
