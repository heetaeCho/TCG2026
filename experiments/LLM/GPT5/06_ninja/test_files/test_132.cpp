// File: ./TestProjects/ninja/src/util_info_test.cc

#include "util.h"

#include <string>

#include "gtest/gtest.h"

using std::string;

// The TEST_ID is 132

TEST(InfoTest_132, PrintsSimpleMessageWithPrefixAndNewline_132) {
  testing::internal::CaptureStdout();
  Info("hello");
  string output = testing::internal::GetCapturedStdout();

  // Should contain the prefix and message.
  EXPECT_NE(output.find("ninja: hello"), string::npos);

  // Should end with a newline.
  ASSERT_FALSE(output.empty());
  EXPECT_EQ('\n', output.back());
}

TEST(InfoTest_132, FormatsSingleIntegerArgument_132) {
  testing::internal::CaptureStdout();
  Info("value=%d", 42);
  string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("ninja: value=42"), string::npos);
  ASSERT_FALSE(output.empty());
  EXPECT_EQ('\n', output.back());
}

TEST(InfoTest_132, FormatsMultipleArguments_132) {
  testing::internal::CaptureStdout();
  Info("coords (%d, %d, %s)", 10, 20, "ok");
  string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("ninja: coords (10, 20, ok)"), string::npos);
  ASSERT_FALSE(output.empty());
  EXPECT_EQ('\n', output.back());
}

TEST(InfoTest_132, HandlesEscapedPercentSign_132) {
  testing::internal::CaptureStdout();
  Info("progress %d%%", 75);
  string output = testing::internal::GetCapturedStdout();

  // Verify that the percent sign was printed correctly.
  EXPECT_NE(output.find("ninja: progress 75%"), string::npos);
  ASSERT_FALSE(output.empty());
  EXPECT_EQ('\n', output.back());
}

TEST(InfoTest_132, MultipleCallsProduceMultipleLinesInOrder_132) {
  testing::internal::CaptureStdout();
  Info("first");
  Info("second");
  string output = testing::internal::GetCapturedStdout();

  size_t first_pos = output.find("ninja: first");
  size_t second_pos = output.find("ninja: second");

  EXPECT_NE(first_pos, string::npos);
  EXPECT_NE(second_pos, string::npos);
  EXPECT_LT(first_pos, second_pos);  // Ensure ordering is preserved.

  ASSERT_FALSE(output.empty());
  EXPECT_EQ('\n', output.back());
}
