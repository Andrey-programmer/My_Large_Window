#include "SubWindows.h"
#include "non_modal_dialog.h"
#include "myapplication.h"
#include "my_mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QValidator>
#include <QDebug>
#include <QColorDialog>
#include <QStringList>
#include <QStringListIterator>
#include <algorithm>
#include <QTimer>
#include <QTime>
#include <QRect>
#include <QDesktopWidget>
#include <QIcon>
#include <QList>


namespace WINDOW {



SubWindows_1::SubWindows_1(QWidget *parent):
    QDockWidget(parent)
{
    setWindowTitle(tr("Yellow"));
    setMinimumSize(30,100);
    setVisible(false);// делаем невидимым по умолчанию
    mainFrame = new QFrame();
    mainFrame->setStyleSheet("QFrame{background: #FFDF00}");//устанавливаем цвет фона

    butn = new QPushButton();
    butn->setText(tr("&nonModalDialog"));
    butn->setDefault(true);

    modalBtn = new QPushButton();
    modalBtn->setText(tr("&ModalDialog"));

    textLine = new QLineEdit();
    lbl1 = new QLabel(tr("&Enter text"));
    lbl1->setBuddy(textLine);
    QRegExp stroka("[а-яА-Я*]{1,4}[0-9]{2}[/*]");
    textLine->setValidator(new QRegExpValidator(stroka, this));

    QHBoxLayout *hLayout10 = new QHBoxLayout();
    hLayout10->addWidget(lbl1);
    hLayout10->addWidget(textLine);

    QVBoxLayout *vLayout9 = new QVBoxLayout();
    vLayout9->addLayout(hLayout10);
    vLayout9->addWidget(butn,0,Qt::AlignCenter);
    vLayout9->addWidget(modalBtn, 0, Qt::AlignCenter);

    mainFrame->setLayout(vLayout9);
    setWidget(mainFrame);
    //Слоты к кнопкам
    connect(butn,SIGNAL(clicked(bool)),this,SLOT(sltextUp()));
    connect(modalBtn,SIGNAL(clicked(bool)),this,SLOT(sltextInvUp_Modal()));

}
void SubWindows_1::sltextInvUp_Modal()
{
    non_Modal_Dialog *dia = new non_Modal_Dialog(this);
    //Перебор элементов строки---------------------------------

    QString str;
    str=textLine->text();
    QStringList *strList = new QStringList();
                *strList=str.split("",QString::SkipEmptyParts);//1й параметр- разделитель, 2-c пропуском пустых частей
    QListIterator<QString> it(*strList);
    it.toBack();//нереставляем итератор в конец списка
    while(it.hasPrevious())//Обратный перебор
    qDebug()<<it.previous();
    //===========================================================

    std::reverse(strList->begin(),strList->end());
    qDebug()<<*strList;
    str=""; //опустошаем строку
    foreach(QString x, *strList)
    {
       str.append(x);//добавляем каждый элемент QStringlist в строку
    }
     qDebug()<<str;

    dia->sltextUpdia(str);
    dia->exec();
    dia->deleteLater();// очистка памяти после закрытия диалога
}

void SubWindows_1::sltextUp()
{
    non_Modal_Dialog *lia = new non_Modal_Dialog(this);
    lia->sltextUpdia(textLine->text());
    lia->show();
   // lia->deleteLater();//nene не нужно иначе окно сразу пропадёт
}


SubWindows_1::~SubWindows_1()
{

}

//--------------------------------------------------------------------------

SubWindows_2::SubWindows_2(QWidget *parent):
    QDockWidget(parent)
{
    setWindowTitle(tr("Red"));
    setMinimumSize(30,100);
    setVisible(false);
    mainFrame = new QFrame();
    mainFrame->setStyleSheet("background: red");//устанавливаем цвет фона

    QHBoxLayout *hLayout10 = new QHBoxLayout();
    mainFrame->setLayout(hLayout10);

    setWidget(mainFrame);

    setContextMenuPolicy(Qt::ActionsContextMenu);
//так работает
    {
        QAction *A  = actBlue = new QAction( this );
        A->setText(tr("Blue"));
        A->setShortcut(tr("Ctrl+B"));
        addAction(A);
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slBlue()));

