#include "filesystemdirsizemodel.h"

#include <QPushButton>

FileSystemDirSizeModel::FileSystemDirSizeModel(QObject* parent) : QFileSystemModel(parent) {}

int FileSystemDirSizeModel::columnCount(const QModelIndex& parent) const
{
    return QFileSystemModel::columnCount() + 1;
}

QVariant FileSystemDirSizeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || (index.column() != columnCount() - 1 && index.column() != 1))
    {
        return QFileSystemModel::data(index, role);
    }
    if (index.column() == 1)
    {
        if (role != Qt::DisplayRole)
        {
            return {};
        }
        if (!isDir(index))
        {
            return QFileSystemModel::data(index, role);
        }
        else
        {
            if (QHash<QString, quint64>::const_iterator it = dirSizes.find(index.siblingAtColumn(0).data().toString());
                it != dirSizes.end())
            {
                return it.value();
            }
            else
            {
                return {};
            }
        }
    }
    switch (role)
    {
    case Qt::DisplayRole:
        if (!isDir(index))
        {
            return {};
        }
        return QString("click me");
    default:
        return {};
    }
}

Qt::ItemFlags FileSystemDirSizeModel::flags(const QModelIndex& index) const
{
    if (index.column() == columnCount() - 1)
    {
        return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
    }
    else if (index.column() == 1)
    {
        return QFileSystemModel::flags(index) | Qt::ItemIsEditable;
    }
    else
    {
        return QFileSystemModel::flags(index);
    }
}

bool FileSystemDirSizeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (isDir(index) && index.column() == 1 && value.canConvert<quint64>())
    {
        dirSizes.insert(index.siblingAtColumn(0).data().toString(), value.value<quint64>());
        return true;
    }
    else
    {
        return QFileSystemModel::setData(index, value, role);
    }
}
