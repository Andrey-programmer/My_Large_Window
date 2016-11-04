#include "myApplication.h"

#include <QFile>
#include <QString>

namespace WINDOW {

MyApplication::MyApplication(int argc, char *argv[] ) :
    QApplication(argc, argv)
{
//----Подключение файла стилей-----------
   QFile stylecss;
   stylecss.setFileName(":/style/style.css");
   stylecss.open(QFile::ReadOnly);
   QString qssStyle = stylecss.readAll();
   setStyleSheet(qssStyle);
//--------------Установка переводчика----------------------
  /* pTranslator = new QTranslator(this);
   pTranslator->load(":/lang/rus");
   installTranslator(pTranslator);*/



}

MyApplication::~MyApplication()
{

}

}

