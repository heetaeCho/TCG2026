// File: string_piece_end_test_5.cc

#include "gtest/gtest.h"
#include "string_piece.h"

// Fixture for TEST_ID = 5
class StringPieceEndTest_5 : public ::testing::Test {};

// Normal case: non-empty string, end() marks one-past-last element in iteration.
TEST_F(StringPieceEndTest_5, EndIteratesOverAllCharacters_5) {
  const std::string source = "hello";
  StringPiece piece(source);

  std::string iterated;
  for (StringPiece::const_iterator it = piece.begin(); it != piece.end(); ++it) {
    iterated.push_back(*it);
  }

  EXPECT_EQ(source, iterated);
  EXPECT_EQ(source.size(), iterated.size());
}

// Boundary case: empty StringPiece via default constructor, begin() == end().
TEST_F(StringPieceEndTest_5, EmptyDefaultConstructedBeginEqualsEnd_5) {
  StringPiece piece;

  EXPECT_EQ(piece.begin(), piece.end());

  // Also verify no iteration occurs.
  std::string iterated;
  for (StringPiece::const_iterator it = piece.begin(); it != piece.end(); ++it) {
    iterated.push_back(*it);
  }
  EXPECT_TRUE(iterated.empty());
}

// Boundary case: empty StringPiece from explicit length 0, begin() == end().
TEST_F(StringPieceEndTest_5, EmptyExplicitLengthBeginEqualsEnd_5) {
  const char* cstr = "abc";  // non-empty source, but explicit length 0
  StringPiece piece(cstr, 0);

  EXPECT_EQ(piece.begin(), piece.end());
  EXPECT_EQ(0u, piece.size());

  std::string iterated;
  for (StringPiece::const_iterator it = piece.begin(); it != piece.end(); ++it) {
    iterated.push_back(*it);
  }
  EXPECT_TRUE(iterated.empty());
}

// Boundary / special-content case: explicit length with embedded nulls.
// Verifies that end() respects the length rather than C-string terminator.
TEST_F(StringPieceEndTest_5, EndRespectsExplicitLengthWithEmbeddedNull_5) {
  const char data[] = { 'a', '\0', 'b', 'c' };
  StringPiece piece(data, sizeof(data));

  // Iterate using begin() / end() and collect characters.
  std::string iterated;
  for (StringPiece::const_iterator it = piece.begin(); it != piece.end(); ++it) {
    iterated.push_back(*it);
  }

  // AsString() should represent the same sequence as [begin, end).
  std::string as_string = piece.AsString();

  EXPECT_EQ(sizeof(data), iterated.size());
  EXPECT_EQ(sizeof(data), as_string.size());

  EXPECT_EQ(iterated, as_string);
  EXPECT_EQ('a', iterated[0]);
  EXPECT_EQ('\0', iterated[1]);
  EXPECT_EQ('b', iterated[2]);
  EXPECT_EQ('c', iterated[3]);
}

// Consistency case: end() is stable and works correctly after copying StringPiece.
TEST_F(StringPieceEndTest_5, EndWorksAfterCopyConstruction_5) {
  const std::string source = "copy-test";
  StringPiece original(source);
  StringPiece copy = original;  // use copy construction / assignment

  std::string iterated_original;
  for (StringPiece::const_iterator it = original.begin(); it != original.end(); ++it) {
    iterated_original.push_back(*it);
  }

  std::string iterated_copy;
  for (StringPiece::const_iterator it = copy.begin(); it != copy.end(); ++it) {
    iterated_copy.push_back(*it);
  }

  EXPECT_EQ(source, iterated_original);
  EXPECT_EQ(source, iterated_copy);
  EXPECT_EQ(iterated_original, iterated_copy);
}
