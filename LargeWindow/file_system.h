#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include <QTreeWidget>
#include <QWidget>


namespace WINDOW {

class File_System : public QTreeWidget
{
    Q_OBJECT

private:
    QTreeWidgetItem *twgIt;

public:
    File_System(const QString &path, QWidget *parent = 0);
    virtual ~File_System();

    QTreeWidgetItem* All_Directory(const QString &path, QTreeWidgetItem *itm);
};

}

#endif // FILE_SYSTEM_H
