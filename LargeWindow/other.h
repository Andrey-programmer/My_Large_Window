#ifndef OTHER_H
#define OTHER_H

#include <QFrame>
#include <QSlider>
#include <QSpinBox>
#include <QProgressBar>
#include <QAction>
#include <QImage>
#include <QLabel>

namespace WINDOW {
class Other : public QFrame
{
    Q_OBJECT

private:
    QAction *actProgress;

    QSlider *slider1;
    QSpinBox *spinbox1;
    QProgressBar *progress;
    QFrame *frameImg;
    QImage img;// Оригинал картинки
    QLabel *lblImg;

    QImage brightness(const QImage &img, int X);

public:
    Other(QWidget *parent = 0);
    virtual ~Other();

protected slots:
    void slProgress(int x);
    void slBrightness(int x);//Слот для динамического изменения размеров картинки


};

}


#endif // OTHER_H
