#include "gtest/gtest.h"
#include "string_piece_util.h"
#include "string_piece.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

// Test with empty list
TEST(JoinStringPieceTest_125, EmptyList_125) {
  vector<StringPiece> list;
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ("", result);
}

// Test with single element
TEST(JoinStringPieceTest_125, SingleElement_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("hello"));
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ("hello", result);
}

// Test with two elements
TEST(JoinStringPieceTest_125, TwoElements_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("hello"));
  list.push_back(StringPiece("world"));
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ("hello,world", result);
}

// Test with multiple elements
TEST(JoinStringPieceTest_125, MultipleElements_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("a"));
  list.push_back(StringPiece("b"));
  list.push_back(StringPiece("c"));
  list.push_back(StringPiece("d"));
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ("a,b,c,d", result);
}

// Test with space separator
TEST(JoinStringPieceTest_125, SpaceSeparator_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("hello"));
  list.push_back(StringPiece("world"));
  string result = JoinStringPiece(list, ' ');
  EXPECT_EQ("hello world", result);
}

// Test with slash separator
TEST(JoinStringPieceTest_125, SlashSeparator_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("path"));
  list.push_back(StringPiece("to"));
  list.push_back(StringPiece("file"));
  string result = JoinStringPiece(list, '/');
  EXPECT_EQ("path/to/file", result);
}

// Test with empty string elements
TEST(JoinStringPieceTest_125, EmptyStringElements_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece(""));
  list.push_back(StringPiece(""));
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ(",", result);
}

// Test with mix of empty and non-empty elements
TEST(JoinStringPieceTest_125, MixedEmptyAndNonEmpty_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece(""));
  list.push_back(StringPiece("hello"));
  list.push_back(StringPiece(""));
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ(",hello,", result);
}

// Test with single empty element
TEST(JoinStringPieceTest_125, SingleEmptyElement_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece(""));
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ("", result);
}

// Test with StringPiece constructed from std::string
TEST(JoinStringPieceTest_125, StringPieceFromStdString_125) {
  string s1 = "foo";
  string s2 = "bar";
  vector<StringPiece> list;
  list.push_back(StringPiece(s1));
  list.push_back(StringPiece(s2));
  string result = JoinStringPiece(list, '-');
  EXPECT_EQ("foo-bar", result);
}

// Test with StringPiece constructed with explicit length
TEST(JoinStringPieceTest_125, StringPieceWithExplicitLength_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("hello world", 5));
  list.push_back(StringPiece("goodbye world", 7));
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ("hello,goodbye", result);
}

// Test with null character separator
TEST(JoinStringPieceTest_125, NullCharSeparator_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("a"));
  list.push_back(StringPiece("b"));
  string result = JoinStringPiece(list, '\0');
  // Result should be "a\0b" which has length 3
  EXPECT_EQ(3u, result.size());
  EXPECT_EQ('a', result[0]);
  EXPECT_EQ('\0', result[1]);
  EXPECT_EQ('b', result[2]);
}

// Test with many elements
TEST(JoinStringPieceTest_125, ManyElements_125) {
  vector<StringPiece> list;
  for (int i = 0; i < 100; ++i) {
    list.push_back(StringPiece("x"));
  }
  string result = JoinStringPiece(list, ',');
  // 100 'x' characters with 99 commas
  EXPECT_EQ(199u, result.size());
  EXPECT_EQ('x', result[0]);
  EXPECT_EQ(',', result[1]);
  EXPECT_EQ('x', result[198]);
}

// Test that separator appears only between elements, not at start or end
TEST(JoinStringPieceTest_125, SeparatorOnlyBetweenElements_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("first"));
  list.push_back(StringPiece("second"));
  list.push_back(StringPiece("third"));
  string result = JoinStringPiece(list, ';');
  EXPECT_EQ("first;second;third", result);
  // Verify no leading or trailing separator
  EXPECT_EQ('f', result.front());
  EXPECT_EQ('d', result.back());
}

// Test with elements containing the separator character
TEST(JoinStringPieceTest_125, ElementsContainSeparator_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("a,b"));
  list.push_back(StringPiece("c,d"));
  string result = JoinStringPiece(list, ',');
  EXPECT_EQ("a,b,c,d", result);
}

// Test with single character elements
TEST(JoinStringPieceTest_125, SingleCharElements_125) {
  vector<StringPiece> list;
  list.push_back(StringPiece("a"));
  list.push_back(StringPiece("b"));
  list.push_back(StringPiece("c"));
  string result = JoinStringPiece(list, ':');
  EXPECT_EQ("a:b:c", result);
}
