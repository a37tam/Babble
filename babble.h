#ifndef BABBLE_H
#define BABBLE_H

// Local Headers
#include "session.h"

// Qt Headers
#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

// Network Programming Headers
#include <asio.hpp>

// Standard Library Headers
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class Babble; }
QT_END_NAMESPACE

class Babble : public QWidget
{
    Q_OBJECT

public:
    Babble( QWidget *parent, std::shared_ptr<asio::io_context> context );
    ~Babble();

private:
    void displayMessage( const QString & message );
    void sendMessage( const QString & message );

private slots:
    void on_sendButton_clicked();
    void on_lineEdit_returnPressed();

private:
    Ui::Babble *mUi;

    QStringListModel *mModel;

    Session mSession;
};

#endif // BABBLE_H
