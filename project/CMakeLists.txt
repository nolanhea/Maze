cmake_minimum_required(VERSION 3.5)

project(Maze VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Threads REQUIRED)


set(PROJECT_SOURCES
        main.cpp
        view/mainwindow.cpp
        view/mainwindow.h
        view/mainwindow.ui
        maze/maze_generator.cpp
        maze/maze_generator.h
        view/MazeDrawer.h
        view/mazeview.h
        view/mazeview.cpp
        maze/mazesolver.h
        maze/mazesolver.cpp
        cavity/cavitygenerator.h
        view/cavityview.h
        view/cavityview.cpp
        view/MazeDrawer.cpp
        cavity/cavitygenerator.cpp
        #gtest/maze_generator_unittest.cpp
        #gtest/cavity_generator_unittest.cpp
        #gtest/maze_solver_unittest.cpp

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Maze
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Maze APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Maze SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Maze
            ${PROJECT_SOURCES}
        )
    endif()
endif()


set_target_properties(Maze PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Maze
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

target_link_libraries(
  Maze
  PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
  PRIVATE Threads::Threads
  #GTest::gtest_main
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Maze)
endif()


