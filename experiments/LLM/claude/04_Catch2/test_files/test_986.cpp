#include <gtest/gtest.h>

// Declaration of the function under test
namespace Catch {
namespace Benchmark {
namespace Detail {
double mean(double const* first, double const* last);
}
}
}

using Catch::Benchmark::Detail::mean;

class MeanTest_986 : public ::testing::Test {
protected:
};

// Normal operation: single element
TEST_F(MeanTest_986, SingleElement_986) {
    double data[] = {5.0};
    double result = mean(data, data + 1);
    EXPECT_DOUBLE_EQ(result, 5.0);
}

// Normal operation: multiple elements
TEST_F(MeanTest_986, MultipleElements_986) {
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double result = mean(data, data + 5);
    EXPECT_DOUBLE_EQ(result, 3.0);
}

// Normal operation: two elements
TEST_F(MeanTest_986, TwoElements_986) {
    double data[] = {10.0, 20.0};
    double result = mean(data, data + 2);
    EXPECT_DOUBLE_EQ(result, 15.0);
}

// Normal operation: all same values
TEST_F(MeanTest_986, AllSameValues_986) {
    double data[] = {7.0, 7.0, 7.0, 7.0};
    double result = mean(data, data + 4);
    EXPECT_DOUBLE_EQ(result, 7.0);
}

// Normal operation: negative values
TEST_F(MeanTest_986, NegativeValues_986) {
    double data[] = {-1.0, -2.0, -3.0};
    double result = mean(data, data + 3);
    EXPECT_DOUBLE_EQ(result, -2.0);
}

// Normal operation: mixed positive and negative values
TEST_F(MeanTest_986, MixedPositiveNegative_986) {
    double data[] = {-10.0, 10.0};
    double result = mean(data, data + 2);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Normal operation: all zeros
TEST_F(MeanTest_986, AllZeros_986) {
    double data[] = {0.0, 0.0, 0.0};
    double result = mean(data, data + 3);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Normal operation: floating point values
TEST_F(MeanTest_986, FloatingPointValues_986) {
    double data[] = {1.5, 2.5, 3.5};
    double result = mean(data, data + 3);
    EXPECT_DOUBLE_EQ(result, 2.5);
}

// Normal operation: large array
TEST_F(MeanTest_986, LargeArray_986) {
    const int size = 1000;
    double data[size];
    for (int i = 0; i < size; ++i) {
        data[i] = static_cast<double>(i + 1);
    }
    double result = mean(data, data + size);
    // Mean of 1..1000 = (1000 * 1001) / 2 / 1000 = 500.5
    EXPECT_DOUBLE_EQ(result, 500.5);
}

// Boundary: very large values
TEST_F(MeanTest_986, VeryLargeValues_986) {
    double data[] = {1e308, 1e308};
    double result = mean(data, data + 2);
    EXPECT_DOUBLE_EQ(result, 1e308);
}

// Boundary: very small values
TEST_F(MeanTest_986, VerySmallValues_986) {
    double data[] = {1e-308, 2e-308, 3e-308};
    double result = mean(data, data + 3);
    EXPECT_DOUBLE_EQ(result, 2e-308);
}

// Normal operation: subset of array
TEST_F(MeanTest_986, SubsetOfArray_986) {
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0};
    double result = mean(data + 1, data + 4);  // {2.0, 3.0, 4.0}
    EXPECT_DOUBLE_EQ(result, 3.0);
}

// Normal operation: single negative element
TEST_F(MeanTest_986, SingleNegativeElement_986) {
    double data[] = {-42.0};
    double result = mean(data, data + 1);
    EXPECT_DOUBLE_EQ(result, -42.0);
}

// Normal operation: values that don't divide evenly
TEST_F(MeanTest_986, NonEvenDivision_986) {
    double data[] = {1.0, 2.0};
    double result = mean(data, data + 2);
    EXPECT_DOUBLE_EQ(result, 1.5);
}

// Normal operation: three elements with known mean
TEST_F(MeanTest_986, ThreeElementsKnownMean_986) {
    double data[] = {2.0, 4.0, 9.0};
    double result = mean(data, data + 3);
    EXPECT_DOUBLE_EQ(result, 5.0);
}
