#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("登录");

    init();

    ui->label_newuser->installEventFilter(this);//安装事件过滤器

    ui->textEdit_passwd->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}


/**
 * 初始化数据库
 * 新建用户信息表
 */
void login::init()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setDatabaseName("data");
    db.open();
    bool ok=db.open();
    if(ok){
        qDebug()<<"open database success";
    }
    else{
        qDebug()<<"error open database because";
    }

    //创建用户表
    //用户账号、密码、密保问题、密保问题答案
    QSqlQuery qry;
    qry.prepare( "CREATE TABLE IF NOT EXISTS user "
                 "(userid VARCHAR(30) PRIMARY KEY, "
                 "passwd VARCHAR(30), "
                 "question VARCHAR(40), "
                 "answer VARCHAR(30), "
                 "name VARCHAR(40), "
                 "address VARCHAR(60), "
                 "phone VARCHAR(40), "
                 "time DATE, "
                 "icon VARCHAR(60)"
                 ")" );
    if( !qry.exec() )
        qDebug()<<"Table created error "<<qry.lastError();
    else
        qDebug()<<"Table created!";
}

/**
 * 设置Label的过滤器
 * 让Label相应鼠标点击事件
 */
bool login::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_newuser)//指定某个QLabel
    {
        if (event->type() == QEvent::MouseButtonPress)//mouse button pressed
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(mouseEvent->button() == Qt::LeftButton)
            {
                newuser *n = new newuser();
                n->show();

            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        // pass the event on to the parent class
        return login::eventFilter(obj, event);
    }
}


/**
 * 登录按钮
 * 检查邮件名和密码
 * 如果正确，进入主界面MainWindow
 */
void login::on_btn_login_clicked()
{
    QSqlQuery qry;
    QString name = ui->textEdit_user->text();
    qry.prepare( "select count(*) from user where userid = '"+name+"'" );
      if( !qry.exec() )
        qDebug() <<"Select error"<<qry.lastError();
      else
        qDebug( "Select success!" );
    qry.next();
    qDebug()<<qry.value(0).toInt();
    if(qry.value(0).toInt()==0){
        QMessageBox::information(this,"提示","用户不存在！");
    }
    else{
        qry.prepare( "select passwd from user where userid = '"+name+"'" );
          if( !qry.exec() )
            qDebug() <<"Select error"<<qry.lastError();
          else
            qDebug( "Select success!" );
        qry.next();
        qDebug() << "密码："<<qry.value(0).toString();
        QString passwd = ui->textEdit_passwd->text();
        if(passwd==qry.value(0).toString()){
            this->close();//关闭当前窗口
            MainWindow *w = new MainWindow(name);
            w->show();//展示主窗口
        }
        else{
            QMessageBox::information(this,"提示","密码错误！");
        }
    }
}
