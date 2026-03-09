#pragma once

#include <QWidget>

class QTreeView;
class QFileSystemModel;

// File browser panel showing .lst/.prl/.prc files.
class FileBrowserPanel : public QWidget {
    Q_OBJECT

public:
    explicit FileBrowserPanel(QWidget *parent = nullptr);

    void setRootPath(const QString &path);

signals:
    void fileDoubleClicked(const QString &filePath);

private:
    QTreeView        *tree_;
    QFileSystemModel *model_;
};
