#include <gtest/gtest.h>
#include <string>
#include "util/pcre.h"

namespace re2 {

// ============================================================
// Construction Tests
// ============================================================

TEST(PCRETest_588, ConstructFromCString_588) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_TRUE(re.error().empty());
}

TEST(PCRETest_588, ConstructFromStdString_588) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), "world");
  EXPECT_TRUE(re.error().empty());
}

TEST(PCRETest_588, ConstructWithOption_588) {
  PCRE re("test", PCRE::UTF8);
  EXPECT_EQ(re.pattern(), "test");
}

TEST(PCRETest_588, ConstructFromStdStringWithOption_588) {
  std::string pat = "foo";
  PCRE re(pat, PCRE::None);
  EXPECT_EQ(re.pattern(), "foo");
}

TEST(PCRETest_588, ConstructEmptyPattern_588) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
}

TEST(PCRETest_588, ConstructComplexPattern_588) {
  PCRE re("^([a-z]+)(\\d+)$");
  EXPECT_EQ(re.pattern(), "^([a-z]+)(\\d+)$");
}

// ============================================================
// NumberOfCapturingGroups Tests
// ============================================================

TEST(PCRETest_588, NumberOfCapturingGroupsNone_588) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(PCRETest_588, NumberOfCapturingGroupsOne_588) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(PCRETest_588, NumberOfCapturingGroupsMultiple_588) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRETest_588, NumberOfCapturingGroupsNested_588) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRETest_588, NumberOfCapturingGroupsEmpty_588) {
  PCRE re("");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

// ============================================================
// HitLimit / ClearHitLimit Tests
// ============================================================

TEST(PCRETest_588, HitLimitInitiallyFalse_588) {
  PCRE re("abc");
  EXPECT_FALSE(re.HitLimit());
}

TEST(PCRETest_588, ClearHitLimit_588) {
  PCRE re("abc");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ============================================================
// QuoteMeta Tests
// ============================================================

TEST(PCRETest_588, QuoteMetaSimple_588) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

TEST(PCRETest_588, QuoteMetaSpecialChars_588) {
  std::string result = PCRE::QuoteMeta("a.b");
  EXPECT_NE(result, "a.b");
  // The dot should be escaped
  EXPECT_NE(result.find("\\"), std::string::npos);
}

TEST(PCRETest_588, QuoteMetaEmpty_588) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

TEST(PCRETest_588, QuoteMetaAllSpecial_588) {
  std::string result = PCRE::QuoteMeta(".*+?[](){}^$|\\");
  // All characters should be escaped, result should be longer
  EXPECT_GT(result.size(), strlen(".*+?[](){}^$|\\"));
}

// ============================================================
// DoMatch Tests
// ============================================================

TEST(PCRETest_588, DoMatchFullMatchSuccess_588) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_588, DoMatchFullMatchFailure_588) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch(absl::string_view("world"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_588, DoMatchPartialMatchSuccess_588) {
  PCRE re("ell");
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCRETest_588, DoMatchPartialMatchFailure_588) {
  PCRE re("xyz");
  EXPECT_FALSE(re.DoMatch(absl::string_view("hello"), PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCRETest_588, DoMatchAnchorStart_588) {
  PCRE re("hel");
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCRETest_588, DoMatchAnchorStartFailure_588) {
  PCRE re("llo");
  EXPECT_FALSE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCRETest_588, DoMatchEmptyPatternEmptyString_588) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch(absl::string_view(""), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_588, DoMatchEmptyPatternNonEmptyString_588) {
  PCRE re("");
  EXPECT_FALSE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_588, DoMatchWithConsumed_588) {
  PCRE re("hel");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 3u);
}

TEST(PCRETest_588, DoMatchWithCapturingGroup_588) {
  PCRE re("(\\w+)");
  std::string captured;
  PCRE::Arg arg(&captured);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello"), PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(captured, "hello");
}

TEST(PCRETest_588, DoMatchWithMultipleCapturingGroups_588) {
  PCRE re("(\\w+)\\s(\\w+)");
  std::string first, second;
  PCRE::Arg arg1(&first);
  PCRE::Arg arg2(&second);
  const PCRE::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(re.DoMatch(absl::string_view("hello world"), PCRE::ANCHOR_BOTH, nullptr, args, 2));
  EXPECT_EQ(first, "hello");
  EXPECT_EQ(second, "world");
}

TEST(PCRETest_588, DoMatchWithIntCapture_588) {
  PCRE re("(\\d+)");
  int value = 0;
  PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch(absl::string_view("42"), PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(value, 42);
}

// ============================================================
// Replace Tests
// ============================================================

TEST(PCRETest_588, ReplaceSuccess_588) {
  std::string s = "hello world";
  EXPECT_TRUE(PCRE::Replace(&s, PCRE("world"), "there"));
  EXPECT_EQ(s, "hello there");
}

TEST(PCRETest_588, ReplaceNoMatch_588) {
  std::string s = "hello world";
  EXPECT_FALSE(PCRE::Replace(&s, PCRE("xyz"), "there"));
  EXPECT_EQ(s, "hello world");
}

TEST(PCRETest_588, ReplaceFirstOnly_588) {
  std::string s = "aaa";
  PCRE::Replace(&s, PCRE("a"), "b");
  EXPECT_EQ(s, "baa");
}

TEST(PCRETest_588, ReplaceWithBackreference_588) {
  std::string s = "hello world";
  PCRE::Replace(&s, PCRE("(\\w+) (\\w+)"), "\\2 \\1");
  EXPECT_EQ(s, "world hello");
}

TEST(PCRETest_588, ReplaceEmptyString_588) {
  std::string s = "";
  EXPECT_FALSE(PCRE::Replace(&s, PCRE("a"), "b"));
  EXPECT_EQ(s, "");
}

// ============================================================
// GlobalReplace Tests
// ============================================================

TEST(PCRETest_588, GlobalReplaceAll_588) {
  std::string s = "aaa";
  int count = PCRE::GlobalReplace(&s, PCRE("a"), "b");
  EXPECT_EQ(s, "bbb");
  EXPECT_EQ(count, 3);
}

TEST(PCRETest_588, GlobalReplaceNone_588) {
  std::string s = "hello";
  int count = PCRE::GlobalReplace(&s, PCRE("x"), "y");
  EXPECT_EQ(s, "hello");
  EXPECT_EQ(count, 0);
}

TEST(PCRETest_588, GlobalReplaceMultiple_588) {
  std::string s = "a-b-c";
  int count = PCRE::GlobalReplace(&s, PCRE("-"), ".");
  EXPECT_EQ(s, "a.b.c");
  EXPECT_EQ(count, 2);
}

TEST(PCRETest_588, GlobalReplaceEmptyMatch_588) {
  std::string s = "";
  int count = PCRE::GlobalReplace(&s, PCRE("x"), "y");
  EXPECT_EQ(count, 0);
}

// ============================================================
// Extract Tests
// ============================================================

TEST(PCRETest_588, ExtractSuccess_588) {
  std::string out;
  EXPECT_TRUE(PCRE::Extract("boris@kremvax.ru", PCRE("(.*)@([^.]*)"), "\\2!\\1", &out));
  EXPECT_EQ(out, "kremvax!boris");
}

TEST(PCRETest_588, ExtractNoMatch_588) {
  std::string out;
  EXPECT_FALSE(PCRE::Extract("no-at-sign", PCRE("(.*)@(.*)"), "\\2!\\1", &out));
}

TEST(PCRETest_588, ExtractSimple_588) {
  std::string out;
  EXPECT_TRUE(PCRE::Extract("hello", PCRE("(h\\w+)"), "\\1!", &out));
  EXPECT_EQ(out, "hello!");
}

// ============================================================
// CheckRewriteString Tests
// ============================================================

TEST(PCRETest_588, CheckRewriteStringValid_588) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(PCRETest_588, CheckRewriteStringInvalidGroup_588) {
  PCRE re("(\\w+)");
  std::string error;
  // Group 2 doesn't exist when there is only 1 capturing group
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST(PCRETest_588, CheckRewriteStringNoGroups_588) {
  PCRE re("hello");
  std::string error;
  EXPECT_FALSE(re.CheckRewriteString("\\1", &error));
}

TEST(PCRETest_588, CheckRewriteStringEmptyRewrite_588) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("", &error));
}

TEST(PCRETest_588, CheckRewriteStringLiteralBackslash_588) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("no backrefs here", &error));
}

// ============================================================
// Pattern and Error accessors
// ============================================================

TEST(PCRETest_588, PatternAccessor_588) {
  PCRE re("foobar");
  EXPECT_EQ(re.pattern(), "foobar");
}

TEST(PCRETest_588, ErrorAccessorValidPattern_588) {
  PCRE re("valid");
  EXPECT_TRUE(re.error().empty());
}

TEST(PCRETest_588, InvalidPatternError_588) {
  // Unmatched parenthesis - should produce an error
  PCRE re("(unclosed");
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// Boundary and Special Cases
// ============================================================

TEST(PCRETest_588, PatternWithSpecialRegexChars_588) {
  PCRE re("a\\.b");
  EXPECT_TRUE(re.DoMatch(absl::string_view("a.b"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch(absl::string_view("axb"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_588, PatternWithAlternation_588) {
  PCRE re("cat|dog");
  EXPECT_TRUE(re.DoMatch(absl::string_view("cat"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("dog"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch(absl::string_view("bird"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_588, PatternWithQuantifiers_588) {
  PCRE re("a{2,4}");
  EXPECT_FALSE(re.DoMatch(absl::string_view("a"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("aa"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("aaa"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_TRUE(re.DoMatch(absl::string_view("aaaa"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch(absl::string_view("aaaaa"), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_588, LongPatternMatch_588) {
  std::string long_str(1000, 'a');
  PCRE re("a+");
  EXPECT_TRUE(re.DoMatch(absl::string_view(long_str), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_588, QuoteMetaRoundTrip_588) {
  // QuoteMeta should produce a pattern that matches the literal string
  std::string special = "hello.world*foo+bar?";
  std::string quoted = PCRE::QuoteMeta(special);
  PCRE re(quoted);
  EXPECT_TRUE(re.DoMatch(absl::string_view(special), PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

}  // namespace re2
