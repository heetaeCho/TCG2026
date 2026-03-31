#include <gtest/gtest.h>
#include <string>
#include <cstdarg>

// Declaration of the Error function from util.h
void Error(const char* msg, ...);

// Note: Error() typically prints to stderr and/or calls exit(). 
// Since we're treating it as a black box, we test what we can observe.
// The Error function with varargs typically formats and outputs an error message,
// and may terminate the program. We need to test carefully.

// Test that Error can be called with a simple message (death test since Error likely exits)
TEST(ErrorTest_131, SimpleMessage_131) {
  EXPECT_DEATH(Error("simple error"), ".*simple error.*");
}

// Test that Error can be called with format string and arguments
TEST(ErrorTest_131, FormattedMessage_131) {
  EXPECT_DEATH(Error("error: %s", "details"), ".*error: details.*");
}

// Test that Error can be called with integer format arguments
TEST(ErrorTest_131, IntegerFormatArg_131) {
  EXPECT_DEATH(Error("error code: %d", 42), ".*error code: 42.*");
}

// Test that Error can be called with multiple format arguments
TEST(ErrorTest_131, MultipleFormatArgs_131) {
  EXPECT_DEATH(Error("%s failed with code %d", "operation", -1), 
               ".*operation failed with code -1.*");
}

// Test that Error handles empty string
TEST(ErrorTest_131, EmptyMessage_131) {
  EXPECT_DEATH(Error(""), ".*");
}

// Test with a longer formatted message
TEST(ErrorTest_131, LongFormattedMessage_131) {
  EXPECT_DEATH(Error("file '%s' not found at line %d in %s", 
                     "test.txt", 100, "main.cpp"),
               ".*test.txt.*");
}

// Test with special characters in format string
TEST(ErrorTest_131, SpecialCharactersInMessage_131) {
  EXPECT_DEATH(Error("path: %s", "/usr/local/bin"), ".*path:.*");
}

// Test with zero as integer argument
TEST(ErrorTest_131, ZeroIntArg_131) {
  EXPECT_DEATH(Error("count: %d", 0), ".*count: 0.*");
}
