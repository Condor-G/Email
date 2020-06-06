#ifndef VERIFICATIONCODELABEL_H
#define VERIFICATIONCODELABEL_H

#include <QLabel>
#include <QAbstractItemModel>
#include <QStyleOptionViewItem>

class VerificationCodeLabel : public QLabel
{
    Q_OBJECT

public:
    VerificationCodeLabel(QWidget *parent=0);
    ~VerificationCodeLabel();
    //返回一个字符串（字母一律都按照大写返回）
    QString getVerificationCode() const;

protected:
    //重写绘制事件,以此来生成验证码
    void paintEvent(QPaintEvent *event);


private:
    const int letter_number = 4;//产生字符的数量
    int noice_point_number ;//噪点的数量
    enum {
        NUMBER_FLAG,
        UPLETTER_FLAG,
        LOWLETTER_FLAG
    };
    //这是一个用来生成验证码的函数
    void produceVerificationCode() const;
    //产生一个随机的字符
    QChar produceRandomLetter() const;
    //产生随机的颜色
    void produceRandomColor() const;

    void mousePressEvent(QMouseEvent *e);

    QChar *verificationCode;
    QColor *colorArray;
};

#endif // VERIFICATIONCODELABEL_H
