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

}


#endif // LTT_H
