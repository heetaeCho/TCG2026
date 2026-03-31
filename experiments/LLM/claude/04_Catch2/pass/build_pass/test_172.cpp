#include <gtest/gtest.h>
#include <string>
#include <type_traits>

#include "catch2/matchers/catch_matchers_templated.hpp"
#include "catch2/matchers/catch_matchers.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "catch2/matchers/catch_matchers_contains.hpp"
#include "catch2/matchers/catch_matchers_predicate.hpp"

// A simple generic matcher for testing purposes
struct AlwaysTrueGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template <typename T>
    bool match(T const&) const { return true; }
    std::string describe() const override { return "always true"; }
};

struct AlwaysFalseGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template <typename T>
    bool match(T const&) const { return false; }
    std::string describe() const override { return "always false"; }
};

struct IsPositiveGenericMatcher : Catch::Matchers::MatcherGenericBase {
    template <typename T>
    bool match(T const& val) const { return val > 0; }
    std::string describe() const override { return "is positive"; }
};

// A typed matcher (derives from MatcherBase<int>)
class IsEvenMatcher : public Catch::Matchers::MatcherBase<int> {
public:
    bool match(int const& val) const override { return val % 2 == 0; }
    std::string describe() const override { return "is even"; }
};

// A typed matcher for strings
class ContainsHelloMatcher : public Catch::Matchers::MatcherBase<std::string> {
public:
    bool match(std::string const& val) const override {
        return val.find("hello") != std::string::npos;
    }
    std::string describe() const override { return "contains 'hello'"; }
};

class LengthGreaterThanMatcher : public Catch::Matchers::MatcherBase<std::string> {
public:
    explicit LengthGreaterThanMatcher(size_t len) : m_len(len) {}
    bool match(std::string const& val) const override { return val.size() > m_len; }
    std::string describe() const override { return "length > " + std::to_string(m_len); }
private:
    size_t m_len;
};

class MatchAllOfGenericOperatorTest_172 : public ::testing::Test {
protected:
    AlwaysTrueGenericMatcher alwaysTrue;
    AlwaysFalseGenericMatcher alwaysFalse;
    IsPositiveGenericMatcher isPositive;
    IsEvenMatcher isEven;
};

// Test that combining a generic true matcher with a typed true matcher matches
TEST_F(MatchAllOfGenericOperatorTest_172, BothMatchersMatch_ReturnsTrue_172) {
    auto combined = alwaysTrue && isEven;
    EXPECT_TRUE(combined.match(4)); // 4 is even, and alwaysTrue matches everything
}

// Test that when the generic matcher (LHS) would match but typed (RHS) doesn't, result is false
TEST_F(MatchAllOfGenericOperatorTest_172, GenericMatchesButTypedDoesNot_ReturnsFalse_172) {
    auto combined = alwaysTrue && isEven;
    EXPECT_FALSE(combined.match(3)); // 3 is not even
}

// Test that when the generic matcher (LHS) doesn't match but typed (RHS) does, result is false
TEST_F(MatchAllOfGenericOperatorTest_172, GenericDoesNotMatchButTypedDoes_ReturnsFalse_172) {
    auto combined = alwaysFalse && isEven;
    EXPECT_FALSE(combined.match(4)); // alwaysFalse never matches
}

// Test that when neither matches, result is false
TEST_F(MatchAllOfGenericOperatorTest_172, NeitherMatches_ReturnsFalse_172) {
    auto combined = alwaysFalse && isEven;
    EXPECT_FALSE(combined.match(3)); // neither matches
}

// Test with a more meaningful generic matcher and typed matcher
TEST_F(MatchAllOfGenericOperatorTest_172, IsPositiveAndIsEven_BothSatisfied_172) {
    auto combined = isPositive && isEven;
    EXPECT_TRUE(combined.match(6));  // positive and even
}

TEST_F(MatchAllOfGenericOperatorTest_172, IsPositiveAndIsEven_OnlyPositive_172) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(5)); // positive but not even
}

TEST_F(MatchAllOfGenericOperatorTest_172, IsPositiveAndIsEven_OnlyEven_172) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(-2)); // even but not positive
}

TEST_F(MatchAllOfGenericOperatorTest_172, IsPositiveAndIsEven_NeitherSatisfied_172) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(-3)); // neither positive nor even
}

// Test with string matchers
TEST_F(MatchAllOfGenericOperatorTest_172, StringGenericAndTypedMatcher_BothMatch_172) {
    ContainsHelloMatcher containsHello;
    auto combined = alwaysTrue && containsHello;
    EXPECT_TRUE(combined.match(std::string("hello world")));
}

TEST_F(MatchAllOfGenericOperatorTest_172, StringGenericAndTypedMatcher_TypedFails_172) {
    ContainsHelloMatcher containsHello;
    auto combined = alwaysTrue && containsHello;
    EXPECT_FALSE(combined.match(std::string("goodbye world")));
}

