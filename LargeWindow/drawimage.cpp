#include "drawimage.h"

#include <QHBoxLayout>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDebug>
#include <QPainter>
#include <QFileDialog>

namespace WINDOW {
DrawImage::DrawImage(QWidget *parent):
    QFrame(parent)
{
    image.load(":/icons/Almaz");

    QHBoxLayout *hLayout11 = new QHBoxLayout();
    QFrame *frameUp = new QFrame();

    QVBoxLayout *vLayout1 = new QVBoxLayout();
    lblChooseImg = new QLabel(tr("Choose Image"));
    btnImage = new QPushButton(tr("Choose"));
    vLayout1->addWidget(lblChooseImg);
    vLayout1->addWidget(btnImage);
    vLayout1->addItem(new QSpacerItem(0,0,QSizePolicy::Minimum,QSizePolicy::Expanding));
    lblmainImg = new QLabel();
    lblmainImg->setPixmap(QPixmap::fromImage(image));//Добавляем картинку на lbl
    frameUp->setLayout(vLayout1);
    hLayout11->addWidget(frameUp);
    hLayout11->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));
    hLayout11->addWidget(lblmainImg);

    QHBoxLayout *hLayout10 = new QHBoxLayout();
    lblInvers = new QLabel(tr("Inverse"));
    cbInvers = new QCheckBox();
    hLayout10->addWidget(cbInvers);
    hLayout10->addWidget(lblInvers);
    hLayout10->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));

    QHBoxLayout *hLayout9 = new QHBoxLayout();
    lblMirrored = new QLabel(tr("Mirrored"));
    cbMirrored = new QCheckBox();
    hLayout9->addWidget(cbMirrored);
    hLayout9->addWidget(lblMirrored);
    hLayout9->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));


    QHBoxLayout *hLayout8 = new QHBoxLayout();
    lblResize = new QLabel(tr("Resize"));
    cbResize = new QCheckBox();
    hLayout8->addWidget(cbResize);
    hLayout8->addWidget(lblResize);
    hLayout8->addItem(new QSpacerItem(0,0,QSizePolicy::Expanding,QSizePolicy::Minimum));

    QFrame *frameAction = new QFrame();
    frameAction->setObjectName("frameImage");

    QVBoxLayout *vLayout2 = new QVBoxLayout();
    vLayout2->setSpacing(30);
    vLayout2->addLayout(hLayout10);
    vLayout2->addLayout(hLayout9);
    vLayout2->addLayout(hLayout8);

    QVBoxLayout *vLayout3 = new QVBoxLayout();
    lblChangeImg = new QLabel();
    vLayout3->setMargin(0);
    vLayout3->addWidget(lblChangeImg);

    QHBoxLayout *hLayout7 = new QHBoxLayout();
    hLayout7->addLayout(vLayout2);
    hLayout7->addLayout(vLayout3);

    frameAction->setLayout(hLayout7);

    QVBoxLayout *vmainLayout = new QVBoxLayout();
    vmainLayout->addLayout(hLayout11);
    vmainLayout->addWidget(frameAction);

    setLayout(vmainLayout);

    {
        auto *A = actChooseImg = new QAction();
        A->setText(tr("Choose"));
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slChooseImg()));
    }

    {
        auto *A = actInversImg = new QAction();
        A->setText(tr("Inverse"));
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slInverse()));
    }
    {
        auto *A = actMirroredImg = new QAction();
        A->setText(tr("Mirrored"));
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slMirrored()));
    }
    {
        auto *A = actResizeImg = new QAction();
        A->setText(tr("Resize"));
        connect(A,SIGNAL(triggered(bool)),this,SLOT(slResizeImg()));
    }

    connect(btnImage,SIGNAL(clicked(bool)),actChooseImg,SIGNAL(triggered(bool)));
    connect(cbInvers,SIGNAL(clicked(bool)),actInversImg,SIGNAL(triggered(bool)));
    connect(cbMirrored,SIGNAL(clicked(bool)),actMirroredImg,SIGNAL(triggered(bool)));
    connect(cbResize,SIGNAL(clicked(bool)),actResizeImg,SIGNAL(triggered(bool)));

}

void DrawImage::slChooseImg()
{qDebug() << "slChooseImg";
    cbInvers->setChecked(false);
    cbMirrored->setChecked(false);
    cbResize->setChecked(false);
    image.load(QFileDialog::getOpenFileName(0,tr("Choose Image"),"","*.png *.ico *.jpg"));
    lblmainImg->setFixedSize(image.size());
    lblmainImg->setPixmap(QPixmap::fromImage(image));
    lblChangeImg->setFixedSize(image.size());
    lblChangeImg->setPixmap(QPixmap::fromImage(image));

 }

void DrawImage::slInverse()
{qDebug() << "slInverse";
    lblChangeImg->setFixedSize(image.size());
    image.invertPixels(QImage::InvertRgb);
    lblChangeImg->setPixmap(QPixmap::fromImage(image));
    slResizeImg();
}

void DrawImage::slMirrored()
{qDebug() << "slMirrored";
    lblChangeImg->setFixedSize(image.size());
    image = image.mirrored(true,true);
    cbMirrored->isChecked()?lblChangeImg->setPixmap(QPixmap::fromImage(image))
                          :lblChangeImg->setPixmap(QPixmap::fromImage(image));
     slResizeImg();

}

void DrawImage::slResizeImg()
{qDebug() << "lResizeImg";
  QImage imageTemp;
        if(cbResize->isChecked())
    {
        imageTemp = image.scaled(image.width()/2,image.height()/2, Qt::IgnoreAspectRatio);//изменение размеров(масштабирование)
        lblChangeImg->setFixedSize(imageTemp.size());
        lblChangeImg->setPixmap(QPixmap::fromImage(imageTemp));
    }
    else
    {
        /*image = image.scaled(image.width()*2,image.height()*2, Qt::IgnoreAspectRatio);*/
        lblChangeImg->setFixedSize(image.size());
        lblChangeImg->setPixmap(QPixmap::fromImage(image));
    }


}

DrawImage::~DrawImage()
{

}
}
