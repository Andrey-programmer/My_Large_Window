#include "my_MainWindow.h"
#include "my_dialogframe.h"
#include "other.h"
#include "non_modal_dialog.h"
#include "auto_dialog.h"
#include "myapplication.h"

#include <QVBoxLayout>
#include <QMenuBar>
#include <QActionGroup>
#include <QTabWidget>
#include <QDebug>
#include <QIcon>
#include <QCoreApplication>
#include <QStatusBar>
#include <QInputDialog>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QTimer>
#include <QFileDialog>
#include <QDateTime>
#include <QImage>
#include <QToolButton>
#include <QDesktopWidget>
#include <QScreen>


/*
 * Прогресс обработки любого файла можно вычислить так:
 * QFile file("box.txt");
//...
int progress = file.pos()*100/file.size();
*/
namespace WINDOW {

My_MainWindow::My_MainWindow(QWidget *parent) : QMainWindow(parent)
{

 setWindowTitle(tr("My Large Window"));
 setMinimumSize(600,600);

 mainFrame = new QFrame();
 mainFrame->setObjectName("mainFrame");
 setCentralWidget(mainFrame);

//Добавляем СтатусБар============================
 lbl_X = new QLabel(this);
 lbl_Y = new QLabel(this);
 //не работает
 mainFrame->setMouseTracking(true);//Включаем отслеживание координат при нажатии левой кнопки мыши

 statusBar()->addWidget(lbl_X);
 statusBar()->addWidget(lbl_Y);
 setMouseTracking(true);//в основной класс добавлять обязательно для отслеживания курсора
//=================================================

 QVBoxLayout *vLayout10 = new QVBoxLayout();
 vLayout10->setMargin(0);//делаем отступы от рамки равными нулю
 lbl_Screen = new QLabel();//Метка для размещения скриншота
 vLayout10->addWidget(lbl_Screen,20,Qt::AlignBaseline);//Размещаем метку
 mainFrame->setLayout(vLayout10);// натягиваем слой на рамку

 QIcon icon(":/icons/fox");
 setWindowIcon(icon);
 setWindowIconText("Fox");//хз зачем и где

 //-----------Интересные флаги--------------------------------------

 //setWindowFlags(Qt::CustomizeWindowHint);//свойство устанавливает шапку главного окна невидимой
 //setWindowFlags(Qt::WindowCloseButtonHint);//оставляет из кнопок только снопку закрытя
 /*setWindowFlags(Qt::Window
                | Qt::MSWindowsFixedSizeDialogHint
                | Qt::X11BypassWindowManagerHint
                | Qt::WindowTitleHint
                | Qt::CustomizeWindowHint);//делает окно фиксированным без кнопок но с возможностью перемещения
*/
/* setWindowFlags(Qt::Popup
                | Qt::MSWindowsFixedSizeDialogHint); //делает окно закрывающимся при нажатии на шапку
*/
//setWindowFlags(Qt::Tool);//хороший вид, но без иконки и кнопок свернуть развернуть.
 //setWindowFlags(Qt::SplashScreen); //въеденое окно без возможности перемещения, закрытия, кнопок и рамки
//setWindowFlags(Qt::Dialog);//окно со знаком вопроса

 //----------------------------------------------------------------------------------
 QActionGroup *ActionGroup = new QActionGroup(this);
 ActionGroup->setExclusive(true);//позволяет отключать все экшены при включённом одном

 //Дествие 1: создаем вкладку dialogframe
 {
 QAction *A = actEnterField = new QAction(this);
 A->setText(tr("Autorization"));
 A->setShortcut(tr("Ctrl+A"));
 ActionGroup->addAction(A);
 connect(A,SIGNAL(triggered(bool)),this,SLOT(EnterField()));

 QIcon icon(":/icons/disc");
 A->setIcon(icon);
 }

 //Дествие: создаем вкладку other
 {
 QAction *A = actOther = new QAction(this);
 A->setText(tr("Other"));
 A->setShortcut(tr("Ctrl+O"));
 ActionGroup->addAction(A);
 connect(A,SIGNAL(triggered(bool)),this,SLOT(slSetOther()));

 QIcon icon(":/icons/car_1");
 A->setIcon(icon);
 }

 //======= Экшен для работы с картинкой =============

  {
      QAction *A = actImages = new QAction(this);
      A->setText(tr("Menu Image"));
      A->setShortcut(tr("Ctrl+I"));
      ActionGroup->addAction(A);
      connect(A,SIGNAL(triggered(bool)),this,SLOT(slImages()));

      QIcon icon(":/icons/fox");
      A->setIcon(icon);

  }




 //Создаём Экшн для суб_окошек
 {
     QAction *A = actToolbars = new QAction(this);
     A->setText(tr("&SubWindows"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(miniwindows(bool)));

     QIcon icon(":/icons/periya");
     A->setIcon(icon);
 }
 //экшн для toolbar закладок
 {
     QAction *A = actBootmarks = new QAction(this);
     A->setText(tr("&Bootmarks"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(bootmarks(bool)));

     QIcon icon(":/icons/folder_doc");
     A->setIcon(icon);
 }
 //экшн диалога Auto
 {   QAction *A = actAuto = new QAction();
     A->setText(tr("Cars"));
     A->setShortcut(tr("Ctrl+C"));
     ActionGroup->addAction(A);
     connect(A,SIGNAL(triggered(bool)),this, SLOT(slAutoDialog()));

     QIcon icon(":/icons/car_10");
     A->setIcon(icon);
 }

 //============= ЭКШЕНЫ ТРАНСЛЯТОРА ========================================//

 {
     QAction *A = actLanguage = new QAction(this);
     A->setText(tr("rus"));
     A->setShortcut(tr("Ctrl+R"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slLanguage()));

 }

 {
     QAction *A = actLanguageDefault = new QAction(this);
     A->setText(tr("eng"));
     A->setShortcut(tr("Ctrl+E"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slLanguageDefault()));

 }

//================= ЭКШЕНЫ типа МОДЕЛЬ-ПРЕДСТАВЛЕНИЕ ====================
 {
     QAction *A = actLTT = new QAction(this);
     A->setText(tr("List+Tree+Table"));
     A->setIcon(QIcon(":/icons/loop"));
     connect(A,SIGNAL(triggered(bool)),this, SLOT(slLTT()));
 }

 {
     QAction *A = actStdItemModel = new QAction(this);
     A->setText(tr("StdItemModel"));
     A->setIcon(QIcon(":/icons/folder_doc"));
     connect(A,SIGNAL(triggered(bool)),this, SLOT(slStdItemModel()));
 }

 {
     QAction *A = actFile_System = new QAction(this);
     A->setText(tr("File System"));
     A->setIcon(QIcon(":/icons/File_Tree"));
     connect(A,SIGNAL(triggered(bool)),this, SLOT(slFile_System()));
 }
 //======================ЭКШЕНЫ ДЛЯ РАБОТЫ С ФАЙЛАМИ=====================================
 {
     QAction *A = actReadFromFile = new QAction(this);
     A->setText(tr("Read file"));
     A->setShortcut(tr("Ctrl+F"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slReadFile()));

 }

 {
     QAction *A = actWriteToFile = new QAction(this);
     A->setText(tr("Write file"));
     A->setShortcut(tr("Ctrl+W"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slWriteFile()));
     A->setEnabled(false);//Делаем его изначально неактивным так как читать будем только после Read экшена

 }
 {
     QAction *A = actDir = new QAction(this);
     A->setText(tr("Directory"));
     A->setShortcut(tr("Ctrl+D"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slDir()));

 }

 {
     QAction *A = actAllDirectory = new QAction(this);
     A->setText(tr("All Directory"));
     A->setShortcut(tr("Ctrl+A+D"));
     ActionGroup->addAction(A);//так как будем менять центральный виджет
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slAllDirectory()));

 }

 {
     QAction *A = actCopyFile = new QAction(this);
     A->setText(tr("Copy"));
     A->setShortcut(tr("Ctrl+C"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slCopyFile()));

 }

 {
     QAction *A = actBinarFileWrite = new QAction(this);
     A->setText(tr(".img to .bin"));
     A->setShortcut(tr("Ctrl+B"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slBinarFileWrite()));

 }

 {
     QAction *A = actBinarFileRead = new QAction(this);
     A->setText(tr(".bin to .img"));
     A->setShortcut(tr("Ctrl+B"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slBinarFileRead()));

 }
//========================================================================================================

    //===========Меню Файл=========//
  menuFile = menuBar()->addMenu(tr("&File"));
  menuFile->addAction(actReadFromFile);
  menuFile->addAction(actWriteToFile);
  menuFile->addAction(actDir);
  menuFile->addAction(actAllDirectory);
  menuFile->addAction(actCopyFile);
  menuFile->addAction(actBinarFileWrite);
  menuFile->addAction(actBinarFileRead);



//Добавляем Меню с полем ввода и Другим... )
 Menubar = menuBar()->addMenu(tr("&Bookmarks"));
 Menubar->addAction(actEnterField);//Экшн поле ввода
 Menubar->addAction(actOther);//Экшн Открыть вкладку Другое..
 Menubar->addAction(actImages);//работа с картинкой

 //============ Меню смены языка ================
 QMenu *Language = new QMenu(tr("&Language"));
 Language->addAction(actLanguage);
 Language->addAction(actLanguageDefault);

 //Меню ОТРЫВНОЕ с панелями
 QMenu *menuToolbars = menuBar()->addMenu(tr("&Toolbars"));
 menuToolbars->addAction(actToolbars);
 menuToolbars->addAction(actBootmarks);
 menuToolbars->addSeparator();//Добавляем линию подраздела(сеперетор)
 menuToolbars->addMenu(Language);//добавляем подменю
 menuToolbars->setTearOffEnabled(true);
 menuToolbars->setWindowTitle(tr("Toolbars"));

 //Меню с диалогами
 QMenu *dialogs = menuBar()->addMenu(tr("&Dialogs"));
 dialogs->addAction(actAuto);

  //Создание припаркованных окон
 //--------------------------------------------------
 QMenu *SubWindow = menuBar()->addMenu(tr("&SubWindows"));

 SubWindow_1 = new SubWindows_1();
 addDockWidget(Qt::LeftDockWidgetArea,SubWindow_1);//место по отношению к главному окну
 SubWindow->addAction(SubWindow_1->toggleViewAction());//добавляем подменю в котором переключаем видимость окон
 QIcon icon_3(":/icons/button_yellow");
 SubWindow_1->toggleViewAction()->setIcon(icon_3);//иконка вместо флажка

 SubWindow_2 = new SubWindows_2();
 addDockWidget(Qt::RightDockWidgetArea,SubWindow_2);
 SubWindow->addAction(SubWindow_2->toggleViewAction());
 QIcon icon_4(":/icons/button_red");
 SubWindow_2->toggleViewAction()->setIcon(icon_4);

 SubWindow_3 = new SubWindows_3();
 addDockWidget(Qt::TopDockWidgetArea,SubWindow_3);
 SubWindow->addAction(SubWindow_3->toggleViewAction());
 QIcon icon_5(":/icons/button_green");
 SubWindow_3->toggleViewAction()->setIcon(icon_5);

 SubWindow_4 = new SubWindows_4();
 addDockWidget(Qt::BottomDockWidgetArea,SubWindow_4);
 SubWindow->addAction(SubWindow_4->toggleViewAction());
 QIcon icon_6(":/icons/button_blue");
 SubWindow_4->toggleViewAction()->setIcon(icon_6);

 //Устанавливаем положение закладок в зависимости
 //от расположения припаркованных окон
 setTabPosition(Qt::TopDockWidgetArea,QTabWidget::North);
 setTabPosition(Qt::BottomDockWidgetArea,QTabWidget::North);
 setTabPosition(Qt::LeftDockWidgetArea,QTabWidget::West);
 setTabPosition(Qt::RightDockWidgetArea,QTabWidget::East);
 setTabShape(QTabWidget::Triangular);//закладки со скошенными углами


 //формируем Toolbar из наших экшенов
 tbActions = new QToolBar(this);
 tbActions->setWindowTitle(tr("Actions"));
 tbActions->addAction(actEnterField);
 tbActions->addAction(actOther);
 tbActions->setVisible(false);
 addToolBar(Qt::TopToolBarArea,tbActions);//Обязательная строка с указанием где разместить тулбар


 //Формируем тулбар для наших цветных суб_окошек
 tbSubwindow = new QToolBar(this);
 tbSubwindow->setWindowTitle(tr("&Subwindows"));
 tbSubwindow->addAction(SubWindow_1->toggleViewAction());//видимость включается галочкой
 tbSubwindow->addAction(SubWindow_2->toggleViewAction());
 tbSubwindow->addAction(SubWindow_3->toggleViewAction());
 tbSubwindow->addAction(SubWindow_4->toggleViewAction());
 tbSubwindow->setVisible(false);
 addToolBar(Qt::TopToolBarArea,tbSubwindow);
 tbSubwindow->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//Показывать не только иконку но и текст

 connect(SubWindow_4,SIGNAL(sigHidden()),this,SLOT(slTimerHiddenWindow()));
 connect(SubWindow_4,SIGNAL(signScreenShot()),this,SLOT(slScreenSHot()));

 //======== Меню Модель-Представление==========================
 menuModels = menuBar()->addMenu(tr("&Models"));
 menuModels->addAction(actLTT);
 menuModels->addAction(actStdItemModel);
 menuModels->addAction(actFile_System);


 //===================Подключаем СИСТЕМНЫй ТРЕЙ===================
   trayIcon = new SystemTray(this);
   trayIcon->show();

  connect(trayIcon,SIGNAL(hidden_window()),this,SLOT(slHiddenWindow()));
  connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(slDoubleClick(QSystemTrayIcon::ActivationReason)));//Отслеживаем двойной клик системного трея

}

