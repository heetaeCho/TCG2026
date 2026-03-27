#!/bin/bash
#
./build/JsonConfig.exe $1
# #./build/NewCreateDB.exe ./TestProjects/leveldb/db/builder.cc
export PYTHONPATH=src
python3 src/application/main_prompt_creator.py
