#ifndef HERB_WIN_H
#define HERB_WIN_H

#include <QDialog>
#include "environment.h"

namespace Ui {
class herb_win;
}

class herb_win : public QDialog
{
    Q_OBJECT

public:
    explicit herb_win(Environment *environment, QWidget *parent = nullptr);
    ~herb_win();
    virtual void resizeEvent(QResizeEvent*);

private slots:

    void on_randbut_clicked();

    void on_resetbut_clicked();

    void on_add_herbi_clicked();

private:
    Ui::herb_win *ui;
    Environment *environment;
    void setBackgroundImage(QString filePath);
    void stretchBackground();
};

#endif // HERB_WIN_H
