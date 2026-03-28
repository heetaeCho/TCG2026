#include "gtest/gtest.h"

#include "string_piece.h"
#include "string_piece_util.h"  // Assuming JoinStringPiece is declared here

// Basic behavior: empty list should return an empty std::string.
TEST(JoinStringPieceTest_125, EmptyListReturnsEmptyString_125) {
  std::vector<StringPiece> pieces;

  std::string result = JoinStringPiece(pieces, ',');

  EXPECT_TRUE(result.empty());
}

// Single element: no separator should be inserted.
TEST(JoinStringPieceTest_125, SingleElementNoSeparator_125) {
  std::vector<StringPiece> pieces;
  pieces.push_back(StringPiece("hello"));

  std::string result = JoinStringPiece(pieces, ',');

  EXPECT_EQ(std::string("hello"), result);
}

// Multiple elements: separator should appear between all elements, but not at ends.
TEST(JoinStringPieceTest_125, MultipleElementsWithSeparator_125) {
  std::vector<StringPiece> pieces;
  pieces.push_back(StringPiece("hello"));
  pieces.push_back(StringPiece("world"));
  pieces.push_back(StringPiece("ninja"));

  std::string result = JoinStringPiece(pieces, '-');

  EXPECT_EQ(std::string("hello-world-ninja"), result);
}

// Handles empty StringPiece elements: separators still inserted between positions.
TEST(JoinStringPieceTest_125, HandlesEmptyStringPieces_125) {
  std::vector<StringPiece> pieces;
  pieces.push_back(StringPiece("first"));
  pieces.push_back(StringPiece("", 0));  // explicit empty piece
  pieces.push_back(StringPiece("third"));

  std::string result = JoinStringPiece(pieces, ',');

  // Expected: "first,,third" (empty segment in the middle)
  EXPECT_EQ(std::string("first,,third"), result);
}

// Supports StringPiece constructed from different sources: std::string, const char*, (ptr,len).
TEST(JoinStringPieceTest_125, SupportsVariousStringPieceConstructors_125) {
  std::string base = std::string("stdstring");
  const char* literal = "literal";

  const char raw_data[] = {'r', 'a', 'w', '3'};
  StringPiece sp1(base);                 // from std::string
  StringPiece sp2(literal);              // from const char*
  StringPiece sp3(raw_data, sizeof raw_data);  // from (ptr,len)

  std::vector<StringPiece> pieces;
  pieces.push_back(sp1);
  pieces.push_back(sp2);
  pieces.push_back(sp3);

  std::string result = JoinStringPiece(pieces, '|');

  std::string expected;
  expected.append(base);
  expected.push_back('|');
  expected.append(literal);
  expected.push_back('|');
  expected.append(raw_data, sizeof raw_data);

  EXPECT_EQ(expected, result);
}

// Handles embedded null characters in StringPiece contents and/or separator.
TEST(JoinStringPieceTest_125, HandlesEmbeddedNullCharacters_125) {
  const char data1[] = {'a', '\0', 'b'};
  const char data2[] = {'X', 'Y', '\0'};

  StringPiece sp1(data1, sizeof data1);
  StringPiece sp2(data2, sizeof data2);

  std::vector<StringPiece> pieces;
  pieces.push_back(sp1);
  pieces.push_back(sp2);

  // Use a normal separator here; embedded nulls are inside the pieces.
  std::string result = JoinStringPiece(pieces, '-');

  std::string expected;
  expected.append(data1, sizeof data1);
  expected.push_back('-');
  expected.append(data2, sizeof data2);

  // Compare as std::string (supports embedded nulls)
  EXPECT_EQ(expected.size(), result.size());
  EXPECT_EQ(expected, result);
}

// Uses a null character as the separator; result should include that separator.
TEST(JoinStringPieceTest_125, NullCharacterAsSeparator_125) {
  std::vector<StringPiece> pieces;
  pieces.push_back(StringPiece("AA"));
  pieces.push_back(StringPiece("BB"));

  char sep = '\0';
  std::string result = JoinStringPiece(pieces, sep);

  // Expected bytes: 'A','A','\0','B','B'
  std::string expected;
  expected.append("AA");
  expected.push_back('\0');
  expected.append("BB");

  EXPECT_EQ(expected.size(), result.size());
  EXPECT_EQ(expected, result);
}

// Large input: verifies that JoinStringPiece can handle many elements without failure.
TEST(JoinStringPieceTest_125, HandlesLargeNumberOfElements_125) {
  const size_t kCount = 1000;
  std::vector<StringPiece> pieces;
  pieces.reserve(kCount);

  for (size_t i = 0; i < kCount; ++i) {
    pieces.push_back(StringPiece("x"));
  }

  std::string result = JoinStringPiece(pieces, ',');

  // Result should have kCount 'x' characters and kCount - 1 separators.
  size_t expected_size = kCount + (kCount - 1);
  EXPECT_EQ(expected_size, result.size());

  // Check first, some middle, and last positions for correctness.
  EXPECT_EQ('x', result[0]);
  EXPECT_EQ(',', result[1]);
  EXPECT_EQ('x', result[2]);
  EXPECT_EQ('x', result[result.size() - 1]);
}
