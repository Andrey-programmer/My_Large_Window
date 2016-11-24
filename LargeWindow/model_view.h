#ifndef LTT_H
#define LTT_H

#include <QtWidgets>

namespace WINDOW
{

class LTT:public QWidget
{
    Q_OBJECT

private:
    QStringListModel *listmodel;
    QTreeView *treeView;
    QListView *listView;
    QTableView *tableView;

public:
    LTT(QWidget *parent = 0);
    virtual ~LTT();

};


class StdItemModel:public QTreeView
{
    Q_OBJECT

public:
    StdItemModel(QWidget *parent = 0);
    virtual ~StdItemModel();

};


class File_Model:public QWidget
{
    Q_OBJECT

private:
    QTreeView *tree;
    QFileSystemModel *model;
    QTableView *table;

public:
    File_Model(QWidget *parent = 0);
    virtual ~File_Model();

protected slots:
    void slOpenFile(QModelIndex index);
};
}


#endif // LTT_H
