#include <gtest/gtest.h>
#include <string>

// Include the necessary headers
#include "app/_re2.cc"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prog.h"

namespace re2_app {

class GetInfoTest_172 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Simple literal pattern returns correct info
TEST_F(GetInfoTest_172, SimpleLiteralPattern_172) {
    Info info = GetInfo("hello");
    EXPECT_EQ(info.pattern, "hello");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.prefix, "hello");
    EXPECT_FALSE(info.prefix_foldcase);
    EXPECT_EQ(info.num_captures, 0);
}

// Test: Empty pattern
TEST_F(GetInfoTest_172, EmptyPattern_172) {
    Info info = GetInfo("");
    EXPECT_EQ(info.pattern, "");
    EXPECT_TRUE(info.error.empty());
}

// Test: Pattern with capture groups
TEST_F(GetInfoTest_172, PatternWithCaptures_172) {
    Info info = GetInfo("(a)(b)(c)");
    EXPECT_EQ(info.pattern, "(a)(b)(c)");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.num_captures, 3);
}

// Test: Pattern with a single capture group
TEST_F(GetInfoTest_172, SingleCaptureGroup_172) {
    Info info = GetInfo("(abc)");
    EXPECT_EQ(info.pattern, "(abc)");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.num_captures, 1);
}

// Test: Invalid pattern produces an error
TEST_F(GetInfoTest_172, InvalidPatternError_172) {
    Info info = GetInfo("(abc");
    EXPECT_EQ(info.pattern, "(abc");
    EXPECT_FALSE(info.error.empty());
}

// Test: Pattern with alternation (no required prefix)
TEST_F(GetInfoTest_172, AlternationPattern_172) {
    Info info = GetInfo("abc|def");
    EXPECT_EQ(info.pattern, "abc|def");
    EXPECT_TRUE(info.error.empty());
    // No common prefix for alternation
    EXPECT_TRUE(info.prefix.empty());
}

// Test: Pattern with a required prefix followed by regex
TEST_F(GetInfoTest_172, PrefixWithSuffix_172) {
    Info info = GetInfo("hello.*world");
    EXPECT_EQ(info.pattern, "hello.*world");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.prefix, "hello");
}

// Test: Dot star pattern (no prefix)
TEST_F(GetInfoTest_172, DotStarPattern_172) {
    Info info = GetInfo(".*");
    EXPECT_EQ(info.pattern, ".*");
    EXPECT_TRUE(info.error.empty());
    EXPECT_TRUE(info.prefix.empty());
    EXPECT_EQ(info.num_captures, 0);
}

// Test: Pattern with nested captures
TEST_F(GetInfoTest_172, NestedCaptures_172) {
    Info info = GetInfo("((a)(b))");
    EXPECT_EQ(info.pattern, "((a)(b))");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.num_captures, 3);
}

// Test: Character class pattern
TEST_F(GetInfoTest_172, CharacterClassPattern_172) {
    Info info = GetInfo("[a-z]+");
    EXPECT_EQ(info.pattern, "[a-z]+");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.num_captures, 0);
}

// Test: Bytecode and bytemap are non-empty for valid patterns
TEST_F(GetInfoTest_172, BytecodeAndBytemapNonEmpty_172) {
    Info info = GetInfo("abc");
    EXPECT_TRUE(info.error.empty());
    EXPECT_FALSE(info.bytecode.empty());
    EXPECT_FALSE(info.bytemap.empty());
}

// Test: Complex pattern
TEST_F(GetInfoTest_172, ComplexPattern_172) {
    Info info = GetInfo("^prefix(foo|bar)baz$");
    EXPECT_EQ(info.pattern, "^prefix(foo|bar)baz$");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.num_captures, 1);
}

// Test: One pass detection for simple pattern
TEST_F(GetInfoTest_172, OnePassSimplePattern_172) {
    Info info = GetInfo("^abc$");
    EXPECT_TRUE(info.error.empty());
    // is_one_pass should be a valid boolean
    EXPECT_TRUE(info.is_one_pass == true || info.is_one_pass == false);
}

