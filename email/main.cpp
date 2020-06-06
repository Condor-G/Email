#include "mainwindow.h"
#include <QApplication>
#include <QMovie>
#include <QSplashScreen>
#include <QThread>
#include <login.h>
#include <QtGui>
#include <ActiveQt/QAxWidget>
#include <login.h>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pix(":/res/splash2.gif");
        QSplashScreen splash(pix);
        splash.setWindowOpacity(0.9);
        QLabel label(&splash);
        QMovie mv(":/res/splash2.gif");
        label.setMovie(&mv);
        mv.start();
        splash.show();
        splash.setCursor(Qt::BlankCursor);
        a.processEvents();
        for(int i=0;i<3200;i+=mv.speed()){
            QCoreApplication::processEvents();
            Sleep(mv.speed());
        }


        login w;
        w.show();

        splash.finish(&w);


    return a.exec();
}
