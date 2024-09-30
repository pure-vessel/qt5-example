#ifndef PUSHBUTTONITEMDELEGATE_H
#define PUSHBUTTONITEMDELEGATE_H

#include <QHash>
#include <QPushButton>
#include <QStyledItemDelegate>

#include "pushbuttonwithflag.h"

class PushButtonItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit PushButtonItemDelegate(QObject* parent = nullptr);
    virtual PushButtonWithFlag*
    createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
    virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;
};

#endif // PUSHBUTTONITEMDELEGATE_H
