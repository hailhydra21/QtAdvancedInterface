QT       += core gui concurrent multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Base/GlobalStatic.cpp \
    src/CustomWidget/CircularState.cpp \
    src/CustomWidget/CustomCard.cpp \
    src/CustomWidget/CustomMessageBox.cpp \
    src/CustomWidget/CustomProgressBar.cpp \
    src/CustomWidget/CustomTreeWidget.cpp \
    src/CustomWidget/CustomUserList.cpp \
    src/CustomWidget/CustomUserProfile.cpp \
    src/CustomWidget/MenuItem.cpp \
    src/CustomWidget/MenuItemGroup.cpp \
    src/MainWin/MainWin.cpp \
    src/MainWin/main.cpp \
    src/StackedWidget/HomePage.cpp \
    src/StackedWidget/TempPage.cpp

HEADERS += \
    src/Base/DataType.h \
    src/Base/GlobalStatic.h \
    src/CustomWidget/CircularState.h \
    src/CustomWidget/CustomCard.h \
    src/CustomWidget/CustomMessageBox.h \
    src/CustomWidget/CustomProgressBar.h \
    src/CustomWidget/CustomTreeWidget.h \
    src/CustomWidget/CustomUserList.h \
    src/CustomWidget/CustomUserProfile.h \
    src/CustomWidget/MenuItem.h \
    src/CustomWidget/MenuItemGroup.h \
    src/MainWin/MainWin.h \
    src/StackedWidget/HomePage.h \
    src/StackedWidget/TempPage.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    src/CustomWidget/CircularState.ui \
    src/CustomWidget/CustomCard.ui \
    src/CustomWidget/CustomMessageBox.ui \
    src/CustomWidget/CustomProgressBar.ui \
    src/CustomWidget/MenuItem.ui \
    src/CustomWidget/MenuItemGroup.ui \
    src/MainWin/MainWin.ui \
    src/StackedWidget/HomePage.ui \
    src/StackedWidget/TempPage.ui

RC_FILE = example1.rc

RESOURCES += \
    src/Resoures/SoundEffects.qrc \
    src/Resoures/images.qrc \
    src/Resoures/qss.qrc
