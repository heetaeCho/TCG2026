// File: parse_unicode_group_test_527.cc

#include <gtest/gtest.h>
#include "absl/strings/string_view.h"
#include "re2/regexp.h"

// Forward declaration of the function under test (defined in parse.cc).
namespace re2 {
ParseStatus ParseUnicodeGroup(absl::string_view* s,
                              Regexp::ParseFlags parse_flags,
                              CharClassBuilder* cc,
                              RegexpStatus* status);
}  // namespace re2

namespace re2 {

class ParseUnicodeGroupTest_527 : public ::testing::Test {
 protected:
  ParseUnicodeGroupTest_527() = default;

  static absl::string_view MakeView(const char* lit) {
    return absl::string_view(lit, strlen(lit));
  }
};

// --- kParseNothing cases ---

TEST_F(ParseUnicodeGroupTest_527, ReturnsNothingWhenUnicodeFlagNotSet_527) {
  absl::string_view s = MakeView("\\pL");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::NoParseFlags, &cc, &st);

  EXPECT_EQ(ps, kParseNothing);
  // Input must remain unchanged on kParseNothing.
  EXPECT_EQ(s, "\\pL");
  EXPECT_TRUE(st.ok());
}

TEST_F(ParseUnicodeGroupTest_527, ReturnsNothingForWrongPrefix_527) {
  absl::string_view s = MakeView("\\x");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::UnicodeGroups, &cc, &st);

  EXPECT_EQ(ps, kParseNothing);
  EXPECT_EQ(s, "\\x");
  EXPECT_TRUE(st.ok());
}

TEST_F(ParseUnicodeGroupTest_527, ReturnsNothingWhenTooShort_527) {
  absl::string_view s = MakeView("\\");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::UnicodeGroups, &cc, &st);

  EXPECT_EQ(ps, kParseNothing);
  EXPECT_EQ(s, "\\");
  EXPECT_TRUE(st.ok());
}

// --- kParseOk cases (short and brace forms) ---

TEST_F(ParseUnicodeGroupTest_527, ParsesShortFormCategoryOk_527) {
  absl::string_view s = MakeView("\\pL");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::UnicodeGroups, &cc, &st);

  EXPECT_EQ(ps, kParseOk);
  // Should consume exactly 3 bytes: '\', 'p', 'L'
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(st.ok());

  // Observable effect: letters should typically include 'A'.
  // We do not assert exact contents beyond a basic inclusion check.
  EXPECT_TRUE(cc.Contains(static_cast<Rune>('A')));
}

TEST_F(ParseUnicodeGroupTest_527, ParsesBraceFormCategoryOk_527) {
  absl::string_view s = MakeView("\\p{L}");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::UnicodeGroups, &cc, &st);

  EXPECT_EQ(ps, kParseOk);
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(st.ok());
  EXPECT_TRUE(cc.Contains(static_cast<Rune>('a')));
}

// --- Negation forms ---

TEST_F(ParseUnicodeGroupTest_527, ParsesCapitalPNegation_527) {
  absl::string_view s = MakeView("\\PL");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::UnicodeGroups, &cc, &st);

  EXPECT_EQ(ps, kParseOk);
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(st.ok());

  // If negation worked, 'A' (a letter) should not be included,
  // while a non-letter like '1' should be included.
  EXPECT_FALSE(cc.Contains(static_cast<Rune>('A')));
  EXPECT_TRUE(cc.Contains(static_cast<Rune>('1')));
}

TEST_F(ParseUnicodeGroupTest_527, ParsesCaretNegationInsideBraces_527) {
  absl::string_view s = MakeView("\\p{^L}");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::UnicodeGroups, &cc, &st);

  EXPECT_EQ(ps, kParseOk);
  EXPECT_TRUE(s.empty());
  EXPECT_TRUE(st.ok());

  EXPECT_FALSE(cc.Contains(static_cast<Rune>('z')));
  EXPECT_TRUE(cc.Contains(static_cast<Rune>('0')));
}

// --- Error cases ---

TEST_F(ParseUnicodeGroupTest_527, ErrorOnMissingClosingBrace_527) {
  absl::string_view s = MakeView("\\p{NoClose");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::UnicodeGroups, &cc, &st);

  EXPECT_EQ(ps, kParseError);
  EXPECT_EQ(st.code(), kRegexpBadCharRange);
  // error_arg() should reference the sequence that failed to parse.
  // We do not assert an exact value for error_arg() here because the
  // implementation can report the original seq; just ensure it’s non-empty.
  EXPECT_FALSE(st.error_arg().empty());
}

TEST_F(ParseUnicodeGroupTest_527, ErrorOnUnknownGroupName_527) {
  absl::string_view s = MakeView("\\p{NotAGroupNameSurely}");
  CharClassBuilder cc;
  RegexpStatus st;

  ParseStatus ps = ParseUnicodeGroup(&s, Regexp::UnicodeGroups, &cc, &st);

  EXPECT_EQ(ps, kParseError);
  EXPECT_EQ(st.code(), kRegexpBadCharRange);
  // For unknown group, implementation reports the parsed sequence in error_arg.
  EXPECT_EQ(std::string(st.error_arg()), "\\p{NotAGroupNameSurely}");
}

}  // namespace re2
