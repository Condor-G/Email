#ifndef BUTTONDELEGATE_H
#define BUTTONDELEGATE_H

#include <QObject>
#include <QItemDelegate>
#include <QPushButton>
#include <QModelIndex>
#include <QFileDialog>
#include <QAbstractItemModel>
#include <QDebug>
#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>
#include "receiver.h"


class ButtonDelegate: public QStyledItemDelegate
{
public:
    explicit ButtonDelegate(QWidget *parent = 0);

private slots:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

private:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index)const;


    QRect CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const;

};

#endif // BUTTONDELEGATE_H
