#include "gtest/gtest.h"
#include "string_piece_util.h"
#include "string_piece.h"

// Test: Both strings are empty
TEST(EqualsCaseInsensitiveASCIITest_126, BothEmpty_126) {
  StringPiece a("", 0);
  StringPiece b("", 0);
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Identical lowercase strings
TEST(EqualsCaseInsensitiveASCIITest_126, IdenticalLowercase_126) {
  StringPiece a("hello");
  StringPiece b("hello");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Identical uppercase strings
TEST(EqualsCaseInsensitiveASCIITest_126, IdenticalUppercase_126) {
  StringPiece a("HELLO");
  StringPiece b("HELLO");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Mixed case strings that are equal case-insensitively
TEST(EqualsCaseInsensitiveASCIITest_126, MixedCaseEqual_126) {
  StringPiece a("HeLLo");
  StringPiece b("hEllO");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Different lengths should return false
TEST(EqualsCaseInsensitiveASCIITest_126, DifferentLengths_126) {
  StringPiece a("hello");
  StringPiece b("hell");
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Same length but different content
TEST(EqualsCaseInsensitiveASCIITest_126, SameLengthDifferentContent_126) {
  StringPiece a("hello");
  StringPiece b("world");
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: One empty, one non-empty
TEST(EqualsCaseInsensitiveASCIITest_126, OneEmptyOneNonEmpty_126) {
  StringPiece a("");
  StringPiece b("a");
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Single character, same case
TEST(EqualsCaseInsensitiveASCIITest_126, SingleCharSameCase_126) {
  StringPiece a("a");
  StringPiece b("a");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Single character, different case
TEST(EqualsCaseInsensitiveASCIITest_126, SingleCharDifferentCase_126) {
  StringPiece a("a");
  StringPiece b("A");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Single character, different characters
TEST(EqualsCaseInsensitiveASCIITest_126, SingleCharDifferent_126) {
  StringPiece a("a");
  StringPiece b("b");
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Strings with numbers (non-alpha characters)
TEST(EqualsCaseInsensitiveASCIITest_126, NumbersEqual_126) {
  StringPiece a("test123");
  StringPiece b("TEST123");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Strings with special characters
TEST(EqualsCaseInsensitiveASCIITest_126, SpecialCharsEqual_126) {
  StringPiece a("hello-world_123!");
  StringPiece b("HELLO-WORLD_123!");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Strings differ only at the last character
TEST(EqualsCaseInsensitiveASCIITest_126, DifferAtLastChar_126) {
  StringPiece a("hellx");
  StringPiece b("helly");
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Strings differ only at the first character
TEST(EqualsCaseInsensitiveASCIITest_126, DifferAtFirstChar_126) {
  StringPiece a("xello");
  StringPiece b("yello");
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: All uppercase vs all lowercase
TEST(EqualsCaseInsensitiveASCIITest_126, AllUpperVsAllLower_126) {
  StringPiece a("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  StringPiece b("abcdefghijklmnopqrstuvwxyz");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Strings constructed from std::string
TEST(EqualsCaseInsensitiveASCIITest_126, StdStringConstruction_126) {
  std::string sa = "FooBar";
  std::string sb = "foobar";
  StringPiece a(sa);
  StringPiece b(sb);
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Strings with spaces
TEST(EqualsCaseInsensitiveASCIITest_126, WithSpaces_126) {
  StringPiece a("Hello World");
  StringPiece b("hello world");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Strings with only spaces, different lengths
TEST(EqualsCaseInsensitiveASCIITest_126, SpacesDifferentLength_126) {
  StringPiece a("  ");
  StringPiece b("   ");
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Symmetry of comparison
TEST(EqualsCaseInsensitiveASCIITest_126, Symmetry_126) {
  StringPiece a("Hello");
  StringPiece b("hELLO");
  EXPECT_EQ(EqualsCaseInsensitiveASCII(a, b), EqualsCaseInsensitiveASCII(b, a));
}

// Test: StringPiece with explicit length including potential null bytes
TEST(EqualsCaseInsensitiveASCIITest_126, ExplicitLengthWithNullByte_126) {
  const char data1[] = "ab\0cd";
  const char data2[] = "AB\0CD";
  StringPiece a(data1, 5);
  StringPiece b(data2, 5);
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Digits only strings
TEST(EqualsCaseInsensitiveASCIITest_126, DigitsOnly_126) {
  StringPiece a("12345");
  StringPiece b("12345");
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Digit vs letter same length
TEST(EqualsCaseInsensitiveASCIITest_126, DigitVsLetter_126) {
  StringPiece a("1");
  StringPiece b("a");
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Long identical strings with mixed case
TEST(EqualsCaseInsensitiveASCIITest_126, LongMixedCaseEqual_126) {
  std::string s1(1000, 'A');
  std::string s2(1000, 'a');
  StringPiece a(s1);
  StringPiece b(s2);
  EXPECT_TRUE(EqualsCaseInsensitiveASCII(a, b));
}

// Test: Long strings differ at the very end
TEST(EqualsCaseInsensitiveASCIITest_126, LongStringsDifferAtEnd_126) {
  std::string s1(1000, 'a');
  std::string s2(1000, 'a');
  s2[999] = 'b';
  StringPiece a(s1);
  StringPiece b(s2);
  EXPECT_FALSE(EqualsCaseInsensitiveASCII(a, b));
}
