#include "buttondelegate.h"


ButtonDelegate::ButtonDelegate(QWidget *parent) :
    QStyledItemDelegate(parent)
{

}

void ButtonDelegate::paint(QPainter * painter,
                           const QStyleOptionViewItem & option,
                           const QModelIndex & index) const
{
    if (index.column() == 0)
       {
           //获取值
           bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
           //按钮的风格选项
           QStyleOptionButton *checkBoxOption = new QStyleOptionButton();
           checkBoxOption->state |= QStyle::State_Enabled;
           //根据值判断是否选中
           if(checked){
               checkBoxOption->state |= QStyle::State_On;
           }
           else{
               checkBoxOption->state |= QStyle::State_Off;
           }
           //返回QCheckBox几何形状
           checkBoxOption->rect = CheckBoxRect(option);
           //绘制QCheckBox
           QApplication::style()->drawControl(QStyle::CE_CheckBox,checkBoxOption,painter);

       }
    else if(index.column()==3){
        QPixmap  star;
        if(index.data().toString()=="yes") star.load(":/img/img/red_star.png");
        else if(index.data().toString()=="no") star.load(":/img/img/gray_star.png");

        int width=star.width();
        int height=star.height();
        QRect rect=option.rect;
        int x=rect.x()+rect.width()/2-width/2;
        int y=rect.y()+rect.height()/2-height/2;

        painter->drawPixmap(x,y,star);
    }
    else if(index.column()==1){
        bool b;
        if(index.data().toString()=="no") b = true;
        else if(index.data().toString()=="yes") b= false;
        QPixmap  star;
        if(b) star=QPixmap(":/img/img/unread.png");
        int width=star.width();
        int height=star.height();
        QRect rect=option.rect;
        int x=rect.x()+rect.width()/2-width/2;
        int y=rect.y()+rect.height()/2-height/2;

        painter->drawPixmap(x,y,star);
    }
    else{
        QStyledItemDelegate::paint(painter, option, index);
    }


}

/**
 * 绘制CheckBox
 */
QRect ButtonDelegate::CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const
{
    //绘制按钮所需要的参数
    QStyleOptionButton StyleOption;
    //按照给定的风格参数 返回元素子区域
    QRect Rect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &StyleOption);
    //返回QCheckBox坐标
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - Rect.width() / 2,
                         viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - Rect.height() / 2);
    //返回QCheckBox几何形状
    return QRect(checkBoxPoint, Rect.size());
}


/**
 * 设置CheckBox可以选择
 */
bool ButtonDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonPress )
    {
        if (index.column() == 0){
            bool data = model->data(index, Qt::DisplayRole).toBool();
            model->setData(index, !data, Qt::DisplayRole);
        }
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

