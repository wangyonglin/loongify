QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimediawidgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include($$PWD/QVideoFFmpeg/QVideoFFmpeg.pri)

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CameraWidget.cpp \
    VideoWidget.cpp \
    main.cpp \
    MainWidget.cpp

HEADERS += \
    CameraWidget.h \
    MainWidget.h \
    VideoWidget.h

INCLUDEPATH +=$$PWD/ffmpeg-n4.4.1-50-ga4e1dd6940-win64-gpl-shared-4.4/include

LIBS += $$PWD/ffmpeg-n4.4.1-50-ga4e1dd6940-win64-gpl-shared-4.4/lib/avcodec.lib \
        $$PWD/ffmpeg-n4.4.1-50-ga4e1dd6940-win64-gpl-shared-4.4/lib/avfilter.lib \
        $$PWD/ffmpeg-n4.4.1-50-ga4e1dd6940-win64-gpl-shared-4.4/lib/avformat.lib \
        $$PWD/ffmpeg-n4.4.1-50-ga4e1dd6940-win64-gpl-shared-4.4/lib/avutil.lib \
        $$PWD/ffmpeg-n4.4.1-50-ga4e1dd6940-win64-gpl-shared-4.4/lib/postproc.lib \
        $$PWD/ffmpeg-n4.4.1-50-ga4e1dd6940-win64-gpl-shared-4.4/lib/swresample.lib \
        $$PWD/ffmpeg-n4.4.1-50-ga4e1dd6940-win64-gpl-shared-4.4/lib/swscale.lib
TRANSLATIONS += \
    loongpulse_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon_kjiaii37s5c.qrc \
    resources.qrc


