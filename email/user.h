#ifndef USER_H
#define USER_H
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>


class User
{
public:
    bool ison;
    QString username;

    User(QString name);

    void init();

    void changePasswd();//修改密码

    void retrievePasswd();//找回密码

private:


};

#endif // USER_H
