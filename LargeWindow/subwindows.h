#ifndef SUBWINDOW_1_H
#define SUBWINDOW_1_H

#include <QDockWidget>
#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QAction>
#include <QToolButton>
#include <QListWidget>


namespace WINDOW {

class SubWindows_1 : public QDockWidget
{
    Q_OBJECT

private:
    QFrame *mainFrame;
    QPushButton *butn;
    QPushButton *modalBtn;
    QLabel *lbl1;
    QLineEdit *textLine;

public:
    SubWindows_1(QWidget *parent = 0);
    virtual ~SubWindows_1();

private slots:
    void sltextUp();
    void sltextInvUp_Modal();
};

//-----------------------------------------
class SubWindows_2 : public QDockWidget
{
    Q_OBJECT

private:
    QFrame *mainFrame;
    QAction *actRed;
    QAction *actBlue;
    QAction *actGreen;
    QAction *actOther;

private slots:
    void slGreen();
    void slBlue();
    void slRed();
    void slOther();

public:
    SubWindows_2(QWidget *parent = 0);
    virtual ~SubWindows_2();
};
//------------------------------------------

class SubWindows_3 : public QDockWidget
{
    Q_OBJECT

private:
    QFrame *mainFrame;
    QListWidget *listWidget;
    QPushButton *pbPictogramm;

    void setListWidget(QListWidget *lwidget);

protected slots:
    void slPictogramm();

public:
    SubWindows_3(QWidget *parent = 0);
    virtual ~SubWindows_3();
};
//------------------------------------------
class SubWindows_4 : public QDockWidget
{
    Q_OBJECT

private:
    int X = 300,
        Y = 400;
    bool flagX = false,
         flagY = false;

    QFrame *mainFrame;
    QToolButton *Ok;
    QToolButton *Hidden;
    QPushButton *SwimButton;
    QPushButton *Shleif;
    QAction *actSwimButton;
    QAction *actHidden;

    bool swimFlag = true;//Флаг для создания бегающей кнопки. чтоб не размножалась

signals:
    void sigHidden();

private slots:
    void slSwimButton();
    void slHidden();
    void slsetPozition();
/*
protected:
    virtual void timerEvent(QTimer* );
 */

public:
    SubWindows_4(QWidget *parent = 0);
    virtual ~SubWindows_4();
};
//------------------------------------------
}


#endif // SUBWINDOW_1_H
