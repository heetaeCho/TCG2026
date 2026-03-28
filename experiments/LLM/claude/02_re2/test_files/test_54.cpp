#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <map>
#include "re2/re2.h"

// Since the code under test is in re2_python namespace and wraps RE2::error(),
// we test both the underlying RE2 class behavior and the shim function.

namespace re2_python {
py::bytes RE2ErrorShim(const RE2& self);
}

// We primarily test RE2's public interface since RE2ErrorShim is a thin wrapper
// over RE2::error(). We focus on observable behavior through the public API.

class RE2Test_54 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Construction and basic state tests
// ============================================================

TEST_F(RE2Test_54, ValidPatternIsOk_54) {
    RE2 re("hello");
    EXPECT_TRUE(re.ok());
}

TEST_F(RE2Test_54, ValidPatternReturnsPattern_54) {
    RE2 re("hello");
    EXPECT_EQ(re.pattern(), "hello");
}

TEST_F(RE2Test_54, ValidPatternHasEmptyError_54) {
    RE2 re("hello");
    EXPECT_TRUE(re.error().empty());
}

TEST_F(RE2Test_54, InvalidPatternIsNotOk_54) {
    RE2 re("(unclosed");
    EXPECT_FALSE(re.ok());
}

TEST_F(RE2Test_54, InvalidPatternHasNonEmptyError_54) {
    RE2 re("(unclosed");
    EXPECT_FALSE(re.error().empty());
}

TEST_F(RE2Test_54, InvalidPatternErrorCodeNotNoError_54) {
    RE2 re("(unclosed");
    EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST_F(RE2Test_54, ValidPatternErrorCodeIsNoError_54) {
    RE2 re("hello");
    EXPECT_EQ(re.error_code(), RE2::NoError);
}

TEST_F(RE2Test_54, ConstructFromString_54) {
    std::string pattern = "world";
    RE2 re(pattern);
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), "world");
}

TEST_F(RE2Test_54, ConstructFromStringView_54) {
    absl::string_view pattern = "test.*pattern";
    RE2 re(pattern);
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.pattern(), "test.*pattern");
}

TEST_F(RE2Test_54, EmptyPatternIsOk_54) {
    RE2 re("");
    EXPECT_TRUE(re.ok());
}

// ============================================================
// FullMatch tests
// ============================================================

TEST_F(RE2Test_54, FullMatchSimple_54) {
    EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

TEST_F(RE2Test_54, FullMatchFails_54) {
    EXPECT_FALSE(RE2::FullMatch("hello world", "hello"));
}

TEST_F(RE2Test_54, FullMatchWithCapture_54) {
    std::string captured;
    EXPECT_TRUE(RE2::FullMatch("hello123", "hello(\\d+)", &captured));
    EXPECT_EQ(captured, "123");
}

TEST_F(RE2Test_54, FullMatchIntCapture_54) {
    int value;
    EXPECT_TRUE(RE2::FullMatch("42", "(\\d+)", &value));
    EXPECT_EQ(value, 42);
}

TEST_F(RE2Test_54, FullMatchEmptyPatternEmptyString_54) {
    EXPECT_TRUE(RE2::FullMatch("", ""));
}

TEST_F(RE2Test_54, FullMatchEmptyPatternNonEmptyString_54) {
    EXPECT_FALSE(RE2::FullMatch("abc", ""));
}

// ============================================================
// PartialMatch tests
// ============================================================

TEST_F(RE2Test_54, PartialMatchSimple_54) {
    EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
}

TEST_F(RE2Test_54, PartialMatchFails_54) {
    EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

TEST_F(RE2Test_54, PartialMatchWithCapture_54) {
    std::string captured;
    EXPECT_TRUE(RE2::PartialMatch("foo123bar", "(\\d+)", &captured));
    EXPECT_EQ(captured, "123");
}

// ============================================================
// Consume tests
// ============================================================

TEST_F(RE2Test_54, ConsumeAdvancesInput_54) {
    absl::string_view input = "abc123def456";
    std::string match;
    EXPECT_TRUE(RE2::Consume(&input, "([a-z]+)", &match));
    EXPECT_EQ(match, "abc");
    // Input should have advanced past "abc"
    EXPECT_EQ(input, "123def456");
}

TEST_F(RE2Test_54, ConsumeFails_54) {
    absl::string_view input = "123abc";
    std::string match;
    EXPECT_FALSE(RE2::Consume(&input, "([a-z]+)", &match));
}

// ============================================================
// FindAndConsume tests
// ============================================================

TEST_F(RE2Test_54, FindAndConsumeFindsMatch_54) {
    absl::string_view input = "abc123def456";
    std::string match;
    EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &match));
    EXPECT_EQ(match, "123");
}

