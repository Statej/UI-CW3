QT += core gui widgets multimedia multimediawidgets

CONFIG += c++11


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        play_pause.cpp \
        progress_slider.cpp \
        the_button.cpp \
        the_player.cpp \
        tomeo.cpp \
        volume_button.cpp \
        volume_slider.cpp

HEADERS += \
    play_pause.h \
    progress_slider.h \
    the_button.h \
    the_player.h \
    volume_button.h \
    volume_slider.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

