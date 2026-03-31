#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/stringpiece.h"

// Tests for one-pass DFA functionality in RE2, exercised through the public interface.
// One-pass regexps are a subset of regexps where the match can be determined in a single
// pass through the input.

class OnePassTest_566 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test simple one-pass pattern matching
TEST_F(OnePassTest_566, SimpleMatch_566) {
    RE2 re("hello");
    ASSERT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("hello", re));
    EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test one-pass pattern with capturing groups
TEST_F(OnePassTest_566, CapturingGroups_566) {
    RE2 re("(\\w+)@(\\w+)");
    ASSERT_TRUE(re.ok());
    std::string user, domain;
    EXPECT_TRUE(RE2::FullMatch("user@host", re, &user, &domain));
    EXPECT_EQ("user", user);
    EXPECT_EQ("host", domain);
}

// Test one-pass with alternation (simple alternation can be one-pass)
TEST_F(OnePassTest_566, SimpleAlternation_566) {
    RE2 re("(a|b)c");
    ASSERT_TRUE(re.ok());
    std::string cap;
    EXPECT_TRUE(RE2::FullMatch("ac", re, &cap));
    EXPECT_EQ("a", cap);
    EXPECT_TRUE(RE2::FullMatch("bc", re, &cap));
    EXPECT_EQ("b", cap);
    EXPECT_FALSE(RE2::FullMatch("cc", re));
}

// Test empty string matching
TEST_F(OnePassTest_566, EmptyStringMatch_566) {
    RE2 re("");
    ASSERT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("", re));
}

// Test one-pass with character classes
TEST_F(OnePassTest_566, CharacterClasses_566) {
    RE2 re("[a-z]+");
    ASSERT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("abcdef", re));
    EXPECT_FALSE(RE2::FullMatch("ABC", re));
    EXPECT_FALSE(RE2::FullMatch("123", re));
}

// Test one-pass with anchored patterns
TEST_F(OnePassTest_566, AnchoredPattern_566) {
    RE2 re("^abc$");
    ASSERT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("abc", re));
    EXPECT_FALSE(RE2::FullMatch("xabc", re));
    EXPECT_FALSE(RE2::FullMatch("abcx", re));
}

// Test one-pass with quantifiers
TEST_F(OnePassTest_566, Quantifiers_566) {
    RE2 re("a{3}b{2}");
    ASSERT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("aaabb", re));
    EXPECT_FALSE(RE2::FullMatch("aabb", re));
    EXPECT_FALSE(RE2::FullMatch("aaab", re));
}

// Test one-pass with optional groups
TEST_F(OnePassTest_566, OptionalGroup_566) {
    RE2 re("(foo)?(bar)");
    ASSERT_TRUE(re.ok());
    std::string s1, s2;
    EXPECT_TRUE(RE2::FullMatch("foobar", re, &s1, &s2));
    EXPECT_EQ("foo", s1);
    EXPECT_EQ("bar", s2);
    EXPECT_TRUE(RE2::FullMatch("bar", re, &s1, &s2));
    EXPECT_EQ("bar", s2);
}

// Test partial match with one-pass eligible pattern
TEST_F(OnePassTest_566, PartialMatch_566) {
    RE2 re("(\\d+)");
    ASSERT_TRUE(re.ok());
    std::string num;
    EXPECT_TRUE(RE2::PartialMatch("abc123def", re, &num));
    EXPECT_EQ("123", num);
}

// Test no match scenario
TEST_F(OnePassTest_566, NoMatch_566) {
    RE2 re("xyz");
    ASSERT_TRUE(re.ok());
    EXPECT_FALSE(RE2::FullMatch("abc", re));
    EXPECT_FALSE(RE2::PartialMatch("abc", re));
}

// Test with longer patterns that exercise state indexing
TEST_F(OnePassTest_566, LongerPattern_566) {
    RE2 re("([a-z]+):([0-9]+):([a-z]+)");
    ASSERT_TRUE(re.ok());
    std::string a, b, c;
    EXPECT_TRUE(RE2::FullMatch("hello:123:world", re, &a, &b, &c));
    EXPECT_EQ("hello", a);
    EXPECT_EQ("123", b);
    EXPECT_EQ("world", c);
}

// Test boundary: single character
TEST_F(OnePassTest_566, SingleCharMatch_566) {
    RE2 re("a");
    ASSERT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("a", re));
    EXPECT_FALSE(RE2::FullMatch("b", re));
    EXPECT_FALSE(RE2::FullMatch("aa", re));
}

// Test with dot (any character)
TEST_F(OnePassTest_566, DotMatch_566) {
    RE2 re(".+");
    ASSERT_TRUE(re.ok());
    EXPECT_TRUE(RE2::FullMatch("anything", re));
    EXPECT_FALSE(RE2::FullMatch("", re));
}

// Test with nested groups
TEST_F(OnePassTest_566, NestedGroups_566) {
    RE2 re("((a)(b))");
    ASSERT_TRUE(re.ok());
    std::string s1, s2, s3;
    EXPECT_TRUE(RE2::FullMatch("ab", re, &s1, &s2, &s3));
    EXPECT_EQ("ab", s1);
    EXPECT_EQ("a", s2);
    EXPECT_EQ("b", s3);
}

// Test with non-capturing groups
TEST_F(OnePassTest_566, NonCapturingGroup_566) {
    RE2 re("(?:foo)(bar)");
    ASSERT_TRUE(re.ok());
    std::string cap;
    EXPECT_TRUE(RE2::FullMatch("foobar", re, &cap));
    EXPECT_EQ("bar", cap);
}
