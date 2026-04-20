#!/bin/bash

if [ "$4" = "My" ]; then
    path="$HOME/MyProjects/TCG2026"
else
	path="$HOME/TCG2026"
fi

echo "$path"

if [ -n "$1" ] && [ -n "$2" ]; then
    mkdir "$1"
    cd "$1"
    mkdir "$2"
    ln -s "$path" "TCG2026"
else
    echo ex: bash 1st_config.sh claude-proj json-box JsonBox
    echo ex: bash 1st_config.sh codex-proj json-box JsonBox
fi

if [ "$3" = "JsonBox" ]; then
    ln -s "$path/TestProjects/$3" "./$2/$3"
    cp -r "TCG2026/experiments/LLM/claude/01_JsonBox/test_files" "./$2/"
elif [ "$3" = "glomap" ]; then
    ln -s "$path/TestProjects/$3" "./$2/$3"
    cp -r "TCG2026/experiments/LLM/claude/05_glomap/test_files" "./$2/"
fi
