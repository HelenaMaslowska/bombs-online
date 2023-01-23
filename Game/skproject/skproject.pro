QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    game.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    game.h \
    mainwindow.h

FORMS += \
    game.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Graphics/Graphics/bomb.png \
    Graphics/Graphics/boom.png \
    Graphics/Graphics/player1.png \
    Graphics/Graphics/player2.png \
    Graphics/Graphics/player3.png \
    Graphics/Graphics/player4.png \
    Graphics/Graphics/powerup.png \
    Graphics/Graphics/wall.png \
    Graphics/bomb.png \
    Graphics/boom.png \
    Graphics/player1.png \
    Graphics/player2.png \
    Graphics/player3.png \
    Graphics/player4.png \
    Graphics/powerup.png \
    Graphics/wall.png \
    Maps/map1.txt \
    Maps/map2.txt \
    Maps/map3.txt \
    Maps/map4.txt \
    Maps/map5.txt \
    Maps/map6.txt \
    Maps/map7.txt \
    Maps/map8.txt