        QIcon icon(":/icons/button_blue");
        A->setIcon(icon);
    }
    {
        QAction *A  = actGreen = new QAction( this );
        A->setText(tr("Green"));
        A->setShortcut(tr("Ctrl+G"));
        addAction(A);
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slGreen()));

        QIcon icon(":/icons/button_green");
        A->setIcon(icon);
    }
    {
        QAction *A  = actRed = new QAction( this );
        A->setText(tr("Red"));
        A->setShortcut(tr("Ctrl+R"));
        addAction(A);
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slRed()));

        QIcon icon(":/icons/button_red");
        A->setIcon(icon);
    }

    {
        QAction *A  = actOther = new QAction( this );
        A->setText(tr("Other"));
        A->setShortcut(tr("Ctrl+O"));
        addAction(A);
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slOther()));

        QIcon icon(":/icons/diagram");
        A->setIcon(icon);
    }

}
// Реализуем слоты (смена фона)
  void SubWindows_2::slBlue()
  {
      mainFrame->setStyleSheet("QFrame{background: blue}");

  }

  void SubWindows_2::slGreen()
  {
      mainFrame->setStyleSheet("QFrame{background: green}");
  }

  void SubWindows_2::slRed()
  {
       mainFrame->setStyleSheet("QFrame{background: red}");
  }

  void SubWindows_2::slOther()
  {
      QColor color = QColorDialog::getColor(Qt::blue,this);
      qDebug()<<color.name();//color.name() переводит цвет из rgb в hex кодировку
      mainFrame->setStyleSheet(QString("QFrame{background: %1}").arg(color.name()));
  }

SubWindows_2::~SubWindows_2()
{

}

//--------------------------------------------------------------------------

SubWindows_3::SubWindows_3(QWidget *parent):
    QDockWidget(parent)
{
    setWindowTitle(tr("Green"));
    setMinimumSize(30,100);//устанавливаем минимальные размеры
    setVisible(false);

    mainFrame = new QFrame();//Основная рамка
    mainFrame->setStyleSheet("background: green");//устанавливаем цвет фона

    QHBoxLayout *hLayoutMain = new QHBoxLayout();
    listWidget = new QListWidget();
    setListWidget(listWidget);

    QVBoxLayout *vLayout10 = new QVBoxLayout();
    hLayoutMain->addLayout(vLayout10);

    pbPictogramm = new QPushButton(tr("Pictogramm"));

    vLayout10->addWidget(listWidget);
    vLayout10->addWidget(pbPictogramm);

    mainFrame->setLayout(hLayoutMain);
    setWidget(mainFrame);

    connect(pbPictogramm,SIGNAL(clicked(bool)),this,SLOT(slPictogramm()));

 }

void SubWindows_3::setListWidget(QListWidget *lwidget)
{
    lwidget->setIconSize(QSize(50,50));// устанавливаем размер иконок для виджета
    lwidget->setSelectionMode(QAbstractItemView::MultiSelection);// разрешаем выбор нескольких элементов одновременно

    QStringList list;
    list << "Windows" << "Linux" << "MacOSX" << "Android"<<"Apple"; //формируем данные
    QListWidgetItem *lwi = 0;

    foreach (QString str, list) {
        lwi = new QListWidgetItem(str, lwidget);//каждый новый элемент автоматически добавляется в QListWidget
        lwi->setFlags(Qt::ItemIsUserCheckable);//Добавляем флажки
        lwi->setCheckState(Qt::Checked);//устанавливаем флажки в состояние (выбрано)
        lwi->setFlags(Qt::ItemIsEditable|Qt::ItemIsEnabled|Qt::ItemIsSelectable|Qt::ItemIsDragEnabled);// разрешаем редактировать
        lwi->setIcon(QIcon(":/icons/"+str));
        qDebug()<<QString(":/icons/"+str);
   }
   lwidget->resize(200,150);
}

void SubWindows_3::slPictogramm()
{
    listWidget->setViewMode(QListView::IconMode);//переводим список в режим пиктограмм
    listWidget->setFlow(QListView::TopToBottom);//заполняет виджет сверху вниз вместо слева направо
    listWidget->setSortingEnabled(true);
    listWidget->sortItems(Qt::AscendingOrder);//сортировка по возрастанию
    listWidget->setSelectionMode(QAbstractItemView::ContiguousSelection);//делаем возможным ПЕРЕКЛЮЧЕННЫЙ ВЫБОР (хз как работает, но лучше чем другие в пиктограмме)
}

SubWindows_3::~SubWindows_3()
{

}

//--------------------------------------------------------------------------

