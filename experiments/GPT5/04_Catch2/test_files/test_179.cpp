// File: none_match_matcher_tests_179.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <list>

// Assume the production header provides this (from the prompt)
#include "catch2/matchers/catch_matchers_quantifiers.hpp"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

// Minimal mock for a collaborator that conforms to the expected interface:
// it must provide bool match(const T&) const;
template <typename T>
class MockMatcher {
public:
    MOCK_METHOD(bool, match, (const T&), (const));
};

//
// Tests
//

// Empty range should result in true (no elements match).
TEST(NoneMatchMatcherTest_179, EmptyRange_ReturnsTrue_179) {
    MockMatcher<int> mock;
    // No calls expected since the range is empty
    Catch::Matchers::NoneMatchMatcher<MockMatcher<int>> sut(mock);

    std::vector<int> empty;
    EXPECT_TRUE(sut.match(empty));
}

// Range where no element matches should return true and call match for each element.
TEST(NoneMatchMatcherTest_179, NoElementsMatch_ReturnsTrue_AndChecksAll_179) {
    MockMatcher<int> mock;

    // For elements 1,2,3 -> always false
    {
        InSequence seq;
        EXPECT_CALL(mock, match(1)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(2)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(3)).WillOnce(Return(false));
    }

    Catch::Matchers::NoneMatchMatcher<MockMatcher<int>> sut(mock);

    std::vector<int> v{1,2,3};
    EXPECT_TRUE(sut.match(v));
}

// If any element matches, result should be false and iteration should short-circuit.
TEST(NoneMatchMatcherTest_179, OneElementMatches_ReturnsFalse_AndStopsEarly_179) {
    MockMatcher<int> mock;

    // For elements 10, 20, 30 -> first two false, third true; should stop at 30
    {
        InSequence seq;
        EXPECT_CALL(mock, match(10)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(20)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(30)).WillOnce(Return(true));
    }
    // No expectation for any element after 30 — verifies short-circuiting

    Catch::Matchers::NoneMatchMatcher<MockMatcher<int>> sut(mock);

    std::vector<int> v{10,20,30,40,50};
    EXPECT_FALSE(sut.match(v));
}

// If the first element matches, it should return false after a single call.
TEST(NoneMatchMatcherTest_179, FirstElementMatches_StopsImmediately_179) {
    MockMatcher<int> mock;

    EXPECT_CALL(mock, match(42)).WillOnce(Return(true));
    // No more calls expected

    Catch::Matchers::NoneMatchMatcher<MockMatcher<int>> sut(mock);

    std::list<int> lst{42, 43, 44, 45};
    EXPECT_FALSE(sut.match(lst));
}

// Verify it works with rvalue ranges (temporary containers) as well.
TEST(NoneMatchMatcherTest_179, WorksWithRvalueRange_179) {
    MockMatcher<int> mock;

    {
        InSequence seq;
        EXPECT_CALL(mock, match(5)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(6)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(7)).WillOnce(Return(false));
    }

    Catch::Matchers::NoneMatchMatcher<MockMatcher<int>> sut(mock);

    EXPECT_TRUE(sut.match(std::vector<int>{5,6,7}));
}

// When all elements would match, the matcher should still short-circuit at the first.
TEST(NoneMatchMatcherTest_179, AllElementsWouldMatch_ButStopsAtFirst_179) {
    MockMatcher<int> mock;

    // Only the first element call is required to prove short-circuit
    EXPECT_CALL(mock, match(1)).WillOnce(Return(true));

    Catch::Matchers::NoneMatchMatcher<MockMatcher<int>> sut(mock);

    std::vector<int> v{1,1,1,1};
    EXPECT_FALSE(sut.match(v));
}

// Mixed values: ensure parameters are forwarded as seen and evaluated in order.
TEST(NoneMatchMatcherTest_179, EvaluatesElementsInOrder_179) {
    MockMatcher<int> mock;

    {
        InSequence seq;
        EXPECT_CALL(mock, match(3)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(1)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(4)).WillOnce(Return(true)); // stop here
    }

    Catch::Matchers::NoneMatchMatcher<MockMatcher<int>> sut(mock);

    std::vector<int> v{3,1,4,1,5,9};
    EXPECT_FALSE(sut.match(v));
}
