#ifndef PLANT_WIN_H
#define PLANT_WIN_H

#include <QDialog>

namespace Ui {
class Plant_win;
}

class Plant_win : public QDialog
{
    Q_OBJECT

public:
    explicit Plant_win(QWidget *parent = nullptr);
    ~Plant_win();
    virtual void resizeEvent(QResizeEvent*);

private:
    Ui::Plant_win *ui;
    void setBackgroundImage(QString filePath);
    void stretchBackground();
};

#endif // PLANT_WIN_H
