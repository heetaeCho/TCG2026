// File: string_piece_operator_index_test_6.cc

#include <string>
#include "gtest/gtest.h"
#include "string_piece.h"

class StringPieceTest_6 : public ::testing::Test {};

// Normal operation: indexing characters from a std::string-based StringPiece
TEST_F(StringPieceTest_6, IndexingFromStdStringReturnsCorrectCharacters_6) {
  std::string source = "hello";
  StringPiece piece(source);

  EXPECT_EQ('h', piece[0]);
  EXPECT_EQ('e', piece[1]);
  EXPECT_EQ('l', piece[2]);
  EXPECT_EQ('l', piece[3]);
  EXPECT_EQ('o', piece[4]);
}

// Normal operation: indexing characters from a const char* based StringPiece
TEST_F(StringPieceTest_6, IndexingFromCStringReturnsCorrectCharacters_6) {
  const char* source = "world";
  StringPiece piece(source);

  EXPECT_EQ('w', piece[0]);
  EXPECT_EQ('o', piece[1]);
  EXPECT_EQ('r', piece[2]);
  EXPECT_EQ('l', piece[3]);
  EXPECT_EQ('d', piece[4]);
}

// Boundary conditions: first and last valid indices
TEST_F(StringPieceTest_6, IndexingFirstAndLastCharacter_6) {
  const char* source = "boundary";
  StringPiece piece(source);

  ASSERT_GT(piece.size(), static_cast<size_t>(0));
  size_t last_index = piece.size() - 1;

  EXPECT_EQ('b', piece[0]);
  EXPECT_EQ('y', piece[last_index]);
}

// Normal operation: indexing for a StringPiece constructed with (ptr, len)
TEST_F(StringPieceTest_6, IndexingRespectsProvidedLength_6) {
  const char* source = "abcdef";
  // Create a view "bcd"
  StringPiece piece(source + 1, 3);

  ASSERT_EQ(static_cast<size_t>(3), piece.size());

  EXPECT_EQ('b', piece[0]);
  EXPECT_EQ('c', piece[1]);
  EXPECT_EQ('d', piece[2]);
}

// Normal operation: indexing on a const instance (const-correctness)
TEST_F(StringPieceTest_6, IndexingOnConstInstance_6) {
  const StringPiece piece("xyz");

  char c0 = piece[0];
  char c1 = piece[1];
  char c2 = piece[2];

  EXPECT_EQ('x', c0);
  EXPECT_EQ('y', c1);
  EXPECT_EQ('z', c2);
}

// Normal operation / boundary-like case: supports embedded null characters
TEST_F(StringPieceTest_6, IndexingEmbeddedNullCharacters_6) {
  const char buffer[] = { 'a', '\0', 'b' };
  StringPiece piece(buffer, 3);

  ASSERT_EQ(static_cast<size_t>(3), piece.size());

  EXPECT_EQ('a', piece[0]);
  EXPECT_EQ('\0', piece[1]);
  EXPECT_EQ('b', piece[2]);
}
