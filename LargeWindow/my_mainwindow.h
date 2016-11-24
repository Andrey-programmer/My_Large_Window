#ifndef MY_MAINWINDOW_H
#define MY_MAINWINDOW_H

#include "SubWindows.h"
#include "systemtray.h"
#include "drawimage.h"
#include "file_system.h"
#include "model_view.h"


#include <QMainWindow>
#include <QToolBar>
#include <QEvent>
#include <QTranslator>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>
#include <QTreeWidget>



namespace WINDOW {

class My_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit My_MainWindow(QWidget *parent = 0);
    virtual ~My_MainWindow();

private:
    bool flagShowHidden = true;

    File_System *directory;

    SystemTray *trayIcon;

    QFrame *mainFrame;
    QTranslator* pTranslator;

    QToolBar *tbSubwindow;
    QToolBar *tbActions;

    QAction *actOther;
    QAction *actEnterField;
    QAction *actImages;


    QAction *actToolbars;
    QAction *actBootmarks;
    QAction *actAuto;

    QAction *actLanguage;
    QAction *actLanguageDefault;

    QMenu *menuModels;
    QAction *actLTT;
    QAction *actStdItemModel;
    QAction *actFile_System;

    QMenu *menuFile;
    QAction *actReadFromFile;
    QAction *actWriteToFile;
    QAction *actDir;
    QAction *actAllDirectory;
    QAction *actCopyFile;
    QAction *actBinarFileWrite;
    QAction *actBinarFileRead;
    QMessageBox *msg;

    QMenu *Menubar;

    QLabel *lbl_X;
    QLabel *lbl_Y;

    QLabel *lbl_Screen;

    SubWindows_1 *SubWindow_1;
    SubWindows_2 *SubWindow_2;
    SubWindows_3 *SubWindow_3;
    SubWindows_4 *SubWindow_4;

    bool flag_tool = false;//Флаг для переключения видимости toolbara subwindows
    bool flag_bootmarks = false; //флаг для переключения видимости toolbara bootmarks

protected:
    void retranslateUi();
    void changeEvent(QEvent *event) override;//метод получения событий, в данном случае событие перевода приложения
    virtual void mouseMoveEvent(QMouseEvent *event);

protected slots:
    void EnterField();
    void slSetOther();
    void slImages();

    void miniwindows(bool);
    void bootmarks(bool);
    void slAutoDialog();

    //Слоты транслятора
    void slLanguage();
    void slLanguageDefault();

    //Слоты меню File
    void slReadFile();
    void slWriteFile();
    void slDir();
    void slAllDirectory();
    void slCopyFile();
    void slBinarFileWrite();
    void slBinarFileRead();

    //Слот сокрытия приложения
    void slHiddenWindow();
    void slTimerHiddenWindow();

    void slDoubleClick(QSystemTrayIcon::ActivationReason reason);

    void slScreenSHot();//Скриншот

    //Слоты работы с МОДЕЛЬ-ПРЕДСТАВЛЕНИЕ
    void slLTT();
    void slStdItemModel();
    void slFile_System();

};
}



#endif // MY_MAINWINDOW_H
