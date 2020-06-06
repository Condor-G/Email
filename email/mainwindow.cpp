#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "user.h"

#include <QButtonGroup>
#include <QFontDialog>

MainWindow::MainWindow(QString name,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("我的邮箱");

    //连接listWidget和stackedWidget
    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));

    user = new User(name);

    init_sendLetter();

    //tableWidget布局
    init_tableWidget();

    init_person();


    timer = new QTimer();
    timer->start(10000);
    connect(timer, SIGNAL(timeout()),this, SLOT(updateTime()));

    //添加表内信息
    display(user->username);

}

/**
 * 刷新tableWidget
 */
void MainWindow::updateTime()
{
    display(user->username);
    init_person();
}


MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * 个人信息
 */
void MainWindow::init_person()
{
    QSqlQuery qry;
    qry.prepare( "SELECT * from user WHERE userid = '"+user->username+"' " );
      if( !qry.exec() )
        qDebug() << qry.lastError();
      else
        qDebug( "SELECT!" );
    qry.next();
    ui->label_person_id->setText(user->username);
    ui->label_person_name->setText(qry.value(4).toString());
    ui->label_person_address->setText(qry.value(5).toString());
    ui->label_person_phone->setText(qry.value(6).toString());
    ui->label_person_time->setText(qry.value(7).toString());
    if(qry.value(8).toString()!="") ui->label_18->setStyleSheet("\nborder-image: url("+qry.value(8).toString()+");");

    if(qry.value(4).toString()!=""){
        ui->label_firstPage_name->setText(qry.value(4).toString()+"，您好");
    }

    else{
        ui->label_firstPage_name->setText(user->username+"，您好");
    }




}


void MainWindow::init_sendLetter()
{
    MainLayout = new QVBoxLayout(this);
    toplayout = new QHBoxLayout();
    toplayout->addWidget(ui->Btn_send);
    toplayout->addWidget(ui->Btn_preview);
    toplayout->addWidget(ui->Btn_draft);
    toplayout->addWidget(ui->Btn_cancel);
    toplayout->addStretch();
    toplayout->addWidget(ui->Btn_resend);
    toplayout->addWidget(ui->Btn_sendsecret);
    toplayout->addWidget(ui->Btn_qfdx);
    toplayout->addWidget(ui->Btn_invite);

    middlelayout = new QGridLayout;
    middlelayout->addWidget(ui->label_reciever,0,0);
    middlelayout->addWidget(ui->Editor_reciever,0,1);
    middlelayout->addWidget(ui->label_theme,1,0);
    middlelayout->addWidget(ui->Editor_theme,1,1);

    Buttonlayout = new QHBoxLayout();

    fontLabel1 = new QLabel(tr("字体:"));
    fontComboBox = new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);

    fontLabel2 = new QLabel(tr("字号:"));
    sizeComboBox = new QComboBox;
    QFontDatabase db;
    foreach(int size, db.standardSizes())
    {
        sizeComboBox->addItem(QString::number(size));
    }

    QSize size(24,24);

    boldBtn = new QToolButton;
    boldBtn->setIcon(QIcon(":/res/bold.PNG"));
    boldBtn->setCheckable(true);
    boldBtn->setIconSize(size);
    boldBtn->setAutoRaise(true);

    italicBtn = new QToolButton;
    italicBtn->setIcon(QIcon(":/res/italic.PNG"));
    italicBtn->setCheckable(true);
    italicBtn->setIconSize(size);
    italicBtn->setAutoRaise(true);

    underlineBtn = new QToolButton;
    underlineBtn->setIcon(QIcon(":/res/underline.PNG"));
    underlineBtn->setCheckable(true);
    underlineBtn->setIconSize(size);
    underlineBtn->setAutoRaise(true);

    colorBtn = new QToolButton;
    colorBtn->setIcon(QIcon(":/res/color.PNG"));
    colorBtn->setIconSize(size);
    colorBtn->setAutoRaise(true);

    Btgrp2 = new QButtonGroup;
    //undo/redo Action
    undoAction = new QToolButton;
    undoAction->setIcon(QIcon(":/res/undo.PNG"));
    undoAction->setIconSize(size);
    undoAction->setAutoRaise(true);
    Btgrp2->addButton(undoAction,1);

    redoAction= new QToolButton;
    redoAction->setIcon(QIcon(":/res/redo.PNG"));
    redoAction->setIconSize(size);
    redoAction->setAutoRaise(true);
    Btgrp2->addButton(redoAction,2);
    connect(Btgrp2,SIGNAL(buttonClicked(int)),this,SLOT(unredo(int)));

     //排版
     Btgrp = new QButtonGroup;
     leftAction= new QToolButton;
     leftAction->setIcon(QIcon(":/res/left.PNG"));
     leftAction->setCheckable(true);
     leftAction->setIconSize(size);
     leftAction->setAutoRaise(true);
     Btgrp->addButton(leftAction,1);

     rightAction= new QToolButton;
     rightAction->setIcon(QIcon(":/res/right.PNG"));
     rightAction->setCheckable(true);
     rightAction->setIconSize(size);
     rightAction->setAutoRaise(true);
     Btgrp->addButton(rightAction,2);

     centerAction= new QToolButton;
     centerAction->setIcon(QIcon(":/res/center.PNG"));
     centerAction->setCheckable(true);
     centerAction->setIconSize(size);
     centerAction->setAutoRaise(true);
     Btgrp->addButton(centerAction,3);

     justifyAction= new QToolButton;
     justifyAction->setIcon(QIcon(":/res/justify.PNG"));
     justifyAction->setCheckable(true);
     justifyAction->setIconSize(size);
     justifyAction->setAutoRaise(true);
     Btgrp->addButton(justifyAction,4);
    connect(Btgrp,SIGNAL(buttonClicked(int)),this,SLOT(ShowAlignment(int)));

    Buttonlayout->addWidget(boldBtn);
    Buttonlayout->addWidget(italicBtn);
    Buttonlayout->addWidget(underlineBtn);
    Buttonlayout->addWidget(colorBtn);

    Buttonlayout->addWidget(leftAction);
    Buttonlayout->addWidget(centerAction);
    Buttonlayout->addWidget(rightAction);
    Buttonlayout->addWidget(justifyAction);

    Buttonlayout->addWidget(fontLabel2);
    Buttonlayout->addWidget(sizeComboBox);
    Buttonlayout->addWidget(fontLabel1);
    Buttonlayout->addWidget(fontComboBox);

