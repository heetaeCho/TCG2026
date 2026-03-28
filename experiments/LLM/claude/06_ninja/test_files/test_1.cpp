#include "gtest/gtest.h"
#include "string_piece.h"
#include <string>
#include <cstring>

// Normal operation tests

TEST(StringPieceTest_1, DefaultConstructor_1) {
  StringPiece sp;
  EXPECT_EQ(nullptr, sp.str_);
  EXPECT_EQ(0u, sp.len_);
}

TEST(StringPieceTest_1, ConstructFromStdString_1) {
  std::string s = "hello";
  StringPiece sp(s);
  EXPECT_EQ(s.data(), sp.str_);
  EXPECT_EQ(s.size(), sp.len_);
}

TEST(StringPieceTest_1, ConstructFromCString_1) {
  const char* cstr = "world";
  StringPiece sp(cstr);
  EXPECT_EQ(cstr, sp.str_);
  EXPECT_EQ(5u, sp.len_);
}

TEST(StringPieceTest_1, ConstructFromCStringAndLength_1) {
  const char* cstr = "hello world";
  StringPiece sp(cstr, 5);
  EXPECT_EQ(cstr, sp.str_);
  EXPECT_EQ(5u, sp.len_);
}

TEST(StringPieceTest_1, EqualityOperatorSameContent_1) {
  StringPiece a("hello");
  StringPiece b("hello");
  EXPECT_TRUE(a == b);
}

TEST(StringPieceTest_1, EqualityOperatorDifferentContent_1) {
  StringPiece a("hello");
  StringPiece b("world");
  EXPECT_FALSE(a == b);
}

TEST(StringPieceTest_1, EqualityOperatorDifferentLength_1) {
  StringPiece a("hello");
  StringPiece b("hell");
  EXPECT_FALSE(a == b);
}

TEST(StringPieceTest_1, InequalityOperator_1) {
  StringPiece a("hello");
  StringPiece b("world");
  EXPECT_TRUE(a != b);
}

TEST(StringPieceTest_1, InequalityOperatorSameContent_1) {
  StringPiece a("hello");
  StringPiece b("hello");
  EXPECT_FALSE(a != b);
}

TEST(StringPieceTest_1, AsStringReturnsCorrectString_1) {
  StringPiece sp("test string");
  std::string result = sp.AsString();
  EXPECT_EQ("test string", result);
}

TEST(StringPieceTest_1, AsStringWithPartialBuffer_1) {
  const char* buf = "hello world";
  StringPiece sp(buf, 5);
  std::string result = sp.AsString();
  EXPECT_EQ("hello", result);
}

TEST(StringPieceTest_1, BeginReturnsStartPointer_1) {
  const char* cstr = "abcdef";
  StringPiece sp(cstr);
  EXPECT_EQ(cstr, sp.begin());
}

TEST(StringPieceTest_1, EndReturnsPointerPastEnd_1) {
  const char* cstr = "abcdef";
  StringPiece sp(cstr);
  EXPECT_EQ(cstr + 6, sp.end());
}

TEST(StringPieceTest_1, IteratorRange_1) {
  StringPiece sp("abc");
  std::string reconstructed(sp.begin(), sp.end());
  EXPECT_EQ("abc", reconstructed);
}

TEST(StringPieceTest_1, IndexOperator_1) {
  StringPiece sp("abcde");
  EXPECT_EQ('a', sp[0]);
  EXPECT_EQ('c', sp[2]);
  EXPECT_EQ('e', sp[4]);
}

TEST(StringPieceTest_1, SizeReturnsLength_1) {
  StringPiece sp("hello");
  EXPECT_EQ(5u, sp.size());
}

TEST(StringPieceTest_1, SizeOfEmptyStringPiece_1) {
  StringPiece sp;
  EXPECT_EQ(0u, sp.size());
}

TEST(StringPieceTest_1, EmptyReturnsTrueForDefault_1) {
  StringPiece sp;
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_1, EmptyReturnsFalseForNonEmpty_1) {
  StringPiece sp("hello");
  EXPECT_FALSE(sp.empty());
}

