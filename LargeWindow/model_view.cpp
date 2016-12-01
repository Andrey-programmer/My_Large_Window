#include "model_view.h"

#include <QHBoxLayout>
#include <QDebug>

namespace WINDOW {

LTT::LTT(QWidget *parent):
    QWidget(parent)
{
    listmodel = new QStringListModel();//модель данных
    listmodel->setStringList(QStringList()<<tr("Windows")<<tr("Android")<<tr("Linux")
                             <<tr("Apple")<<tr("MacOSX"));//загоняем данные
    treeView = new QTreeView();
    treeView->setModel(listmodel);//устанавливаем модель для представления

    listView = new QListView();
    listView->setModel(listmodel);
    listView->setSelectionMode(QAbstractItemView::ExtendedSelection);//Возможность выбора нескольких элементов
    listView->setObjectName("ListView_1");

    tableView = new QTableView();
    tableView->setModel(listmodel);


    QItemSelectionModel *selection = new QItemSelectionModel(listmodel);//Присваиваем модель выделения элементу модели
    listView->setSelectionModel(selection);// и передаем это выделение виджетам представления
    treeView->setSelectionModel(selection);
    tableView->setSelectionModel(selection);

    QHBoxLayout *hLayout10 = new QHBoxLayout();
    hLayout10->addWidget(listView);
    hLayout10->addWidget(treeView);
    hLayout10->addWidget(tableView);

    setLayout(hLayout10);//устанавливаем центральный слой

}

LTT::~LTT()
{

}



StdItemModel::StdItemModel(QWidget *parent):
    QTreeView(parent)
{

    qDebug()<<"Сработал StdItemModel";
    QStandardItemModel *model = new QStandardItemModel(5,4);//загоняем модель данных 5x3
    for(int Row = 1; Row < 5; Row++)//перебираем главные строки первого столбца
    {
        QModelIndex index = model->index(Row,0);//присваиваем индексы
        model->setData(index,"item"+QString::number(Row+1));//заполняем строки

        //рисуем подтаблицу
        model->insertRows(0,4,index);//добавляем к главному индексу 4 подстроки
        model->insertColumns(0,3,index);//добавляем к главному индексу 3 подколонки

        for(int nRow = 0; nRow < 4; nRow++)
        {
            for(int nColomn = 0; nColomn <3; nColomn++)
            {
                QString str = QString("%1-%2").arg(nRow).arg(nColomn);//Заполняем строки
                model->setData(model->index(nRow, nColomn, index),str);
            }
        }

    }
   setModel(model);
}


StdItemModel::~StdItemModel()
{

}


File_Model::File_Model(QWidget *parent):
    QWidget(parent)
{
    QSplitter *splitter = new QSplitter(Qt::Horizontal);//объявляем разделитель

    model = new QFileSystemModel();
    model->setRootPath(QDir::rootPath());//загоняем в модель корневой путь по которой она должна раскрываться

    tree = new QTreeView();//Представление деревом
    tree->setModel(model);
    tree->setColumnWidth(0,250);// Задаём Ширину первой колонки

    table = new QTableView();//Представление таблицей
    table->setModel(model);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//Растягиваем столбец под содержимое

    //Устанавливаем связь между выбранными элементами  дерева и таблицы
    QItemSelectionModel *selection = new QItemSelectionModel(model);
    tree->setSelectionModel(selection);
    table->setSelectionModel(selection);

//помещаем в разделитель виджеты
    splitter->addWidget(tree);
    splitter->addWidget(table);

    QHBoxLayout *hLayout10 = new QHBoxLayout();
    hLayout10->addWidget(splitter);
    setLayout(hLayout10);

    setWindowTitle(tr("File_System"));

    connect(tree,SIGNAL(activated(QModelIndex)),this,SLOT(slOpenFile(QModelIndex)));//Слот открытия файлов в дереве
    connect(table,SIGNAL(activated(QModelIndex)),this,SLOT(slOpenDirTable(QModelIndex)));//открытие поддиректории в таблице при нажатии элемента
    connect(tree,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slTreeDoubleClick(QModelIndex)));//При двойном клике элемента дерева раскрывается таблица
    connect(table,SIGNAL(doubleClicked(QModelIndex)),tree,SLOT(expand(QModelIndex)));//При выборе элемента таблицы выбирается элемент дерева
    connect(table,SIGNAL(doubleClicked(QModelIndex)),tree,SIGNAL(activated(QModelIndex)));//чтобы при выборе элемента он открывался
}

void File_Model::slOpenFile(QModelIndex index)
{
    if(!model->fileInfo(index).isDir())//Если файл - не директория
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(model->filePath(index)));//тогда открываем его
         table->setRootIndex(index.parent());//и в таблице раскрываем папку (родителя) в которой он находится
    }
}

void File_Model::slOpenDirTable(QModelIndex index)
{
    if(model->fileInfo(index).isDir())//Если выбрана папка,
       table->setRootIndex(index);//то раскрываем её

}

void File_Model::slTreeDoubleClick(QModelIndex index)
{
    if(!tree->isExpanded(index))//Если элемент был закрыт(то он раскрывается и...)
        table->activated(index);//таблица перегружается на этот элемент
    else
    {
        if(index.parent().row()<0) table->reset();/*При нажатии диска
                    индекс родителя получается с отрицательной строкой
                    поэтому перезагружаем исходное состояние таблицы */
        else
        table->activated(index.parent());//Если при двойном клике элемент сворачивается
                                         //то в таблице открываем элемент на порядок выше
    }
    qDebug()<<"Индекс элемента"<<index;
    qDebug()<<"Индекс родителя"<<index.parent();
    qDebug()<<"==============";
}

