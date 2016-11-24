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

    table = new QTableView();//Представление таблицей
    table->setModel(model);

    splitter->addWidget(tree);
    splitter->addWidget(table);

    QHBoxLayout *hLayout10 = new QHBoxLayout();
    hLayout10->addWidget(splitter);
    setLayout(hLayout10);

    setWindowTitle(tr("File_System"));

    connect(tree,SIGNAL(activated(QModelIndex)),this,SLOT(slOpenFile(QModelIndex)));
}

void File_Model::slOpenFile(QModelIndex index)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(model->filePath(index)));
}

File_Model::~File_Model()
{

}


}

