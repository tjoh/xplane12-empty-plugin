#!/bin/sh

SRC_PATH=.
BUILD_PATH=build

XPLANE_PATH=~/X-Plane12/
PLUGINS_PATH=$XPLANE_PATH/Resources/plugins/

INSTALL_PATH=$PLUGINS_PATH

cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_PATH -DCMAKE_BUILD_TYPE=Release -B $BUILD_PATH -S $SRC_PATH
cmake --build $BUILD_PATH --target install
