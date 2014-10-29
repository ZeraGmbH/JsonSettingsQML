TEMPLATE = lib
TARGET = JsonSettings
QT += qml quick
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = JsonSettings

# Input
SOURCES += \
    jsonglobalsettings.cpp \
    jsonsettingsfile.cpp \
    jsonsettings_plugin.cpp

HEADERS += \
    jsonglobalsettings.h \
    jsonsettingsfile.h \
    jsonsettings_plugin.h

OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

equals(QT_MAJOR_VERSION, 5){
  equals(QT_MINOR_VERSION, 3){
    #Qt is broken: https://bugreports.qt-project.org/browse/QTBUG-37638
    CONFIG -= android_install
  }
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

