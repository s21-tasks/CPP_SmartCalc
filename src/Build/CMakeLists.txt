cmake_minimum_required(VERSION 3.5)

project(calc_view VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS PrintSupport)

set(PROJECT_SOURCES
        main.cc
        qcustomplot.cpp
        qcustomplot.h
        ../View/mainwindow.cc
        ../View/mainwindow.h
        ../View/mainwindow.ui
        ../Controller/Controller.cc
        ../Controller/Controller.h
        ../Model/Model.cc
        ../Model/Model.h

)

set(MACOSX_BUNDLE_ICON_FILE MyIcon.icns)
#target_include_directories(calc PUBLIC qcustomplot.h)
set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/MyIcon.icns")
set_source_files_properties(${app_icon_macos} PROPERTIES
           MACOSX_PACKAGE_LOCATION "Resources")


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calc_view
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${app_icon_macos}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET calc_view APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(calc_view SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(calc_view
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(calc_view PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(calc_view PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(calc_view PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calc_view)
endif()
