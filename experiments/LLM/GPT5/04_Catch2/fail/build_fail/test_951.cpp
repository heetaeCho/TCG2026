// File: tests/ContainsMatcherMatcherTests_951.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/extras/catch_amalgamated.hpp"
#include <array>
#include <string>
#include <vector>

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Simple mocks bound to concrete element types, used only as external collaborators.
struct MockIntMatcher {
    MOCK_METHOD(bool, match, (int), (const));
};

struct MockCharMatcher {
    MOCK_METHOD(bool, match, (char), (const));
};

struct MockStringMatcher {
    MOCK_METHOD(bool, match, (const std::string&), (const));
};

// A move-only matcher to verify the constructor accepts move-only types.
// This is an external collaborator (test double), not simulating internals.
class MoveOnlyIntMatcher {
public:
    explicit MoveOnlyIntMatcher(int target) : target_(target) {}
    MoveOnlyIntMatcher(const MoveOnlyIntMatcher&) = delete;
    MoveOnlyIntMatcher& operator=(const MoveOnlyIntMatcher&) = delete;
    MoveOnlyIntMatcher(MoveOnlyIntMatcher&&) noexcept = default;
    MoveOnlyIntMatcher& operator=(MoveOnlyIntMatcher&&) noexcept = default;

    bool match(int v) const { return v == target_; }

private:
    int target_;
};

} // namespace

// Test fixture (kept minimal; no reliance on private/internal state).
class ContainsMatcherMatcherTest_951 : public ::testing::Test {};


// Normal operation: returns true when any element matches.
TEST_F(ContainsMatcherMatcherTest_951, ReturnsTrueWhenAnyElementMatches_951) {
    StrictMock<MockIntMatcher> mock;
    Catch::Matchers::ContainsMatcherMatcher<StrictMock<MockIntMatcher>> contains(mock);

    std::vector<int> v{1, 2, 3};

    InSequence seq;
    EXPECT_CALL(mock, match(1)).WillOnce(Return(false));
    EXPECT_CALL(mock, match(2)).WillOnce(Return(false));
    EXPECT_CALL(mock, match(3)).WillOnce(Return(true));

    EXPECT_TRUE(contains.match(v));
}

// Normal operation (negative case): returns false when no elements match.
TEST_F(ContainsMatcherMatcherTest_951, ReturnsFalseWhenNoElementsMatch_951) {
    StrictMock<MockIntMatcher> mock;
    Catch::Matchers::ContainsMatcherMatcher<StrictMock<MockIntMatcher>> contains(mock);

    std::vector<int> v{4, 5};

    InSequence seq;
    EXPECT_CALL(mock, match(4)).WillOnce(Return(false));
    EXPECT_CALL(mock, match(5)).WillOnce(Return(false));

    EXPECT_FALSE(contains.match(v));
}

// Boundary: empty range -> no elements to test; should return false and not invoke matcher.
TEST_F(ContainsMatcherMatcherTest_951, HandlesEmptyRange_951) {
    StrictMock<MockIntMatcher> mock;
    Catch::Matchers::ContainsMatcherMatcher<StrictMock<MockIntMatcher>> contains(mock);

    std::vector<int> empty;
    // No calls expected
    EXPECT_FALSE(contains.match(empty));
}

// External interaction verification: stops after first successful match
// (i.e., does not invoke matcher on subsequent elements).
TEST_F(ContainsMatcherMatcherTest_951, StopsAfterFirstSuccessfulMatch_951) {
    StrictMock<MockIntMatcher> mock;
    Catch::Matchers::ContainsMatcherMatcher<StrictMock<MockIntMatcher>> contains(mock);

    std::vector<int> v{10, 20, 30};

    {
        InSequence seq;
        EXPECT_CALL(mock, match(10)).WillOnce(Return(false));
        EXPECT_CALL(mock, match(20)).WillOnce(Return(true));
        // When it returns true for 20, 30 should not be consulted:
        // no EXPECT_CALL for match(30) => any unexpected call would fail the test.
    }

    EXPECT_TRUE(contains.match(v));
}

// RangeLike rvalue (initializer_list): works with temporary ranges.
TEST_F(ContainsMatcherMatcherTest_951, WorksWithInitializerListRvalue_951) {
    StrictMock<MockCharMatcher> mock;
    Catch::Matchers::ContainsMatcherMatcher<StrictMock<MockCharMatcher>> contains(mock);

    InSequence seq;
    EXPECT_CALL(mock, match('a')).WillOnce(Return(false));
    EXPECT_CALL(mock, match('b')).WillOnce(Return(true));

    EXPECT_TRUE(contains.match(std::initializer_list<char>{'a', 'b', 'c'}));
}

// Different element type: strings in an array.
TEST_F(ContainsMatcherMatcherTest_951, WorksWithArrayOfStrings_951) {
    StrictMock<MockStringMatcher> mock;
    Catch::Matchers::ContainsMatcherMatcher<StrictMock<MockStringMatcher>> contains(mock);

    std::array<std::string, 3> arr{{"foo", "bar", "baz"}};

    InSequence seq;
    EXPECT_CALL(mock, match(std::string("foo"))).WillOnce(Return(false));
    EXPECT_CALL(mock, match(std::string("bar"))).WillOnce(Return(true));

    EXPECT_TRUE(contains.match(arr));
}

// Constructor should accept move-only matchers (by value + move) and function should work.
TEST_F(ContainsMatcherMatcherTest_951, AcceptsMoveOnlyMatcher_951) {
    Catch::Matchers::ContainsMatcherMatcher<MoveOnlyIntMatcher> contains(MoveOnlyIntMatcher{42});

    std::vector<int> v{0, 1, 42, 100};
    EXPECT_TRUE(contains.match(v));

    std::vector<int> w{1, 2, 3};
    EXPECT_FALSE(contains.match(w));
}