// Test that the describe method produces a non-empty description
TEST_F(MatchAllOfGenericOperatorTest_172, DescribeIsNonEmpty_172) {
    auto combined = alwaysTrue && isEven;
    std::string desc = combined.describe();
    EXPECT_FALSE(desc.empty());
}

// Test that the description contains info from both matchers
TEST_F(MatchAllOfGenericOperatorTest_172, DescribeContainsBothDescriptions_172) {
    auto combined = isPositive && isEven;
    std::string desc = combined.describe();
    EXPECT_NE(desc.find("is positive"), std::string::npos);
    EXPECT_NE(desc.find("is even"), std::string::npos);
}

// Boundary: Test with zero
TEST_F(MatchAllOfGenericOperatorTest_172, BoundaryZero_IsPositiveAndEven_172) {
    auto combined = isPositive && isEven;
    EXPECT_FALSE(combined.match(0)); // 0 is even but not positive (0 > 0 is false)
}

// Boundary: Test with INT_MAX
TEST_F(MatchAllOfGenericOperatorTest_172, BoundaryIntMax_172) {
    auto combined = isPositive && isEven;
    // INT_MAX is positive but odd (2^31 - 1)
    EXPECT_FALSE(combined.match(std::numeric_limits<int>::max()));
}

// Boundary: Test with INT_MIN
TEST_F(MatchAllOfGenericOperatorTest_172, BoundaryIntMin_172) {
    auto combined = isPositive && isEven;
    // INT_MIN is negative and even
    EXPECT_FALSE(combined.match(std::numeric_limits<int>::min()));
}

// Test with large even positive
TEST_F(MatchAllOfGenericOperatorTest_172, LargeEvenPositive_172) {
    auto combined = isPositive && isEven;
    EXPECT_TRUE(combined.match(1000000));
}

// Test return type is MatchAllOfGeneric
TEST_F(MatchAllOfGenericOperatorTest_172, ReturnTypeIsMatchAllOfGeneric_172) {
    auto combined = alwaysTrue && isEven;
    using ResultType = decltype(combined);
    bool isCorrectType = std::is_same<
        ResultType,
        Catch::Matchers::Detail::MatchAllOfGeneric<AlwaysTrueGenericMatcher, Catch::Matchers::MatcherBase<int>>
    >::value;
    EXPECT_TRUE(isCorrectType);
}

// Test SFINAE: verify that the operator is only enabled for generic matchers on LHS
// This is a compile-time check - we verify the trait itself
TEST_F(MatchAllOfGenericOperatorTest_172, GenericMatcherTraitIsTrue_172) {
    EXPECT_TRUE(Catch::Matchers::Detail::is_generic_matcher_v<AlwaysTrueGenericMatcher>);
    EXPECT_TRUE(Catch::Matchers::Detail::is_generic_matcher_v<AlwaysFalseGenericMatcher>);
    EXPECT_TRUE(Catch::Matchers::Detail::is_generic_matcher_v<IsPositiveGenericMatcher>);
}

// Verify that the typed matcher is NOT considered a generic matcher
TEST_F(MatchAllOfGenericOperatorTest_172, TypedMatcherTraitIsFalse_172) {
    EXPECT_FALSE(Catch::Matchers::Detail::is_generic_matcher_v<IsEvenMatcher>);
}

// Test combining with a different string typed matcher
TEST_F(MatchAllOfGenericOperatorTest_172, GenericAndLengthMatcher_BothSatisfied_172) {
    LengthGreaterThanMatcher lengthGt3(3);
    auto combined = alwaysTrue && lengthGt3;
    EXPECT_TRUE(combined.match(std::string("abcde")));
}

TEST_F(MatchAllOfGenericOperatorTest_172, GenericAndLengthMatcher_LengthNotSatisfied_172) {
    LengthGreaterThanMatcher lengthGt3(3);
    auto combined = alwaysTrue && lengthGt3;
    EXPECT_FALSE(combined.match(std::string("ab")));
}

// Edge case: empty string
TEST_F(MatchAllOfGenericOperatorTest_172, EmptyString_GenericAndLength_172) {
    LengthGreaterThanMatcher lengthGt0(0);
    auto combined = alwaysTrue && lengthGt0;
    EXPECT_FALSE(combined.match(std::string(""))); // length 0 is not > 0
}

TEST_F(MatchAllOfGenericOperatorTest_172, SingleCharString_GenericAndLength_172) {
    LengthGreaterThanMatcher lengthGt0(0);
    auto combined = alwaysTrue && lengthGt0;
    EXPECT_TRUE(combined.match(std::string("a"))); // length 1 > 0
}
