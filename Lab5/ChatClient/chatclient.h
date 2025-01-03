#ifndef CHARCLIENT_H
#define CHARCLIENT_H

#include <QObject>
#include <QTcpSocket>

class ChatClient : public QObject
{
    Q_OBJECT
public:
    explicit ChatClient(QObject *parent = nullptr);

signals:
    void connected();
    void messageReceived(const QString &text);
    void jsonReceived(const QJsonObject &docObj);

public slots:
    void onReadyRead();
    void sendMessage(const QString &text,const QString &type = "message");
    void connectToServer(const QHostAddress &address,quint16 port);
    void disconnectFromHost();

private:
    QTcpSocket *m_clientSocket;
};

#endif // CHARCLIENT_H
