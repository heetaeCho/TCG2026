// File: ascii_strcasecmp_test_261.cc
#include <gtest/gtest.h>

// Include the implementation unit so the internal-linkage function is available
// to this translation unit for testing without altering production code.
#include "TestProjects/re2/re2/re2.cc"

using re2::ascii_strcasecmp;

namespace {

TEST(AsciiStrcasecmpTest_261, EqualStrings_ReturnsZero_261) {
  const char* a = "hello";
  const char* b = "hello";
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 5));
}

TEST(AsciiStrcasecmpTest_261, CaseFoldOnBOnly_SymmetricVsAsymmetric_261) {
  // Normal case-insensitive match when 'b' differs by case
  EXPECT_EQ(0, ascii_strcasecmp("abc", "ABC", 3));

  // Asymmetry: only 'b' is folded; 'a' is not.
  // 'A' (65) vs lowered 'a' (97) -> negative result
  EXPECT_LT(ascii_strcasecmp("ABC", "abc", 3), 0);
}

TEST(AsciiStrcasecmpTest_261, PartialLength_RespectsPrefixOnly_261) {
  // First 3 chars equal ignoring case on b
  EXPECT_EQ(0, ascii_strcasecmp("abcdef", "ABCxyz", 3));

  // At length 4, 'd'(100) vs 'x'(120) -> negative
  EXPECT_LT(ascii_strcasecmp("abcdef", "ABCxyz", 4), 0);
}

TEST(AsciiStrcasecmpTest_261, ZeroLength_ReturnsZeroRegardlessOfInputs_261) {
  EXPECT_EQ(0, ascii_strcasecmp("anything", "ANYTHING", 0));
  EXPECT_EQ(0, ascii_strcasecmp("", "", 0));
}

TEST(AsciiStrcasecmpTest_261, EmbeddedNulls_AreCompared_261) {
  const char a[] = {'\0', 'a', 'Z'};
  const char b[] = {'\0', 'A', 'z'};
  // Compare first two bytes: 0 == 0, then 'a' vs folded 'A' -> equal
  EXPECT_EQ(0, ascii_strcasecmp(a, b, 2));

  // Including third byte: 'Z'(90) vs folded 'z'(122) -> negative
  EXPECT_LT(ascii_strcasecmp(a, b, 3), 0);
}

TEST(AsciiStrcasecmpTest_261, EarlyDifference_NegativeWhenAIsSmaller_261) {
  // 'b'(98) vs folded 'C'->'c'(99) -> negative
  EXPECT_LT(ascii_strcasecmp("ab", "aC", 2), 0);
}

TEST(AsciiStrcasecmpTest_261, PositiveWhenAIsLarger_261) {
  // 'c'(99) vs folded 'B'->'b'(98) -> positive
  EXPECT_GT(ascii_strcasecmp("c", "B", 1), 0);
}

TEST(AsciiStrcasecmpTest_261, NonAsciiBytes_TreatedAsRawBytes_261) {
  // Construct explicit bytes >= 128 to avoid signed-char pitfalls.
  const unsigned char ua[] = {0xFF, 0x80, 0x41};  // 0x41 = 'A'
  const unsigned char ub[] = {0xFF, 0x80, 0x61};  // 0x61 = 'a'
  // First two bytes equal; third: 'A'(65) vs folded 'a'(97) -> negative
  EXPECT_LT(ascii_strcasecmp(reinterpret_cast<const char*>(ua),
                             reinterpret_cast<const char*>(ub), 3));

  // Same raw high bytes compared to themselves -> equal
  const unsigned char uc[] = {0xFE, 0xC3, 0x00};
  EXPECT_EQ(0, ascii_strcasecmp(reinterpret_cast<const char*>(uc),
                                reinterpret_cast<const char*>(uc), 3));
}

}  // namespace
