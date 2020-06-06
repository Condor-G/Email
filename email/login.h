#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QMouseEvent>
#include <newuser.h>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void init();

private slots:
    bool eventFilter(QObject *obj, QEvent *event);

    void on_btn_login_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
