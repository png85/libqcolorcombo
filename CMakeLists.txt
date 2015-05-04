#
# CMakeLists.txt for libqcolorcombo
#
project(QColorCombo)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#
# Enable C++11 for GCC builds
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-std=c++11" GCC_stdcxx11)
    check_cxx_compiler_flag("-std=c++0x" GCC_stdcxx0x)

    if(GCC_stdcxx11)
        # Compiler supports -std=c++11
        message(STATUS "Using -std=c++11 to enable C++11 in GCC")
        add_definitions(-std=c++11)
    elseif(GCC_stdcxx0x)
        # Compiler doesn't support -std=c++11 but -std=c++0x
        message(STATUS "Using -std=c++0x to enable C++11 in GCC")
        add_definitions(-std=c++0x)
    else()
        # Neither -std=c++11 nor -std=c++0x are supported
        message(WARNING "Failed to determine C++11 flag for GCC :-(")
    endif()
endif(CMAKE_COMPILER_IS_GNUCXX)

include(CheckCXX11Features)
foreach(flag ${CXX11_FEATURE_LIST})
  add_definitions(-D${flag})
endforeach()


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
