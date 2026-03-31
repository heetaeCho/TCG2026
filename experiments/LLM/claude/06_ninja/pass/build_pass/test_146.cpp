#include <gtest/gtest.h>
#include <string>

using std::string;

// Declaration of the function under test
string StripAnsiEscapeCodes(const string& in);

// Normal operation tests

TEST(StripAnsiEscapeCodesTest_146, EmptyString_146) {
  EXPECT_EQ("", StripAnsiEscapeCodes(""));
}

TEST(StripAnsiEscapeCodesTest_146, NoEscapeCodes_146) {
  EXPECT_EQ("hello world", StripAnsiEscapeCodes("hello world"));
}

TEST(StripAnsiEscapeCodesTest_146, SimpleCSISequence_146) {
  // ESC [ 31 m  (red color)
  string input = "hello \33[31mworld";
  EXPECT_EQ("hello world", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, MultipleCSISequences_146) {
  // ESC[31m ... ESC[0m
  string input = "\33[31mhello\33[0m world";
  EXPECT_EQ("hello world", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, CSIWithMultipleParameters_146) {
  // ESC[1;31m (bold red)
  string input = "\33[1;31mbold red\33[0m";
  EXPECT_EQ("bold red", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, OnlyCSISequence_146) {
  string input = "\33[31m";
  EXPECT_EQ("", StripAnsiEscapeCodes(input));
}

// Boundary condition tests

TEST(StripAnsiEscapeCodesTest_146, EscapeAtEnd_146) {
  // ESC at the very end of string, no more characters
  string input = "hello\33";
  EXPECT_EQ("hello", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, EscapeFollowedByNonBracket_146) {
  // ESC followed by something other than '[' — not a CSI, skip ESC only
  string input = "hello\33Aworld";
  EXPECT_EQ("helloworld", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, EscapeBracketNoTerminator_146) {
  // ESC [ but no alpha terminator — should consume until end
  string input = "hello\33[123";
  EXPECT_EQ("hello", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, EscapeBracketImmediateAlpha_146) {
  // ESC [ m — shortest possible CSI
  string input = "abc\33[mdef";
  EXPECT_EQ("abcdef", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, ConsecutiveCSISequences_146) {
  string input = "\33[1m\33[31m\33[42mtext\33[0m";
  EXPECT_EQ("text", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, SingleCharString_146) {
  EXPECT_EQ("a", StripAnsiEscapeCodes("a"));
}

TEST(StripAnsiEscapeCodesTest_146, OnlyEscapeCharacter_146) {
  string input(1, '\33');
  EXPECT_EQ("", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, EscapeBracketOnly_146) {
  // ESC [ with nothing after
  string input = "\33[";
  EXPECT_EQ("", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, TextBeforeAndAfterCSI_146) {
  string input = "before\33[32mafter";
  EXPECT_EQ("beforeafter", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, CSIWithDigitsAndSemicolons_146) {
  // ESC[38;5;196m — 256 color
  string input = "x\33[38;5;196my";
  EXPECT_EQ("xy", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, MultipleEscNonCSI_146) {
  // Multiple ESC followed by non-bracket chars
  string input = "\33A\33B\33C";
  EXPECT_EQ("", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, MixedEscAndText_146) {
  string input = "a\33[1mb\33Xc\33[0md";
  EXPECT_EQ("abcd", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, CSICursorMovement_146) {
  // ESC[2J — clear screen, ESC[H — cursor home
  string input = "\33[2J\33[Hhello";
  EXPECT_EQ("hello", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, PreservesNewlinesAndTabs_146) {
  string input = "line1\n\33[31mline2\33[0m\ttab";
  EXPECT_EQ("line1\nline2\ttab", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, EscapeAtBeginning_146) {
  string input = "\33[36mcolored";
  EXPECT_EQ("colored", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, LongParameterSequence_146) {
  // Very long parameter list before terminator
  string input = "start\33[0;1;2;3;4;5;6;7;8;9mend";
  EXPECT_EQ("startend", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, EscapeFollowedByBracketThenDigitsNoAlpha_146) {
  // ESC [ 1 2 3 — digits but no terminating alpha
  string input = "test\33[123";
  EXPECT_EQ("test", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, UpperCaseTerminator_146) {
  // CSI with uppercase terminator letter e.g. ESC[2J
  string input = "x\33[2Jy";
  EXPECT_EQ("xy", StripAnsiEscapeCodes(input));
}

TEST(StripAnsiEscapeCodesTest_146, LowerCaseTerminator_146) {
  // CSI with lowercase terminator letter e.g. ESC[32m
  string input = "x\33[32my";
  EXPECT_EQ("xy", StripAnsiEscapeCodes(input));
}
