CONFIG      += designer plugin debug_and_release

TEMPLATE    = lib

HEADERS     = \
    ../../UiTest/iconeditor.h \
    iconeditorplugin.h
SOURCES     = \
    ../../UiTest/iconeditor.cpp \
    iconeditorplugin.cpp
RESOURCES   = icons.qrc

DESTDIR = $$[QT_INSTALL_PLUGINS]/designer
