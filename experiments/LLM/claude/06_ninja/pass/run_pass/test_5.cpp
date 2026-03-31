#include "gtest/gtest.h"
#include "string_piece.h"
#include <string>
#include <cstring>

// Default constructor tests
TEST(StringPieceTest_5, DefaultConstructor_IsEmpty_5) {
  StringPiece sp;
  EXPECT_EQ(sp.str_, nullptr);
  EXPECT_EQ(sp.len_, 0u);
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.size(), 0u);
}

// Constructor from std::string
TEST(StringPieceTest_5, ConstructFromStdString_5) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(sp.str_, s.data());
  EXPECT_EQ(sp.len_, 5u);
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_FALSE(sp.empty());
}

TEST(StringPieceTest_5, ConstructFromEmptyStdString_5) {
  std::string s;
  StringPiece sp(s);
  EXPECT_EQ(sp.len_, 0u);
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_TRUE(sp.empty());
}

// Constructor from const char*
TEST(StringPieceTest_5, ConstructFromCString_5) {
  const char* s = "world";
  StringPiece sp(s);
  EXPECT_EQ(sp.str_, s);
  EXPECT_EQ(sp.len_, 5u);
  EXPECT_EQ(sp.size(), 5u);
}

TEST(StringPieceTest_5, ConstructFromEmptyCString_5) {
  const char* s = "";
  StringPiece sp(s);
  EXPECT_EQ(sp.len_, 0u);
  EXPECT_TRUE(sp.empty());
}

// Constructor from const char* and length
TEST(StringPieceTest_5, ConstructFromCStringAndLength_5) {
  const char* s = "hello world";
  StringPiece sp(s, 5);
  EXPECT_EQ(sp.str_, s);
  EXPECT_EQ(sp.len_, 5u);
  EXPECT_EQ(sp.size(), 5u);
}

TEST(StringPieceTest_5, ConstructFromCStringAndZeroLength_5) {
  const char* s = "hello";
  StringPiece sp(s, 0);
  EXPECT_EQ(sp.len_, 0u);
  EXPECT_TRUE(sp.empty());
}

// operator==
TEST(StringPieceTest_5, EqualityOperator_SameContent_5) {
  StringPiece sp1("hello");
  StringPiece sp2("hello");
  EXPECT_TRUE(sp1 == sp2);
}

TEST(StringPieceTest_5, EqualityOperator_DifferentContent_5) {
  StringPiece sp1("hello");
  StringPiece sp2("world");
  EXPECT_FALSE(sp1 == sp2);
}

TEST(StringPieceTest_5, EqualityOperator_DifferentLengths_5) {
  StringPiece sp1("hello");
  StringPiece sp2("hell");
  EXPECT_FALSE(sp1 == sp2);
}

TEST(StringPieceTest_5, EqualityOperator_BothEmpty_5) {
  StringPiece sp1;
  StringPiece sp2;
  EXPECT_TRUE(sp1 == sp2);
}

TEST(StringPieceTest_5, EqualityOperator_EmptyStrings_5) {
  StringPiece sp1("");
  StringPiece sp2("");
  EXPECT_TRUE(sp1 == sp2);
}

// operator!=
TEST(StringPieceTest_5, InequalityOperator_DifferentContent_5) {
  StringPiece sp1("hello");
  StringPiece sp2("world");
  EXPECT_TRUE(sp1 != sp2);
}

TEST(StringPieceTest_5, InequalityOperator_SameContent_5) {
  StringPiece sp1("hello");
  StringPiece sp2("hello");
  EXPECT_FALSE(sp1 != sp2);
}

// AsString
TEST(StringPieceTest_5, AsString_ReturnsCorrectString_5) {
  StringPiece sp("hello");
  std::string result = sp.AsString();
  EXPECT_EQ(result, "hello");
}

TEST(StringPieceTest_5, AsString_PartialString_5) {
  const char* s = "hello world";
  StringPiece sp(s, 5);
  std::string result = sp.AsString();
  EXPECT_EQ(result, "hello");
}

