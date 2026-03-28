// File: tests/weighted_average_quantile_984_test.cpp

#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <algorithm>

// Forward declaration matching the provided interface.
// We do not include or rely on any private headers/impl details.
namespace Catch { namespace Benchmark { namespace Detail {
    double weighted_average_quantile( int k, int q, double* first, double* last );
}}}

// For brevity
using Catch::Benchmark::Detail::weighted_average_quantile;

// NOTE: The function mutates the input range (it uses std::nth_element).
// Each test uses its own fresh container to avoid cross-test effects.

TEST(WeightedAverageQuantileTest_984, ReturnsMinWhenK0_984) {
    // Boundary: k == 0 should pick the minimum element (g == 0).
    std::array<double, 5> a{5, 3, 4, 1, 2};
    const double result = weighted_average_quantile(/*k=*/0, /*q=*/5, a.data(), a.data() + a.size());
    EXPECT_DOUBLE_EQ(result, 1.0);
}

TEST(WeightedAverageQuantileTest_984, ReturnsMaxSideWhenKEqualsQMinus1_984) {
    // Boundary near the upper end: k == q - 1
    // n = 5, k = 4, q = 5 -> idx = (n-1)*k/q = 4*4/5 = 3.2
    // j=3, g=0.2; sorted values [1,2,3,4,5] -> xj=4, xj1=5 -> expected 4.2
    std::array<double, 5> a{5, 4, 3, 2, 1};
    const double result = weighted_average_quantile(/*k=*/4, /*q=*/5, a.data(), a.data() + a.size());
    EXPECT_NEAR(result, 4.2, 1e-12);
}

TEST(WeightedAverageQuantileTest_984, MedianExactWhenDivisible_984) {
    // Exact index case (g == 0): n=5, k=1, q=2 -> idx=(4*1)/2=2 -> return the 3rd smallest => 3
    std::array<double, 5> a{1, 2, 3, 4, 5};
    const double result = weighted_average_quantile(/*k=*/1, /*q=*/2, a.data(), a.data() + a.size());
    EXPECT_DOUBLE_EQ(result, 3.0);
}

TEST(WeightedAverageQuantileTest_984, FractionalInterpolation_984) {
    // Fractional case: n=4, k=1, q=4 -> idx=(3*1)/4=0.75 -> j=0, g=0.75
    // sorted values [0,10,20,30] -> xj=0, xj1=10 -> expected = 0 + 0.75*(10) = 7.5
    std::array<double, 4> a{10, 0, 20, 30};
    const double result = weighted_average_quantile(/*k=*/1, /*q=*/4, a.data(), a.data() + a.size());
    EXPECT_NEAR(result, 7.5, 1e-12);
}

TEST(WeightedAverageQuantileTest_984, SingleElementAlwaysThatElement_984) {
    // Single element array: regardless of k/q (with q>0), result must be that element (g==0 path).
    std::array<double, 1> a{42.0};
    const double result = weighted_average_quantile(/*k=*/0, /*q=*/1, a.data(), a.data() + a.size());
    EXPECT_DOUBLE_EQ(result, 42.0);
}

TEST(WeightedAverageQuantileTest_984, AllEqualElementsReturnThatValue_984) {
    // All elements equal: any quantile should be the same value.
    std::array<double, 4> a{5.0, 5.0, 5.0, 5.0};
    const double result = weighted_average_quantile(/*k=*/2, /*q=*/3, a.data(), a.data() + a.size());
    EXPECT_DOUBLE_EQ(result, 5.0);
}

TEST(WeightedAverageQuantileTest_984, HandlesNegativeAndUnsortedValues_984) {
    // Mixed signs and unsorted input:
    // n=4, k=1, q=2 -> idx=(3*1)/2=1.5 -> j=1, g=0.5
    // sorted [-50, -1, 3, 100] -> xj=-1, xj1=3 -> expected -1 + 0.5*(4) = 1.0
    std::array<double, 4> a{-1, 100, -50, 3};
    const double result = weighted_average_quantile(/*k=*/1, /*q=*/2, a.data(), a.data() + a.size());
    EXPECT_NEAR(result, 1.0, 1e-12);
}

TEST(WeightedAverageQuantileTest_984, ResultIndependentOfInitialOrder_984) {
    // Observable behavior: result should not depend on initial ordering of the inputs.
    // Use the same multiset of values in different orders and compare returned value.
    std::array<double, 6> a1{9, 1, 5, 7, 3, 11};
    std::array<double, 6> a2{11, 7, 5, 3, 1, 9};
    // Choose a fractional index: n=6, k=2, q=5 -> idx=(5*2)/5=2.0 (exact), expect the 3rd smallest = 5
    const double r1 = weighted_average_quantile(/*k=*/2, /*q=*/5, a1.data(), a1.data() + a1.size());
    const double r2 = weighted_average_quantile(/*k=*/2, /*q=*/5, a2.data(), a2.data() + a2.size());
    EXPECT_DOUBLE_EQ(r1, 5.0);
    EXPECT_DOUBLE_EQ(r2, 5.0);
}
