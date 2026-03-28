#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_predicate.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_templated.hpp>

#include <gtest/gtest.h>
#include <string>

using namespace Catch::Matchers;

class MatchAnyOfTest_140 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test describe with two string matchers combined via ||
TEST_F(MatchAnyOfTest_140, DescribeWithTwoMatchers_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") || Catch::Matchers::ContainsSubstring("world");
    std::string desc = combined.describe();
    // Should contain "or" between the two matcher descriptions
    EXPECT_NE(desc.find(" or "), std::string::npos);
    // Should start with "( " and end with " )"
    EXPECT_EQ(desc.front(), '(');
    EXPECT_EQ(desc.back(), ')');
    // Should contain descriptions of both matchers
    EXPECT_NE(desc.find("hello"), std::string::npos);
    EXPECT_NE(desc.find("world"), std::string::npos);
}

// Test match returns true when first matcher matches
TEST_F(MatchAnyOfTest_140, MatchReturnsTrueWhenFirstMatches_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") || Catch::Matchers::ContainsSubstring("world");
    EXPECT_TRUE(combined.match("hello there"));
}

// Test match returns true when second matcher matches
TEST_F(MatchAnyOfTest_140, MatchReturnsTrueWhenSecondMatches_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") || Catch::Matchers::ContainsSubstring("world");
    EXPECT_TRUE(combined.match("the world"));
}

// Test match returns true when both matchers match
TEST_F(MatchAnyOfTest_140, MatchReturnsTrueWhenBothMatch_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") || Catch::Matchers::ContainsSubstring("world");
    EXPECT_TRUE(combined.match("hello world"));
}

// Test match returns false when no matcher matches
TEST_F(MatchAnyOfTest_140, MatchReturnsFalseWhenNoneMatch_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") || Catch::Matchers::ContainsSubstring("world");
    EXPECT_FALSE(combined.match("foo bar"));
}

// Test chaining three matchers with ||
TEST_F(MatchAnyOfTest_140, DescribeWithThreeMatchers_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") 
                 || Catch::Matchers::ContainsSubstring("world")
                 || Catch::Matchers::ContainsSubstring("test");
    std::string desc = combined.describe();
    // Should contain two "or" separators
    size_t firstOr = desc.find(" or ");
    EXPECT_NE(firstOr, std::string::npos);
    size_t secondOr = desc.find(" or ", firstOr + 4);
    EXPECT_NE(secondOr, std::string::npos);
    EXPECT_NE(desc.find("hello"), std::string::npos);
    EXPECT_NE(desc.find("world"), std::string::npos);
    EXPECT_NE(desc.find("test"), std::string::npos);
}

// Test three matchers: match on third
TEST_F(MatchAnyOfTest_140, ThreeMatchersMatchOnThird_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") 
                 || Catch::Matchers::ContainsSubstring("world")
                 || Catch::Matchers::ContainsSubstring("test");
    EXPECT_TRUE(combined.match("this is a test"));
}

// Test three matchers: no match
TEST_F(MatchAnyOfTest_140, ThreeMatchersNoMatch_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") 
                 || Catch::Matchers::ContainsSubstring("world")
                 || Catch::Matchers::ContainsSubstring("test");
    EXPECT_FALSE(combined.match("nothing here"));
}

// Test describe format starts with "( " and ends with " )"
TEST_F(MatchAnyOfTest_140, DescribeFormatBraces_140) {
    auto combined = Catch::Matchers::ContainsSubstring("a") || Catch::Matchers::ContainsSubstring("b");
    std::string desc = combined.describe();
    EXPECT_GE(desc.size(), 4u);
    EXPECT_EQ(desc.substr(0, 2), "( ");
    EXPECT_EQ(desc.substr(desc.size() - 2), " )");
}

// Test with empty string matching
TEST_F(MatchAnyOfTest_140, MatchWithEmptyString_140) {
    auto combined = Catch::Matchers::ContainsSubstring("") || Catch::Matchers::ContainsSubstring("hello");
    // Empty substring is contained in any string
    EXPECT_TRUE(combined.match("anything"));
}

// Test move construction compiles and works
TEST_F(MatchAnyOfTest_140, MoveConstruction_140) {
    auto combined = Catch::Matchers::ContainsSubstring("hello") || Catch::Matchers::ContainsSubstring("world");
    auto moved = std::move(combined);
    EXPECT_TRUE(moved.match("hello"));
    EXPECT_FALSE(moved.match("foo"));
    std::string desc = moved.describe();
    EXPECT_NE(desc.find("hello"), std::string::npos);
}
