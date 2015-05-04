find_package(Qt4 COMPONENTS QtCore QtGui)
if(Qt4_FOUND AND QColorCombo_ENABLE_QT4)
    add_library(QColorCombo4 ${LIB_TYPE} ../src/QColorCombo.cc ../include/QColorCombo.h)
    target_link_libraries(QColorCombo4 Qt4::QtGui Qt4::QtCore)
    if(UNIX AND QColorCombo_BUILD_SHARED_LIBS)
        set_target_properties(QColorCombo4 PROPERTIES SONAME "QColorCombo4"
                                                      VERSION ${QColorCombo_VERSION_MAJOR}.${QColorCombo_VERSION_MINOR}
                                                      SOVERSION ${QColorCombo_VERSION_MAJOR})
    endif(UNIX AND QColorCombo_BUILD_SHARED_LIBS)
    generate_export_header(QColorCombo4 BASE_NAME QColorCombo
                                        EXPORT_MACRO_NAME QColorCombo_EXPORT
                                        EXPORT_FILE_NAME QColorCombo4_Export.h
                                        STATIC_DEFINE QColorCombo_BUILT_AS_STATIC)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QColorCombo4_Export.h DESTINATION include)
    install(TARGETS QColorCombo4 ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)

    if(QColorCombo_WITH_EXAMPLE)
        add_executable(QColorCombo4-test ../src/example.cc ../src/ExampleWindow.cc ../include/ExampleWindow.h)
        target_link_libraries(QColorCombo4-test QColorCombo4 Qt4::QtCore Qt4::QtGui)
        install(TARGETS QColorCombo4-test RUNTIME DESTINATION bin)
    endif(QColorCombo_WITH_EXAMPLE)

    if(QColorCombo_WITH_DESIGNER_PLUGIN)
        add_definitions(-DQT_PLUGIN -DQT_SHARED)
        if(WIN32)
            add_definitions(-DQT_DLL)
        endif(WIN32)
        add_library(QColorCombo4Plugin SHARED ../src/QColorComboDesignerFactory.cc ../include/QColorComboDesignerFactory.h)
        target_link_libraries(QColorCombo4Plugin QColorCombo4 Qt4::QtGui Qt4::QtCore)
        install(TARGETS QColorCombo4Plugin ARCHIVE DESTINATION lib/qt4/plugins/designer LIBRARY DESTINATION lib/qt4/plugins/designer RUNTIME DESTINATION lib/qt4/plugins/designer)
    endif(QColorCombo_WITH_DESIGNER_PLUGIN)
endif(Qt4_FOUND AND QColorCombo_ENABLE_QT4)
