// File: tests/ContainsElementMatcher_match_950_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/extras/catch_amalgamated.hpp"
#include <vector>
#include <list>
#include <forward_list>
#include <array>
#include <string>
#include <initializer_list>

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

template <typename ElemT>
struct EqMock {
    // Mock the underlying callable; operator() forwards to this.
    MOCK_METHOD(bool, Call, (const ElemT&, const ElemT&), (const));
    bool operator()(const ElemT& a, const ElemT& b) const { return Call(a, b); }
};

} // namespace

// ---------- Normal operation: finds desired element and stops early ----------
TEST(ContainsElementMatcher_950, ReturnsTrueWhenElementPresentStopsEarly_950) {
    using T = int;
    StrictMock<EqMock<T>> pred;
    const T desired = 2;

    // Construct matcher with (target, predicate)
    Catch::Matchers::ContainsElementMatcher<T, StrictMock<EqMock<T>>> matcher(desired, pred);

    std::vector<T> rng{1, 2, 3};

    // Expect predicate called for 1 (false) then 2 (true). No call for 3.
    EXPECT_CALL(pred, Call(Eq(1), Eq(desired))).WillOnce(Return(false));
    EXPECT_CALL(pred, Call(Eq(2), Eq(desired))).WillOnce(Return(true));

    EXPECT_TRUE(matcher.match(rng));
}

// ---------- Normal operation: not found -> false; all elements visited ----------
TEST(ContainsElementMatcher_950, ReturnsFalseWhenElementAbsentCallsAll_950) {
    using T = int;
    StrictMock<EqMock<T>> pred;
    const T desired = 2;

    Catch::Matchers::ContainsElementMatcher<T, StrictMock<EqMock<T>>> matcher(desired, pred);

    std::vector<T> rng{1, 3, 5};

    // All elements should be checked, each returning false.
    EXPECT_CALL(pred, Call(Eq(1), Eq(desired))).WillOnce(Return(false));
    EXPECT_CALL(pred, Call(Eq(3), Eq(desired))).WillOnce(Return(false));
    EXPECT_CALL(pred, Call(Eq(5), Eq(desired))).WillOnce(Return(false));

    EXPECT_FALSE(matcher.match(rng));
}

// ---------- Boundary: empty range ----------
TEST(ContainsElementMatcher_950, EmptyRangeReturnsFalseAndDoesNotInvokePredicate_950) {
    using T = int;
    StrictMock<EqMock<T>> pred;
    const T desired = 42;

    Catch::Matchers::ContainsElementMatcher<T, StrictMock<EqMock<T>>> matcher(desired, pred);

    std::vector<T> empty;
    // No calls expected.
    EXPECT_FALSE(matcher.match(empty));
}

// ---------- RangeLike rvalue (initializer_list) ----------
TEST(ContainsElementMatcher_950, WorksWithInitializerListRvalueRange_950) {
    using T = int;

    // Simple lambda predicate acting like equality: observable behavior only.
    auto pred = [](const T& a, const T& b) { return a == b; };
    Catch::Matchers::ContainsElementMatcher<T, decltype(pred)> matcher(3, pred);

    // Pass a temporary range
    EXPECT_TRUE(matcher.match(std::initializer_list<T>{1, 2, 3, 4}));
}

// ---------- Non-integral / different RangeLike: std::string of chars ----------
TEST(ContainsElementMatcher_950, WorksWithStringRange_950) {
    using T = char;
    auto pred = [](const T& a, const T& b) { return a == b; };
    Catch::Matchers::ContainsElementMatcher<T, decltype(pred)> matcher('b', pred);

    std::string s = "abc";
    EXPECT_TRUE(matcher.match(s));   // 'b' present
}

// ---------- Exceptional case: predicate throws -> exception propagates ----------
TEST(ContainsElementMatcher_950, ExceptionFromPredicatePropagates_950) {
    using T = int;
    struct ThrowingPred {
        bool operator()(const T&, const T&) const { throw std::runtime_error("boom"); }
    };

    Catch::Matchers::ContainsElementMatcher<T, ThrowingPred> matcher(1, ThrowingPred{});
    std::vector<T> rng{1, 2};

    EXPECT_THROW({ (void)matcher.match(rng); }, std::runtime_error);
}

// ---------- Single-pass style container (forward_list) & single element ----------
TEST(ContainsElementMatcher_950, WorksWithForwardListSingleElement_950) {
    using T = int;
    auto pred = [](const T& a, const T& b) { return a == b; };
    Catch::Matchers::ContainsElementMatcher<T, decltype(pred)> matcher(7, pred);

    std::forward_list<T> fl{7};
    EXPECT_TRUE(matcher.match(fl));
}

// ---------- Verify parameter order: (elem, desired) ----------
TEST(ContainsElementMatcher_950, PredicateReceivesDesiredAsSecondArg_950) {
    using T = int;
    StrictMock<EqMock<T>> pred;
    const T desired = 42;

    Catch::Matchers::ContainsElementMatcher<T, StrictMock<EqMock<T>>> matcher(desired, pred);

    std::array<T, 2> arr{10, 11};

    // Ensure second argument is always the desired target value.
    EXPECT_CALL(pred, Call(Eq(10), Eq(desired))).WillOnce(Return(false));
    EXPECT_CALL(pred, Call(Eq(11), Eq(desired))).WillOnce(Return(false));

    EXPECT_FALSE(matcher.match(arr));
}
