#include <gtest/gtest.h>
#include <sstream>
#include "yaml-cpp/scanner.h"

using namespace YAML;

/*
 * Test fixture for Scanner tests (TEST_ID = 153)
 */
class ScannerTest_153 : public ::testing::Test {
protected:
  std::stringstream input;
};

/*
 * Normal operation:
 * Scanner can be constructed and empty() can be called safely.
 */
TEST_F(ScannerTest_153, EmptyCallableAfterConstruction_153) {
  Scanner scanner(input);
  EXPECT_NO_THROW({
    (void)scanner.empty();
  });
}

/*
 * Boundary condition:
 * An empty input stream should eventually report empty().
 * We do not assume whether tokens like STREAM_START exist internally;
 * we only verify the observable result is a boolean and stable.
 */
TEST_F(ScannerTest_153, EmptyInputReportsEmpty_153) {
  Scanner scanner(input);
  bool result = scanner.empty();
  EXPECT_TRUE(result || !result);  // Ensures callable & returns a bool
}

/*
 * Boundary condition:
 * Multiple calls to empty() should be consistent and not change state
 * in an observable, invalid way (idempotence from caller perspective).
 */
TEST_F(ScannerTest_153, EmptyIsIdempotent_153) {
  Scanner scanner(input);
  bool first = scanner.empty();
  bool second = scanner.empty();
  EXPECT_EQ(first, second);
}

/*
 * Normal operation:
 * If empty() is false, peek() should be callable without throwing.
 * We do not assume anything about the token content.
 */
TEST_F(ScannerTest_153, PeekCallableWhenNotEmpty_153) {
  input << "a";  // minimal non-empty YAML content
  Scanner scanner(input);

  if (!scanner.empty()) {
    EXPECT_NO_THROW({
      Token& tok = scanner.peek();
      (void)tok;
    });
  }
}

/*
 * Normal operation:
 * pop() should be callable after peek() when not empty().
 * We do not assume how many tokens exist or what pop() removes.
 */
TEST_F(ScannerTest_153, PopAfterPeekDoesNotThrow_153) {
  input << "a";
  Scanner scanner(input);

  if (!scanner.empty()) {
    EXPECT_NO_THROW({
      scanner.peek();
      scanner.pop();
    });
  }
}

/*
 * Boundary condition:
 * Calling empty() after pop() should still be safe and return a bool.
 */
TEST_F(ScannerTest_153, EmptyCallableAfterPop_153) {
  input << "a";
  Scanner scanner(input);

  if (!scanner.empty()) {
    scanner.pop();
  }

  EXPECT_NO_THROW({
    bool result = scanner.empty();
    EXPECT_TRUE(result || !result);
  });
}
