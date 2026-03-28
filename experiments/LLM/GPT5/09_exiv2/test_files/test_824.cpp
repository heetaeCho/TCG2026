// =================================================================================================
// File:        test_commentvalue_charsetid_824.cpp
// Description: Unit tests for Exiv2::CommentValue::charsetId() (black-box via public interface)
// Test ID:     824
// =================================================================================================

#include <gtest/gtest.h>

#include <string>

#include "exiv2/value.hpp"

namespace {

class CommentValueCharsetIdTest_824 : public ::testing::Test {
 protected:
  Exiv2::CommentValue cv_;
};

TEST_F(CommentValueCharsetIdTest_824, EmptyValueReturnsUndefined_824) {
  // Default constructed value should have length < 8, therefore charsetId() should be undefined.
  EXPECT_EQ(Exiv2::CommentValue::undefined, cv_.charsetId());
}

TEST_F(CommentValueCharsetIdTest_824, ValueShorterThan8ReturnsUndefined_824) {
  cv_.value_ = "1234567";  // length == 7
  EXPECT_EQ(Exiv2::CommentValue::undefined, cv_.charsetId());

  cv_.value_.clear();  // length == 0
  EXPECT_EQ(Exiv2::CommentValue::undefined, cv_.charsetId());
}

TEST_F(CommentValueCharsetIdTest_824, Exactly8CharsUsesCharsetInfoMapping_824) {
  // Use CharsetInfo as the authoritative mapping source (no re-implementation).
  const Exiv2::CommentValue::CharsetId ids[] = {
      Exiv2::CommentValue::ascii,
      Exiv2::CommentValue::jis,
      Exiv2::CommentValue::unicode,
      Exiv2::CommentValue::undefined,
  };

  for (const auto id : ids) {
    const char* code_cstr = Exiv2::CommentValue::CharsetInfo::code(id);
    ASSERT_NE(nullptr, code_cstr);

    const std::string code(code_cstr);
    // charsetId() only looks at the first 8 bytes when length >= 8; ensure the code is usable.
    ASSERT_GE(code.size(), 8u);

    cv_.value_ = code.substr(0, 8);
    const auto expected = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(cv_.value_);
    EXPECT_EQ(expected, cv_.charsetId()) << "code='" << cv_.value_ << "'";
  }
}

TEST_F(CommentValueCharsetIdTest_824, LongerThan8IgnoresTailAndUsesPrefix_824) {
  // Pick a known code from CharsetInfo (if available) and append data after the 8-byte prefix.
  const char* code_cstr = Exiv2::CommentValue::CharsetInfo::code(Exiv2::CommentValue::ascii);
  ASSERT_NE(nullptr, code_cstr);

  const std::string code(code_cstr);
  ASSERT_GE(code.size(), 8u);

  const std::string prefix = code.substr(0, 8);
  cv_.value_ = prefix + "THIS_IS_TAIL_DATA";

  const auto expected = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(prefix);
  EXPECT_EQ(expected, cv_.charsetId());
}

TEST_F(CommentValueCharsetIdTest_824, Unknown8BytePrefixReturnsCharsetInfoResult_824) {
  // Boundary/error-like case: an unrecognized prefix should yield whatever CharsetInfo reports.
  // We do not assume what that value is (could be undefined/invalid/etc.).
  const std::string unknown = "ZZZZZZZZ";
  ASSERT_EQ(8u, unknown.size());

  cv_.value_ = unknown;

  const auto expected = Exiv2::CommentValue::CharsetInfo::charsetIdByCode(unknown);
  EXPECT_EQ(expected, cv_.charsetId());
}

}  // namespace