#include "echo_server.h"
#include <QHostAddress>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>

EchoServer::EchoServer(QObject *parent)
    : QTcpServer(parent)
{
    // 서버에 새 연결이 들어오면 슬롯으로 연결
    connect(this, &QTcpServer::newConnection,
            this, &EchoServer::onNewConnection);
}

void EchoServer::startListening(quint16 port)
{
    if (isListening()) {
        qDebug() << "Server is already listening.";
        return;
    }

    // 모든 인터페이스에서 접속 허용
    if (listen(QHostAddress::Any, port)) {
        qDebug() << "Server started and listening on port" << port;
        emit runningChanged();
    } else {
        qCritical() << "Server failed to start:" << errorString();
    }
}

void EchoServer::stopServer()
{
    if (!isListening()) {
        qDebug() << "Server is not running.";
        return;
    }

    qDebug() << "Stopping server...";


    for (QTcpSocket* client : m_clients) {
        if (client) {
            client->disconnectFromHost();
            client->deleteLater();
        }
    }
    m_clients.clear();

    close();
    emit runningChanged();

    qDebug() << "Server stopped.";
}

void EchoServer::onNewConnection()
{
    QTcpSocket *newClientSocket = nextPendingConnection();

    connect(newClientSocket, &QTcpSocket::readyRead,
            this, &EchoServer::onReadyRead);
    connect(newClientSocket, &QTcpSocket::disconnected,
            this, &EchoServer::onClientDisconnected);

    m_clients.append(newClientSocket);

    qDebug() << "Client connected from:"
             << newClientSocket->peerAddress().toString();

    emit clientConnected(newClientSocket->peerAddress().toString(),
                         newClientSocket->peerPort());
}

void EchoServer::onReadyRead()
{
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket*>(sender());
    if (!senderSocket) return;

    QByteArray data = senderSocket->readAll();
    qDebug() << "[SERVER RAW]" << data;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);

    if (err.error != QJsonParseError::NoError) {
        qWarning() << "[JSON ERROR]" << err.errorString();
        return;
    }

    if (!doc.isObject()) {
        qWarning() << "[JSON] Not an object";
        return;
    }

    QJsonObject obj = doc.object();

    qDebug() << "[JSON OK]"
             << QJsonDocument(obj).toJson(QJsonDocument::Compact);

    emit jsonReceived(senderSocket->peerAddress().toString(), doc);
}

void EchoServer::onClientDisconnected()
{
    QTcpSocket *disconnectedSocket = qobject_cast<QTcpSocket*>(sender());
    if (!disconnectedSocket) return;

    m_clients.removeOne(disconnectedSocket);

    qDebug() << "Client disconnected:"
             << disconnectedSocket->peerAddress().toString();

    emit clientDisconnected(disconnectedSocket->peerAddress().toString(),
                            disconnectedSocket->peerPort());

    disconnectedSocket->deleteLater();
}
