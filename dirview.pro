QT += widgets
requires(qtConfig(treeview))

SOURCES       = main.cpp \
    filesystemdirsizemodel.cpp \
    mainwindow.cpp \
    pushbuttonitemdelegate.cpp \
    pushbuttonwithflag.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/itemviews/dirview
INSTALLS += target

DISTFILES +=

FORMS += \
    mainwindow.ui

HEADERS += \
    filesystemdirsizemodel.h \
    mainwindow.h \
    pushbuttonitemdelegate.h \
    pushbuttonwithflag.h
