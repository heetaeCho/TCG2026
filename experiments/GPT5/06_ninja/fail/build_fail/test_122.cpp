#include <string>
#include <gtest/gtest.h>

using std::string;

// Declare the function under test (it will be defined in the production code).
string EscapeForDepfile(const string& path);

//
// TEST_ID: 122
//

// No spaces: string should remain unchanged.
TEST(EscapeForDepfileTest_122, NoSpacesUnchanged_122) {
  const string input = "path/with/no_spaces";
  const string output = EscapeForDepfile(input);
  EXPECT_EQ(output, input);
}

// Single space: space should be escaped with backslash-space.
TEST(EscapeForDepfileTest_122, SingleSpaceEscaped_122) {
  const string input = "a b";
  const string expected = "a\\ b";
  const string output = EscapeForDepfile(input);
  EXPECT_EQ(output, expected);
}

// Multiple spaces: each space should be escaped.
TEST(EscapeForDepfileTest_122, MultipleSpacesEscaped_122) {
  const string input = "a b c";
  const string expected = "a\\ b\\ c";
  const string output = EscapeForDepfile(input);
  EXPECT_EQ(output, expected);
}

// Consecutive spaces: each individual space should be escaped.
TEST(EscapeForDepfileTest_122, ConsecutiveSpacesEscapedIndividually_122) {
  const string input = "a  b";
  const string expected = "a\\ \\ b";
  const string output = EscapeForDepfile(input);
  EXPECT_EQ(output, expected);
}

// Leading and trailing spaces should also be escaped.
TEST(EscapeForDepfileTest_122, LeadingAndTrailingSpacesEscaped_122) {
  const string input = " a b ";
  const string expected = "\\ a\\ b\\ ";
  const string output = EscapeForDepfile(input);
  EXPECT_EQ(output, expected);
}

// Empty string: should remain empty (boundary case).
TEST(EscapeForDepfileTest_122, EmptyStringStaysEmpty_122) {
  const string input = "";
  const string output = EscapeForDepfile(input);
  EXPECT_TRUE(output.empty());
}

// Typical Windows-style path with spaces: spaces in directory names are escaped.
TEST(EscapeForDepfileTest_122, WindowsPathWithSpacesEscaped_122) {
  const string input = "C:\\Program Files\\ninja";
  const string expected = "C:\\Program\\ Files\\ninja";
  const string output = EscapeForDepfile(input);
  EXPECT_EQ(output, expected);
}
