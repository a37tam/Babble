#include "babble.h"
#include "./ui_babble.h"

Babble::Babble(QWidget *parent)
    : QWidget( parent ), mUi( new Ui::Babble ), mModel( new QStringListModel( this ) )
{
    mUi->setupUi(this);

    // Create model
    //mModel = new QStringListModel( this );

    // Glue model and view together
    mUi->listView->setModel( mModel );

    // Prevent editing the items in view
    mUi->listView->setEditTriggers( QAbstractItemView::NoEditTriggers );

    // Give QLineEdit focus on startup
    mUi->lineEdit->setFocus();
}

Babble::~Babble()
{
    delete mModel;
    delete mUi;
}

void Babble::on_sendButton_clicked()
{
    QString message = mUi->lineEdit->text();
    if( !message.isEmpty() )
    {
        sendMessage( message );
        displayMessage( message );

        mUi->lineEdit->clear();
    }
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
}
