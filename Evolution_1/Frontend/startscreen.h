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
    virtual void resizeEvent(QResizeEvent*);

private slots:
    void setBackgroundImage(QString filePath);
    void on_StartBut_clicked();
    void stretchBackground();



private:
    Ui::startscreen *ui;
};

#endif // STARTSCREEN_H
