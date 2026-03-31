#include <gtest/gtest.h>
#include <string>

using std::string;

// Declaration of the function under test
string EscapeForDepfile(const string& path);

// Test normal path without spaces
TEST(EscapeForDepfileTest_122, NoSpaces_122) {
  string input = "C:\\Users\\file.txt";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "C:\\Users\\file.txt");
}

// Test path with a single space
TEST(EscapeForDepfileTest_122, SingleSpace_122) {
  string input = "C:\\Program Files\\file.txt";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "C:\\Program\\ Files\\file.txt");
}

// Test path with multiple spaces
TEST(EscapeForDepfileTest_122, MultipleSpaces_122) {
  string input = "C:\\Program Files\\My Documents\\file.txt";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "C:\\Program\\ Files\\My\\ Documents\\file.txt");
}

// Test empty string
TEST(EscapeForDepfileTest_122, EmptyString_122) {
  string input = "";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "");
}

// Test string that is only a single space
TEST(EscapeForDepfileTest_122, OnlyOneSpace_122) {
  string input = " ";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "\\ ");
}

// Test string with consecutive spaces
TEST(EscapeForDepfileTest_122, ConsecutiveSpaces_122) {
  string input = "a  b";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "a\\ \\ b");
}

// Test string that is only multiple spaces
TEST(EscapeForDepfileTest_122, OnlyMultipleSpaces_122) {
  string input = "   ";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "\\ \\ \\ ");
}

// Test path with space at the beginning
TEST(EscapeForDepfileTest_122, SpaceAtBeginning_122) {
  string input = " leading";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "\\ leading");
}

// Test path with space at the end
TEST(EscapeForDepfileTest_122, SpaceAtEnd_122) {
  string input = "trailing ";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "trailing\\ ");
}

// Test path with spaces at both ends
TEST(EscapeForDepfileTest_122, SpaceAtBothEnds_122) {
  string input = " both ";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "\\ both\\ ");
}

// Test that backslashes not followed by space are preserved
TEST(EscapeForDepfileTest_122, ExistingBackslashes_122) {
  string input = "C:\\foo\\bar";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "C:\\foo\\bar");
}

// Test path with existing backslash-space sequence (not a real escape, just literal chars)
TEST(EscapeForDepfileTest_122, ExistingBackslashBeforeSpace_122) {
  string input = "C:\\foo\\ bar";
  string result = EscapeForDepfile(input);
  // The space in "\\ bar" should be escaped, the existing backslash stays
  EXPECT_EQ(result, "C:\\foo\\\\ bar");
}

// Test a typical Windows path with spaces in directory names
TEST(EscapeForDepfileTest_122, TypicalWindowsPath_122) {
  string input = "C:\\Program Files (x86)\\Some App\\include\\header.h";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "C:\\Program\\ Files\\ (x86)\\Some\\ App\\include\\header.h");
}

// Test a single character string (no space)
TEST(EscapeForDepfileTest_122, SingleCharNoSpace_122) {
  string input = "a";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "a");
}

// Test with tabs (should not be escaped, only spaces)
TEST(EscapeForDepfileTest_122, TabCharacterNotEscaped_122) {
  string input = "a\tb";
  string result = EscapeForDepfile(input);
  EXPECT_EQ(result, "a\tb");
}
