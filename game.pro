QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app.cpp \
    leaderboard.cpp \
    main.cpp \
    menuscreen.cpp \
    recordlistmodel.cpp \
    settings.cpp \
    snake.cpp

HEADERS += \
    app.h \
    leaderboard.h \
    menuscreen.h \
    recordlistmodel.h \
    settings.h \
    snake.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/apple.png \
    images/apple_krasivoe.png \
    images/dot.png \
    images/dot_black.png \
    images/dot_white.png \
    images/head.png
