// File: test_mean_986.cpp
#include <gtest/gtest.h>
#include <cmath>   // std::isnan, std::isfinite

// Forward declare only the public-facing signature inside the correct namespaces.
// We assume the implementation is linked from the production object/library.
namespace Catch { namespace Benchmark { namespace Detail {
    double mean(double const* first, double const* last);
}}}

// Test fixture (optional, for naming consistency & future extension)
class MeanFunctionTest_986 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(MeanFunctionTest_986, MeanOfPositiveNumbers_986) {
    double data[] = {1.0, 2.0, 3.0, 4.0};
    double result = Catch::Benchmark::Detail::mean(std::begin(data), std::end(data));
    EXPECT_DOUBLE_EQ(result, 2.5);
}

TEST_F(MeanFunctionTest_986, MeanOfNegativeNumbers_986) {
    double data[] = {-5.0, -1.0, -4.0};
    double result = Catch::Benchmark::Detail::mean(std::begin(data), std::end(data));
    EXPECT_DOUBLE_EQ(result, (-5.0 - 1.0 - 4.0) / 3.0); // -3.333...
}

TEST_F(MeanFunctionTest_986, MeanOfMixedNumbers_986) {
    double data[] = {-2.0, 3.0, -1.0, 4.0, -4.0};
    // Sum = 0, n = 5 -> mean = 0
    double result = Catch::Benchmark::Detail::mean(std::begin(data), std::end(data));
    EXPECT_DOUBLE_EQ(result, 0.0);
}

TEST_F(MeanFunctionTest_986, MeanOfZeros_986) {
    double data[] = {0.0, 0.0, 0.0, 0.0};
    double result = Catch::Benchmark::Detail::mean(std::begin(data), std::end(data));
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// --- Boundary conditions ---

TEST_F(MeanFunctionTest_986, SingleElementRange_986) {
    double data[] = {42.5};
    double result = Catch::Benchmark::Detail::mean(std::begin(data), std::end(data));
    EXPECT_DOUBLE_EQ(result, 42.5);
}

TEST_F(MeanFunctionTest_986, EmptyRangeReturnsNaN_986) {
    // first == last -> empty range. The observable behavior of double math is NaN (0.0/0.0).
    double* first = nullptr;
    double* last  = nullptr;
    double result = Catch::Benchmark::Detail::mean(first, last);
    EXPECT_TRUE(std::isnan(result));
}

// --- Large magnitude / precision sanity ---

TEST_F(MeanFunctionTest_986, LargeValuesRemainFiniteAndReasonable_986) {
    // Use values large enough to be meaningful but avoid guaranteed overflow when summed.
    // This is a sanity check that the returned value is the expected average.
    const double a = 1e300;
    const double b = 1e300;
    const double c = 1e300;
    double data[] = {a, b, c}; // sum = 3e300, mean = 1e300
    double result = Catch::Benchmark::Detail::mean(std::begin(data), std::end(data));
    // Exact equality is fine here because the exact mean is representable as 1e300.
    EXPECT_DOUBLE_EQ(result, 1e300);
}

// --- Stability around small decimals ---

TEST_F(MeanFunctionTest_986, SmallDecimalValues_986) {
    double data[] = {0.1, 0.2, 0.3};
    double expected = (0.1 + 0.2 + 0.3) / 3.0; // Beware FP representation; use NEAR.
    double result = Catch::Benchmark::Detail::mean(std::begin(data), std::end(data));
    EXPECT_NEAR(result, expected, 1e-15);
}
