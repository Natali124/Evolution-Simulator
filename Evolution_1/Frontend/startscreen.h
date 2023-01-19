#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>

namespace Ui {
class startscreen;
}

class startscreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit startscreen(QWidget *parent = nullptr);
    ~startscreen();

private slots:
    void on_StartBut_clicked();

private:
    Ui::startscreen *ui;
};

#endif // STARTSCREEN_H
