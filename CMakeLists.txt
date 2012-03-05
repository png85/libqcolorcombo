#
# CMakeLists.txt for libqcolorcombo
#
project(libqcolorcombo)
cmake_minimum_required(VERSION 2.8)

#
# Locate Qt4 headers/libraries
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(QCOLORCOMBO_SOURCES qcolorcombo.cc)
set(QCOLORCOMBO_MOC_HEADERS qcolorcombo.h)
set(QCOLORCOMBO_HEADERS QColorCombo ${QCOLORCOMBO_MOC_HEADERS})

QT4_WRAP_CPP(QCOLORCOMBO_MOC_SOURCES ${QCOLORCOMBO_MOC_HEADERS})

add_library(QColorCombo ${QCOLORCOMBO_MOC_SOURCES} ${QCOLORCOMBO_SOURCES})
