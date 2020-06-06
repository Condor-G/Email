#ifndef NEWUSER_H
#define NEWUSER_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMouseEvent>
#include <QTimer>
#include <QDateTime>
#include <verificationcodelabel.h>

namespace Ui {
class newuser;
}

class newuser : public QMainWindow
{
    Q_OBJECT

public:
    explicit newuser(QWidget *parent = nullptr);
    ~newuser();

    int check_name();
    int check_passwd();
    int check_passwd_same();
    int check_code();


private slots:
    void updateTime();

    void on_pushButton_clicked();

    void on_textEdit_1();

    void on_textEdit_2();

    void on_textEdit_3();

    void on_textEdit_5();

private:
    Ui::newuser *ui;

    VerificationCodeLabel* label_code;

    QTimer *timer;
};

#endif // NEWUSER_H
