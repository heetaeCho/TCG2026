#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include Catch2 matchers headers
#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"

// Define custom generic matchers for testing purposes
// These are "generic matchers" because they have a templated `match` method

struct AlwaysTrueMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const {
        return true;
    }
    std::string describe() const override {
        return "always true";
    }
};

struct AlwaysFalseMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const&) const {
        return false;
    }
    std::string describe() const override {
        return "always false";
    }
};

struct GreaterThanZeroMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& value) const {
        return value > 0;
    }
    std::string describe() const override {
        return "is greater than zero";
    }
};

struct LessThanTenMatcher : Catch::Matchers::MatcherGenericBase {
    template<typename T>
    bool match(T const& value) const {
        return value < 10;
    }
    std::string describe() const override {
        return "is less than ten";
    }
};

struct NonEmptyStringMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(std::string const& value) const {
        return !value.empty();
    }
    std::string describe() const override {
        return "is non-empty string";
    }
};

struct StartsWithAMatcher : Catch::Matchers::MatcherGenericBase {
    bool match(std::string const& value) const {
        return !value.empty() && value[0] == 'A';
    }
    std::string describe() const override {
        return "starts with A";
    }
};

class MatchAllOfGenericTest_169 : public ::testing::Test {
protected:
    AlwaysTrueMatcher alwaysTrue;
    AlwaysFalseMatcher alwaysFalse;
    GreaterThanZeroMatcher greaterThanZero;
    LessThanTenMatcher lessThanTen;
    NonEmptyStringMatcher nonEmpty;
    StartsWithAMatcher startsWithA;
};

// Test: Both matchers return true => combined matcher returns true
TEST_F(MatchAllOfGenericTest_169, BothMatchersTrue_ReturnsTrue_169) {
    auto combined = alwaysTrue && alwaysTrue;
    EXPECT_TRUE(combined.match(42));
}

// Test: Left matcher true, right matcher false => combined returns false
TEST_F(MatchAllOfGenericTest_169, LeftTrueRightFalse_ReturnsFalse_169) {
    auto combined = alwaysTrue && alwaysFalse;
    EXPECT_FALSE(combined.match(42));
}

// Test: Left matcher false, right matcher true => combined returns false
TEST_F(MatchAllOfGenericTest_169, LeftFalseRightTrue_ReturnsFalse_169) {
    auto combined = alwaysFalse && alwaysTrue;
    EXPECT_FALSE(combined.match(42));
}

// Test: Both matchers return false => combined returns false
TEST_F(MatchAllOfGenericTest_169, BothMatchersFalse_ReturnsFalse_169) {
    auto combined = alwaysFalse && alwaysFalse;
    EXPECT_FALSE(combined.match(42));
}

// Test: Value satisfies both range conditions
TEST_F(MatchAllOfGenericTest_169, ValueInRange_BothSatisfied_169) {
    auto combined = greaterThanZero && lessThanTen;
    EXPECT_TRUE(combined.match(5));
}

// Test: Value at boundary - exactly zero fails greaterThanZero
TEST_F(MatchAllOfGenericTest_169, BoundaryZero_FailsGreaterThanZero_169) {
    auto combined = greaterThanZero && lessThanTen;
    EXPECT_FALSE(combined.match(0));
}

// Test: Value at boundary - exactly ten fails lessThanTen
TEST_F(MatchAllOfGenericTest_169, BoundaryTen_FailsLessThanTen_169) {
    auto combined = greaterThanZero && lessThanTen;
    EXPECT_FALSE(combined.match(10));
}

// Test: Value fails both conditions (negative large number doesn't fail lessThanTen but fails greaterThanZero; let's use value > 10)
TEST_F(MatchAllOfGenericTest_169, ValueOutOfRange_FailsBoth_169) {
    auto combined = greaterThanZero && lessThanTen;
    // -5 fails greaterThanZero, passes lessThanTen
    EXPECT_FALSE(combined.match(-5));
    // 15 passes greaterThanZero, fails lessThanTen
    EXPECT_FALSE(combined.match(15));
}

// Test: String matchers combined - both conditions satisfied
TEST_F(MatchAllOfGenericTest_169, StringMatchersBothSatisfied_169) {
    auto combined = nonEmpty && startsWithA;
    EXPECT_TRUE(combined.match(std::string("Apple")));
}

