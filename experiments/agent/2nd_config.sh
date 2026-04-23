#!/bin/bash

if [ "$1" = "leveldb" ]; then
    sudo apt install -y libpfm4-dev

elif [ "$1" = "Catch2" ]; then
	sudo apt install -y libbrotli-dev

elif [ "$1" = "glomap" ]; then
    sudo apt install -y libeigen3-dev libceres-dev libboost-all-dev libomp-20-dev libgl-dev libglu1-mesa-dev freeglut3-dev libcgal-dev libmetis-dev libfreeimage-dev

elif [ "$1" = "ninja" ]; then
	sudo apt install -y libicu-dev

elif [ "$1" = "exiv2" ]; then
	sudo apt install -y libexpat1-dev

elif [ "$1" = "poppler" ]; then
	sudo apt install -y libfreetype6-dev libfontconfig1-dev libnss3-dev libtiff-dev qtbase5-dev qt5-qmake libopenjp2-7-dev liblcms2-dev libcurl4-openssl-dev libpoppler-glib-dev libglib2.0-dev

fi