TEST(StringPieceTest_5, AsString_EmptyStringPiece_5) {
  StringPiece sp("");
  std::string result = sp.AsString();
  EXPECT_EQ(result, "");
}

// begin() and end()
TEST(StringPieceTest_5, BeginEndIterators_5) {
  const char* s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(sp.begin(), s);
  EXPECT_EQ(sp.end(), s + 5);
}

TEST(StringPieceTest_5, BeginEndIterators_EmptyString_5) {
  const char* s = "";
  StringPiece sp(s);
  EXPECT_EQ(sp.begin(), sp.end());
}

TEST(StringPieceTest_5, IteratorTraversal_5) {
  StringPiece sp("abc");
  std::string result;
  for (StringPiece::const_iterator it = sp.begin(); it != sp.end(); ++it) {
    result += *it;
  }
  EXPECT_EQ(result, "abc");
}

// operator[]
TEST(StringPieceTest_5, IndexOperator_5) {
  StringPiece sp("hello");
  EXPECT_EQ(sp[0], 'h');
  EXPECT_EQ(sp[1], 'e');
  EXPECT_EQ(sp[2], 'l');
  EXPECT_EQ(sp[3], 'l');
  EXPECT_EQ(sp[4], 'o');
}

// size()
TEST(StringPieceTest_5, Size_5) {
  StringPiece sp("test");
  EXPECT_EQ(sp.size(), 4u);
}

TEST(StringPieceTest_5, SizeEmpty_5) {
  StringPiece sp;
  EXPECT_EQ(sp.size(), 0u);
}

// empty()
TEST(StringPieceTest_5, EmptyOnNonEmpty_5) {
  StringPiece sp("test");
  EXPECT_FALSE(sp.empty());
}

TEST(StringPieceTest_5, EmptyOnEmpty_5) {
  StringPiece sp("");
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_5, EmptyOnDefault_5) {
  StringPiece sp;
  EXPECT_TRUE(sp.empty());
}

// Boundary: single character string
TEST(StringPieceTest_5, SingleCharacter_5) {
  StringPiece sp("a");
  EXPECT_EQ(sp.size(), 1u);
  EXPECT_FALSE(sp.empty());
  EXPECT_EQ(sp[0], 'a');
  EXPECT_EQ(sp.begin() + 1, sp.end());
  EXPECT_EQ(sp.AsString(), "a");
}

// Equality with different underlying pointers but same content
TEST(StringPieceTest_5, EqualityDifferentPointers_5) {
  std::string s1 = "test";
  std::string s2 = "test";
  StringPiece sp1(s1);
  StringPiece sp2(s2);
  EXPECT_NE(sp1.str_, sp2.str_);  // Different pointers
  EXPECT_TRUE(sp1 == sp2);         // But equal content
}

// Partial overlap in content
TEST(StringPieceTest_5, PrefixSubstring_5) {
  const char* s = "hello";
  StringPiece full(s, 5);
  StringPiece prefix(s, 3);
  EXPECT_FALSE(full == prefix);
  EXPECT_TRUE(full != prefix);
}

// Construct from std::string preserves embedded data
TEST(StringPieceTest_5, StringWithSpaces_5) {
  std::string s = "hello world foo";
  StringPiece sp(s);
  EXPECT_EQ(sp.size(), s.size());
  EXPECT_EQ(sp.AsString(), s);
}

// Large string
TEST(StringPieceTest_5, LargeString_5) {
  std::string large(10000, 'x');
  StringPiece sp(large);
  EXPECT_EQ(sp.size(), 10000u);
  EXPECT_EQ(sp[0], 'x');
  EXPECT_EQ(sp[9999], 'x');
  EXPECT_EQ(sp.AsString(), large);
}

// String with null-like content via explicit length
TEST(StringPieceTest_5, ExplicitLengthBeyondNullByte_5) {
  const char data[] = {'a', '\0', 'b'};
  StringPiece sp(data, 3);
  EXPECT_EQ(sp.size(), 3u);
  EXPECT_EQ(sp[0], 'a');
  EXPECT_EQ(sp[1], '\0');
  EXPECT_EQ(sp[2], 'b');
}
