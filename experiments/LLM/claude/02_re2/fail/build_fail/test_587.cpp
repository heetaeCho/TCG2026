#include "gtest/gtest.h"
#include "util/pcre.h"
#include <string>

namespace re2 {

// ============================================================
// Construction Tests
// ============================================================

TEST(PCREConstructionTest_587, ConstructFromCString_587) {
  PCRE re("hello");
  EXPECT_EQ(re.pattern(), "hello");
  EXPECT_TRUE(re.error().empty());
}

TEST(PCREConstructionTest_587, ConstructFromCStringWithOption_587) {
  PCRE re("hello", PCRE::UTF8);
  EXPECT_EQ(re.pattern(), "hello");
}

TEST(PCREConstructionTest_587, ConstructFromStdString_587) {
  std::string pattern = "world";
  PCRE re(pattern);
  EXPECT_EQ(re.pattern(), "world");
}

TEST(PCREConstructionTest_587, ConstructFromStdStringWithOption_587) {
  std::string pattern = "world";
  PCRE re(pattern, PCRE::UTF8);
  EXPECT_EQ(re.pattern(), "world");
}

TEST(PCREConstructionTest_587, ConstructWithEmptyPattern_587) {
  PCRE re("");
  EXPECT_EQ(re.pattern(), "");
}

TEST(PCREConstructionTest_587, ConstructWithInvalidPattern_587) {
  PCRE re("[invalid");
  // Invalid pattern should produce a non-empty error
  EXPECT_FALSE(re.error().empty());
}

// ============================================================
// Pattern and Error Tests
// ============================================================

TEST(PCREPatternTest_587, PatternReturnsOriginalPattern_587) {
  PCRE re("foo.*bar");
  EXPECT_EQ(re.pattern(), "foo.*bar");
}

TEST(PCREPatternTest_587, ValidPatternHasEmptyError_587) {
  PCRE re("(abc)+");
  EXPECT_TRUE(re.error().empty());
}

// ============================================================
// NumberOfCapturingGroups Tests
// ============================================================

TEST(PCRECapturingGroupsTest_587, NoCapturingGroups_587) {
  PCRE re("hello");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(PCRECapturingGroupsTest_587, OneCapturingGroup_587) {
  PCRE re("(hello)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST(PCRECapturingGroupsTest_587, MultipleCapturingGroups_587) {
  PCRE re("(a)(b)(c)");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRECapturingGroupsTest_587, NestedCapturingGroups_587) {
  PCRE re("((a)(b))");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(PCRECapturingGroupsTest_587, InvalidPatternReturnsNegative_587) {
  PCRE re("[invalid");
  EXPECT_LT(re.NumberOfCapturingGroups(), 0);
}

// ============================================================
// DoMatch Tests
// ============================================================

TEST(PCREDoMatchTest_587, SimpleMatchUnanchored_587) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_587, SimpleMatchAnchored_587) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_587, AnchoredMatchFails_587) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_587, AnchorStartMatch_587) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_587, AnchorStartMatchFails_587) {
  PCRE re("hello");
  EXPECT_FALSE(re.DoMatch("say hello", PCRE::ANCHOR_START, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_587, UnanchoredMatchInMiddle_587) {
  PCRE re("hello");
  EXPECT_TRUE(re.DoMatch("say hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_587, NoMatchReturnsfalse_587) {
  PCRE re("xyz");
  EXPECT_FALSE(re.DoMatch("hello world", PCRE::UNANCHORED, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_587, EmptyPatternMatchesEmpty_587) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREDoMatchTest_587, MatchWithConsumed_587) {
  PCRE re("hel+o");
  size_t consumed = 0;
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_START, &consumed, nullptr, 0));
  EXPECT_EQ(consumed, 5u);
}

TEST(PCREDoMatchTest_587, MatchWithCapturingGroupAndArg_587) {
  PCRE re("(\\w+)");
  std::string captured;
  PCRE::Arg arg(&captured);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("hello", PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(captured, "hello");
}

TEST(PCREDoMatchTest_587, MatchWithIntCapture_587) {
  PCRE re("(\\d+)");
  int value = 0;
  PCRE::Arg arg(&value);
  const PCRE::Arg* args[] = {&arg};
  EXPECT_TRUE(re.DoMatch("12345", PCRE::ANCHOR_BOTH, nullptr, args, 1));
  EXPECT_EQ(value, 12345);
}

TEST(PCREDoMatchTest_587, MatchWithMultipleCaptures_587) {
  PCRE re("(\\w+)\\s(\\w+)");
  std::string first, second;
  PCRE::Arg arg1(&first);
  PCRE::Arg arg2(&second);
  const PCRE::Arg* args[] = {&arg1, &arg2};
  EXPECT_TRUE(re.DoMatch("hello world", PCRE::ANCHOR_BOTH, nullptr, args, 2));
  EXPECT_EQ(first, "hello");
  EXPECT_EQ(second, "world");
}

// ============================================================
// Replace Tests
// ============================================================

TEST(PCREReplaceTest_587, SimpleReplace_587) {
  std::string str = "hello world";
  PCRE re("world");
  EXPECT_TRUE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello there");
}

TEST(PCREReplaceTest_587, ReplaceNoMatch_587) {
  std::string str = "hello world";
  PCRE re("xyz");
  EXPECT_FALSE(PCRE::Replace(&str, re, "there"));
  EXPECT_EQ(str, "hello world");
}

TEST(PCREReplaceTest_587, ReplaceWithBackreference_587) {
  std::string str = "hello world";
  PCRE re("(\\w+) (\\w+)");
  EXPECT_TRUE(PCRE::Replace(&str, re, "\\2 \\1"));
  EXPECT_EQ(str, "world hello");
}

TEST(PCREReplaceTest_587, ReplaceFirstOccurrence_587) {
  std::string str = "aaa";
  PCRE re("a");
  EXPECT_TRUE(PCRE::Replace(&str, re, "b"));
  EXPECT_EQ(str, "baa");
}

// ============================================================
// GlobalReplace Tests
// ============================================================

TEST(PCREGlobalReplaceTest_587, ReplaceAllOccurrences_587) {
  std::string str = "aaa";
  PCRE re("a");
  int count = PCRE::GlobalReplace(&str, re, "b");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "bbb");
}

TEST(PCREGlobalReplaceTest_587, GlobalReplaceNoMatch_587) {
  std::string str = "hello";
  PCRE re("xyz");
  int count = PCRE::GlobalReplace(&str, re, "abc");
  EXPECT_EQ(count, 0);
  EXPECT_EQ(str, "hello");
}

TEST(PCREGlobalReplaceTest_587, GlobalReplaceMultipleOccurrences_587) {
  std::string str = "the cat sat on the mat";
  PCRE re("the");
  int count = PCRE::GlobalReplace(&str, re, "a");
  EXPECT_EQ(count, 2);
  EXPECT_EQ(str, "a cat sat on a mat");
}

// ============================================================
// Extract Tests
// ============================================================

TEST(PCREExtractTest_587, SimpleExtract_587) {
  std::string out;
  PCRE re("(\\w+)@(\\w+)");
  EXPECT_TRUE(PCRE::Extract("user@host", re, "\\1 at \\2", &out));
  EXPECT_EQ(out, "user at host");
}

TEST(PCREExtractTest_587, ExtractNoMatch_587) {
  std::string out;
  PCRE re("(\\d+)");
  EXPECT_FALSE(PCRE::Extract("no digits here", re, "\\1", &out));
}

TEST(PCREExtractTest_587, ExtractWholeMatch_587) {
  std::string out;
  PCRE re("\\w+");
  EXPECT_TRUE(PCRE::Extract("hello world", re, "\\0", &out));
  EXPECT_EQ(out, "hello");
}

// ============================================================
// QuoteMeta Tests
// ============================================================

TEST(PCREQuoteMetaTest_587, NoSpecialCharacters_587) {
  std::string result = PCRE::QuoteMeta("hello");
  EXPECT_EQ(result, "hello");
}

TEST(PCREQuoteMetaTest_587, SpecialCharactersAreEscaped_587) {
  std::string result = PCRE::QuoteMeta("hello.world");
  EXPECT_NE(result.find("\\"), std::string::npos);
  // The quoted version should match the literal "hello.world"
  PCRE re(result);
  EXPECT_TRUE(re.DoMatch("hello.world", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("helloXworld", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREQuoteMetaTest_587, EmptyString_587) {
  std::string result = PCRE::QuoteMeta("");
  EXPECT_EQ(result, "");
}

TEST(PCREQuoteMetaTest_587, AllSpecialChars_587) {
  std::string input = "^$.*+?()[]{}|\\";
  std::string quoted = PCRE::QuoteMeta(input);
  PCRE re(quoted);
  EXPECT_TRUE(re.DoMatch(input, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

// ============================================================
// CheckRewriteString Tests
// ============================================================

TEST(PCRECheckRewriteTest_587, ValidRewriteString_587) {
  PCRE re("(\\w+) (\\w+)");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("\\1-\\2", &error));
  EXPECT_TRUE(error.empty());
}

TEST(PCRECheckRewriteTest_587, InvalidRewriteStringTooManyBackrefs_587) {
  PCRE re("(\\w+)");
  std::string error;
  // Pattern has only 1 capturing group, \\2 is invalid
  EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
  EXPECT_FALSE(error.empty());
}

TEST(PCRECheckRewriteTest_587, RewriteWithNoBackrefs_587) {
  PCRE re("hello");
  std::string error;
  EXPECT_TRUE(re.CheckRewriteString("world", &error));
}

// ============================================================
// HitLimit / ClearHitLimit Tests
// ============================================================

TEST(PCREHitLimitTest_587, InitiallyNotHit_587) {
  PCRE re("hello");
  EXPECT_FALSE(re.HitLimit());
}

TEST(PCREHitLimitTest_587, ClearHitLimitResetsFlag_587) {
  PCRE re("hello");
  re.ClearHitLimit();
  EXPECT_FALSE(re.HitLimit());
}

// ============================================================
// Complex / Edge Case Tests
// ============================================================

TEST(PCREEdgeCaseTest_587, MatchEmptyStringWithEmptyPattern_587) {
  PCRE re("");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_587, MatchEmptyStringWithStarPattern_587) {
  PCRE re("a*");
  EXPECT_TRUE(re.DoMatch("", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_587, MatchLongString_587) {
  std::string longStr(10000, 'a');
  PCRE re("a+");
  EXPECT_TRUE(re.DoMatch(longStr, PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_587, ComplexPattern_587) {
  PCRE re("^(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})$");
  EXPECT_EQ(re.NumberOfCapturingGroups(), 4);
  EXPECT_TRUE(re.DoMatch("192.168.1.1", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("999.999.999.999.999", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_587, PatternWithSpecialCharacters_587) {
  PCRE re("\\d+\\.\\d+");
  EXPECT_TRUE(re.DoMatch("3.14", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
  EXPECT_FALSE(re.DoMatch("3X14", PCRE::ANCHOR_BOTH, nullptr, nullptr, 0));
}

TEST(PCREEdgeCaseTest_587, ReplaceEmptyMatch_587) {
  std::string str = "abc";
  PCRE re("b*");
  // Replace first empty match
  PCRE::Replace(&str, re, "X");
  // Behavior depends on implementation, but should not crash
}

TEST(PCREEdgeCaseTest_587, GlobalReplaceWithCapturingGroup_587) {
  std::string str = "abc def ghi";
  PCRE re("(\\w+)");
  int count = PCRE::GlobalReplace(&str, re, "[\\1]");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(str, "[abc] [def] [ghi]");
}

}  // namespace re2
