#include <gtest/gtest.h>
#include <string>
#include "string_piece.h"

// Test fixture for StringPiece::begin() tests (TEST_ID = 4)
class StringPieceBeginTest_4 : public ::testing::Test {};

// begin() on a StringPiece constructed from std::string
// should point to the first character and allow reconstructing the string.
TEST_F(StringPieceBeginTest_4,
       BeginOnStdStringConstructedPiecePointsToFirstChar_4) {
  const std::string original = "hello world";
  StringPiece piece(original);

  ASSERT_EQ(original.size(), piece.size());
  ASSERT_FALSE(piece.empty());

  // begin() should point to the first character
  EXPECT_EQ(original[0], *piece.begin());

  // Iteration from begin() to end() should reconstruct the same string
  std::string reconstructed(piece.begin(), piece.end());
  EXPECT_EQ(original, reconstructed);

  // AsString() should be consistent with the range [begin(), end())
  EXPECT_EQ(piece.AsString(), reconstructed);
}

// begin() on a StringPiece constructed from const char*
// should point to the first character and match AsString().
TEST_F(StringPieceBeginTest_4,
       BeginOnConstCharConstructedPiecePointsToFirstChar_4) {
  const char* cstr = "string piece test";
  StringPiece piece(cstr);

  ASSERT_EQ(std::strlen(cstr), piece.size());
  ASSERT_FALSE(piece.empty());

  // begin() should point to the first character
  EXPECT_EQ(cstr[0], *piece.begin());

  // Range [begin(), end()) should match the original C-string
  std::string from_iterators(piece.begin(), piece.end());
  EXPECT_EQ(std::string(cstr), from_iterators);

  // Consistency with AsString()
  EXPECT_EQ(piece.AsString(), from_iterators);
}

// begin() on a default-constructed StringPiece
// should denote an empty range and equal end().
TEST_F(StringPieceBeginTest_4,
       BeginOnDefaultConstructedPieceEqualsEndForEmpty_4) {
  StringPiece piece;

  EXPECT_TRUE(piece.empty());
  EXPECT_EQ(static_cast<size_t>(0), piece.size());

  // For an empty piece, begin() and end() should be the same iterator.
  EXPECT_EQ(piece.begin(), piece.end());
}

// begin() on a StringPiece constructed with (const char*, size)
// should correctly handle explicit length, including embedded '\0'.
TEST_F(StringPieceBeginTest_4,
       BeginOnExplicitLengthConstructedPieceHandlesEmbeddedNulls_4) {
  const char buffer[] = { 'a', 'b', '\0', 'c', 'd' };
  const size_t len = sizeof(buffer) / sizeof(buffer[0]);  // 5

  StringPiece piece(buffer, len);

  ASSERT_EQ(len, piece.size());
  ASSERT_FALSE(piece.empty());

  // begin() should point to the first character
  EXPECT_EQ(buffer[0], *piece.begin());

  // begin() + i should correspond to operator[](i) for valid indices
  for (size_t i = 0; i < piece.size(); ++i) {
    EXPECT_EQ(piece[i], *(piece.begin() + i)) << "Mismatch at index " << i;
  }
}

// begin() on a StringPiece constructed with (const char*, 0)
// should represent an empty range and equal end().
TEST_F(StringPieceBeginTest_4,
       BeginOnZeroLengthConstructedPieceEqualsEnd_4) {
  const char* data = "abcde";
  StringPiece piece(data, 0);

  EXPECT_TRUE(piece.empty());
  EXPECT_EQ(static_cast<size_t>(0), piece.size());
  EXPECT_EQ(piece.begin(), piece.end());
}
