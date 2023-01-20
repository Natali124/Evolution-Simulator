#ifndef OMNI_WIN_H
#define OMNI_WIN_H

#include <QDialog>

namespace Ui {
class omni_win;
}

class omni_win : public QDialog
{
    Q_OBJECT

public:
    explicit omni_win(QWidget *parent = nullptr);
    ~omni_win();
    virtual void resizeEvent(QResizeEvent*);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::omni_win *ui;
    void setBackgroundImage(QString filePath);
    void stretchBackground();
};


#endif // OMNI_WIN_H
