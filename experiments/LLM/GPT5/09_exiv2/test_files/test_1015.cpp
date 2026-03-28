// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_minoltamn_int_trim_1015.cpp
//
// Unit tests for Exiv2::Internal::trim (from minoltamn_int.cpp)
//
// Notes:
// - The function under test is defined as `static` in a .cpp, so it has internal linkage.
//   To test it, we include the implementation file so the symbol is available in this TU.
// - These tests treat behavior as a black box and validate only observable outcomes.

#include <gtest/gtest.h>

#include <string>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4702) // unreachable code (paranoia for some build configs)
#endif

// Include the implementation to access the internal-linkage function.
#include "minoltamn_int.cpp"

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

namespace {

class MinoltaMnTrimTest_1015 : public ::testing::Test {};

TEST_F(MinoltaMnTrimTest_1015, ReturnsSameStringReference_1015) {
  std::string s = "  abc  ";
  std::string* originalPtr = &s;

  std::string& out = Exiv2::Internal::trim(s);

  EXPECT_EQ(originalPtr, &out);
  EXPECT_EQ(originalPtr, &s);
}

TEST_F(MinoltaMnTrimTest_1015, NoLeadingOrTrailingWhitespaceLeavesStringUnchanged_1015) {
  std::string s = "abc";
  Exiv2::Internal::trim(s);
  EXPECT_EQ("abc", s);
}

TEST_F(MinoltaMnTrimTest_1015, TrimsLeadingSpaces_1015) {
  std::string s = "   abc";
  Exiv2::Internal::trim(s);
  EXPECT_EQ("abc", s);
}

TEST_F(MinoltaMnTrimTest_1015, TrimsTrailingSpaces_1015) {
  std::string s = "abc   ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ("abc", s);
}

TEST_F(MinoltaMnTrimTest_1015, TrimsLeadingAndTrailingSpaces_1015) {
  std::string s = "   abc   ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ("abc", s);
}

TEST_F(MinoltaMnTrimTest_1015, DoesNotRemoveInternalWhitespace_1015) {
  std::string s = "  a b c  ";
  Exiv2::Internal::trim(s);
  EXPECT_EQ("a b c", s);
}

TEST_F(MinoltaMnTrimTest_1015, TrimsTabsAndNewlinesByDefault_1015) {
  std::string s = "\t\n\r  abc \v\f\t";
  Exiv2::Internal::trim(s);
  EXPECT_EQ("abc", s);
}

TEST_F(MinoltaMnTrimTest_1015, EmptyStringRemainsEmpty_1015) {
  std::string s;
  Exiv2::Internal::trim(s);
  EXPECT_TRUE(s.empty());
}

TEST_F(MinoltaMnTrimTest_1015, AllTrimmableCharactersResultsInEmptyString_1015) {
  std::string s = " \t\n\r\f\v  \t";
  Exiv2::Internal::trim(s);
  EXPECT_EQ("", s);
}

TEST_F(MinoltaMnTrimTest_1015, CustomTrimCharactersAffectOnlyEnds_1015) {
  std::string s = "***a*b***";
  Exiv2::Internal::trim(s, "*");
  EXPECT_EQ("a*b", s);
}

TEST_F(MinoltaMnTrimTest_1015, CustomTrimCharactersDoNotTrimIfNotAtEnds_1015) {
  std::string s = "  *abc*  ";
  // Trim only '*', not spaces; should remove only leading/trailing '*' (none at extreme ends).
  Exiv2::Internal::trim(s, "*");
  EXPECT_EQ("  *abc*  ", s);
}

TEST_F(MinoltaMnTrimTest_1015, CustomTrimCharactersCanTrimMultipleKinds_1015) {
  std::string s = "xyxyHELLOyxx";
  Exiv2::Internal::trim(s, "xy");
  EXPECT_EQ("HELLO", s);
}

}  // namespace