#!/bin/bash

THIS_DIR=$(pwd)
WEB_DIR=$THIS_DIR/web

rm -rf build
mkdir build && cd $_
emcmake cmake ..
emmake make -j12

rm -rf $WEB_DIR/*.js $WEB_DIR/*.wasm
cp *.js *.wasm $WEB_DIR