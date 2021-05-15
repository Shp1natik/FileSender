#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include "ui_clientform.h"
#include <QTcpSocket>
#include "QHostAddress"

class ClientForm:public QWidget, private Ui::ClientForm
{
    Q_OBJECT
public:
    explicit ClientForm(QWidget *parent=0);
    virtual ~ClientForm();
private:
    QTcpSocket *pTcpSocket;
public slots:
    void readyRead();
};

#endif // CLIENTFORM_H
