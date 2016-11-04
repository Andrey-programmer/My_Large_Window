#include "data.h"

#include <QDebug>
#include <algorithm>


using namespace std;//обязательно подключить для вывода в дебаг максимального элемента


namespace WINDOW {

namespace DATAS {

Properties_Cars::Properties_Cars()
{
//Индекс в векторе формируется автоматически

    {
    Color.push_back(QObject::tr("Red"));//d случае если класс не наследован от Q_Object
    Color.push_back(tr("White"));
    Color.push_back(tr("Blue"));
    Color.push_back(tr("Black"));
    Color.push_back(tr("Gray"));
    Color.push_back(tr("Green"));
    Color.push_back(tr("Silver"));
    }

    //Сортируем вектор - или данные вектора по возрастанию
    std::sort(Color.begin(),Color.end());
    qDebug() << Color;
    //Выводим на экран номер максимального элемента
    qDebug() << "индекс максимального элемента :" << std::max_element(Color.begin(),Color.end())-Color.begin()
             << "и это элемент" << *max_element(Color.begin(),Color.end());


    //Проверка через итератор
    QVector<QString>::iterator it;
    it=lower_bound(Color.begin(),Color.end(),"Red");// используя быстрый бинарный поиск
    qDebug() << "Red №" << it-Color.begin(); //выводим индекс элемента Red на экран

    it=Color.begin()+4;
    qDebug() << *it;
    //======================================================================================

    //Марка

    {
        Mark << tr("BMW");
        Mark << tr("Mercedes");
        Mark << tr("Honda");
        Mark << tr("Wolchvagen");
        Mark << tr("Lexus");
        Mark << tr("Porshe");
    }


   std::sort(Mark.begin(),Mark.end());
   qDebug() << Mark;

   //======================================================================================

   //Модель
 //   setMultiMap(Mark); //заполняем модель Ключи-Марка

   setCarMap(Mark);

   {
           Model["Mercedes"] << "C215";
           Model["Mercedes"] << "W202";
           Model["Mercedes"] << "W210";
           Model["Mercedes"] << "P192";

           Model["Porshe"] << "Carrera GT";
           Model["Porshe"] << "918 Spyder";
           Model["Porshe"] << "Cayenne";

           Model["Lexus"] << "NX 200";
           Model["Lexus"] << "GS F";
           Model["Lexus"] << "LS 460 AWD";

   }

}

void Properties_Cars::setCarMap(QVector<QString>& mark)
{
 for(auto it : mark)
  Model[it] = QVector<QString>();
}
// или так:
/*
void Properties_Cars::setCarMap(QVector<QString> &mark)
{
    QVectorIterator<QString> it(mark);//используем Java-итератор
    while(it.hasNext())
    {
      Model.insertMulti(it.next(),QVector<QString>());
    }
}
*/

}//DATAS
}//WINDOW

