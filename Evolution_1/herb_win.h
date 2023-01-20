#ifndef HERB_WIN_H
#define HERB_WIN_H

#include <QDialog>

namespace Ui {
class herb_win;
}

class herb_win : public QDialog
{
    Q_OBJECT

public:
    explicit herb_win(QWidget *parent = nullptr);
    ~herb_win();

private:
    Ui::herb_win *ui;
    void setBackgroundImage(QString filePath);
};

#endif // HERB_WIN_H
