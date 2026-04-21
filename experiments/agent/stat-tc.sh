#!/bin/bash

LLM="$1"
PROJECT_FOLDER="$2"

if [ "$LLM" = "claude" ]; then
    BASE="claude-proj"
elif [ "$LLM" = "codex" ]; then
    BASE="codex-proj"
fi

ROOT="./$BASE/$PROJECT_FOLDER"
RESULTS_DIR="$ROOT/results"
TEST_DIR="$ROOT/test_files"

total=0
compile_fail=0
run_fail=0
pass=0

for f in "$TEST_DIR"/test_*.cpp; do
    name=$(basename "$f" .cpp)
    total=$((total + 1))
    echo "$ROOT/repair/$name/$name" 

    if [ ! -f "$ROOT/repair/build/$name/$name" ]; then
        compile_fail=$((compile_fail + 1))
        echo "[COMPILE FAIL] $name"
        continue
    fi

    result_file="$RESULTS_DIR/logs/${name}_result.txt"
    if [ ! -f "$result_file" ]; then
        run_fail=$((run_fail + 1))
        echo "[NO RESULT]    $name"
    elif grep -q "FAILED" "$result_file"; then
        run_fail=$((run_fail + 1))
        echo "[TEST FAIL]    $name"
    else
        pass=$((pass + 1))
        echo "[PASS]         $name"
    fi
done

echo ""
echo "=============================="
echo " 📊 테스트 통계"
echo "=============================="
echo " 전체 테스트  : $total"
echo " 컴파일 실패  : $compile_fail"
echo " 실행 실패    : $run_fail"
echo " 통과         : $pass"
echo "=============================="