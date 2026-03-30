// File: string_piece_as_string_test_3.cc

#include <gtest/gtest.h>
#include <string>

#include "string_piece.h"

// We treat StringPiece as a black box and only use its public interface.

TEST(StringPieceTest_3, AsStringFromDefaultConstructedIsEmpty_3) {
  StringPiece piece;  // default constructor

  std::string result = piece.AsString();

  EXPECT_TRUE(result.empty());
  EXPECT_EQ(result.size(), static_cast<size_t>(0));
}

TEST(StringPieceTest_3, AsStringFromStdStringCopiesContent_3) {
  std::string original = "hello world";
  StringPiece piece(original);

  std::string result = piece.AsString();

  EXPECT_EQ(result, original);
  EXPECT_EQ(result.size(), original.size());
}

TEST(StringPieceTest_3, AsStringFromCStringCopiesContent_3) {
  const char* cstr = "ninja";
  StringPiece piece(cstr);

  std::string result = piece.AsString();

  EXPECT_EQ(result, std::string("ninja"));
  EXPECT_EQ(result.size(), static_cast<size_t>(5));
}

TEST(StringPieceTest_3, AsStringFromPointerAndLengthUsesGivenLength_3) {
  const char* cstr = "abcdef";
  // Only take first 3 characters
  StringPiece piece(cstr, 3);

  std::string result = piece.AsString();

  EXPECT_EQ(result, std::string("abc"));
  EXPECT_EQ(result.size(), static_cast<size_t>(3));
}

TEST(StringPieceTest_3, AsStringFromPointerAndZeroLengthIsEmpty_3) {
  const char* cstr = "some text";
  StringPiece piece(cstr, 0);

  std::string result = piece.AsString();

  EXPECT_TRUE(result.empty());
  EXPECT_EQ(result.size(), static_cast<size_t>(0));
}

TEST(StringPieceTest_3, AsStringPreservesEmbeddedNullCharacters_3) {
  // Create a std::string with an embedded null character.
  std::string with_null("ab\0cd", 5);
  StringPiece piece(with_null);

  std::string result = piece.AsString();

  // Compare as std::string to handle embedded '\0' safely.
  EXPECT_EQ(result.size(), with_null.size());
  EXPECT_EQ(result, with_null);
}
