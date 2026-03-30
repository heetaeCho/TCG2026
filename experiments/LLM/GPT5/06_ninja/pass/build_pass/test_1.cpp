// File: string_piece_equal_test_1.cc

#include <gtest/gtest.h>
#include <string>
#include "string_piece.h"

namespace {

class StringPieceTest_1 : public ::testing::Test {
protected:
  // No special setup/teardown needed for these tests.
};

// Self-comparison should always be equal.
TEST_F(StringPieceTest_1, SelfEquality_1) {
  StringPiece piece("hello");
  EXPECT_TRUE(piece == piece);
}

// Two StringPieces constructed from the same std::string
// should be equal.
TEST_F(StringPieceTest_1, EqualWhenConstructedFromSameStdString_1) {
  std::string str = "ninja";
  StringPiece a(str);
  StringPiece b(str);

  EXPECT_TRUE(a == b);
}

// Two StringPieces constructed using different constructors
// but with the same character sequence should be equal.
TEST_F(StringPieceTest_1, EqualWithDifferentConstructorsSameContent_1) {
  std::string str = "build";
  StringPiece from_std(str);
  StringPiece from_cstr(str.c_str());
  StringPiece from_ptr_len(str.data(), str.size());

  EXPECT_TRUE(from_std == from_cstr);
  EXPECT_TRUE(from_std == from_ptr_len);
  EXPECT_TRUE(from_cstr == from_ptr_len);
}

// StringPieces of different logical lengths must not be equal.
TEST_F(StringPieceTest_1, NotEqualWhenLengthsDiffer_1) {
  StringPiece short_piece("hello");
  StringPiece long_piece("hello world");

  EXPECT_FALSE(short_piece == long_piece);
  EXPECT_FALSE(long_piece == short_piece);
}

// StringPieces with the same length but different contents
// should not be equal.
TEST_F(StringPieceTest_1, NotEqualWhenContentsDifferSameLength_1) {
  StringPiece piece1("hello");
  StringPiece piece2("hxllo");  // same length, different content

  EXPECT_FALSE(piece1 == piece2);
  EXPECT_FALSE(piece2 == piece1);
}

// Empty StringPieces from various constructors should all be equal.
TEST_F(StringPieceTest_1, EmptyStringPiecesAreEqual_1) {
  StringPiece default_piece;             // default constructor
  StringPiece empty_cstr("");           // from C-string
  std::string empty_std;
  StringPiece empty_std_piece(empty_std);  // from std::string
  StringPiece empty_ptr_len("abc", 0);  // explicit zero length

  EXPECT_TRUE(default_piece == empty_cstr);
  EXPECT_TRUE(default_piece == empty_std_piece);
  EXPECT_TRUE(default_piece == empty_ptr_len);
  EXPECT_TRUE(empty_cstr == empty_std_piece);
  EXPECT_TRUE(empty_cstr == empty_ptr_len);
  EXPECT_TRUE(empty_std_piece == empty_ptr_len);
}

// StringPieces with embedded null characters should compare based on
// the explicit length (constructor with (const char*, size_t)).
TEST_F(StringPieceTest_1, EmbeddedNullCharactersRespected_1) {
  const char data1[] = { 'a', '\0', 'b', 'c' };
  const char data2[] = { 'a', '\0', 'b', 'c' };
  const char data3[] = { 'a', '\0', 'x', 'c' };  // differs in one position

  StringPiece piece1(data1, sizeof(data1));
  StringPiece piece2(data2, sizeof(data2));
  StringPiece piece3(data3, sizeof(data3));

  // Same bytes, same length => equal
  EXPECT_TRUE(piece1 == piece2);

  // Same length, different bytes => not equal
  EXPECT_FALSE(piece1 == piece3);
  EXPECT_FALSE(piece2 == piece3);
}

// Basic consistency check between operator== and operator!=
// using only their observable behavior.
TEST_F(StringPieceTest_1, EqualityConsistentWithInequalityOperator_1) {
  StringPiece a("config");
  StringPiece b("config");
  StringPiece c("confix");

  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a != b);

  EXPECT_FALSE(a == c);
  EXPECT_TRUE(a != c);
}

}  // namespace