//    Buttonlayout->addWidget(action);
    Buttonlayout->addWidget(undoAction);
    Buttonlayout->addWidget(redoAction);
    Buttonlayout->addWidget(ui->toolButton);

    Buttonlayout->addWidget(ui->Btn_add);
    Buttonlayout->addStretch();

    buttomlayout = new QHBoxLayout();
    buttomlayout->addWidget(ui->Btn_send_2);
    buttomlayout->addWidget(ui->Btn_cancel_2);
    buttomlayout->addStretch();

    MainLayout->addLayout(toplayout);
    MainLayout->addLayout(middlelayout);
    MainLayout->addLayout(Buttonlayout);
    MainLayout->addWidget(ui->textEdit);
    MainLayout->addWidget(ui->label_sender);
    MainLayout->addLayout(buttomlayout);

    ui->page_Writeletter->setLayout(MainLayout);

    connect(fontComboBox,SIGNAL(activated(QString)),this,SLOT(ShowFontComboBox(QString)));
    connect(sizeComboBox,SIGNAL(activated(QString)),this,SLOT(ShowSizeSpinBox(QString)));
    connect(boldBtn,SIGNAL(clicked()),this,SLOT(ShowBoldBtn()));
    connect(italicBtn,SIGNAL(clicked()),this,SLOT(ShowItalicBtn()));
    connect(underlineBtn,SIGNAL(clicked()),this,SLOT(showUnderlineButton()));
    connect(colorBtn,SIGNAL(clicked()),this,SLOT(ShowColorBtn()));
    connect( ui->textEdit, SIGNAL( currentCharFormatChanged( const QTextCharFormat & ) ), this, SLOT( ShowCurrentFormatChanged(const QTextCharFormat&)));

    connect(ui->Btn_send,SIGNAL(clicked()),this,SLOT(button_send()));
    connect(ui->Btn_send_2,SIGNAL(clicked()),this,SLOT(button_send()));
}



void MainWindow::ShowBoldBtn()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(boldBtn->isChecked()?QFont::Bold:QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::ShowItalicBtn()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::showUnderlineButton()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineBtn->isChecked());
    ui->textEdit->mergeCurrentCharFormat(fmt);
    qDebug()<<"underline!!!";
}

void MainWindow::ShowColorBtn()
{
    QColor color = QColorDialog::getColor(Qt::red,this);

    if(color.isValid()){
        QTextCharFormat fmt;
        fmt.setForeground(color);
        ui->textEdit->mergeCurrentCharFormat(fmt);
    }
}

void MainWindow::ShowAlignment(int id)
{
    qDebug()<<"id:"<<id;
    if(id==1){
        ui->textEdit->setAlignment(Qt::AlignLeft);
    }
    if(id==2){
        ui->textEdit->setAlignment(Qt::AlignRight);
    }
    if(id==3){
        ui->textEdit->setAlignment(Qt::AlignCenter);
    }
    if(id==4){
        ui->textEdit->setAlignment(Qt::AlignJustify);
    }
}

void MainWindow::unredo(int id)
{
    if(id==1){
        ui->textEdit->undo();
    }
    if(id==2){
        ui->textEdit->redo();
    }
}

void MainWindow::ShowCurrentFormatChanged(const QTextCharFormat &fmt)
{
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamily()));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underlineBtn->setChecked(fmt.fontUnderline());
}

void MainWindow::ShowFontComboBox(QString comboStr)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(comboStr);
    mergeFormat(fmt);
}

