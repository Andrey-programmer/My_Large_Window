#include "plus_dialog.h"

#include <QVBoxLayout>
#include <QSpacerItem>
#include <QValidator>

namespace WINDOW
{

Plus_Mark_dialog::Plus_Mark_dialog(QWidget *parent):
    QDialog(parent)
{
    setWindowTitle(tr("New Mark"));
    setMaximumWidth(300);
    setMaximumHeight(200);

    lbl = new QLabel(tr("Enter new mark"));
    line = new QLineEdit();
    Ok = new QPushButton(tr("&Add"));

    QRegExp str_mark("[a-zA-Zа-яА-Я]{1,15}");
    line->setValidator(new QRegExpValidator(str_mark));

    QVBoxLayout *vLayout10 = new QVBoxLayout();
    QSpacerItem *sp = new QSpacerItem(20,15,QSizePolicy::Expanding,QSizePolicy::Expanding);

    vLayout10->addWidget(lbl);
    vLayout10->addWidget(line);
    vLayout10->addSpacerItem(sp);
    vLayout10->addWidget(Ok);

    setLayout(vLayout10);

    {   //Экшн на кнопку Add
        auto *A = addMark = new QAction();
        connect(Ok,SIGNAL(clicked(bool)),A,SIGNAL(triggered(bool)));//вешаем экшн на кнопку
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slAddMark()));
    }

}


 void Plus_Mark_dialog::slAddMark()
 {
      //plMark = line->text();//-используется при глобальной переменной static
      this->accept();
 }

Plus_Mark_dialog::~Plus_Mark_dialog()
{

}
}
