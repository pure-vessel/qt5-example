#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemModel>
#include <QMainWindow>
#include <QString>

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
    QFileSystemModel* fsModel;

    void filterChanged();
};

#endif // MAINWINDOW_H
