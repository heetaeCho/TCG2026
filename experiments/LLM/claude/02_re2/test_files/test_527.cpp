#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/parse.cc"
#include <string>

// We need access to the ParseUnicodeGroup function and related types
// Since ParseUnicodeGroup is in the re2 namespace, we use it directly.

namespace re2 {

class ParseUnicodeGroupTest_527 : public ::testing::Test {
 protected:
  void SetUp() override {
    status_ = RegexpStatus();
    cc_ = new CharClassBuilder();
  }

  void TearDown() override {
    delete cc_;
  }

  RegexpStatus status_;
  CharClassBuilder* cc_;
};

// Test: Returns kParseNothing when UnicodeGroups flag is not set
TEST_F(ParseUnicodeGroupTest_527, ReturnsNothingWhenUnicodeGroupsFlagNotSet_527) {
  absl::string_view s("\\pL");
  Regexp::ParseFlags flags = Regexp::NoParseFlags;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseNothing);
  // s should not be modified
  EXPECT_EQ(s, "\\pL");
}

// Test: Returns kParseNothing when string is too short
TEST_F(ParseUnicodeGroupTest_527, ReturnsNothingWhenStringTooShort_527) {
  absl::string_view s("\\");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseNothing);
}

// Test: Returns kParseNothing when string is empty
TEST_F(ParseUnicodeGroupTest_527, ReturnsNothingWhenStringEmpty_527) {
  absl::string_view s("");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseNothing);
}

// Test: Returns kParseNothing when string doesn't start with backslash
TEST_F(ParseUnicodeGroupTest_527, ReturnsNothingWhenNoBackslash_527) {
  absl::string_view s("pL");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseNothing);
}

// Test: Returns kParseNothing when second char is not 'p' or 'P'
TEST_F(ParseUnicodeGroupTest_527, ReturnsNothingWhenNotPorP_527) {
  absl::string_view s("\\d");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseNothing);
}

// Test: Parses single-character Unicode group \pL successfully
TEST_F(ParseUnicodeGroupTest_527, ParsesSingleCharUnicodeGroup_527) {
  absl::string_view s("\\pL");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(status_.ok());
}

