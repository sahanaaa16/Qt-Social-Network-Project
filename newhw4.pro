QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    home.cpp \
    network.cpp \
    post.cpp \
    song.cpp \
    user.cpp

HEADERS += \
    home.h \
    network.h \
    post.h \
    song.h \
    user.h

FORMS += \
    home.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../hw4.txt \
    ../posts.txt \
    hw4.txt \
    posts.txt \
    songs.txt \
    try again
