#include "file_browser_panel.h"

#include <QVBoxLayout>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDir>

FileBrowserPanel::FileBrowserPanel(QWidget *parent)
    : QWidget(parent)
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    model_ = new QFileSystemModel(this);
    model_->setNameFilters({"*.lst", "*.prl", "*.prc", "*.cml"});
    model_->setNameFilterDisables(false);   // hide non-matching files

    tree_ = new QTreeView(this);
    tree_->setModel(model_);
    // Show only name column by default
    tree_->setColumnHidden(1, true);   // size
    tree_->setColumnHidden(2, true);   // type
    tree_->setColumnHidden(3, true);   // date
    tree_->setHeaderHidden(true);

    layout->addWidget(tree_);

    // Default: show current directory
    setRootPath(QDir::currentPath());
}

void FileBrowserPanel::setRootPath(const QString &path)
{
    auto root = model_->setRootPath(path);
    tree_->setRootIndex(root);
}
