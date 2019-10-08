#!/bin/sh

cd ./lib
sudo apt-get update
unzip ./irrlicht-1.8.4.zip
sudo apt-get install build-essential
sudo apt-get install freeglut3 freeglut3-dev freeglut3-dbg
sudo apt-get install xserver-xorg-dev x11proto-xf86vidmode-dev libxxf86vm-dev mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev libxext-dev libxcursor-dev
cd ./irrlicht-1.8.4/source/Irrlicht
make NDEBUG=1
cd ../../
sudo cp -r include/* /usr/local/include/
sudo cp lib/Linux/libIrrlicht.a /usr/local/lib
cd ..
rm -rf irrlicht-1.8.4
cd ../