//====== СЛОТы, ПРЯЧУЩИЕ ГЛАВНОЕ ОКНО MAINWINDOW!!! ==============
void My_MainWindow::slHiddenWindow()
{
    flagShowHidden = !flagShowHidden;
    flagShowHidden?this->show():this->hide();


}

void My_MainWindow::slDoubleClick(QSystemTrayIcon::ActivationReason reason)
{
   if(reason == QSystemTrayIcon::DoubleClick)
   {
       qDebug()<<"Двойной клик по трею";
       slHiddenWindow();
   }
}
//==============================================


//закрытие по таймеру
void My_MainWindow::slTimerHiddenWindow()
{
    QTimer timer;
    timer.singleShot(2000, this, SLOT(hide()));

    flagShowHidden = false;

}


//======================СЛОТЫ РАБОТЫ С ФАЙЛАМИ===========================================
//Слот чтения файла
void My_MainWindow::slReadFile()
{
    QString path;
    path = QInputDialog::getText(this,tr("File"),tr("Enter a path"),QLineEdit::Normal);

    QFile myFile(path);
    if(!myFile.open(QFile::ReadOnly|QFile::Text))
    {
        statusBar()->showMessage(tr("Error!!!"));
        QMessageBox::information(this,tr("Error!"),tr("Path not correct!"));
        return;
    }
    statusBar()->showMessage("Read from file: "+path);
    QTextStream stream(&myFile);

    QString buffer = stream.readAll();
    myFile.flush();// сбросить всё с файла в программу независимо от объёма кванта
    myFile.close();//закрываем файл
    msg = new QMessageBox(this);//D:\Qt\Large_Window\Large_Window\LargeWindow\my_mainwindow.cpp
    msg->setWindowTitle(path);
    msg->setText(buffer);
    QTimer::singleShot(15000, msg, SLOT(close()));//Таймер
    msg->show();

    actWriteToFile->setEnabled(true);//делаем активным запись в файл)
}

