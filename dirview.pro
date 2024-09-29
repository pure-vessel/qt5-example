QT += widgets
requires(qtConfig(treeview))

SOURCES       = main.cpp \
    mainwindow.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/dirview
INSTALLS += target

DISTFILES +=

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h
