#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <cstdlib>
#include <QGraphicsScene>
#include <iostream>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_startBut_clicked();
    void on_button_pred_clicked();
    void on_button_prey_clicked();
    void on_button_plant_clicked();
    void on_button_rdm_clicked();
    void on_button_delete_all_clicked();
    void on_button_reset_clicked();
    // void on_creature_list_item_clicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