void My_MainWindow::slWriteFile()
{

    QFile myFile("./text.txt");
        if(!myFile.open(QFile::Append|QFile::Text))
    {
        statusBar()->showMessage(tr("Error!!!"));
        QMessageBox::information(this,tr("Error!"),tr("Path not correct!"));
        return;
    }

    QTextStream stream(&myFile);//делаем файл - потоком
    stream<<msg->text();//Пишем из ранее прочитанного окна. иначе выдает ошибку
    myFile.close();

}

void My_MainWindow::slDir()
{

    QString path = QDir::current().absolutePath();//Прописываем путь по умолчанию
    QString str = QFileDialog::getExistingDirectory(0,tr("Select a Directory"), path);//Получаем путь из Browse
    if(!str.isEmpty()) path = str;//если выбранная строка не пуста, то устанавливаем выбранный путь.

    QString buffer;
    QDir *myDir = new QDir(path);


    for(QFileInfo temp: myDir->entryInfoList())
    {
        buffer += temp.filePath()+'\n';//Путь к файлу
        buffer += temp.created().toString()+'\n';//Дата и время создания

        {//Метод для вывода размера кбт,Мбт и тд...
        qint64 i=0;
        int sizefile = temp.size();
        for(;sizefile>1023; sizefile /= 1024, ++i){ }
        buffer += QString().setNum(sizefile)+"BKMGT"[i]+'\n';//Выводим размер
        }
        buffer +="=======================================\n";
    }

    QMessageBox::information(this,tr("All files"),buffer+tr("count of elements: ")+QString::number(myDir->count()-2));//выводим буфер и количество элементов

    //myDir->mkdir("Folder_XP");//создаёт папку

}

