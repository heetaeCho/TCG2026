// File: match_all_of_tests_152.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/src/catch2/matchers/catch_matchers_templated.hpp"

#include <array>
#include <utility>
#include <stdexcept>

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace {

template <typename... Ptrs>
constexpr auto make_void_array(const Ptrs*... ptrs) {
    return std::array<void const*, sizeof...(Ptrs)>{static_cast<void const*>(ptrs)...};
}

struct MatchAllOfTest_152 : ::testing::Test {};

// Simple mock matchers for int arguments
class MockMatcherIntA {
public:
    MOCK_METHOD(bool, match, (int), (const));
};
class MockMatcherIntB {
public:
    MOCK_METHOD(bool, match, (int), (const));
};

// A throwing matcher to observe exception propagation
struct ThrowingMatcherInt {
    bool match(int) const {
        throw std::runtime_error("boom");
    }
};

// ---------- Tests ----------

// All matchers succeed => overall result is true; both are invoked
TEST_F(MatchAllOfTest_152, AllTrue_TwoMatchers_ReturnsTrue_152) {
    StrictMock<MockMatcherIntA> m1;
    StrictMock<MockMatcherIntB> m2;

    EXPECT_CALL(m1, match(42)).WillOnce(Return(true));
    EXPECT_CALL(m2, match(42)).WillOnce(Return(true));

    auto ptrs = make_void_array(&m1, &m2);
    bool ok = Catch::Matchers::Detail::match_all_of<MockMatcherIntA, MockMatcherIntB, 2, int>(
        42, ptrs, std::index_sequence<0, 1>{});

    EXPECT_TRUE(ok);
}

// First matcher fails => result is false; second is NOT invoked (short-circuit)
TEST_F(MatchAllOfTest_152, FirstFalse_ShortCircuits_152) {
    StrictMock<MockMatcherIntA> m1;
    StrictMock<MockMatcherIntB> m2;

    EXPECT_CALL(m1, match(_)).WillOnce(Return(false));
    EXPECT_CALL(m2, match(_)).Times(0);

    auto ptrs = make_void_array(&m1, &m2);
    bool ok = Catch::Matchers::Detail::match_all_of<MockMatcherIntA, MockMatcherIntB, 2, int>(
        7, ptrs, std::index_sequence<0, 1>{});

    EXPECT_FALSE(ok);
}

// First succeeds, second fails => result is false; both are invoked exactly once
TEST_F(MatchAllOfTest_152, SecondFalse_CallsBoth_ReturnsFalse_152) {
    StrictMock<MockMatcherIntA> m1;
    StrictMock<MockMatcherIntB> m2;

    EXPECT_CALL(m1, match(7)).WillOnce(Return(true));
    EXPECT_CALL(m2, match(7)).WillOnce(Return(false));

    auto ptrs = make_void_array(&m1, &m2);
    bool ok = Catch::Matchers::Detail::match_all_of<MockMatcherIntA, MockMatcherIntB, 2, int>(
        7, ptrs, std::index_sequence<0, 1>{});

    EXPECT_FALSE(ok);
}

// Single matcher (base case) true
TEST_F(MatchAllOfTest_152, SingleMatcher_True_152) {
    StrictMock<MockMatcherIntA> m;

    EXPECT_CALL(m, match(123)).WillOnce(Return(true));

    auto ptrs = make_void_array(&m);
    bool ok = Catch::Matchers::Detail::match_all_of<MockMatcherIntA, 1, int>(
        123, ptrs, std::index_sequence<0>{});

    EXPECT_TRUE(ok);
}

// Single matcher (base case) false
TEST_F(MatchAllOfTest_152, SingleMatcher_False_152) {
    StrictMock<MockMatcherIntA> m;

    EXPECT_CALL(m, match(123)).WillOnce(Return(false));

    auto ptrs = make_void_array(&m);
    bool ok = Catch::Matchers::Detail::match_all_of<MockMatcherIntA, 1, int>(
        123, ptrs, std::index_sequence<0>{});

    EXPECT_FALSE(ok);
}

// Heterogeneous matcher types in the same array are supported and called in order
TEST_F(MatchAllOfTest_152, HeterogeneousTypes_BothTrue_152) {
    StrictMock<MockMatcherIntA> m1;
    StrictMock<MockMatcherIntB> m2;

    EXPECT_CALL(m1, match(10)).WillOnce(Return(true));
    EXPECT_CALL(m2, match(10)).WillOnce(Return(true));

    auto ptrs = make_void_array(&m1, &m2);
    bool ok = Catch::Matchers::Detail::match_all_of<MockMatcherIntA, MockMatcherIntB, 2, int>(
        10, ptrs, std::index_sequence<0, 1>{});

    EXPECT_TRUE(ok);
}

// If a matcher throws, the exception propagates and subsequent matchers are not called
TEST_F(MatchAllOfTest_152, ExceptionInFirst_Propagates_And_Stops_152) {
    ThrowingMatcherInt throwing;
    StrictMock<MockMatcherIntB> next;

    EXPECT_CALL(next, match(_)).Times(0);

    auto ptrs = make_void_array(&throwing, &next);

    EXPECT_THROW(
        (void)Catch::Matchers::Detail::match_all_of<ThrowingMatcherInt, MockMatcherIntB, 2, int>(
            99, ptrs, std::index_sequence<0, 1>{}),
        std::runtime_error
    );
}

} // namespace
