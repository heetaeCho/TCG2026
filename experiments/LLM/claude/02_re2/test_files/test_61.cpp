#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <re2/re2.h>
#include <re2/set.h>
#include <vector>
#include <string>

// Since the actual class uses pybind11 (py::buffer), and we cannot easily
// instantiate py::buffer objects without a Python interpreter, we test the
// underlying RE2::Set directly, which is what the wrapper delegates to.
// This tests the observable behavior of the Set class through its public interface.

class RE2SetTest_61 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that adding a valid pattern returns a non-negative index
TEST_F(RE2SetTest_61, AddValidPatternReturnsNonNegativeIndex_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int index = set.Add("hello", &error);
    EXPECT_GE(index, 0);
}

// Test that adding multiple valid patterns returns sequential indices
TEST_F(RE2SetTest_61, AddMultiplePatternsReturnsSequentialIndices_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int index0 = set.Add("hello", &error);
    int index1 = set.Add("world", &error);
    int index2 = set.Add("foo", &error);
    EXPECT_EQ(index0, 0);
    EXPECT_EQ(index1, 1);
    EXPECT_EQ(index2, 2);
}

// Test that adding an invalid pattern returns -1
TEST_F(RE2SetTest_61, AddInvalidPatternReturnsNegativeOne_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int index = set.Add("[invalid", &error);
    EXPECT_EQ(index, -1);
}

// Test that Compile succeeds after adding valid patterns
TEST_F(RE2SetTest_61, CompileSucceedsWithValidPatterns_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    set.Add("world", &error);
    bool compiled = set.Compile();
    EXPECT_TRUE(compiled);
}

// Test that Compile succeeds with no patterns
TEST_F(RE2SetTest_61, CompileSucceedsWithNoPatterns_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    bool compiled = set.Compile();
    EXPECT_TRUE(compiled);
}

// Test matching with UNANCHORED set
TEST_F(RE2SetTest_61, MatchFindsCorrectPatterns_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    set.Add("world", &error);
    set.Add("foobar", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("hello world", &matches);
    EXPECT_TRUE(matched);
    EXPECT_THAT(matches, ::testing::UnorderedElementsAre(0, 1));
}

// Test matching returns no matches for non-matching text
TEST_F(RE2SetTest_61, MatchReturnsNoMatchesForNonMatchingText_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    set.Add("world", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("xyz", &matches);
    EXPECT_FALSE(matched);
    EXPECT_TRUE(matches.empty());
}

// Test matching with ANCHOR_BOTH
TEST_F(RE2SetTest_61, MatchWithAnchorBoth_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::ANCHOR_BOTH);
    std::string error;
    set.Add("hello", &error);
    set.Add("world", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("hello", &matches);
    EXPECT_TRUE(matched);
    EXPECT_THAT(matches, ::testing::UnorderedElementsAre(0));

    matches.clear();
    matched = set.Match("hello world", &matches);
    EXPECT_FALSE(matched);
    EXPECT_TRUE(matches.empty());
}

// Test matching with empty string
TEST_F(RE2SetTest_61, MatchWithEmptyString_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add(".*", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("", &matches);
    EXPECT_TRUE(matched);
    EXPECT_THAT(matches, ::testing::UnorderedElementsAre(0));
}

// Test matching with empty pattern set after compile
TEST_F(RE2SetTest_61, MatchWithEmptyPatternSet_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("anything", &matches);
    EXPECT_FALSE(matched);
    EXPECT_TRUE(matches.empty());
}

// Test adding pattern with special regex characters
TEST_F(RE2SetTest_61, AddPatternWithSpecialCharacters_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int index = set.Add("a+b*c?d", &error);
    EXPECT_GE(index, 0);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("aad", &matches);
    EXPECT_TRUE(matched);
}

// Test adding duplicate patterns
TEST_F(RE2SetTest_61, AddDuplicatePatternsReturnsDifferentIndices_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    int index0 = set.Add("hello", &error);
    int index1 = set.Add("hello", &error);
    EXPECT_EQ(index0, 0);
    EXPECT_EQ(index1, 1);
}

// Test that both duplicates match
TEST_F(RE2SetTest_61, DuplicatePatternsAllMatch_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("hello", &matches);
    EXPECT_TRUE(matched);
    EXPECT_THAT(matches, ::testing::UnorderedElementsAre(0, 1));
}

// Test case-insensitive matching via options
TEST_F(RE2SetTest_61, CaseInsensitiveMatch_61) {
    RE2::Options options;
    options.set_case_sensitive(false);
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("HELLO", &matches);
    EXPECT_TRUE(matched);
    EXPECT_THAT(matches, ::testing::UnorderedElementsAre(0));
}

// Test adding a pattern with NULL error pointer (mimics the wrapper behavior)
TEST_F(RE2SetTest_61, AddWithNullErrorPointer_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    int index = set.Add("valid_pattern", nullptr);
    EXPECT_GE(index, 0);
}

// Test adding an invalid pattern with NULL error pointer returns -1
TEST_F(RE2SetTest_61, AddInvalidPatternWithNullErrorPointer_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    int index = set.Add("[invalid", nullptr);
    EXPECT_EQ(index, -1);
}

// Test with ANCHOR_START
TEST_F(RE2SetTest_61, MatchWithAnchorStart_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::ANCHOR_START);
    std::string error;
    set.Add("hello", &error);
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("hello world", &matches);
    EXPECT_TRUE(matched);

    matches.clear();
    matched = set.Match("say hello", &matches);
    EXPECT_FALSE(matched);
}

// Test a large number of patterns
TEST_F(RE2SetTest_61, AddManyPatterns_61) {
    RE2::Options options;
    RE2::Set set(options, RE2::UNANCHORED);
    std::string error;
    const int count = 100;
    for (int i = 0; i < count; i++) {
        std::string pattern = "pattern" + std::to_string(i);
        int index = set.Add(pattern, &error);
        EXPECT_EQ(index, i);
    }
    ASSERT_TRUE(set.Compile());

    std::vector<int> matches;
    bool matched = set.Match("pattern42", &matches);
    EXPECT_TRUE(matched);
    EXPECT_THAT(matches, ::testing::Contains(42));
}
