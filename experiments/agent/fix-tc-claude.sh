#!/bin/bash
# =============================================
# JsonBox 테스트 자동 수정 파이프라인
# =============================================
PYTHON=python3

# 입력 인자
LLM="$1"
PROJECT="$2"
PROJ_DIR="$3"
TEST_FILE="$4"

# BASE 설정
BASE="claude-proj"

ROOT="./$BASE/$PROJ_DIR"

TEST_DIR="$ROOT/test_files"
RESULTS_DIR="$ROOT/results"
LOG_DIR="$RESULTS_DIR/logs"
FIX_DIR="$RESULTS_DIR/fix_logs"
MAX_RETRY=2  # 수정 후 재시도 횟수

mkdir -p "$LOG_DIR" "$FIX_DIR"

# =============================================
# 함수: 컴파일 + 실행
# =============================================
compile_and_run() {
    local src="$1"
    local name="$2"
    local retry="${3:-0}"  # 0이면 초기 실행

    $PYTHON build.py --LLM "$LLM" --project_folder_name "$PROJ_DIR" --project "$PROJECT" --test_file "$name.cpp" --retry "$retry" > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "COMPILE_FAIL"
        return 1
    fi

    $PYTHON execute.py --LLM "$LLM" --project_folder_name "$PROJ_DIR" --project "$PROJECT" --test_file "$name.cpp" --retry "$retry" > /dev/null 2>&1
    if grep -q "FAILED" "$LOG_DIR/${name}_result_retry#${retry}.txt"; then
        echo "TEST_FAIL"
        return 2
    fi

    echo "PASS"
    return 0
}
# =============================================
# 함수: Claude로 수정
# =============================================
fix_with_claude() {
    local src="$1"
    local name="$2"
    local status="$3"
    local retry="$4"
    local real_project_path="./$BASE/$PROJECT"

    echo "  [Claude] 분석 중..."

    local compile_log=""
    local result_log=""
    [ -f "$LOG_DIR/${name}_compile_retry#${retry}.txt" ] && compile_log=$(cat "$LOG_DIR/${name}_compile_retry#${retry}.txt")
    [ -f "$LOG_DIR/${name}_result_retry#${retry}.txt" ]  && result_log=$(cat "$LOG_DIR/${name}_result_retry#${retry}.txt")

    # 1단계: 계획 수립 (읽기 전용)
    local plan
    plan=$(claude -p \
        "## 역할
C++ 라이브러리 테스트 코드 수정 전문가

## 프로젝트 구조
- 프로젝트 루트: $real_project_path
- 테스트 파일: $src

## 실패 유형: $status

## 컴파일 로그
$compile_log

## 실행 결과 로그
$result_log

## 지시사항
1. 프로젝트 루트에서 헤더, 소스, CMakeLists.txt 등을 탐색해 API를 파악할 것
2. 테스트 파일을 읽어서 실패 원인을 파악할 것
3. 수정이 필요한 부분과 수정 방법을 구체적으로 작성할 것
4. 절대로 코드를 수정하지 말고 분석과 계획만 출력할 것" \
        --allowedTools "Read,Grep,Glob" \
        --max-turns 5 \
        --output-format json 2>/dev/null | jq -r '.result // "분석 실패"')

    echo "  [PLAN] $plan" | tee "$FIX_DIR/${name}_plan.txt"

    # 2단계: 수정 실행 (계획 기반)
    echo "  [Claude] 수정 중..."

    claude \
        "## 역할
C++ 라이브러리 테스트 코드 수정 전문가

## 프로젝트 루트
$real_project_path

## 수정 대상 파일
$src

## 수정 계획
$plan

## 제약 조건
- $src 파일만 수정할 것
- $real_project_path 하위 라이브러리 코드는 절대 수정 금지
- gtest 프레임워크 문법을 올바르게 사용할 것

## 작업
계획에 따라 테스트 파일을 수정하고, 수정한 내용을 요약해서 출력해" \
        --allowedTools "Read,Write,Edit" \
        --max-turns 10 \
        --dangerously-skip-permissions

    echo "  [Claude] 수정 완료"
}

# =============================================
# 메인 루프
# =============================================
total=0; pass=0; compile_fail=0; test_fail=0; fixed=0; fix_fail=0

run_one() {
    local src="$1"
    local name="$2"

    total=$((total + 1))
    echo ""
    echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
    echo "▶ [$name]"

    status=$(compile_and_run "$src" "$name" 0)  # 초기

    if [ "$status" = "PASS" ]; then
        echo "  ✅ PASS"
        pass=$((pass + 1))
        return
    fi

    echo "  ❌ $status → Claude 수정 시작"
    [ "$status" = "COMPILE_FAIL" ] && compile_fail=$((compile_fail + 1))
    [ "$status" = "TEST_FAIL" ]    && test_fail=$((test_fail + 1))

    retry=0
    success=false
    while [ $retry -lt $MAX_RETRY ]; do
        retry=$((retry + 1))
        echo "  [시도 $retry/$MAX_RETRY]"

        fix_with_claude "$src" "$name" "$status" "$retry"

        if [ "$PROJECT" = "JsonBox" ]; then
            original_src="./$BASE/TCG2026/experiments/LLM/claude/01_JsonBox/test_files/${name}.cpp"
        elif [ "$PROJECT" = "glomap" ]; then
            original_src="./$BASE/TCG2026/experiments/LLM/claude/05_glomap/test_files/${name}.cpp"
        fi

        echo "$original_src" 
        echo "$src"

        if diff -q "$original_src" "$src" > /dev/null 2>&1; then
            echo "  ⚠️  파일 변경 없음"
        else
            echo "  📝 파일 변경됨"
        fi

        status=$(compile_and_run "$src" "$name" "$retry")
        if [ "$status" = "PASS" ]; then
            echo "  ✅ 수정 성공!"
            fixed=$((fixed + 1))
            success=true
            break
        fi
        echo "  ↩ 재시도 필요 ($status)"
    done

    $success || fix_fail=$((fix_fail + 1))
}

if [ -n "$TEST_FILE" ]; then
    name=$(basename "$TEST_FILE" .cpp)
    run_one "$TEST_DIR/$TEST_FILE" "$name"
else
    for src in "$TEST_DIR"/test_*.cpp; do
        name=$(basename "$src" .cpp)
        run_one "$src" "$name"
    done
fi

# =============================================
# 최종 통계
# =============================================
echo ""
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo " 📊 최종 결과"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo " 전체           : $total"
echo " ✅ 원래 통과   : $pass"
echo " 🔧 수정 후 통과: $fixed"
echo " ❌ 컴파일 실패 : $compile_fail"
echo " ❌ 테스트 실패 : $test_fail"
echo " 💀 수정 불가   : $fix_fail"
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
