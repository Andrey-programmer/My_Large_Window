#include "other.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>
#include <QDebug>

namespace WINDOW{
Other::Other(QWidget *parent):
    QFrame(parent)
{
   setFrameStyle(WinPanel|Sunken);
   spinbox1 = new QSpinBox();
   spinbox1->setMaximum(150);
   slider1 = new QSlider(Qt::Horizontal);
   slider1->setMaximum(150);
   progress = new QProgressBar();


   //Рамка с картинкой
   frameImg = new QFrame();
   img.load(":/icons/diagram");
   lblImg = new QLabel();
   lblImg->setFixedSize(img.size());
   lblImg->setPixmap(QPixmap::fromImage(img));

   QHBoxLayout *hLayout8 = new QHBoxLayout();
   hLayout8->addWidget(lblImg);
   frameImg->setLayout(hLayout8);




  /* QAction *A = actProgress = new QAction();
   connect(A,SIGNAL(triggered(bool)),this,SLOT(slProgress()));*/

   QHBoxLayout *hLayout10 = new QHBoxLayout();
   hLayout10->addWidget(slider1);
   hLayout10->addWidget(spinbox1);

   QVBoxLayout *vLayout9 = new QVBoxLayout();
   vLayout9->addLayout(hLayout10);
   vLayout9->addWidget(progress);
   vLayout9->addWidget(frameImg);

   setLayout(vLayout9);


   //Устанавливаем зависимость spinbox-slider
   connect(spinbox1,SIGNAL(valueChanged(int)),slider1,SLOT(setValue(int)));
   connect(slider1,SIGNAL(valueChanged(int)),spinbox1,SLOT(setValue(int)));
  //ПрогрессБар
   connect(slider1,SIGNAL(valueChanged(int)),this,SLOT(slProgress(int)));
   //яркость картинки
   connect(slider1,SIGNAL(valueChanged(int)),this,SLOT(slBrightness(int)));



}

void Other::slProgress(int x)
{

    progress->setValue((x * progress->maximum())/slider1->maximum())  ;

}

void Other::slBrightness(int X)
{
   // brightness(img,X);//Закидываем в Label ->
    lblImg->setPixmap(QPixmap::fromImage(brightness(img,X)));
    //qDebug() <<"Сработал слот slBrightness";
}

QImage Other::brightness(const QImage &img, int X)//Получаем новую картинку
{
    QImage imgTemp = img;//делаем копию картинки
    qint64 imgHeight = imgTemp.height();
    qint64 imgWidth = imgTemp.width();

    for(qint64 y = 0; y < imgHeight; ++y)
    {
        QRgb *tempLine = reinterpret_cast<QRgb*>(imgTemp.scanLine(y));//Делим изображение на линии
        for(qint64 z = 0; z < imgWidth; ++z)
        {
            int r = qRed(tempLine[z])+X;
            int g = qGreen(tempLine[z])+X;
            int b = qBlue(tempLine[z])+X;
            int a = qAlpha(tempLine[z]);

            tempLine[z] = qRgba(r>255?255:r<0?0:r,
                              g>255?255:g<0?0:g,
                              b>255?255:b<0?0:b,
                              a);
        }
    }
    return imgTemp;
}

Other::~Other()
{

}

}

