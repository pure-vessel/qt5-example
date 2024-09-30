#include "pushbuttonitemdelegate.h"

#include <algorithm>
#include <QDebug>
#include <QDirIterator>
#include <QPushButton>
#include <QString>

PushButtonItemDelegate::PushButtonItemDelegate(QObject* parent) : QStyledItemDelegate(parent) {}

PushButtonWithFlag*
PushButtonItemDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index)
        const
{
    PushButtonWithFlag* button = new PushButtonWithFlag(parent);
    connect(button, &QPushButton::clicked, this, [button] { button->set(); });
    return button;
}

void PushButtonItemDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
    PushButtonWithFlag* button = static_cast<PushButtonWithFlag*>(editor);
    if (button->flag)
    {
        QModelIndex filenameIndex = index.siblingAtColumn(0);
        QString filename = "";
        while (filenameIndex.isValid())
        {
            filename = filenameIndex.data().toString() + "/" + filename;
            filenameIndex = filenameIndex.parent();
        }
        filename.remove(0, 1);
        QDirIterator it(filename, QDirIterator::Subdirectories);
        quint64 totalSize = 0;
        while (it.hasNext())
        {
            it.next();
            QFileInfo info = it.fileInfo();
            // qDebug() << info.absoluteFilePath() << '\n';
            totalSize += info.size();
        }
        model->setData(index.siblingAtColumn(1), totalSize);
        button->flag = false;
    }
}
