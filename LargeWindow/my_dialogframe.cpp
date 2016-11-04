#include "my_dialogframe.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QValidator>
#include <QFile>


namespace WINDOW {

My_DialogFrame::My_DialogFrame(QWidget *parent):
    QFrame(parent)
{

    //Кнопки ----------------------------------
    Ok = new QPushButton(tr("&Ok"));
    Ok->setDefault(true);
    Ok->setEnabled(false);//устанавливаем первоначальное состояние кнопки
    //Ok->setFont(QFont("Arial",18,QFont::Bold)); - параметры шрифта
    Cancel = new QPushButton(tr("&Cancel"));
    Cancel->setObjectName("CancelButton");

    QHBoxLayout *hLayout10 = new QHBoxLayout();
    QSpacerItem *hSpacer10 = new QSpacerItem(10, 20,QSizePolicy::Expanding,QSizePolicy::Minimum);
    hLayout10->addItem(hSpacer10);
    hLayout10->addWidget(Cancel);
    hLayout10->addWidget(Ok);
//---------------------------------------------
    lbl_1 = new QLabel(tr("&Enter text"));
    textLine = new QLineEdit();
    lbl_1->setBuddy(textLine);//связываем метку с полем ввода
    QRegExp stroka("[а-яА-Я]{1,3}[.][1-9]{2}[а-яА-я]{1,3}");//создаём перечень вводимых символов
    textLine->setValidator(new QRegExpValidator(stroka,this));

    cbLineText = new QCheckBox();
    cbLineText->setChecked(true);

    //слой с строкой для ввода и меткой
    QHBoxLayout *hLayout9 = new QHBoxLayout();
    hLayout9->addWidget(cbLineText);
    hLayout9->addWidget(lbl_1);
    hLayout9->addWidget(textLine);
    hLayout9->addStretch(200);
//---------------------------------------------------
    //виджеты под пароль и имя

    cbPass = new QCheckBox();
    lbl_autorization = new QLabel(tr("&Autorization"));
    lbl_autorization->setBuddy(cbPass);

    passLine = new QLineEdit();
    lbl_pass = new QLabel(tr("&Password"));
    lbl_pass->setBuddy(passLine);
    //passLine->setInputMask("0000.0000.0000.0000");
    //устанавливаем поле под пароль(делаем символы скрытыми)
    passLine->setEchoMode(QLineEdit::Password);

    lbl_name = new QLabel(tr("&Name      "));
    nameLine = new QLineEdit();
    lbl_name->setBuddy(nameLine);



    QHBoxLayout *hLayout8 = new QHBoxLayout();
    hLayout8->addWidget(cbPass);
    hLayout8->addWidget(lbl_autorization);
    hLayout8->addStretch(100);

    QHBoxLayout *hLayout6 = new QHBoxLayout();
    hLayout6->addWidget(lbl_pass);
    hLayout6->addWidget(passLine);

    QHBoxLayout *hLayout5 = new QHBoxLayout();
    hLayout5->addWidget(lbl_name);
    hLayout5->addWidget(nameLine);

    QVBoxLayout *vLayout4 = new QVBoxLayout();
    vLayout4->addLayout(hLayout5);
    vLayout4->addLayout(hLayout6);

    frame_autoriz = new QFrame();
    frame_autoriz->setLayout(vLayout4);
    frame_autoriz->setFixedWidth(300);
    frame_autoriz->setVisible(false);

    QVBoxLayout *vLayout7 = new QVBoxLayout();
    vLayout7->addLayout(hLayout8);
    vLayout7->addWidget(frame_autoriz);
    vLayout7->addStretch(200);



//------------------------------------------------




    //У Рамки приоритет в размерах над слоями, как и у TextField
    //Нижний и верхний слои раздвигаем за счет рамки
    QFrame *hLayout = new QFrame();
    hLayout->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    hLayout->setFrameStyle(StyledPanel|Sunken);
    hLayout->setLayout(vLayout7);


    QVBoxLayout *VLayout = new QVBoxLayout();
    VLayout->addLayout(hLayout9);
    VLayout->addWidget(hLayout);
    VLayout->addLayout(hLayout10);

    setLayout(VLayout);

    //Экшн нажатия кнопки Ok
    QAction *A = actOkClicked = new QAction();
    connect(A,SIGNAL(triggered(bool)),this,SLOT(clickOk()));

    //Экшн активации текстового поля
    QAction *B = actTextLine = new QAction();
    connect(B,SIGNAL(triggered(bool)),this,SLOT(slEnableTextLine()));

    //Экшн Активации полей авторизации
    QAction *C = actPassword = new QAction();
    connect(C,SIGNAL(triggered(bool)),this,SLOT(slAutorization()));

    //Вешаем Экшн на кнопку
    connect(Ok,SIGNAL(clicked(bool)),A,SIGNAL(triggered(bool)));
    //вешаем экшн на чекбокс
    connect(cbPass,SIGNAL(clicked(bool)),C,SIGNAL(triggered(bool)));
    //Закрытие при нажатии кнопки Cancel
    connect(Cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(textLine,SIGNAL(textChanged(QString)),this,SLOT(EnableOk(QString)));
    connect(cbLineText,SIGNAL(clicked(bool)),B,SIGNAL(triggered(bool)));

}

//Слоты
void My_DialogFrame::clickOk()
{
this->close();
}

void My_DialogFrame::EnableOk(QString text)
{
    Ok->setEnabled(!text.isEmpty());
}
void My_DialogFrame::slEnableTextLine()
{
    textLine->setEnabled(cbLineText->isChecked());
}

void My_DialogFrame::slAutorization()
{
    frame_autoriz->setVisible(cbPass->isChecked());
}

My_DialogFrame::~My_DialogFrame()
{

}

}

