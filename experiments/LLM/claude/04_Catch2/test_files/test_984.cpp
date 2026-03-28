#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <cmath>

// Forward declaration of the function under test
namespace Catch {
namespace Benchmark {
namespace Detail {
double weighted_average_quantile(int k, int q, double* first, double* last);
}
}
}

using Catch::Benchmark::Detail::weighted_average_quantile;

class WeightedAverageQuantileTest_984 : public ::testing::Test {
protected:
};

// Test with a single element array - should return that element
TEST_F(WeightedAverageQuantileTest_984, SingleElement_984) {
    std::vector<double> data = {42.0};
    double result = weighted_average_quantile(0, 1, data.data(), data.data() + data.size());
    EXPECT_DOUBLE_EQ(result, 42.0);
}

// Test median (k=1, q=2) of an odd-sized sorted array
TEST_F(WeightedAverageQuantileTest_984, MedianOddSortedArray_984) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (5-1)*1/2 = 2.0, j=2, g=0.0 => xj = element at index 2 after partial sort = 3.0
    EXPECT_DOUBLE_EQ(result, 3.0);
}

// Test median (k=1, q=2) of an even-sized sorted array
TEST_F(WeightedAverageQuantileTest_984, MedianEvenSortedArray_984) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (4-1)*1/2 = 1.5, j=1, g=0.5 => xj=2.0, xj1=3.0, result = 2.0 + 0.5*(3.0-2.0) = 2.5
    EXPECT_DOUBLE_EQ(result, 2.5);
}

// Test with k=0 (minimum quantile boundary)
TEST_F(WeightedAverageQuantileTest_984, KZeroReturnsFirstElement_984) {
    std::vector<double> data = {5.0, 3.0, 1.0, 4.0, 2.0};
    double result = weighted_average_quantile(0, 4, data.data(), data.data() + data.size());
    // idx = (5-1)*0/4 = 0.0, j=0, g=0.0 => returns min element = 1.0
    EXPECT_DOUBLE_EQ(result, 1.0);
}

// Test with k=q (maximum quantile boundary)
TEST_F(WeightedAverageQuantileTest_984, KEqualsQReturnsLastElement_984) {
    std::vector<double> data = {5.0, 3.0, 1.0, 4.0, 2.0};
    double result = weighted_average_quantile(4, 4, data.data(), data.data() + data.size());
    // idx = (5-1)*4/4 = 4.0, j=4, g=0.0 => returns max element = 5.0
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// Test with unsorted data
TEST_F(WeightedAverageQuantileTest_984, UnsortedData_984) {
    std::vector<double> data = {10.0, 1.0, 5.0, 3.0, 8.0};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // Sorted: {1, 3, 5, 8, 10}, idx = 4*1/2 = 2.0, j=2, g=0.0 => 5.0
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// Test first quartile (k=1, q=4)
TEST_F(WeightedAverageQuantileTest_984, FirstQuartile_984) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    double result = weighted_average_quantile(1, 4, data.data(), data.data() + data.size());
    // idx = (5-1)*1/4 = 1.0, j=1, g=0.0 => 2.0
    EXPECT_DOUBLE_EQ(result, 2.0);
}

// Test third quartile (k=3, q=4)
TEST_F(WeightedAverageQuantileTest_984, ThirdQuartile_984) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0};
    double result = weighted_average_quantile(3, 4, data.data(), data.data() + data.size());
    // idx = (5-1)*3/4 = 3.0, j=3, g=0.0 => 4.0
    EXPECT_DOUBLE_EQ(result, 4.0);
}

// Test interpolation with non-integer index
TEST_F(WeightedAverageQuantileTest_984, InterpolationNonIntegerIndex_984) {
    std::vector<double> data = {10.0, 20.0, 30.0};
    double result = weighted_average_quantile(1, 4, data.data(), data.data() + data.size());
    // idx = (3-1)*1/4 = 0.5, j=0, g=0.5 => xj=10.0, xj1=20.0, result = 10.0 + 0.5*(20.0-10.0) = 15.0
    EXPECT_DOUBLE_EQ(result, 15.0);
}

// Test with two elements, median
TEST_F(WeightedAverageQuantileTest_984, TwoElementsMedian_984) {
    std::vector<double> data = {100.0, 200.0};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (2-1)*1/2 = 0.5, j=0, g=0.5 => xj=100.0, xj1=200.0, result = 100.0 + 0.5*(200.0-100.0) = 150.0
    EXPECT_DOUBLE_EQ(result, 150.0);
}

// Test with identical elements
TEST_F(WeightedAverageQuantileTest_984, AllIdenticalElements_984) {
    std::vector<double> data = {7.0, 7.0, 7.0, 7.0, 7.0};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    EXPECT_DOUBLE_EQ(result, 7.0);
}

