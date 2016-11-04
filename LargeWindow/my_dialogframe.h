    #ifndef MY_DIALOGFRAME_H
    #define MY_DIALOGFRAME_H

    #include <QFrame>
    #include <QPushButton>
    #include <QLabel>
    #include <QLineEdit>
    #include <QAction>
    #include <QCheckBox>

    namespace WINDOW {

    class My_DialogFrame : public QFrame
    {
        Q_OBJECT

    private:
        QAction *actOkClicked;
        QAction *actTextLine;
        QAction *actPassword;

        QPushButton *Ok;
        QPushButton *Cancel;


        QCheckBox *cbLineText;
        QCheckBox *cbPass;

        QLabel *lbl_1;
        QLabel *lbl_pass;
        QLabel *lbl_name;
        QLabel *lbl_autorization;

        QLineEdit *nameLine;
        QLineEdit *textLine;
        QLineEdit *passLine;

        QFrame *frame_autoriz;

       public:
        My_DialogFrame(QWidget *parent = 0);
        virtual ~My_DialogFrame();

    public slots:
        void clickOk();
        void EnableOk(QString text);
        void slEnableTextLine();
        void slAutorization();

    signals:
        void accepting();

    };

    }


    #endif // MY_DIALOGFRAME_H
