#ifndef DRAWIMAGE_H
#define DRAWIMAGE_H

#include <QFrame>
#include <QCheckBox>
#include <QLabel>
#include <QAction>
#include <QPushButton>
#include <QImage>


namespace WINDOW {

class DrawImage : public QFrame
{
    Q_OBJECT

private:
    QAction *actChooseImg;
    QAction *actInversImg;
    QAction *actMirroredImg;
    QAction *actResizeImg;

    QCheckBox *cbInvers;
    QCheckBox *cbMirrored;
    QCheckBox *cbResize;

    QLabel *lblChooseImg;
    QLabel *lblInvers;
    QLabel *lblMirrored;
    QLabel *lblResize;

    QLabel *lblmainImg;
    QLabel *lblChangeImg;

    QPushButton *btnImage;

    QImage image;

public:
    DrawImage(QWidget *parent = 0);
    virtual ~DrawImage();

protected slots:
    //Слоты работы с QImage
    void slChooseImg();
    void slInverse();
    void slMirrored();//Отразить
    void slResizeImg();

};
}



#endif // DRAWIMAGE_H
