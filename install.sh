#!/bin/bash

apt update
apt -y install g++ git
# sudo apt -y install python3
# sudo apt -y install python3-pip
# sudo apt -y install libgtest-dev
# todo: uncomment after issue resolved in CI
# Serialization libraries (JSON for string, boost for binary)
# pip install cget
# cget install https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz
# cget install https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.gz