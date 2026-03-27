#include <gtest/gtest.h>
#include <string>
#include "string_piece.h"

// Test fixture for TEST_ID 7
class StringPieceTest_7 : public ::testing::Test {};

// Default-constructed StringPiece should have size 0.
TEST_F(StringPieceTest_7, DefaultConstructedHasZeroSize_7) {
  StringPiece sp;
  EXPECT_EQ(0u, sp.size());
}

// Constructed from std::string: size() should match the std::string's size.
TEST_F(StringPieceTest_7, FromStdStringMatchesStringSize_7) {
  std::string src = "hello world";
  StringPiece sp(src);

  EXPECT_EQ(src.size(), sp.size());
}

// Constructed from C-string literal: size() should match strlen of the literal.
TEST_F(StringPieceTest_7, FromCStringLiteralReturnsCorrectSize_7) {
  const char* cstr = "ninja";
  StringPiece sp(cstr);

  EXPECT_EQ(std::strlen(cstr), sp.size());
}

// Constructed from (const char*, size_t): size() should equal the provided length
// even if the data contains embedded null characters (boundary/edge behavior).
TEST_F(StringPieceTest_7, FromPointerAndLengthUsesProvidedLength_7) {
  const char buffer[] = { 'a', '\0', 'b', 'c' };
  const size_t len = sizeof(buffer);  // 4
  StringPiece sp(buffer, len);

  EXPECT_EQ(len, sp.size());
}

// Constructed from empty C-string: size() should be 0.
TEST_F(StringPieceTest_7, FromEmptyCStringHasZeroSize_7) {
  const char* empty = "";
  StringPiece sp(empty);

  EXPECT_EQ(0u, sp.size());
}

// Large std::string input: size() should still match input size.
TEST_F(StringPieceTest_7, LargeStringSizeMatchesInput_7) {
  std::string large(1000, 'x');
  StringPiece sp(large);

  EXPECT_EQ(large.size(), sp.size());
}