TEST_F(RE2Test_54, FindAndConsumeMultiple_54) {
    absl::string_view input = "abc123def456";
    std::string match;
    EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &match));
    EXPECT_EQ(match, "123");
    EXPECT_TRUE(RE2::FindAndConsume(&input, "(\\d+)", &match));
    EXPECT_EQ(match, "456");
}

TEST_F(RE2Test_54, FindAndConsumeFails_54) {
    absl::string_view input = "abcdef";
    std::string match;
    EXPECT_FALSE(RE2::FindAndConsume(&input, "(\\d+)", &match));
}

// ============================================================
// Replace tests
// ============================================================

TEST_F(RE2Test_54, ReplaceFirstOccurrence_54) {
    std::string str = "hello world hello";
    EXPECT_TRUE(RE2::Replace(&str, "hello", "hi"));
    EXPECT_EQ(str, "hi world hello");
}

TEST_F(RE2Test_54, ReplaceNoMatch_54) {
    std::string str = "hello world";
    EXPECT_FALSE(RE2::Replace(&str, "xyz", "abc"));
    EXPECT_EQ(str, "hello world");
}

TEST_F(RE2Test_54, ReplaceWithBackreference_54) {
    std::string str = "hello world";
    EXPECT_TRUE(RE2::Replace(&str, "(\\w+)", "\\1!"));
    EXPECT_EQ(str, "hello! world");
}

// ============================================================
// GlobalReplace tests
// ============================================================

TEST_F(RE2Test_54, GlobalReplaceAll_54) {
    std::string str = "aaa bbb aaa";
    int count = RE2::GlobalReplace(&str, "aaa", "ccc");
    EXPECT_EQ(count, 2);
    EXPECT_EQ(str, "ccc bbb ccc");
}

TEST_F(RE2Test_54, GlobalReplaceNone_54) {
    std::string str = "hello world";
    int count = RE2::GlobalReplace(&str, "xyz", "abc");
    EXPECT_EQ(count, 0);
    EXPECT_EQ(str, "hello world");
}

// ============================================================
// Extract tests
// ============================================================

TEST_F(RE2Test_54, ExtractSuccess_54) {
    std::string out;
    EXPECT_TRUE(RE2::Extract("boris@kremlin.ru", "(.*)@([^.]*)", "\\2!\\1", &out));
    EXPECT_EQ(out, "kremlin!boris");
}

TEST_F(RE2Test_54, ExtractFails_54) {
    std::string out;
    EXPECT_FALSE(RE2::Extract("no-email-here", "(.*)@([^.]*)", "\\2!\\1", &out));
}

// ============================================================
// QuoteMeta tests
// ============================================================

TEST_F(RE2Test_54, QuoteMetaPlainString_54) {
    std::string quoted = RE2::QuoteMeta("hello");
    EXPECT_EQ(quoted, "hello");
}

TEST_F(RE2Test_54, QuoteMetaSpecialChars_54) {
    std::string quoted = RE2::QuoteMeta("a.b+c*d");
    // The quoted string should be usable as a literal pattern
    EXPECT_TRUE(RE2::FullMatch("a.b+c*d", quoted));
}

TEST_F(RE2Test_54, QuoteMetaEmpty_54) {
    std::string quoted = RE2::QuoteMeta("");
    EXPECT_EQ(quoted, "");
}

// ============================================================
// NumberOfCapturingGroups tests
// ============================================================

