#include "auto_frame.h"
#include "plus_dialog.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QValidator>
#include <QCompleter>
#include <QDebug>
#include <typeinfo>
#include <QImage>


namespace WINDOW{

//QString Plus_Mark_dialog::plMark;//-глобальная переменная

Auto_Frame::Auto_Frame(QWidget *parent)://-конструктор класса
    QFrame(parent)
{
    setObjectName("Car_Settings");


    grProperties = new QGroupBox(tr("Data car"));//Рамочка вокруг группы
    grProperties->setObjectName("gpProperties");
    grProperties->setMinimumHeight(250);


    //Подключаем свойства машины
    Properties = new DATAS::Properties_Cars();
    DataFrame = new QFrame();
    DataFrame->setObjectName("DataFrame");

    //-------------------------------------
    lbl_Number = new QLabel(tr("Number"));
    line_Number = new QLineEdit();
    lbl_Number->setBuddy(line_Number);
    plusNumber = new QPushButton("+");

    QGridLayout *grLayout = new QGridLayout();

    auto *fr_Number = new QFrame();
    auto *hLayout10 = new QHBoxLayout();
    fr_Number->setObjectName("GridLayout");

    //ХЗ знаю как это работает но добавление QSpaser в качестве итема раздвигает пространство по максимуму
    hLayout10->addItem(new QSpacerItem(0,0,QSizePolicy::MinimumExpanding,QSizePolicy::Expanding));
    hLayout10->addWidget(line_Number);
    hLayout10->addWidget(plusNumber);
    hLayout10->setContentsMargins(2,2,2,2);//Устанавливаем отступы слоя от внешних рамок
    fr_Number->setLayout(hLayout10);

    grLayout->addWidget(lbl_Number,0,0);
    grLayout->addWidget(fr_Number,0,1);

    grLayout->setSpacing(3);//толщина стенки между объектами слоя

    line_Number->setFixedWidth(180);
    lbl_Number->setFixedWidth(180);
    plusNumber->setFixedWidth(30);
    plusNumber->setObjectName("Plus");

    //Валидатор для ввода номера
    QRegExp regNumber("[a-zA-Z0-9]{7}");
    line_Number->setValidator(new QRegExpValidator(regNumber,this));
    //-------------------------------------

    auto *fr_Mark = new QFrame();
    auto *hLayout9 = new QHBoxLayout();
    fr_Mark->setObjectName("GridLayout");

    lbl_Mark = new QLabel(tr("Mark"));
    cmb_Mark = new QComboBox();
    lbl_Mark->setBuddy(cmb_Mark);
    plusMark = new QPushButton("+");

    hLayout9->addItem(new QSpacerItem(0,0,QSizePolicy::MinimumExpanding,QSizePolicy::Expanding));
    hLayout9->addWidget(cmb_Mark);
    hLayout9->addWidget(plusMark);
    hLayout9->setContentsMargins(2,2,2,2);
    fr_Mark->setLayout(hLayout9);

    grLayout->addWidget(lbl_Mark,1,0);
    grLayout->addWidget(fr_Mark,1,1);

    cmb_Mark->setFixedWidth(180);
    lbl_Mark->setFixedWidth(180);
    plusMark->setFixedWidth(30);
    plusMark->setObjectName("Plus");
    fcmbMark(cmb_Mark);
    //-------------------------------------

    auto *fr_Model = new QFrame();
    auto *hLayout8 = new QHBoxLayout();
    fr_Model->setObjectName("GridLayout");

    lbl_Model = new QLabel(tr("Model"));
    cmb_Model = new QComboBox();
    cmb_Model->setEditable(true);//Добавляем возможность добавления элементов
    lbl_Model->setBuddy(cmb_Model);
    plusModel = new QPushButton("+");

    hLayout8->addItem(new QSpacerItem(0,0,QSizePolicy::MinimumExpanding,QSizePolicy::Expanding));
    hLayout8->addWidget(cmb_Model);
    hLayout8->addWidget(plusModel);
    hLayout8->setContentsMargins(2,2,2,2);
    fr_Model->setLayout(hLayout8);

    grLayout->addWidget(lbl_Model,3,0);
    grLayout->addWidget(fr_Model,3,1);

    cmb_Model->setFixedWidth(180);
    lbl_Model->setFixedWidth(180);
    plusModel->setFixedWidth(30);
    plusModel->setObjectName("Plus");

    //-------------------------------------

    auto *fr_Color = new QFrame();
    auto *hLayout7 = new QHBoxLayout();
    fr_Color->setObjectName("GridLayout");

    lbl_Color = new QLabel(tr("Color"));
    line_Color = new QLineEdit();
    line_Color->setWindowTitle(tr("Color"));
    line_Color->setFixedWidth(180);
    plusColor = new QPushButton("+");

    QStringList *list_color = new QStringList();//создаём лист данных
    copyColorList(list_color);//формируем начинку листа
/*
    *list_color << "Red"
                << "Blue"
                << "Gray"
                << "Silver"
                << "White"
                << "Black";*/

    qDebug() << (*list_color)[2];//проверка - выводим элемент листа на экран

    QCompleter *completer_color = new QCompleter(*list_color);//формируем компановщик и помещаем в компановщик лист
    completer_color->setCaseSensitivity(Qt::CaseInsensitive );//отключаем чувствительность к регистру
    line_Color->setCompleter(completer_color);//устанавливаем компановщик для поля
    line_Color->show();//отображаем содержимое поля

    hLayout7->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Expanding));
    hLayout7->addWidget(line_Color);
    hLayout7->addWidget(plusColor);
    hLayout7->setContentsMargins(2,2,2,2);
    fr_Color->setLayout(hLayout7);

    grLayout->addWidget(lbl_Color,4,0);
    grLayout->addWidget(fr_Color,4,1);


    lbl_Color->setFixedWidth(180);
    plusColor->setFixedWidth(30);
    plusColor->setObjectName("Plus");


    //-------------------------------------

    auto *fr_Data = new QFrame();
    auto *hLayout6 = new QHBoxLayout();
    fr_Data->setObjectName("GridLayout");

    lbl_Date_of_reristration = new QLabel(tr("Date_of_registration"));
    line_Date_of_reristration = new QLineEdit();
    lbl_Date_of_reristration->setBuddy(line_Date_of_reristration);
    line_Date_of_reristration->setInputMask("00.00.0000");
    plusData = new QPushButton("+");

    hLayout6->addItem(new QSpacerItem(0,0,QSizePolicy::MinimumExpanding,QSizePolicy::Expanding));
    hLayout6->addWidget(line_Date_of_reristration);
    hLayout6->addWidget(plusData);
    hLayout6->setContentsMargins(2,2,2,2);
    fr_Data->setLayout(hLayout6);

    grLayout->addWidget(lbl_Date_of_reristration,2,0);
    grLayout->addWidget(fr_Data,2,1);

    line_Date_of_reristration->setFixedWidth(180);
    lbl_Date_of_reristration->setFixedWidth(180);
    plusData->setFixedWidth(30);
    plusData->setObjectName("Plus");

    //-------------------------------------
    auto *fr_Category = new QFrame();
    auto *hLayout5 = new QHBoxLayout();
    fr_Category->setObjectName("GridLayout");

    lbl_Category = new QLabel(tr("Category"));
    cmb_Category = new QComboBox();
    lbl_Category->setBuddy(cmb_Category);
    auto *lbl_buf = new QLabel();//создаем пустую метку для обеспечения отступа
    lbl_buf->setFixedWidth(30);

    hLayout5->addItem(new QSpacerItem(0,0,QSizePolicy::MinimumExpanding,QSizePolicy::Expanding));
    hLayout5->addWidget(cmb_Category);
    hLayout5->addWidget(lbl_buf);//включаем пустую метку в слой
    hLayout5->setContentsMargins(2,2,2,2);
    fr_Category->setLayout(hLayout5);

    grLayout->addWidget(lbl_Category,5,0);
    grLayout->addWidget(fr_Category,5,1);

    cmb_Category->setFixedWidth(180);
    lbl_Category->setFixedWidth(180);

    //комбобокс Категория:
    cmb_Category->addItem(tr("Passenger"),DATAS::Passenger);
    cmb_Category->addItem(tr("Truck"),DATAS::Truck);
    cmb_Category->addItem(tr("Motorcycle"),DATAS::Motorcycle);

    //-------------------------------------
    QVBoxLayout *vLayout4 = new QVBoxLayout();
    vLayout4->addLayout(grLayout);//Номер

    DataFrame->setLayout(vLayout4);//рамка

    ScrollL = new QScrollArea();
    ScrollL->setWidget(DataFrame);
    ScrollL->setWidgetResizable(true);//Обязательно!!! позволяет внутреннему виджету менять размеры
    ScrollL->setObjectName("ScrollL");

    QVBoxLayout  *vLayout3 = new QVBoxLayout();

    vLayout3->addWidget(ScrollL);

    grProperties->setLayout(vLayout3);