// Boundary condition tests

TEST(StringPieceTest_1, EmptyStdString_1) {
  std::string s = "";
  StringPiece sp(s);
  EXPECT_EQ(0u, sp.len_);
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_1, EmptyCString_1) {
  StringPiece sp("");
  EXPECT_EQ(0u, sp.len_);
  EXPECT_TRUE(sp.empty());
}

TEST(StringPieceTest_1, EqualityBothEmpty_1) {
  StringPiece a;
  StringPiece b;
  // Both have len_ == 0, and memcmp with len 0 should be fine
  // However, str_ is NULL for default, so this depends on implementation
  // Both default constructed should be equal
  EXPECT_TRUE(a == b);
}

TEST(StringPieceTest_1, EqualityEmptyCStrings_1) {
  StringPiece a("");
  StringPiece b("");
  EXPECT_TRUE(a == b);
}

TEST(StringPieceTest_1, SingleCharacterStringPiece_1) {
  StringPiece sp("x");
  EXPECT_EQ(1u, sp.size());
  EXPECT_EQ('x', sp[0]);
  EXPECT_FALSE(sp.empty());
}

TEST(StringPieceTest_1, ZeroLengthWithNonNullPointer_1) {
  const char* buf = "nonempty";
  StringPiece sp(buf, 0);
  EXPECT_EQ(0u, sp.size());
  EXPECT_TRUE(sp.empty());
  EXPECT_EQ("", sp.AsString());
}

TEST(StringPieceTest_1, EqualityWithSameUnderlyingBuffer_1) {
  const char* buf = "hello";
  StringPiece a(buf, 5);
  StringPiece b(buf, 5);
  EXPECT_TRUE(a == b);
}

TEST(StringPieceTest_1, EqualityDifferentBuffersSameContent_1) {
  std::string s1 = "test";
  std::string s2 = "test";
  StringPiece a(s1);
  StringPiece b(s2);
  // Different pointers but same content
  EXPECT_TRUE(a == b);
}

TEST(StringPieceTest_1, EqualitySubstringsOfSameBuffer_1) {
  const char* buf = "aabb";
  StringPiece a(buf, 2);      // "aa"
  StringPiece b(buf + 2, 2);  // "bb"
  EXPECT_FALSE(a == b);
}

TEST(StringPieceTest_1, PrefixAndFullString_1) {
  StringPiece full("hello");
  StringPiece prefix("hello", 3);  // "hel"
  EXPECT_FALSE(full == prefix);
  EXPECT_TRUE(full != prefix);
}

TEST(StringPieceTest_1, StringWithNullBytes_1) {
  const char buf[] = {'a', '\0', 'b'};
  StringPiece sp(buf, 3);
  EXPECT_EQ(3u, sp.size());
  EXPECT_EQ('a', sp[0]);
  EXPECT_EQ('\0', sp[1]);
  EXPECT_EQ('b', sp[2]);
}

TEST(StringPieceTest_1, EqualityWithEmbeddedNulls_1) {
  const char buf1[] = {'a', '\0', 'b'};
  const char buf2[] = {'a', '\0', 'b'};
  const char buf3[] = {'a', '\0', 'c'};
  StringPiece a(buf1, 3);
  StringPiece b(buf2, 3);
  StringPiece c(buf3, 3);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
}

TEST(StringPieceTest_1, AsStringFromStdString_1) {
  std::string original = "hello world";
  StringPiece sp(original);
  std::string result = sp.AsString();
  EXPECT_EQ(original, result);
}

TEST(StringPieceTest_1, BeginEndForEmptyPiece_1) {
  StringPiece sp("");
  EXPECT_EQ(sp.begin(), sp.end());
}

TEST(StringPieceTest_1, ConstructFromLongString_1) {
  std::string longStr(10000, 'x');
  StringPiece sp(longStr);
  EXPECT_EQ(10000u, sp.size());
  EXPECT_EQ(longStr, sp.AsString());
}
