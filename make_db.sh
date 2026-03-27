#!/bin/bash

#arr=("JsonBox" "re2" "leveldb" "Catch2" "glomap" "ninja" "tinyxml2" "yaml-cpp" "exiv2" "poppler")
arr=("exiv2" "poppler")
for project in "${arr[@]}"; do
    bash ./create_db.sh "$project"
    bash ./trace_db.sh "$project"
done
