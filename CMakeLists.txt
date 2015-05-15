#
# CMakeLists.txt for libqcolorcombo
#
project(QColorCombo)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


#
# User configurable build options
option(QColorCombo_BUILD_AS_SUBMODULE "Build QColorCombo as git submodule?" OFF)
option(QColorCombo_BUILD_SHARED_LIBS "Build QColorCombo as shared library?" ON)
option(QColorCombo_WITH_DESIGNER_PLUGIN "Build plugin to use QColorCombo with Qt Designer?" ON)
option(QColorCombo_WITH_EXAMPLE "Build small example program for QColorCombo?" ON)
option(QColorCombo_ENABLE_QT4 "Build QColorCombo widget for Qt4?" ON)
option(QColorCombo_ENABLE_QT5 "Build QColorCombo widget for Qt5?" ON)

set(QColorCombo_VERSION_MAJOR 1)
set(QColorCombo_VERSION_MINOR 1)
set(QColorCombo_VERSION_PATCH 0)

if(NOT QColorCombo_BUILD_AS_SUBMODULE)
    set(CPACK_PACKAGE_DESCRIPTION "QColorCombo widget for Qt4")
    set(CPACK_PACKAGE_VERSION_MAJOR ${QColorCombo_VERSION_MAJOR})
    set(CPACK_PACKAGE_VERSION_MINOR ${QColorCombo_VERSION_MINOR})
    set(CPACK_PACKAGE_VERSION_PATCH ${QColorCombo_VERSION_PATCH})
    if(WIN32)
        set(CPACK_GENERATOR "ZIP")
    endif(WIN32)
    include(CPack)
endif(NOT QColorCombo_BUILD_AS_SUBMODULE)


#
# Set library type depending on user choice
if(QColorCombo_BUILD_SHARED_LIBS)
    set(LIB_TYPE SHARED)
else(QColorCombo_BUILD_SHARED_LIBS)
    set(LIB_TYPE STATIC)
endif(QColorCombo_BUILD_SHARED_LIBS)

include(GenerateExportHeader)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

if(NOT QColorCombo_ENABLE_QT4 AND NOT QColorCombo_ENABLE_QT5)
    message(ERROR "You have to select at least one of Qt4/5!")
endif(NOT QColorCombo_ENABLE_QT4 AND NOT QColorCombo_ENABLE_QT5)

if(QColorCombo_ENABLE_QT4)
    add_subdirectory(QColorCombo4)
endif(QColorCombo_ENABLE_QT4)
if(QColorCombo_ENABLE_QT5)
    add_subdirectory(QColorCombo5)
endif(QColorCombo_ENABLE_QT5)

install(FILES include/QColorCombo.h DESTINATION include)
