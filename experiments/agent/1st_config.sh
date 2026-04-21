#!/bin/bash

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

if [ "$3" = "JsonBox" ]; then
    ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    cp -r "./$1/TCG2026/experiments/LLM/claude/01_JsonBox/test_files" "./$1/$2/"
elif [ "$3" = "glomap" ]; then
    ln -s "$path/TestProjects/$3" "./$1/$2/$3"
    cp -r "./$1/TCG2026/experiments/LLM/claude/05_glomap/test_files" "./$1/$2/"
fi