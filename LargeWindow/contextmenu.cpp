#include "contextmenu.h"

#include <QDebug>

namespace WINDOW {

ContextMenu::ContextMenu(QWidget *parent):
    QWidget(parent)
{
     contMenu = new QMenu(this);
     contMenu->addMenu("&Color");

     {
         QAction *A = colorGreen = new QAction();
         A->setText(tr("&Green"));
         addAction(A);
         connect(A,SIGNAL(triggered(bool)),this,SLOT(slContextMenu(bool)));
     }

   /*  {
         QAction *A = colorBlue = new QAction();
         A->setText(tr("&Blue"));
         addAction(A);
         connect(A,SIGNAL(triggered(A)),this,SLOT(slContextMenu(A)));
     }

     {
         QAction *A = colorRed = new QAction();
         A->setText(tr("&Red"));
         addAction(A);
         connect(A,SIGNAL(triggered(A)),this,SLOT(slContextMenu(A)));
     }

     {
         QAction *A = colorWhite = new QAction();
         A->setText(tr("&White"));
         addAction(A);
         connect(A,SIGNAL(triggered(A)),this,SLOT(slContextMenu(A)));
     }*/



}

void ContextMenu::ContextMenuEvent(QContextMenuEvent *event)
{
     if (contMenu) contMenu->exec(event->globalPos());
}

void ContextMenu::slContextMenu(bool)
{
    qDebug()<< " рррррррррррррр ";
 //  QString strMenu = actMenu->text().remove("&");//удаляем символ из строки экшна
   //setHtml(QString("<BODY BGCOLOR=%1></BODY>").arg(strMenu));//меняем цвет фона через html
}

ContextMenu::~ContextMenu()
{

}
}
