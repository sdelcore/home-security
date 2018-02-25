#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QByteArray>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class WebSocketServer : public QObject
{
    Q_OBJECT
public:
    explicit WebSocketServer(quint16 port, bool debug = false, QObject *parent = Q_NULLPTR);
    ~WebSocketServer();

Q_SIGNALS:
    void closed();
    void messageReceived(QString message);

private Q_SLOTS:
    void onNewConnection();
    void onTextMessageRecieved(QString message);
    void processBinaryMessage(QByteArray message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;

};

#endif // WEBSOCKETSERVER_H
