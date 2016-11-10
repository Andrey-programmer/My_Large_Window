#ifndef TABLE_MULTIPLICATION_H
#define TABLE_MULTIPLICATION_H

#include <QTableWidget>

namespace WINDOW {

class Table_Multiplication : public QTableWidget
{
    Q_OBJECT

public:
    Table_Multiplication(QWidget *parent = 0);
    ~Table_Multiplication();
};

}

#endif // TABLE_MULTIPLICATION_H
