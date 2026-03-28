#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>
#include "re2/re2.h"

using namespace re2;

// ==================== RE2 Construction Tests ====================

TEST(RE2ConstructionTest_60, ConstructFromCString_60) {
    RE2 re("hello");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ("hello", re.pattern());
}

TEST(RE2ConstructionTest_60, ConstructFromStdString_60) {
    std::string pattern = "world";
    RE2 re(pattern);
    EXPECT_TRUE(re.ok());
    EXPECT_EQ("world", re.pattern());
}

TEST(RE2ConstructionTest_60, ConstructFromStringView_60) {
    absl::string_view sv = "test.*pattern";
    RE2 re(sv);
    EXPECT_TRUE(re.ok());
    EXPECT_EQ("test.*pattern", re.pattern());
}

TEST(RE2ConstructionTest_60, ConstructWithOptions_60) {
    RE2::Options opts;
    opts.set_case_sensitive(false);
    RE2 re("Hello", opts);
    EXPECT_TRUE(re.ok());
}

TEST(RE2ConstructionTest_60, InvalidPattern_60) {
    RE2 re("(unclosed");
    EXPECT_FALSE(re.ok());
    EXPECT_NE("", re.error());
    EXPECT_NE(RE2::NoError, re.error_code());
}

TEST(RE2ConstructionTest_60, EmptyPattern_60) {
    RE2 re("");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ("", re.pattern());
}

// ==================== FullMatch Tests ====================

TEST(RE2FullMatchTest_60, SimpleFullMatch_60) {
    EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST(RE2FullMatchTest_60, FullMatchFails_60) {
    EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST(RE2FullMatchTest_60, FullMatchWithCapture_60) {
    int n;
    EXPECT_TRUE(RE2::FullMatch("12345", "(\\d+)", &n));
    EXPECT_EQ(12345, n);
}

TEST(RE2FullMatchTest_60, FullMatchWithStringCapture_60) {
    std::string s;
    EXPECT_TRUE(RE2::FullMatch("hello", "(\\w+)", &s));
    EXPECT_EQ("hello", s);
}

TEST(RE2FullMatchTest_60, FullMatchMultipleCaptures_60) {
    std::string a, b;
    EXPECT_TRUE(RE2::FullMatch("hello-world", "(\\w+)-(\\w+)", &a, &b));
    EXPECT_EQ("hello", a);
    EXPECT_EQ("world", b);
}

TEST(RE2FullMatchTest_60, FullMatchEmptyString_60) {
    EXPECT_TRUE(RE2::FullMatch("", ""));
    EXPECT_TRUE(RE2::FullMatch("", ".*"));
}

TEST(RE2FullMatchTest_60, FullMatchNoMatch_60) {
    EXPECT_FALSE(RE2::FullMatch("abc", "\\d+"));
}

// ==================== PartialMatch Tests ====================

TEST(RE2PartialMatchTest_60, SimplePartialMatch_60) {
    EXPECT_TRUE(RE2::PartialMatch("hello world", "ello"));
}

TEST(RE2PartialMatchTest_60, PartialMatchFails_60) {
    EXPECT_FALSE(RE2::PartialMatch("hello", "xyz"));
}

TEST(RE2PartialMatchTest_60, PartialMatchWithCapture_60) {
    int n;
    EXPECT_TRUE(RE2::PartialMatch("abc 123 def", "(\\d+)", &n));
    EXPECT_EQ(123, n);
}

TEST(RE2PartialMatchTest_60, PartialMatchEmptyPattern_60) {
    EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ==================== Consume Tests ====================

TEST(RE2ConsumeTest_60, SimpleConsume_60) {
    absl::string_view input = "abc123def";
    std::string word;
    EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &word));
    EXPECT_EQ("abc", word);
    EXPECT_EQ("123def", input);
}

TEST(RE2ConsumeTest_60, ConsumeFails_60) {
    absl::string_view input = "123abc";
    std::string word;
    EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &word));
}

TEST(RE2ConsumeTest_60, ConsumeMultipleTimes_60) {
    absl::string_view input = "aaa111bbb222";
    std::string s;
    EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &s));
    EXPECT_EQ("aaa", s);
    int n;
    EXPECT_TRUE(RE2::Consume(&input, "(\\d+)", &n));
    EXPECT_EQ(111, n);
}

// ==================== FindAndConsume Tests ====================

TEST(RE2FindAndConsumeTest_60, SimpleFindAndConsume_60) {
    absl::string_view input = "abc 123 def 456";
    int n;
    EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
    EXPECT_EQ(123, n);
    EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &n));
    EXPECT_EQ(456, n);
    EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &n));
}

// ==================== Replace Tests ====================

TEST(RE2ReplaceTest_60, SimpleReplace_60) {
    std::string s = "hello world";
    EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
    EXPECT_EQ("hello there", s);
}

