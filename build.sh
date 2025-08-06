#!/bin/bash
set -e
cd /app/SDL
rm -rf build
mkdir build
cd build
cmake .. -DSDL_OPENGL=ON -DSDL_VIDEO_X11=ON
make
cd /app
make clean
make
LD_LIBRARY_PATH=/app/SDL/build xvfb-run ./engine > engine_run.log 2>&1 &
sleep 5
kill %1
