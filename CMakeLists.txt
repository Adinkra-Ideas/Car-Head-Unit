cmake_minimum_required(VERSION 3.16)

project(head_unit VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Multimedia
    Quick
    Qml
    Core
    QuickControls2
    SpatialAudio
)

set(C src_C)
set(CPP src_CPP)
set(QML src_QML)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(apphead_unit
    ${CPP}/main.cpp
)

qt_add_qml_module(apphead_unit
    URI head_unit
    VERSION 1.0
    QML_FILES
        ${QML}/Main.qml
        QML_FILES ${QML}/Dinkplay.qml
        QML_FILES ${QML}/TopControls.qml
        QML_FILES ${QML}/Playing.qml
        QML_FILES ${QML}/Audio.qml
        QML_FILES ${QML}/Settings.qml
        QML_FILES ${QML}/MediaControls.qml
        SOURCES
        ${CPP}/GearWorker.hpp ${CPP}/GearWorker.cpp
        ${CPP}/Gear.hpp ${CPP}/Gear.cpp
        ${CPP}/Props.hpp ${CPP}/Props.cpp
        ${CPP}/Car.hpp ${CPP}/Car.cpp
        ${CPP}/Steering.hpp ${CPP}/Steering.cpp
        ${CPP}/SteeringWorker.hpp ${CPP}/SteeringWorker.cpp
        ${CPP}/MediaDirectory.hpp ${CPP}/MediaDirectory.cpp
    RESOURCES
        ${QML}/images/HU_logo.gif
        ${QML}/images/cameraView.gif
        ${QML}/images/selected_gear.gif
        ${QML}/images/home.png
        ${QML}/images/music.png
        ${QML}/images/boardBg2.png
        ${QML}/images/musicIco/musicSpin.gif
        ${QML}/images/musicIco/artist.png
        ${QML}/images/musicIco/playing.png
        ${QML}/images/musicIco/playing_white.png
        ${QML}/images/musicIco/audio.png
        ${QML}/images/musicIco/audio_white.png
        ${QML}/images/musicIco/add.png
        ${QML}/images/musicIco/minimize.png
        ${QML}/images/musicIco/minimize_w.png
        ${QML}/images/musicIco/rand.png
        ${QML}/images/musicIco/rand_white.png
        ${QML}/images/musicIco/next.png
        ${QML}/images/musicIco/pause.png
        ${QML}/images/musicIco/play.png
        ${QML}/images/musicIco/prev.png
        ${QML}/images/musicIco/loop.png
        ${QML}/images/musicIco/loop1.png
        ${QML}/images/musicIco/loop2.png
        ${QML}/images/musicIco/screen_w.png
        ${QML}/images/musicIco/screen.png
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apphead_unit PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apphead_unit
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# target_compile_options(apphead_unit PUBLIC -fPIC)
# target_link_options(apphead_unit BEFORE PUBLIC -L../${C} -Wl,-rpath=../${C})

target_link_libraries(apphead_unit PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::Multimedia
    Qt6::Core
    Qt6::QuickControls2
    Qt6::SpatialAudio
    # aptc apsc
)

include(GNUInstallDirs)
install(TARGETS apphead_unit
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
