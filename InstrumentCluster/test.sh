#!/bin/bash
#

docker pull sejokim/qt_cross:latest

docker run --rm --platform linux/arm64 -v .:/project -w /project sejokim/qt_cross:latest /bin/bash -c "
          mkdir -p build && \
          find /project -mindepth 1 -maxdepth 1 ! -name build -exec cp -r {} build/ \; && \
          echo 'Contents of /project/build after copy:' && \
          ls -la /project/build && \
          echo 'Checking for CMakeLists.txt in build directory:' && \
          ls -l /project/build/CMakeLists.txt && \
          cd build && \
          cmake . && \
          make && \
          cp InstrumentCluster /project/
          ldd InstrumentCluster
          "