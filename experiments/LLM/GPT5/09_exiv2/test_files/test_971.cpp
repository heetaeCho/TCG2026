// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_pngimage_findi_971.cpp
//
// Unit tests for the partial implementation in:
//   ./TestProjects/exiv2/src/pngimage.cpp
//
// Provided code under test:
// namespace Exiv2 {
//   static std::string::size_type findi(const std::string& str, const std::string& substr) {
//     return str.find(substr);
//   }
// }
//
// Notes:
// - We treat this as a black box and only test observable behavior via return values.
// - Because the function is declared `static` at namespace scope, it has internal linkage;
//   to test it, we include the production .cpp directly in this test TU.

#include <gtest/gtest.h>

#include <cstddef>
#include <string>

// Include the implementation file to access the internal-linkage function.
#include "TestProjects/exiv2/src/pngimage.cpp"

namespace {

// TEST_ID = 971

class PngImageFindiTest_971 : public ::testing::Test {};

TEST_F(PngImageFindiTest_971, FindsSubstringAtBeginning_971) {
  const std::string str = "abcdef";
  const std::string sub = "abc";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, 0u);
}

TEST_F(PngImageFindiTest_971, FindsSubstringInMiddle_971) {
  const std::string str = "xxHELLOyy";
  const std::string sub = "HELLO";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, 2u);
}

TEST_F(PngImageFindiTest_971, FindsSubstringAtEnd_971) {
  const std::string str = "12345END";
  const std::string sub = "END";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, 5u);
}

TEST_F(PngImageFindiTest_971, ReturnsNposWhenSubstringNotFound_971) {
  const std::string str = "abcdef";
  const std::string sub = "gh";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, std::string::npos);
}

TEST_F(PngImageFindiTest_971, EmptySubstringReturnsZero_971) {
  const std::string str = "abcdef";
  const std::string sub = "";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, 0u);
}

TEST_F(PngImageFindiTest_971, EmptyStringAndEmptySubstringReturnsZero_971) {
  const std::string str = "";
  const std::string sub = "";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, 0u);
}

TEST_F(PngImageFindiTest_971, EmptyStringAndNonEmptySubstringReturnsNpos_971) {
  const std::string str = "";
  const std::string sub = "x";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, std::string::npos);
}

TEST_F(PngImageFindiTest_971, SubstringLongerThanStringReturnsNpos_971) {
  const std::string str = "ab";
  const std::string sub = "abc";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, std::string::npos);
}

TEST_F(PngImageFindiTest_971, IsCaseSensitiveBasedOnObservableBehavior_971) {
  const std::string str = "AbCdEf";
  const std::string sub = "abcdef";

  const auto pos = Exiv2::findi(str, sub);

  // Observable behavior: since it delegates to std::string::find, this should not match.
  EXPECT_EQ(pos, std::string::npos);
}

TEST_F(PngImageFindiTest_971, FindsFirstOccurrenceWhenMultipleMatchesExist_971) {
  const std::string str = "one two one two";
  const std::string sub = "one";

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, 0u);
}

TEST_F(PngImageFindiTest_971, HandlesEmbeddedNullBytesInString_971) {
  // Construct a string with embedded '\0': "ab\0cd" (size 5)
  const std::string str(std::string("ab\0cd", 5));
  const std::string sub(std::string("\0c", 2));

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, 2u);
}

TEST_F(PngImageFindiTest_971, HandlesEmbeddedNullBytesNotFound_971) {
  const std::string str(std::string("ab\0cd", 5));
  const std::string sub(std::string("\0e", 2));

  const auto pos = Exiv2::findi(str, sub);

  EXPECT_EQ(pos, std::string::npos);
}

}  // namespace