void MainWindow::mergeFormat(QTextCharFormat format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if(!cursor.hasSelection()){
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void MainWindow::ShowSizeSpinBox(QString spinValue)
{
    QTextCharFormat fmt;
    fmt.setFontPointSize(spinValue.toDouble());
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::ShowCursorPositionChanged()
{
    if(ui->textEdit->alignment()==Qt::AlignLeft)
        leftAction->setChecked(true);
    if(ui->textEdit->alignment()==Qt::AlignRight)
        rightAction->setChecked(true);
    if(ui->textEdit->alignment()==Qt::AlignCenter)
        centerAction->setChecked(true);
    if(ui->textEdit->alignment()==Qt::AlignJustify)
        justifyAction->setChecked(true);
}

/**
 * 保存图片到File内，File是存所有附件图片的文件夹
 */
void MainWindow::saveImg(const QString &imgFileName,QString sn)
{
    QFile inImg(save_filename);
    QImage img;
    if(!inImg.open(QIODevice::ReadOnly)){
        QMessageBox::warning(0,"Error","Open Image File Failed");
        return;
    }
    else{
        if(!(img.load(save_filename)))
        {
            QMessageBox::information(this,tr("Open failed!"),tr("Failed!"));
            return;
        }
    }
	QDir *file = new QDir;
    bool exist = file->exists("./File");
    if(exist)
        qDebug()<<"File exits!";
    else {
        bool ok = file->mkdir("./File");
        if(ok){
            qDebug()<<"file success!";
        }
    }
    QString savename="./File/"+sn;
    img.save(savename);
}


/**
 * 添加附件图片
 */
void MainWindow::on_Btn_add_clicked()
{
    save_filename = QFileDialog::getOpenFileName(this,"Choose a file...",".");
    QString str=save_filename.section('.',-1);
    save_name = save_filename.section("/",-1);
    ui->Btn_add->setText(save_name);
}


void MainWindow::on_textEdit_cursorPositionChanged()
{
    ShowCursorPositionChanged();
}

void MainWindow::button_send()
{
    if(save_filename!="") saveImg(save_filename,save_name);

    QDateTime time = QDateTime::currentDateTime();

    if(ui->Editor_reciever->text()==""){
        QMessageBox::information(this,"提示","请输入收件人！");
        return;
    }
    if(ui->Editor_theme->text()==""){
        QMessageBox::information(this,"提示","请输入邮件的主题！");
        return;
    }
    if(ui->textEdit->toPlainText()==""){
        QMessageBox::information(this,"提示","请输入内容！");
        return;
    }

    QString nname;
    if(save_filename=="") nname="null";
    else nname = save_filename;

    QString InsertStr = QString("INSERT INTO message("
                                "id, "
                                "sender, "
                                "receiver, "
                                "title, "
                                "content, "
                                "accessory, "
                                "senddate, "
                                "state, "
                                "read,"
                                "important)"

                                "VALUES("
                                "'"+user->username+time.toString("yyyyMMddhhmmss")+"', "
                                "'"+user->username+"', "
                                "'"+ui->Editor_reciever->text()+"', "
                                "'"+ui->Editor_theme->text()+"', "
                                "'"+ui->textEdit->toHtml().replace("'","\"") +"', "
                                "'"+nname+"', "
                                "'"+time.toString("yyyy-MM-dd hh:mm:ss")+"', "
                                "'sended', "
                                "'no', "
                                "'no' "
                                    " ); "
                                );

    query.prepare(InsertStr);
    qDebug()<<InsertStr;

    if(!query.exec()){
        qDebug()<<"Send Button Insert error :"<<query.lastError();
    }
    else{
        qDebug()<<"Send Button  insert data success!";
    }
    display(user->username);

    ui->Editor_reciever->clear();
    ui->Editor_theme->clear();
    ui->textEdit->clear();

    QMessageBox::information(this,"提示","发送成功！");
}


/**
 * 发送邮件的发送按钮
 */
void MainWindow::on_Btn_draft_clicked()
{
    if(save_filename!="") saveImg(save_filename,save_name);

        QDateTime time = QDateTime::currentDateTime();

        if(ui->Editor_reciever->text()==""){
            QMessageBox::information(this,"提示","请输入收件人！");
            return;
        }
        if(ui->Editor_theme->text()==""){
            QMessageBox::information(this,"提示","请输入邮件的主题！");
            return;
        }
        if(ui->textEdit->toPlainText()==""){
            QMessageBox::information(this,"提示","请输入内容！");
            return;
        }

        QString InsertStr = QString("INSERT INTO message("
                                    "id, "
                                    "sender, "
                                    "receiver, "
                                    "title, "
                                    "content, "
                                    "senddate, "
                                    "state, "
                                    "read,"
                                    "important)"

                                    "VALUES("
                                    "'"+user->username+time.toString("yyyyMMddhhmmss")+"', "
                                    "'"+user->username+"', "
                                    "'"+ui->Editor_reciever->text()+"', "
                                    "'"+ui->Editor_theme->text()+"', "
                                    "'"+ui->textEdit->toHtml().replace("'","\"")+"', "
                                    "'"+time.toString("yyyy-MM-dd hh:mm:ss")+"', "
                                    "'draft', "
                                    "'no', "
                                    "'no' "
                                        " ); "
                                    );

        query.prepare(InsertStr);
        qDebug()<<InsertStr;
        QMessageBox::information(this,"提示","成功发送！");

        if(!query.exec()){
            qDebug()<<"Send Button Insert error :"<<query.lastError();
        }
        else{
            qDebug()<<"Send Button  insert data success!";
        }
        display(user->username);
}

/**
 * 初始化tableWidget的布局
 */
void MainWindow::init_tableWidget()
{
    //收件箱的布局--------------------------------------------------------------

    model = new QStandardItemModel();

    //添加表头信息
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("选")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("读")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("发件人")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("星")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("标题")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("内容")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("日期")));

    //连接model和tableView
    ui->tableView->setModel(model);

    //设置列的宽度
    ui->tableView->setColumnWidth(0,10);
    ui->tableView->setColumnWidth(1,10);
    ui->tableView->setColumnWidth(2,130);
    ui->tableView->setColumnWidth(3,10);
    ui->tableView->setColumnWidth(4,150);
    ui->tableView->setColumnWidth(5,400);
    ui->tableView->setColumnWidth(6,150);

    //可隐藏grid
    ui->tableView->setShowGrid(false);

    //默认显示行头，也可以将隐藏
    ui->tableView->verticalHeader()->hide();

    //设置选中时为整行选中
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //ui->tableView->setEditTriggers(QAbstractItemView::QAbstractItemView::CurrentChanged);



    //星际邮箱的布局--------------------------------------------------------------

    model_star = new QStandardItemModel();

    //添加表头信息
    model_star->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("选")));
    model_star->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("读")));
    model_star->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("发件人")));
    model_star->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("星")));
    model_star->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("标题")));
    model_star->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("内容")));
    model_star->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("日期")));

    //连接model和tableView
    ui->tableView_star->setModel(model_star);

    //设置列的宽度
    ui->tableView_star->setColumnWidth(0,10);
    ui->tableView_star->setColumnWidth(1,10);
    ui->tableView_star->setColumnWidth(2,130);
    ui->tableView_star->setColumnWidth(3,10);
    ui->tableView_star->setColumnWidth(4,150);
    ui->tableView_star->setColumnWidth(5,400);
    ui->tableView_star->setColumnWidth(6,150);

    //可隐藏grid
    ui->tableView_star->setShowGrid(false);

    //默认显示行头，也可以将隐藏
    ui->tableView_star->verticalHeader()->hide();

    //设置选中时为整行选中
    ui->tableView_star->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->tableView_star->setEditTriggers(QAbstractItemView::NoEditTriggers);



    //草稿邮箱的布局--------------------------------------------------------------

    model_draft = new QStandardItemModel();

    //添加表头信息
    model_draft->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("选")));
    model_draft->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("读")));
    model_draft->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("收件人")));
    model_draft->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("星")));
    model_draft->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("标题")));
    model_draft->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("内容")));
    model_draft->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("日期")));

    //连接model和tableView
    ui->tableView_draft->setModel(model_draft);

    //设置列的宽度
    ui->tableView_draft->setColumnWidth(0,10);
    ui->tableView_draft->setColumnWidth(1,10);
    ui->tableView_draft->setColumnWidth(2,130);
    ui->tableView_draft->setColumnWidth(3,10);
    ui->tableView_draft->setColumnWidth(4,150);
    ui->tableView_draft->setColumnWidth(5,400);
    ui->tableView_draft->setColumnWidth(6,150);

    //可隐藏grid
    ui->tableView_draft->setShowGrid(false);

    //默认显示行头，也可以将隐藏
    ui->tableView_draft->verticalHeader()->hide();

    //设置选中时为整行选中
    ui->tableView_draft->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->tableView_draft->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //已发送的布局--------------------------------------------------------------
    model_sended = new QStandardItemModel();

    //添加表头信息
    model_sended->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("选")));
    model_sended->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("读")));
    model_sended->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("收件人")));
    model_sended->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("星")));
    model_sended->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("标题")));
    model_sended->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("内容")));
    model_sended->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("日期")));

    //连接model和tableView
    ui->tableView_sended->setModel(model_sended);

    //设置列的宽度
    ui->tableView_sended->setColumnWidth(0,10);
    ui->tableView_sended->setColumnWidth(1,10);
    ui->tableView_sended->setColumnWidth(2,130);
    ui->tableView_sended->setColumnWidth(3,10);
    ui->tableView_sended->setColumnWidth(4,150);
    ui->tableView_sended->setColumnWidth(5,400);
    ui->tableView_sended->setColumnWidth(6,150);

    //可隐藏grid
    ui->tableView_sended->setShowGrid(false);

    //默认显示行头，也可以将隐藏
    ui->tableView_sended->verticalHeader()->hide();

    //设置选中时为整行选中
    ui->tableView_sended->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->tableView_sended->setEditTriggers(QAbstractItemView::NoEditTriggers);



    //回收站的布局--------------------------------------------------------------
    model_bin = new QStandardItemModel();

    //添加表头信息
    model_bin->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("选")));
    model_bin->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("读")));
    model_bin->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("发件人")));
    model_bin->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("星")));
    model_bin->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("标题")));
    model_bin->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("内容")));
    model_bin->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("日期")));

    //连接model和tableView
    ui->tableView_bin->setModel(model_bin);

    //设置列的宽度
    ui->tableView_bin->setColumnWidth(0,10);
    ui->tableView_bin->setColumnWidth(1,10);
    ui->tableView_bin->setColumnWidth(2,130);
    ui->tableView_bin->setColumnWidth(3,10);
    ui->tableView_bin->setColumnWidth(4,150);
    ui->tableView_bin->setColumnWidth(5,400);
    ui->tableView_bin->setColumnWidth(6,150);

    //可隐藏grid
    ui->tableView_bin->setShowGrid(false);

    //默认显示行头，也可以将隐藏
    ui->tableView_bin->verticalHeader()->hide();

    //设置选中时为整行选中
    ui->tableView_bin->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->tableView_bin->setEditTriggers(QAbstractItemView::NoEditTriggers);


    //垃圾邮箱的布局--------------------------------------------------------------
    model_rubbish = new QStandardItemModel();

    //添加表头信息
    model_rubbish->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("选")));
    model_rubbish->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("读")));
    model_rubbish->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("发件人")));
    model_rubbish->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("星")));
    model_rubbish->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("标题")));
    model_rubbish->setHorizontalHeaderItem(5, new QStandardItem(QObject::tr("内容")));
    model_rubbish->setHorizontalHeaderItem(6, new QStandardItem(QObject::tr("日期")));

    //连接model和tableView
    ui->tableView_rubbish->setModel(model_rubbish);

    //设置列的宽度
    ui->tableView_rubbish->setColumnWidth(0,10);
    ui->tableView_rubbish->setColumnWidth(1,10);
    ui->tableView_rubbish->setColumnWidth(2,130);
    ui->tableView_rubbish->setColumnWidth(3,10);
    ui->tableView_rubbish->setColumnWidth(4,150);
    ui->tableView_rubbish->setColumnWidth(5,400);
    ui->tableView_rubbish->setColumnWidth(6,150);

    //可隐藏grid
    ui->tableView_rubbish->setShowGrid(false);

    //默认显示行头，也可以将隐藏
    ui->tableView_rubbish->verticalHeader()->hide();

    //设置选中时为整行选中
    ui->tableView_rubbish->setSelectionBehavior(QAbstractItemView::SelectRows);

    //设置表格的单元为只读属性，即不能编辑
    ui->tableView_rubbish->setEditTriggers(QAbstractItemView::NoEditTriggers);

}


