#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemModel>
#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QString>

#include "filesystemdirsizemodel.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    QFileSystemModel* model() const;
    void setRootPath(const QString& path);

private:
    Ui::MainWindow* ui;
    FileSystemDirSizeModel* fsModel;
    QSortFilterProxyModel* filterModel;

    void filterChanged();

    QString rootPath;
};

#endif // MAINWINDOW_H
