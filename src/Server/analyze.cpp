#include "analyze.h"
#include "network.h"
#include "server.h"

using namespace NetworkServ;

Analyzer::Analyzer(QTcpSocket *sock) : mysocket(sock)
{
    connect(&socket(), SIGNAL(disconnected()), SIGNAL(disconnected()));
    connect(&socket(), SIGNAL(isFull(QByteArray)), this, SLOT(commandReceived(QByteArray)));
    connect(&socket(), SIGNAL(_error()), this, SLOT(error()));
    connect(this, SIGNAL(sendCommand(QByteArray)), &socket(), SLOT(send(QByteArray)));
}

void Analyzer::sendMessage(const QString &message)
{
    QByteArray tosend;
    QDataStream out(&tosend, QIODevice::WriteOnly);

    out << uchar(SendMessage) << message;

    emit sendCommand(tosend);
}

void Analyzer::error()
{
    emit connectionError(socket().error(), socket().errorString());
}

void Analyzer::commandReceived(const QByteArray &commandline)
{
    QDataStream in (commandline);
    uchar command;

    in >> command;

    switch (command) {
	case Login:
	{
	    QString name;
	    in >> name;
	    emit loggedIn(name);
	    break;
	}
	case SendMessage:
	{
	    QString mess;
	    in >> mess;
	    emit messageReceived(mess);
	    break;
	}
	default:
	    emit protocolError(UnknownCommand, tr("Protocol error: unknown command received"));
	    break;
    }
}

Network & Analyzer::socket()
{
    return mysocket;
}