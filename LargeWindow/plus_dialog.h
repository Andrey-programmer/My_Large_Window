#ifndef PLUS_DIALOG_H
#define PLUS_DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QAction>

namespace WINDOW {

class Plus_Mark_dialog : public QDialog
{
    Q_OBJECT

private:
    QLabel *lbl;
    QLineEdit *line;
    QPushButton *Ok;

    QAction *addMark;

public slots:
    void slAddMark();

public:
   // static QString plMark;//-глобальная переменная
    QString getResult() const { return line->text(); }

public:
    Plus_Mark_dialog(QWidget *parent = 0);

    virtual ~Plus_Mark_dialog();
};

}


#endif // PLUS_DIALOG_H
