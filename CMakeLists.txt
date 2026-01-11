cmake_minimum_required(VERSION 3.16)

project(KioskServer1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Network Quick Qml Sql)

qt_add_executable(appKioskServer1
    src/main.cpp
    src/echo_server.cpp
    src/echo_server.h
    src/TableManager.cpp
    src/TableManager.h
    src/DbManager.cpp
    src/DbManager.h
)

qt_add_qml_module(appKioskServer1
    URI KioskServer1
    VERSION 1.0

    QML_FILES
        qml/main.qml
        qml/ServerPage.qml
        qml/TablePage.qml
        qml/TableDetailPage.qml
        qml/HeaderBar.qml
        qml/TableCard.qml

    SOURCES
        src/TableManager.h
        src/TableManager.cpp
        src/DbManager.h
        src/DbManager.cpp
)

target_link_libraries(appKioskServer1
    PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Qml
        Qt6::Network
        Qt6::Sql
)

qt_finalize_executable(appKioskServer1)
