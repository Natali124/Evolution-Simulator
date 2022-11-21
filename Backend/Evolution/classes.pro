TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG+=debug

QMAKE_CXXFLAGS_DEBUG -= -O2
QMAKE_CXXFLAGS_DEBUG += -O0



HEADERS += \
    common.hpp \
    creature.hpp \
    food.hpp \
    environment.hpp \
    living_being.hpp \
    plant.hpp

SOURCES += \
        common.cpp \
        creature.cpp \
        environment.cpp \
        living_being.cpp \
        main.cpp \
        plant.cpp

TARGET = grading

