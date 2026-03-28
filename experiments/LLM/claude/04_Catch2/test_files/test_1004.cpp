#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// Include necessary Catch2 headers
#include "catch2/catch_test_spec.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_tag_alias_autoregistrar.hpp"

// We need to include the amalgamated or relevant headers
// Adjust includes based on actual project structure
#include "catch2/internal/catch_source_line_info.hpp"

using namespace Catch;

// Helper to create a TestCaseInfo with specific tags
// We use NameAndTags to construct TestCaseInfo which parses tags
namespace {

// Helper function to create a TestCaseInfo with given tags
std::unique_ptr<TestCaseInfo> makeTestCaseInfo(const std::string& name, const std::string& tags) {
    NameAndTags nameAndTags(name, tags);
    SourceLineInfo lineInfo("test_file.cpp", 1);
    return std::make_unique<TestCaseInfo>(StringRef("TestClass"), nameAndTags, lineInfo);
}

} // anonymous namespace

class TagPatternMatchesTest_1004 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that TagPattern matches a TestCaseInfo that has the specified tag
TEST_F(TagPatternMatchesTest_1004, MatchesWhenTagIsPresent_1004) {
    auto testCase = makeTestCaseInfo("test1", "[fast]");
    
    TestSpec::TagPattern pattern("fast", "[fast]");
    
    EXPECT_TRUE(pattern.matches(*testCase));
}

// Test that TagPattern does not match a TestCaseInfo that lacks the specified tag
TEST_F(TagPatternMatchesTest_1004, DoesNotMatchWhenTagIsAbsent_1004) {
    auto testCase = makeTestCaseInfo("test1", "[slow]");
    
    TestSpec::TagPattern pattern("fast", "[fast]");
    
    EXPECT_FALSE(pattern.matches(*testCase));
}

// Test that TagPattern matches when multiple tags are present and one matches
TEST_F(TagPatternMatchesTest_1004, MatchesWhenOneOfMultipleTagsMatches_1004) {
    auto testCase = makeTestCaseInfo("test1", "[fast][unit][critical]");
    
    TestSpec::TagPattern pattern("unit", "[unit]");
    
    EXPECT_TRUE(pattern.matches(*testCase));
}

// Test that TagPattern does not match when none of multiple tags match
TEST_F(TagPatternMatchesTest_1004, DoesNotMatchWhenNoneOfMultipleTagsMatch_1004) {
    auto testCase = makeTestCaseInfo("test1", "[fast][unit][critical]");
    
    TestSpec::TagPattern pattern("slow", "[slow]");
    
    EXPECT_FALSE(pattern.matches(*testCase));
}

// Test that TagPattern does not match when TestCaseInfo has no tags
TEST_F(TagPatternMatchesTest_1004, DoesNotMatchWhenNoTags_1004) {
    auto testCase = makeTestCaseInfo("test1", "");
    
    TestSpec::TagPattern pattern("fast", "[fast]");
    
    EXPECT_FALSE(pattern.matches(*testCase));
}

// Test that TagPattern matching is case-insensitive (Catch2 tags are typically lowercased)
TEST_F(TagPatternMatchesTest_1004, MatchesTagCaseInsensitive_1004) {
    // Catch2 lowercases tags internally, so [Fast] should become [fast]
    auto testCase = makeTestCaseInfo("test1", "[Fast]");
    
    TestSpec::TagPattern pattern("fast", "[fast]");
    
    EXPECT_TRUE(pattern.matches(*testCase));
}

// Test matching with a tag that has special meaning like hidden tag
TEST_F(TagPatternMatchesTest_1004, MatchesHiddenTag_1004) {
    auto testCase = makeTestCaseInfo("test1", "[.][hidden]");
    
    TestSpec::TagPattern pattern(".", "[.]");
    
    EXPECT_TRUE(pattern.matches(*testCase));
}

// Test that TagPattern correctly distinguishes between similar but different tags
TEST_F(TagPatternMatchesTest_1004, DoesNotMatchSimilarButDifferentTag_1004) {
    auto testCase = makeTestCaseInfo("test1", "[fast]");
    
    TestSpec::TagPattern pattern("faster", "[faster]");
    
    EXPECT_FALSE(pattern.matches(*testCase));
}

// Test matching the first tag among multiple
TEST_F(TagPatternMatchesTest_1004, MatchesFirstTag_1004) {
    auto testCase = makeTestCaseInfo("test1", "[alpha][beta][gamma]");
    
    TestSpec::TagPattern pattern("alpha", "[alpha]");
    
    EXPECT_TRUE(pattern.matches(*testCase));
}

// Test matching the last tag among multiple
TEST_F(TagPatternMatchesTest_1004, MatchesLastTag_1004) {
    auto testCase = makeTestCaseInfo("test1", "[alpha][beta][gamma]");
    
    TestSpec::TagPattern pattern("gamma", "[gamma]");
    
    EXPECT_TRUE(pattern.matches(*testCase));
}

// Test matching a single character tag
TEST_F(TagPatternMatchesTest_1004, MatchesSingleCharTag_1004) {
    auto testCase = makeTestCaseInfo("test1", "[a]");
    
    TestSpec::TagPattern pattern("a", "[a]");
    
    EXPECT_TRUE(pattern.matches(*testCase));
}

// Test that empty pattern tag does not match a test with tags
TEST_F(TagPatternMatchesTest_1004, EmptyTagPatternBehavior_1004) {
    auto testCase = makeTestCaseInfo("test1", "[fast]");
    
    TestSpec::TagPattern pattern("", "[]");
    
    EXPECT_FALSE(pattern.matches(*testCase));
}
