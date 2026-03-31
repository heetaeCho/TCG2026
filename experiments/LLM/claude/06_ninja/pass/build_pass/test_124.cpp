#include "gtest/gtest.h"
#include "string_piece_util.h"
#include "string_piece.h"
#include <vector>
#include <string>

using namespace std;

// Helper to convert vector<StringPiece> to vector<string> for easier comparison
static vector<string> ToStrings(const vector<StringPiece>& pieces) {
  vector<string> result;
  for (size_t i = 0; i < pieces.size(); ++i) {
    result.push_back(pieces[i].AsString());
  }
  return result;
}

TEST(SplitStringPieceTest_124, BasicSplitBySpace_124) {
  string input = "hello world foo";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ' ');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("hello", strs[0]);
  EXPECT_EQ("world", strs[1]);
  EXPECT_EQ("foo", strs[2]);
}

TEST(SplitStringPieceTest_124, NoSeparatorFound_124) {
  string input = "noseparator";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(1u, strs.size());
  EXPECT_EQ("noseparator", strs[0]);
}

TEST(SplitStringPieceTest_124, EmptyInput_124) {
  string input = "";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(1u, strs.size());
  EXPECT_EQ("", strs[0]);
}

TEST(SplitStringPieceTest_124, SeparatorAtBeginning_124) {
  string input = ",hello,world";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("", strs[0]);
  EXPECT_EQ("hello", strs[1]);
  EXPECT_EQ("world", strs[2]);
}

TEST(SplitStringPieceTest_124, SeparatorAtEnd_124) {
  string input = "hello,world,";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("hello", strs[0]);
  EXPECT_EQ("world", strs[1]);
  EXPECT_EQ("", strs[2]);
}

TEST(SplitStringPieceTest_124, ConsecutiveSeparators_124) {
  string input = "a,,b";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("a", strs[0]);
  EXPECT_EQ("", strs[1]);
  EXPECT_EQ("b", strs[2]);
}

TEST(SplitStringPieceTest_124, OnlySeparators_124) {
  string input = ",,";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("", strs[0]);
  EXPECT_EQ("", strs[1]);
  EXPECT_EQ("", strs[2]);
}

TEST(SplitStringPieceTest_124, SingleCharacterInput_124) {
  string input = "x";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(1u, strs.size());
  EXPECT_EQ("x", strs[0]);
}

TEST(SplitStringPieceTest_124, SingleSeparatorCharInput_124) {
  string input = ",";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(2u, strs.size());
  EXPECT_EQ("", strs[0]);
  EXPECT_EQ("", strs[1]);
}

TEST(SplitStringPieceTest_124, SplitByColon_124) {
  string input = "path1:path2:path3";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ':');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("path1", strs[0]);
  EXPECT_EQ("path2", strs[1]);
  EXPECT_EQ("path3", strs[2]);
}

TEST(SplitStringPieceTest_124, SplitByNewline_124) {
  string input = "line1\nline2\nline3";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), '\n');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("line1", strs[0]);
  EXPECT_EQ("line2", strs[1]);
  EXPECT_EQ("line3", strs[2]);
}

TEST(SplitStringPieceTest_124, MultipleConsecutiveSeparators_124) {
  string input = "a,,,b";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(4u, strs.size());
  EXPECT_EQ("a", strs[0]);
  EXPECT_EQ("", strs[1]);
  EXPECT_EQ("", strs[2]);
  EXPECT_EQ("b", strs[3]);
}

TEST(SplitStringPieceTest_124, LongStringWithManySeparators_124) {
  string input = "a,b,c,d,e,f,g,h,i,j";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(10u, strs.size());
  EXPECT_EQ("a", strs[0]);
  EXPECT_EQ("j", strs[9]);
}

TEST(SplitStringPieceTest_124, SplitWithSpacesInTokens_124) {
  string input = "hello world,foo bar,baz qux";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("hello world", strs[0]);
  EXPECT_EQ("foo bar", strs[1]);
  EXPECT_EQ("baz qux", strs[2]);
}

TEST(SplitStringPieceTest_124, StringPieceFromCString_124) {
  const char* input = "one:two:three";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ':');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("one", strs[0]);
  EXPECT_EQ("two", strs[1]);
  EXPECT_EQ("three", strs[2]);
}

TEST(SplitStringPieceTest_124, ResultPointsIntoOriginalString_124) {
  string input = "abc,def,ghi";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), ',');
  ASSERT_EQ(3u, result.size());
  // Verify that the StringPiece points into the original string's data
  EXPECT_GE(result[0].str_, input.data());
  EXPECT_LE(result[0].str_, input.data() + input.size());
  EXPECT_GE(result[1].str_, input.data());
  EXPECT_LE(result[1].str_, input.data() + input.size());
  EXPECT_GE(result[2].str_, input.data());
  EXPECT_LE(result[2].str_, input.data() + input.size());
}

TEST(SplitStringPieceTest_124, TwoElementsSplit_124) {
  string input = "key=value";
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), '=');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(2u, strs.size());
  EXPECT_EQ("key", strs[0]);
  EXPECT_EQ("value", strs[1]);
}

TEST(SplitStringPieceTest_124, SplitByNullChar_124) {
  // Using StringPiece with explicit length to include null characters
  string input("a\0b\0c", 5);
  vector<StringPiece> result = SplitStringPiece(StringPiece(input), '\0');
  vector<string> strs = ToStrings(result);
  ASSERT_EQ(3u, strs.size());
  EXPECT_EQ("a", strs[0]);
  EXPECT_EQ("b", strs[1]);
  EXPECT_EQ("c", strs[2]);
}
