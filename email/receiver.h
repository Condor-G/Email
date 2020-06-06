#ifndef RECEIVER_H
#define RECEIVER_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QPainter>

namespace Ui {
class Receiver;
}

class Receiver : public QMainWindow
{
    Q_OBJECT

public:
    Receiver(QString s,QWidget *parent = nullptr);
    ~Receiver();

    void init();

private slots:
    void on_Btn_readatttach_clicked();

    void on_Btn_back_clicked();

private:
    Ui::Receiver *ui;
    QSqlQuery qry;
    QPixmap outImg;
    QString name;
};

#endif // RECEIVER_H
