#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>
#include <QEvent>
#include <QMainWindow>

namespace WINDOW {

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT

private:
    bool flagShow = true;

    QAction *actShowHidden;
    QAction *actMessage;
    QAction *actChangeIcon;
    QAction *actDesktop;
    QAction *actQuit;

    QMenu *trayMenu;
    bool flagTray;

    void delay(int n);//Функция задержки

public:
    SystemTray(QWidget *parent = 0);
    virtual ~SystemTray();

signals:
    void hidden_window();

public slots:
    void slShowHidden();
    void slShowMessage();
    void slChangeIcon();
    void slAboutDesktop();

protected:
    virtual bool event(QEvent *ev);

};

}


#endif // SYSTEMTRAY_H
