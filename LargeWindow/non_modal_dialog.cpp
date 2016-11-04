#include "non_modal_dialog.h"
#include "subwindows.h"

#include <QHBoxLayout>



namespace WINDOW {


non_Modal_Dialog::non_Modal_Dialog(QWidget *parent):
    QDialog(parent)
{
    lbl1 = new QLabel(this);
    QHBoxLayout *hLayout10 = new QHBoxLayout();
    hLayout10->addWidget(lbl1,10,Qt::AlignCenter);
    setLayout(hLayout10);
}



void non_Modal_Dialog::sltextUpdia(const QString str)
{
   lbl1->setText(str.toUpper());

}
 non_Modal_Dialog::~non_Modal_Dialog()
{

}


}

