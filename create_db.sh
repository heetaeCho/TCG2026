#!/bin/bash
#
./build/JsonConfig.exe $1
#./build/NewCreateDB.exe ./TestProjects/leveldb/db/builder.cc
./build/NewCreateDB.exe $1
