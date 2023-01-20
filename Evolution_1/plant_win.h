#ifndef PLANT_WIN_H
#define PLANT_WIN_H

#include <QDialog>

#include "environment.h"

namespace Ui {
class Plant_win;
}

class Plant_win : public QDialog
{
    Q_OBJECT

public:
    explicit Plant_win(Environment *environment, QWidget *parent = nullptr);
    ~Plant_win();
    virtual void resizeEvent(QResizeEvent*);

private slots:
    void on_add_plant1_clicked();

private:
    Ui::Plant_win *ui;
    Environment *environment;
    void setBackgroundImage(QString filePath);
    void stretchBackground();
};

#endif // PLANT_WIN_H
