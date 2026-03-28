// File: match_not_operator_tests_147.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <type_traits>
#include <string>

// Include the code under test
#include "Catch2/src/catch2/matchers/catch_matchers.hpp"

using ::testing::Return;

namespace {

using Catch::Matchers::MatcherBase;

// Simple concrete matchers for observable behavior checks
struct AlwaysTrueIntMatcher : MatcherBase<int> {
    bool match(int const&) const override { return true; }
    std::string describe() const override { return "always true"; }
};

struct AlwaysFalseIntMatcher : MatcherBase<int> {
    bool match(int const&) const override { return false; }
    std::string describe() const override { return "always false"; }
};

// Google Mock-based matcher to verify external interactions
struct MockIntMatcher : MatcherBase<int> {
    MOCK_METHOD(bool, match, (int const&), (const, override));
    MOCK_METHOD(std::string, describe, (), (const, override));
};

} // namespace

// --- Tests ---

TEST(MatchNotOperatorTest_147, NotOfTrueMatcherReturnsFalse_147) {
    AlwaysTrueIntMatcher base;
    auto neg = !base;

    EXPECT_FALSE(neg.match(123)); // observable behavior: negation should not match here
}

TEST(MatchNotOperatorTest_147, NotOfFalseMatcherReturnsTrue_147) {
    AlwaysFalseIntMatcher base;
    auto neg = !base;

    EXPECT_TRUE(neg.match(-42)); // observable behavior: negation should match here
}

TEST(MatchNotOperatorTest_147, DelegatesToUnderlyingMatcher_OnceWithSameValue_147) {
    MockIntMatcher mock;

    // Underlying matcher will return true; negated result should be false.
    EXPECT_CALL(mock, match(42)).Times(1).WillOnce(Return(true));
    ON_CALL(mock, describe()).WillByDefault(Return("mock-matcher"));

    auto neg = !mock;
    EXPECT_FALSE(neg.match(42)); // verifies both delegation and negation as observed behavior
}

TEST(MatchNotOperatorTest_147, WorksWithTemporaryMatcher_147) {
    // Using a temporary is an observable usage pattern.
    // The lifetime of the temporary extends through the full expression below.
    EXPECT_FALSE((!AlwaysTrueIntMatcher{}).match(7));
    EXPECT_TRUE((!AlwaysFalseIntMatcher{}).match(7));
}

TEST(MatchNotOperatorTest_147, ReturnsMatchNotOfTypeForSameT_147) {
    AlwaysTrueIntMatcher base;
    auto expr = !base;

    // Compile-time observable: resulting type is the documented return type for T=int
    using Expected = Catch::Matchers::Detail::MatchNotOf<int>;
    static_assert(std::is_same<decltype(expr), Expected>::value, "operator! should return MatchNotOf<int>");
    SUCCEED(); // keep the test counted even though it's compile-time
}

TEST(MatchNotOperatorTest_147, DescribeOfNegatedIsDifferentFromBase_147) {
    // We don't assert exact wording; just that the negated description differs observably.
    MockIntMatcher mock;
    ON_CALL(mock, describe()).WillByDefault(Return("is even"));
    auto neg = !mock;

    const std::string baseDesc = mock.describe();
    const std::string negDesc  = neg.describe();

    // Observable expectations about description surface:
    EXPECT_FALSE(negDesc.empty());
    EXPECT_NE(negDesc, baseDesc);
}
