#ifndef FILESYSTEMDIRSIZEMODEL_H
#define FILESYSTEMDIRSIZEMODEL_H

#include <QFileSystemModel>
#include <QHash>

class FileSystemDirSizeModel : public QFileSystemModel
{
public:
    explicit FileSystemDirSizeModel(QObject* parent = nullptr);

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex& index, int role) const override;

    virtual Qt::ItemFlags flags(const QModelIndex& index) const override;

    virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

private:
    QHash<QString, quint64> dirSizes;
};

#endif // FILESYSTEMDIRSIZEMODEL_H
