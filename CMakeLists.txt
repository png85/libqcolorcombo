#
# CMakeLists.txt for libqcolorcombo
#
project(libqcolorcombo)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(CheckCXX11Features)
foreach(flag ${CXX11_FEATURE_LIST})
  add_definitions(-D${flag})
endforeach()

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++0x")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS)

  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG)
endif(CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W4")
  list(REMOVE_DUPLICATES CMAKE_CXX_FLAGS_DEBUG)
endif(MSVC)


#
# Locate Qt4 headers/libraries
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

#
# libQtColorCombo: library that contains our widget
set(QCOLORCOMBO_SOURCES QColorCombo.cc)
set(QCOLORCOMBO_MOC_HEADERS QColorCombo.h)
set(QCOLORCOMBO_HEADERS ${QCOLORCOMBO_MOC_HEADERS})
QT4_WRAP_CPP(QCOLORCOMBO_MOC_SOURCES ${QCOLORCOMBO_MOC_HEADERS})

option(QCOLORCOMBO_UPDATE_TRANSLATIONS "Update translations in source tree" OFF)
if(QCOLORCOMBO_UPDATE_TRANSLATIONS)
  QT4_CREATE_TRANSLATION(QCOLORCOMBO_QM_FILES ${QCOLORCOMBO_SOURCES} QColorCombo.ts)
else(QCOLORCOMBO_UPDATE_TRANSLATIONS)
  QT4_ADD_TRANSLATION(QCOLORCOMBO_QM_FILES QColorCombo.ts)
endif(QCOLORCOMBO_UPDATE_TRANSLATIONS)

add_library(QColorCombo ${QCOLORCOMBO_MOC_SOURCES} ${QCOLORCOMBO_SOURCES} ${QCOLORCOMBO_QM_FILES})
install(TARGETS QColorCombo ARCHIVE DESTINATION lib)
install(FILES ${QCOLORCOMBO_HEADERS} DESTINATION include)
install(FILES ${QCOLORCOMBO_QM_FILES} DESTINATION translations)


#
# QColorComboPlugin: Qt Designer plugin to use QColorCombo in .ui files
option(QCOLORCOMBO_WITH_DESIGNER_PLUGIN "Build plugin to use widget in Qt Designer" ON)
if(QCOLORCOMBO_WITH_DESIGNER_PLUGIN)
  add_definitions(${QT_DEFINITIONS})
  add_definitions(-DQT_PLUGIN)
  add_definitions(-DQT_SHARED)
  if(WIN32)
    add_definitions(-DQT_DLL)
  endif(WIN32)
  set(libQColorComboPlugin_MOC_HDRS QColorComboDesignerFactory.h)
  set(libQColorComboPlugin_SRCS QColorComboDesignerFactory.cc)
  QT4_WRAP_CPP(libQColorComboPlugin_MOC_SRCS ${libQColorComboPlugin_MOC_HDRS})
  add_library(QColorComboPlugin SHARED ${libQColorComboPlugin_MOC_SRCS} ${libQColorComboPlugin_SRCS}
                                       ${QCOLORCOMBO_MOC_SOURCES} ${QCOLORCOMBO_SOURCES} ${QCOLORCOMBO_PM_FILES})
  target_link_libraries(QColorComboPlugin ${QT_LIBRARIES})
  install(TARGETS QColorComboPlugin DESTINATION ${QT_PLUGINS_DIR}/designer)
endif(QCOLORCOMBO_WITH_DESIGNER_PLUGIN)

#
# example: Simple example program to demonstrate QColorCombo
set(EXAMPLE_SOURCES example.cc ExampleWindow.cc)
set(EXAMPLE_MOC_HEADERS ExampleWindow.h)
QT4_WRAP_CPP(EXAMPLE_MOC_SOURCES ${EXAMPLE_MOC_HEADERS})
add_executable(example ${EXAMPLE_MOC_SOURCES} ${EXAMPLE_SOURCES})
target_link_libraries(example QColorCombo)
target_link_libraries(example ${QT_LIBRARIES})
