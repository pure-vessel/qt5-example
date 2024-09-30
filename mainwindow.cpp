#include "mainwindow.h"

#include <QDir>
#include <QLineEdit>
#include <QScreen>
#include <QScroller>

#include "filesystemdirsizemodel.h"
#include "pushbuttonitemdelegate.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow),
        fsModel(new FileSystemDirSizeModel(this)),
        filterModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);

    setWindowTitle(QObject::tr("Dir View"));

    // | QDir::NoDotAndDotDot if . and .. should not be shown
    fsModel->setFilter(QDir::AllDirs | QDir::Files | QDir::Hidden);

    filterModel->setSourceModel(fsModel);
    filterModel->setRecursiveFilteringEnabled(true);

    ui->dirView->setModel(filterModel);

    PushButtonItemDelegate* delegate = new PushButtonItemDelegate(ui->dirView);
    ui->dirView->setItemDelegateForColumn(fsModel->columnCount() - 1, delegate);

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
    filterModel->setFilterWildcard(filter);
    // For situations where root did not match filter before
    setRootPath(rootPath);
}

QFileSystemModel* MainWindow::model() const
{
    return fsModel;
}

void MainWindow::setRootPath(const QString& path)
{
    rootPath = path;
    if (!path.isEmpty())
    {
        const QModelIndex sourceIndex = fsModel->index(QDir::cleanPath(path));
        if (sourceIndex.isValid())
        {
            fsModel->setRootPath(path);
            const QModelIndex filteredIndex = filterModel->mapFromSource(sourceIndex);
            if (filteredIndex.isValid())
            {
                ui->dirView->setRootIndex(filteredIndex);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
