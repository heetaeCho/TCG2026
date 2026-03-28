#include "gtest/gtest.h"
#include "string_piece.h"
#include <string>
#include <cstring>

// Normal operation tests

TEST(StringPieceTest_7, DefaultConstructor_7) {
  StringPiece sp;
  EXPECT_EQ(sp.str_, nullptr);
  EXPECT_EQ(sp.len_, 0u);
  EXPECT_EQ(sp.size(), 0u);
}

TEST(StringPieceTest_7, ConstructFromStdString_7) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(sp.str_, s.data());
  EXPECT_EQ(sp.size(), 5u);
  EXPECT_EQ(sp.len_, 5u);
}

TEST(StringPieceTest_7, ConstructFromCString_7) {
  const char* cstr = "world";
  StringPiece sp(cstr);
  EXPECT_EQ(sp.str_, cstr);
  EXPECT_EQ(sp.size(), 5u);
}

TEST(StringPieceTest_7, ConstructFromCStringAndLength_7) {
  const char* cstr = "hello world";
  StringPiece sp(cstr, 5);
  EXPECT_EQ(sp.str_, cstr);
  EXPECT_EQ(sp.size(), 5u);
}

TEST(StringPieceTest_7, SizeReturnsCorrectLength_7) {
  StringPiece sp("testing");
  EXPECT_EQ(sp.size(), 7u);
}

TEST(StringPieceTest_7, AsStringReturnsStdString_7) {
  StringPiece sp("hello");
  std::string result = sp.AsString();
  EXPECT_EQ(result, "hello");
}

TEST(StringPieceTest_7, AsStringFromPartialCString_7) {
  const char* cstr = "hello world";
  StringPiece sp(cstr, 5);
  std::string result = sp.AsString();
  EXPECT_EQ(result, "hello");
}

TEST(StringPieceTest_7, EqualityOperatorSameContent_7) {
  StringPiece sp1("hello");
  StringPiece sp2("hello");
  EXPECT_TRUE(sp1 == sp2);
}

TEST(StringPieceTest_7, EqualityOperatorDifferentContent_7) {
  StringPiece sp1("hello");
  StringPiece sp2("world");
  EXPECT_FALSE(sp1 == sp2);
}

TEST(StringPieceTest_7, InequalityOperatorDifferentContent_7) {
  StringPiece sp1("hello");
  StringPiece sp2("world");
  EXPECT_TRUE(sp1 != sp2);
}

TEST(StringPieceTest_7, InequalityOperatorSameContent_7) {
  StringPiece sp1("hello");
  StringPiece sp2("hello");
  EXPECT_FALSE(sp1 != sp2);
}

TEST(StringPieceTest_7, BeginReturnsPointerToStart_7) {
  const char* cstr = "hello";
  StringPiece sp(cstr);
  EXPECT_EQ(sp.begin(), cstr);
}

TEST(StringPieceTest_7, EndReturnsPointerPastEnd_7) {
  const char* cstr = "hello";
  StringPiece sp(cstr);
  EXPECT_EQ(sp.end(), cstr + 5);
}

TEST(StringPieceTest_7, SubscriptOperator_7) {
  StringPiece sp("hello");
  EXPECT_EQ(sp[0], 'h');
  EXPECT_EQ(sp[1], 'e');
  EXPECT_EQ(sp[4], 'o');
}

TEST(StringPieceTest_7, EmptyReturnsTrueForDefault_7) {
  StringPiece sp;
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_7, EmptyReturnsFalseForNonEmpty_7) {
  StringPiece sp("hello");
  EXPECT_FALSE(sp.empty());
}

// Boundary condition tests

TEST(StringPieceTest_7, EmptyStringConstructor_7) {
  StringPiece sp("");
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_7, EmptyStdStringConstructor_7) {
  std::string s;
  StringPiece sp(s);
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_7, ZeroLengthWithNonNullPointer_7) {
  const char* cstr = "hello";
  StringPiece sp(cstr, 0);
  EXPECT_EQ(sp.size(), 0u);
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_7, SingleCharacterString_7) {
  StringPiece sp("a");
  EXPECT_EQ(sp.size(), 1u);
  EXPECT_EQ(sp[0], 'a');
  EXPECT_FALSE(sp.empty());
}

TEST(StringPieceTest_7, EqualityDifferentLengths_7) {
  StringPiece sp1("hello");
  StringPiece sp2("hell");
  EXPECT_FALSE(sp1 == sp2);
  EXPECT_TRUE(sp1 != sp2);
}

TEST(StringPieceTest_7, EqualityEmptyStrings_7) {
  StringPiece sp1;
  StringPiece sp2("");
  // Both have size 0; behavior depends on implementation
  // but both represent empty pieces
  EXPECT_EQ(sp1.size(), sp2.size());
}

TEST(StringPieceTest_7, BeginEndIterationMatchesContent_7) {
  StringPiece sp("abc");
  std::string result(sp.begin(), sp.end());
  EXPECT_EQ(result, "abc");
}

TEST(StringPieceTest_7, ConstructFromStdStringWithEmbeddedNull_7) {
  std::string s("hel\0lo", 6);
  StringPiece sp(s);
  EXPECT_EQ(sp.size(), 6u);
  EXPECT_EQ(sp[3], '\0');
  EXPECT_EQ(sp[4], 'l');
}

TEST(StringPieceTest_7, AsStringPreservesContent_7) {
  std::string original = "test string";
  StringPiece sp(original);
  EXPECT_EQ(sp.AsString(), original);
}

TEST(StringPieceTest_7, LongString_7) {
  std::string longStr(10000, 'x');
  StringPiece sp(longStr);
  EXPECT_EQ(sp.size(), 10000u);
  EXPECT_EQ(sp[0], 'x');
  EXPECT_EQ(sp[9999], 'x');
  EXPECT_EQ(sp.AsString(), longStr);
}

TEST(StringPieceTest_7, PartialLengthAsString_7) {
  const char* cstr = "abcdef";
  StringPiece sp(cstr, 3);
  EXPECT_EQ(sp.AsString(), "abc");
  EXPECT_EQ(sp.size(), 3u);
}

TEST(StringPieceTest_7, EqualitySamePointerDifferentLength_7) {
  const char* cstr = "hello";
  StringPiece sp1(cstr, 3);
  StringPiece sp2(cstr, 5);
  EXPECT_FALSE(sp1 == sp2);
}

TEST(StringPieceTest_7, EqualitySamePointerSameLength_7) {
  const char* cstr = "hello";
  StringPiece sp1(cstr, 5);
  StringPiece sp2(cstr, 5);
  EXPECT_TRUE(sp1 == sp2);
}

TEST(StringPieceTest_7, SubscriptFirstAndLastChar_7) {
  StringPiece sp("abcde");
  EXPECT_EQ(sp[0], 'a');
  EXPECT_EQ(sp[sp.size() - 1], 'e');
}

TEST(StringPieceTest_7, EmptyBeginEqualsEnd_7) {
  StringPiece sp("");
  EXPECT_EQ(sp.begin(), sp.end());
}

TEST(StringPieceTest_7, EndMinusBeginEqualsSize_7) {
  StringPiece sp("test");
  EXPECT_EQ(static_cast<size_t>(sp.end() - sp.begin()), sp.size());
}
