// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_commentvalue_write_822.cpp
//
// Unit tests for Exiv2::CommentValue::write(std::ostream&)
// Constraints: treat implementation as black-box; test only observable behavior.

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <ostream>
#include <sstream>
#include <string>

namespace {

class CommentValueWriteTest_822 : public ::testing::Test {
 protected:
  static std::string ToString(const Exiv2::CommentValue& v) {
    std::ostringstream oss;
    // The interface in headers indicates write(std::ostream&) exists.
    // We only observe what gets written to the stream.
    v.write(oss);
    return oss.str();
  }

  static std::string CharsetPrefixFor(const Exiv2::CommentValue& v) {
    // Only build an expected prefix using public API.
    const auto cs = v.charsetId();
    if (cs == Exiv2::CommentValue::undefined) return std::string{};
    return std::string("charset=") + Exiv2::CommentValue::CharsetInfo::name(cs) + " ";
  }

  static std::string MakeCharsetHeaderString(Exiv2::CommentValue::CharsetId cs, const std::string& text) {
    // Use public API to obtain the canonical charset name string.
    // Do not guess what the name is.
    const char* name = Exiv2::CommentValue::CharsetInfo::name(cs);
    return std::string("charset=") + (name ? name : "") + " " + text;
  }
};

TEST_F(CommentValueWriteTest_822, DefaultConstructed_IsConsistentWithCharsetIdAndComment_822) {
  Exiv2::CommentValue v;

  const auto cs = v.charsetId();
  const std::string out = ToString(v);

  if (cs == Exiv2::CommentValue::undefined) {
    EXPECT_EQ(std::string::npos, out.find("charset="));
    // Only compare against the public comment() result.
    EXPECT_EQ(v.comment(nullptr), out);
  } else {
    EXPECT_EQ(0u, out.find(CharsetPrefixFor(v))) << out;
    EXPECT_EQ(CharsetPrefixFor(v) + v.comment(nullptr), out);
  }
}

TEST_F(CommentValueWriteTest_822, ExplicitCommentConstructor_WritesCommentAndOptionalCharsetPrefix_822) {
  const std::string input = "hello world";
  Exiv2::CommentValue v(input);

  const auto cs = v.charsetId();
  const std::string out = ToString(v);

  if (cs == Exiv2::CommentValue::undefined) {
    EXPECT_EQ(std::string::npos, out.find("charset="));
    EXPECT_EQ(v.comment(nullptr), out);
  } else {
    EXPECT_EQ(0u, out.find(CharsetPrefixFor(v))) << out;
    EXPECT_EQ(CharsetPrefixFor(v) + v.comment(nullptr), out);
  }
}

TEST_F(CommentValueWriteTest_822, ReadEmptyString_WritesEmptyOrOnlyCharsetPrefixDependingOnState_822) {
  Exiv2::CommentValue v;
  const int rc = v.read(std::string{});

  // Don't assume exact return code semantics; only ensure it is callable.
  (void)rc;

  const auto cs = v.charsetId();
  const std::string out = ToString(v);

  if (cs == Exiv2::CommentValue::undefined) {
    EXPECT_EQ(std::string::npos, out.find("charset="));
    EXPECT_EQ(v.comment(nullptr), out);
  } else {
    EXPECT_EQ(0u, out.find(CharsetPrefixFor(v))) << out;
    EXPECT_EQ(CharsetPrefixFor(v) + v.comment(nullptr), out);
  }
}

TEST_F(CommentValueWriteTest_822, ReadWithCharsetHeader_IfCharsetIdNotUndefined_OutputStartsWithCharsetPrefix_822) {
  Exiv2::CommentValue v;

  const std::string text = "payload";
  const std::string input = MakeCharsetHeaderString(Exiv2::CommentValue::ascii, text);
  const int rc = v.read(input);
  (void)rc;

  const auto cs = v.charsetId();
  const std::string out = ToString(v);

  // Observable rule: write should include "charset=... " iff charsetId()!=undefined.
  if (cs == Exiv2::CommentValue::undefined) {
    EXPECT_EQ(std::string::npos, out.find("charset="));
  } else {
    EXPECT_EQ(0u, out.find(CharsetPrefixFor(v))) << out;
  }

  // In all cases, written output must be consistent with the public comment().
  EXPECT_EQ(CharsetPrefixFor(v) + v.comment(nullptr), out);
}

TEST_F(CommentValueWriteTest_822, ReadWithUnknownCharsetToken_DoesNotCrash_AndOutputMatchesPublicState_822) {
  Exiv2::CommentValue v;

  const std::string input = "charset=ThisIsNotARealCharset some text";
  const int rc = v.read(input);
  (void)rc;

  const auto cs = v.charsetId();
  const std::string out = ToString(v);

  // Only assert consistency with public state; do not guess how parsing behaves.
  if (cs == Exiv2::CommentValue::undefined) {
    EXPECT_EQ(std::string::npos, out.find("charset="));
  } else {
    EXPECT_EQ(0u, out.find(CharsetPrefixFor(v))) << out;
  }
  EXPECT_EQ(CharsetPrefixFor(v) + v.comment(nullptr), out);
}

TEST_F(CommentValueWriteTest_822, CommentWithEmbeddedNull_IsWrittenAsReturnedByCommentApi_822) {
  Exiv2::CommentValue v;

  // std::string can contain embedded '\0'. We only validate consistency with public comment().
  const std::string with_null(std::string("A\0B", 3));
  const int rc = v.read(with_null);
  (void)rc;

  const std::string out = ToString(v);

  // Validate exact byte-for-byte equality with what the class reports via comment().
  const std::string expected = CharsetPrefixFor(v) + v.comment(nullptr);
  EXPECT_EQ(expected.size(), out.size());
  EXPECT_EQ(expected, out);
}

}  // namespace