#!/bin/bash
apt-get update
apt-get -y upgrade 
apt-get -y install g++ git python3 python3-pip libgtest-dev
# todo: uncomment after issue resolved in CI
# Serialization libraries (JSON for string, boost for binary)
pip install cget
cget install https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz
cget install https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.gz

# Install Go
FILENAME=go1.21.6.linux-amd64.tar.gz
wget https://go.dev/dl/$FILENAME 
# Remove old directory if exists, and then untar
sudo rm -rf /usr/local/go && sudo tar -xvf $FILENAME -C /usr/local
echo 'export PATH=$PATH:/usr/local/go/bin' | sudo tee -a /etc/profile && source /etc/profile
rm $FILENAME
