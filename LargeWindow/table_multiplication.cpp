#include "table_multiplication.h"
#include "myapplication.h"

#include <QDebug>
#include <QBuffer>
#include <QClipboard>

namespace WINDOW {

Table_Multiplication::Table_Multiplication(QWidget *parent):
    QTableWidget(parent)
{
    setObjectName("Table_Multiplication");
    const int n = 10;

    setContextMenuPolicy(Qt::ActionsContextMenu);// Добавляем контекстное меню

    {
     auto *A = actCopy = new QAction(this);
     A->setText(tr("&Copy"));
     A->setShortcut(tr("Ctrl+S"));
     connect(A,SIGNAL(triggered(bool)),this,SLOT(slCopy()));
    }

    addAction(actCopy);


    setRowCount(n);//количество элементов таблицы должно быть определено в начале
    setColumnCount(n);

    qDebug()<< "Таблица подлключена";
    //QTableWidgetItem *tblItem = 0;
    QStringList lst; //List для сохранения заголовков

    for(int i=1; i<=n; i++)
    {
        lst.append(QString::number(i));//заполняем List
    }
    setHorizontalHeaderLabels(lst);//Горизонтальные заголовки
    setVerticalHeaderLabels(lst);//Вертикальные заголовки

    //==заполняем ячейки таблицы===
    for(int i = 0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            int l =(i+1)*(j+1);
            QTableWidgetItem* tblItem = new QTableWidgetItem(QString("%1").arg(l));//Создаём таблицу умножения
            tblItem->setTextAlignment(Qt::AlignCenter);// текст по центру
            setItem(i,j,tblItem);//Подключаем ячейки
        }
    }
    resize(300,n*60);

}

void Table_Multiplication::slCopy()
{
   QClipboard *buffer = MyApplication::clipboard();//Подключаем системный буффер
   buffer->setText(this->currentItem()->text());//копируем в него содержимое ячейки

   qDebug() << buffer->text();

}


Table_Multiplication::~Table_Multiplication()
{

}

}
