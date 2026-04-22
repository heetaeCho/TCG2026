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
MAX_RETRY=2

total=0
compile_fail=0
run_fail=0
pass=0
pass_retry0=0
pass_retry1=0
pass_retry2=0

for f in "$TEST_DIR"/test_*.cpp; do
    name=$(basename "$f" .cpp)
    total=$((total + 1))

    if [ ! -f "$ROOT/repair/build/$name/$name" ]; then
        compile_fail=$((compile_fail + 1))
        echo "[COMPILE FAIL] $name"
        continue
    fi

    result_file=""
    result_retry=-1
    for i in $(seq $MAX_RETRY -1 0); do
        candidate="$RESULTS_DIR/logs/${name}_result_retry#${i}.txt"
        if [ -f "$candidate" ]; then
            result_file="$candidate"
            result_retry=$i
            break
        fi
    done

    if [ -z "$result_file" ]; then
        run_fail=$((run_fail + 1))
        echo "[NO RESULT]    $name"
    elif grep -q "FAILED" "$result_file"; then
        run_fail=$((run_fail + 1))
        echo "[TEST FAIL]    $name"
    else
        pass=$((pass + 1))
        if [ "$result_retry" -eq 0 ]; then
            pass_retry0=$((pass_retry0 + 1))
        elif [ "$result_retry" -eq 1 ]; then
            pass_retry1=$((pass_retry1 + 1))
        elif [ "$result_retry" -eq 2 ]; then
            pass_retry2=$((pass_retry2 + 1))
        fi
        echo "[PASS]         $name (retry#$result_retry)"
    fi
done

echo ""
echo "=============================="
echo " 📊 테스트 통계"
echo "=============================="
echo " 전체 테스트       : $total"
echo " 컴파일 실패       : $compile_fail"
echo " 실행 실패         : $run_fail"
echo " 통과 (수정 없음)  : $pass_retry0"
echo " 통과 (1회 수정)   : $pass_retry1"
echo " 통과 (2회 수정)   : $pass_retry2"
echo " 통과 합계         : $pass"
echo "=============================="