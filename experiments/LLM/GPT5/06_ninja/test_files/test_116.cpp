// File name suggestion: ./TestProjects/ninja/tests/print_json_string_test_116.cc

#include <gtest/gtest.h>

#include <string>

#include "json.h"  // Declares EncodeJSONString and PrintJSONString

using std::string;

class PrintJSONStringTest_116 : public ::testing::Test {};

// Verifies that an empty input is passed through EncodeJSONString and
// the result is written to stdout without extra characters.
TEST_F(PrintJSONStringTest_116, EmptyString_WritesEncodedJsonToStdout_116) {
  const string input = "";

  // Expected is whatever EncodeJSONString produces for the same input.
  const string expected = EncodeJSONString(input);

  testing::internal::CaptureStdout();
  PrintJSONString(input);
  const string captured = testing::internal::GetCapturedStdout();

  EXPECT_EQ(captured, expected);
}

// Verifies that a simple, non-empty input string is correctly written to stdout
// exactly as returned by EncodeJSONString.
TEST_F(PrintJSONStringTest_116, SimpleText_WritesEncodedJsonToStdout_116) {
  const string input = "hello world";

  const string expected = EncodeJSONString(input);

  testing::internal::CaptureStdout();
  PrintJSONString(input);
  const string captured = testing::internal::GetCapturedStdout();

  EXPECT_EQ(captured, expected);
}

// Verifies that strings containing special characters (quotes, backslashes,
// control characters, etc.) are forwarded correctly to stdout via EncodeJSONString.
TEST_F(PrintJSONStringTest_116, SpecialCharacters_WritesEncodedJsonToStdout_116) {
  const string input = "line1\nline2\t\"quote\"\\backslash";

  const string expected = EncodeJSONString(input);

  testing::internal::CaptureStdout();
  PrintJSONString(input);
  const string captured = testing::internal::GetCapturedStdout();

  EXPECT_EQ(captured, expected);
}

// Verifies behavior with a relatively long input (boundary-ish case for size).
// Ensures the entire encoded string is written and no truncation occurs.
TEST_F(PrintJSONStringTest_116, LongString_WritesFullEncodedJsonToStdout_116) {
  // Build a long string.
  string input;
  input.reserve(4096);
  for (int i = 0; i < 4096; ++i) {
    input.push_back('a' + (i % 26));
  }

  const string expected = EncodeJSONString(input);

  testing::internal::CaptureStdout();
  PrintJSONString(input);
  const string captured = testing::internal::GetCapturedStdout();

  EXPECT_EQ(captured, expected);
}

// Verifies that multiple calls to PrintJSONString append to stdout in order,
// each contributing exactly its own EncodeJSONString output.
TEST_F(PrintJSONStringTest_116, MultipleCalls_OutputsAreAppendedInOrder_116) {
  const string input1 = "first";
  const string input2 = "second\nline";

  const string expected1 = EncodeJSONString(input1);
  const string expected2 = EncodeJSONString(input2);

  testing::internal::CaptureStdout();
  PrintJSONString(input1);
  PrintJSONString(input2);
  const string captured = testing::internal::GetCapturedStdout();

  EXPECT_EQ(captured, expected1 + expected2);
}
