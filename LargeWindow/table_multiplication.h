#ifndef TABLE_MULTIPLICATION_H
#define TABLE_MULTIPLICATION_H

#include <QTableWidget>
#include <QAction>

namespace WINDOW {

class Table_Multiplication : public QTableWidget
{
    Q_OBJECT

private:
    QAction *actCopy;

public:
    Table_Multiplication(QWidget *parent = 0);
    ~Table_Multiplication();

protected slots:
    void slCopy();
};

}

#endif // TABLE_MULTIPLICATION_H
