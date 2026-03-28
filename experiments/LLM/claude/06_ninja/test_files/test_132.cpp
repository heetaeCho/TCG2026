#include <gtest/gtest.h>
#include <cstdarg>
#include <string>
#include <cstdio>

// Forward declaration of the function under test
void Info(const char* msg, ...);

// Since Info is a logging/output function, we test that it doesn't crash
// with various inputs. We can't easily capture its output without knowing
// the internal implementation, but we can verify it handles different
// argument patterns without crashing.

class InfoTest_132 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Normal operation with a simple string message (no format specifiers)
TEST_F(InfoTest_132, SimpleMessage_132) {
  EXPECT_NO_THROW(Info("simple message"));
}

// Test: Normal operation with a format string and an integer argument
TEST_F(InfoTest_132, FormatWithInteger_132) {
  EXPECT_NO_THROW(Info("value: %d", 42));
}

// Test: Normal operation with a format string and a string argument
TEST_F(InfoTest_132, FormatWithString_132) {
  EXPECT_NO_THROW(Info("name: %s", "test"));
}

// Test: Normal operation with multiple variadic arguments
TEST_F(InfoTest_132, MultipleArguments_132) {
  EXPECT_NO_THROW(Info("%s: %d, %f", "test", 123, 3.14));
}

// Test: Empty string message
TEST_F(InfoTest_132, EmptyMessage_132) {
  EXPECT_NO_THROW(Info(""));
}

// Test: Message with percent literal
TEST_F(InfoTest_132, PercentLiteral_132) {
  EXPECT_NO_THROW(Info("100%% done"));
}

// Test: Message with special characters
TEST_F(InfoTest_132, SpecialCharacters_132) {
  EXPECT_NO_THROW(Info("line1\nline2\ttab"));
}

// Test: Message with zero integer argument
TEST_F(InfoTest_132, ZeroIntegerArgument_132) {
  EXPECT_NO_THROW(Info("count: %d", 0));
}

// Test: Message with negative integer argument
TEST_F(InfoTest_132, NegativeIntegerArgument_132) {
  EXPECT_NO_THROW(Info("offset: %d", -1));
}

// Test: Message with large integer argument
TEST_F(InfoTest_132, LargeIntegerArgument_132) {
  EXPECT_NO_THROW(Info("big: %ld", 9999999999L));
}

// Test: Message with empty string argument
TEST_F(InfoTest_132, EmptyStringArgument_132) {
  EXPECT_NO_THROW(Info("name: '%s'", ""));
}

// Test: Message with floating point argument
TEST_F(InfoTest_132, FloatingPointArgument_132) {
  EXPECT_NO_THROW(Info("pi: %f", 3.14159));
}

// Test: Message with character argument
TEST_F(InfoTest_132, CharArgument_132) {
  EXPECT_NO_THROW(Info("char: %c", 'A'));
}

// Test: Message with hex formatting
TEST_F(InfoTest_132, HexFormat_132) {
  EXPECT_NO_THROW(Info("hex: 0x%x", 255));
}

// Test: Long message string
TEST_F(InfoTest_132, LongMessage_132) {
  std::string longMsg(500, 'a');
  EXPECT_NO_THROW(Info("%s", longMsg.c_str()));
}

// Test: No extra arguments (just format string with no specifiers)
TEST_F(InfoTest_132, NoExtraArguments_132) {
  EXPECT_NO_THROW(Info("no args here"));
}

// Test: Multiple string arguments
TEST_F(InfoTest_132, MultipleStringArguments_132) {
  EXPECT_NO_THROW(Info("%s %s %s", "hello", "world", "test"));
}
