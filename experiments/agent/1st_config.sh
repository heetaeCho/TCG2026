#!/bin/bash
PYTHON=python3

LLM="$1"
PROJ_DIR="$2"
PROJECT="$3"

if [ "$4" = "My" ]; then
    path="$HOME/MyProjects/TCG2026"
else
    path="$HOME/TCG2026"
fi

echo "$path"

if [ -n "$1" ] && [ -n "$2" ]; then
    mkdir -p "$1/$2"
    if [ ! -e "./$1/TCG2026" ]; then
        ln -s "$path" "./$1/TCG2026"
    fi
else
    echo "ex: bash 1st_config.sh claude-proj json-box JsonBox"
    echo "ex: bash 1st_config.sh codex-proj json-box JsonBox"
    exit 1
fi

$PYTHON target_copy.py --LLM "claude" --project_folder_name "$PROJ_DIR" --project "$PROJECT" > /dev/null 2>&1
if [ "$3" = "JsonBox" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi
elif [ "$3" = "re2" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi
elif [ "$3" = "leveldb" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi

elif [ "$3" = "Catch2" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi

elif [ "$3" = "glomap" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi

elif [ "$3" = "ninja" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi

elif [ "$3" = "tinyxml2" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi

elif [ "$3" = "yaml-cpp" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi

elif [ "$3" = "exiv2" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi
elif [ "$3" = "poppler" ]; then
    if [ ! -e "./$1/$2/$3" ]; then
        ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    fi
fi
