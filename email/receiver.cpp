#include "receiver.h"
#include "ui_receiver.h"


Receiver::Receiver(QString s,QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::Receiver)
{
    ui->setupUi(this);
    setWindowTitle("邮件信息");

    name = s;

    init();


}

Receiver::~Receiver()
{
    delete ui;
}

void Receiver::init()
{

    qry.prepare( "select * from message where id = '"+name+"' " );
    if( !qry.exec() )
        qDebug() <<"display error"<<qry.lastError();
    else
        qDebug( "Select success!  display. " );

    qry.next();

    ui->label_Title->setText(qry.value(3).toString());
    ui->label_sender->setText(qry.value(1).toString());
    ui->label_reciever->setText(qry.value(2).toString());
    ui->label_time->setText(qry.value(6).toString());
    ui->textBrowser->setHtml(qry.value(4).toString());

}

void Receiver::on_Btn_readatttach_clicked()
{
    


}

void Receiver::on_Btn_back_clicked()
{
    this->close();
}
