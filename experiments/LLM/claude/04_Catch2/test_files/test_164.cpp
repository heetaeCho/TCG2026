#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the header under test
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// We need to create some concrete matchers to test the operator|| functionality
// These are simple matchers that conform to the Catch2 matcher interface

namespace {

// A simple matcher that checks if an int equals a given value
struct EqualsMatcher : Catch::Matchers::MatcherGenericBase {
    int m_value;
    explicit EqualsMatcher(int v) : m_value(v) {}

    bool match(int const& arg) const {
        return arg == m_value;
    }

    std::string describe() const override {
        return "equals " + std::to_string(m_value);
    }
};

// A simple matcher that checks if an int is greater than a given value
struct GreaterThanMatcher : Catch::Matchers::MatcherGenericBase {
    int m_value;
    explicit GreaterThanMatcher(int v) : m_value(v) {}

    bool match(int const& arg) const {
        return arg > m_value;
    }

    std::string describe() const override {
        return "is greater than " + std::to_string(m_value);
    }
};

// A simple matcher that checks if an int is less than a given value
struct LessThanMatcher : Catch::Matchers::MatcherGenericBase {
    int m_value;
    explicit LessThanMatcher(int v) : m_value(v) {}

    bool match(int const& arg) const {
        return arg < m_value;
    }

    std::string describe() const override {
        return "is less than " + std::to_string(m_value);
    }
};

// A matcher that always returns true
struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int const&) const {
        return true;
    }

    std::string describe() const override {
        return "always true";
    }
};

// A matcher that always returns false
struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(int const&) const {
        return false;
    }

    std::string describe() const override {
        return "always false";
    }
};

// String matcher for testing with different types
struct StringContainsMatcher : Catch::Matchers::MatcherGenericBase {
    std::string m_substring;
    explicit StringContainsMatcher(std::string sub) : m_substring(std::move(sub)) {}

    bool match(std::string const& arg) const {
        return arg.find(m_substring) != std::string::npos;
    }

    std::string describe() const override {
        return "contains \"" + m_substring + "\"";
    }
};

} // anonymous namespace

class MatchAnyOfGenericTest_164 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Combining two matchers with || where first matcher matches
TEST_F(MatchAnyOfGenericTest_164, OperatorOrFirstMatcherMatches_164) {
    EqualsMatcher eq5(5);
    EqualsMatcher eq10(10);

    auto combined = eq5 || eq10;
    EXPECT_TRUE(combined.match(5));
}

// Test: Combining two matchers with || where second matcher matches
TEST_F(MatchAnyOfGenericTest_164, OperatorOrSecondMatcherMatches_164) {
    EqualsMatcher eq5(5);
    EqualsMatcher eq10(10);

    auto combined = eq5 || eq10;
    EXPECT_TRUE(combined.match(10));
}

// Test: Combining two matchers with || where neither matches
TEST_F(MatchAnyOfGenericTest_164, OperatorOrNeitherMatches_164) {
    EqualsMatcher eq5(5);
    EqualsMatcher eq10(10);

    auto combined = eq5 || eq10;
    EXPECT_FALSE(combined.match(7));
}

// Test: Combining two matchers with || where both match
TEST_F(MatchAnyOfGenericTest_164, OperatorOrBothMatch_164) {
    GreaterThanMatcher gt3(3);
    LessThanMatcher lt10(10);

    auto combined = gt3 || lt10;
    EXPECT_TRUE(combined.match(5)); // both match
}

// Test: Chaining three matchers with ||
TEST_F(MatchAnyOfGenericTest_164, ChainingThreeMatchers_164) {
    EqualsMatcher eq1(1);
    EqualsMatcher eq2(2);
    EqualsMatcher eq3(3);

    auto combined = eq1 || eq2 || eq3;
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(2));
    EXPECT_TRUE(combined.match(3));
    EXPECT_FALSE(combined.match(4));
}

// Test: Chaining four matchers with ||
TEST_F(MatchAnyOfGenericTest_164, ChainingFourMatchers_164) {
    EqualsMatcher eq1(1);
    EqualsMatcher eq2(2);
    EqualsMatcher eq3(3);
    EqualsMatcher eq4(4);

    auto combined = eq1 || eq2 || eq3 || eq4;
    EXPECT_TRUE(combined.match(1));
    EXPECT_TRUE(combined.match(2));
    EXPECT_TRUE(combined.match(3));
    EXPECT_TRUE(combined.match(4));
    EXPECT_FALSE(combined.match(5));
}

// Test: Combining AlwaysTrue with AlwaysFalse
TEST_F(MatchAnyOfGenericTest_164, AlwaysTrueOrAlwaysFalse_164) {
    AlwaysTrueMatcher alwaysTrue;
    AlwaysFalseMatcher alwaysFalse;

    auto combined = alwaysTrue || alwaysFalse;
    EXPECT_TRUE(combined.match(42));
}

