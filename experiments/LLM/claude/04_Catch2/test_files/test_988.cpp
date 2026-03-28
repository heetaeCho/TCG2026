#include <gtest/gtest.h>
#include <cmath>
#include <limits>

// Declaration of the functions we're testing
namespace Catch {
namespace Benchmark {
namespace Detail {
double erfc_inv(double x);
double erf_inv(double x);
}
}
}

using Catch::Benchmark::Detail::erfc_inv;

// Test normal operation: erfc_inv(1.0) should equal erf_inv(0.0) which should be 0.0
TEST(ErfcInvTest_988, ErfcInvOfOne_988) {
    double result = erfc_inv(1.0);
    EXPECT_DOUBLE_EQ(result, 0.0);
}

// Test that erfc_inv(2.0) corresponds to erf_inv(-1.0)
// erf_inv(-1.0) should be -infinity or a very large negative number
TEST(ErfcInvTest_988, ErfcInvOfTwo_988) {
    double result = erfc_inv(2.0);
    // erf_inv(-1.0) is -infinity
    EXPECT_TRUE(std::isinf(result) || result < -1e10);
}

// Test that erfc_inv(0.0) corresponds to erf_inv(1.0)
// erf_inv(1.0) should be +infinity or a very large positive number
TEST(ErfcInvTest_988, ErfcInvOfZero_988) {
    double result = erfc_inv(0.0);
    EXPECT_TRUE(std::isinf(result) || result > 1e10);
}

// Test symmetry: erfc_inv(1 - x) should be close to erf_inv(x) by definition
// erfc_inv(1.0 - 0.5) = erf_inv(0.5)
TEST(ErfcInvTest_988, ErfcInvRelationToErfInv_988) {
    double erfc_result = erfc_inv(0.5);
    double erf_result = Catch::Benchmark::Detail::erf_inv(0.5);
    EXPECT_DOUBLE_EQ(erfc_result, erf_result);
}

// Test that erfc_inv(0.5) gives a positive value
// erfc_inv(0.5) = erf_inv(0.5) > 0 since erf is monotonically increasing and erf(0)=0
TEST(ErfcInvTest_988, ErfcInvOfHalf_988) {
    double result = erfc_inv(0.5);
    EXPECT_GT(result, 0.0);
}

// Test values near 1.0: erfc_inv should be close to 0
TEST(ErfcInvTest_988, ErfcInvNearOne_988) {
    double result = erfc_inv(0.99);
    // erfc_inv(0.99) = erf_inv(0.01), which should be small and positive
    EXPECT_GT(result, 0.0);
    EXPECT_LT(result, 0.1);  // Should be a small positive number
}

// Test value greater than 1: erfc_inv(1.5) = erf_inv(-0.5) should be negative
TEST(ErfcInvTest_988, ErfcInvOfOnePointFive_988) {
    double result = erfc_inv(1.5);
    EXPECT_LT(result, 0.0);
}

// Test that erfc_inv(x) and erfc_inv(2-x) are negatives of each other
// erfc_inv(x) = erf_inv(1-x), erfc_inv(2-x) = erf_inv(x-1) = -erf_inv(1-x)
TEST(ErfcInvTest_988, ErfcInvSymmetryAroundOne_988) {
    double x = 0.3;
    double result1 = erfc_inv(x);
    double result2 = erfc_inv(2.0 - x);
    EXPECT_NEAR(result1, -result2, 1e-10);
}

// Test another symmetry point
TEST(ErfcInvTest_988, ErfcInvSymmetryAroundOneAnother_988) {
    double x = 0.7;
    double result1 = erfc_inv(x);
    double result2 = erfc_inv(2.0 - x);
    EXPECT_NEAR(result1, -result2, 1e-10);
}

// Verify known numerical value: erfc(1) ≈ 0.1573, so erfc_inv(0.1573) ≈ 1.0
TEST(ErfcInvTest_988, ErfcInvKnownValue_988) {
    double erfc_of_1 = std::erfc(1.0);  // ≈ 0.15729920705
    double result = erfc_inv(erfc_of_1);
    EXPECT_NEAR(result, 1.0, 1e-4);
}

// Test with a value close to 0 (but not 0)
TEST(ErfcInvTest_988, ErfcInvSmallPositive_988) {
    double result = erfc_inv(0.01);
    // erfc_inv(0.01) = erf_inv(0.99) which should be a large positive number
    EXPECT_GT(result, 1.0);
}

// Test with a value close to 2 (but not 2)
TEST(ErfcInvTest_988, ErfcInvNearTwo_988) {
    double result = erfc_inv(1.99);
    // erfc_inv(1.99) = erf_inv(-0.99) which should be a large negative number
    EXPECT_LT(result, -1.0);
}
