// uniform_integer_distribution_b_tests_338.cpp
#include <gtest/gtest.h>
#include <limits>
#include "catch2/internal/catch_uniform_integer_distribution.hpp"

using Catch::uniform_integer_distribution;

//
// Normal operation
//
TEST(UniformIntDistTest_338, PositiveRange_ReturnsUpperInclusive_338) {
    uniform_integer_distribution<int> dist(1, 10);
    auto upper = dist.b();
    EXPECT_EQ(upper, 10);
}

TEST(UniformIntDistTest_338, CrossZeroRange_ReturnsUpperInclusive_338) {
    uniform_integer_distribution<int> dist(-3, 4);
    auto upper = dist.b();
    EXPECT_EQ(upper, 4);
}

//
// Boundary conditions
//
TEST(UniformIntDistTest_338, SingleValueRange_ReturnsThatValue_338) {
    uniform_integer_distribution<int> dist(5, 5);
    auto upper = dist.b();
    EXPECT_EQ(upper, 5);
}

TEST(UniformIntDistTest_338, NegativeOnlyRange_ReturnsUpperInclusive_338) {
    uniform_integer_distribution<int> dist(-10, -2);
    auto upper = dist.b();
    EXPECT_EQ(upper, -2);
}

TEST(UniformIntDistTest_338, NearIntExtremes_ReturnsUpperInclusive_338) {
    constexpr int minp1 = std::numeric_limits<int>::min() + 1;
    constexpr int maxm1 = std::numeric_limits<int>::max() - 1;

    // Exact-equality (narrow, safe) ranges near extremes
    {
        uniform_integer_distribution<int> dist(minp1, minp1);
        EXPECT_EQ(dist.b(), minp1);
    }
    {
        uniform_integer_distribution<int> dist(maxm1 - 4, maxm1);
        EXPECT_EQ(dist.b(), maxm1);
    }
}

//
// Type generality
//
TEST(UniformIntDistTest_338, WorksWithLongLong_ReturnsUpperInclusive_338) {
    using I = long long;
    uniform_integer_distribution<I> dist(static_cast<I>(-10000000000LL),
                                         static_cast<I>( 9999999999LL));
    auto upper = dist.b();
    EXPECT_EQ(upper, 9999999999LL);
}

//
// Idempotence / const-correctness (observable)
//
TEST(UniformIntDistTest_338, RepeatedCallsReturnSameValue_338) {
    uniform_integer_distribution<int> dist(2, 8);
    auto first = dist.b();
    auto second = dist.b();
    EXPECT_EQ(first, 8);
    EXPECT_EQ(second, 8);
}

//
// constexpr availability (compile-time observable behavior)
//
TEST(UniformIntDistTest_338, ConstexprContext_ReturnsUpperInclusive_338) {
    constexpr uniform_integer_distribution<int> dist(-7, 12);
    constexpr auto upper = dist.b();
    static_assert(upper == 12, "b() must yield the upper endpoint in constexpr context");
    EXPECT_EQ(upper, 12); // runtime check mirrors compile-time check
}
