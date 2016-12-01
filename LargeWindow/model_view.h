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
    void slOpenDirTable(QModelIndex index);
    void slTreeDoubleClick(QModelIndex index);
};


class Total_Commander:public QWidget
{
    Q_OBJECT

private:
    QListView *listMaster;
    QListView *listSlave;

    QPushButton *btnCopy;
    QAction *actCopy;

    QPushButton *btnDel;
    QAction *actDel;

    QFileSystemModel *model;

    QString Path;
    QString Path_2;

    void copyFile(QString Path, QString Path_2);
    void deleteFiles(QString Path);

public:
    Total_Commander(QWidget *parent = 0);
    virtual ~Total_Commander();

protected slots:
    void slDoubleClick(QModelIndex index);
    void slCopyFiles();
    void slDelFiles();
};


}//namespace WINDOW

#endif // LTT_H
