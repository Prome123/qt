#include "echoServer.h"
#include <QTcpSocket>
#include <qDebug>

EchoServer::EchoServer(QObject *parent)
    : QTcpServer(parent)
{
    connect(this, SIGNAL(newConnection()),
            this, SLOT(onNewConnection()));
}

EchoServer::~EchoServer()
{
}

void EchoServer::onNewConnection()
{
    while(hasPendingConnections())
    {
        qDebug() << QLatin1String("onNewConnection");
        QTcpSocket *sock = nextPendingConnection();
        connect(sock, SIGNAL(readyRead()),
                this, SLOT(onReadyRead()));
        connect(sock, SIGNAL(disconnected()),
                this, SLOT(deleteLater()));
        if (sock->bytesAvailable() > 0)
        {
            echo(sock);
        }
    }
}

void EchoServer::onReadyRead()
{
    QTcpSocket *sock = qobject_cast<QTcpSocket*>(sender());
    qDebug() << QLatin1String("onReadyRead");
    echo(sock);
}

void EchoServer::echo(QTcpSocket *sock)
{
    QByteArray inData = sock->readAll();
    qDebug() << inData;
    sock->write(inData);
    sock->flush();
}

