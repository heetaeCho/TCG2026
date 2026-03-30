// File: match_allof_and_operator_tests_138.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/src/catch2/matchers/catch_matchers.hpp"

using ::testing::Return;
using ::testing::_;
using ::testing::AnyNumber;
using ::testing::AtLeast;

namespace Catch { namespace Matchers {

// Mock collaborator: external to the class under test (allowed by constraints).
template <typename T>
class MockMatcher : public MatcherBase<T> {
public:
    MOCK_METHOD(bool, match, (T const&), (const, override));
    MOCK_METHOD(std::string, describe, (), (const, override));
};

}} // namespace Catch::Matchers

// Alias to reduce verbosity in tests
template <typename T>
using MockMatcher = Catch::Matchers::MockMatcher<T>;

template <typename T>
using MatchAllOfT = Catch::Matchers::Detail::MatchAllOf<T>;

// -------------------- Tests --------------------

// Normal operation: combining a single matcher with an empty MatchAllOf rvalue.
// Verifies that calling match() on the resulting object consults the LHS matcher once.
TEST(MatchAllOfAndOperator_138, SingleMatcherIsConsultedOnMatch_138) {
    MockMatcher<int> lhs;
    EXPECT_CALL(lhs, match(42)).Times(1).WillOnce(Return(true));
    // describe() might be called by the implementation; we allow any calls safely.
    EXPECT_CALL(lhs, describe()).Times(AnyNumber());

    auto combined = lhs && MatchAllOfT<int>{};
    (void)combined.match(42);
}

// Normal operation: chaining multiple && inserts additional matchers and all are consulted.
// We do not assert final boolean result (black-box), only that each collaborator is invoked.
TEST(MatchAllOfAndOperator_138, ChainedAndInvokesAllSubMatchers_138) {
    MockMatcher<int> m1, m2;

    EXPECT_CALL(m1, match(7)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(m2, match(7)).Times(1).WillOnce(Return(false));
    EXPECT_CALL(m1, describe()).Times(AnyNumber());
    EXPECT_CALL(m2, describe()).Times(AnyNumber());

    auto combined = m1 && MatchAllOfT<int>{};
    auto combined2 = m2 && std::move(combined);

    // We only verify interaction (each collaborator is consulted).
    (void)combined2.match(7);
}

// Boundary condition: empty MatchAllOf composed and then moved again.
// Ensures the result remains callable (no UB/crash) and collaborators are still consulted once added.
TEST(MatchAllOfAndOperator_138, MoveChainedRvalueRemainsUsable_138) {
    MockMatcher<int> m1, m2;

    EXPECT_CALL(m1, match(0)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(m2, match(0)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(m1, describe()).Times(AnyNumber());
    EXPECT_CALL(m2, describe()).Times(AnyNumber());

    // Build in two steps with explicit moves to exercise rvalue handling.
    auto step1 = m1 && MatchAllOfT<int>{};
    auto step2 = m2 && std::move(step1);

    (void)step2.match(0);
}

// Observable description behavior: the combined description should reflect that
// both sub-matchers contribute *some* text. We do not assert exact formatting,
// only that both substrings appear in the combined description.
TEST(MatchAllOfAndOperator_138, DescribeMentionsAllSubMatchers_138) {
    MockMatcher<int> m1, m2;

    EXPECT_CALL(m1, match(_)).Times(AtLeast(0)).WillRepeatedly(Return(true));
    EXPECT_CALL(m2, match(_)).Times(AtLeast(0)).WillRepeatedly(Return(true));

    EXPECT_CALL(m1, describe()).Times(AtLeast(1)).WillRepeatedly(Return("is positive"));
    EXPECT_CALL(m2, describe()).Times(AtLeast(1)).WillRepeatedly(Return("is even"));

    auto combined = m1 && MatchAllOfT<int>{};
    auto combined2 = m2 && std::move(combined);

    const std::string desc = combined2.describe();
    // Order-agnostic containment checks to avoid relying on internal formatting.
    EXPECT_NE(desc.find("is positive"), std::string::npos);
    EXPECT_NE(desc.find("is even"), std::string::npos);
}

// Edge-ish behavior: Calling match/describe on a default-constructed MatchAllOf
// after prepending a single matcher should still work.
// This test focuses on robustness of the operator and public methods under minimal composition.
TEST(MatchAllOfAndOperator_138, WorksWithDefaultConstructedRhs_138) {
    MockMatcher<int> lhs;

    EXPECT_CALL(lhs, match(123)).Times(1).WillOnce(Return(true));
    EXPECT_CALL(lhs, describe()).Times(AtLeast(0)).WillRepeatedly(Return("anything"));

    auto combined = lhs && MatchAllOfT<int>{};
    EXPECT_NO_THROW({
        (void)combined.match(123);
        (void)combined.describe();
    });
}
