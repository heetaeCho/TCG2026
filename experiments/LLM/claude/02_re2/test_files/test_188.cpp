#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

// =============================================================================
// Construction Tests
// =============================================================================

TEST(PCRETest_188, ConstructFromCString_188) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_EQ(re.error(), "");
}

TEST(PCRETest_188, ConstructFromStdString_188) {
  std::string pat = "world";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), "world");
  EXPECT_EQ(re.error(), "");
}

TEST(PCRETest_188, ConstructSimplePattern_188) {
  PCRE re("(\\d+)");
  EXPECT_EQ(re.pattern(), "(\\d+)");
  EXPECT_EQ(re.error(), "");
}

TEST(PCRETest_188, ConstructInvalidPattern_188) {
  PCRE re("(unclosed");
  // An invalid pattern should produce a non-empty error
  EXPECT_NE(re.error(), "");
}

TEST(PCRETest_188, ConstructEmptyPattern_188) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
  EXPECT_EQ(re.error(), "");
}

// =============================================================================
// NumberOfCapturingGroups Tests
// =============================================================================

TEST(PCRETest_188, NumberOfCapturingGroupsNone_188) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(PCRETest_188, NumberOfCapturingGroupsOne_188) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(PCRETest_188, NumberOfCapturingGroupsMultiple_188) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRETest_188, NumberOfCapturingGroupsNested_188) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// =============================================================================
// DoMatch Tests
// =============================================================================

TEST(PCRETest_188, DoMatchFullMatch_188) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_188, DoMatchFullMatchFails_188) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_188, DoMatchUnanchoredMatch_188) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("say hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCRETest_188, DoMatchUnanchoredNoMatch_188) {
  PCRE re("xyz");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCRETest_188, DoMatchAnchorStart_188) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCRETest_188, DoMatchAnchorStartFails_188) {
  PCRE re("world");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCRETest_188, DoMatchWithConsumed_188) {
  PCRE re("(\\w+)");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 5u);
}

TEST(PCRETest_188, DoMatchWithCapture_188) {
  PCRE re("(\\d+)");
  std::string captured;
  PCRE::Arg arg(&captured);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("abc123def", PCRE::UNANCHORED, nullptr, args, 1));
  EXPECT_EQ(captured, "123");
}

TEST(PCRETest_188, DoMatchEmptyString_188) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_188, DoMatchEmptyStringAgainstNonEmpty_188) {
  PCRE re("");
  // Empty pattern with ANCHOR_BOTH against non-empty should fail
  EXPECT_FALSE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// =============================================================================
// HitLimit / ClearHitLimit Tests
// =============================================================================

TEST(PCRETest_188, HitLimitInitiallyFalse_188) {
  PCRE re("hello");
  EXPECT_FALSE(re.HitLimit());
}

TEST(PCRETest_188, ClearHitLimit_188) {
  PCRE re("hello");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// =============================================================================
// Replace Tests
// =============================================================================

TEST(PCRETest_188, ReplaceSimple_188) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello there");
}

TEST(PCRETest_188, ReplaceNoMatch_188) {
  std::string str = "hello world";
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello world");
}

TEST(PCRETest_188, ReplaceWithCapture_188) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  EXPECT_TRUE(PCRE::Replace(&str, re, "\\2 \\1"));
  EXPECT_EQ(str, "world hello");
}

TEST(PCRETest_188, ReplaceFirstOccurrenceOnly_188) {
  std::string str = "aaa";
  PCRE re("a");
  EXPECT_TRUE(PCRE::Replace(&str, re, "b"));
  EXPECT_EQ(str, "baa");
}

// =============================================================================
// GlobalReplace Tests
// =============================================================================

TEST(PCRETest_188, GlobalReplaceAll_188) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST(PCRETest_188, GlobalReplaceNone_188) {
  std::string str = "hello";
  PCRE re("x");
  int count = PCRE::GlobalReplace(&str, re, "y");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST(PCRETest_188, GlobalReplaceMultipleOccurrences_188) {
  std::string str = "abcabc";
  PCRE re("abc");
  int count = PCRE::GlobalReplace(&str, re, "X");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "XX");
}

// =============================================================================
// Extract Tests
// =============================================================================

TEST(PCRETest_188, ExtractSimple_188) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
  EXPECT_EQ(out, "user at host");
}

