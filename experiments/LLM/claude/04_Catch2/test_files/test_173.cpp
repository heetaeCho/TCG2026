#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include Catch2 matcher headers
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// A concrete matcher deriving from MatcherBase<int>
struct IntEqualsMatcher : Catch::Matchers::MatcherBase<int> {
    int expected;
    explicit IntEqualsMatcher(int val) : expected(val) {}
    bool match(int const& actual) const override {
        return actual == expected;
    }
    std::string describe() const override {
        return "equals " + std::to_string(expected);
    }
};

// A concrete matcher deriving from MatcherBase<std::string>
struct StringContainsMatcher : Catch::Matchers::MatcherBase<std::string> {
    std::string substring;
    explicit StringContainsMatcher(std::string s) : substring(std::move(s)) {}
    bool match(std::string const& actual) const override {
        return actual.find(substring) != std::string::npos;
    }
    std::string describe() const override {
        return "contains \"" + substring + "\"";
    }
};

// A generic matcher (satisfies is_generic_matcher_v) for int-compatible types
struct GenericPositiveMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& val) const {
        return val > 0;
    }
    std::string describe() const override {
        return "is positive";
    }
};

// Another generic matcher
struct GenericNonEmptyMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& val) const {
        return !val.empty();
    }
    std::string describe() const override {
        return "is non-empty";
    }
};

// A generic matcher that always matches
struct GenericAlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const {
        return true;
    }
    std::string describe() const override {
        return "always true";
    }
};

// A generic matcher that never matches
struct GenericAlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const {
        return false;
    }
    std::string describe() const override {
        return "always false";
    }
};

class MatcherOperatorAndTest_173 : public ::testing::Test {
protected:
};

// Test that operator&& between MatcherBase<int> and a generic matcher produces correct type
TEST_F(MatcherOperatorAndTest_173, ResultTypeIsMatchAllOfGeneric_173) {
    IntEqualsMatcher lhs(42);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    // Verify the result is a MatchAllOfGeneric type (it should compile and be usable)
    using ResultType = decltype(combined);
    bool is_correct_type = std::is_same<ResultType,
        Catch::Matchers::Detail::MatchAllOfGeneric<
            Catch::Matchers::MatcherBase<int>,
            GenericPositiveMatcher>>::value;
    EXPECT_TRUE(is_correct_type);
}

// Test that combined matcher matches when both matchers match
TEST_F(MatcherOperatorAndTest_173, BothMatchersMatch_ReturnsTrue_173) {
    IntEqualsMatcher lhs(42);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_TRUE(combined.match(42));
}

// Test that combined matcher fails when LHS doesn't match
TEST_F(MatcherOperatorAndTest_173, LhsDoesNotMatch_ReturnsFalse_173) {
    IntEqualsMatcher lhs(42);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(10)); // 10 != 42, so LHS fails
}

// Test that combined matcher fails when RHS doesn't match
TEST_F(MatcherOperatorAndTest_173, RhsDoesNotMatch_ReturnsFalse_173) {
    IntEqualsMatcher lhs(-5);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    // -5 == -5 (LHS matches), but -5 is not positive (RHS fails)
    EXPECT_FALSE(combined.match(-5));
}

// Test that combined matcher fails when neither matcher matches
TEST_F(MatcherOperatorAndTest_173, NeitherMatches_ReturnsFalse_173) {
    IntEqualsMatcher lhs(42);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(-10)); // -10 != 42 and -10 is not positive
}

// Test with string matchers
TEST_F(MatcherOperatorAndTest_173, StringMatcherWithGenericMatcher_BothMatch_173) {
    StringContainsMatcher lhs("hello");
    GenericNonEmptyMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_TRUE(combined.match(std::string("say hello world")));
}

// Test with string matchers where LHS fails
TEST_F(MatcherOperatorAndTest_173, StringMatcherWithGenericMatcher_LhsFails_173) {
    StringContainsMatcher lhs("goodbye");
    GenericNonEmptyMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(std::string("hello world")));
}

// Test with AlwaysTrue generic matcher - result depends only on LHS
TEST_F(MatcherOperatorAndTest_173, AlwaysTrueGenericMatcher_LhsMatches_173) {
    IntEqualsMatcher lhs(100);
    GenericAlwaysTrueMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_TRUE(combined.match(100));
}

TEST_F(MatcherOperatorAndTest_173, AlwaysTrueGenericMatcher_LhsFails_173) {
    IntEqualsMatcher lhs(100);
    GenericAlwaysTrueMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(99));
}

// Test with AlwaysFalse generic matcher - result is always false
TEST_F(MatcherOperatorAndTest_173, AlwaysFalseGenericMatcher_AlwaysFalse_173) {
    IntEqualsMatcher lhs(42);
    GenericAlwaysFalseMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(42)); // LHS matches but RHS always false
}

// Test that describe produces a non-empty description
TEST_F(MatcherOperatorAndTest_173, DescribeProducesNonEmptyString_173) {
    IntEqualsMatcher lhs(42);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    std::string description = combined.describe();
    EXPECT_FALSE(description.empty());
}

// Test that description contains info from both matchers
TEST_F(MatcherOperatorAndTest_173, DescribeContainsBothDescriptions_173) {
    IntEqualsMatcher lhs(42);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    std::string description = combined.describe();
    // The combined description should mention both sub-matchers
    EXPECT_NE(description.find("equals 42"), std::string::npos);
    EXPECT_NE(description.find("is positive"), std::string::npos);
}

// Boundary: test with zero value
TEST_F(MatcherOperatorAndTest_173, BoundaryZeroValue_173) {
    IntEqualsMatcher lhs(0);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    // 0 == 0 (LHS matches) but 0 > 0 is false (RHS fails)
    EXPECT_FALSE(combined.match(0));
}

// Boundary: test with negative value matching LHS
TEST_F(MatcherOperatorAndTest_173, BoundaryNegativeValue_173) {
    IntEqualsMatcher lhs(-1);
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(-1));
}

// Test with INT_MAX
TEST_F(MatcherOperatorAndTest_173, BoundaryIntMax_173) {
    IntEqualsMatcher lhs(std::numeric_limits<int>::max());
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_TRUE(combined.match(std::numeric_limits<int>::max()));
}

// Test with INT_MIN
TEST_F(MatcherOperatorAndTest_173, BoundaryIntMin_173) {
    IntEqualsMatcher lhs(std::numeric_limits<int>::min());
    GenericPositiveMatcher rhs;
    auto combined = lhs && rhs;
    EXPECT_FALSE(combined.match(std::numeric_limits<int>::min()));
}

// Test empty string with string matchers
TEST_F(MatcherOperatorAndTest_173, EmptyStringBoundary_173) {
    StringContainsMatcher lhs("");
    GenericNonEmptyMatcher rhs;
    auto combined = lhs && rhs;
    // "" is found in any string, but empty string is empty
    EXPECT_FALSE(combined.match(std::string("")));
}
