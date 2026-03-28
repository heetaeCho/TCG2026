#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <list>
#include <array>

// Include the Catch2 amalgamated header for the matchers
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Matchers;

// Helper to check if a matcher matches a given value
template <typename Matcher, typename T>
bool doesMatch(const Matcher& matcher, const T& value) {
    return matcher.match(value);
}

// ============================================================
// Tests for Contains matcher with basic element matchers
// ============================================================

class ContainsMatcherTest_954 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that Contains with an equality matcher finds matching element in vector
TEST_F(ContainsMatcherTest_954, ContainsFindsMatchingElementInVector_954) {
    auto matcher = Contains(Catch::Matchers::Equals("hello"));
    std::vector<std::string> vec = {"world", "hello", "foo"};
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test that Contains returns false when no element matches
TEST_F(ContainsMatcherTest_954, ContainsReturnsFalseWhenNoMatch_954) {
    auto matcher = Contains(Catch::Matchers::Equals("bar"));
    std::vector<std::string> vec = {"world", "hello", "foo"};
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test Contains with an empty container returns false
TEST_F(ContainsMatcherTest_954, ContainsReturnsFalseForEmptyContainer_954) {
    auto matcher = Contains(Catch::Matchers::Equals("hello"));
    std::vector<std::string> vec = {};
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test Contains with a single element container that matches
TEST_F(ContainsMatcherTest_954, ContainsSingleElementMatch_954) {
    auto matcher = Contains(Catch::Matchers::Equals("only"));
    std::vector<std::string> vec = {"only"};
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test Contains with a single element container that doesn't match
TEST_F(ContainsMatcherTest_954, ContainsSingleElementNoMatch_954) {
    auto matcher = Contains(Catch::Matchers::Equals("other"));
    std::vector<std::string> vec = {"only"};
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test Contains with predicate-based matcher (e.g., StartsWith)
TEST_F(ContainsMatcherTest_954, ContainsWithStartsWithMatcher_954) {
    auto matcher = Contains(Catch::Matchers::StartsWith("hel"));
    std::vector<std::string> vec = {"world", "hello", "foo"};
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test Contains with predicate-based matcher that doesn't match
TEST_F(ContainsMatcherTest_954, ContainsWithStartsWithMatcherNoMatch_954) {
    auto matcher = Contains(Catch::Matchers::StartsWith("xyz"));
    std::vector<std::string> vec = {"world", "hello", "foo"};
    EXPECT_FALSE(doesMatch(matcher, vec));
}

// Test Contains with EndsWith matcher
TEST_F(ContainsMatcherTest_954, ContainsWithEndsWithMatcher_954) {
    auto matcher = Contains(Catch::Matchers::EndsWith("llo"));
    std::vector<std::string> vec = {"world", "hello", "foo"};
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test Contains matcher has a meaningful describe method
TEST_F(ContainsMatcherTest_954, ContainsMatcherHasDescription_954) {
    auto matcher = Contains(Catch::Matchers::Equals("hello"));
    std::string description = matcher.describe();
    EXPECT_FALSE(description.empty());
}

// Test Contains with a list container
TEST_F(ContainsMatcherTest_954, ContainsWorksWithList_954) {
    auto matcher = Contains(Catch::Matchers::Equals("hello"));
    std::list<std::string> lst = {"world", "hello", "foo"};
    EXPECT_TRUE(doesMatch(matcher, lst));
}

// Test Contains with multiple matching elements still returns true
TEST_F(ContainsMatcherTest_954, ContainsWithMultipleMatches_954) {
    auto matcher = Contains(Catch::Matchers::Equals("hello"));
    std::vector<std::string> vec = {"hello", "hello", "hello"};
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test Contains match is found at the last position
TEST_F(ContainsMatcherTest_954, ContainsMatchAtLastPosition_954) {
    auto matcher = Contains(Catch::Matchers::Equals("last"));
    std::vector<std::string> vec = {"first", "middle", "last"};
    EXPECT_TRUE(doesMatch(matcher, vec));
}

// Test Contains match is found at the first position
TEST_F(ContainsMatcherTest_954, ContainsMatchAtFirstPosition_954) {
    auto matcher = Contains(Catch::Matchers::Equals("first"));
    std::vector<std::string> vec = {"first", "middle", "last"};
    EXPECT_TRUE(doesMatch(matcher, vec));
}
