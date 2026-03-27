// SPDX-License-Identifier: GPL-2.0-or-later
#include <gtest/gtest.h>

#include <string>

// NOTE:
// ltrim() is defined as a `static` function in a .cpp file, giving it internal linkage.
// To test it without re-implementing or altering production code, we include the .cpp
// translation unit directly here.
#include "TestProjects/exiv2/src/minoltamn_int.cpp"

namespace {

class LTrimTest_1013 : public ::testing::Test {};

TEST_F(LTrimTest_1013, RemovesLeadingDefaultWhitespace_1013) {
  std::string s = " \t\n\r\f\vHello";
  std::string* original_ptr = &s;

  std::string& r = Exiv2::Internal::ltrim(s);

  EXPECT_EQ(&r, original_ptr);  // returns a reference to the same string object
  EXPECT_EQ(s, "Hello");
}

TEST_F(LTrimTest_1013, NoLeadingTrimCharactersLeavesStringUnchanged_1013) {
  std::string s = "Hello";
  std::string* original_ptr = &s;

  std::string& r = Exiv2::Internal::ltrim(s);

  EXPECT_EQ(&r, original_ptr);
  EXPECT_EQ(s, "Hello");
}

TEST_F(LTrimTest_1013, EmptyStringRemainsEmpty_1013) {
  std::string s;
  std::string* original_ptr = &s;

  std::string& r = Exiv2::Internal::ltrim(s);

  EXPECT_EQ(&r, original_ptr);
  EXPECT_TRUE(s.empty());
}

TEST_F(LTrimTest_1013, AllTrimCharactersResultsInEmptyString_1013) {
  std::string s = " \t\n\r\f\v";
  std::string* original_ptr = &s;

  std::string& r = Exiv2::Internal::ltrim(s);

  EXPECT_EQ(&r, original_ptr);
  EXPECT_TRUE(s.empty());
}

TEST_F(LTrimTest_1013, TrimsUsingCustomCharacterSet_1013) {
  std::string s = "xxxyHello";
  std::string* original_ptr = &s;

  std::string& r = Exiv2::Internal::ltrim(s, "xy");

  EXPECT_EQ(&r, original_ptr);
  EXPECT_EQ(s, "Hello");
}

TEST_F(LTrimTest_1013, CustomSetDoesNotTrimCharactersNotInSet_1013) {
  std::string s = "  Hello";  // leading spaces
  std::string* original_ptr = &s;

  // Only trim 'x' and 'y', so leading spaces should remain.
  std::string& r = Exiv2::Internal::ltrim(s, "xy");

  EXPECT_EQ(&r, original_ptr);
  EXPECT_EQ(s, "  Hello");
}

TEST_F(LTrimTest_1013, EmptyTrimSetDoesNotChangeString_1013) {
  std::string s = "  Hello";
  std::string* original_ptr = &s;

  std::string& r = Exiv2::Internal::ltrim(s, "");

  EXPECT_EQ(&r, original_ptr);
  EXPECT_EQ(s, "  Hello");
}

TEST_F(LTrimTest_1013, CanBeChainedViaReturnedReference_1013) {
  std::string s = "   abc";
  std::string* original_ptr = &s;

  // If ltrim returns a usable reference, this should compile and behave as expected.
  std::string& r = Exiv2::Internal::ltrim(s);
  r += "def";

  EXPECT_EQ(&r, original_ptr);
  EXPECT_EQ(s, "abcdef");
}

}  // namespace