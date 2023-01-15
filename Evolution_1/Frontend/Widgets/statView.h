#ifndef STATVIEW_H
#define STATVIEW_H

#include "Living_Beings/living_being.h"
#include "qboxlayout.h"
#include "qlabel.h"
#include "qwidget.h"

//qstring is stupid and I can't figure out a better way to deal with it
template<typename T>
    inline QString to_QString(T number){
        return QString::number(number);
    };
template<>
    inline QString to_QString(std::string string){
        return QString::fromStdString(string);
    };
//A simple label showing one parameter of a being
//The left label has the text provided by the labelText and the value is provided by the getter function getterFunct of the respective being
template<class Being, typename T>
    class ParameterDisplay: public QWidget{
        public:
            // here you give the environment if you want the display to update together with it (when the updated signal is called from the environment)
            ParameterDisplay(std::string labelText, Being* being, T (Being::*getterFunc)(), QWidget* parent, Environment* environment = nullptr) : QWidget(parent),
                                                                                                                                                   being(being),
                                                                                                                                                   getterFunc(getterFunc){
                if(environment != nullptr)
                    connect(environment, &Environment::updated, this, &ParameterDisplay<Being, T>::update);
                connect(being, &LivingBeing::destroyed, this, &ParameterDisplay<Being, T>::being_destroyed); //this is so dumb, but very necessary as we need to stop updating the widget once the being does not exist anymore

                init_layout( QString::fromStdString(labelText), to_QString( (being->*getterFunc)() ) );

            }
            //might be useful for having a nice stat display quickly, but the compiler does not infer template types (as they are not needed) so it's ugly; I'll keep it for now
            ParameterDisplay(std::string labelText, std::string value, QWidget* parent) : QWidget(parent){
                init_layout( QString::fromStdString(labelText), QString::fromStdString(value) );
            }

            void update(){
                if(not destroyed)
                    parameterLabel->setText( to_QString( (being->*getterFunc)() ) );
            }

        private:
            bool destroyed = false;
            void being_destroyed(QObject* obj){
                destroyed = true;
                setStyleSheet("QWidget{color: red}");
            }

            QLabel* label;
            QLabel* parameterLabel;

            Being* being;
            T (Being::*getterFunc)();

            void init_layout(QString labelText, QString value){
                auto layout = new QHBoxLayout;

                label = new QLabel( labelText, this );
                label->setAlignment(Qt::AlignCenter);

                parameterLabel = new QLabel(this);
                parameterLabel->setText( value );
                parameterLabel->setStyleSheet("QLabel { background-color : gray;"
                                              "color : white; }");
                parameterLabel->setAlignment(Qt::AlignCenter);

                layout->addWidget(label);
                layout->addWidget(parameterLabel);
                setLayout(layout);

                setStyleSheet("QWidget#ParameterDisplayWidget{border: 1px solid black}");
                setObjectName("ParameterDisplayWidget"); //important for updating but also the stylesheet
            }
    };

//A window that you get by double-clicking a living being on the display and shows its parameters
class StatView : public QWidget{
    public:
        StatView(LivingBeing* being = nullptr, QWidget* parent = nullptr);

        void update();

        int get_updates(){return updates;}

    private:
        LivingBeing* being;

        void setTitle(std::string title = "");
        int updates = 0;
};

#endif // STATVIEW_H
