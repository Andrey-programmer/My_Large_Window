#ifndef AUTO_DIALOG_H
#define AUTO_DIALOG_H

#include "auto_frame.h"

#include <QWidget>
#include <QDialog>
#include <QTabWidget>

namespace WINDOW {
class Auto_Dialog : public QDialog
{
    Q_OBJECT

private:
    QTabWidget *Data_Auto;
    Auto_Frame *a_frame;

public:
    Auto_Dialog(QWidget *parent = 0);
    virtual ~Auto_Dialog();

};
}

#endif // AUTO_DIALOG_H
