#include "herb_win.h"
#include "ui_herb_win.h"

herb_win::herb_win(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::herb_win)
{
    ui->setupUi(this);
    connect(ui->strength_c, SIGNAL(valueChanged(int)),ui->strength_s,SLOT(setValue(int)) );
    connect(ui->strength_s,SIGNAL(valueChanged(int)),ui->strength_c,SLOT(setValue(int)) );

    connect(ui->energy_c, SIGNAL(valueChanged(int)),ui->energy_s,SLOT(setValue(int)) );
    connect(ui->energy_s,SIGNAL(valueChanged(int)),ui->energy_c,SLOT(setValue(int)) );

    connect(ui->eyesight_c, SIGNAL(valueChanged(int)),ui->eyesight_s,SLOT(setValue(int)) );
    connect(ui->eyesight_s,SIGNAL(valueChanged(int)),ui->eyesight_c,SLOT(setValue(int)) );

    connect(ui->visibility_c, SIGNAL(valueChanged(int)),ui->visibility_s,SLOT(setValue(int)) );
    connect(ui->visibility_s,SIGNAL(valueChanged(int)),ui->visibility_c,SLOT(setValue(int)) );

    connect(ui->health_c, SIGNAL(valueChanged(int)),ui->health_s,SLOT(setValue(int)) );
    connect(ui->health_s,SIGNAL(valueChanged(int)),ui->health_c,SLOT(setValue(int)) );

    connect(ui->size_c, SIGNAL(valueChanged(int)),ui->size_s,SLOT(setValue(int)) );
    connect(ui->size_s,SIGNAL(valueChanged(int)),ui->size_c,SLOT(setValue(int)) );

    ui->strength_c->setStyleSheet("color: black; background_color: white");
    ui->visibility_c->setStyleSheet("color: black; background_color: white");
    ui->size_c->setStyleSheet("color: black; background_color: white");
    ui->health_c->setStyleSheet("color: black; background_color: white");
    ui->eyesight_c->setStyleSheet("color: black; background_color: white");
    ui->energy_c->setStyleSheet("color: black; background_color: white");

    ui->strength_l->setStyleSheet("color: black; background_color: white");
    ui->visibility_l->setStyleSheet("color: black; background_color: white");
    ui->size_l->setStyleSheet("color: black; background_color: white");
    ui->health_l->setStyleSheet("color: black; background_color: white");
    ui->eyesight_l->setStyleSheet("color: black; background_color: white");
    ui->energy_l->setStyleSheet("color: black; background_color: white");

    ui->strength_s->setStyleSheet("color: black; background_color: white");
    ui->visibility_s->setStyleSheet("color: black; background_color: white");
    ui->size_s->setStyleSheet("color: black; background_color: white");
    ui->health_s->setStyleSheet("color: black; background_color: white");
    ui->eyesight_s->setStyleSheet("color: black; background_color: white");
    ui->energy_s->setStyleSheet("color: black; background_color: white");

    ui->add_herbi->setStyleSheet("color: black; background_color: white");
    ui->groupBox->setStyleSheet("color: black; background_color: white");

    QString back(":/backgrounds/images/gradient_1.jpg");
    setBackgroundImage(back);
}
void herb_win::setBackgroundImage(QString filePath){
    QPixmap bkgnd = QPixmap(filePath);
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    setPalette(palette);
}
void herb_win::resizeEvent(QResizeEvent *evt)
{
    stretchBackground();
    //fitDisplay();

    QDialog::resizeEvent(evt); //call base implementation
}

void herb_win::stretchBackground(){
    QString back(":/backgrounds/images/gradient_1.jpg");
    QPixmap bkgnd(back);
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Window, bkgnd);
    setPalette(p);
}

herb_win::~herb_win()
{
    delete ui;
}
