 #pragma once
#include <QObject>
#include <QString>
#include <QProcess>
#include <QByteArray>
#include <QHash>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextCursor>

// COMAL LSP client for IDE integration
class ComalLspClient : public QObject {
    Q_OBJECT
public:
    explicit ComalLspClient(QObject *parent = nullptr);
    ~ComalLspClient();

    // Start LSP server process
    void startServer(const QString &programPath);
    // Stop LSP server process
    void stopServer();

    // Send document open/change/close events
    void sendDidOpen(const QString &filePath, const QString &text);
    void sendDidChange(const QString &filePath, const QString &text);
    void sendDidClose(const QString &filePath);

    // Request completion, hover, definition
    void requestCompletion(const QString &filePath, int line, int character);
    void requestHover(const QString &filePath, int line, int character);
    void requestDefinition(const QString &filePath, int line, int character);

signals:
    // Diagnostics, completion, hover, definition results
    void diagnosticsReceived(const QString &filePath, const QJsonObject &diagnostics);
    void completionReceived(const QString &filePath, const QJsonObject &completion);
    void hoverReceived(const QString &filePath, const QJsonObject &hover);
    void definitionReceived(const QString &filePath, const QJsonObject &definition);

private slots:
    void handleServerOutput();
    void handleServerError();

private:
    struct PendingRequest {
        QString method;
        QString filePath;
    };

    QProcess *lspProcess_;
    int nextRequestId_;
    QByteArray readBuffer_;
    QHash<int, PendingRequest> pendingRequests_;

    int parseContentLength(const QByteArray &headers) const;
    void handleMessage(const QJsonObject &message);
    void sendRequest(const QJsonObject &request);
    void sendNotification(const QJsonObject &notification);
};
