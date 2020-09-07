#ifndef BABBLE_H
#define BABBLE_H

// Qt Headers
#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>
#include <QCloseEvent>

// Network Programming Headers
#include "asio.hpp"

// Standard Library Headers
#include <memory>
#include <string>

namespace defaults
{
    constexpr short unsigned int port{ 9999 };
    constexpr char service[]{ "Babble" };
    constexpr char server[]{ "localhost" };
}

QT_BEGIN_NAMESPACE
namespace Ui { class Babble; }
QT_END_NAMESPACE

class Babble : public QWidget
{
    Q_OBJECT

public:
    Babble( QWidget *parent, std::shared_ptr<asio::io_context> context );
    ~Babble();

    // Communication
    void establishService();
    void establishConnection();

    // Socket calls
    void readMessage();
    void sendMessage();

private:
    // View
    void displayMessage( const QString & message );
    void writeMessage( const QString & message );

    // Cleanup
    void closeEvent( QCloseEvent * event );

private slots:
    void on_lineEdit_textChanged( const QString & text );
    void on_sendButton_clicked();
    void on_lineEdit_returnPressed();

private:
    // View
    Ui::Babble *mUi;

    // Model
    QStringListModel *mModel;

    // Communication
    std::shared_ptr<asio::io_context> mContext;
    asio::ip::tcp::socket mSocket;
    asio::ip::tcp::acceptor mAcceptor;
    asio::streambuf mBuffer;
    std::string mMessage;
};

#endif // BABBLE_H
