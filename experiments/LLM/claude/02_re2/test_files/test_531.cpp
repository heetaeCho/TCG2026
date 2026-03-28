#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "absl/strings/string_view.h"

namespace re2 {

// We test ParseCharClass indirectly through Regexp::Parse, since ParseState
// is an internal class. However, we can observe the behavior through the
// public Parse interface which exercises ParseCharClass internally.

class ParseCharClassTest_531 : public ::testing::Test {
 protected:
  RegexpStatus status_;

  // Helper: parse a regex and return the Regexp*, or nullptr on failure.
  Regexp* Parse(absl::string_view pattern, Regexp::ParseFlags flags = Regexp::PerlX) {
    return Regexp::Parse(pattern, flags, &status_);
  }
};

// Test: Simple character class [abc]
TEST_F(ParseCharClassTest_531, SimpleCharClass_531) {
  Regexp* re = Parse("[abc]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Negated character class [^abc]
TEST_F(ParseCharClassTest_531, NegatedCharClass_531) {
  Regexp* re = Parse("[^abc]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with range [a-z]
TEST_F(ParseCharClassTest_531, CharClassWithRange_531) {
  Regexp* re = Parse("[a-z]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with multiple ranges [a-zA-Z0-9]
TEST_F(ParseCharClassTest_531, CharClassMultipleRanges_531) {
  Regexp* re = Parse("[a-zA-Z0-9]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with ] as first character []abc]
TEST_F(ParseCharClassTest_531, CharClassBracketAsFirstChar_531) {
  Regexp* re = Parse("[]abc]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Negated character class with ] as first character [^]abc]
TEST_F(ParseCharClassTest_531, NegatedCharClassBracketAsFirstChar_531) {
  Regexp* re = Parse("[^]abc]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Missing closing bracket - should fail with kRegexpMissingBracket
TEST_F(ParseCharClassTest_531, MissingClosingBracket_531) {
  Regexp* re = Parse("[abc");
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpMissingBracket);
}

// Test: Negated missing closing bracket
TEST_F(ParseCharClassTest_531, NegatedMissingClosingBracket_531) {
  Regexp* re = Parse("[^abc");
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpMissingBracket);
}

// Test: Empty character class [] - ] is first char, so this is valid with just ]
TEST_F(ParseCharClassTest_531, BracketOnlyClass_531) {
  Regexp* re = Parse("[]]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with POSIX named class [:alpha:]
TEST_F(ParseCharClassTest_531, POSIXNamedClass_531) {
  Regexp* re = Parse("[[:alpha:]]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with POSIX named class [:digit:]
TEST_F(ParseCharClassTest_531, POSIXDigitClass_531) {
  Regexp* re = Parse("[[:digit:]]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with negated POSIX named class [:^alpha:]
TEST_F(ParseCharClassTest_531, NegatedPOSIXNamedClass_531) {
  Regexp* re = Parse("[[:^alpha:]]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with Perl escape \d
TEST_F(ParseCharClassTest_531, PerlEscapeDigit_531) {
  Regexp* re = Parse("[\\d]", Regexp::PerlClasses);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with Perl escape \w
TEST_F(ParseCharClassTest_531, PerlEscapeWord_531) {
  Regexp* re = Parse("[\\w]", Regexp::PerlClasses);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with Perl escape \s
TEST_F(ParseCharClassTest_531, PerlEscapeSpace_531) {
  Regexp* re = Parse("[\\s]", Regexp::PerlClasses);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with Unicode property \p{L}
TEST_F(ParseCharClassTest_531, UnicodePropertyInClass_531) {
  Regexp* re = Parse("[\\p{L}]", Regexp::UnicodeGroups);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with escaped character [\n]
TEST_F(ParseCharClassTest_531, EscapedNewlineInClass_531) {
  Regexp* re = Parse("[\\n]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with escaped character [\t]
TEST_F(ParseCharClassTest_531, EscapedTabInClass_531) {
  Regexp* re = Parse("[\\t]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Bad character range [z-a] should fail
TEST_F(ParseCharClassTest_531, BadCharRange_531) {
  Regexp* re = Parse("[z-a]");
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpBadCharRange);
}

// Test: Single character class [a]
TEST_F(ParseCharClassTest_531, SingleCharClass_531) {
  Regexp* re = Parse("[a]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with hyphen at end [a-]
TEST_F(ParseCharClassTest_531, HyphenAtEnd_531) {
  // In PerlX mode, hyphen at end should be treated as literal
  Regexp* re = Parse("[a-]", Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with hyphen at start [-a]
TEST_F(ParseCharClassTest_531, HyphenAtStart_531) {
  Regexp* re = Parse("[-a]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Bad dash in middle without PerlX [a-b-c]
TEST_F(ParseCharClassTest_531, BadDashInMiddleNoPerlX_531) {
  // Without PerlX, a dash in the middle after a range is an error
  Regexp* re = Parse("[a-b-c]", Regexp::NoParseFlags);
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpBadCharRange);
}

// Test: Dash in middle with PerlX [a-b-c] should succeed
TEST_F(ParseCharClassTest_531, DashInMiddleWithPerlX_531) {
  Regexp* re = Parse("[a-b-c]", Regexp::PerlX);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Negated class with ClassNL flag
TEST_F(ParseCharClassTest_531, NegatedClassWithClassNL_531) {
  Regexp* re = Parse("[^a]", Regexp::ClassNL);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Negated class with NeverNL flag
TEST_F(ParseCharClassTest_531, NegatedClassWithNeverNL_531) {
  Regexp* re = Parse("[^a]", static_cast<Regexp::ParseFlags>(Regexp::NeverNL));
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Complex character class [a-zA-Z0-9_]
TEST_F(ParseCharClassTest_531, ComplexCharClass_531) {
  Regexp* re = Parse("[a-zA-Z0-9_]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with FoldCase flag [a-z]
TEST_F(ParseCharClassTest_531, CharClassWithFoldCase_531) {
  Regexp* re = Parse("[a-z]", Regexp::FoldCase);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Nested brackets [a[b] - not a valid POSIX class
TEST_F(ParseCharClassTest_531, NestedBrackets_531) {
  // [ inside a class is treated as literal
  Regexp* re = Parse("[a[b]", Regexp::PerlX);
  // This should parse [a[b] where [ is literal, ] closes it
  // But "a[b" doesn't have closing bracket... actually "[a[b]" 
  // The first [ opens class, then a, [, b, then ] closes.
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with backslash at end (trailing backslash)
TEST_F(ParseCharClassTest_531, TrailingBackslashInClass_531) {
  Regexp* re = Parse("[\\]");
  EXPECT_EQ(re, nullptr);
  // Should fail - missing bracket or bad escape
}

// Test: Empty negated class missing bracket [^
TEST_F(ParseCharClassTest_531, EmptyNegatedClassMissingBracket_531) {
  Regexp* re = Parse("[^");
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpMissingBracket);
}

// Test: Character class in larger regex a[bc]d
TEST_F(ParseCharClassTest_531, CharClassInLargerRegex_531) {
  Regexp* re = Parse("a[bc]d");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Multiple character classes [ab][cd]
TEST_F(ParseCharClassTest_531, MultipleCharClasses_531) {
  Regexp* re = Parse("[ab][cd]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with special chars [.*+?]
TEST_F(ParseCharClassTest_531, SpecialCharsInClass_531) {
  Regexp* re = Parse("[.*+?]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Invalid POSIX class name [[:invalid:]]
TEST_F(ParseCharClassTest_531, InvalidPOSIXClassName_531) {
  Regexp* re = Parse("[[:invalid:]]");
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status_.ok());
}

// Test: Character class with octal escape [\060]
TEST_F(ParseCharClassTest_531, OctalEscapeInClass_531) {
  Regexp* re = Parse("[\\060]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with hex escape [\x41]
TEST_F(ParseCharClassTest_531, HexEscapeInClass_531) {
  Regexp* re = Parse("[\\x41]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class [a-z] produces a Regexp that can be converted to string
TEST_F(ParseCharClassTest_531, CharClassToString_531) {
  Regexp* re = Parse("[a-z]");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test: Negated character class [^a-z] produces correct ToString
TEST_F(ParseCharClassTest_531, NegatedCharClassToString_531) {
  Regexp* re = Parse("[^a-z]");
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test: Just [ without closing
TEST_F(ParseCharClassTest_531, JustOpenBracket_531) {
  Regexp* re = Parse("[");
  EXPECT_EQ(re, nullptr);
  EXPECT_EQ(status_.code(), kRegexpMissingBracket);
}

// Test: Character class with range and single char [a-ce]
TEST_F(ParseCharClassTest_531, RangeAndSingleChar_531) {
  Regexp* re = Parse("[a-ce]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

// Test: Character class with hyphen before closing bracket [a-]
TEST_F(ParseCharClassTest_531, HyphenBeforeClosingBracket_531) {
  Regexp* re = Parse("[a-]");
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status_.ok());
  re->Decref();
}

}  // namespace re2
