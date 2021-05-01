#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T17:19:24
#
#-------------------------------------------------

QT       += core gui
QT+=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Chess
TEMPLATE = app


SOURCES += main.cpp \
    game.cpp \
    chessbox.cpp \
    chessboard.cpp \
    chesspiece.cpp \
    network.cpp \
    queen.cpp \
    pawn.cpp \
    bishop.cpp \
    knight.cpp \
    rook.cpp \
    king.cpp \
    button.cpp

HEADERS  += \
    game.h \
    chessbox.h \
    chessboard.h \
    chesspiece.h \
    network.h \
    queen.h \
    pawn.h \
    bishop.h \
    knight.h \
    rook.h \
    king.h \
    button.h

FORMS    +=

RESOURCES += \
    resource.qrc

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/Downloads/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

