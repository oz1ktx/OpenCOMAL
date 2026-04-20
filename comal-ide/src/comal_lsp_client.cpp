#include "comal_lsp_client.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonParseError>

ComalLspClient::ComalLspClient(QObject *parent)
    : QObject(parent), lspProcess_(nullptr), nextRequestId_(1) {}

ComalLspClient::~ComalLspClient() {
    stopServer();
}

void ComalLspClient::startServer(const QString &programPath) {
    if (lspProcess_) return;
    lspProcess_ = new QProcess(this);
    readBuffer_.clear();
    pendingRequests_.clear();
    nextRequestId_ = 1;
    connect(lspProcess_, &QProcess::readyReadStandardOutput, this, &ComalLspClient::handleServerOutput);
    connect(lspProcess_, &QProcess::readyReadStandardError, this, &ComalLspClient::handleServerError);
    lspProcess_->start(programPath);

    if (!lspProcess_->waitForStarted(3000)) {
        qWarning() << "LSP failed to start:" << programPath << lspProcess_->errorString();
        lspProcess_->deleteLater();
        lspProcess_ = nullptr;
        return;
    }
    qDebug() << "LSP started:" << programPath << "pid" << lspProcess_->processId();
    
    // Send LSP initialize request
    const int initId = nextRequestId_++;
    QJsonObject initParams;
    initParams["processId"] = QJsonValue();  // null
    initParams["rootPath"] = QJsonValue();   // null
    initParams["rootUri"] = QJsonValue();    // null
    initParams["capabilities"] = QJsonObject{};
    QJsonObject initRequest{{"jsonrpc", "2.0"}, {"id", initId}, {"method", "initialize"}, {"params", initParams}};
    pendingRequests_.insert(initId, PendingRequest{"initialize", ""});
    sendRequest(initRequest);
}

void ComalLspClient::stopServer() {
    if (lspProcess_) {
        lspProcess_->kill();
        lspProcess_->waitForFinished(3000);  // Wait up to 3 seconds for graceful shutdown
        lspProcess_->deleteLater();
        lspProcess_ = nullptr;
    }
    readBuffer_.clear();
    pendingRequests_.clear();
}

void ComalLspClient::sendDidOpen(const QString &filePath, const QString &text) {
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}, {"text", text}};
    QJsonObject notification{{"jsonrpc", "2.0"}, {"method", "textDocument/didOpen"}, {"params", params}};
    sendNotification(notification);
}

void ComalLspClient::sendDidChange(const QString &filePath, const QString &text) {
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}};
    params["contentChanges"] = QJsonArray{QJsonObject{{"text", text}}};
    QJsonObject notification{{"jsonrpc", "2.0"}, {"method", "textDocument/didChange"}, {"params", params}};
    sendNotification(notification);
}

void ComalLspClient::sendDidClose(const QString &filePath) {
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}};
    QJsonObject notification{{"jsonrpc", "2.0"}, {"method", "textDocument/didClose"}, {"params", params}};
    sendNotification(notification);
}

void ComalLspClient::requestCompletion(const QString &filePath, int line, int character) {
    const int requestId = nextRequestId_++;
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}};
    params["position"] = QJsonObject{{"line", line}, {"character", character}};
    QJsonObject request{{"jsonrpc", "2.0"}, {"id", requestId}, {"method", "textDocument/completion"}, {"params", params}};
    pendingRequests_.insert(requestId, PendingRequest{"textDocument/completion", filePath});
    sendRequest(request);
}

void ComalLspClient::requestHover(const QString &filePath, int line, int character) {
    const int requestId = nextRequestId_++;
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}};
    params["position"] = QJsonObject{{"line", line}, {"character", character}};
    QJsonObject request{{"jsonrpc", "2.0"}, {"id", requestId}, {"method", "textDocument/hover"}, {"params", params}};
    pendingRequests_.insert(requestId, PendingRequest{"textDocument/hover", filePath});
    sendRequest(request);
}

void ComalLspClient::requestDefinition(const QString &filePath, int line, int character) {
    const int requestId = nextRequestId_++;
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}};
    params["position"] = QJsonObject{{"line", line}, {"character", character}};
    QJsonObject request{{"jsonrpc", "2.0"}, {"id", requestId}, {"method", "textDocument/definition"}, {"params", params}};
    pendingRequests_.insert(requestId, PendingRequest{"textDocument/definition", filePath});
    sendRequest(request);
}

void ComalLspClient::sendRequest(const QJsonObject &request) {
    if (!lspProcess_) return;
    QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    QByteArray message = QString("Content-Length: %1\r\n\r\n").arg(data.size()).toUtf8() + data;
    qDebug() << "LSP: Sending request:" << request.value("method") << "ID:" << request.value("id");
    lspProcess_->write(message);
    lspProcess_->waitForBytesWritten(1000);
}

