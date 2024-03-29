#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <cstdlib>
#include <QGraphicsScene>
#include <iostream>
#include "Living_Beings/living_being.h"
#include "environment.h"
#include "qlistwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class BeingItem : public QListWidgetItem{
    public:
        BeingItem(LivingBeing* being) : QListWidgetItem(being->objectName()), being(being){};

    public:
        LivingBeing* being;
        bool operator<(const QListWidgetItem &other) const { // for sorting the items
            QStringList list1 = text().split(' ');
            QStringList list2 = other.text().split(' ');
            int n1 = list1.takeLast().toInt();
            int n2 = list2.takeLast().toInt();
            QString w1 = list1.join(' ');
            QString w2 = list2.join(' ');
            if(w1 != w2) //sort by the name first
                return w1 < w2;
            return n1 < n2; // and then by the number at the end
        }
};

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

    void on_button_pred_clicked();

    void on_button_prey_clicked();

    void on_button_plant_clicked();

    void on_button_delete_all_clicked();

    void on_button_delete_creature_clicked();

    void create_proper_sliders(QListWidgetItem*);

    void on_simBut_clicked();

    void clearsliders();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
