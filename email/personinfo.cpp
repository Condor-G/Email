#include "personinfo.h"
#include "ui_personinfo.h"
#include "mainwindow.h"

personInfo::personInfo(QString s,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::personInfo)
{
    ui->setupUi(this);
    setWindowTitle("修改信息");

    id = s;
}

personInfo::~personInfo()
{
    delete ui;
}

void personInfo::on_pushButton_clicked()
{
    QSqlQuery qry;
    QString name = ui->lineEdit_name->text();
    QString phone = ui->lineEdit_phone->text();
    QString address = ui->lineEdit_address->text();


    QString update = "UPDATE user SET "
                     "name = '"+name+"',"
                     "phone = '"+phone+"',"
                     "address = '"+address+"' "
                     "WHERE userid = '"+id+"' " ;
    qry.prepare(update);
    qDebug()<<"!!!!!       "<<id<<endl<<update;
      if( !qry.exec() )
        qDebug() << qry.lastError();
      else{
        qDebug( "Updated!" );
        QMessageBox::information(this,"提示","修改信息成功！");
        this->close();

      }

}
