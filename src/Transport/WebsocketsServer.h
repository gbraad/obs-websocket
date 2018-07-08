
#pragma once

#include <libwebsockets.h>
#include <QThread>
#include <QMap>

class WebsocketsServer : QThread
{
Q_OBJECT

public:
	WebsocketsServer(QString protocolName);
	~WebsocketsServer();

	void setPort(int port) {
		this->_port = port;
	}

signals:
	void newClientConnected();

private:
	static int wsCallback(
		struct lws* wsInstance,
		enum lws_callback_reasons reason,
		void* userData,
		void* in,
		size_t len
	);

	void run() override;

	int _port;
	QString _protocolName;
	struct lws_context* _lwsContext;
	QMap<struct lws*, void*> remoteClients;
};
