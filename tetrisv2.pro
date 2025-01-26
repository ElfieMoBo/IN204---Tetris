QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

QMAKE_CXXFLAGS += "-I../dwarfstack/include"

win32:RC_ICONS += tetrisv2.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    board.cpp \
    main.cpp \
    menu.cpp \
    piece.cpp \
    qboard.cpp \
    server.cpp \
    show.cpp

HEADERS += \
    board.hpp \
    menu.hpp \
    piece.hpp \
    qboard.hpp \
    server.hpp \
    shape2D.hpp \
    show.hpp


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
