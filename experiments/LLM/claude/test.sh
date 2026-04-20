compile_and_run() {
  local src="$1"
  local name="$2"

  # 컴파일
  $COMPILER "$src" "$LIB" \
    -I"$INCLUDE_PROJ" -I"$INCLUDE_BUILD" \
    -lgtest -lgtest_main -lgmock -lpthread \
    -o "$BIN_DIR/$name" \
    > "$LOG_DIR/${name}_compile.txt" 2>&1

  if [ $? -ne 0 ]; then
    echo "COMPILE_FAIL"
    return 1
  fi

  # 실행
  "$BIN_DIR/$name" > "$LOG_DIR/${name}_result.txt" 2>&1
  local exit_code=$?

  if grep -q "FAILED" "$LOG_DIR/${name}_result.txt"; then
    echo "TEST_FAIL"
    return 2
  fi

  echo "PASS"
  return 0
}

TEST_DIR="./01_JsonBox/test_files"
PROJ_DIR="/home/user/MyProjects/TCG2026/TestProjects/JsonBox"
LIB="$PROJ_DIR/build/libJsonBox.a"
INCLUDE_PROJ="$PROJ_DIR/include"
INCLUDE_BUILD="$PROJ_DIR/build"
RESULTS_DIR="./results"
BIN_DIR="$RESULTS_DIR/bin"
LOG_DIR="$RESULTS_DIR/logs"
FIX_DIR="$RESULTS_DIR/fix_logs"

COMPILER="clang++-20"
MAX_RETRY=2  # 수정 후 재시도 횟수

mkdir -p "$BIN_DIR" "$LOG_DIR" "$FIX_DIR"

for src in "$TEST_DIR"/test_*.cpp; do
  echo "$src"
  name=$(basename "$src" .cpp)
  compile_and_run "$src" "$name"
done
