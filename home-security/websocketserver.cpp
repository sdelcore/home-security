#include "websocketserver.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

WebSocketServer::WebSocketServer(quint16 port, bool debug, QObject *parent)
    : QObject(parent),
      m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Server"), QWebSocketServer::NonSecureMode, this)),
      m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::Any, port))
    {
        if (m_debug)
            qDebug() << "WebSocketServer listening on port" << port;

        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &WebSocketServer::closed);
    }
}

WebSocketServer::~WebSocketServer()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void WebSocketServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    if(m_debug)
    {
        qDebug() << "New client: " << pSocket;
        connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageRecieved);
        connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::processBinaryMessage);
    }
    else
        connect(pSocket, &QWebSocket::textMessageReceived, this, &WebSocketServer::messageReceived);

    connect(pSocket, &QWebSocket::disconnected, this, &WebSocketServer::socketDisconnected);

    m_clients << pSocket;
}

void WebSocketServer::processBinaryMessage(QByteArray message)
{
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
}

void WebSocketServer::onTextMessageRecieved(QString message)
{
    qDebug() << message;
    emit messageReceived(message);
}

void WebSocketServer::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());

    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;

    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
