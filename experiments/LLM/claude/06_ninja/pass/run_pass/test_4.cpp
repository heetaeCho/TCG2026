#include "gtest/gtest.h"
#include "string_piece.h"
#include <string>
#include <cstring>

// Test default constructor
TEST(StringPieceTest_4, DefaultConstructor_4) {
  StringPiece sp;
  EXPECT_EQ(sp.str_, nullptr);
  EXPECT_EQ(sp.len_, 0u);
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.size(), 0u);
}

// Test construction from std::string
TEST(StringPieceTest_4, ConstructFromStdString_4) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(sp.str_, s.data());
  EXPECT_EQ(sp.len_, s.size());
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_FALSE(sp.empty());
  EXPECT_EQ(sp.AsString(), "hello");
}

// Test construction from const char*
TEST(StringPieceTest_4, ConstructFromCString_4) {
  const char* cstr = "world";
  StringPiece sp(cstr);
  EXPECT_EQ(sp.str_, cstr);
  EXPECT_EQ(sp.len_, strlen(cstr));
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_EQ(sp.AsString(), "world");
}

// Test construction from const char* and length
TEST(StringPieceTest_4, ConstructFromCStringAndLength_4) {
  const char* cstr = "hello world";
  StringPiece sp(cstr, 5);
  EXPECT_EQ(sp.str_, cstr);
  EXPECT_EQ(sp.len_, 5u);
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_EQ(sp.AsString(), "hello");
}

// Test construction from empty std::string
TEST(StringPieceTest_4, ConstructFromEmptyStdString_4) {
  std::string s = "";
  StringPiece sp(s);
  EXPECT_EQ(sp.len_, 0u);
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_EQ(sp.AsString(), "");
}

// Test construction from empty C string
TEST(StringPieceTest_4, ConstructFromEmptyCString_4) {
  const char* cstr = "";
  StringPiece sp(cstr);
  EXPECT_EQ(sp.len_, 0u);
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.AsString(), "");
}

// Test equality operator - equal strings
TEST(StringPieceTest_4, EqualityOperatorEqual_4) {
  StringPiece sp1("hello");
  StringPiece sp2("hello");
  EXPECT_TRUE(sp1 == sp2);
  EXPECT_FALSE(sp1 != sp2);
}

// Test equality operator - different strings
TEST(StringPieceTest_4, EqualityOperatorNotEqual_4) {
  StringPiece sp1("hello");
  StringPiece sp2("world");
  EXPECT_FALSE(sp1 == sp2);
  EXPECT_TRUE(sp1 != sp2);
}

// Test equality operator - different lengths
TEST(StringPieceTest_4, EqualityOperatorDifferentLengths_4) {
  StringPiece sp1("hello");
  StringPiece sp2("hell");
  EXPECT_FALSE(sp1 == sp2);
  EXPECT_TRUE(sp1 != sp2);
}

// Test equality operator - both empty
TEST(StringPieceTest_4, EqualityOperatorBothEmpty_4) {
  StringPiece sp1("");
  StringPiece sp2("");
  EXPECT_TRUE(sp1 == sp2);
  EXPECT_FALSE(sp1 != sp2);
}

// Test equality with default constructed
TEST(StringPieceTest_4, EqualityDefaultConstructed_4) {
  StringPiece sp1;
  StringPiece sp2;
  EXPECT_TRUE(sp1 == sp2);
}

// Test begin() and end()
TEST(StringPieceTest_4, BeginEnd_4) {
  const char* cstr = "hello";
  StringPiece sp(cstr);
  EXPECT_EQ(sp.begin(), cstr);
  EXPECT_EQ(sp.end(), cstr + 5);
  EXPECT_EQ(sp.end() - sp.begin(), 5);
}

// Test begin() and end() for empty string
TEST(StringPieceTest_4, BeginEndEmpty_4) {
  const char* cstr = "";
  StringPiece sp(cstr);
  EXPECT_EQ(sp.begin(), sp.end());
}

// Test operator[]
TEST(StringPieceTest_4, IndexOperator_4) {
  StringPiece sp("abcde");
  EXPECT_EQ(sp[0], 'a');
  EXPECT_EQ(sp[1], 'b');
  EXPECT_EQ(sp[2], 'c');
  EXPECT_EQ(sp[3], 'd');
  EXPECT_EQ(sp[4], 'e');
}