TEST(PCRETest_188, ExtractNoMatch_188) {
  std::string out;
  PCRE re("(\\d+)");
  EXPECT_FALSE(PCRE::Extract("hello", re, "\\1", &out));
}

// =============================================================================
// QuoteMeta Tests
// =============================================================================

TEST(PCRETest_188, QuoteMetaSimple_188) {
  std::string quoted = PCRE::QuoteMeta("hello");
  EXPECT_EQ(quoted, "hello");
}

TEST(PCRETest_188, QuoteMetaSpecialChars_188) {
  std::string quoted = PCRE::QuoteMeta("a.b");
  // The dot should be escaped
  PCRE re(quoted);
  EXPECT_TRUE(re.DoMatch("a.b", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("axb", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_188, QuoteMetaParens_188) {
  std::string quoted = PCRE::QuoteMeta("(a)");
  PCRE re(quoted);
  EXPECT_TRUE(re.DoMatch("(a)", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("a", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_188, QuoteMetaEmpty_188) {
  std::string quoted = PCRE::QuoteMeta("");
  EXPECT_EQ(quoted, "");
}

TEST(PCRETest_188, QuoteMetaBrackets_188) {
  std::string quoted = PCRE::QuoteMeta("[abc]");
  PCRE re(quoted);
  EXPECT_TRUE(re.DoMatch("[abc]", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("a", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// =============================================================================
// CheckRewriteString Tests
// =============================================================================

TEST(PCRETest_188, CheckRewriteStringValid_188) {
  PCRE re("(\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
  EXPECT_EQ(error, "");
}

TEST(PCRETest_188, CheckRewriteStringInvalidBackref_188) {
  PCRE re("(\\w+)");
  std::string error;
  // \\2 refers to a second group that doesn't exist
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_NE(error, "");
}

TEST(PCRETest_188, CheckRewriteStringNoBackref_188) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("world", &error));
  EXPECT_EQ(error, "");
}

// =============================================================================
// Pattern and Error Accessors
// =============================================================================

TEST(PCRETest_188, PatternAccessor_188) {
  PCRE re("test_pattern");
  EXPECT_EQ(re.pattern(), "test_pattern");
}

TEST(PCRETest_188, ErrorAccessorOnValidPattern_188) {
  PCRE re("valid");
  EXPECT_EQ(re.error(), "");
}

TEST(PCRETest_188, ErrorAccessorOnInvalidPattern_188) {
  PCRE re("[invalid");
  EXPECT_NE(re.error(), "");
}

// =============================================================================
// Multiple Capture Groups
// =============================================================================

TEST(PCRETest_188, DoMatchMultipleCaptures_188) {
  PCRE re("(\\w+)\\s(\\w+)");
  std::string first, second;
  PCRE::Arg arg1(&first);
  PCRE::Arg arg2(&second);
  const PCRE::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, args, 2));
  EXPECT_EQ(first, "hello");
  EXPECT_EQ(second, "world");
}

TEST(PCRETest_188, DoMatchIntCapture_188) {
  PCRE re("(\\d+)");
  int value = 0;
  PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("42", PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(value, 42);
}

// =============================================================================
// Boundary and Edge Cases
// =============================================================================

TEST(PCRETest_188, DoMatchEmptyPatternEmptyText_188) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCRETest_188, ReplaceEmptyMatch_188) {
  std::string str = "abc";
  PCRE re("b*");
  // Replace first match of zero-or-more b's
  PCRE::Replace(&str, re, "X");
  // The first match at position 0 is empty b* -> "X"
  // Behavior depends on implementation
}

TEST(PCRETest_188, GlobalReplaceEmptyString_188) {
  std::string str = "";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "");
}

TEST(PCRETest_188, ReplaceWithEmptyRewrite_188) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, ""));
  EXPECT_EQ(str, "hello ");
}

TEST(PCRETest_188, DoMatchPartialConsume_188) {
  PCRE re("(\\d+)");
  size_t consumed = 0;
  std::string num;
  PCRE::Arg arg(&num);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("123abc", PCRE::ANCHOR_START, &consumed, args, 1));
  EXPECT_EQ(consumed, 3u);
  EXPECT_EQ(num, "123");
}

}  // namespace re2
