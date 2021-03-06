

#/****************************************************************
# * This file is distributed under the following license:
# *
# * Copyright (C) 2017, Bernd Stramm

#This is free software: you can redistribute it and/or modify
#it under the terms of the GNU Affero General Public License as
#published by the Free Software Foundation, either version 3 of the
#License, or (at your option) any later version.

#This program is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU Affero General Public License for more details.

#You should have received a copy of the GNU Affero General Public License
#along with this program. If not, see <http://www.gnu.org/licenses/>.

# ****************************************************************/



QT += gui
QT += core
QT += widgets
QT += quick
CONFIG += c++11

CONFIG += debug_and_release

CONFIG(debug,debug|release)  {
  TARGET = bclkd
}
else {
  TARGET = bclk
}
TEMPLATE = app

target.path = /usr/bin/
INSTALLS += target

MOC_DIR = moctmp
OBJECTS_DIR = objtmp
UI_DIR = uitmp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/main.cpp\
        src/mainwindow.cpp \
    src/settingschange.cpp \
    src/licensewindow.cpp \
    src/version.cpp \
    src/deliberate.cpp \
    src/cmdoptions.cpp \
    src/config-edit.cpp

HEADERS  += \
        src/mainwindow.h \
    src/settingschange.h \
    src/agpl2.h \
    src/licensewindow.h \
    src/version.h \
    src/deliberate.h \
    src/cmdoptions.h \
    src/config-edit.h

FORMS    += \
    ui/settingschange.ui \
    ui/licensewindow.ui \
    ui/mainwindow.ui

RESOURCES += \
    clock.qrc

DISTFILES += \
    LICENSE.txt \
    img/agplv3-88x31.png \
    img/up.png \
    img/down.img
