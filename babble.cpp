#include "babble.h"
#include "./ui_babble.h"

Babble::Babble(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Babble)
{
    ui->setupUi(this);

    // Create model
    model = new QStringListModel( this );

    // Glue model and view together
    ui->listView->setModel( model );

    ui->listView->setEditTriggers( QAbstractItemView::NoEditTriggers );
}

Babble::~Babble()
{
    delete model;
    delete ui;
}

void Babble::on_sendButton_clicked()
{
    QString message = ui->lineEdit->text();
    if( !message.isEmpty() )
    {
        // Add new message to view
        model->insertRow( model->rowCount() );
        QModelIndex index = model->index( model->rowCount() - 1, 0 );
        model->setData( index, message );

        ui->lineEdit->clear();
    }
}

void Babble::on_lineEdit_returnPressed()
{
    on_sendButton_clicked();
}
