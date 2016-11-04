#ifndef DATA_H
#define DATA_H

#include <QString>
#include <QVector>
#include <QSet>
#include <QObject>
#include <QMap>


namespace WINDOW {


namespace DATAS {

struct Properties_Cars: public QObject
{
    Q_OBJECT

public:
    Properties_Cars();
    QString Nomber;
    QVector<QString> Mark;
    QMap<QString,QVector<QString>> Model;
    QVector<QString> Color;
    QString Category;
    QString Date_of_Registration;
    int Miliage;

    void setCarMap(QVector<QString> &mark);
    virtual ~Properties_Cars(){}
};


enum enColor
{
    White = 0,
    Silver = 1 ,
    Black = 2,
    Gray = 3,
    Red = 4

};


enum Category_Cars
{
    Passenger = 0,
    Truck = 1,
    Motorcycle = 2

};

}
}


#endif // DATA_H
