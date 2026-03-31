#include "gtest/gtest.h"
#include <string>
#include <cstdarg>

// Declaration of the Warning function from util.h
void Warning(const char* msg, ...);

// Since Warning typically prints to stderr, we can test that it doesn't crash
// and handles various input scenarios. We capture stderr to verify output.

class WarningTest_130 : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Warning with a simple message does not crash
TEST_F(WarningTest_130, SimpleMessage_130) {
  EXPECT_NO_FATAL_FAILURE(Warning("simple warning message"));
}

// Test that Warning with format specifiers works correctly
TEST_F(WarningTest_130, FormattedMessageWithString_130) {
  EXPECT_NO_FATAL_FAILURE(Warning("warning: %s", "something went wrong"));
}

// Test that Warning with integer format specifier works
TEST_F(WarningTest_130, FormattedMessageWithInt_130) {
  EXPECT_NO_FATAL_FAILURE(Warning("warning code: %d", 42));
}

// Test that Warning with multiple format specifiers works
TEST_F(WarningTest_130, FormattedMessageWithMultipleArgs_130) {
  EXPECT_NO_FATAL_FAILURE(Warning("%s: %d items, ratio %.2f", "test", 10, 3.14));
}

// Test that Warning with an empty string does not crash
TEST_F(WarningTest_130, EmptyMessage_130) {
  EXPECT_NO_FATAL_FAILURE(Warning(""));
}

// Test that Warning with special characters does not crash
TEST_F(WarningTest_130, SpecialCharactersMessage_130) {
  EXPECT_NO_FATAL_FAILURE(Warning("warning: path/to/file\twith\nnewline"));
}

// Test that Warning with a long message does not crash
TEST_F(WarningTest_130, LongMessage_130) {
  std::string long_msg(1000, 'a');
  EXPECT_NO_FATAL_FAILURE(Warning("%s", long_msg.c_str()));
}

// Test that Warning with percent literal works
TEST_F(WarningTest_130, PercentLiteral_130) {
  EXPECT_NO_FATAL_FAILURE(Warning("100%% complete"));
}

// Test that Warning with zero integer argument works
TEST_F(WarningTest_130, ZeroIntegerArg_130) {
  EXPECT_NO_FATAL_FAILURE(Warning("count: %d", 0));
}

// Test that Warning with negative integer argument works
TEST_F(WarningTest_130, NegativeIntegerArg_130) {
  EXPECT_NO_FATAL_FAILURE(Warning("error code: %d", -1));
}

// Test that Warning with null string argument doesn't crash (implementation dependent)
// Some implementations handle NULL %s gracefully
TEST_F(WarningTest_130, NullStringArg_130) {
  // This test checks the function doesn't cause a fatal crash with typical usage
  // Note: passing NULL for %s is technically undefined behavior in C/C++,
  // but many implementations handle it. We skip this if it's too risky.
  // EXPECT_NO_FATAL_FAILURE(Warning("value: %s", (const char*)nullptr));
  // Instead, test with empty string
  EXPECT_NO_FATAL_FAILURE(Warning("value: %s", ""));
}

// Test Warning outputs to stderr by capturing it
TEST_F(WarningTest_130, OutputContainsWarningPrefix_130) {
  testing::internal::CaptureStderr();
  Warning("test output message");
  std::string output = testing::internal::GetCapturedStderr();
  // Warning typically prefixes with "ninja: warning: "
  EXPECT_FALSE(output.empty());
  EXPECT_NE(output.find("warning"), std::string::npos);
}

// Test Warning output contains the formatted message
TEST_F(WarningTest_130, OutputContainsFormattedContent_130) {
  testing::internal::CaptureStderr();
  Warning("specific content %d", 999);
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_NE(output.find("specific content 999"), std::string::npos);
}

// Test Warning output ends with newline
TEST_F(WarningTest_130, OutputEndsWithNewline_130) {
  testing::internal::CaptureStderr();
  Warning("newline test");
  std::string output = testing::internal::GetCapturedStderr();
  ASSERT_FALSE(output.empty());
  EXPECT_EQ(output.back(), '\n');
}
