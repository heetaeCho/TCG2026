#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include <string>
#include <vector>

namespace re2 {

// Test ID: 564

// Tests for OnePass functionality through the public RE2 interface.
// Since onepass.cc is an internal implementation detail, we test its behavior
// through RE2's public matching interface, which uses the one-pass NFA
// when applicable.

class OnePassTest_564 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the EmptyOp flags and kEmptyShift are consistent
// (1 << kEmptyShift) - 1 == kEmptyAllFlags
TEST_F(OnePassTest_564, EmptyShiftConsistentWithFlags_564) {
    // kEmptyShift is 6, so (1<<6)-1 = 63 = kEmptyAllFlags
    EXPECT_EQ((1 << 6) - 1, kEmptyAllFlags);
    EXPECT_EQ(kEmptyAllFlags, 63);
}

// Test that kEmptyAllFlags covers all individual empty flags
TEST_F(OnePassTest_564, EmptyAllFlagsCoversAllFlags_564) {
    int allFlags = kEmptyBeginLine | kEmptyEndLine | kEmptyBeginText |
                   kEmptyEndText | kEmptyWordBoundary | kEmptyNonWordBoundary;
    EXPECT_EQ(allFlags, kEmptyAllFlags);
}

// Test simple one-pass regex matching (full match)
TEST_F(OnePassTest_564, SimpleFullMatch_564) {
    EXPECT_TRUE(RE2::FullMatch("hello", "hello"));
}

// Test simple one-pass regex that doesn't match
TEST_F(OnePassTest_564, SimpleFullMatchFails_564) {
    EXPECT_FALSE(RE2::FullMatch("hello", "world"));
}

// Test one-pass regex with capturing groups
TEST_F(OnePassTest_564, CapturingGroups_564) {
    std::string s1, s2;
    EXPECT_TRUE(RE2::FullMatch("hello world", "(\\w+) (\\w+)", &s1, &s2));
    EXPECT_EQ(s1, "hello");
    EXPECT_EQ(s2, "world");
}

// Test one-pass matching with anchored patterns (begin/end of line)
TEST_F(OnePassTest_564, AnchoredBeginEnd_564) {
    EXPECT_TRUE(RE2::FullMatch("abc", "^abc$"));
    EXPECT_FALSE(RE2::FullMatch("xabc", "^abc$"));
}

// Test one-pass matching with word boundary
TEST_F(OnePassTest_564, WordBoundary_564) {
    EXPECT_TRUE(RE2::PartialMatch("hello world", "\\bhello\\b"));
    EXPECT_FALSE(RE2::PartialMatch("helloworld", "\\bhello\\b\\s"));
}

// Test one-pass matching with empty string
TEST_F(OnePassTest_564, EmptyString_564) {
    EXPECT_TRUE(RE2::FullMatch("", ""));
    EXPECT_TRUE(RE2::FullMatch("", ".*"));
    EXPECT_FALSE(RE2::FullMatch("", ".+"));
}

// Test one-pass matching with alternation
TEST_F(OnePassTest_564, Alternation_564) {
    EXPECT_TRUE(RE2::FullMatch("cat", "cat|dog"));
    EXPECT_TRUE(RE2::FullMatch("dog", "cat|dog"));
    EXPECT_FALSE(RE2::FullMatch("bird", "cat|dog"));
}

// Test one-pass matching with repetition
TEST_F(OnePassTest_564, Repetition_564) {
    EXPECT_TRUE(RE2::FullMatch("aaa", "a{3}"));
    EXPECT_FALSE(RE2::FullMatch("aa", "a{3}"));
    EXPECT_TRUE(RE2::FullMatch("aaaa", "a{2,5}"));
}

// Test one-pass matching with character classes
TEST_F(OnePassTest_564, CharacterClasses_564) {
    EXPECT_TRUE(RE2::FullMatch("a", "[a-z]"));
    EXPECT_TRUE(RE2::FullMatch("5", "[0-9]"));
    EXPECT_FALSE(RE2::FullMatch("A", "[a-z]"));
}

// Test partial match with one-pass
TEST_F(OnePassTest_564, PartialMatch_564) {
    EXPECT_TRUE(RE2::PartialMatch("hello world", "world"));
    EXPECT_FALSE(RE2::PartialMatch("hello world", "xyz"));
}

// Test one-pass with multiple capture groups
TEST_F(OnePassTest_564, MultipleCaptureGroups_564) {
    std::string a, b, c;
    EXPECT_TRUE(RE2::FullMatch("1-2-3", "(\\d+)-(\\d+)-(\\d+)", &a, &b, &c));
    EXPECT_EQ(a, "1");
    EXPECT_EQ(b, "2");
    EXPECT_EQ(c, "3");
}

// Test one-pass with non-capturing groups
TEST_F(OnePassTest_564, NonCapturingGroup_564) {
    EXPECT_TRUE(RE2::FullMatch("abc", "(?:abc)"));
}

// Test that the one-pass engine handles begin/end text anchors correctly
TEST_F(OnePassTest_564, BeginEndTextAnchors_564) {
    EXPECT_TRUE(RE2::FullMatch("hello", "\\Ahello\\z"));
}

// Test one-pass with optional groups
TEST_F(OnePassTest_564, OptionalGroup_564) {
    std::string cap;
    EXPECT_TRUE(RE2::FullMatch("ac", "a(b)?c", &cap));
    EXPECT_EQ(cap, "");
    
    EXPECT_TRUE(RE2::FullMatch("abc", "a(b)?c", &cap));
    EXPECT_EQ(cap, "b");
}

// Test boundary: kMaxOnePassCapture limit
// Prog::kMaxOnePassCapture defines the maximum number of capture groups
// for one-pass. We test with patterns near that boundary.
TEST_F(OnePassTest_564, ManyCaptures_564) {
    // Test with a few captures - should work fine
    std::string s1, s2, s3, s4;
    EXPECT_TRUE(RE2::FullMatch("abcd", "(a)(b)(c)(d)", &s1, &s2, &s3, &s4));
    EXPECT_EQ(s1, "a");
    EXPECT_EQ(s2, "b");
    EXPECT_EQ(s3, "c");
    EXPECT_EQ(s4, "d");
}

// Test one-pass with dot matching
TEST_F(OnePassTest_564, DotMatching_564) {
    EXPECT_TRUE(RE2::FullMatch("a", "."));
    EXPECT_TRUE(RE2::FullMatch("abc", "..."));
    EXPECT_FALSE(RE2::FullMatch("ab", "..."));
}

// Test one-pass with newline in pattern
TEST_F(OnePassTest_564, NewlineHandling_564) {
    EXPECT_TRUE(RE2::FullMatch("a\nb", "a\nb"));
    // dot doesn't match newline by default
    EXPECT_FALSE(RE2::FullMatch("a\nb", "a.b"));
}

// Test one-pass with dot matching newline (s flag)
TEST_F(OnePassTest_564, DotMatchesNewline_564) {
    RE2::Options opts;
    opts.set_dot_nl(true);
    RE2 re("a.b", opts);
    EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

// Test individual EmptyOp flag values
TEST_F(OnePassTest_564, EmptyOpValues_564) {
    EXPECT_EQ(kEmptyBeginLine, 1);
    EXPECT_EQ(kEmptyEndLine, 2);
    EXPECT_EQ(kEmptyBeginText, 4);
    EXPECT_EQ(kEmptyEndText, 8);
    EXPECT_EQ(kEmptyWordBoundary, 16);
    EXPECT_EQ(kEmptyNonWordBoundary, 32);
}

// Test that each EmptyOp flag is a power of 2 (single bit)
TEST_F(OnePassTest_564, EmptyOpFlagsSingleBit_564) {
    EXPECT_EQ(kEmptyBeginLine & (kEmptyBeginLine - 1), 0);
    EXPECT_EQ(kEmptyEndLine & (kEmptyEndLine - 1), 0);
    EXPECT_EQ(kEmptyBeginText & (kEmptyBeginText - 1), 0);
    EXPECT_EQ(kEmptyEndText & (kEmptyEndText - 1), 0);
    EXPECT_EQ(kEmptyWordBoundary & (kEmptyWordBoundary - 1), 0);
    EXPECT_EQ(kEmptyNonWordBoundary & (kEmptyNonWordBoundary - 1), 0);
}

// Test one-pass with case-insensitive matching
TEST_F(OnePassTest_564, CaseInsensitive_564) {
    RE2::Options opts;
    opts.set_case_sensitive(false);
    RE2 re("hello", opts);
    EXPECT_TRUE(RE2::FullMatch("HELLO", re));
    EXPECT_TRUE(RE2::FullMatch("Hello", re));
    EXPECT_TRUE(RE2::FullMatch("hello", re));
}

// Test one-pass with longest match semantics
TEST_F(OnePassTest_564, LongestMatch_564) {
    RE2::Options opts;
    opts.set_longest_match(true);
    RE2 re("a(b+)", opts);
    std::string cap;
    EXPECT_TRUE(RE2::PartialMatch("abbb", re, &cap));
    EXPECT_EQ(cap, "bbb");
}

}  // namespace re2