void ComalLspClient::sendNotification(const QJsonObject &notification) {
    if (!lspProcess_) return;
    QByteArray data = QJsonDocument(notification).toJson(QJsonDocument::Compact);
    QByteArray message = QString("Content-Length: %1\r\n\r\n").arg(data.size()).toUtf8() + data;
    qDebug() << "LSP: Sending notification:" << notification.value("method");
    lspProcess_->write(message);
    lspProcess_->waitForBytesWritten(1000);
}

void ComalLspClient::handleServerOutput() {
    if (!lspProcess_) return;
    readBuffer_.append(lspProcess_->readAllStandardOutput());

    while (true) {
        const int headerEnd = readBuffer_.indexOf("\r\n\r\n");
        if (headerEnd < 0) {
            break;
        }

        const QByteArray headers = readBuffer_.left(headerEnd);
        const int contentLength = parseContentLength(headers);
        if (contentLength < 0) {
            qWarning() << "LSP: missing Content-Length header";
            readBuffer_.remove(0, headerEnd + 4);
            continue;
        }

        const int bodyStart = headerEnd + 4;
        if (readBuffer_.size() < bodyStart + contentLength) {
            break;
        }

        const QByteArray payload = readBuffer_.mid(bodyStart, contentLength);
        readBuffer_.remove(0, bodyStart + contentLength);

        QJsonParseError error;
        const QJsonDocument doc = QJsonDocument::fromJson(payload, &error);
        if (error.error != QJsonParseError::NoError || !doc.isObject()) {
            qWarning() << "LSP: invalid JSON payload" << error.errorString() << payload;
            continue;
        }

        handleMessage(doc.object());
    }
}

void ComalLspClient::handleServerError() {
    if (!lspProcess_) return;
    QByteArray error = lspProcess_->readAllStandardError();
    qDebug() << "LSP error:" << error;
}

int ComalLspClient::parseContentLength(const QByteArray &headers) const {
    const QList<QByteArray> lines = headers.split('\n');
    for (QByteArray line : lines) {
        line = line.trimmed();
        if (line.startsWith("Content-Length:")) {
            const QByteArray value = line.mid(QByteArray("Content-Length:").size()).trimmed();
            bool ok = false;
            const int length = value.toInt(&ok);
            if (ok && length >= 0) {
                return length;
            }
            return -1;
        }
    }
    return -1;
}

void ComalLspClient::handleMessage(const QJsonObject &message) {
    const QString method = message.value("method").toString();
    if (!method.isEmpty()) {
        qDebug() << "LSP: Received notification:" << method;
        if (method == "textDocument/publishDiagnostics") {
            const QJsonObject params = message.value("params").toObject();
            const QString filePath = params.value("uri").toString();
            qDebug() << "LSP: Diagnostics for" << filePath << "count:" << params.value("diagnostics").toArray().size();
            emit diagnosticsReceived(filePath, params);
            return;
        }
        return;
    }

    const QJsonValue idValue = message.value("id");
    if (!idValue.isDouble()) {
        return;
    }

    const int id = idValue.toInt();
    auto it = pendingRequests_.find(id);
    if (it == pendingRequests_.end()) {
        return;
    }

    const PendingRequest pending = it.value();
    pendingRequests_.erase(it);

    qDebug() << "LSP: Response for" << pending.method << "ID:" << id;

    if (message.contains("error")) {
        qWarning() << "LSP request failed" << pending.method << message.value("error");
        return;
    }

    // Handle initialize response
    if (pending.method == "initialize") {
        qDebug() << "LSP initialized, sending initialized notification";
        // Send initialized notification
        QJsonObject initializedNotif{{"jsonrpc", "2.0"}, {"method", "initialized"}, {"params", QJsonObject{}}};
        sendNotification(initializedNotif);
        return;
    }

    const QJsonValue result = message.value("result");
    if (pending.method == "textDocument/hover") {
        QJsonObject hover;
        if (result.isObject()) {
            hover = result.toObject();
        }
        emit hoverReceived(pending.filePath, hover);
        return;
    }

    if (pending.method == "textDocument/completion") {
        QJsonObject completion;
        if (result.isObject()) {
            completion = result.toObject();
        } else if (result.isArray()) {
            completion.insert("items", result.toArray());
        }
        emit completionReceived(pending.filePath, completion);
        return;
    }

    if (pending.method == "textDocument/definition") {
        QJsonObject definition;
        if (result.isObject()) {
            definition = result.toObject();
        } else if (result.isArray()) {
            definition.insert("locations", result.toArray());
        }
        emit definitionReceived(pending.filePath, definition);
        return;
    }
}
