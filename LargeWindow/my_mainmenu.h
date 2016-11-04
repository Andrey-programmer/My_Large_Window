#ifndef MY_MENU_H
#define MY_MENU_H

#include <QMenu>


namespace WINDOW{

class My_MainMenu : public QMenu
{
    Q_OBJECT

public:
    My_MainMenu(QWidget *parent);
    virtual ~My_MainMenu();

};
}

#endif // MY_MENU_H