//-------------------------------------------//
    //Рамка И Фото в QGroupBox//
    grImage =  new QGroupBox(tr("Photo"));
    grImage->setObjectName("autoPhoto");
    \
    QImage img(":/JPEG/Lambarginy");
    PhotoFrame = new QFrame();//Рамка под фото
    PhotoFrame->setObjectName("PhotoFrame");
   // PhotoFrame->setFixedSize(img.size());


    ScrollImage = new QScrollArea();
    ScrollImage->setWidgetResizable(true);

    lbl_Image = new QLabel();

    lbl_Image->setPixmap(QPixmap::fromImage(img));//Добавляем Картинку на QLabel
    ScrollImage->setWidget(lbl_Image);

    QVBoxLayout *vLayout5 = new QVBoxLayout();
    vLayout5->addWidget(ScrollImage,0,Qt::AlignCenter);
    vLayout5->setMargin(0);

    PhotoFrame->setLayout(vLayout5);

    QVBoxLayout *vLayout6 = new QVBoxLayout();
    vLayout6->addWidget(PhotoFrame);

    grImage->setLayout(vLayout6);


//-------------------------------------------//
    //Основной слой
    QVBoxLayout  *vLayout2 = new QVBoxLayout();
    vLayout2->addWidget(grProperties);
    vLayout2->addWidget(grImage,0, Qt::AlignCenter);

    setLayout(vLayout2);

    connect(plusModel,SIGNAL(clicked(bool)),this,SLOT(slAddModel()));
    connect(plusMark,SIGNAL(clicked(bool)),this,SLOT(slMark()));


    {
        auto *A = actSelectMark = new QAction(this);
        connect(A,SIGNAL(objectNameChanged(QString)),this,SLOT(slModel(QString)));
    }
        connect(cmb_Mark,SIGNAL(activated(QString)),actSelectMark,SIGNAL(objectNameChanged(QString)));

}