// Test size()
TEST(StringPieceTest_4, Size_4) {
  StringPiece sp("test");
  EXPECT_EQ(sp.size(), 4u);
}

// Test size() for empty
TEST(StringPieceTest_4, SizeEmpty_4) {
  StringPiece sp;
  EXPECT_EQ(sp.size(), 0u);
}

// Test empty()
TEST(StringPieceTest_4, EmptyNonEmpty_4) {
  StringPiece sp("notempty");
  EXPECT_FALSE(sp.empty());
}

TEST(StringPieceTest_4, EmptyIsEmpty_4) {
  StringPiece sp;
  EXPECT_TRUE(sp.empty());
}

// Test AsString()
TEST(StringPieceTest_4, AsString_4) {
  const char* cstr = "convert me";
  StringPiece sp(cstr);
  std::string result = sp.AsString();
  EXPECT_EQ(result, "convert me");
  EXPECT_EQ(result.size(), 10u);
}

// Test AsString() with partial string (using length constructor)
TEST(StringPieceTest_4, AsStringPartial_4) {
  const char* cstr = "hello world";
  StringPiece sp(cstr, 5);
  std::string result = sp.AsString();
  EXPECT_EQ(result, "hello");
}

// Test AsString() for empty
TEST(StringPieceTest_4, AsStringEmpty_4) {
  StringPiece sp("");
  std::string result = sp.AsString();
  EXPECT_EQ(result, "");
  EXPECT_EQ(result.size(), 0u);
}

// Test iteration with range-based concepts
TEST(StringPieceTest_4, IterationOverCharacters_4) {
  StringPiece sp("abc");
  std::string collected;
  for (auto it = sp.begin(); it != sp.end(); ++it) {
    collected += *it;
  }
  EXPECT_EQ(collected, "abc");
}

// Test with string containing null bytes using length constructor
TEST(StringPieceTest_4, StringWithEmbeddedNull_4) {
  const char data[] = "he\0lo";
  StringPiece sp(data, 5);
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_EQ(sp[0], 'h');
  EXPECT_EQ(sp[1], 'e');
  EXPECT_EQ(sp[2], '\0');
  EXPECT_EQ(sp[3], 'l');
  EXPECT_EQ(sp[4], 'o');
}

// Test equality with prefix substring
TEST(StringPieceTest_4, EqualityPrefixVsFull_4) {
  const char* cstr = "hello";
  StringPiece full(cstr, 5);
  StringPiece prefix(cstr, 3);
  EXPECT_FALSE(full == prefix);
  EXPECT_TRUE(full != prefix);
}

// Test equality same content different sources
TEST(StringPieceTest_4, EqualitySameContentDifferentSource_4) {
  std::string s1 = "test";
  std::string s2 = "test";
  StringPiece sp1(s1);
  StringPiece sp2(s2);
  // Different pointers but same content
  EXPECT_NE(sp1.str_, sp2.str_);
  EXPECT_TRUE(sp1 == sp2);
}

// Test single character string
TEST(StringPieceTest_4, SingleCharacter_4) {
  StringPiece sp("x");
  EXPECT_EQ(sp.size(), 1u);
  EXPECT_FALSE(sp.empty());
  EXPECT_EQ(sp[0], 'x');
  EXPECT_EQ(sp.begin() + 1, sp.end());
  EXPECT_EQ(sp.AsString(), "x");
}

// Test long string
TEST(StringPieceTest_4, LongString_4) {
  std::string long_str(10000, 'a');
  StringPiece sp(long_str);
  EXPECT_EQ(sp.size(), 10000u);
  EXPECT_FALSE(sp.empty());
  EXPECT_EQ(sp[0], 'a');
  EXPECT_EQ(sp[9999], 'a');
  EXPECT_EQ(sp.AsString(), long_str);
}

// Test zero length with non-null pointer
TEST(StringPieceTest_4, ZeroLengthNonNullPointer_4) {
  const char* cstr = "hello";
  StringPiece sp(cstr, 0);
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.begin(), sp.end());
}

// Test inequality operator explicitly
TEST(StringPieceTest_4, InequalityOperator_4) {
  StringPiece sp1("abc");
  StringPiece sp2("abd");
  EXPECT_TRUE(sp1 != sp2);
  EXPECT_FALSE(sp1 == sp2);
}
