#!/bin/bash

./build/JsonConfig.exe $1
#./build/NewCreateDB.exe ./TestProjects/leveldb/db/builder.cc
./build/NewTraceDB.exe $1
