#ifndef PROPERTYSLIDER_H
#define PROPERTYSLIDER_H

#include <QWidget>

namespace Ui {
class PropertySlider;
}

class PropertySlider : public QWidget
{
    Q_OBJECT

public:
    explicit PropertySlider(QWidget *parent = nullptr);
    ~PropertySlider();

private:
    Ui::PropertySlider *ui;
};

#endif // PROPERTYSLIDER_H