SubWindows_4::SubWindows_4(QWidget *parent):
    QDockWidget(parent)
{
    setWindowTitle(tr("Blue"));
    setMinimumSize(30,100);

    mainFrame = new QFrame();
    mainFrame->setObjectName("Blue_window");
//===Кнопка с иконкой в 1 действие===============================================
    QPixmap pix(":/icons/apple");//Подгружаем картинку

    Ok = new QToolButton();
    Ok->setText(tr("Okey"));
    Ok->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);//текст под иконкой
    Ok->setIcon(pix);
    Ok->setObjectName("Apple");
//================================================================================
    QPixmap pix2(":/icons/disc");
    Hidden = new QToolButton();
    Hidden->setText(tr("Hidden window"));
    Hidden->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//текст рядом с иконкой
    Hidden->setIcon(pix2);
    Hidden->setObjectName("Apple");

    QVBoxLayout *vLayout10 = new QVBoxLayout();
    vLayout10->addWidget(Ok,0,Qt::AlignCenter);
    vLayout10->addWidget(Hidden,20,Qt::AlignRight);
    mainFrame->setLayout(vLayout10);

    // Если хотим растянуть виджет на весь слой
    // Ok->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    // hLayout10->setContentsMargins(0,0,0,0);
    // при этом обязательно необходимо убрать
    // 0,Qt::AlignCenter)
     setWidget(mainFrame);
     setFeatures(NoDockWidgetFeatures);//убираем все действия с окна и делаем его неподвижным

     {
         auto *A = actSwimButton = new QAction();
         connect(A,SIGNAL(triggered(bool)),this,SLOT(slSwimButton()));
     }
     connect(Ok,SIGNAL(clicked(bool)),actSwimButton,SIGNAL(triggered(bool)));

     {
         auto *A = actHidden = new QAction();
         connect(A,SIGNAL(triggered(bool)),this,SLOT(slHidden()));
     }
    connect(Hidden,SIGNAL(clicked(bool)),actHidden,SIGNAL(triggered(bool)));
     //Вызываем функцию Qsrand только 1 раз и не в цикле иначе числа будут повторяться
     qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));//-генератор случайных чисел


}
//Слот плавающей кнопки:
void SubWindows_4::slSwimButton()
{


   if(swimFlag == true)
    {
    SwimButton = new QPushButton(this);//Плавающая кнопка
    SwimButton->setText(tr("SwimButton"));
    SwimButton->setObjectName("SwimButton");
    SwimButton->setWindowFlags(Qt::SplashScreen);
    SwimButton->show();

    connect(SwimButton,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(SwimButton,SIGNAL(clicked(bool)),SwimButton,SLOT(deleteLater()));

    //SwimButton->startTimer(500);
       //QTimer::singleShot(1000,this,SLOT(slsetPozition()));//-одноразовый таймер
    auto *myTimer = new QTimer(SwimButton);
    myTimer->start(100);
    connect(myTimer,SIGNAL(timeout()),SLOT(slsetPozition()));

      Shleif = new QPushButton(SwimButton);
      Shleif->setObjectName("Shleif");
      Shleif->setWindowFlags(Qt::SplashScreen);
      Shleif->setText(QString("X= %1, y= %2").arg(1000).arg(1000));// не работает
      Shleif->show();

      swimFlag = !swimFlag;
     }

}

//Плавающая ударяющаяся кнопка
void SubWindows_4::slsetPozition()

{
   Shleif->setText(QString("X= %1, y= %2").arg(X).arg(Y));// не работает
   Shleif->setGeometry(X,Y,Shleif->width(),Shleif->height());//Добавляем шлейф к кнопке

    QRect rec = MyApplication::desktop()->screenGeometry();

      if(flagX == false)
    {
        X+=(qrand()%20+1);
        flagX = X > rec.width()- 100?true:false;
    }
    if(flagX == true)
    {
         X-=(qrand()%20+1);
         flagX = X < 0?false:true;
    }
    if(flagY == false)
    {
        Y+=(qrand()%50+1);
        flagY = Y > rec.height()-40?true:false;
    }
    if(flagY == true)
    {
         Y-=(qrand()%50+1);
         flagY = Y < 0 ? false : true;
    }


    SwimButton->setGeometry(X,Y,SwimButton->width(),SwimButton->height());// не меняя размеры задаем начально положение виджета

}

void SubWindows_4::slHidden()
{
       emit sigHidden();
}

SubWindows_4::~SubWindows_4()
{

}

//--------------------------------------------------------------------------


}
