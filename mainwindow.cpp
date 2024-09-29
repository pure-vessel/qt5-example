#include "mainwindow.h"

#include <QDir>
#include <QLineEdit>
#include <QScreen>
#include <QScroller>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        fsModel(new QFileSystemModel(this))
{
    ui->setupUi(this);

    setWindowTitle(QObject::tr("Dir View"));

    fsModel->setNameFilterDisables(false);
    // | QDir::NoDotAndDotDot if . and .. should not be shown
    fsModel->setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden);

    ui->dirView->setModel(fsModel);

    // Demonstrating look and feel features
    ui->dirView->setAnimated(false);
    ui->dirView->setIndentation(20);
    ui->dirView->setSortingEnabled(true);
    const QSize availableSize = ui->dirView->screen()->availableGeometry().size();
    ui->dirView->resize(availableSize / 2);
    ui->dirView->setColumnWidth(0, ui->dirView->width() / 3);

    // Make it flickable on touchscreens
    QScroller::grabGesture(ui->dirView, QScroller::TouchGesture);

    connect(ui->filterLine, &QLineEdit::textChanged, this, &MainWindow::filterChanged);
}

void MainWindow::filterChanged()
{
    QString filter = ui->filterLine->text();
    if (filter.isEmpty())
    {
        filter = "*";
    }
    fsModel->setNameFilters({filter});
}

QFileSystemModel* MainWindow::model() const
{
    return fsModel;
}

void MainWindow::setRootPath(const QString& path)
{
    if (!path.isEmpty())
    {
        const QModelIndex rootIndex = fsModel->index(QDir::cleanPath(path));
        if (rootIndex.isValid())
        {
            ui->dirView->setRootIndex(rootIndex);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
