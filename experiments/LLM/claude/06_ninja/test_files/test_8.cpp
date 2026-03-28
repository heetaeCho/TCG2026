#include "string_piece.h"
#include <gtest/gtest.h>
#include <string>

// Test default constructor
TEST(StringPieceTest_8, DefaultConstructor_8) {
  StringPiece sp;
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_EQ(sp.str_, nullptr);
}

// Test constructor from std::string
TEST(StringPieceTest_8, StdStringConstructor_8) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_FALSE(sp.empty());
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_EQ(sp.AsString(), "hello");
}

// Test constructor from const char*
TEST(StringPieceTest_8, CStringConstructor_8) {
  StringPiece sp("world");
  EXPECT_FALSE(sp.empty());
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_EQ(sp.AsString(), "world");
}

// Test constructor from const char* with length
TEST(StringPieceTest_8, CStringWithLenConstructor_8) {
  const char* str = "hello world";
  StringPiece sp(str, 5);
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_EQ(sp.AsString(), "hello");
}

// Test empty string from std::string
TEST(StringPieceTest_8, EmptyStdString_8) {
  std::string s = "";
  StringPiece sp(s);
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_EQ(sp.AsString(), "");
}

// Test empty string from const char*
TEST(StringPieceTest_8, EmptyCString_8) {
  StringPiece sp("");
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.size(), 0u);
}

// Test equality operator with equal strings
TEST(StringPieceTest_8, EqualityOperatorEqual_8) {
  StringPiece sp1("hello");
  StringPiece sp2("hello");
  EXPECT_TRUE(sp1 == sp2);
  EXPECT_FALSE(sp1 != sp2);
}

// Test equality operator with different strings
TEST(StringPieceTest_8, EqualityOperatorNotEqual_8) {
  StringPiece sp1("hello");
  StringPiece sp2("world");
  EXPECT_FALSE(sp1 == sp2);
  EXPECT_TRUE(sp1 != sp2);
}

// Test equality operator with different lengths
TEST(StringPieceTest_8, EqualityOperatorDifferentLengths_8) {
  StringPiece sp1("hello");
  StringPiece sp2("hell");
  EXPECT_FALSE(sp1 == sp2);
  EXPECT_TRUE(sp1 != sp2);
}

// Test equality of two empty StringPieces
TEST(StringPieceTest_8, EqualityEmptyPieces_8) {
  StringPiece sp1;
  StringPiece sp2;
  EXPECT_TRUE(sp1 == sp2);
}

// Test AsString
TEST(StringPieceTest_8, AsString_8) {
  StringPiece sp("test string");
  std::string result = sp.AsString();
  EXPECT_EQ(result, "test string");
}

// Test AsString with partial string
TEST(StringPieceTest_8, AsStringPartial_8) {
  const char* str = "hello world";
  StringPiece sp(str, 5);
  EXPECT_EQ(sp.AsString(), "hello");
}

// Test begin and end iterators
TEST(StringPieceTest_8, BeginEnd_8) {
  StringPiece sp("abc");
  EXPECT_EQ(sp.end() - sp.begin(), 3);
  EXPECT_EQ(*sp.begin(), 'a');
  EXPECT_EQ(*(sp.end() - 1), 'c');
}

// Test begin and end for empty piece
TEST(StringPieceTest_8, BeginEndEmpty_8) {
  StringPiece sp("");
  EXPECT_EQ(sp.begin(), sp.end());
}

// Test operator[]
TEST(StringPieceTest_8, IndexOperator_8) {
  StringPiece sp("abcdef");
  EXPECT_EQ(sp[0], 'a');
  EXPECT_EQ(sp[1], 'b');
  EXPECT_EQ(sp[5], 'f');
}

// Test size
TEST(StringPieceTest_8, Size_8) {
  StringPiece sp("twelve chars");
  EXPECT_EQ(sp.size(), 12u);
}

// Test size of default constructed
TEST(StringPieceTest_8, SizeDefault_8) {
  StringPiece sp;
  EXPECT_EQ(sp.size(), 0u);
}

// Test with embedded null character using explicit length
TEST(StringPieceTest_8, EmbeddedNull_8) {
  const char data[] = "hel\0lo";
  StringPiece sp(data, 6);
  EXPECT_EQ(sp.size(), 6u);
  EXPECT_FALSE(sp.empty());
  EXPECT_EQ(sp[3], '\0');
  EXPECT_EQ(sp[4], 'l');
}

// Test inequality between StringPiece with same prefix but different lengths
TEST(StringPieceTest_8, PrefixInequality_8) {
  StringPiece sp1("abc");
  StringPiece sp2("abcdef");
  EXPECT_FALSE(sp1 == sp2);
  EXPECT_TRUE(sp1 != sp2);
}

// Test single character string
TEST(StringPieceTest_8, SingleCharacter_8) {
  StringPiece sp("x");
  EXPECT_EQ(sp.size(), 1u);
  EXPECT_FALSE(sp.empty());
  EXPECT_EQ(sp[0], 'x');
  EXPECT_EQ(sp.AsString(), "x");
}

// Test range-based iteration
TEST(StringPieceTest_8, RangeIteration_8) {
  StringPiece sp("abc");
  std::string result;
  for (auto it = sp.begin(); it != sp.end(); ++it) {
    result += *it;
  }
  EXPECT_EQ(result, "abc");
}

// Test zero-length StringPiece with non-null pointer
TEST(StringPieceTest_8, ZeroLengthNonNull_8) {
  const char* str = "hello";
  StringPiece sp(str, 0);
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_EQ(sp.AsString(), "");
}

// Test equality with std::string-constructed vs char*-constructed
TEST(StringPieceTest_8, CrossConstructorEquality_8) {
  std::string s = "test";
  StringPiece sp1(s);
  StringPiece sp2("test");
  EXPECT_TRUE(sp1 == sp2);
}
