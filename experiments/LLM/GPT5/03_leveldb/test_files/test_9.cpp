// File: slice_to_string_test_9.cc
#include <gtest/gtest.h>
#include <string>
#include "leveldb/slice.h"

using leveldb::Slice;

class SliceToStringTest_9 : public ::testing::Test {};

// Normal: default-constructed slice -> empty string
TEST_F(SliceToStringTest_9, DefaultCtorReturnsEmptyString_9) {
  Slice s;
  EXPECT_TRUE(s.ToString().empty());
  EXPECT_EQ(std::string(), s.ToString());
}

// Normal: constructed from C-string -> same content
TEST_F(SliceToStringTest_9, FromCStringReturnsSameText_9) {
  const char* txt = "hello world";
  Slice s(txt);
  EXPECT_EQ(std::string("hello world"), s.ToString());
}

// Boundary: constructed from empty C-string -> empty std::string
TEST_F(SliceToStringTest_9, FromEmptyCStringReturnsEmpty_9) {
  const char* empty = "";
  Slice s(empty);
  EXPECT_EQ(std::string(), s.ToString());
}

// Normal: constructed from std::string -> same content
TEST_F(SliceToStringTest_9, FromStdStringReturnsSameText_9) {
  std::string src = "leveldb slice";
  Slice s(src);
  EXPECT_EQ(src, s.ToString());
}

// Boundary: size-limited constructor with n == 0 -> empty string
TEST_F(SliceToStringTest_9, FromPointerSizeZeroReturnsEmpty_9) {
  const char* any = "ignored";
  Slice s(any, 0);
  EXPECT_EQ(std::string(), s.ToString());
  EXPECT_TRUE(s.ToString().empty());
}

// Edge/Observable: embedded NUL bytes preserved with (ptr, size) ctor
TEST_F(SliceToStringTest_9, FromPointerSizePreservesEmbeddedNulls_9) {
  const char* with_nul = "ab\0cd";       // literal length (excluding terminator) is 5
  Slice s(with_nul, 5);                  // capture "a","b","\0","c","d"
  std::string expected("ab\0cd", 5);
  EXPECT_EQ(expected.size(), s.ToString().size());
  EXPECT_EQ(expected, s.ToString());
  // Spot-check positions around the NUL
  EXPECT_EQ('a', s.ToString()[0]);
  EXPECT_EQ('b', s.ToString()[1]);
  EXPECT_EQ('c', s.ToString()[3]);
  EXPECT_EQ('d', s.ToString()[4]);
}

// Edge/Observable: C-string ctor uses strlen (stops at first NUL)
TEST_F(SliceToStringTest_9, CStringCtorStopsAtFirstNull_9) {
  const char* with_nul = "xy\0zz";  // strlen -> 2
  Slice s(with_nul);                // C-string based
  EXPECT_EQ(std::string("xy"), s.ToString());
}

// Normal: copy construction preserves ToString result
TEST_F(SliceToStringTest_9, CopyConstructionPreservesContent_9) {
  std::string src = "copy-me";
  Slice original(src);
  Slice copy(original);
  EXPECT_EQ(original.ToString(), copy.ToString());
}

// Normal: assignment preserves ToString result
TEST_F(SliceToStringTest_9, AssignmentPreservesContent_9) {
  Slice a("alpha");
  Slice b("beta");
  b = a;
  EXPECT_EQ(a.ToString(), b.ToString());
}

// International/UTF-8 data passes through unchanged (treat as bytes)
TEST_F(SliceToStringTest_9, Utf8BytesRoundTrip_9) {
  std::string utf8 = u8"한글과🙂emoji";   // UTF-8 bytes
  Slice s(utf8);
  EXPECT_EQ(utf8, s.ToString());
}
