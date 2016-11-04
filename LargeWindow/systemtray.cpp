#include "systemtray.h"
#include "myapplication.h"

#include <QDebug>
#include <QDesktopWidget>
#include <QTimer>

namespace WINDOW {
SystemTray::SystemTray(QWidget *parent):
    QSystemTrayIcon(parent)
{
    {//скрыть иконку
        auto *A = actShowHidden = new QAction();
        A->setText(tr("Show/Hidden"));
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slShowHidden()));
    }

    {//показать сообщение
        auto *A = actMessage = new QAction();
        A->setText(tr("Info"));
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slShowMessage()));
    }

    {//изменить иконку
        auto *A = actChangeIcon = new QAction();
        A->setText(tr("ChangeIcon"));
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slChangeIcon()));
    }

    {//информация о экранах
        auto *A = actDesktop = new QAction();
        A->setText(tr("About Desktop"));
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slAboutDesktop()));
    }

    {//Выход из приложения
        auto *A = actQuit = new QAction();
        A->setText(tr("Quit"));
        connect(A,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    }

    setIcon(QPixmap(":/icons/button_green"));//Иконка для отображения в системном трее
    setToolTip(tr("Large Window"));//Всплывающая подсказка

    trayMenu = new QMenu();
    trayMenu->addAction(actShowHidden);
    trayMenu->addAction(actMessage);
    trayMenu->addAction(actChangeIcon);
    trayMenu->addAction(actDesktop);
    trayMenu->addAction(actQuit);

    setContextMenu(trayMenu);
}

void SystemTray::slShowHidden()
{
    qDebug() << "Сработал сигнал Hiddend/Show системном трее";
    emit hidden_window();

    flagShow = !flagShow;
    flagShow?setIcon(QPixmap(":/icons/button_green")):setIcon(QPixmap(":/icons/button_red"));

}

void SystemTray::slShowMessage()
{
     this->showMessage(tr("Info about programm"),tr("Autor: Kadochnikov Andrey \n Version 10.0.0 \n Data 18.10.2016"),
                       QSystemTrayIcon::Information,3000);
}

void SystemTray::slChangeIcon()
{
     setIcon(QPixmap(":/icons/button_blue"));
}

bool SystemTray::event(QEvent *ev)
{
    if(ev->type() == QEvent::MouseButtonDblClick)
    {
        qDebug() << "двойной клик прочитан";
        slShowHidden();
    }
    return true;
}

void SystemTray::slAboutDesktop()
{
    QString str = "";
    QDesktopWidget *desk = MyApplication::desktop();
    for(int i = 0; i < desk->numScreens(); i++)
    {        
        str.append(QString (" Display: %1").arg(i+1));
        str.append(QString (" width: %1").arg(desk->screenGeometry(i).width()));
        str.append(QString (" heigth: %1 \n").arg(desk->screenGeometry(i).height()));
        this->showMessage("About Desktop",str,QSystemTrayIcon::Information,3000);

        qDebug() << QString("Сработало %1-й раз").arg(i+1) ;
        delay(3000);//эту функцию прописываем сами
        //не работает
        QTimer *timer = new QTimer(this);
        timer->setInterval(300);
        timer->start(500);
      }

}
//Задержка м/с
void SystemTray::delay(int n)
{
    QEventLoop loop;
    QTimer::singleShot(n,&loop, SLOT(quit()));
    loop.exec();
}

 SystemTray::~SystemTray()
{

}


}

