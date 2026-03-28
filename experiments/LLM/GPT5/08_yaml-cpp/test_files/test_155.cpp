#include <gtest/gtest.h>
#include <sstream>
#include "scanner.h"

using namespace YAML;

class ScannerPeekTest_155 : public ::testing::Test {
protected:
  std::stringstream input;
};

/**
 * Normal operation:
 * peek() returns a reference and does not consume the token.
 */
TEST_F(ScannerPeekTest_155, PeekDoesNotConsumeToken_155) {
  input << "a";
  Scanner scanner(input);

  EXPECT_FALSE(scanner.empty());

  Token& firstPeek = scanner.peek();
  Token& secondPeek = scanner.peek();

  // Same token reference must be returned if pop() is not called
  EXPECT_EQ(&firstPeek, &secondPeek);
}

/**
 * Normal operation:
 * pop() advances the scanner so peek() returns a different token.
 */
TEST_F(ScannerPeekTest_155, PeekAfterPopReturnsNextToken_155) {
  input << "a b";
  Scanner scanner(input);

  Token& firstToken = scanner.peek();
  scanner.pop();

  Token& secondToken = scanner.peek();

  // After pop(), peek() must return a different token
  EXPECT_NE(&firstToken, &secondToken);
}

/**
 * Boundary condition:
 * peek() on a freshly constructed scanner with input should succeed.
 */
TEST_F(ScannerPeekTest_155, PeekOnFreshScannerWithInput_155) {
  input << "key: value";
  Scanner scanner(input);

  EXPECT_FALSE(scanner.empty());

  // Should not throw or crash
  EXPECT_NO_THROW({
    scanner.peek();
  });
}

/**
 * Exceptional case:
 * peek() on an empty scanner triggers assertion failure.
 */
TEST_F(ScannerPeekTest_155, PeekOnEmptyScannerCausesDeath_155) {
  input << "";
  Scanner scanner(input);

  // Ensure scanner reports empty state
  EXPECT_TRUE(scanner.empty());

  // peek() asserts that token queue is not empty
  EXPECT_DEATH(
    {
      scanner.peek();
    },
    ""
  );
}
