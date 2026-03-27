// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

// NOTE:
// The function under test is defined as a `static` function in a .cpp file (internal linkage).
// To test it through its provided interface/signature, we include the implementation file
// so the tests are in the same translation unit.
#include "TestProjects/exiv2/src/minoltamn_int.cpp"

namespace {

class RtrimTest_1014 : public ::testing::Test {};

TEST_F(RtrimTest_1014, ReturnsSameReference_1014) {
  std::string s = "abc   ";
  std::string* p_before = &s;

  std::string& r = Exiv2::Internal::rtrim(s);

  EXPECT_EQ(&r, p_before);
  EXPECT_EQ(&s, p_before);
}

TEST_F(RtrimTest_1014, TrimsDefaultWhitespaceCharacters_1014) {
  std::string s = "abc \t\n\r\f\v";
  Exiv2::Internal::rtrim(s);
  EXPECT_EQ(s, "abc");
}

TEST_F(RtrimTest_1014, DoesNotTrimLeadingWhitespace_1014) {
  std::string s = "   abc   ";
  Exiv2::Internal::rtrim(s);
  EXPECT_EQ(s, "   abc");
}

TEST_F(RtrimTest_1014, NoTrailingTrimCharactersLeavesStringUnchanged_1014) {
  std::string s = "abc";
  Exiv2::Internal::rtrim(s);
  EXPECT_EQ(s, "abc");
}

TEST_F(RtrimTest_1014, CustomTrimSetOnlyTrimsThoseCharacters_1014) {
  std::string s = "abcxxx   ";
  Exiv2::Internal::rtrim(s, "x");
  // Only trailing 'x' should be removed; spaces are not in the custom trim set.
  EXPECT_EQ(s, "abcxxx   ");
}

TEST_F(RtrimTest_1014, CustomTrimSetTrimsTrailingCustomCharacters_1014) {
  std::string s = "abcxxx";
  Exiv2::Internal::rtrim(s, "x");
  EXPECT_EQ(s, "abc");
}

TEST_F(RtrimTest_1014, Boundary_EmptyString_ThrowsOutOfRange_1014) {
  std::string s;
  EXPECT_THROW((void)Exiv2::Internal::rtrim(s), std::out_of_range);
}

TEST_F(RtrimTest_1014, Boundary_AllTrimCharacters_ThrowsOutOfRange_1014) {
  std::string s = " \t\n\r\f\v";
  EXPECT_THROW((void)Exiv2::Internal::rtrim(s), std::out_of_range);
}

}  // namespace