File_Model::~File_Model()
{

}

Total_Commander::Total_Commander(QWidget *parent):
    QWidget(parent)
{
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries);// отображаем всё
    model->setRootPath("");// устанавливаем корневой путь

    QVBoxLayout *vLayoutMain = new QVBoxLayout(this);
    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    QHBoxLayout *hLayout10 = new QHBoxLayout();

    listMaster = new QListView();
    listSlave = new QListView();
    listMaster->setMinimumWidth(200);
    listSlave->setMinimumWidth(200);
    listMaster->setModel(model);
    listSlave->setModel(model);

    splitter->addWidget(listMaster);
    splitter->addWidget(listSlave);
    btnCopy = new QPushButton(QIcon (":/icons/Copy_files"),tr("Copy"));
    btnDel = new QPushButton(QIcon(":/icons/Delete"),tr("Delete"));


    hLayout10->addWidget(btnCopy,0,Qt::AlignHCenter);
    hLayout10->addWidget(btnDel,0,Qt::AlignCenter);
    vLayoutMain->addWidget(splitter);
    vLayoutMain->addLayout(hLayout10);


    setWindowTitle(tr("Total Commander"));
    connect(listMaster,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slDoubleClick(QModelIndex)));
    connect(listSlave,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slDoubleClick(QModelIndex)));

    {//Экш копирования файла в директории
        auto *A = actCopy = new QAction();
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slCopyFiles()));
    }
    connect(btnCopy,SIGNAL(clicked(bool)),actCopy,SIGNAL(triggered(bool)));

    {//Экш копирования файла в директории
        auto *A = actDel = new QAction();
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slDelFiles()));
    }
    connect(btnDel,SIGNAL(clicked(bool)),actDel,SIGNAL(triggered(bool)));
}

void Total_Commander::slDoubleClick(QModelIndex index)
{
    QListView *listView = (QListView*)sender();//Метод получает указатель на объект, посылающий данный сигнал
    QFileInfo fileinfo = model->fileInfo(index);

    if(fileinfo.fileName() == "..")
    {
        QDir dir = fileinfo.dir();
        dir.cdUp();//переходим в родительскую папку, т.е на уровень выше
        listView->setRootIndex(model->index(dir.absolutePath())); //устанавливаем корневую директорию в этом листе
    }
    else if(fileinfo.fileName() == ".")
    {
        listView->setRootIndex(model->index(""));//Переходим в корневую папку
    }
    else if(fileinfo.isDir())// Если элемент- папка
    {
        listView->setRootIndex(index);//раскрываем выбранный элемент
    }


}

void Total_Commander::copyFile(QString Path, QString Path_2)
{
    QFileInfo fileInfo(Path);
    if(fileInfo.isFile())//если выбран файл
    {
         Path_2 += "/" + fileInfo.fileName();//формируем новую директорию
         QFile::copy(Path,Path_2);//копируем файл
    }

    if(fileInfo.isDir())//Если выбрана папка
    {
        QDir(Path_2).mkdir(fileInfo.fileName());//создаём новую директорию и присваиваем её к subir
        QString subDir = Path_2+"/"+fileInfo.fileName();//поддиректория (путь)
        qDebug() << "поддиректория " << subDir;

        //ФИЛЬТР В QDIR ДОБАВЛЯЕМ ОБЯЗАТЕЛЬНО!!!
        foreach(QFileInfo infoFile, QDir(Path).entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name|QDir::DirsFirst))//Гуляем по папке
        {   qDebug() << "абсолютный путь " << infoFile.absoluteFilePath();
            copyFile(infoFile.absoluteFilePath(),subDir);


        }

    }

}

void Total_Commander::slCopyFiles()
{
    QString Path = model->fileInfo(listMaster->currentIndex()).absoluteFilePath();//Путь исходный
    QString Path_2 = model->fileInfo(listSlave->rootIndex()).absoluteFilePath();//Путь загрузки

    qDebug() << model->fileInfo(listSlave->rootIndex()).absoluteFilePath() + "/" + model->fileInfo(listMaster->currentIndex()).fileName();

    copyFile(Path, Path_2);
}

void Total_Commander::slDelFiles()
{
    QString Path = model->fileInfo(listSlave->currentIndex()).absoluteFilePath();
    deleteFiles(Path);
}

void Total_Commander::deleteFiles(QString Path)
{
    QFileInfo fileInfo(Path);
    if(fileInfo.isFile())
    {
        QFile(Path).remove();
            QDir(Path).rmdir(Path);
    }

      if(fileInfo.isDir())//Если выбрана папка
    {
        foreach(QFileInfo infoFile, QDir(Path).entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name|QDir::DirsFirst))
        {
            deleteFiles(infoFile.absoluteFilePath());//удаляем все вложенные файлы рекурсивно
        }
        QDir(fileInfo.absoluteFilePath()).rmdir(fileInfo.absoluteFilePath());//удаляем саму папку
    }
}

Total_Commander::~Total_Commander()
{

}

}//namespace WINDOW