void My_MainWindow::slAllDirectory()
{

    qDebug() << "Слот slAllDirectory сработал";
    QString path = QDir::current().absolutePath();//Прописываем путь по умолчанию
    QString str = QFileDialog::getExistingDirectory(0,tr("Select a Directory"), path);//Получаем путь из Browse
    if(!str.isEmpty()) path = str;//если выбранная строка не пуста, то устанавливаем выбранный путь.



    {//  Стандартная смена центрального виджета
    QWidget *S = centralWidget();
    setCentralWidget(0);
    delete S;

    QWidget *W = directory = new File_System(str,this);
    setCentralWidget(W);
    actAllDirectory->setCheckable(true);
    actAllDirectory->setChecked(true);
    }
}
//Слот копирования файлов
void My_MainWindow::slCopyFile()
{
    QFile myFile1("./text.txt");

    if(!myFile1.open(QFile::ReadOnly|QFile::Text))
    {
        statusBar()->showMessage(tr("Error!!!"));
        QMessageBox::information(this,tr("Error!"),tr("Path not correct!"));
        return;
    }

    QFile myFile2("./textCopy.txt");

    if(!myFile2.open(QFile::Append|QFile::Text))
    {
        statusBar()->showMessage(tr("Error!!!"));
        QMessageBox::information(this,tr("Error!"),tr("Path not correct!"));
        return;
    }

    QByteArray buf = myFile1.readAll();
    myFile2.write(buf);
    myFile1.close();
    myFile2.close();

}

