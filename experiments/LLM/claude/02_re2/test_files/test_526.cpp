#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

// Forward declaration of the function and types we need
namespace re2 {

struct UGroup;

const UGroup* MaybeParsePerlCCEscape(absl::string_view* s,
                                      Regexp::ParseFlags parse_flags);

}  // namespace re2

using re2::Regexp;
using re2::MaybeParsePerlCCEscape;

class MaybeParsePerlCCEscapeTest_526 : public ::testing::Test {};

// Test that without PerlClasses flag, the function returns NULL
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNullWithoutPerlClassesFlag_526) {
  absl::string_view s("\\d");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::NoParseFlags);
  EXPECT_EQ(result, nullptr);
  // String should not be modified
  EXPECT_EQ(s, "\\d");
}

// Test that with PerlClasses flag and valid \\d, function returns non-null
TEST_F(MaybeParsePerlCCEscapeTest_526, RecognizesBackslashD_526) {
  absl::string_view s("\\d");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_NE(result, nullptr);
  // After successful parse, the prefix should be consumed
  EXPECT_TRUE(s.empty());
}

// Test that with PerlClasses flag and valid \\D, function returns non-null
TEST_F(MaybeParsePerlCCEscapeTest_526, RecognizesBackslashCapitalD_526) {
  absl::string_view s("\\D");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_NE(result, nullptr);
  EXPECT_TRUE(s.empty());
}

// Test that with PerlClasses flag and valid \\s, function returns non-null
TEST_F(MaybeParsePerlCCEscapeTest_526, RecognizesBackslashS_526) {
  absl::string_view s("\\s");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_NE(result, nullptr);
  EXPECT_TRUE(s.empty());
}

// Test that with PerlClasses flag and valid \\S, function returns non-null
TEST_F(MaybeParsePerlCCEscapeTest_526, RecognizesBackslashCapitalS_526) {
  absl::string_view s("\\S");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_NE(result, nullptr);
  EXPECT_TRUE(s.empty());
}

// Test that with PerlClasses flag and valid \\w, function returns non-null
TEST_F(MaybeParsePerlCCEscapeTest_526, RecognizesBackslashW_526) {
  absl::string_view s("\\w");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_NE(result, nullptr);
  EXPECT_TRUE(s.empty());
}

// Test that with PerlClasses flag and valid \\W, function returns non-null
TEST_F(MaybeParsePerlCCEscapeTest_526, RecognizesBackslashCapitalW_526) {
  absl::string_view s("\\W");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_NE(result, nullptr);
  EXPECT_TRUE(s.empty());
}

// Test that an unrecognized escape returns NULL even with PerlClasses flag
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNullForUnrecognizedEscape_526) {
  absl::string_view s("\\x");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_EQ(result, nullptr);
  // String should not be modified on failure from LookupPerlGroup
  EXPECT_EQ(s, "\\x");
}

// Test that empty string returns NULL
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNullForEmptyString_526) {
  absl::string_view s("");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_EQ(result, nullptr);
  EXPECT_TRUE(s.empty());
}

// Test that single character string returns NULL
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNullForSingleChar_526) {
  absl::string_view s("\\");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(s, "\\");
}

// Test that string not starting with backslash returns NULL
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNullForNoBackslash_526) {
  absl::string_view s("dd");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(s, "dd");
}

// Test that only the first two characters are consumed, leaving the rest
TEST_F(MaybeParsePerlCCEscapeTest_526, ConsumesOnlyTwoChars_526) {
  absl::string_view s("\\dfoo");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_NE(result, nullptr);
  EXPECT_EQ(s, "foo");
}

// Test with LikePerl flag (which includes PerlClasses)
TEST_F(MaybeParsePerlCCEscapeTest_526, WorksWithLikePerlFlag_526) {
  absl::string_view s("\\d");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::LikePerl);
  EXPECT_NE(result, nullptr);
  EXPECT_TRUE(s.empty());
}

// Test that other flags combined without PerlClasses returns NULL
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNullWithOtherFlagsNoPerlClasses_526) {
  absl::string_view s("\\d");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlB);
  EXPECT_EQ(result, nullptr);
  EXPECT_EQ(s, "\\d");
}

// Test PerlClasses combined with other flags
TEST_F(MaybeParsePerlCCEscapeTest_526, WorksWithPerlClassesCombinedWithOtherFlags_526) {
  absl::string_view s("\\w");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::PerlClasses | Regexp::FoldCase);
  auto result = MaybeParsePerlCCEscape(&s, flags);
  EXPECT_NE(result, nullptr);
  EXPECT_TRUE(s.empty());
}

// Test that \\b is not a Perl character class (it's a boundary, not a CC)
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNullForBackslashB_526) {
  absl::string_view s("\\b");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_EQ(result, nullptr);
}

// Test that \\n is not a Perl character class
TEST_F(MaybeParsePerlCCEscapeTest_526, ReturnsNullForBackslashN_526) {
  absl::string_view s("\\n");
  auto result = MaybeParsePerlCCEscape(&s, Regexp::PerlClasses);
  EXPECT_EQ(result, nullptr);
}

// Test that different valid escapes return different groups
TEST_F(MaybeParsePerlCCEscapeTest_526, DifferentEscapesReturnDifferentGroups_526) {
  absl::string_view s1("\\d");
  absl::string_view s2("\\w");
  auto result1 = MaybeParsePerlCCEscape(&s1, Regexp::PerlClasses);
  auto result2 = MaybeParsePerlCCEscape(&s2, Regexp::PerlClasses);
  EXPECT_NE(result1, nullptr);
  EXPECT_NE(result2, nullptr);
  EXPECT_NE(result1, result2);
}

// Test that \\d and \\D return different groups
TEST_F(MaybeParsePerlCCEscapeTest_526, LowerAndUpperCaseReturnDifferentGroups_526) {
  absl::string_view s1("\\d");
  absl::string_view s2("\\D");
  auto result1 = MaybeParsePerlCCEscape(&s1, Regexp::PerlClasses);
  auto result2 = MaybeParsePerlCCEscape(&s2, Regexp::PerlClasses);
  EXPECT_NE(result1, nullptr);
  EXPECT_NE(result2, nullptr);
  EXPECT_NE(result1, result2);
}
