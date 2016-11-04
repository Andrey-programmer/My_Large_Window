#include "myApplication.h"
#include "my_MainWindow.h"



int main(int argc, char *argv[])
{
   WINDOW::MyApplication appl(argc, argv);
   //WINDOW::MyApplication::setQuitOnLastWindowClosed(false);//запрещаем выходить из приложения при
                                                           //нажатии крестика будет сворачиваться в трей

   WINDOW::My_MainWindow window;
   window.show();

   return appl.exec();
}