void My_MainWindow::slBinarFileWrite()
{
    QFile file("file.bin");
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_7);//обизательно прописываем версию создания бинарного потока
        stream << QImage(QFileDialog::getOpenFileName(0,tr("Select page"),"",QString("Small conteiners(*.png *.ico) ;; JPEG containers(*.jpg *.jpeg)")));
        if(stream.status() != QDataStream::Ok)
        {
            statusBar()->showMessage(tr("Error of .bin!!!"));
        }
    }
    file.close();
}

void My_MainWindow::slBinarFileRead()
{
    QImage img;
    QFile file(QFileDialog::getOpenFileName(0,tr("Select_file.bin"),"","*.bin"));
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_7);
        stream >> img;
        if(stream.status() != QDataStream::Ok)
        {
            statusBar()->showMessage(tr("Error .bin to .img!!!"));
        }
    }
    file.close();

    //Сохраняем картинку как файл
    img.save(QFileDialog::getSaveFileName(0,tr("Save image"),QDir::currentPath(),QString("ImageIco(*.ico *.png);;ImageRastr( *.bmp);;ImageJPG(*.jpg)")));

  //  QMessageBox::Information(1,"Picture format:",img.format());//Выводим на экран формат картинки
    qDebug() <<  img.format();


}

//===================================================================================================

void My_MainWindow::EnterField()
{   qDebug() << "EnterField";
    QWidget *S = centralWidget();
    setCentralWidget(0);//снимаем центральный виджет
    delete S;// очищаем память

    QWidget *W = 0;
    W = new My_DialogFrame();
    W->setObjectName("dialogframe");
    setCentralWidget(W);//ставим центральным виджетом My_DialogFrame()
    actEnterField->setCheckable(true);
    actEnterField->setChecked(true);//устанавливаем флажок в нормальное состояние
}

