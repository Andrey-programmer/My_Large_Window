#ifndef NON_MODAL_DIALOG_H
#define NON_MODAL_DIALOG_H

#include <QDialog>
#include <QLabel>


namespace  WINDOW {

class non_Modal_Dialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *lbl1;

public:
    non_Modal_Dialog(QWidget *parent = 0);
    virtual ~non_Modal_Dialog();

public slots:
    void sltextUpdia(const QString str);

};
}


#endif // NON_MODAL_DIALOG_H
