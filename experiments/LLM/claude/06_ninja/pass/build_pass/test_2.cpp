#include "gtest/gtest.h"
#include "string_piece.h"
#include <string>

// Test default constructor
TEST(StringPieceTest_2, DefaultConstructor_2) {
  StringPiece sp;
  EXPECT_EQ(nullptr, sp.str_);
  EXPECT_EQ(0u, sp.len_);
}

// Test construction from std::string
TEST(StringPieceTest_2, ConstructFromStdString_2) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(s.data(), sp.str_);
  EXPECT_EQ(s.size(), sp.len_);
}

// Test construction from const char*
TEST(StringPieceTest_2, ConstructFromCString_2) {
  const char* s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(s, sp.str_);
  EXPECT_EQ(5u, sp.len_);
}

// Test construction from const char* and length
TEST(StringPieceTest_2, ConstructFromCStringAndLength_2) {
  const char* s = "hello world";
  StringPiece sp(s, 5);
  EXPECT_EQ(s, sp.str_);
  EXPECT_EQ(5u, sp.len_);
}

// Test equality operator with equal strings
TEST(StringPieceTest_2, EqualityOperator_Equal_2) {
  StringPiece a("hello");
  StringPiece b("hello");
  EXPECT_TRUE(a == b);
}

// Test equality operator with different strings
TEST(StringPieceTest_2, EqualityOperator_NotEqual_2) {
  StringPiece a("hello");
  StringPiece b("world");
  EXPECT_FALSE(a == b);
}

// Test equality operator with different lengths
TEST(StringPieceTest_2, EqualityOperator_DifferentLengths_2) {
  StringPiece a("hello");
  StringPiece b("hell");
  EXPECT_FALSE(a == b);
}

// Test inequality operator with equal strings
TEST(StringPieceTest_2, InequalityOperator_Equal_2) {
  StringPiece a("hello");
  StringPiece b("hello");
  EXPECT_FALSE(a != b);
}

// Test inequality operator with different strings
TEST(StringPieceTest_2, InequalityOperator_NotEqual_2) {
  StringPiece a("hello");
  StringPiece b("world");
  EXPECT_TRUE(a != b);
}

// Test AsString
TEST(StringPieceTest_2, AsString_2) {
  StringPiece sp("hello");
  std::string s = sp.AsString();
  EXPECT_EQ("hello", s);
}

// Test AsString with partial string
TEST(StringPieceTest_2, AsStringPartial_2) {
  StringPiece sp("hello world", 5);
  std::string s = sp.AsString();
  EXPECT_EQ("hello", s);
}

// Test begin and end iterators
TEST(StringPieceTest_2, BeginEnd_2) {
  StringPiece sp("hello");
  EXPECT_EQ(sp.str_, sp.begin());
  EXPECT_EQ(sp.str_ + 5, sp.end());
}

// Test iterator range produces correct characters
TEST(StringPieceTest_2, IteratorRange_2) {
  StringPiece sp("abc");
  std::string result(sp.begin(), sp.end());
  EXPECT_EQ("abc", result);
}

// Test operator[]
TEST(StringPieceTest_2, IndexOperator_2) {
  StringPiece sp("hello");
  EXPECT_EQ('h', sp[0]);
  EXPECT_EQ('e', sp[1]);
  EXPECT_EQ('l', sp[2]);
  EXPECT_EQ('l', sp[3]);
  EXPECT_EQ('o', sp[4]);
}

// Test size
TEST(StringPieceTest_2, Size_2) {
  StringPiece sp("hello");
  EXPECT_EQ(5u, sp.size());
}

// Test size of empty string
TEST(StringPieceTest_2, SizeEmpty_2) {
  StringPiece sp("");
  EXPECT_EQ(0u, sp.size());
}

// Test empty on non-empty string
TEST(StringPieceTest_2, EmptyFalse_2) {
  StringPiece sp("hello");
  EXPECT_FALSE(sp.empty());
}

// Test empty on empty string
TEST(StringPieceTest_2, EmptyTrue_2) {
  StringPiece sp("");
  EXPECT_TRUE(sp.empty());
}

// Test empty on default constructed
TEST(StringPieceTest_2, EmptyDefaultConstructed_2) {
  StringPiece sp;
  EXPECT_TRUE(sp.empty());
}

// Test equality of empty StringPieces
TEST(StringPieceTest_2, EqualityEmptyPieces_2) {
  StringPiece a("");
  StringPiece b("");
  EXPECT_TRUE(a == b);
}

// Test equality with same content different sources
TEST(StringPieceTest_2, EqualitySameContentDifferentSources_2) {
  std::string s1 = "test";
  std::string s2 = "test";
  StringPiece a(s1);
  StringPiece b(s2);
  EXPECT_TRUE(a == b);
}

// Test inequality of different lengths same prefix
TEST(StringPieceTest_2, InequalityDifferentLengthsSamePrefix_2) {
  StringPiece a("hello");
  StringPiece b("hello!");
  EXPECT_TRUE(a != b);
}

// Test construction from std::string preserves embedded data
TEST(StringPieceTest_2, ConstructFromStdStringWithLength_2) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(5u, sp.size());
  EXPECT_EQ('h', sp[0]);
  EXPECT_EQ('o', sp[4]);
}

// Test single character StringPiece
TEST(StringPieceTest_2, SingleCharacter_2) {
  StringPiece sp("x");
  EXPECT_EQ(1u, sp.size());
  EXPECT_EQ('x', sp[0]);
  EXPECT_FALSE(sp.empty());
}

// Test AsString on empty StringPiece
TEST(StringPieceTest_2, AsStringEmpty_2) {
  StringPiece sp("");
  EXPECT_EQ("", sp.AsString());
}

// Test begin equals end for empty StringPiece
TEST(StringPieceTest_2, BeginEqualsEndForEmpty_2) {
  StringPiece sp("");
  EXPECT_EQ(sp.begin(), sp.end());
}

// Test self equality
TEST(StringPieceTest_2, SelfEquality_2) {
  StringPiece sp("test");
  EXPECT_TRUE(sp == sp);
  EXPECT_FALSE(sp != sp);
}

// Test substring via pointer and length constructor
TEST(StringPieceTest_2, SubstringConstruction_2) {
  const char* full = "hello world";
  StringPiece sp(full + 6, 5);
  EXPECT_EQ("world", sp.AsString());
  EXPECT_EQ(5u, sp.size());
}