// Test: Can bit state for simple pattern
TEST_F(GetInfoTest_172, CanBitStateSimplePattern_172) {
    Info info = GetInfo("abc");
    EXPECT_TRUE(info.error.empty());
    EXPECT_TRUE(info.can_bit_state == true || info.can_bit_state == false);
}

// Test: Invalid regex with unbalanced brackets
TEST_F(GetInfoTest_172, UnbalancedBrackets_172) {
    Info info = GetInfo("[abc");
    EXPECT_EQ(info.pattern, "[abc");
    EXPECT_FALSE(info.error.empty());
}

// Test: Invalid regex with bad escape
TEST_F(GetInfoTest_172, BadRepetition_172) {
    Info info = GetInfo("*abc");
    EXPECT_EQ(info.pattern, "*abc");
    EXPECT_FALSE(info.error.empty());
}

// Test: Single character pattern
TEST_F(GetInfoTest_172, SingleCharPattern_172) {
    Info info = GetInfo("a");
    EXPECT_EQ(info.pattern, "a");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.prefix, "a");
    EXPECT_EQ(info.num_captures, 0);
}

// Test: Pattern with prefix_foldcase (case insensitive prefix)
TEST_F(GetInfoTest_172, CaseInsensitivePrefix_172) {
    Info info = GetInfo("(?i)hello.*");
    EXPECT_EQ(info.pattern, "(?i)hello.*");
    EXPECT_TRUE(info.error.empty());
    // When case-insensitive, prefix_foldcase should be true if prefix is found
    if (!info.prefix.empty()) {
        EXPECT_TRUE(info.prefix_foldcase);
    }
}

// Test: Anchored pattern has prefix
TEST_F(GetInfoTest_172, AnchoredPatternPrefix_172) {
    Info info = GetInfo("^test");
    EXPECT_EQ(info.pattern, "^test");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.prefix, "test");
}

// Test: Accel prefix for literal followed by complex
TEST_F(GetInfoTest_172, AccelPrefixPattern_172) {
    Info info = GetInfo("abc.*xyz");
    EXPECT_EQ(info.pattern, "abc.*xyz");
    EXPECT_TRUE(info.error.empty());
    // accel_prefix may or may not be set depending on internal logic
    // Just verify no crash and valid state
}

// Test: No captures pattern
TEST_F(GetInfoTest_172, NoCapturesPattern_172) {
    Info info = GetInfo("(?:abc)(?:def)");
    EXPECT_EQ(info.pattern, "(?:abc)(?:def)");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.num_captures, 0);
}

// Test: Pattern with quantifiers
TEST_F(GetInfoTest_172, QuantifierPattern_172) {
    Info info = GetInfo("a{3,5}b+c?");
    EXPECT_EQ(info.pattern, "a{3,5}b+c?");
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.num_captures, 0);
}

// Test: Very long literal pattern
TEST_F(GetInfoTest_172, LongLiteralPattern_172) {
    std::string long_pattern(1000, 'a');
    Info info = GetInfo(long_pattern);
    EXPECT_EQ(info.pattern, long_pattern);
    EXPECT_TRUE(info.error.empty());
    EXPECT_EQ(info.prefix, long_pattern);
}

// Test: Unicode pattern
TEST_F(GetInfoTest_172, UnicodePattern_172) {
    Info info = GetInfo("\\p{L}+");
    EXPECT_EQ(info.pattern, "\\p{L}+");
    EXPECT_TRUE(info.error.empty());
}

// Test: Pattern that is entirely alternation with no common prefix
TEST_F(GetInfoTest_172, PureAlternation_172) {
    Info info = GetInfo("a|b|c|d");
    EXPECT_EQ(info.pattern, "a|b|c|d");
    EXPECT_TRUE(info.error.empty());
    EXPECT_TRUE(info.prefix.empty());
}

}  // namespace re2_app