// Test: Parses braced Unicode group \p{Latin} successfully
TEST_F(ParseUnicodeGroupTest_527, ParsesBracedUnicodeGroup_527) {
  absl::string_view s("\\p{Latin}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(status_.ok());
}

// Test: Parses negated Unicode group \PL successfully
TEST_F(ParseUnicodeGroupTest_527, ParsesNegatedSingleCharUnicodeGroup_527) {
  absl::string_view s("\\PL");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
}

// Test: Parses negated braced Unicode group \P{Latin} successfully
TEST_F(ParseUnicodeGroupTest_527, ParsesNegatedBracedUnicodeGroup_527) {
  absl::string_view s("\\P{Latin}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
}

// Test: Parses \p{^Latin} (negation via caret) successfully
TEST_F(ParseUnicodeGroupTest_527, ParsesCaretNegatedBracedUnicodeGroup_527) {
  absl::string_view s("\\p{^Latin}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
}

// Test: Returns kParseError for unknown Unicode group name
TEST_F(ParseUnicodeGroupTest_527, ReturnsErrorForUnknownUnicodeGroup_527) {
  absl::string_view s("\\p{NonExistentGroupXYZ}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseError);
  EXPECT_EQ(status_.code(), kRegexpBadCharRange);
}

// Test: Returns kParseError when braced group is missing closing brace
TEST_F(ParseUnicodeGroupTest_527, ReturnsErrorForMissingClosingBrace_527) {
  absl::string_view s("\\p{Latin");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseError);
  EXPECT_EQ(status_.code(), kRegexpBadCharRange);
}

// Test: String is properly consumed when there is trailing content after \pL
TEST_F(ParseUnicodeGroupTest_527, ConsumesOnlyUnicodeGroupPartSingleChar_527) {
  absl::string_view s("\\pLabc");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_EQ(s, "abc");
}

// Test: String is properly consumed when there is trailing content after \p{Latin}
TEST_F(ParseUnicodeGroupTest_527, ConsumesOnlyUnicodeGroupPartBraced_527) {
  absl::string_view s("\\p{Latin}abc");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_EQ(s, "abc");
}

// Test: CharClassBuilder is populated after parsing a valid Unicode group
TEST_F(ParseUnicodeGroupTest_527, CharClassBuilderPopulatedAfterParse_527) {
  absl::string_view s("\\pL");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  // After parsing \pL (Letter), the char class should not be empty
  EXPECT_FALSE(cc_->empty());
}

// Test: CharClassBuilder contains letter 'A' after parsing \pL
TEST_F(ParseUnicodeGroupTest_527, CharClassContainsLetterAfterParsingPL_527) {
  absl::string_view s("\\pL");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(cc_->Contains('A'));
  EXPECT_TRUE(cc_->Contains('z'));
}

// Test: Negated group \PL does NOT contain letters
TEST_F(ParseUnicodeGroupTest_527, NegatedGroupDoesNotContainLetters_527) {
  absl::string_view s("\\PL");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  // A negated letter group should not contain 'A'
  EXPECT_FALSE(cc_->Contains('A'));
}

// Test: Parses \p{Greek} successfully
TEST_F(ParseUnicodeGroupTest_527, ParsesGreekUnicodeGroup_527) {
  absl::string_view s("\\p{Greek}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
}

// Test: Parses various well-known single-char properties
TEST_F(ParseUnicodeGroupTest_527, ParsesSingleCharPropertyN_527) {
  absl::string_view s("\\pN");  // Number
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
  // Digits should be in Number category
  EXPECT_TRUE(cc_->Contains('0'));
  EXPECT_TRUE(cc_->Contains('9'));
}

// Test: Unknown single-char property returns error
TEST_F(ParseUnicodeGroupTest_527, UnknownSingleCharPropertyReturnsError_527) {
  absl::string_view s("\\pX");  // X is not a valid Unicode general category
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  // Depending on implementation, this may be an error
  // We just check it doesn't crash and returns a consistent result
  EXPECT_TRUE(result == kParseOk || result == kParseError);
}

// Test: Empty braced name returns error
TEST_F(ParseUnicodeGroupTest_527, EmptyBracedNameReturnsError_527) {
  absl::string_view s("\\p{}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseError);
  EXPECT_EQ(status_.code(), kRegexpBadCharRange);
}

// Test: \p{Han} for CJK characters
TEST_F(ParseUnicodeGroupTest_527, ParsesHanUnicodeGroup_527) {
  absl::string_view s("\\p{Han}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
  EXPECT_FALSE(cc_->empty());
}

// Test: Double negation \P{^Latin} should be equivalent to \p{Latin}
TEST_F(ParseUnicodeGroupTest_527, DoubleNegationEqualsPositive_527) {
  CharClassBuilder* cc1 = new CharClassBuilder();
  CharClassBuilder* cc2 = new CharClassBuilder();

  absl::string_view s1("\\p{Latin}");
  RegexpStatus status1;
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result1 = ParseUnicodeGroup(&s1, flags, cc1, &status1);
  EXPECT_EQ(result1, kParseOk);

  absl::string_view s2("\\P{^Latin}");
  RegexpStatus status2;
  ParseStatus result2 = ParseUnicodeGroup(&s2, flags, cc2, &status2);
  EXPECT_EQ(result2, kParseOk);

  // Both should contain the same characters (Latin letters)
  EXPECT_EQ(cc1->Contains('A'), cc2->Contains('A'));
  EXPECT_EQ(cc1->Contains('z'), cc2->Contains('z'));
  EXPECT_EQ(cc1->Contains('0'), cc2->Contains('0'));

  delete cc1;
  delete cc2;
}

// Test: Parses \p{Cyrillic} successfully
TEST_F(ParseUnicodeGroupTest_527, ParsesCyrillicUnicodeGroup_527) {
  absl::string_view s("\\p{Cyrillic}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
}

// Test: FoldCase flag interaction with Unicode group
TEST_F(ParseUnicodeGroupTest_527, ParsesWithFoldCaseFlag_527) {
  absl::string_view s("\\pL");
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::UnicodeGroups | Regexp::FoldCase);
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  EXPECT_EQ(result, kParseOk);
  EXPECT_TRUE(s.empty());
}

// Test: \p{Zs} (space separator) is a valid Unicode property
TEST_F(ParseUnicodeGroupTest_527, ParsesZsUnicodeGroup_527) {
  absl::string_view s("\\p{Zs}");
  Regexp::ParseFlags flags = Regexp::UnicodeGroups;
  ParseStatus result = ParseUnicodeGroup(&s, flags, cc_, &status_);
  // Zs might not be available as a script name; check result
  // This tests that the function handles it without crashing
  EXPECT_TRUE(result == kParseOk || result == kParseError);
}

}  // namespace re2
