#include "user.h"

User::User(QString name)
{
    username = name;
    init();
}

void User::init()
{
    QSqlQuery qry;
    qry.prepare( "CREATE TABLE IF NOT EXISTS message"
                  "(id VARCHAR(30) PRIMARY KEY, "
                  "sender VARCHAR(30), "
                  "receiver VARCHAR(120), "
                  "title VARCHAR(30), "
                  "content VARCHAR(1000000), "
                  "accessory VARCHAR(1000000), "
                  "senddate DATE, "
                  "state VARCHAR(20), "
                  "read VARCHAR(10), "
                  "important VARCHAR(10)"
                  ")" );
     if( !qry.exec() )
         qDebug()<<"Table message created error "<<qry.lastError();
     else
         qDebug()<<"Table message created!";
}



/**
 * 修改密码
 */
void User::changePasswd()
{

}

/**
 * 找回密码
 * 密保问题
 */
void User::retrievePasswd()
{


}
