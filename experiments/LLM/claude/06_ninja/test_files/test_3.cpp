#include "string_piece.h"
#include <gtest/gtest.h>
#include <string>

// Normal operation tests

TEST(StringPieceTest_3, DefaultConstructor_3) {
  StringPiece sp;
  EXPECT_EQ(sp.str_, nullptr);
  EXPECT_EQ(sp.len_, 0u);
}

TEST(StringPieceTest_3, ConstructFromStdString_3) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(sp.len_, 5u);
  EXPECT_EQ(sp.AsString(), "hello");
}

TEST(StringPieceTest_3, ConstructFromCString_3) {
  const char* cstr = "world";
  StringPiece sp(cstr);
  EXPECT_EQ(sp.len_, 5u);
  EXPECT_EQ(sp.AsString(), "world");
}

TEST(StringPieceTest_3, ConstructFromCStringAndLength_3) {
  const char* cstr = "hello world";
  StringPiece sp(cstr, 5);
  EXPECT_EQ(sp.len_, 5u);
  EXPECT_EQ(sp.AsString(), "hello");
}

TEST(StringPieceTest_3, AsStringNormal_3) {
  StringPiece sp("test");
  std::string result = sp.AsString();
  EXPECT_EQ(result, "test");
}

TEST(StringPieceTest_3, AsStringEmpty_3) {
  StringPiece sp;
  std::string result = sp.AsString();
  EXPECT_EQ(result, "");
}

TEST(StringPieceTest_3, AsStringZeroLength_3) {
  const char* cstr = "something";
  StringPiece sp(cstr, 0);
  std::string result = sp.AsString();
  EXPECT_EQ(result, "");
}

TEST(StringPieceTest_3, EqualityOperatorSameContent_3) {
  StringPiece sp1("hello");
  StringPiece sp2("hello");
  EXPECT_TRUE(sp1 == sp2);
}

TEST(StringPieceTest_3, EqualityOperatorDifferentContent_3) {
  StringPiece sp1("hello");
  StringPiece sp2("world");
  EXPECT_FALSE(sp1 == sp2);
}

TEST(StringPieceTest_3, EqualityOperatorDifferentLength_3) {
  StringPiece sp1("hello");
  StringPiece sp2("hell");
  EXPECT_FALSE(sp1 == sp2);
}

TEST(StringPieceTest_3, InequalityOperator_3) {
  StringPiece sp1("hello");
  StringPiece sp2("world");
  EXPECT_TRUE(sp1 != sp2);
}

TEST(StringPieceTest_3, InequalityOperatorSameContent_3) {
  StringPiece sp1("hello");
  StringPiece sp2("hello");
  EXPECT_FALSE(sp1 != sp2);
}

TEST(StringPieceTest_3, BeginEnd_3) {
  StringPiece sp("abc");
  EXPECT_EQ(sp.end() - sp.begin(), 3);
  EXPECT_EQ(*sp.begin(), 'a');
}

TEST(StringPieceTest_3, BeginEndEmpty_3) {
  StringPiece sp;
  EXPECT_EQ(sp.begin(), sp.end());
}

TEST(StringPieceTest_3, SubscriptOperator_3) {
  StringPiece sp("abcdef");
  EXPECT_EQ(sp[0], 'a');
  EXPECT_EQ(sp[1], 'b');
  EXPECT_EQ(sp[5], 'f');
}

TEST(StringPieceTest_3, SizeNormal_3) {
  StringPiece sp("hello");
  EXPECT_EQ(sp.size(), 5u);
}

TEST(StringPieceTest_3, SizeEmpty_3) {
  StringPiece sp;
  EXPECT_EQ(sp.size(), 0u);
}

TEST(StringPieceTest_3, EmptyWhenDefault_3) {
  StringPiece sp;
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_3, EmptyWhenNotEmpty_3) {
  StringPiece sp("hello");
  EXPECT_FALSE(sp.empty());
}

TEST(StringPieceTest_3, EmptyWithEmptyString_3) {
  std::string s = "";
  StringPiece sp(s);
  EXPECT_TRUE(sp.empty());
}

// Boundary conditions

TEST(StringPieceTest_3, SingleCharacter_3) {
  StringPiece sp("x");
  EXPECT_EQ(sp.size(), 1u);
  EXPECT_EQ(sp[0], 'x');
  EXPECT_EQ(sp.AsString(), "x");
  EXPECT_FALSE(sp.empty());
}

TEST(StringPieceTest_3, PartialStringView_3) {
  const char* data = "hello world";
  StringPiece sp(data, 5);
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_EQ(sp.AsString(), "hello");
}

TEST(StringPieceTest_3, EqualityBothEmpty_3) {
  StringPiece sp1;
  StringPiece sp2;
  EXPECT_TRUE(sp1 == sp2);
}

TEST(StringPieceTest_3, EqualityOneEmptyOneNot_3) {
  StringPiece sp1;
  StringPiece sp2("hello");
  EXPECT_FALSE(sp1 == sp2);
  EXPECT_TRUE(sp1 != sp2);
}

TEST(StringPieceTest_3, IterateOverContent_3) {
  StringPiece sp("abc");
  std::string accumulated;
  for (StringPiece::const_iterator it = sp.begin(); it != sp.end(); ++it) {
    accumulated += *it;
  }
  EXPECT_EQ(accumulated, "abc");
}

TEST(StringPieceTest_3, ConstructFromEmptyCString_3) {
  StringPiece sp("");
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ(sp.AsString(), "");
}

TEST(StringPieceTest_3, AsStringPreservesNullBytes_3) {
  const char data[] = "he\0lo";
  StringPiece sp(data, 5);
  std::string result = sp.AsString();
  EXPECT_EQ(result.size(), 5u);
  EXPECT_EQ(result[2], '\0');
  EXPECT_EQ(result[3], 'l');
}

TEST(StringPieceTest_3, EqualityWithSubstring_3) {
  const char* data = "hello";
  StringPiece sp1(data, 3);  // "hel"
  StringPiece sp2("hel");
  EXPECT_TRUE(sp1 == sp2);
}

TEST(StringPieceTest_3, LongString_3) {
  std::string long_str(10000, 'a');
  StringPiece sp(long_str);
  EXPECT_EQ(sp.size(), 10000u);
  EXPECT_EQ(sp.AsString(), long_str);
}

TEST(StringPieceTest_3, ConstructFromStdStringDoesNotCopy_3) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(sp.str_, s.data());
}
