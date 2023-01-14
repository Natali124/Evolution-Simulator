#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QtWidgets/qlistwidget.h"
#include <QMainWindow>
#include <QApplication>
#include <cstdlib>
#include <QGraphicsScene>
#include <iostream>
#include "environment.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    virtual void resizeEvent(QResizeEvent*);
    Environment* env = new Environment;


private slots:

    // all functions are explained in mainwindow.cpp

    void setBackgroundImage(QString filePath);

    void stretchBackground();

//    void on_startBut_clicked();

    void on_button_pred_clicked();

    void on_button_prey_clicked();

    void on_button_plant_clicked();

    void on_button_rdm_clicked();

    void on_button_delete_all_clicked();

    void on_button_reset_clicked();

    void on_button_delete_creature_clicked();

    void sort_creature_list(QListWidget *creature_list);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
