// File: tests/any_match_matcher_test_181.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

/// A tiny mockable predicate interface; the class under test only requires a
/// collaborator with a `bool match(const T&) const` method.
struct IntPredicateMock {
    MOCK_METHOD(bool, call, (const int&), (const));
};

/// A small forwarding matcher that satisfies the interface expected by
/// AnyMatchMatcher: it exposes `bool match(const T&) const` and forwards to the mock.
/// Copying this object preserves shared state via shared_ptr so expectations
/// remain valid even if AnyMatchMatcher stores it by value.
struct ForwardingIntMatcher {
    std::shared_ptr<IntPredicateMock> mock;
    bool match(const int& v) const { return mock->call(v); }
};

using AnyIntMatch = Catch::Matchers::AnyMatchMatcher<ForwardingIntMatcher>;

} // namespace

// Normal operation: returns true when the first element matches; should stop after first match.
TEST(AnyMatchMatcherTest_181, ReturnsTrueAndShortCircuitsOnFirstElement_181) {
    auto mock = std::make_shared<StrictMock<IntPredicateMock>>();
    ForwardingIntMatcher base{mock};
    AnyIntMatch any(base);

    // Only the first element (3) should be queried; then short-circuit.
    EXPECT_CALL(*mock, call(3)).WillOnce(Return(true));

    const std::vector<int> data{3, 4, 5};
    EXPECT_TRUE(any.match(data));
}

// Normal operation: returns true when a later element matches; should query elements up to that point only.
TEST(AnyMatchMatcherTest_181, ReturnsTrueAndStopsAfterLaterMatch_181) {
    auto mock = std::make_shared<StrictMock<IntPredicateMock>>();
    ForwardingIntMatcher base{mock};
    AnyIntMatch any(base);

    InSequence seq;
    EXPECT_CALL(*mock, call(1)).WillOnce(Return(false));
    EXPECT_CALL(*mock, call(2)).WillOnce(Return(false));
    EXPECT_CALL(*mock, call(9)).WillOnce(Return(true));
    // No call for 10 expected due to short-circuiting.

    const std::vector<int> data{1, 2, 9, 10};
    EXPECT_TRUE(any.match(data));
}

// No elements match: should return false after checking all items.
TEST(AnyMatchMatcherTest_181, ReturnsFalseWhenNoElementsMatch_181) {
    auto mock = std::make_shared<StrictMock<IntPredicateMock>>();
    ForwardingIntMatcher base{mock};
    AnyIntMatch any(base);

    InSequence seq;
    EXPECT_CALL(*mock, call(1)).WillOnce(Return(false));
    EXPECT_CALL(*mock, call(2)).WillOnce(Return(false));

    const std::vector<int> data{1, 2};
    EXPECT_FALSE(any.match(data));
}

// Boundary condition: empty range should result in no calls and return false.
TEST(AnyMatchMatcherTest_181, EmptyRangeReturnsFalseWithoutInvokingMatcher_181) {
    auto mock = std::make_shared<StrictMock<IntPredicateMock>>();
    ForwardingIntMatcher base{mock};
    AnyIntMatch any(base);

    const std::vector<int> empty{};
    EXPECT_FALSE(any.match(empty)); // With StrictMock, any unexpected call would fail the test.
}

// Accepts rvalue/temporary ranges (initializer_list) and behaves correctly.
TEST(AnyMatchMatcherTest_181, WorksWithTemporaryInitializerList_181) {
    auto mock = std::make_shared<StrictMock<IntPredicateMock>>();
    ForwardingIntMatcher base{mock};
    AnyIntMatch any(base);

    InSequence seq;
    EXPECT_CALL(*mock, call(4)).WillOnce(Return(false));
    EXPECT_CALL(*mock, call(5)).WillOnce(Return(true));

    EXPECT_TRUE(any.match(std::initializer_list<int>{4, 5, 6})); // Should stop at 5; no call for 6.
}
