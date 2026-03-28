// File: ./TestProjects/ninja/tests/warning_test_130.cc

#include "util.h"

#include <string>
#include "gtest/gtest.h"

class WarningTest_130 : public ::testing::Test {};

// Verify that a simple message is printed with the expected prefix and newline.
TEST_F(WarningTest_130, SimpleMessagePrintedWithPrefixAndNewline_130) {
  testing::internal::CaptureStderr();
  Warning("simple message");
  std::string output = testing::internal::GetCapturedStderr();

  EXPECT_EQ("ninja: warning: simple message\n", output);
}

// Verify that format arguments are correctly applied by the variadic wrapper.
TEST_F(WarningTest_130, FormattedMessageUsesArguments_130) {
  testing::internal::CaptureStderr();
  Warning("value=%d %s", 42, "items");
  std::string output = testing::internal::GetCapturedStderr();

  EXPECT_EQ("ninja: warning: value=42 items\n", output);
}

// Verify that multiple calls to Warning result in multiple lines of output.
TEST_F(WarningTest_130, MultipleCallsProduceMultipleLines_130) {
  testing::internal::CaptureStderr();
  Warning("first");
  Warning("second %d", 2);
  std::string output = testing::internal::GetCapturedStderr();

  EXPECT_EQ("ninja: warning: first\n"
            "ninja: warning: second 2\n",
            output);
}
