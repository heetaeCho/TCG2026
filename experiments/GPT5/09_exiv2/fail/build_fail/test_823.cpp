// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_commentvalue_823.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "exiv2/error.hpp"
#include "exiv2/value.hpp"

namespace {

class CommentValueTest_823 : public ::testing::Test {
 protected:
  static std::string AsciiPrefix8() {
    // 8-byte Exif UserComment charset marker (commonly "ASCII\0\0\0")
    return std::string("ASCII\0\0\0", 8);
  }

  static std::string UndefinedPrefix8() {
    // 8 zero bytes
    return std::string(8, '\0');
  }

  static std::string UnicodePrefix8() {
    // 8-byte marker (commonly "UNICODE\0")
    return std::string("UNICODE\0", 8);
  }

  static std::string WithEmbeddedNull(const std::string& a, const std::string& b) {
    std::string s = a;
    s.push_back('\0');
    s += b;
    return s;
  }
};

TEST_F(CommentValueTest_823, CommentReturnsEmptyWhenValueShorterThan8_823) {
  Exiv2::CommentValue v;

  v.value_.assign("1234567");  // 7 bytes (< 8)
  EXPECT_EQ(std::string{}, v.comment(nullptr));

  v.value_.clear();
  EXPECT_EQ(std::string{}, v.comment("UTF-8"));
}

TEST_F(CommentValueTest_823, CommentReturnsSubstringAfter8BytesForAsciiPrefix_823) {
  Exiv2::CommentValue v;

  v.value_ = AsciiPrefix8() + std::string("hello");
  EXPECT_EQ("hello", v.comment(nullptr));

  // encoding argument should not affect ASCII path
  EXPECT_EQ("hello", v.comment("SOME-NONEXISTENT-ENCODING-NAME"));
}

TEST_F(CommentValueTest_823, CommentTruncatesAtFirstNullForAsciiPrefix_823) {
  Exiv2::CommentValue v;

  v.value_ = AsciiPrefix8() + WithEmbeddedNull("hi", "there");
  EXPECT_EQ("hi", v.comment(nullptr));
}

TEST_F(CommentValueTest_823, CommentTruncatesAtFirstNullForUndefinedPrefix_823) {
  Exiv2::CommentValue v;

  v.value_ = UndefinedPrefix8() + WithEmbeddedNull("abc", "def");
  EXPECT_EQ("abc", v.comment(nullptr));
}

TEST_F(CommentValueTest_823, CommentDoesNotTruncateWhenNoNullForAsciiPrefix_823) {
  Exiv2::CommentValue v;

  v.value_ = AsciiPrefix8() + std::string("no-nulls-here");
  EXPECT_EQ("no-nulls-here", v.comment(nullptr));
}

TEST_F(CommentValueTest_823, CommentUnicodeWithInvalidEncodingThrowsError_823) {
  Exiv2::CommentValue v;

  // For unicode charset, comment() may attempt charset conversion.
  // Supplying an invalid "from" encoding should be observable as an exception.
  v.value_ = UnicodePrefix8() + std::string("abc");  // payload content is opaque to the test

  EXPECT_THROW(
      {
        (void)v.comment("THIS-ENCODING-SHOULD-NOT-EXIST-XYZ");
      },
      Exiv2::Error);
}

TEST_F(CommentValueTest_823, CommentAsciiDoesNotThrowEvenWithInvalidEncodingArgument_823) {
  Exiv2::CommentValue v;

  v.value_ = AsciiPrefix8() + std::string("safe");
  EXPECT_NO_THROW({ (void)v.comment("THIS-ENCODING-SHOULD-NOT-EXIST-XYZ"); });
  EXPECT_EQ("safe", v.comment("THIS-ENCODING-SHOULD-NOT-EXIST-XYZ"));
}

}  // namespace