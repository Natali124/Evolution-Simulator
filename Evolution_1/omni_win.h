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

private:
    Ui::omni_win *ui;
    void setBackgroundImage(QString filePath);
};


#endif // OMNI_WIN_H