// Test: Combining AlwaysFalse with AlwaysTrue
TEST_F(MatchAnyOfGenericTest_164, AlwaysFalseOrAlwaysTrue_164) {
    AlwaysFalseMatcher alwaysFalse;
    AlwaysTrueMatcher alwaysTrue;

    auto combined = alwaysFalse || alwaysTrue;
    EXPECT_TRUE(combined.match(42));
}

// Test: Combining two AlwaysFalse matchers
TEST_F(MatchAnyOfGenericTest_164, TwoAlwaysFalseMatchers_164) {
    AlwaysFalseMatcher alwaysFalse1;
    AlwaysFalseMatcher alwaysFalse2;

    auto combined = alwaysFalse1 || alwaysFalse2;
    EXPECT_FALSE(combined.match(42));
}

// Test: Combining two AlwaysTrue matchers
TEST_F(MatchAnyOfGenericTest_164, TwoAlwaysTrueMatchers_164) {
    AlwaysTrueMatcher alwaysTrue1;
    AlwaysTrueMatcher alwaysTrue2;

    auto combined = alwaysTrue1 || alwaysTrue2;
    EXPECT_TRUE(combined.match(42));
}

// Test: Combining different matcher types (EqualsMatcher and GreaterThanMatcher)
TEST_F(MatchAnyOfGenericTest_164, DifferentMatcherTypes_164) {
    EqualsMatcher eq5(5);
    GreaterThanMatcher gt100(100);

    auto combined = eq5 || gt100;
    EXPECT_TRUE(combined.match(5));
    EXPECT_TRUE(combined.match(200));
    EXPECT_FALSE(combined.match(50));
}

// Test: describe() returns a meaningful description
TEST_F(MatchAnyOfGenericTest_164, DescribeReturnsNonEmpty_164) {
    EqualsMatcher eq5(5);
    EqualsMatcher eq10(10);

    auto combined = eq5 || eq10;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test: describe() for chained matchers returns a meaningful description
TEST_F(MatchAnyOfGenericTest_164, DescribeChainedReturnsNonEmpty_164) {
    EqualsMatcher eq1(1);
    EqualsMatcher eq2(2);
    EqualsMatcher eq3(3);

    auto combined = eq1 || eq2 || eq3;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test: String matchers combined with ||
TEST_F(MatchAnyOfGenericTest_164, StringMatchersCombined_164) {
    StringContainsMatcher containsHello("hello");
    StringContainsMatcher containsWorld("world");

    auto combined = containsHello || containsWorld;
    EXPECT_TRUE(combined.match(std::string("hello there")));
    EXPECT_TRUE(combined.match(std::string("the world")));
    EXPECT_TRUE(combined.match(std::string("hello world")));
    EXPECT_FALSE(combined.match(std::string("goodbye")));
}

// Test: Boundary - combining MatchAnyOfGeneric with another matcher via ||
TEST_F(MatchAnyOfGenericTest_164, MatchAnyOfCombinedWithAnotherMatcher_164) {
    EqualsMatcher eq1(1);
    EqualsMatcher eq2(2);
    EqualsMatcher eq3(3);

    // First combine two, then add a third via ||
    auto twoMatchers = eq1 || eq2;
    auto threeMatchers = std::move(twoMatchers) || eq3;

    EXPECT_TRUE(threeMatchers.match(1));
    EXPECT_TRUE(threeMatchers.match(2));
    EXPECT_TRUE(threeMatchers.match(3));
    EXPECT_FALSE(threeMatchers.match(4));
}

// Test: Boundary values for int matchers
TEST_F(MatchAnyOfGenericTest_164, BoundaryIntValues_164) {
    EqualsMatcher eqMin(std::numeric_limits<int>::min());
    EqualsMatcher eqMax(std::numeric_limits<int>::max());

    auto combined = eqMin || eqMax;
    EXPECT_TRUE(combined.match(std::numeric_limits<int>::min()));
    EXPECT_TRUE(combined.match(std::numeric_limits<int>::max()));
    EXPECT_FALSE(combined.match(0));
}

// Test: Single element boundary - two matchers with same value
TEST_F(MatchAnyOfGenericTest_164, SameValueMatchers_164) {
    EqualsMatcher eq5a(5);
    EqualsMatcher eq5b(5);

    auto combined = eq5a || eq5b;
    EXPECT_TRUE(combined.match(5));
    EXPECT_FALSE(combined.match(6));
}

// Test: Mixing different types of matchers (equals, greater than, less than)
TEST_F(MatchAnyOfGenericTest_164, MixedMatcherTypes_164) {
    EqualsMatcher eq0(0);
    GreaterThanMatcher gt100(100);
    LessThanMatcher ltNeg100(-100);

    auto combined = eq0 || gt100 || ltNeg100;
    EXPECT_TRUE(combined.match(0));
    EXPECT_TRUE(combined.match(200));
    EXPECT_TRUE(combined.match(-200));
    EXPECT_FALSE(combined.match(50));
    EXPECT_FALSE(combined.match(-50));
}
