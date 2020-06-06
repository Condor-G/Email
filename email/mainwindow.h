#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include <QRadioButton>
#include <QCheckBox>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QPushButton>
#include <QIcon>
#include <QSpinBox>
#include <QCheckBox>
#include <QBoxLayout>
#include <QLabel>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include <QActionGroup>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFileDialog>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QTextCharFormat>
#include <QTextList>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QButtonGroup>
#include <QTime>
#include <QTimer>
#include <QListWidget>
#include "user.h"
#include "buttondelegate.h"
#include "login.h"
#include "personinfo.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString name,QWidget *parent = nullptr);

    ~MainWindow();

    void init_sendLetter();

    void init_tableWidget();

    void init_person();

    void mergeFormat(QTextCharFormat format);



    void saveImg(const QString &imgFileName, QString sn);

public slots:

    void ShowAlignment(int id);

    void unredo(int id);

    void showUnderlineButton();

private slots:

    void ShowFontComboBox(QString comboStr);

    void ShowSizeSpinBox(QString spinValue);

    void ShowBoldBtn();

    void ShowItalicBtn();

    void ShowColorBtn();

    void ShowCurrentFormatChanged(const QTextCharFormat &fmt);

    void ShowCursorPositionChanged();

    void on_Btn_add_clicked();

    void display(QString name);

    void on_textEdit_cursorPositionChanged();

    void button_send();

    void updateTime();

    void on_tableView_clicked(const QModelIndex &index);

    void on_tableView_star_clicked(const QModelIndex &index);

    void on_tableView_draft_clicked(const QModelIndex &index);

    void on_tableView_sended_clicked(const QModelIndex &index);

    void on_tableView_bin_clicked(const QModelIndex &index);

    void on_tableView_rubbish_clicked(const QModelIndex &index);

    void on_btn_receive_selectall_clicked();


    void on_pushButton_readall_clicked();

    void on_btn_receive_delete_clicked();

    void on_btn_receive_deleteall_clicked();

    void on_Btn_draft_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_btn_star_selectall_clicked();

    void on_btn_star_cancel_clicked();


    void on_btn_draft_delete_clicked();

    void on_btn_bin_recover_clicked();

    void on_btn_bin_selectAll_clicked();

    void on_btn_bin_delete_clicked();

    void on_btn_rubbish_selectAll_clicked();

    void on_btn_rubbish_recover_clicked();

    void on_btn_rubbish_delete_clicked();

    void on_changepic_clicked();

    void on_btn_person_back_clicked();

    void on_btn_person_update_clicked();

    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    QHBoxLayout *toplayout;
    QGridLayout *middlelayout;
    QHBoxLayout *Buttonlayout;
    QHBoxLayout *buttomlayout;
    QVBoxLayout *MainLayout;

    QLabel *fontLabel1;
    QFontComboBox *fontComboBox;
    QLabel *fontLabel2;
    QComboBox *sizeComboBox;
    QToolButton *boldBtn;
    QToolButton *italicBtn;
    QToolButton *underlineBtn;
    QToolButton *colorBtn;

    QToolButton *undoAction;
    QToolButton *redoAction;
    QToolButton *action;

    QLabel *listLabel;
    QComboBox *listComboBox;
    QToolButton *leftAction;
    QToolButton *rightAction;
    QToolButton *centerAction;
    QToolButton *justifyAction;

    QButtonGroup *Btgrp2;
    QButtonGroup *Btgrp;

    QString save_filename;
    QString save_name;
    QFileDialog *FileDlg;

    //database
    QSqlDatabase db;
    QSqlQuery query;
    QPixmap outImg;

    QStandardItemModel *model;
    QStandardItemModel *model_star;
    QStandardItemModel *model_draft;
    QStandardItemModel *model_sended;
    QStandardItemModel *model_bin;
    QStandardItemModel *model_rubbish;

    User *user;


};

#endif // MAINWINDOW_H
