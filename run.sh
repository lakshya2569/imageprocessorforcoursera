#!/bin/bash

echo "Building project..."

make

echo "Running processor..."

./image_processor \
data/input_images \
output

echo "Done."