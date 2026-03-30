// File: string_piece_empty_test_8.cc

#include <gtest/gtest.h>
#include <string>
#include "string_piece.h"

class StringPieceTest_8 : public ::testing::Test {
protected:
  // Common setup/teardown if needed later
};

// Normal operation: default-constructed StringPiece is empty.
TEST_F(StringPieceTest_8, DefaultConstructorIsEmpty_8) {
  StringPiece sp;
  EXPECT_NE(static_cast<size_t>(0), sp.empty());  // non-zero means "true"
}

// Normal operation: StringPiece from non-empty std::string is not empty.
TEST_F(StringPieceTest_8, NonEmptyStdStringIsNotEmpty_8) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(static_cast<size_t>(0), sp.empty());  // zero means "false"
}

// Boundary: StringPiece from empty std::string is empty.
TEST_F(StringPieceTest_8, EmptyStdStringIsEmpty_8) {
  std::string s = "";
  StringPiece sp(s);
  EXPECT_NE(static_cast<size_t>(0), sp.empty());
}

// Normal operation: StringPiece from non-empty C-string is not empty.
TEST_F(StringPieceTest_8, NonEmptyCStringIsNotEmpty_8) {
  const char* s = "world";
  StringPiece sp(s);
  EXPECT_EQ(static_cast<size_t>(0), sp.empty());
}

// Boundary: StringPiece from C-string + explicit zero length is empty.
TEST_F(StringPieceTest_8, CStringWithZeroLengthIsEmpty_8) {
  const char* s = "data";
  StringPiece sp(s, 0u);
  EXPECT_NE(static_cast<size_t>(0), sp.empty());
}

// Normal operation: StringPiece from C-string + non-zero length is not empty.
TEST_F(StringPieceTest_8, CStringWithNonZeroLengthIsNotEmpty_8) {
  const char* s = "data";
  StringPiece sp(s, 4u);
  EXPECT_EQ(static_cast<size_t>(0), sp.empty());
}

// Consistency check: empty() agrees with size() for several constructions.
TEST_F(StringPieceTest_8, EmptyConsistentWithSize_8) {
  // default-constructed
  StringPiece sp_default;
  EXPECT_EQ(static_cast<size_t>(0), sp_default.size());
  EXPECT_NE(static_cast<size_t>(0), sp_default.empty());

  // empty std::string
  std::string empty_str;
  StringPiece sp_empty_str(empty_str);
  EXPECT_EQ(static_cast<size_t>(0), sp_empty_str.size());
  EXPECT_NE(static_cast<size_t>(0), sp_empty_str.empty());

  // non-empty std::string
  std::string non_empty_str = "abc";
  StringPiece sp_non_empty(non_empty_str);
  EXPECT_EQ(static_cast<size_t>(3), sp_non_empty.size());
  EXPECT_EQ(static_cast<size_t>(0), sp_non_empty.empty());
}
