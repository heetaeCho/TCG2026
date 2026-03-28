// File: match_any_of_tests_154.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <utility>

// Include the header that contains match_any_of
#include <catch2/matchers/catch_matchers_templated.hpp>

using ::testing::Return;
using ::testing::InSequence;
using ::testing::StrictMock;

namespace {

// Simple mock with const-qualified match (because match_any_of uses T const*)
struct MockIntMatcher {
    MOCK_METHOD(bool, match, (int), (const));
};

// Helper for testing value-category forwarding behavior.
// It has two overloads: one for rvalues and one for lvalues.
struct Probe { };

struct OverloadMatcher {
    // Counters live outside so we can mutate them inside const-qualified methods.
    int* lref_calls;
    int* rref_calls;
    explicit OverloadMatcher(int& lref, int& rref) : lref_calls(&lref), rref_calls(&rref) {}

    bool match(const Probe&) const {
        ++(*lref_calls);
        return true;
    }
    bool match(Probe&&) const {
        ++(*rref_calls);
        return true;
    }
};

} // namespace

// 1) If the first matcher returns true, match_any_of should short-circuit and not call others.
TEST(MatchAnyOfTest_154, FirstMatcherShortCircuits_154) {
    StrictMock<MockIntMatcher> m0;
    StrictMock<MockIntMatcher> m1; // should NOT be called
    StrictMock<MockIntMatcher> m2; // should NOT be called

    // Later pointers are intentionally nullptr to prove they are not dereferenced on short-circuit.
    std::array<void const*, 3> matchers{ &m0, nullptr, nullptr };

    EXPECT_CALL(m0, match(42)).WillOnce(Return(true));

    int arg = 42;
    bool res = Catch::Matchers::Detail::match_any_of<MockIntMatcher, MockIntMatcher, MockIntMatcher>(
        arg, matchers, std::index_sequence<0, 1, 2>{});

    EXPECT_TRUE(res);
}

// 2) If the first is false and the second is true, the third must not be called.
TEST(MatchAnyOfTest_154, SubsequentMatcherEvaluatedWhenFirstFalse_154) {
    StrictMock<MockIntMatcher> m0;
    StrictMock<MockIntMatcher> m1;
    StrictMock<MockIntMatcher> m2; // should NOT be called

    std::array<void const*, 3> matchers{ &m0, &m1, nullptr };

    {
        InSequence seq;
        EXPECT_CALL(m0, match(7)).WillOnce(Return(false));
        EXPECT_CALL(m1, match(7)).WillOnce(Return(true));
        // No expectation for m2; StrictMock would fail if it gets called.
    }

    int arg = 7;
    bool res = Catch::Matchers::Detail::match_any_of<MockIntMatcher, MockIntMatcher, MockIntMatcher>(
        arg, matchers, std::index_sequence<0, 1, 2>{});

    EXPECT_TRUE(res);
}

// 3) When all matchers return false, the result is false and all are invoked in order.
TEST(MatchAnyOfTest_154, ReturnsFalseWhenNoMatchersMatch_154) {
    StrictMock<MockIntMatcher> m0;
    StrictMock<MockIntMatcher> m1;
    StrictMock<MockIntMatcher> m2;

    std::array<void const*, 3> matchers{ &m0, &m1, &m2 };

    {
        InSequence seq;
        EXPECT_CALL(m0, match(-1)).WillOnce(Return(false));
        EXPECT_CALL(m1, match(-1)).WillOnce(Return(false));
        EXPECT_CALL(m2, match(-1)).WillOnce(Return(false));
    }

    int arg = -1;
    bool res = Catch::Matchers::Detail::match_any_of<MockIntMatcher, MockIntMatcher, MockIntMatcher>(
        arg, matchers, std::index_sequence<0, 1, 2>{});

    EXPECT_FALSE(res);
}

// 4) Calls follow the order given by the index_sequence, not necessarily array index order.
TEST(MatchAnyOfTest_154, RespectsIndexSequenceOrder_154) {
    StrictMock<MockIntMatcher> a; // array index 0
    StrictMock<MockIntMatcher> b; // array index 1
    StrictMock<MockIntMatcher> c; // array index 2

    // Note: array is [a, b, c], but we will visit in order [2, 0, 1].
    std::array<void const*, 3> matchers{ &a, &b, &c };

    {
        InSequence seq;
        EXPECT_CALL(c, match(100)).WillOnce(Return(false)); // index 2 first
        EXPECT_CALL(a, match(100)).WillOnce(Return(false)); // then index 0
        EXPECT_CALL(b, match(100)).WillOnce(Return(true));  // finally index 1
    }

    int arg = 100;
    bool res = Catch::Matchers::Detail::match_any_of<MockIntMatcher, MockIntMatcher, MockIntMatcher>(
        arg, matchers, std::index_sequence<2, 0, 1>{});

    EXPECT_TRUE(res);
}

// 5) Arg forwarding check: even with an rvalue, arg is passed to match as an lvalue (no std::forward).
TEST(MatchAnyOfTest_154, DoesNotForwardRvalueArg_154) {
    int lref_calls = 0;
    int rref_calls = 0;
    OverloadMatcher m(lref_calls, rref_calls);

    std::array<void const*, 1> matchers{ &m };

    // Pass a temporary (rvalue). If forwarding were preserved, the rvalue overload would be used.
    // Because match_any_of calls match(arg) (not forwarding), the lvalue overload should be selected.
    bool res = Catch::Matchers::Detail::match_any_of<OverloadMatcher>(
        Probe{}, matchers, std::index_sequence<0>{});

    EXPECT_TRUE(res);
    EXPECT_EQ(lref_calls, 1) << "Expected lvalue overload to be called";
    EXPECT_EQ(rref_calls, 0) << "Rvalue overload should not be called";
}
