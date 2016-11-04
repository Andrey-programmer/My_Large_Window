#ifndef MYAPPLICATION_H
#define MYAPPLICATION_H

#include <QApplication>
#include <QTranslator>

namespace WINDOW {
class MyApplication : public QApplication
{

    Q_OBJECT

private:
   // QTranslator *pTranslator;// Статичный переводчик

public:
    explicit MyApplication(int argc, char *argv[]);
    virtual ~MyApplication();

};
}
#endif // MYAPPLICATION_H
