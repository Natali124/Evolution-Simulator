TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG+=debug

QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O0



HEADERS += \
    Neural Network/network.hpp \
    common.hpp \
    creature.hpp \
    food.hpp \
    living_being.hpp \
    plant.hpp \
    network.hpp

SOURCES += \
        Neural Network/network.cpp \
        common.cpp \
        creature.cpp \
        living_being.cpp \
        main.cpp \
        plant.cpp \
        network.cpp

TARGET = grading

