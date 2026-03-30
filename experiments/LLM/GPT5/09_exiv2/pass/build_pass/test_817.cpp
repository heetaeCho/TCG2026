// ============================================================================
// TEST_ID: 817
// File: test_value_charsetinfo_817.cpp
// Unit tests for Exiv2::CommentValue::CharsetInfo::charsetIdByName()
// ============================================================================

#include <gtest/gtest.h>

#include <string>
#include <vector>

// Exiv2 public header
#include <exiv2/value.hpp>

namespace {

// Helper to avoid repeating casts and to keep tests resilient to enum placement.
// In Exiv2, CharsetId is typically nested in Exiv2::CommentValue (class) or
// Exiv2::CommentValue (namespace). The provided interface indicates
// Exiv2::CommentValue::CharsetInfo and Exiv2::CommentValue::CharsetId.
using CharsetInfo = Exiv2::CommentValue::CharsetInfo;
using CharsetId   = Exiv2::CommentValue::CharsetId;

class CommentValueCharsetInfoTest_817 : public ::testing::Test {
 protected:
  static std::vector<CharsetId> KnownCharsetIds() {
    // Only IDs explicitly listed in the prompt (excluding sentinels).
    return {Exiv2::CommentValue::ascii, Exiv2::CommentValue::jis, Exiv2::CommentValue::unicode,
            Exiv2::CommentValue::undefined};
  }
};

}  // namespace

TEST_F(CommentValueCharsetInfoTest_817, UnknownNameReturnsInvalid_817) {
  const CharsetId id = CharsetInfo::charsetIdByName("this_is_not_a_real_charset_name_817");
  EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

TEST_F(CommentValueCharsetInfoTest_817, EmptyNameReturnsInvalid_817) {
  const CharsetId id = CharsetInfo::charsetIdByName(std::string());
  EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

TEST_F(CommentValueCharsetInfoTest_817, VeryLongNameReturnsInvalid_817) {
  const std::string longName(4096, 'X');
  const CharsetId id = CharsetInfo::charsetIdByName(longName);
  EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, id);
}

TEST_F(CommentValueCharsetInfoTest_817, RoundTripNameToIdForKnownIds_817) {
  // Black-box property test:
  // For each known CharsetId, take the public name(id) and ensure that
  // charsetIdByName(name(id)) returns the same id (when name is usable).
  for (const CharsetId expected : KnownCharsetIds()) {
    const char* n = CharsetInfo::name(expected);

    // If the library returns a null/empty name for some ids, we can't construct
    // a meaningful round-trip assertion for that id. Treat that as "not testable"
    // via this interface without making assumptions.
    ASSERT_NE(nullptr, n) << "CharsetInfo::name returned nullptr for id=" << static_cast<int>(expected);
    const std::string nameStr(n);
    ASSERT_FALSE(nameStr.empty()) << "CharsetInfo::name returned empty string for id=" << static_cast<int>(expected);

    const CharsetId got = CharsetInfo::charsetIdByName(nameStr);
    EXPECT_EQ(expected, got) << "Round-trip failed for name='" << nameStr << "'";
  }
}

TEST_F(CommentValueCharsetInfoTest_817, NameLookupIsDeterministic_817) {
  // Boundary/robustness: repeated calls with the same input should yield the same output.
  const std::string input = "definitely_unknown_charset_name_817";
  const CharsetId first = CharsetInfo::charsetIdByName(input);
  const CharsetId second = CharsetInfo::charsetIdByName(input);
  EXPECT_EQ(first, second);
  EXPECT_EQ(Exiv2::CommentValue::invalidCharsetId, first);
}

TEST_F(CommentValueCharsetInfoTest_817, LookupDoesNotThrow_817) {
  // Exceptional case (observable): ensure no exceptions are thrown for typical inputs.
  EXPECT_NO_THROW((void)CharsetInfo::charsetIdByName("this_is_not_a_real_charset_name_817"));
  EXPECT_NO_THROW((void)CharsetInfo::charsetIdByName(std::string()));
  EXPECT_NO_THROW((void)CharsetInfo::charsetIdByName(std::string(1024, 'A')));
}