// Test with negative values
TEST_F(WeightedAverageQuantileTest_984, NegativeValues_984) {
    std::vector<double> data = {-5.0, -3.0, -1.0, 0.0, 2.0};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (5-1)*1/2 = 2.0, j=2, g=0.0 => -1.0
    EXPECT_DOUBLE_EQ(result, -1.0);
}

// Test with mixed negative and positive, unsorted
TEST_F(WeightedAverageQuantileTest_984, MixedNegativePositiveUnsorted_984) {
    std::vector<double> data = {3.0, -2.0, 7.0, -5.0, 1.0, 0.0};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // Sorted: {-5, -2, 0, 1, 3, 7}, idx = (6-1)*1/2 = 2.5, j=2, g=0.5
    // xj=0.0, xj1=1.0, result = 0.0 + 0.5*(1.0-0.0) = 0.5
    EXPECT_DOUBLE_EQ(result, 0.5);
}

// Test with large array
TEST_F(WeightedAverageQuantileTest_984, LargeArray_984) {
    std::vector<double> data(1000);
    for (int i = 0; i < 1000; ++i) {
        data[i] = static_cast<double>(i + 1); // 1.0 to 1000.0
    }
    // Shuffle to test with unsorted data
    std::reverse(data.begin(), data.end());
    
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (1000-1)*1/2 = 499.5, j=499, g=0.5
    // After sorting: xj = 500.0, xj1 = 501.0, result = 500.0 + 0.5*1.0 = 500.5
    EXPECT_DOUBLE_EQ(result, 500.5);
}

// Test percentile k=1, q=10 (10th percentile)
TEST_F(WeightedAverageQuantileTest_984, TenthPercentile_984) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};
    double result = weighted_average_quantile(1, 10, data.data(), data.data() + data.size());
    // idx = (11-1)*1/10 = 1.0, j=1, g=0.0 => 2.0
    EXPECT_DOUBLE_EQ(result, 2.0);
}

// Test with floating point data
TEST_F(WeightedAverageQuantileTest_984, FloatingPointData_984) {
    std::vector<double> data = {0.1, 0.2, 0.3, 0.4, 0.5};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (5-1)*1/2 = 2.0, j=2, g=0.0 => 0.3
    EXPECT_DOUBLE_EQ(result, 0.3);
}

// Test interpolation with g close to 1
TEST_F(WeightedAverageQuantileTest_984, InterpolationGCloseToOne_984) {
    std::vector<double> data = {0.0, 10.0, 20.0};
    double result = weighted_average_quantile(3, 4, data.data(), data.data() + data.size());
    // idx = (3-1)*3/4 = 1.5, j=1, g=0.5 => xj=10.0, xj1=20.0, result = 10.0 + 0.5*10.0 = 15.0
    EXPECT_DOUBLE_EQ(result, 15.0);
}

// Test with duplicate values in array
TEST_F(WeightedAverageQuantileTest_984, DuplicateValues_984) {
    std::vector<double> data = {1.0, 1.0, 2.0, 2.0, 3.0, 3.0};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (6-1)*1/2 = 2.5, j=2, g=0.5 => sorted: {1,1,2,2,3,3}, xj=2.0, xj1=2.0
    // result = 2.0 + 0.5*(2.0-2.0) = 2.0
    EXPECT_DOUBLE_EQ(result, 2.0);
}

// Test with very large values
TEST_F(WeightedAverageQuantileTest_984, VeryLargeValues_984) {
    std::vector<double> data = {1e15, 2e15, 3e15};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (3-1)*1/2 = 1.0, j=1, g=0.0 => 2e15
    EXPECT_DOUBLE_EQ(result, 2e15);
}

// Test with very small values
TEST_F(WeightedAverageQuantileTest_984, VerySmallValues_984) {
    std::vector<double> data = {1e-15, 2e-15, 3e-15};
    double result = weighted_average_quantile(1, 2, data.data(), data.data() + data.size());
    // idx = (3-1)*1/2 = 1.0, j=1, g=0.0 => 2e-15
    EXPECT_DOUBLE_EQ(result, 2e-15);
}

// Test k=0, q=1 for a single element
TEST_F(WeightedAverageQuantileTest_984, KZeroQOneSingleElement_984) {
    std::vector<double> data = {99.0};
    double result = weighted_average_quantile(0, 1, data.data(), data.data() + data.size());
    EXPECT_DOUBLE_EQ(result, 99.0);
}

// Test 90th percentile
TEST_F(WeightedAverageQuantileTest_984, NinetiethPercentile_984) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0};
    double result = weighted_average_quantile(9, 10, data.data(), data.data() + data.size());
    // idx = (11-1)*9/10 = 9.0, j=9, g=0.0 => 10.0
    EXPECT_DOUBLE_EQ(result, 10.0);
}
