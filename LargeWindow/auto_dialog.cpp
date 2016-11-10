#include "auto_dialog.h"
#include "subwindows.h"
#include "table_multiplication.h"

#include <QVBoxLayout>

namespace WINDOW {

Auto_Dialog::Auto_Dialog(QWidget *parent):
    QDialog(parent)
{
    setObjectName("Auto_Dialog");

    Data_Auto = new QTabWidget;
    a_frame = new Auto_Frame(this);
    Data_Auto->setTabShape(QTabWidget::Triangular);//делаем закладки со скошенными углами
                                                   //*не работает при добавлении элемента в CSS
    Data_Auto->setMinimumSize(200,300);

    Data_Auto->addTab(a_frame, tr("Car settings"));
    Data_Auto->addTab(new SubWindows_3, tr("QWigwtList"));//Добавляем SubWindows_3 как новый виджет
    Data_Auto->addTab(new Table_Multiplication,tr("Table_Multiplication"));

    QVBoxLayout *main_vLayout = new QVBoxLayout();
    main_vLayout->addWidget(Data_Auto);
    setLayout(main_vLayout);

}

Auto_Dialog::~Auto_Dialog()
{

}

}
