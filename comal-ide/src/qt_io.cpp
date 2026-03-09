#include "qt_io.h"

QtIO::QtIO(QObject *parent)
    : QObject(parent)
{
}

void QtIO::print(const std::string &text)
{
    emit textOutput(QString::fromStdString(text));
}

std::string QtIO::readLine()
{
    emit inputRequested();

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