TEST(RE2ReplaceTest_60, ReplaceNoMatch_60) {
    std::string s = "hello world";
    EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
    EXPECT_EQ("hello world", s);
}

TEST(RE2ReplaceTest_60, ReplaceWithBackreference_60) {
    std::string s = "hello world";
    EXPECT_TRUE(RE2::Replace(&s, "(\\w+)", "\\1!"));
    EXPECT_EQ("hello! world", s);
}

TEST(RE2ReplaceTest_60, ReplaceFirstOccurrenceOnly_60) {
    std::string s = "aaa bbb aaa";
    RE2::Replace(&s, "aaa", "ccc");
    EXPECT_EQ("ccc bbb aaa", s);
}

// ==================== GlobalReplace Tests ====================

TEST(RE2GlobalReplaceTest_60, SimpleGlobalReplace_60) {
    std::string s = "aaa bbb aaa";
    int count = RE2::GlobalReplace(&s, "aaa", "ccc");
    EXPECT_EQ("ccc bbb ccc", s);
    EXPECT_EQ(2, count);
}

TEST(RE2GlobalReplaceTest_60, GlobalReplaceNoMatch_60) {
    std::string s = "hello";
    int count = RE2::GlobalReplace(&s, "xyz", "abc");
    EXPECT_EQ("hello", s);
    EXPECT_EQ(0, count);
}

TEST(RE2GlobalReplaceTest_60, GlobalReplaceEmptyMatch_60) {
    std::string s = "abc";
    int count = RE2::GlobalReplace(&s, "", "-");
    // Each position between and around characters should be replaced
    EXPECT_GT(count, 0);
}

// ==================== Extract Tests ====================

