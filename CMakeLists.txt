cmake_minimum_required(VERSION 3.8.12)
project(JsonSettingsQml VERSION 1.0 LANGUAGES CXX C)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    message(STATUS "Debug type: " ${CMAKE_BUILD_TYPE})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -O0 -g")
endif()
# Tell CMake to call moc automaticly
set(CMAKE_AUTOMOC ON)



set(JsonSettingsQml_VERSION_MAJOR "0")
set(JsonSettingsQml_VERSION_MINOR "0")
set(JsonSettingsQml_VERSION_PATCH "1")

set(PROJECT_VERSION "${JsonSettingsQml_VERSION_MAJOR}.${JsonSettingsQml_VERSION_MINOR}.${JsonSettingsQml_VERSION_PATCH}")


include(FeatureSummary)
include(GNUInstallDirs)


find_package(Qt5 CONFIG REQUIRED COMPONENTS Qml Quick)



MACRO(HEADER_DIRECTORIES dir return_list)
FILE(GLOB_RECURSE new_list ${dir}/*.h)
SET(dir_list "")
FOREACH(file_path ${new_list})
GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
SET(dir_list ${dir_list} ${dir_path})
ENDFOREACH()
LIST(REMOVE_DUPLICATES dir_list)
SET(${return_list} ${dir_list})
ENDMACRO()



file(GLOB_RECURSE APP_HEADERS
    src/*.h
    )

file(GLOB_RECURSE APP_SOURCES
    src/*.cpp
    )

set(OTHER_FILES qmldir plugins.qmltypes)

HEADER_DIRECTORIES("src" header_dir_list)
include_directories(${header_dir_list})

#qt5_add_resources(PLUGIN_RESOURCES ${CMAKE_CURRENT_LIST_DIR}/JsonSettingsQml.qrc)

add_library(
    JsonSettingsQml
    SHARED

    ${APP_HEADERS}
    ${APP_SOURCES}
  #  ${OTHER_FILES}

    ${PLUGIN_RESOURCES}     # Plugin resources file
    )


target_compile_features(
    JsonSettingsQml
    PRIVATE
    cxx_auto_type
    cxx_generic_lambdas
    )

target_link_libraries(
    JsonSettingsQml
    PUBLIC
    Qt5::Quick
    )


target_include_directories(JsonSettingsQml
    PUBLIC
    $<INSTALL_INTERFACE:include/JsonSettingsQml>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${header_dir_list}
    )

#set target Version
set_target_properties(JsonSettingsQml PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(JsonSettingsQml PROPERTIES SOVERSION ${JsonSettingsQml_VERSION_MAJOR})

#generate export header
include(GenerateExportHeader)
generate_export_header(JsonSettingsQml)

#install export header
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/jsonsettingsqml_export.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/JsonSettingsQml
    )


# install library
install(TARGETS JsonSettingsQml
    EXPORT JsonSettingsQmlExport
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )



# configure *ConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    JsonSettingsQmlConfigVersion.cmake
    VERSION ${PACKAGE_VERSION}
    COMPATIBILITY SameMajorVersion
    )


# configure *Config.cmake
configure_file(JsonSettingsQmlConfig.cmake.in JsonSettingsQmlConfig.cmake @ONLY)


# install *Config(Version).cmake
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/JsonSettingsQmlConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/JsonSettingsQmlConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/JsonSettingsQml
    )

# install targets cmake-files
install(EXPORT JsonSettingsQmlExport
    FILE JsonSettingsQmlTargets.cmake
    NAMESPACE ZeraQml::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/JsonSettingsQml
    )

# install public headers
install(
    FILES ${APP_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/JsonSettingsQml
    )


feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
