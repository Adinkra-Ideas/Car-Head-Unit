cmake_minimum_required(VERSION 3.14)

project(instrument-cluster VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Quick SerialBus)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Quick SerialBus)

set(PROJECT_SOURCES
        src/main.cpp
        src/qml.qrc
        src/CANBusReader.h src/CANBusReader.cpp
        src/Speedometer.h src/Speedometer.cpp
        src/BatteryIcon.hpp src/BatteryIcon.cpp
        # src/ActiveGear.hpp src/ActiveGear.cpp
        # src/INA219.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(InstrumentCluster
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET InstrumentCluster APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(InstrumentCluster SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(InstrumentCluster
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_options(InstrumentCluster PUBLIC -fPIC)
target_link_options(InstrumentCluster PUBLIC -L./drivers -Wl,-rpath=.)

target_link_libraries(InstrumentCluster
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::SerialBus
  # /*ina219*/
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.InstrumentCluster)
endif()
set_target_properties(InstrumentCluster PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS InstrumentCluster
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(InstrumentCluster)
    qt_finalize_executable(InstrumentCluster)
endif()

#-I/usr/include/aarch64-linux-gnu/qt5 -I/usr/include/aarch64-linux-gnu/qt5/QtWidgets -I/usr/include/aarch64-linux-gnu/qt5/QtGui -I/usr/include/aarch64-linux-gnu/qt5/QtSerialBus -I/usr/include/aarch64-linux-gnu/qt5/QtCore -I. -I. -I/usr/lib/aarch64-linux-gnu/qt5/mkspecs/linux-aarch64-gnu-g++