/**
 * 展示收件箱的邮件信息
 *
 *
 * 星际邮箱
 *
 *
 * 草稿箱
 *
 *
 * 已发送邮件
 *
 *
 * 回收站
 *
 *
 * 垃圾站
 *
 */
void MainWindow::display(QString name)
{
    QSqlQuery qry;

    //清空model
    model->clear();
    model_bin->clear();
    model_star->clear();
    model_draft->clear();
    model_sended->clear();
    model_rubbish->clear();

    //初始化布局
    init_tableWidget();

    //显示收件箱--------------------------------------------------------------

    qry.prepare( "select * from message where receiver = '"+name+"' and state = 'sended' " );
    if( !qry.exec() )
        qDebug() <<"display error"<<qry.lastError();
    else
        qDebug( "Select success!  display. " );

    for(int i=0;qry.next();i++){
          model->setItem(i, 1, new QStandardItem(qry.value(8).toString()));
          model->setItem(i, 2, new QStandardItem(qry.value(1).toString()));
          model->setItem(i, 3, new QStandardItem(qry.value(9).toString()));
          model->setItem(i, 4, new QStandardItem(qry.value(3).toString()));

          QTextEdit te;
          te.setHtml(qry.value(4).toString());
          model->setItem(i, 5, new QStandardItem(te.toPlainText()));
          //model->setItem(i, 5, new QStandardItem(qry.value(4).toString()));
          model->setItem(i, 6, new QStandardItem(qry.value(6).toString()));
          ui->tableView->setItemDelegate(new ButtonDelegate());

    }


    //显示星际邮箱--------------------------------------------------------------

    //qry.prepare( "select * from message where sender = '"+name+"' or receiver = '"+ name+" '  and important = 'yes';  " );
    //qry.prepare( "select * from message where receiver = '"+ name+" '  " );
    qry.prepare( "select * from message where receiver = '"+name+"' and important = 'yes' " );
    if( !qry.exec() )
        qDebug() <<"display star error"<<qry.lastError();
    else
        qDebug( "Select success!  display star. " );

    for(int i=0;qry.next();i++){
        model_star->setItem(i, 1, new QStandardItem(qry.value(8).toString()));
        model_star->setItem(i, 2, new QStandardItem(qry.value(1).toString()));
        model_star->setItem(i, 3, new QStandardItem(qry.value(9).toString()));
        model_star->setItem(i, 4, new QStandardItem(qry.value(3).toString()));
        QTextEdit te;
        te.setHtml(qry.value(4).toString());
        model_star->setItem(i, 5, new QStandardItem(te.toPlainText()));
        //model->setItem(i, 5, new QStandardItem(qry.value(4).toString()));
        model_star->setItem(i, 6, new QStandardItem(qry.value(6).toString()));
        ui->tableView_star->setItemDelegate(new ButtonDelegate());
    }



    //显示草稿邮箱--------------------------------------------------------------

    qry.prepare( "select * from message where sender = '"+name+"' and state = 'draft';  " );
    if( !qry.exec() )
        qDebug() <<"display draft error"<<qry.lastError();
    else
        qDebug( "Select success!  display draft. " );

    for(int i=0;qry.next();i++){
        //model_draft->setItem(i, 1, new QStandardItem(qry.value(8).toString()));
        model_draft->setItem(i, 2, new QStandardItem(qry.value(2).toString()));//收件人
        //model_draft->setItem(i, 3, new QStandardItem(qry.value(9).toString()));
        model_draft->setItem(i, 4, new QStandardItem(qry.value(3).toString()));
        QTextEdit te;
        te.setHtml(qry.value(4).toString());
        model_draft->setItem(i, 5, new QStandardItem(te.toPlainText()));
        //model->setItem(i, 5, new QStandardItem(qry.value(4).toString()));
        model_draft->setItem(i, 6, new QStandardItem(qry.value(6).toString()));
        ui->tableView_draft->setItemDelegate(new ButtonDelegate());

    }



    //显示已发件邮箱--------------------------------------------------------------

    qry.prepare( "select * from message where sender = '"+name+"' and state = 'sended';  " );
    if( !qry.exec() )
        qDebug() <<"display sended error"<<qry.lastError();
    else
        qDebug( "Select success!  display sended. " );

    for(int i=0;qry.next();i++){
        //model_sended->setItem(i, 1, new QStandardItem(qry.value(8).toString()));
        model_sended->setItem(i, 2, new QStandardItem(qry.value(2).toString()));//收件人
        //model_sended->setItem(i, 3, new QStandardItem(qry.value(9).toString()));
        model_sended->setItem(i, 4, new QStandardItem(qry.value(3).toString()));
        QTextEdit te;
        te.setHtml(qry.value(4).toString());
        model_sended->setItem(i, 5, new QStandardItem(te.toPlainText()));
        //model->setItem(i, 5, new QStandardItem(qry.value(4).toString()));
        model_sended->setItem(i, 6, new QStandardItem(qry.value(6).toString()));
        ui->tableView_sended->setItemDelegate(new ButtonDelegate());

    }



    //显示回收站邮箱--------------------------------------------------------------

    qry.prepare( "select * from message where receiver = '"+name+"' and state = 'bin';  " );
    if( !qry.exec() )
        qDebug() <<"display bin error"<<qry.lastError();
    else
        qDebug( "Select success!  display bin. " );

    for(int i=0;qry.next();i++){
        model_bin->setItem(i, 1, new QStandardItem(qry.value(8).toString()));
        model_bin->setItem(i, 2, new QStandardItem(qry.value(1).toString()));
        model_bin->setItem(i, 3, new QStandardItem(qry.value(9).toString()));
        model_bin->setItem(i, 4, new QStandardItem(qry.value(3).toString()));
        QTextEdit te;
        te.setHtml(qry.value(4).toString());
        model_bin->setItem(i, 5, new QStandardItem(te.toPlainText()));
        //model->setItem(i, 5, new QStandardItem(qry.value(4).toString()));
        model_bin->setItem(i, 6, new QStandardItem(qry.value(6).toString()));
        ui->tableView_bin->setItemDelegate(new ButtonDelegate());

    }

    //显示垃圾邮箱--------------------------------------------------------------

    qry.prepare( "select * from message where receiver = '"+name+"' and state = 'rubbish';  " );
    if( !qry.exec() )
        qDebug() <<"display rubbish error"<<qry.lastError();
    else
        qDebug( "Select success!  display rubbish. " );

    for(int i=0;qry.next();i++){
        model_rubbish->setItem(i, 1, new QStandardItem(qry.value(8).toString()));
        model_rubbish->setItem(i, 2, new QStandardItem(qry.value(1).toString()));
        model_rubbish->setItem(i, 3, new QStandardItem(qry.value(9).toString()));
        model_rubbish->setItem(i, 4, new QStandardItem(qry.value(3).toString()));
        QTextEdit te;
        te.setHtml(qry.value(4).toString());
        model_rubbish->setItem(i, 5, new QStandardItem(te.toPlainText()));
        //model->setItem(i, 5, new QStandardItem(qry.value(4).toString()));
        model_rubbish->setItem(i, 6, new QStandardItem(qry.value(6).toString()));
        ui->tableView_rubbish->setItemDelegate(new ButtonDelegate());
    }
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
    qDebug()<<index.column();
    qDebug()<<index.data().toString();


    QString id = model->data(QModelIndex(model->index( index.row(),2))).toString();
    QString time = model->data(QModelIndex(model->index( index.row(),6))).toString();
    QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
    id += ttime;
    qDebug()<<id;

    QSqlQuery qry;
    if(index.column()==3){
        if(index.data().toString()=="no"){
            qry.prepare( "UPDATE message SET important = 'yes' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        else if(index.data().toString()=="yes"){
            qry.prepare( "UPDATE message SET important = 'no' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        display(user->username);
        return;
    } 
    if(index.column()!=3&&index.column()!=0){//打开邮件，显示详细信息

        qry.prepare( "UPDATE message SET read = 'yes' WHERE id = '"+id+"' " );//设置已读
        if( !qry.exec() )
           qDebug() << qry.lastError();
        else
           qDebug( "Updated!" );
        display(user->username);

        Receiver *r = new Receiver(id);
        r->show();
    }
}

void MainWindow::on_tableView_star_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
    qDebug()<<index.column();
    qDebug()<<index.data().toString();

    QString id = model_star->data(QModelIndex(model_star->index( index.row(),2))).toString();
    QString time = model_star->data(QModelIndex(model_star->index( index.row(),6))).toString();
    QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
    id += ttime;
    qDebug()<<id;

    QSqlQuery qry;
    if(index.column()==3){
        if(index.data().toString()=="no"){
            qry.prepare( "UPDATE message SET important = 'yes' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        else if(index.data().toString()=="yes"){
            qry.prepare( "UPDATE message SET important = 'no' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        display(user->username);
        return;
    }
    if(index.column()!=3&&index.column()!=0){//打开邮件，显示详细信息

        qry.prepare( "UPDATE message SET read = 'yes' WHERE id = '"+id+"' " );//设置已读
        if( !qry.exec() )
           qDebug() << qry.lastError();
        else
           qDebug( "Updated!" );
        display(user->username);

        Receiver *r = new Receiver(id);
        r->show();
    }

}

void MainWindow::on_tableView_draft_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
    qDebug()<<index.column();
    qDebug()<<index.data().toString();

    QString id = user->username;
    QString time = model_draft->data(QModelIndex(model_draft->index( index.row(),6))).toString();
    QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
    id += ttime;
    qDebug()<<id;

    QSqlQuery qry;
    if(index.column()==3){
        if(index.data().toString()=="no"){
            qry.prepare( "UPDATE message SET important = 'yes' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        else if(index.data().toString()=="yes"){
            qry.prepare( "UPDATE message SET important = 'no' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        display(user->username);
        return;
    }
    if(index.column()!=3&&index.column()!=0){//打开邮件，显示详细信息

        //***********************草稿箱，直接转到写邮件


        //**********************
    }

}

void MainWindow::on_tableView_sended_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
    qDebug()<<index.column();
    qDebug()<<index.data().toString();

    QString id = user->username;
    QString time = model_sended->data(QModelIndex(model_sended->index( index.row(),6))).toString();
    QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
    id += ttime;
    qDebug()<<id;


    QSqlQuery qry;
    if(index.column()==3){
        if(index.data().toString()=="no"){
            qry.prepare( "UPDATE message SET important = 'yes' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        else if(index.data().toString()=="yes"){
            qry.prepare( "UPDATE message SET important = 'no' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        display(user->username);
        return;
    }
    if(index.column()!=3&&index.column()!=0){//打开邮件，显示详细信息
        Receiver *r = new Receiver(id);
        qDebug()<<id<<"         !!!!!!!";
        r->show();
    }

}

void MainWindow::on_tableView_bin_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
    qDebug()<<index.column();
    qDebug()<<index.data().toString();

    QString id = model_bin->data(QModelIndex(model_bin->index( index.row(),2))).toString();
    QString time = model_bin->data(QModelIndex(model_bin->index( index.row(),6))).toString();
    QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
    id += ttime;
    qDebug()<<id;

    QSqlQuery qry;
    if(index.column()==3){
        if(index.data().toString()=="no"){
            qry.prepare( "UPDATE message SET important = 'yes' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        else if(index.data().toString()=="yes"){
            qry.prepare( "UPDATE message SET important = 'no' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        display(user->username);
        return;
    }
    if(index.column()!=3&&index.column()!=0){//打开邮件，显示详细信息

        qry.prepare( "UPDATE message SET read = 'yes' WHERE id = '"+id+"' " );//设置已读
        if( !qry.exec() )
           qDebug() << qry.lastError();
        else
           qDebug( "Updated!" );
        display(user->username);

        Receiver *r = new Receiver(id);
        r->show();
    }

}

void MainWindow::on_tableView_rubbish_clicked(const QModelIndex &index)
{
    qDebug()<<index.row();
    qDebug()<<index.column();
    qDebug()<<index.data().toString();

    QString id = model_rubbish->data(QModelIndex(model_rubbish->index( index.row(),2))).toString();
    QString time = model_rubbish->data(QModelIndex(model_rubbish->index( index.row(),6))).toString();
    QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
    id += ttime;
    qDebug()<<id;

    QSqlQuery qry;
    if(index.column()==3){//设置星标邮件
        if(index.data().toString()=="no"){
            qry.prepare( "UPDATE message SET important = 'yes' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        else if(index.data().toString()=="yes"){
            qry.prepare( "UPDATE message SET important = 'no' WHERE id = '"+id+"' " );
              if( !qry.exec() )
                qDebug() << qry.lastError();
              else
                qDebug( "Updated!" );
        }
        display(user->username);
        return;
    }
    if(index.column()!=3&&index.column()!=0){//打开邮件，显示详细信息

        qry.prepare( "UPDATE message SET read = 'yes' WHERE id = '"+id+"' " );//设置已读
        if( !qry.exec() )
           qDebug() << qry.lastError();
        else
           qDebug( "Updated!" );
        display(user->username);

        Receiver *r = new Receiver(id);
        r->show();
    }

}

/**
 * 收件箱，选择全部按钮
 */
void MainWindow::on_btn_receive_selectall_clicked()
{
    for(int i=0;i<model->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView->model()->index(i,0, QModelIndex());

        model->setData(index, true, Qt::DisplayRole);
    }
}


/**
 * 收件箱，全部已读按钮
 */
void MainWindow::on_pushButton_readall_clicked()
{
    QSqlQuery qry;
    qry.prepare( "update  message set  read = 'yes'  where receiver = '"+user->username+"' and state = 'sended' " );
    if( !qry.exec() )
        qDebug() <<"read all error"<<qry.lastError();
    else
        qDebug( "read all correct " );
    display(user->username);
}


/**
 * 收件箱，删除按钮
 */
void MainWindow::on_btn_receive_delete_clicked()
{
    for(int i=0;i<model->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView->model()->index(i,0, QModelIndex());

        bool data = model->data(index, Qt::DisplayRole).toBool();

        if(data==true){
            QString id = model->data(QModelIndex(model->index( index.row(),2))).toString();
            QString time = model->data(QModelIndex(model->index( index.row(),6))).toString();
            QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
            id += ttime;

            QSqlQuery qry;
            qry.prepare( "update  message  set state = 'bin'  where id = '"+id+"' " );
            if( !qry.exec() )
                qDebug() <<"delete  error"<<qry.lastError();
            else
                qDebug( "delete correct " );

        }
    }
    display(user->username);
}

/**
 * 收件箱，彻底删除按钮
 */
void MainWindow::on_btn_receive_deleteall_clicked()
{
    for(int i=0;i<model->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView->model()->index(i,0, QModelIndex());

        bool data = model->data(index, Qt::DisplayRole).toBool();

        if(data==true){
            QString id = model->data(QModelIndex(model->index( index.row(),2))).toString();
            QString time = model->data(QModelIndex(model->index( index.row(),6))).toString();
            QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
            id += ttime;

            QSqlQuery qry;
            qry.prepare( "delete from message   where id = '"+id+"' " );
            if( !qry.exec() )
                qDebug() <<"delete  error"<<qry.lastError();
            else
                qDebug( "delete correct " );

        }
    }
    display(user->username);
}


/**
 * 星标邮箱，选择全部
 */
void MainWindow::on_btn_star_selectall_clicked()
{
    for(int i=0;i<model_star->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_star->model()->index(i,0, QModelIndex());

        model_star->setData(index, true, Qt::DisplayRole);
    }
}


/**
 * 星标邮箱，取消星标
 */
void MainWindow::on_btn_star_cancel_clicked()
{
    for(int i=0;i<model_star->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_star->model()->index(i,0, QModelIndex());

        bool data = model_star->data(index, Qt::DisplayRole).toBool();

        if(data==true){
            QString id = model_star->data(QModelIndex(model_star->index( index.row(),2))).toString();
            QString time = model_star->data(QModelIndex(model_star->index( index.row(),6))).toString();
            QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
            id += ttime;
            QSqlQuery qry;
            qry.prepare( "UPDATE message SET important = 'no' WHERE id = '"+id+"' " );
            if( !qry.exec() )
                qDebug() <<"update  error"<<qry.lastError();
            else
                qDebug()<< "update correct " ;

        }
    }
    display(user->username);
}

/**
 * 草稿箱，删除
 */
void MainWindow::on_btn_draft_delete_clicked()
{
    for(int i=0;i<model_draft->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_draft->model()->index(i,0, QModelIndex());

        bool data = model_draft->data(index, Qt::DisplayRole).toBool();

        if(data==true){
            QString id = model_draft->data(QModelIndex(model_draft->index( index.row(),2))).toString();
            QString time = model_draft->data(QModelIndex(model_draft->index( index.row(),6))).toString();
            QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
            id += ttime;

            QSqlQuery qry;
            qry.prepare( "delete from message   where id = '"+id+"' " );
            if( !qry.exec() )
                qDebug() <<"delete  error"<<qry.lastError();
            else
                qDebug( "delete correct " );

        }
    }
    display(user->username);
}


/**
 * 焦点Bar，字体变粗
 */
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QFont font;
    font.setBold(true);
    item->setFont(font);
//    ui->listWidget->setSelectionModel();
//    ui->listWidget->setSelectionBehavior();
}

void MainWindow::on_btn_bin_selectAll_clicked()
{
    for(int i=0;i<model_bin->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_bin->model()->index(i,0, QModelIndex());

        model_bin->setData(index, true, Qt::DisplayRole);
    }
}

void MainWindow::on_btn_bin_recover_clicked()
{
    for(int i=0;i<model_bin->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_bin->model()->index(i,0, QModelIndex());

        bool data = model_bin->data(index, Qt::DisplayRole).toBool();

        if(data==true){
            QString id = model_bin->data(QModelIndex(model_bin->index( index.row(),2))).toString();
            QString time = model_bin->data(QModelIndex(model_bin->index( index.row(),6))).toString();
            QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
            id += ttime;
            QSqlQuery qry;
            qry.prepare( "UPDATE message SET state = 'sended' WHERE id = '"+id+"' " );
            if( !qry.exec() )
                qDebug() <<"update  error"<<qry.lastError();
            else
                qDebug()<< "update correct " ;

        }
    }
    display(user->username);
}



void MainWindow::on_btn_bin_delete_clicked()
{
    for(int i=0;i<model_bin->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_bin->model()->index(i,0, QModelIndex());

        bool data = model_bin->data(index, Qt::DisplayRole).toBool();

        if(data==true){
            QString id = model_bin->data(QModelIndex(model_bin->index( index.row(),2))).toString();
            QString time = model_bin->data(QModelIndex(model_bin->index( index.row(),6))).toString();
            QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
            id += ttime;

            QSqlQuery qry;
            qry.prepare( "delete from message   where id = '"+id+"' " );
            if( !qry.exec() )
                qDebug() <<"delete  error"<<qry.lastError();
            else
                qDebug( "delete correct " );

        }
    }
    display(user->username);
}

void MainWindow::on_btn_rubbish_selectAll_clicked()
{
    for(int i=0;i<model_rubbish->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_rubbish->model()->index(i,0, QModelIndex());

        model_rubbish->setData(index, true, Qt::DisplayRole);
    }
}

void MainWindow::on_btn_rubbish_recover_clicked()
{
    for(int i=0;i<model_rubbish->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_rubbish->model()->index(i,0, QModelIndex());

        bool data = model_rubbish->data(index, Qt::DisplayRole).toBool();

        if(data==true){
            QString id = model_rubbish->data(QModelIndex(model_rubbish->index( index.row(),2))).toString();
            QString time = model_rubbish->data(QModelIndex(model_rubbish->index( index.row(),6))).toString();
            QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
            id += ttime;
            QSqlQuery qry;
            qry.prepare( "UPDATE message SET state = 'sended' WHERE id = '"+id+"' " );
            if( !qry.exec() )
                qDebug() <<"update  error"<<qry.lastError();
            else
                qDebug()<< "update correct " ;

        }
    }
    display(user->username);
}

void MainWindow::on_btn_rubbish_delete_clicked()
{
    for(int i=0;i<model_rubbish->rowCount();i++){
        QVariant  ok;
        QModelIndex index= ui->tableView_rubbish->model()->index(i,0, QModelIndex());

        bool data = model_rubbish->data(index, Qt::DisplayRole).toBool();

        if(data==true){
            QString id = model_rubbish->data(QModelIndex(model_rubbish->index( index.row(),2))).toString();
            QString time = model_rubbish->data(QModelIndex(model_rubbish->index( index.row(),6))).toString();
            QString ttime = time.mid(0,4)+time.mid(5,2)+time.mid(8,2)+time.mid(11,2)+time.mid(14,2)+time.mid(17,2);
            id += ttime;

            QSqlQuery qry;
            qry.prepare( "delete from message   where id = '"+id+"' " );
            if( !qry.exec() )
                qDebug() <<"delete  error"<<qry.lastError();
            else
                qDebug( "delete correct " );

        }
    }
    display(user->username);
}

void MainWindow::on_changepic_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"),".",tr("Image Files(*.jpg *.png)"));
    if(path.length()==0)
    {
        QMessageBox::information(NULL,tr("Error"),tr("You didn't select any files!"));
    }
    else {
        ui->label_18->setStyleSheet("\nborder-image: url("+path+");");
        QSqlQuery qry;
        QString update = "UPDATE user SET "
                         "icon = '"+path+"'"
                         "WHERE userid = '"+user->username+"' " ;

        qry.prepare(update);
          if( !qry.exec() )
            qDebug() << qry.lastError();
          else{
            qDebug( "Updated!" );
            QMessageBox::information(this,"提示","修改信息成功！");

          }
    }
}

void MainWindow::on_btn_person_back_clicked()
{
    this->close();
    login *w = new login ();
    w->show();
}

void MainWindow::on_btn_person_update_clicked()
{
    personInfo *info = new personInfo(user->username);
    info->show();
}

void MainWindow::on_toolButton_clicked()
{
    QDateTime current_time= QDateTime::currentDateTime();
    QString ct = current_time.toString("yyyy.mm.dd hh:mm:ss ddd");
    qDebug()<<ct;
    ui->textEdit->append(ct);
}
