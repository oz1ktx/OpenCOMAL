#include "qt_io.h"

QtIO::QtIO(QObject *parent)
    : QObject(parent)
{
}

void QtIO::print(const std::string &text)
{
    QString qtext = QString::fromStdString(text);
    emit textOutput(qtext);

    // Track text since last newline for the input prompt hint
    QMutexLocker lock(&inputMutex_);
    int lastNl = qtext.lastIndexOf('\n');
    if (lastNl >= 0)
        pendingPrompt_ = qtext.mid(lastNl + 1);
    else
        pendingPrompt_ += qtext;
}

std::string QtIO::readLine()
{
    QString prompt;
    {
        QMutexLocker lock(&inputMutex_);
        prompt = pendingPrompt_;
        pendingPrompt_.clear();
    }
    emit inputRequested(prompt);

    QMutexLocker lock(&inputMutex_);
    while (!inputAvailable_)
        inputReady_.wait(&inputMutex_);

    inputAvailable_ = false;
    return inputLine_.toStdString();
}

void QtIO::clearScreen()
{
    emit screenCleared();
}

void QtIO::setCursor(int row, int col)
{
    emit cursorMoved(row, col);
}

void QtIO::provideInput(const QString &line)
{
    QMutexLocker lock(&inputMutex_);
    inputLine_ = line;
    inputAvailable_ = true;
    inputReady_.wakeOne();
}
