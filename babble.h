#ifndef BABBLE_H
#define BABBLE_H

// Local Headers
#include "session.h"

// Qt Headers
#include <QWidget>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

QT_BEGIN_NAMESPACE
namespace Ui { class Babble; }
QT_END_NAMESPACE

class Babble : public QWidget
{
    Q_OBJECT

public:
    Babble( QWidget *parent, std::shared_ptr<asio::io_context> context );
    ~Babble();

    Session& getSession();

private:
    void displayMessage( const QString & message );

    void sendMessage( const QString & message );

    void closeEvent( QCloseEvent *event )

private slots:
    void on_sendButton_clicked();
    void on_lineEdit_returnPressed();

private:
    // View
    Ui::Babble *mUi;

    // Model
    QStringListModel *mModel;

    // Handles communication
    Session mSession;
};

#endif // BABBLE_H
