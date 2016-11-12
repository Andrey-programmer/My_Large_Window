#include "model_view.h"

#include <QHBoxLayout>

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
}

