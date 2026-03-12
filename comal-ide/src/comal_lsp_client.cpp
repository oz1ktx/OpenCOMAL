#include "comal_lsp_client.h"
#include <QDebug>
#include <QJsonArray>

ComalLspClient::ComalLspClient(QObject *parent)
    : QObject(parent), lspProcess_(nullptr), nextRequestId_(1) {}

ComalLspClient::~ComalLspClient() {
    stopServer();
}

void ComalLspClient::startServer(const QString &programPath) {
    if (lspProcess_) return;
    lspProcess_ = new QProcess(this);
    connect(lspProcess_, &QProcess::readyReadStandardOutput, this, &ComalLspClient::handleServerOutput);
    connect(lspProcess_, &QProcess::readyReadStandardError, this, &ComalLspClient::handleServerError);
    lspProcess_->start(programPath);
}

void ComalLspClient::stopServer() {
    if (lspProcess_) {
        lspProcess_->kill();
        lspProcess_->deleteLater();
        lspProcess_ = nullptr;
    }
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
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}};
    params["position"] = QJsonObject{{"line", line}, {"character", character}};
    QJsonObject request{{"jsonrpc", "2.0"}, {"id", nextRequestId_++}, {"method", "textDocument/completion"}, {"params", params}};
    sendRequest(request);
}

void ComalLspClient::requestHover(const QString &filePath, int line, int character) {
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}};
    params["position"] = QJsonObject{{"line", line}, {"character", character}};
    QJsonObject request{{"jsonrpc", "2.0"}, {"id", nextRequestId_++}, {"method", "textDocument/hover"}, {"params", params}};
    sendRequest(request);
}

void ComalLspClient::requestDefinition(const QString &filePath, int line, int character) {
    QJsonObject params;
    params["textDocument"] = QJsonObject{{"uri", filePath}};
    params["position"] = QJsonObject{{"line", line}, {"character", character}};
    QJsonObject request{{"jsonrpc", "2.0"}, {"id", nextRequestId_++}, {"method", "textDocument/definition"}, {"params", params}};
    sendRequest(request);
}

void ComalLspClient::sendRequest(const QJsonObject &request) {
    if (!lspProcess_) return;
    QByteArray data = QJsonDocument(request).toJson(QJsonDocument::Compact);
    lspProcess_->write(data + "\n");
}

void ComalLspClient::sendNotification(const QJsonObject &notification) {
    if (!lspProcess_) return;
    QByteArray data = QJsonDocument(notification).toJson(QJsonDocument::Compact);
    lspProcess_->write(data + "\n");
}

void ComalLspClient::handleServerOutput() {
    if (!lspProcess_) return;
    QByteArray output = lspProcess_->readAllStandardOutput();
    // TODO: Parse JSON, emit signals for diagnostics/completion/hover/definition
    qDebug() << "LSP output:" << output;
}

void ComalLspClient::handleServerError() {
    if (!lspProcess_) return;
    QByteArray error = lspProcess_->readAllStandardError();
    qDebug() << "LSP error:" << error;
}
