// File: string_piece_util_test_124.cc

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "string_piece.h"
#include "string_piece_util.h"

using std::string;
using std::vector;

class SplitStringPieceTest_124 : public ::testing::Test {};

// Empty input -> single empty token
TEST_F(SplitStringPieceTest_124, EmptyInputReturnsSingleEmptyToken_124) {
  StringPiece input("");
  vector<StringPiece> result = SplitStringPiece(input, ',');

  ASSERT_EQ(result.size(), 1u);
  EXPECT_TRUE(result[0].empty());
  EXPECT_EQ(result[0].AsString(), string());
}

// No separator present -> whole string as one token
TEST_F(SplitStringPieceTest_124, NoSeparatorReturnsWholeString_124) {
  StringPiece input("abc");
  vector<StringPiece> result = SplitStringPiece(input, ',');

  ASSERT_EQ(result.size(), 1u);
  EXPECT_FALSE(result[0].empty());
  EXPECT_EQ(result[0].AsString(), string("abc"));
}

// Simple comma-separated string
TEST_F(SplitStringPieceTest_124, SimpleCommaSeparatedString_124) {
  StringPiece input("a,b,c");
  vector<StringPiece> result = SplitStringPiece(input, ',');

  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0].AsString(), string("a"));
  EXPECT_EQ(result[1].AsString(), string("b"));
  EXPECT_EQ(result[2].AsString(), string("c"));
}

// Leading and trailing separators produce empty tokens
TEST_F(SplitStringPieceTest_124, LeadingAndTrailingSeparators_124) {
  StringPiece input(",a,b,");
  vector<StringPiece> result = SplitStringPiece(input, ',');

  ASSERT_EQ(result.size(), 4u);
  EXPECT_EQ(result[0].AsString(), string(""));
  EXPECT_EQ(result[1].AsString(), string("a"));
  EXPECT_EQ(result[2].AsString(), string("b"));
  EXPECT_EQ(result[3].AsString(), string(""));
}

// Consecutive separators produce empty tokens between them
TEST_F(SplitStringPieceTest_124, ConsecutiveSeparatorsYieldEmptyTokens_124) {
  StringPiece input("a,,b");
  vector<StringPiece> result = SplitStringPiece(input, ',');

  ASSERT_EQ(result.size(), 3u);
  EXPECT_EQ(result[0].AsString(), string("a"));
  EXPECT_EQ(result[1].AsString(), string(""));
  EXPECT_EQ(result[2].AsString(), string("b"));
}

// String consisting only of separators
TEST_F(SplitStringPieceTest_124, OnlySeparatorsProduceAllEmptyTokens_124) {
  {
    StringPiece input(",");
    vector<StringPiece> result = SplitStringPiece(input, ',');

    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0].AsString(), string(""));
    EXPECT_EQ(result[1].AsString(), string(""));
  }

  {
    StringPiece input(",,");
    vector<StringPiece> result = SplitStringPiece(input, ',');

    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0].AsString(), string(""));
    EXPECT_EQ(result[1].AsString(), string(""));
    EXPECT_EQ(result[2].AsString(), string(""));
  }
}

// Using a different separator character (space)
TEST_F(SplitStringPieceTest_124, DifferentSeparatorCharacterSpace_124) {
  StringPiece input("a b  c");
  vector<StringPiece> result = SplitStringPiece(input, ' ');

  // "a b  c" -> ["a", "b", "", "c"]
  ASSERT_EQ(result.size(), 4u);
  EXPECT_EQ(result[0].AsString(), string("a"));
  EXPECT_EQ(result[1].AsString(), string("b"));
  EXPECT_EQ(result[2].AsString(), string(""));
  EXPECT_EQ(result[3].AsString(), string("c"));
}

// Embedded null characters are preserved as part of tokens
TEST_F(SplitStringPieceTest_124, EmbeddedNullCharacterPreserved_124) {
  const char raw[] = {'a', '\0', 'b'};
  string original(raw, sizeof(raw));  // length = 3, contains '\0'

  StringPiece input(original);
  vector<StringPiece> result = SplitStringPiece(input, ',');

  ASSERT_EQ(result.size(), 1u);
  string piece = result[0].AsString();
  EXPECT_EQ(piece.size(), original.size());
  EXPECT_EQ(piece, original);
}
