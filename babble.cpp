// Local Headers
#include "babble.h"
#include "./ui_babble.h"

Babble::Babble( QWidget *parent, std::shared_ptr<asio::io_context> context )
    : QWidget( parent ),
      mUi( new Ui::Babble ),
      mModel( new QStringListModel( this ) ),
      mSession( context )
{
    mUi->setupUi( this );

    // Glue model and view together
    mUi->listView->setModel( mModel );

    // Prevent editing the items in view
    mUi->listView->setEditTriggers( QAbstractItemView::NoEditTriggers );

    // Give QLineEdit focus on startup
    mUi->lineEdit->setFocus();

    // Disable QPushButton on startup
    mUi->sendButton->setEnabled( false );
}

Babble::~Babble()
{
    delete mModel;
    delete mUi;
}

Session& Babble::getSession()
{
    return mSession;
}

void Babble::on_lineEdit_textChanged( const QString &text )
{
    if( message.isEmpty() )
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

    sendMessage( message );
    displayMessage( message );

    mUi->lineEdit->clear();
}

void Babble::on_lineEdit_returnPressed()
{
    on_sendButton_clicked();
}

void Babble::displayMessage( const QString & message )
{
        mModel->insertRow( mModel->rowCount() );
        QModelIndex index = mModel->index( mModel->rowCount() - 1, 0 );
        mModel->setData( index, message );
}

void Babble::sendMessage( const QString & message )
{
    displayMessage( message );

    mSession.mMessage = message.toStdString();
}

void Babble::closeEvent( QCloseEvent *event )
{
    // Cancel all asynchronous operations associated with mSocket
    mSocket.cancel();

    event->accept();
}
