#include "newuser.h"
#include "ui_newuser.h"
#include "user.h"
#include "login.h"

newuser::newuser(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newuser)
{
    ui->setupUi(this);

    label_code = new VerificationCodeLabel;

    ui->layout->addWidget(label_code);

    timer = new QTimer();
    timer->start(2000);
    connect(timer, SIGNAL(timeout()),this, SLOT(updateTime()));

}

void newuser::updateTime()
{
    on_textEdit_1();
    on_textEdit_2();
    on_textEdit_3();
    on_textEdit_5();
}


newuser::~newuser()
{
    delete ui;
}

/**
 * 检查邮箱地址是否符合要求：6~18个字符，可使用字母、数字、下划线，需以字母开头
 * return
 * 0 : 符合
 * 1 : 字符太少
 * 2 : 字符太多
 * 3 : 首字符不是字母
 * 4 : 存在不合法的字符
 */
int newuser::check_name()
{
    QString s = ui->textEdit_1->toPlainText();
    if(!( (s[0]>='a'&&s[0]<='z')||(s[0]>='A'&&s[0]<='Z') )) return 3;
    for(int i=0;i<s.size();i++){
        if(!( (s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z')||s[i]=='_'||(s[i]>='0'&&s[i]<='9'))) return 4;
    }
    if(s.size()<6) return 1;
    if(s.size()>18) return 2;
    return 0;
}

/**
 * 检查密码是否符合要求：6~16个字符，区分大小写
 * return
 * 0 : 符合要求
 * 1 : 字符太少
 * 2 : 字符太多
 */
int newuser::check_passwd()
{
    QString x =  ui->textEdit_2->toPlainText();
    if(x.size()<6) return 1;
    else if(x.size()>16) return 2;
    return 0;
}

/**
 * 检查两次输入的密码是否一致
 * return
 * 1 : 一致
 * 0 : 不一致
 */
int newuser::check_passwd_same()
{
    QString a = ui->textEdit_2->toPlainText();
    QString b = ui->textEdit_3->toPlainText();
    if(a==b) return 1;
    else return 0;
}

/**
 * 检查验证码是否一致
 * return
 * 1 : 一致
 * 0 : 不一致
 */
int newuser::check_code()
{
    QString code = ui->textEdit_5->toPlainText();
    if(label_code->getVerificationCode()==code){
        return 1;
    }
    else{
        return 0;
    }
}

/**
 * "立即注册"按钮
 * 将用户信息添加到数据库
 * Insert into user(userid,passwd) values('name'+'passwd');
 */
void newuser::on_pushButton_clicked()
{
    if(check_code()==0){
        QMessageBox::information(this,"提示","验证码错误！");
        return;
    }
    if(check_name()==0&&check_passwd()==0&&check_passwd_same()==1&&check_code()==1&&ui->radioButton->isChecked()){
        QSqlQuery query;
        QString name = ui->textEdit_1->toPlainText();
        QString passwd = ui->textEdit_2->toPlainText();
        QDateTime time = QDateTime::currentDateTime();
        QString InsertStr = QString("INSERT INTO user("
                                     "userid, "
                                     "passwd, "
                                     "time "
                                     ") "
                                     "VALUES("
                                     "'"+name+"', "
                                     "'"+passwd+"', "
                                     "'"+time.toString("yyyy-MM-dd hh:mm:ss")+"' "
                                     ");");
        query.prepare(InsertStr);
        qDebug()<<InsertStr;
        qDebug()<<name;
        qDebug()<<passwd;
        if(!query.exec()){
            qDebug()<<"Insert error :"<<query.lastError();
        }
        else{
            timer->stop();
            qDebug()<<"insert data success!";
            QMessageBox::information(this,"提示","注册成功！");
            this->close();
        }
    }
    else {
        QMessageBox::information(this,"提示","请完善信息");
    }
}


/**
 * 检测邮件名的合法性
 * 在label中给予提示
 */
void newuser::on_textEdit_1()
{
    QSqlQuery qry;
    QString name = ui->textEdit_1->toPlainText();

    if(name=="") {
        ui->label_11->setText("<font color=gray>6~18个字符，可使用字母、数字、下划线，需以字母开头</font>");
        return;
    }

    qry.prepare( "select count(*) from user where userid = '"+name+"'" );
      if( !qry.exec() )
        qDebug() <<"Select error"<<qry.lastError();
      else
        qDebug( "Select success!" );
    qry.next();
    qDebug()<<qry.value(0).toInt();
    if(qry.value(0).toInt()==0){
        int t = check_name();
        if(t==0){
            ui->label_11->setText("<font color=green>可以使用</font>");
        }
        else if(t==1){
            ui->label_11->setText("<font color=red>长度太短，最少6个字符</font>");
        }
        else if(t==2){
            ui->label_11->setText("<font color=red>长度过长，最多18个字符</font>");
        }
        else if(t==3){
            ui->label_11->setText("<font color=red>要以字母开头</font>");
        }
        else if(t==4){
            ui->label_11->setText("<font color=red>含非法字符</font>");
        }


    }
    else{
        ui->label_11->setText("<font color=red>该用户名已经被注册</font>");
    }

}

/**
 * 检测密码的合理性
 * 并在label中给予提示
 */
void newuser::on_textEdit_2()
{
    QString passwd = ui->textEdit_2->toPlainText();
    if(passwd==""){
        ui->label_22->setText("<font color=gray>6~16个字符，区分大小写</font>");
        return;
    }

    int t = check_passwd();
    if(t==0){
        ui->label_22->setText("<font color=green>符合要求</font>");
    }
    else if(t==1){
        ui->label_22->setText("<font color=red>长度太短，最少6个字符</font>");
    }
    else if(t==2){
        ui->label_22->setText("<font color=green>长度过长，最多16个字符</font>");
    }
}


/**
 * 检测确定密码是否一致
 * 在lalel中给予提示
 */
void newuser::on_textEdit_3()
{
    QString passwd = ui->textEdit_3->toPlainText();
    if(passwd==""){
        ui->label_33->setText("<font color=gray>请再次填写密码</font>");
        return;
    }
    if(check_passwd_same()){
        ui->label_33->setText("<font color=green>符合</font>");
    }
    else{
        ui->label_33->setText("<font color=red>密码不一致</font>");
    }
}

/**
 * 检测验证码是否正确
 * 在label中给予提示
 */
void newuser::on_textEdit_5()
{
    if(ui->textEdit_5->toPlainText()==""){
        ui->label_55->setText("<font color=gray>请填写图片中的字符,区分大小写</font>");
        return;
    }
    if(check_code()){
        ui->label_55->setText("<font color=green>正确</font>");
    }
    else{
        if(ui->textEdit_5->toPlainText().length()==4)
            ui->label_55->setText("<font color=red>验证码错误</font>");
    }
}