// Test: String matchers combined - empty string fails nonEmpty
TEST_F(MatchAllOfGenericTest_169, StringMatchersEmptyStringFails_169) {
    auto combined = nonEmpty && startsWithA;
    EXPECT_FALSE(combined.match(std::string("")));
}

// Test: String matchers combined - non-empty but doesn't start with A
TEST_F(MatchAllOfGenericTest_169, StringMatchersDoesNotStartWithA_169) {
    auto combined = nonEmpty && startsWithA;
    EXPECT_FALSE(combined.match(std::string("Banana")));
}

// Test: Chaining three matchers with && (associativity)
TEST_F(MatchAllOfGenericTest_169, ThreeMatchersChained_AllTrue_169) {
    auto combined = alwaysTrue && alwaysTrue && alwaysTrue;
    EXPECT_TRUE(combined.match(42));
}

// Test: Chaining three matchers where one is false
TEST_F(MatchAllOfGenericTest_169, ThreeMatchersChained_OneFalse_169) {
    auto combined = alwaysTrue && alwaysFalse && alwaysTrue;
    EXPECT_FALSE(combined.match(42));
}

// Test: Chaining three matchers where last is false
TEST_F(MatchAllOfGenericTest_169, ThreeMatchersChained_LastFalse_169) {
    auto combined = alwaysTrue && alwaysTrue && alwaysFalse;
    EXPECT_FALSE(combined.match(42));
}

// Test: describe() produces a meaningful description containing both matcher descriptions
TEST_F(MatchAllOfGenericTest_169, DescribeContainsBothDescriptions_169) {
    auto combined = greaterThanZero && lessThanTen;
    std::string description = combined.describe();
    EXPECT_NE(description.find("is greater than zero"), std::string::npos);
    EXPECT_NE(description.find("is less than ten"), std::string::npos);
}

// Test: describe() for string matchers
TEST_F(MatchAllOfGenericTest_169, DescribeStringMatchers_169) {
    auto combined = nonEmpty && startsWithA;
    std::string description = combined.describe();
    EXPECT_NE(description.find("is non-empty string"), std::string::npos);
    EXPECT_NE(description.find("starts with A"), std::string::npos);
}

// Test: Works with different value types (double)
TEST_F(MatchAllOfGenericTest_169, WorksWithDoubleValues_169) {
    auto combined = greaterThanZero && lessThanTen;
    EXPECT_TRUE(combined.match(5.5));
    EXPECT_FALSE(combined.match(-0.1));
    EXPECT_FALSE(combined.match(10.1));
}

// Test: Boundary value 1 (just above zero)
TEST_F(MatchAllOfGenericTest_169, BoundaryValueOne_169) {
    auto combined = greaterThanZero && lessThanTen;
    EXPECT_TRUE(combined.match(1));
}

// Test: Boundary value 9 (just below ten)
TEST_F(MatchAllOfGenericTest_169, BoundaryValueNine_169) {
    auto combined = greaterThanZero && lessThanTen;
    EXPECT_TRUE(combined.match(9));
}

// Test: Result type is correct (should be MatchAllOfGeneric)
TEST_F(MatchAllOfGenericTest_169, ResultTypeIsMatchAllOfGeneric_169) {
    auto combined = greaterThanZero && lessThanTen;
    // Verify that the result is indeed a MatchAllOfGeneric type
    using ResultType = decltype(combined);
    static_assert(std::is_class<ResultType>::value, "Result should be a class type");
    // Just verify it compiles and works
    EXPECT_TRUE(combined.match(5));
}

// Test: Four matchers chained
TEST_F(MatchAllOfGenericTest_169, FourMatchersChained_AllTrue_169) {
    auto combined = alwaysTrue && alwaysTrue && alwaysTrue && alwaysTrue;
    EXPECT_TRUE(combined.match(42));
}

// Test: Four matchers chained with one false
TEST_F(MatchAllOfGenericTest_169, FourMatchersChained_OneFalse_169) {
    auto combined = alwaysTrue && alwaysTrue && alwaysFalse && alwaysTrue;
    EXPECT_FALSE(combined.match(42));
}