void My_MainWindow::slSetOther()
{qDebug() << "slSetOther";
    QWidget *S = centralWidget();
    setCentralWidget(0);
    delete S;

    QWidget *W = 0;
    W = new Other();
    setCentralWidget(W);
    actOther->setCheckable(true);
    actOther->setChecked(true);
}

//Слот открытия рамки работы с картинкой
void My_MainWindow::slImages()
{qDebug() << "slImages";
    QWidget *S = centralWidget();
    setCentralWidget(0);
    delete S;

    QWidget *W = 0;
    W = new DrawImage();
    setCentralWidget(W);
    actImages->setCheckable(true);
    actImages->setChecked(true);
}

//====================================================
void My_MainWindow::miniwindows(bool)
{
  flag_tool = !flag_tool;
  tbSubwindow->setVisible(flag_tool);
}

void My_MainWindow::bootmarks(bool)
{
  flag_bootmarks = !flag_bootmarks;
  tbActions->setVisible(flag_bootmarks);
}

void My_MainWindow::slAutoDialog()
{
    qDebug() << "slAutoDialog";
    QWidget *S = centralWidget();
    setCentralWidget(0);
    delete S;

    QWidget *W = 0;
    W = new Auto_Dialog();
    setCentralWidget(W);
    actAuto->setCheckable(true);
    actAuto->setChecked(true);
}

void My_MainWindow::slLanguage()//меняем язык
{
    pTranslator = new QTranslator(this);
    pTranslator->load(":/lang/rus");
    qApp->installTranslator(pTranslator);
     qDebug()<<"Переводчик загружен";
     actLanguage->setEnabled(false);
}

void My_MainWindow::slLanguageDefault()//меняем язык
{
     qApp->removeTranslator(pTranslator);
     qDebug()<<"переводчик удалён";
     actLanguage->setEnabled(true);
}

void My_MainWindow::changeEvent(QEvent *event)
{
   if(event->type() == QEvent::LanguageChange)
   {
       qDebug()<<"Эвент сработал";
      retranslateUi();
   }

}
//для динамического перевода мы должны прописать все названия тут
void My_MainWindow::retranslateUi()
{
    actEnterField->setText(tr("Autorization"));
    actBootmarks->setText(tr("&Bootmarks"));
    Menubar->setTitle(tr("&Bookmarks"));
    actLanguage->setText(tr("rus"));
    actLanguageDefault->setText(tr("eng"));
}

//События Мыши
void My_MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    lbl_X->setText("X="+QString().setNum(event->x()));//переводим в строку текущую координату X мыши
    lbl_Y->setText("Y="+QString().setNum(event->y()));//переводим в строку текущую координату Y мыши
}

//Скриншот экрана
void My_MainWindow::slScreenSHot()
{
    QDesktopWidget *desktop = MyApplication::desktop();
    //QPixmap pic = QPixmap::grabWindow(desktop->screen()->winId());//Делаем сам скриншот
    QScreen *screen = MyApplication::primaryScreen();//создаем объект скрина
    QPixmap pic = screen->grabWindow(desktop->screen(0)->winId(),
                                      0,0,desktop->geometry().width(),
                                      desktop->geometry().height());//Делаем сам скриншот

    lbl_Screen->clear();//Очищаем метку
    lbl_Screen->setPixmap(pic);//Устанавливаем картинку в метку
}

//=================== Слоты работы с моделями =============================
void My_MainWindow::slLTT()
{
    LTT *lttWidget = new LTT();
    lttWidget->show();
}

void My_MainWindow::slStdItemModel()
{
     StdItemModel *stdItemModelWidget = new StdItemModel();
     stdItemModelWidget->show();
}


void My_MainWindow::slFile_System()
{
    File_Model *fileSystem = new File_Model();
    fileSystem->show();
}

My_MainWindow::~My_MainWindow()
{  qDebug()<<"Деструктор сработал";
    trayIcon->hide();
    trayIcon->deleteLater();

}

}