TEST(RE2ExtractTest_60, SimpleExtract_60) {
    std::string out;
    EXPECT_TRUE(RE2::Extract("boris@kremvax.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
    EXPECT_EQ("kremvax!boris", out);
}

TEST(RE2ExtractTest_60, ExtractNoMatch_60) {
    std::string out;
    EXPECT_FALSE(RE2::Extract("no-email-here", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// ==================== QuoteMeta Tests ====================

TEST(RE2QuoteMetaTest_60, SimpleQuoteMeta_60) {
    std::string quoted = RE2::QuoteMeta("hello");
    EXPECT_EQ("hello", quoted);
}

TEST(RE2QuoteMetaTest_60, QuoteMetaSpecialChars_60) {
    std::string quoted = RE2::QuoteMeta("a.b*c+d?e");
    // The quoted version should escape special regex characters
    EXPECT_TRUE(RE2::FullMatch("a.b*c+d?e", quoted));
}

TEST(RE2QuoteMetaTest_60, QuoteMetaEmpty_60) {
    std::string quoted = RE2::QuoteMeta("");
    EXPECT_EQ("", quoted);
}

TEST(RE2QuoteMetaTest_60, QuoteMetaBackslash_60) {
    std::string quoted = RE2::QuoteMeta("a\\b");
    EXPECT_TRUE(RE2::FullMatch("a\\b", quoted));
}

TEST(RE2QuoteMetaTest_60, QuoteMetaParensAndBrackets_60) {
    std::string quoted = RE2::QuoteMeta("(a)[b]{c}");
    EXPECT_TRUE(RE2::FullMatch("(a)[b]{c}", quoted));
}

TEST(RE2QuoteMetaTest_60, QuoteMetaPipe_60) {
    std::string quoted = RE2::QuoteMeta("a|b");
    EXPECT_TRUE(RE2::FullMatch("a|b", quoted));
    EXPECT_FALSE(RE2::FullMatch("a", quoted));
}

// ==================== Match Tests ====================

TEST(RE2MatchTest_60, SimpleMatch_60) {
    RE2 re("(\\w+)");
    EXPECT_TRUE(re.ok());
    absl::string_view submatch;
    EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::UNANCHORED, &submatch, 1));
    EXPECT_EQ("hello", submatch);
}

TEST(RE2MatchTest_60, MatchAnchored_60) {
    RE2 re("\\d+");
    EXPECT_FALSE(re.Match("abc123", 0, 6, RE2::ANCHOR_START, nullptr, 0));
    EXPECT_TRUE(re.Match("123abc", 0, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST(RE2MatchTest_60, MatchBothAnchored_60) {
    RE2 re("\\d+");
    EXPECT_FALSE(re.Match("123abc", 0, 6, RE2::ANCHOR_BOTH, nullptr, 0));
    EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST(RE2MatchTest_60, MatchWithStartPos_60) {
    RE2 re("\\d+");
    absl::string_view submatch;
    EXPECT_TRUE(re.Match("abc123def", 3, 9, RE2::UNANCHORED, &submatch, 1));
    EXPECT_EQ("123", submatch);
}

TEST(RE2MatchTest_60, MatchNoSubmatch_60) {
    RE2 re("hello");
    EXPECT_TRUE(re.Match("say hello there", 0, 15, RE2::UNANCHORED, nullptr, 0));
}

// ==================== NumberOfCapturingGroups Tests ====================

TEST(RE2CapturingGroupsTest_60, NoCapturingGroups_60) {
    RE2 re("hello");
    EXPECT_EQ(0, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_60, OneCapturingGroup_60) {
    RE2 re("(hello)");
    EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_60, MultipleCapturingGroups_60) {
    RE2 re("(\\w+)@(\\w+)\\.(\\w+)");
    EXPECT_EQ(3, re.NumberOfCapturingGroups());
}

TEST(RE2CapturingGroupsTest_60, NonCapturingGroupNotCounted_60) {
    RE2 re("(?:hello)(world)");
    EXPECT_EQ(1, re.NumberOfCapturingGroups());
}

// ==================== NamedCapturingGroups Tests ====================

TEST(RE2NamedCapturingGroupsTest_60, NoNamedGroups_60) {
    RE2 re("(\\w+)");
    const auto& named = re.NamedCapturingGroups();
    EXPECT_TRUE(named.empty());
}

TEST(RE2NamedCapturingGroupsTest_60, WithNamedGroups_60) {
    RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
    EXPECT_TRUE(re.ok());
    const auto& named = re.NamedCapturingGroups();
    EXPECT_EQ(2u, named.size());
    EXPECT_EQ(1, named.at("first"));
    EXPECT_EQ(2, named.at("second"));
}

// ==================== CapturingGroupNames Tests ====================

TEST(RE2CapturingGroupNamesTest_60, WithNamedGroups_60) {
    RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
    EXPECT_TRUE(re.ok());
    const auto& names = re.CapturingGroupNames();
    EXPECT_EQ(2u, names.size());
    EXPECT_EQ("first", names.at(1));
    EXPECT_EQ("second", names.at(2));
}

// ==================== ProgramSize Tests ====================

TEST(RE2ProgramSizeTest_60, NonZeroProgramSize_60) {
    RE2 re("hello.*world");
    EXPECT_TRUE(re.ok());
    EXPECT_GT(re.ProgramSize(), 0);
}

TEST(RE2ProgramSizeTest_60, ReverseProgramSize_60) {
    RE2 re("hello.*world");
    EXPECT_TRUE(re.ok());
    EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ==================== PossibleMatchRange Tests ====================

TEST(RE2PossibleMatchRangeTest_60, SimpleRange_60) {
    RE2 re("hello");
    std::string min_str, max_str;
    EXPECT_TRUE(re.PossibleMatchRange(&min_str, &max_str, 10));
    EXPECT_LE(min_str, "hello");
    EXPECT_GE(max_str, "hello");
}

// ==================== CheckRewriteString Tests ====================

TEST(RE2CheckRewriteStringTest_60, ValidRewrite_60) {
    RE2 re("(\\w+)");
    std::string error;
    EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST(RE2CheckRewriteStringTest_60, InvalidRewrite_60) {
    RE2 re("(\\w+)");
    std::string error;
    EXPECT_FALSE(re.CheckRewriteString("\\2", &error));
    EXPECT_NE("", error);
}

// ==================== MaxSubmatch Tests ====================

TEST(RE2MaxSubmatchTest_60, NoSubmatch_60) {
    EXPECT_EQ(0, RE2::MaxSubmatch("no backrefs"));
}

TEST(RE2MaxSubmatchTest_60, WithSubmatch_60) {
    EXPECT_EQ(3, RE2::MaxSubmatch("\\1 \\2 \\3"));
}

TEST(RE2MaxSubmatchTest_60, SingleSubmatch_60) {
    EXPECT_EQ(1, RE2::MaxSubmatch("\\1"));
}

// ==================== ProgramFanout Tests ====================

TEST(RE2ProgramFanoutTest_60, ProgramFanout_60) {
    RE2 re("hello|world");
    EXPECT_TRUE(re.ok());
    std::vector<int> histogram;
    int fanout = re.ProgramFanout(&histogram);
    EXPECT_GE(fanout, 0);
}

TEST(RE2ProgramFanoutTest_60, ReverseProgramFanout_60) {
    RE2 re("hello|world");
    EXPECT_TRUE(re.ok());
    std::vector<int> histogram;
    int fanout = re.ReverseProgramFanout(&histogram);
    EXPECT_GE(fanout, 0);
}

// ==================== Options Tests ====================

TEST(RE2OptionsTest_60, CaseInsensitive_60) {
    RE2::Options opts;
    opts.set_case_sensitive(false);
    RE2 re("hello", opts);
    EXPECT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("HELLO", re));
    EXPECT_TRUE(RE2::FullMatch("Hello", re));
    EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2OptionsTest_60, DefaultCaseSensitive_60) {
    RE2 re("hello");
    EXPECT_TRUE(RE2::FullMatch("hello", re));
    EXPECT_FALSE(RE2::FullMatch("HELLO", re));
}

// ==================== Error Handling Tests ====================

TEST(RE2ErrorTest_60, ValidPatternNoError_60) {
    RE2 re("abc");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(RE2::NoError, re.error_code());
    EXPECT_EQ("", re.error());
}

TEST(RE2ErrorTest_60, InvalidPatternError_60) {
    RE2 re("[unclosed");
    EXPECT_FALSE(re.ok());
    EXPECT_NE(RE2::NoError, re.error_code());
    EXPECT_NE("", re.error());
}

TEST(RE2ErrorTest_60, InvalidRepetition_60) {
    RE2 re("*");
    EXPECT_FALSE(re.ok());
}

// ==================== Rewrite Tests ====================

TEST(RE2RewriteTest_60, SimpleRewrite_60) {
    RE2 re("(\\w+)");
    std::string out;
    absl::string_view vec[] = {"fullmatch", "hello"};
    EXPECT_TRUE(re.Rewrite(&out, "\\1-replaced", vec, 2));
    EXPECT_EQ("hello-replaced", out);
}

TEST(RE2RewriteTest_60, RewriteWithZeroRef_60) {
    RE2 re("(\\w+)");
    std::string out;
    absl::string_view vec[] = {"fullmatch", "hello"};
    EXPECT_TRUE(re.Rewrite(&out, "\\0", vec, 2));
    EXPECT_EQ("fullmatch", out);
}

// ==================== Edge Cases ====================

TEST(RE2EdgeCaseTest_60, VeryLongPattern_60) {
    std::string long_pattern(1000, 'a');
    RE2 re(long_pattern);
    EXPECT_TRUE(re.ok());
    std::string long_text(1000, 'a');
    EXPECT_TRUE(RE2::FullMatch(long_text, re));
    std::string short_text(999, 'a');
    EXPECT_FALSE(RE2::FullMatch(short_text, re));
}

TEST(RE2EdgeCaseTest_60, MatchEmptyString_60) {
    RE2 re(".*");
    EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST(RE2EdgeCaseTest_60, FullMatchWithRegexObject_60) {
    RE2 re("\\d{3}-\\d{4}");
    EXPECT_TRUE(RE2::FullMatch("123-4567", re));
    EXPECT_FALSE(RE2::FullMatch("12-4567", re));
    EXPECT_FALSE(RE2::FullMatch("123-456", re));
}

TEST(RE2EdgeCaseTest_60, MatchStartAndEndPositions_60) {
    RE2 re("\\d+");
    absl::string_view text = "abc123def";
    absl::string_view submatch;
    // Only search in the substring "c12"
    EXPECT_TRUE(re.Match(text, 2, 5, RE2::UNANCHORED, &submatch, 1));
    EXPECT_EQ("12", submatch);
}

TEST(RE2EdgeCaseTest_60, MatchEmptyRange_60) {
    RE2 re(".*");
    absl::string_view text = "hello";
    EXPECT_TRUE(re.Match(text, 0, 0, RE2::ANCHOR_BOTH, nullptr, 0));
}

// ==================== FullMatchN / PartialMatchN Tests ====================

TEST(RE2FullMatchNTest_60, FullMatchNWithNoArgs_60) {
    RE2 re("hello");
    EXPECT_TRUE(RE2::FullMatchN("hello", re, nullptr, 0));
    EXPECT_FALSE(RE2::FullMatchN("world", re, nullptr, 0));
}

TEST(RE2PartialMatchNTest_60, PartialMatchNWithNoArgs_60) {
    RE2 re("hello");
    EXPECT_TRUE(RE2::PartialMatchN("say hello", re, nullptr, 0));
    EXPECT_FALSE(RE2::PartialMatchN("say world", re, nullptr, 0));
}

// ==================== ConsumeN / FindAndConsumeN Tests ====================

TEST(RE2ConsumeNTest_60, ConsumeNWithNoArgs_60) {
    RE2 re("\\d+");
    absl::string_view input = "123abc";
    EXPECT_TRUE(RE2::ConsumeN(&input, re, nullptr, 0));
    EXPECT_EQ("abc", input);
}

TEST(RE2FindAndConsumeNTest_60, FindAndConsumeNWithNoArgs_60) {
    RE2 re("\\d+");
    absl::string_view input = "abc123def";
    EXPECT_TRUE(RE2::FindAndConsumeN(&input, re, nullptr, 0));
    EXPECT_EQ("def", input);
}
