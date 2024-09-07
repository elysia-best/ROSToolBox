cmake_minimum_required(VERSION 3.14)

project(ROSToolBox VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt5 REQUIRED COMPONENTS Core Quick Qml Widgets PrintSupport LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick Qml Widgets PrintSupport LinguistTools)

find_package(FluentUI 1.7.7 REQUIRED)

include_directories(src/inc)

#遍历所有Cpp/h文件
file(GLOB_RECURSE CPP_FILES *.cpp *.h)
foreach (filepath ${CPP_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND PROJECT_SOURCES ${filename})
endforeach (filepath)

#遍历所有qrc文件
file(GLOB_RECURSE QRC_FILES *.qrc)
foreach (filepath ${QRC_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND PROJECT_SOURCES ${filename})
endforeach (filepath)

file(GLOB_RECURSE TS_FILES translations/*.ts)
foreach (filepath ${TS_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
    list(APPEND TS_FILES ${filename})
    list(APPEND PROJECT_SOURCES ${filename})
endforeach (filepath)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ROSToolBox
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ROSToolBox APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(ROSToolBox SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ROSToolBox
          ${PROJECT_SOURCES}
        )
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

add_custom_target(translations ALL DEPENDS ${QM_FILES} SOURCES ${TS_FILES})

foreach(_ts_file ${TS_FILES})
    execute_process(
        COMMAND ${LUPDATE_EXECUTABLE} -recursive ${CMAKE_SOURCE_DIR} -ts ${_ts_file})
    execute_process(COMMAND lrelease ${CMAKE_SOURCE_DIR}/${_ts_file})
endforeach()

target_compile_definitions(ROSToolBox
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(ROSToolBox
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  fluentuiplugin
)

set_target_properties(ROSToolBox PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER rostoolbox.qinyn.eu.org
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(ROSToolBox)
    qt_finalize_executable(ROSToolBox)
endif()
