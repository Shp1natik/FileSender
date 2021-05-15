#include "clientform.h"
ClientForm::ClientForm(QWidget *parent):
    QWidget(parent)
{
    setupUi(this);
    setWindowTitle("Клиент");
    //создаем сокет
    pTcpSocket = new QTcpSocket(this);
    //биндим сокет на заданную пару ip и порт
    if (pTcpSocket->bind(QHostAddress::LocalHost)) lblSocketState->setText("binded");
    //установка соединения с сервером по нажатию кнопки
    connect(btnReceiveFile,&QToolButton::clicked,[=](){
        pTcpSocket->connectToHost(QHostAddress::LocalHost,13303);
    });
    //когда соединение с сервером будет установлено, сокет отправит сигнал, тогда клиент
    //шлёт серверу название файла, которое должно быть отправлено
    connect(pTcpSocket,&QTcpSocket::connected, this,[&](){
        lblSocketState->setText("connected");
        lblFileName->setText("ui_clientform.h");
        QByteArray ba ("ui_clientform.h");
        pTcpSocket->write(ba);
        lblExchange->setText("Filename sended");
    });
    connect(pTcpSocket,SIGNAL(readyRead()),SLOT(readyRead()));

}
ClientForm::~ClientForm()
{
    pTcpSocket->close();
}
void ClientForm::readyRead()
{
    textBrowser->setText(pTcpSocket->readAll());
    lblExchange->setText("file received");
    pTcpSocket->close();
}
