// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for Exiv2::CommentValue::CharsetInfo
// Focus: public/static mapping helpers and boundary/exceptional inputs.
//
// TEST_ID: 815

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include <exiv2/value.hpp>

namespace {

using Exiv2::CommentValue;

class CommentValueCharsetInfoTest_815 : public ::testing::Test {};

// Helper: the only "stable" facts we can assert without knowing exact strings:
// - name()/code() must return a non-null C string pointer for any CharsetId.
// - Out-of-range ids are handled (mapped to undefined per provided partial impl for name()).
// - charsetIdByName()/charsetIdByCode() should behave consistently with name()/code()
//   for round-trips using returned strings.
static void ExpectCStrNonNullAndNonEmpty(const char* s) {
  ASSERT_NE(s, nullptr);
  // Non-empty is a reasonable observable requirement for a "name"/"code" table entry.
  // If the implementation legitimately returns empty strings, this will catch it.
  ASSERT_NE(s[0], '\0');
}

TEST_F(CommentValueCharsetInfoTest_815, NameReturnsNonNullForAllDefinedCharsetIds_815) {
  const std::vector<CommentValue::CharsetId> ids = {
      CommentValue::ascii, CommentValue::jis, CommentValue::unicode, CommentValue::undefined};

  for (auto id : ids) {
    const char* n = CommentValue::CharsetInfo::name(id);
    ExpectCStrNonNullAndNonEmpty(n);
  }
}

TEST_F(CommentValueCharsetInfoTest_815, CodeReturnsNonNullForAllDefinedCharsetIds_815) {
  const std::vector<CommentValue::CharsetId> ids = {
      CommentValue::ascii, CommentValue::jis, CommentValue::unicode, CommentValue::undefined};

  for (auto id : ids) {
    const char* c = CommentValue::CharsetInfo::code(id);
    ExpectCStrNonNullAndNonEmpty(c);
  }
}

TEST_F(CommentValueCharsetInfoTest_815, NameOutOfRangeMapsToUndefinedName_815) {
  // Based on provided partial implementation: name() maps charsetId >= lastCharsetId to undefined.
  const char* undef = CommentValue::CharsetInfo::name(CommentValue::undefined);
  ExpectCStrNonNullAndNonEmpty(undef);

  const auto out_of_range =
      static_cast<CommentValue::CharsetId>(static_cast<int>(CommentValue::lastCharsetId));
  const char* n = CommentValue::CharsetInfo::name(out_of_range);
  ASSERT_NE(n, nullptr);
  EXPECT_STREQ(n, undef);
}

TEST_F(CommentValueCharsetInfoTest_815, NameNegativeIdHandledAndReturnsSomeName_815) {
  // Boundary / exceptional input: negative enum value.
  // We cannot assume how it's handled; we only require it doesn't crash and returns a usable string.
  const auto neg = static_cast<CommentValue::CharsetId>(-1);
  const char* n = CommentValue::CharsetInfo::name(neg);
  ExpectCStrNonNullAndNonEmpty(n);
}

TEST_F(CommentValueCharsetInfoTest_815, CodeOutOfRangeIsHandledAndReturnsNonNull_815) {
  // We do NOT assume code() uses the same bounds logic as name() (not shown),
  // but we can still require it to be safe for out-of-range ids.
  const auto out_of_range =
      static_cast<CommentValue::CharsetId>(static_cast<int>(CommentValue::lastCharsetId) + 1000);
  const char* c = CommentValue::CharsetInfo::code(out_of_range);
  ExpectCStrNonNullAndNonEmpty(c);
}

TEST_F(CommentValueCharsetInfoTest_815, CharsetIdByNameRoundTripsForAllDefinedIds_815) {
  // Observable behavior: charsetIdByName(name(id)) should return that id (or at least be stable).
  // If multiple ids share the same name, we can't demand equality for all; but Exiv2's API suggests
  // a bijection for these entries. We'll assert equality for the main known ids.
  const std::vector<CommentValue::CharsetId> ids = {
      CommentValue::ascii, CommentValue::jis, CommentValue::unicode, CommentValue::undefined};

  for (auto id : ids) {
    const char* n = CommentValue::CharsetInfo::name(id);
    ExpectCStrNonNullAndNonEmpty(n);

    const CommentValue::CharsetId back = CommentValue::CharsetInfo::charsetIdByName(std::string(n));
    EXPECT_EQ(back, id);
  }
}

TEST_F(CommentValueCharsetInfoTest_815, CharsetIdByCodeRoundTripsForAllDefinedIds_815) {
  const std::vector<CommentValue::CharsetId> ids = {
      CommentValue::ascii, CommentValue::jis, CommentValue::unicode, CommentValue::undefined};

  for (auto id : ids) {
    const char* c = CommentValue::CharsetInfo::code(id);
    ExpectCStrNonNullAndNonEmpty(c);

    const CommentValue::CharsetId back = CommentValue::CharsetInfo::charsetIdByCode(std::string(c));
    EXPECT_EQ(back, id);
  }
}

TEST_F(CommentValueCharsetInfoTest_815, CharsetIdByNameUnknownStringReturnsInvalidOrUndefined_815) {
  // Exceptional input: unknown name.
  // We don't assume which "sentinel" is used; accept invalidCharsetId or undefined if implemented so.
  const CommentValue::CharsetId id =
      CommentValue::CharsetInfo::charsetIdByName("this-is-not-a-valid-charset-name");
  EXPECT_TRUE(id == CommentValue::invalidCharsetId || id == CommentValue::undefined);
}

TEST_F(CommentValueCharsetInfoTest_815, CharsetIdByCodeUnknownStringReturnsInvalidOrUndefined_815) {
  const CommentValue::CharsetId id =
      CommentValue::CharsetInfo::charsetIdByCode("this-is-not-a-valid-charset-code");
  EXPECT_TRUE(id == CommentValue::invalidCharsetId || id == CommentValue::undefined);
}

TEST_F(CommentValueCharsetInfoTest_815, CharsetIdByNameEmptyStringHandled_815) {
  const CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName(std::string());
  EXPECT_TRUE(id == CommentValue::invalidCharsetId || id == CommentValue::undefined);
}

TEST_F(CommentValueCharsetInfoTest_815, CharsetIdByCodeEmptyStringHandled_815) {
  const CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode(std::string());
  EXPECT_TRUE(id == CommentValue::invalidCharsetId || id == CommentValue::undefined);
}

TEST_F(CommentValueCharsetInfoTest_815, CharsetIdByNameMatchesForExactReturnedNameAndIsCaseSensitiveOrStable_815) {
  // Boundary: case changes. We cannot assume case-insensitive matching.
  // What we *can* test: exact string returned by name() maps back to the same id,
  // and a trivially modified variant should not crash and should return a valid sentinel
  // if it doesn't match.
  const char* n = CommentValue::CharsetInfo::name(CommentValue::ascii);
  ExpectCStrNonNullAndNonEmpty(n);

  EXPECT_EQ(CommentValue::CharsetInfo::charsetIdByName(std::string(n)), CommentValue::ascii);

  std::string modified(n);
  modified += "_X";
  const CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByName(modified);
  EXPECT_TRUE(id == CommentValue::invalidCharsetId || id == CommentValue::undefined ||
              id == CommentValue::ascii /* if impl does prefix/lenient matching */);
}

TEST_F(CommentValueCharsetInfoTest_815, CharsetIdByCodeMatchesForExactReturnedCodeAndIsStableOnModification_815) {
  const char* c = CommentValue::CharsetInfo::code(CommentValue::unicode);
  ExpectCStrNonNullAndNonEmpty(c);

  EXPECT_EQ(CommentValue::CharsetInfo::charsetIdByCode(std::string(c)), CommentValue::unicode);

  std::string modified(c);
  modified.insert(0, "X");
  const CommentValue::CharsetId id = CommentValue::CharsetInfo::charsetIdByCode(modified);
  EXPECT_TRUE(id == CommentValue::invalidCharsetId || id == CommentValue::undefined ||
              id == CommentValue::unicode /* if impl does lenient matching */);
}

}  // namespace