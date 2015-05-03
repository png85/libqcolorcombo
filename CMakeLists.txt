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

if(NOT QColorCombo_BUILD_AS_SUBMODULE)
    set(CPACK_PACKAGE_DESCRIPTION "QColorCombo widget for Qt4")
    set(CPACK_PACKAGE_VERSION_MAJOR 1)
    set(CPACK_PACKAGE_VERSION_MINOR 0)
    set(CPACK_PACKAGE_VERSION_PATCH 1)
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
include_directories(${CMAKE_CURRENT_BINARY_DIR})

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
QT4_CREATE_TRANSLATION(QCOLORCOMBO_QM_FILES_UPDATE ${QCOLORCOMBO_SOURCES} QColorCombo.ts)
QT4_ADD_TRANSLATION(QCOLORCOMBO_QM_FILES QColorCombo-en_US.ts
                                         QColorCombo-de_DE.ts)
add_library(QColorCombo ${LIB_TYPE} ${QCOLORCOMBO_MOC_SOURCES} ${QCOLORCOMBO_SOURCES} ${QCOLORCOMBO_QM_FILES} ${QCOLORCOMBO_QM_FILES_UPDATE})
if(UNIX AND QColorCombo_BUILD_SHARED_LIBS)
    target_set_properties(QColorCombo PROPERTIES SONAME "QColorCombo" SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR})
endif(UNIX AND QColorCombo_BUILD_SHARED_LIBS)
target_link_libraries(QColorCombo ${QT_LIBRARIES})
generate_export_header(QColorCombo BASE_NAME QColorCombo
                                   EXPORT_MACRO_NAME QColorCombo_EXPORT
                                   EXPORT_FILE_NAME QColorCombo_Export.h
                                   STATIC_DEFINE QColorCombo_BUILT_AS_STATIC)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QColorCombo_Export.h DESTINATION include)
install(TARGETS QColorCombo ARCHIVE DESTINATION lib
                            LIBRARY DESTINATION lib
                            RUNTIME DESTINATION bin)
install(FILES ${QCOLORCOMBO_HEADERS} DESTINATION include)
install(FILES ${QCOLORCOMBO_QM_FILES} DESTINATION translations)
install(FILES ${QCOLORCOMBO_QM_FILES_UPDATE} DESTINATION translations)

#
# QColorComboPlugin: Qt Designer plugin to use QColorCombo in .ui files
if(QColorCombo_WITH_DESIGNER_PLUGIN)
  add_definitions(${QT_DEFINITIONS})
  add_definitions(-DQT_PLUGIN)
  add_definitions(-DQT_SHARED)
  if(WIN32)
    add_definitions(-DQT_DLL)
  endif(WIN32)
  set(libQColorComboPlugin_MOC_HDRS QColorComboDesignerFactory.h)
  set(libQColorComboPlugin_SRCS QColorComboDesignerFactory.cc)
  qt4_wrap_cpp(libQColorComboPlugin_MOC_SRCS ${libQColorComboPlugin_MOC_HDRS})
  QT4_CREATE_TRANSLATION(libQColorComboPlugin_QM_SRCS_UPDATE ${libQColorComboPlugin_SRCS} QColorComboPlugin.ts)
  QT4_ADD_TRANSLATION(libQColorComboPlugin_QM_SRCS QColorComboPlugin-en_US.ts QColorComboPlugin-de_DE.ts)
  add_library(QColorComboPlugin SHARED ${libQColorComboPlugin_MOC_SRCS} ${libQColorComboPlugin_SRCS} ${libQColorComboPlugin_QM_SRCS} ${libQColorComboPlugin_QM_SRCS_UPDATE})
  target_link_libraries(QColorComboPlugin QColorCombo ${QT_LIBRARIES})
  install(TARGETS QColorComboPlugin ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
  install(FILES ${libQColorComboPlugin_QM_SRCS} DESTINATION translations)
  install(FILES ${libQColorComboPlugin_QM_SRCS_UPDATE} DESTINATION translations)
  install(TARGETS QColorComboPlugin DESTINATION ${QT_PLUGINS_DIR}/designer)
endif(QColorCombo_WITH_DESIGNER_PLUGIN)

#
# example: Simple example program to demonstrate QColorCombo
if(QColorCombo_WITH_EXAMPLE)
  set(EXAMPLE_SOURCES example.cc ExampleWindow.cc)
  set(EXAMPLE_MOC_HEADERS ExampleWindow.h)
  QT4_WRAP_CPP(EXAMPLE_MOC_SOURCES ${EXAMPLE_MOC_HEADERS})
  add_executable(example ${EXAMPLE_MOC_SOURCES} ${EXAMPLE_SOURCES})
  target_link_libraries(example QColorCombo)
  target_link_libraries(example ${QT_LIBRARIES})
endif(QColorCombo_WITH_EXAMPLE)
