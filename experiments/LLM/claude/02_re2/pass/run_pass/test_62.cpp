#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "re2/set.h"
#include "re2/re2.h"

class RE2SetTest_62 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a newly created Set can compile without any patterns
TEST_F(RE2SetTest_62, CompileWithNoPatterns_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    EXPECT_TRUE(set.Compile());
}

// Test adding a valid pattern returns a non-negative index
TEST_F(RE2SetTest_62, AddValidPattern_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int index = set.Add("hello", &error);
    EXPECT_GE(index, 0);
}

// Test adding an invalid pattern returns -1
TEST_F(RE2SetTest_62, AddInvalidPattern_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int index = set.Add("[invalid", &error);
    EXPECT_EQ(index, -1);
    EXPECT_FALSE(error.empty());
}

// Test adding multiple patterns returns consecutive indices
TEST_F(RE2SetTest_62, AddMultiplePatterns_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int idx0 = set.Add("foo", &error);
    int idx1 = set.Add("bar", &error);
    int idx2 = set.Add("baz", &error);
    EXPECT_EQ(idx0, 0);
    EXPECT_EQ(idx1, 1);
    EXPECT_EQ(idx2, 2);
}

// Test that Compile succeeds with valid patterns
TEST_F(RE2SetTest_62, CompileWithValidPatterns_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    set.Add("world", &error);
    EXPECT_TRUE(set.Compile());
}

// Test matching returns correct pattern indices for a single match
TEST_F(RE2SetTest_62, MatchSinglePattern_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    set.Add("world", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_TRUE(set.Match("hello", &matches));
    ASSERT_EQ(matches.size(), 1);
    EXPECT_EQ(matches[0], 0);
}

// Test matching returns correct pattern indices for multiple matches
TEST_F(RE2SetTest_62, MatchMultiplePatterns_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    set.Add("world", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_TRUE(set.Match("hello world", &matches));
    ASSERT_EQ(matches.size(), 2);
    // Both patterns should match
    std::sort(matches.begin(), matches.end());
    EXPECT_EQ(matches[0], 0);
    EXPECT_EQ(matches[1], 1);
}

// Test matching with no matches returns empty
TEST_F(RE2SetTest_62, MatchNoPatterns_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    set.Add("world", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_FALSE(set.Match("foobar", &matches));
    EXPECT_TRUE(matches.empty());
}

// Test matching with empty text
TEST_F(RE2SetTest_62, MatchEmptyText_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_FALSE(set.Match("", &matches));
    EXPECT_TRUE(matches.empty());
}

// Test matching with empty pattern matches everything
TEST_F(RE2SetTest_62, MatchEmptyPattern_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int idx = set.Add("", &error);
    EXPECT_GE(idx, 0);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_TRUE(set.Match("anything", &matches));
    EXPECT_FALSE(matches.empty());
}

// Test ANCHOR_BOTH mode
TEST_F(RE2SetTest_62, MatchAnchorBoth_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::ANCHOR_BOTH);
    std::string error;
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    // Exact match should work
    EXPECT_TRUE(set.Match("hello", &matches));
    EXPECT_EQ(matches.size(), 1);

    matches.clear();
    // Partial match should not work with ANCHOR_BOTH
    EXPECT_FALSE(set.Match("hello world", &matches));
    EXPECT_TRUE(matches.empty());
}

// Test ANCHOR_START mode
TEST_F(RE2SetTest_62, MatchAnchorStart_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::ANCHOR_START);
    std::string error;
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_TRUE(set.Match("hello world", &matches));
    EXPECT_EQ(matches.size(), 1);

    matches.clear();
    EXPECT_FALSE(set.Match("say hello", &matches));
    EXPECT_TRUE(matches.empty());
}

// Test with regex patterns (not just literals)
TEST_F(RE2SetTest_62, MatchRegexPatterns_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("h[ae]llo", &error);
    set.Add("\\d+", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_TRUE(set.Match("hallo 123", &matches));
    std::sort(matches.begin(), matches.end());
    ASSERT_EQ(matches.size(), 2);
    EXPECT_EQ(matches[0], 0);
    EXPECT_EQ(matches[1], 1);
}

// Test case-insensitive matching via options
TEST_F(RE2SetTest_62, CaseInsensitiveMatch_62) {
    RE2::Options options;
    options.set_case_sensitive(false);
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_TRUE(set.Match("HELLO", &matches));
    EXPECT_EQ(matches.size(), 1);
}

// Test case-sensitive matching (default)
TEST_F(RE2SetTest_62, CaseSensitiveMatchDefault_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_FALSE(set.Match("HELLO", &matches));
    EXPECT_TRUE(matches.empty());
}

// Test with many patterns
TEST_F(RE2SetTest_62, MatchManyPatterns_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    for (int i = 0; i < 100; ++i) {
        std::string pattern = "pattern" + std::to_string(i);
        int idx = set.Add(pattern, &error);
        EXPECT_EQ(idx, i);
    }
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_TRUE(set.Match("pattern42", &matches));
    ASSERT_EQ(matches.size(), 1);
    EXPECT_EQ(matches[0], 42);
}

// Test that Match clears the output vector
TEST_F(RE2SetTest_62, MatchClearsOutputVector_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    matches.push_back(99);  // Pre-populate
    set.Match("hello", &matches);
    // Should not contain the pre-populated value
    for (int m : matches) {
        EXPECT_NE(m, 99);
    }
}

// Test compiled set with no patterns still works on match
TEST_F(RE2SetTest_62, MatchCompiledEmptySet_62) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    EXPECT_FALSE(set.Match("hello", &matches));
    EXPECT_TRUE(matches.empty());
}
