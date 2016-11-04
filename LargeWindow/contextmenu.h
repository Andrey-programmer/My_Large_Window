#ifndef CONTEXTMENU_H
#define CONTEXTMENU_H

#include "myapplication.h"

#include <QWidget>
#include <QContextMenuEvent>
#include <QMenu>


namespace  WINDOW {

class ContextMenu : public QWidget
{
 Q_OBJECT

private:
    QMenu *contMenu;
    QAction *colorRed;
    QAction *colorBlue;
    QAction *colorGreen;
    QAction *colorWhite;

protected:
    virtual void ContextMenuEvent(QContextMenuEvent *event);

public slots:
    void slContextMenu(bool);

public:

    ContextMenu(QWidget *parent = 0);
    virtual ~ContextMenu();

};


}

#endif // CONTEXTMENU_H
