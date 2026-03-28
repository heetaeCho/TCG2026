// File: util_strip_ansi_escape_codes_test.cc

#include "util.h"

#include "gtest/gtest.h"

#include <string>

using std::string;

namespace {

class StripAnsiEscapeCodesTest_146 : public ::testing::Test {};

// Normal operation: input without any escape codes is returned unchanged.
TEST_F(StripAnsiEscapeCodesTest_146, NoEscapeCodesAreUnchanged_146) {
  EXPECT_EQ(StripAnsiEscapeCodes(string()), "");
  EXPECT_EQ(StripAnsiEscapeCodes("plain text"), "plain text");
  EXPECT_EQ(StripAnsiEscapeCodes("1234567890"), "1234567890");
}

// Normal operation: simple ANSI color codes in the middle of text are stripped.
TEST_F(StripAnsiEscapeCodesTest_146, StripsSimpleColorCodes_146) {
  const string input = "start \x1b[31mred\x1b[0m end";
  const string expected = "start red end";

  EXPECT_EQ(StripAnsiEscapeCodes(input), expected);
}

// Normal operation: multiple and adjacent escape sequences are all stripped.
TEST_F(StripAnsiEscapeCodesTest_146, StripsMultipleAndAdjacentSequences_146) {
  const string input =
      "\x1b[31mred\x1b[0m "
      "\x1b[1mbold\x1b[0m";
  const string expected = "red bold";

  EXPECT_EQ(StripAnsiEscapeCodes(input), expected);
}

// Boundary: ESC not followed by '[' (not a CSI) – ESC is removed, following chars stay.
TEST_F(StripAnsiEscapeCodesTest_146, EscNotFollowedByBracket_146) {
  // ESC followed by 'X' should only remove ESC.
  const string input = "A\x1bX";
  const string expected = "AX";

  EXPECT_EQ(StripAnsiEscapeCodes(input), expected);
}

// Boundary: trailing standalone ESC at the end of the string is dropped.
TEST_F(StripAnsiEscapeCodesTest_146, TrailingStandaloneEscIsDropped_146) {
  const string input = "abc\x1b";
  const string expected = "abc";

  EXPECT_EQ(StripAnsiEscapeCodes(input), expected);
}

// Boundary / error-like: truncated CSI (ESC '[' with no terminating alpha) causes
// everything from the escape sequence to the end to be stripped.
TEST_F(StripAnsiEscapeCodesTest_146, TruncatedCsiWithoutTerminator_146) {
  const string input = "prefix\x1b[01;31";
  const string expected = "prefix";

  EXPECT_EQ(StripAnsiEscapeCodes(input), expected);
}

// Mixed content: multiple CSI sequences with different terminators are stripped,
// leaving only the visible text content.
TEST_F(StripAnsiEscapeCodesTest_146, MixedSequencesAndText_146) {
  const string input =
      "normal "
      "\x1b[32mgreen\x1b[0m,"
      " then \x1b[1mBOLD\x1b[0m!";
  const string expected = "normal green, then BOLD!";

  EXPECT_EQ(StripAnsiEscapeCodes(input), expected);
}

}  // namespace
