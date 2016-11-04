#ifndef AUTO_FRAME_H
#define AUTO_FRAME_H

#include "data.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QFrame>
#include <QStringList>
#include <QGroupBox>
#include <QPushButton>
#include <QScrollArea>
#include <QInputDialog>
#include <QAction>

namespace WINDOW {

class Auto_Frame : public QFrame
{
    Q_OBJECT

private:
    DATAS::Properties_Cars *Properties;

    QGroupBox *grProperties;
    QGroupBox *grImage;

    QFrame *DataFrame;
    QFrame *PhotoFrame;

    QLabel *lbl_Number;
    QLabel *lbl_Mark;
    QLabel *lbl_Model;
    QLabel *lbl_Color;
    QLabel *lbl_Category;
    QLabel *lbl_Date_of_reristration;

    QLineEdit *line_Number;
    QComboBox *cmb_Mark;
    QComboBox *cmb_Model;
    QComboBox *cmb_Color;
    QComboBox *cmb_Category;
    void setupCategory(QLayout *L);

    QLineEdit *line_Date_of_reristration;
    QLineEdit *line_Color;

    QPushButton *plusNumber;
    QPushButton *plusMark;
    QPushButton *plusModel;
    QPushButton *plusColor;
    QPushButton *plusData;

    QScrollArea *ScrollL;
    QScrollArea *ScrollImage;
    QAction *actSelectMark;

    QLabel *lbl_Image;

    void copyColorList(QStringList* stringList);
    void fcmbMark(QComboBox *mark);
    void fcmbModel(QComboBox *model, QComboBox *mark);

signals:
    void sigMarkText(QString);


protected slots:
    void slNumber();
    void slMark();
    void slModel(QString mark);
    void slAddModel();
    void slColor();


public:


    Auto_Frame(QWidget *parent = 0);
    virtual ~Auto_Frame();

};
}


#endif // AUTO_FRAME_H