void Auto_Frame::copyColorList(QStringList *stringList)
{
qDebug() << "=====";
    for(int i=0;i<Properties->Color.size();i++)//перебор до размера Вектора
    {
       //(*stringList)[i] - так можно вывести значение
                *stringList << Properties->Color[i];//поочереди вводим цвета в лист
    }

//Выводим в дебаг первый итератор
qDebug() << *(Properties->Color.begin());
}

//Прикрепляем к комбобоксу контейнер данных
void Auto_Frame::fcmbMark(QComboBox *mark)
{
     QVectorIterator<QString> it(Properties->Mark);//используем Java-итератор
     while(it.hasNext())
     {
       mark->addItem(it.next());
     }
}
//===========================================================================
//слоты на добавление данных
void Auto_Frame::slNumber()
{

}

void Auto_Frame::slMark()
{
    Plus_Mark_dialog *dia = new Plus_Mark_dialog();
    dia->exec();
    if(!dia->getResult().isEmpty())
    {
         cmb_Mark->addItem(dia->getResult());//если не пустой то добавляем
         Properties->Model[dia->getResult()]=QVector<QString>();
    }
    dia->deleteLater(); // обязательно очищаем память

   // cmb_Mark->addItem(Plus_Mark_dialog::plMark);//если с использованием глобальной переменной


}

void Auto_Frame::slModel(QString mark)
{

    cmb_Model->clear();//предварительно очищаем комбобокс



/*
    for(int it =0; it <= Properties->Model.lowerBound(mark).value().size()-1; it++)
    {
        if(!Properties->Model.lowerBound(mark).value().isEmpty())//проверяем пустой ли вектор
        cmb_Model->addItem(Properties->Model.lowerBound(mark).value().value(it));
    }
    qDebug()<<Properties->Model.lowerBound(mark).value().value(1);
    qDebug()<<(typeid(Properties->Model.lowerBound(mark).value().value(0)) == typeid(QString));*/
    //то же самое одной строкой!
    cmb_Model->addItems(Properties->Model.lowerBound(mark).value().toList());//преобразовываем QVector<QString> в QStringList
                                                                             //и добаялем весь лист в элементы QCombobox
}

void Auto_Frame::slAddModel()
{
    //добавляем к вызванной модели новые данные
   Properties->Model[cmb_Mark->currentText()]<<QInputDialog::getText(this,tr("Add model"),tr("Model:"),QLineEdit::Normal);
   slModel(cmb_Mark->currentText()); // вызывем слот с заполнением модели

}

void Auto_Frame::slColor()
{


}

Auto_Frame::~Auto_Frame()
{

}
}

