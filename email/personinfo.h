#ifndef PERSONINFO_H
#define PERSONINFO_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QTextCharFormat>
#include <QTextList>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

namespace Ui {
class personInfo;
}

class personInfo : public QMainWindow
{
    Q_OBJECT

public:
    explicit personInfo(QString s,QWidget *parent = nullptr);
    ~personInfo();

private slots:
    void on_pushButton_clicked();

private:
    Ui::personInfo *ui;

    QString id;
};

#endif // PERSONINFO_H
