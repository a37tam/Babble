#ifndef BABBLE_H
#define BABBLE_H

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
    Babble(QWidget *parent = nullptr);
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
};

#endif // BABBLE_H
