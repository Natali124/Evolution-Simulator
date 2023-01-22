cmake_minimum_required(VERSION 3.5)

project(Evolution_1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Evolution_1_en_GB.ts)

#python trying
#find_package(PythonLibs REQUIRED)
#include_directories(${PYTHON_INCLUDE_DIRS})
#find_package (Python COMPONENTS Interpreter Development)
#set(Python_INCLUDE_DIRS "/opt/anaconda3/envs/python37/include/python3.7m")
#set(Python_LIBRARY "/opt/anaconda3/envs/python37/lib/python3.7")

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        environment.h
        environment.cpp
        Living_Beings/living_being.h
        Living_Beings/living_being.cpp
        Living_Beings/creature.h
        Living_Beings/creature.cpp
        Living_Beings/plant.h
        Living_Beings/plant.cpp
        Neural_Network/edge.cpp
        Neural_Network/edge.hpp
        Neural_Network/layer.cpp
        Neural_Network/layer.hpp
        Neural_Network/network.cpp
        Neural_Network/network.hpp
        Neural_Network/neuron.cpp
        Neural_Network/neuron.hpp
        Neural_Network/utils.cpp
        Neural_Network/test_python_integration.cpp
        Neural_Network/test
        results.txt
        Frontend/Widgets/simulationViewWidgets.h
        Frontend/Widgets/creatureDisplay.cpp
        Frontend/Widgets/simulationView.h
        Frontend/Widgets/simulationView.cpp
        Frontend/mainMenuResources.qrc
        Neural_Network/nn_evolution.cpp
        Neural_Network/nn_evolution.hpp
        Neural_Network/reading.hpp
        Neural_Network/reading.cpp
        Frontend/CreatureDesigns.qrc
        Frontend/resources.h
        Frontend/Widgets/SimulationSpeedSlider.cpp
        Frontend/Widgets/environmentTimer.cpp
        Frontend/Widgets/statView.h
        Frontend/Widgets/statView.cpp
        barrier.h barrier.cpp
        Frontend/startscreen.h Frontend/startscreen.cpp Frontend/startscreen.ui
        Frontend/startscreen/propertyslider.h Frontend/startscreen/propertyslider.cpp Frontend/startscreen/propertyslider.ui
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Evolution_1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Evolution_1 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Evolution_1 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Evolution_1
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Evolution_1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(Evolution_1 PRIVATE Qt${PYTHON_INCLUDE_DIRS})

set_target_properties(Evolution_1 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Evolution_1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Evolution_1)
endif()
