#
# CMakeLists.txt for libqcolorcombo
#
project(libqcolorcombo)
cmake_minimum_required(VERSION 2.8)

#
# Locate Qt4 headers/libraries
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

#
# libQtColorCombo: library that contains our widget
set(QCOLORCOMBO_SOURCES qcolorcombo.cc)
set(QCOLORCOMBO_MOC_HEADERS qcolorcombo.h)
set(QCOLORCOMBO_HEADERS QColorCombo ${QCOLORCOMBO_MOC_HEADERS})
set(QCOLORCOMBO_TS qcolorcombo.ts)

QT4_ADD_TRANSLATION(QCOLORCOMBO_TS_SOURCES ${QCOLORCOMBO_TS})
QT4_WRAP_CPP(QCOLORCOMBO_MOC_SOURCES ${QCOLORCOMBO_MOC_HEADERS})

add_library(QColorCombo ${QCOLORCOMBO_MOC_SOURCES} 
  ${QCOLORCOMBO_TS_SOURCES} ${QCOLORCOMBO_SOURCES})

install(TARGETS QColorCombo ARCHIVE DESTINATION lib)
install(FILES ${QCOLORCOMBO_HEADERS} DESTINATION include)
install(FILES ${QCOLORCOMBO_TS_SOURCES} DESTINATION translations)

#
# example: Simple example program to demonstrate QColorCombo
set(EXAMPLE_SOURCES example.cc ExampleWindow.cc)
set(EXAMPLE_MOC_HEADERS ExampleWindow.h)
QT4_WRAP_CPP(EXAMPLE_MOC_SOURCES ${EXAMPLE_MOC_HEADERS})
add_executable(example ${EXAMPLE_MOC_SOURCES} ${EXAMPLE_SOURCES})
target_link_libraries(example QColorCombo)
target_link_libraries(example ${QT_LIBRARIES})
