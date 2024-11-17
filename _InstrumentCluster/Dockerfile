FROM balenalib/raspberrypi4-64-debian:latest

RUN apt-get update && apt-get install -y \
    build-essential \
    qt5-qmake \
    qtbase5-dev \
    qtbase5-dev-tools \
    qtdeclarative5-dev \
    qttools5-dev-tools \
    qtchooser \
    libqt5opengl5-dev \
    libqt5svg5-dev \
    libqt5multimedia5-plugins \
    libqt5multimedia5 \
    libqt5multimediawidgets5 \
    libqt5x11extras5-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libgl1-mesa-dev \
    libglu1-mesa-dev \
    qtmultimedia5-dev \
    qtbase5-private-dev \
    cmake \
    libqt5serialbus5-dev \
    libqt5serialbus5 \
    qml-module-qtquick-shapes \
    qml-module-qtquick-controls2 \
    qml-module-qtquick-layouts \
    libqt5quick5 \
    libqt5qml5 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /project

# set environment variables
ENV QT_QPA_PLATFORM=offscreen
ENV QML2_IMPORT_PATH=/usr/lib/aarch64-linux-gnu/qt5/qml
ENV QT_PLUGIN_PATH=/usr/lib/aarch64-linux-gnu/qt5/plugins