find_package(Qt5Widgets)

if(Qt5Widgets_FOUND AND QColorCombo_ENABLE_QT5)
    if(WIN32)
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(QColorCombo_LIBRARY QBrowseButton5d)
        else(CMAKE_BUILD_TYPE STREQUAL "Debug")
            set(QColorCombo_LIBRARY QBrowseButton5)
        endif(CMAKE_BUILD_TYPE_STREQUAL "Debug")
    else(WIN32)
        set(QColorCombo_LIBRARY QBrowseButton5)
    endif(WIN32)
    add_library(${QColorCombo_LIBRARY} ${LIB_TYPE} ../src/QColorCombo.cc ../include/QColorCombo.h)
    qt5_use_modules(${QColorCombo_LIBRARY} Widgets)
    if(UNIX AND QColorCombo_BUILD_SHARED_LIBS)
        set_target_properties(${QColorCombo_LIBRARY} PROPERTIES SONAME "QColorCombo5"
                                                     VERSION ${QColorCombo_VERSION_MAJOR}.${QColorCombo_VERSION_MINOR}
                                                     SOVERSION ${QColorCombo_VERSION_MAJOR})
    endif(UNIX AND QColorCombo_BUILD_SHARED_LIBS)
    generate_export_header(${QColorCombo_LIBRARY} BASE_NAME QColorCombo
                                                  EXPORT_MACRO_NAME QColorCombo_EXPORT
                                                  EXPORT_FILE_NAME QColorCombo5_Export.h
                                                  STATIC_DEFINE QColorCombo_BUILT_AS_STATIC)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/QColorCombo5_Export.h DESTINATION include/)
    install(TARGETS ${QColorCombo_LIBRARY} ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)


    if(QColorCombo_WITH_EXAMPLE)
        add_executable(${QColorCombo_LIBRARY}-test ../src/example.cc ../src/ExampleWindow.cc ../include/ExampleWindow.h)
        qt5_use_modules(${QColorCombo_LIBRARY}-test Widgets)
        target_link_libraries(${QColorCombo_LIBRARY}-test ${QColorCombo_LIBRARY})
        install(TARGETS ${QColorCombo_LIBRARY}-test RUNTIME DESTINATION bin)
    endif(QColorCombo_WITH_EXAMPLE)

    if(QColorCombo_WITH_DESIGNER_PLUGIN)
        add_definitions(-DQT_SHARED -DQT_PLUGIN)
        if(WIN32)
            add_definitions(-DQT_DLL)
        endif(WIN32)
        add_library(${QColorCombo_LIBRARY}Plugin SHARED ../src/QColorComboDesignerFactory.cc ../include/QColorComboDesignerFactory.h)
        qt5_use_modules(${QColorCombo_LIBRARY}Plugin Widgets)
        target_link_libraries(${QColorCombo_LIBRARY}Plugin ${QColorCombo_LIBRARY})
        install(TARGETS ${QColorCombo_LIBRARY}Plugin ARCHIVE DESTINATION lib/qt5/plugins/designer LIBRARY DESTINATION lib/qt5/plugins/designer RUNTIME DESTINATION lib/qt5/plugins/designer)
    endif(QColorCombo_WITH_DESIGNER_PLUGIN)
endif(Qt5Widgets_FOUND AND QColorCombo_ENABLE_QT5)
