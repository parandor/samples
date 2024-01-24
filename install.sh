#!/bin/bash
apt-get update
apt-get -y install g++ git
apt-get -y install python3
apt-get -y install python3-pip
apt-get -y install libgtest-dev
# todo: uncomment after issue resolved in CI
# Serialization libraries (JSON for string, boost for binary)
# pip install cget
# cget install https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz
# cget install https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.gz