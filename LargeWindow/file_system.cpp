#include "file_system.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

namespace WINDOW {

File_System::File_System(const QString &path, QWidget *parent ):
    QTreeWidget(parent)
{
    twgIt = new QTreeWidgetItem(this);
    twgIt->setText(0,QDir(path).dirName());//Даём имя корневой директории
    addTopLevelItem(All_Directory(path,twgIt));
    QStringList header;
    header << tr("Directory") << tr("Size") << tr("Date of created");
    setHeaderLabels(header);
    setColumnWidth(0,250);//Задаем ширину первой колонки
    setSortingEnabled(true);//Включаем сортировку при выделении заголовка

}


QTreeWidgetItem* File_System::All_Directory(const QString &path, QTreeWidgetItem *itm)
{
    QDir dir(path);

    int check = 1;//счетчик директорий
    foreach (QFileInfo temp, dir.entryInfoList()) {
        if(check > 2)
        {
          qDebug() << "сработал перебор файлов";
            QTreeWidgetItem *itm2 = new QTreeWidgetItem(itm);
            itm2->setText(0,temp.fileName());
            itm->addChild(itm2);
            if(temp.isDir())
                {
                   itm2->setIcon(0,QIcon(":/icons/folder"));
                   All_Directory(temp.absoluteFilePath(),itm2);
                }
            else
            {
                itm2->setIcon(0,QIcon(":/icons/File+"));
                {//Метод для вывода размера кбт,Мбт и тд...
                qint64 i=0;
                int sizefile = temp.size();
                for(;sizefile>1023; sizefile /= 1024, ++i){ }
                 itm2->setText(1,QString().setNum(sizefile)+"BKMGT"[i]);//Выводим размер
                 itm2->setText(2,temp.created().toString());//Дата создания файла
                }
            }


        }
        check++;
    }
    return itm;
}

File_System::~File_System()
{

}
}
