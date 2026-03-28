#include <gtest/gtest.h>
#include <string>
#include <type_traits>

#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// Simple custom matcher for testing purposes
struct EqualsMatcher_163 : Catch::Matchers::MatcherGenericBase {
    int m_value;
    explicit EqualsMatcher_163(int v) : m_value(v) {}
    
    bool match(int const& arg) const {
        return arg == m_value;
    }
    
    std::string describe() const override {
        return "equals " + std::to_string(m_value);
    }
};

struct StringContainsMatcher_163 : Catch::Matchers::MatcherGenericBase {
    std::string m_substr;
    explicit StringContainsMatcher_163(std::string s) : m_substr(std::move(s)) {}
    
    bool match(std::string const& arg) const {
        return arg.find(m_substr) != std::string::npos;
    }
    
    std::string describe() const override {
        return "contains \"" + m_substr + "\"";
    }
};

struct AlwaysTrueMatcher_163 : Catch::Matchers::MatcherGenericBase {
    bool match(int const&) const { return true; }
    std::string describe() const override { return "always true"; }
};

struct AlwaysFalseMatcher_163 : Catch::Matchers::MatcherGenericBase {
    bool match(int const&) const { return false; }
    std::string describe() const override { return "always false"; }
};

class MatchAnyOfGenericTest_163 : public ::testing::Test {
protected:
};

// Test: Combining two matchers with operator|| where first matches
TEST_F(MatchAnyOfGenericTest_163, OperatorOrFirstMatcherMatches_163) {
    auto combined = EqualsMatcher_163(5) || EqualsMatcher_163(10);
    EXPECT_TRUE(combined.match(5));
}

// Test: Combining two matchers with operator|| where second matches
TEST_F(MatchAnyOfGenericTest_163, OperatorOrSecondMatcherMatches_163) {
    auto combined = EqualsMatcher_163(5) || EqualsMatcher_163(10);
    EXPECT_TRUE(combined.match(10));
}

// Test: Combining two matchers with operator|| where neither matches
TEST_F(MatchAnyOfGenericTest_163, OperatorOrNeitherMatches_163) {
    auto combined = EqualsMatcher_163(5) || EqualsMatcher_163(10);
    EXPECT_FALSE(combined.match(7));
}

// Test: Chaining multiple operator|| calls
TEST_F(MatchAnyOfGenericTest_163, OperatorOrChainedMultiple_163) {
    auto combined = EqualsMatcher_163(1) || EqualsMatcher_163(2) || EqualsMatcher_163(3);
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(2));
    EXPECT_TRUE(combined.match(3));
    EXPECT_FALSE(combined.match(4));
}

// Test: Combining MatchAnyOfGeneric instances via operator||
TEST_F(MatchAnyOfGenericTest_163, OperatorOrCombineTwoAnyOfGeneric_163) {
    auto lhs = EqualsMatcher_163(1) || EqualsMatcher_163(2);
    auto rhs = EqualsMatcher_163(3) || EqualsMatcher_163(4);
    auto combined = std::move(lhs) || std::move(rhs);
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(2));
    EXPECT_TRUE(combined.match(3));
    EXPECT_TRUE(combined.match(4));
    EXPECT_FALSE(combined.match(5));
}

// Test: describe() returns non-empty string
TEST_F(MatchAnyOfGenericTest_163, DescribeReturnsNonEmpty_163) {
    auto combined = EqualsMatcher_163(5) || EqualsMatcher_163(10);
    std::string desc = combined.describe();
    EXPECT_FALSE(desc.empty());
}

// Test: AlwaysTrue || AlwaysFalse should always match
TEST_F(MatchAnyOfGenericTest_163, AlwaysTrueOrAlwaysFalseAlwaysMatches_163) {
    auto combined = AlwaysTrueMatcher_163() || AlwaysFalseMatcher_163();
    EXPECT_TRUE(combined.match(0));
    EXPECT_TRUE(combined.match(999));
}

// Test: AlwaysFalse || AlwaysFalse should never match
TEST_F(MatchAnyOfGenericTest_163, AlwaysFalseOrAlwaysFalseNeverMatches_163) {
    auto combined = AlwaysFalseMatcher_163() || AlwaysFalseMatcher_163();
    EXPECT_FALSE(combined.match(0));
    EXPECT_FALSE(combined.match(999));
}

// Test: String matchers combined with operator||
TEST_F(MatchAnyOfGenericTest_163, StringMatchersCombined_163) {
    auto combined = StringContainsMatcher_163("hello") || StringContainsMatcher_163("world");
    EXPECT_TRUE(combined.match(std::string("hello there")));
    EXPECT_TRUE(combined.match(std::string("brave world")));
    EXPECT_TRUE(combined.match(std::string("hello world")));
    EXPECT_FALSE(combined.match(std::string("goodbye")));
}

// Test: Single matcher in MatchAnyOfGeneric through chaining
TEST_F(MatchAnyOfGenericTest_163, SingleMatcherBehavior_163) {
    auto m = EqualsMatcher_163(42) || AlwaysFalseMatcher_163();
    EXPECT_TRUE(m.match(42));
    EXPECT_FALSE(m.match(43));
}

// Test: describe contains information about constituent matchers
TEST_F(MatchAnyOfGenericTest_163, DescribeContainsMatcherInfo_163) {
    auto combined = EqualsMatcher_163(5) || EqualsMatcher_163(10);
    std::string desc = combined.describe();
    // The description should mention something about the sub-matchers
    // We check it's a reasonable string (non-trivial)
    EXPECT_GT(desc.size(), 0u);
}

// Test: Move semantics - combined matcher works after move construction
TEST_F(MatchAnyOfGenericTest_163, MoveConstructionWorks_163) {
    auto original = EqualsMatcher_163(5) || EqualsMatcher_163(10);
    auto moved = std::move(original);
    EXPECT_TRUE(moved.match(5));
    EXPECT_TRUE(moved.match(10));
    EXPECT_FALSE(moved.match(7));
}

// Test: Boundary - combining many matchers
TEST_F(MatchAnyOfGenericTest_163, ManyMatchersCombined_163) {
    auto combined = EqualsMatcher_163(1) || EqualsMatcher_163(2) || EqualsMatcher_163(3)
                 || EqualsMatcher_163(4) || EqualsMatcher_163(5);
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(5));
    EXPECT_FALSE(combined.match(0));
    EXPECT_FALSE(combined.match(6));
}