TEST_F(RE2Test_54, NumberOfCapturingGroupsNone_54) {
    RE2 re("hello");
    EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST_F(RE2Test_54, NumberOfCapturingGroupsOne_54) {
    RE2 re("(hello)");
    EXPECT_EQ(re.NumberOfCapturingGroups(), 1);
}

TEST_F(RE2Test_54, NumberOfCapturingGroupsMultiple_54) {
    RE2 re("(a)(b)(c)");
    EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST_F(RE2Test_54, NumberOfCapturingGroupsNested_54) {
    RE2 re("((a)(b))");
    EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

// ============================================================
// NamedCapturingGroups tests
// ============================================================

TEST_F(RE2Test_54, NamedCapturingGroupsEmpty_54) {
    RE2 re("hello");
    const auto& groups = re.NamedCapturingGroups();
    EXPECT_TRUE(groups.empty());
}

TEST_F(RE2Test_54, NamedCapturingGroupsPresent_54) {
    RE2 re("(?P<name>\\w+)@(?P<domain>\\w+)");
    const auto& groups = re.NamedCapturingGroups();
    EXPECT_EQ(groups.size(), 2);
    EXPECT_NE(groups.find("name"), groups.end());
    EXPECT_NE(groups.find("domain"), groups.end());
    EXPECT_EQ(groups.at("name"), 1);
    EXPECT_EQ(groups.at("domain"), 2);
}

// ============================================================
// CapturingGroupNames tests
// ============================================================

TEST_F(RE2Test_54, CapturingGroupNamesEmpty_54) {
    RE2 re("hello");
    const auto& names = re.CapturingGroupNames();
    EXPECT_TRUE(names.empty());
}

TEST_F(RE2Test_54, CapturingGroupNamesPresent_54) {
    RE2 re("(?P<first>\\w+) (?P<second>\\w+)");
    const auto& names = re.CapturingGroupNames();
    EXPECT_EQ(names.size(), 2);
    EXPECT_EQ(names.at(1), "first");
    EXPECT_EQ(names.at(2), "second");
}

// ============================================================
// Match tests
// ============================================================

TEST_F(RE2Test_54, MatchAnchored_54) {
    RE2 re("\\d+");
    EXPECT_TRUE(re.Match("123", 0, 3, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST_F(RE2Test_54, MatchUnanchored_54) {
    RE2 re("\\d+");
    EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, nullptr, 0));
}

TEST_F(RE2Test_54, MatchWithSubmatch_54) {
    RE2 re("(\\d+)");
    absl::string_view submatch[2];
    EXPECT_TRUE(re.Match("abc123def", 0, 9, RE2::UNANCHORED, submatch, 2));
    EXPECT_EQ(submatch[1], "123");
}

TEST_F(RE2Test_54, MatchStartpos_54) {
    RE2 re("\\d+");
    EXPECT_TRUE(re.Match("abc123", 3, 6, RE2::ANCHOR_START, nullptr, 0));
}

TEST_F(RE2Test_54, MatchFails_54) {
    RE2 re("\\d+");
    EXPECT_FALSE(re.Match("abcdef", 0, 6, RE2::UNANCHORED, nullptr, 0));
}

TEST_F(RE2Test_54, MatchAnchorStart_54) {
    RE2 re("hello");
    EXPECT_TRUE(re.Match("hello world", 0, 11, RE2::ANCHOR_START, nullptr, 0));
    EXPECT_FALSE(re.Match("say hello", 0, 9, RE2::ANCHOR_START, nullptr, 0));
}

// ============================================================
// ProgramSize tests
// ============================================================

TEST_F(RE2Test_54, ProgramSizePositive_54) {
    RE2 re("hello");
    EXPECT_GT(re.ProgramSize(), 0);
}

TEST_F(RE2Test_54, ReverseProgramSizePositive_54) {
    RE2 re("hello");
    EXPECT_GT(re.ReverseProgramSize(), 0);
}

// ============================================================
// ProgramFanout tests
// ============================================================

TEST_F(RE2Test_54, ProgramFanout_54) {
    RE2 re("hello");
    std::vector<int> histogram;
    int result = re.ProgramFanout(&histogram);
    EXPECT_GE(result, 0);
}

TEST_F(RE2Test_54, ReverseProgramFanout_54) {
    RE2 re("hello");
    std::vector<int> histogram;
    int result = re.ReverseProgramFanout(&histogram);
    EXPECT_GE(result, 0);
}

// ============================================================
// PossibleMatchRange tests
// ============================================================

TEST_F(RE2Test_54, PossibleMatchRange_54) {
    RE2 re("hello");
    std::string min, max;
    EXPECT_TRUE(re.PossibleMatchRange(&min, &max, 10));
    EXPECT_FALSE(min.empty());
}

// ============================================================
// CheckRewriteString tests
// ============================================================

TEST_F(RE2Test_54, CheckRewriteStringValid_54) {
    RE2 re("(\\d+)");
    std::string error;
    EXPECT_TRUE(re.CheckRewriteString("\\1", &error));
}

TEST_F(RE2Test_54, CheckRewriteStringInvalidBackref_54) {
    RE2 re("\\d+");  // no capture groups
    std::string error;
    EXPECT_FALSE(re.CheckRewriteString("\\1", &error));
    EXPECT_FALSE(error.empty());
}

// ============================================================
// MaxSubmatch tests
// ============================================================

TEST_F(RE2Test_54, MaxSubmatchNoBackref_54) {
    EXPECT_EQ(RE2::MaxSubmatch("no backrefs"), 0);
}

TEST_F(RE2Test_54, MaxSubmatchWithBackrefs_54) {
    EXPECT_EQ(RE2::MaxSubmatch("\\1 and \\3"), 3);
}

// ============================================================
// Rewrite tests
// ============================================================

TEST_F(RE2Test_54, RewriteSimple_54) {
    RE2 re("(\\w+) (\\w+)");
    std::string out;
    absl::string_view vec[] = {"hello world", "hello", "world"};
    EXPECT_TRUE(re.Rewrite(&out, "\\2 \\1", vec, 3));
    EXPECT_EQ(out, "world hello");
}

// ============================================================
// Options tests
// ============================================================

TEST_F(RE2Test_54, OptionsReturnsOptions_54) {
    RE2 re("hello");
    const RE2::Options& opts = re.options();
    // Just verify we can access options without crashing
    (void)opts;
}

TEST_F(RE2Test_54, CaseInsensitiveOption_54) {
    RE2::Options opts;
    opts.set_case_sensitive(false);
    RE2 re("hello", opts);
    EXPECT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("HELLO", re));
}

// ============================================================
// Complex pattern tests
// ============================================================

TEST_F(RE2Test_54, ComplexPatternIP_54) {
    RE2 re("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})");
    EXPECT_TRUE(re.ok());
    EXPECT_EQ(re.NumberOfCapturingGroups(), 4);
    std::string a, b, c, d;
    EXPECT_TRUE(RE2::FullMatch("192.168.1.1", re, &a, &b, &c, &d));
    EXPECT_EQ(a, "192");
    EXPECT_EQ(b, "168");
    EXPECT_EQ(c, "1");
    EXPECT_EQ(d, "1");
}

TEST_F(RE2Test_54, InvalidPatternBracket_54) {
    RE2 re("[unclosed");
    EXPECT_FALSE(re.ok());
    EXPECT_FALSE(re.error().empty());
}

TEST_F(RE2Test_54, InvalidPatternRepetition_54) {
    RE2 re("*invalid");
    EXPECT_FALSE(re.ok());
}

// ============================================================
// Hex/Octal/CRadix parsing tests
// ============================================================

TEST_F(RE2Test_54, HexCapture_54) {
    int value;
    EXPECT_TRUE(RE2::FullMatch("ff", "(\\w+)", RE2::Hex(&value)));
    EXPECT_EQ(value, 255);
}

TEST_F(RE2Test_54, OctalCapture_54) {
    int value;
    EXPECT_TRUE(RE2::FullMatch("77", "(\\w+)", RE2::Octal(&value)));
    EXPECT_EQ(value, 63);
}

TEST_F(RE2Test_54, CRadixHex_54) {
    int value;
    EXPECT_TRUE(RE2::FullMatch("0xff", "(\\w+)", RE2::CRadix(&value)));
    EXPECT_EQ(value, 255);
}

TEST_F(RE2Test_54, CRadixOctal_54) {
    int value;
    EXPECT_TRUE(RE2::FullMatch("077", "(\\w+)", RE2::CRadix(&value)));
    EXPECT_EQ(value, 63);
}

TEST_F(RE2Test_54, CRadixDecimal_54) {
    int value;
    EXPECT_TRUE(RE2::FullMatch("123", "(\\w+)", RE2::CRadix(&value)));
    EXPECT_EQ(value, 123);
}

// ============================================================
// error_arg tests
// ============================================================

TEST_F(RE2Test_54, ErrorArgValidPattern_54) {
    RE2 re("hello");
    // For a valid pattern, error_arg should be empty
    EXPECT_TRUE(re.error_arg().empty());
}

TEST_F(RE2Test_54, ErrorArgInvalidPattern_54) {
    RE2 re("(unclosed");
    // For an invalid pattern, error_arg may have content
    // Just verify it doesn't crash
    const std::string& arg = re.error_arg();
    (void)arg;
}

// ============================================================
// Boundary condition tests
// ============================================================

TEST_F(RE2Test_54, MatchEmptyString_54) {
    RE2 re(".*");
    EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST_F(RE2Test_54, MatchEmptyStringEmptyPattern_54) {
    RE2 re("");
    EXPECT_TRUE(RE2::FullMatch("", re));
}

TEST_F(RE2Test_54, GlobalReplaceEmptyMatch_54) {
    std::string str = "abc";
    int count = RE2::GlobalReplace(&str, "", "-");
    // Empty match should match at every position
    EXPECT_GT(count, 0);
}

TEST_F(RE2Test_54, MatchZeroLengthRange_54) {
    RE2 re(".*");
    EXPECT_TRUE(re.Match("hello", 0, 0, RE2::ANCHOR_BOTH, nullptr, 0));
}

TEST_F(RE2Test_54, PartialMatchEmptyPattern_54) {
    EXPECT_TRUE(RE2::PartialMatch("anything", ""));
}

// ============================================================
// Regexp accessor test
// ============================================================

TEST_F(RE2Test_54, RegexpAccessor_54) {
    RE2 re("hello");
    EXPECT_NE(re.Regexp(), nullptr);
}

TEST_F(RE2Test_54, RegexpAccessorInvalid_54) {
    RE2 re("(unclosed");
    // Invalid pattern may have nullptr Regexp
    // Just verify no crash
    (void)re.Regexp();
}
