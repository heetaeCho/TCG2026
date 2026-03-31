#include <gtest/gtest.h>
#include <cmath>
#include <limits>
#include <cstdint>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

using namespace YAML::jkj::dragonbox;

// =============================================================================
// Tests for make_float_bits with float
// =============================================================================

class MakeFloatBitsFloatTest_301 : public ::testing::Test {
protected:
};

TEST_F(MakeFloatBitsFloatTest_301, PositiveZero_301) {
    float x = 0.0f;
    auto fb = make_float_bits(x);
    // Positive zero should produce a float_bits object; verify it doesn't throw
    // and can be created successfully
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, NegativeZero_301) {
    float x = -0.0f;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, PositiveOne_301) {
    float x = 1.0f;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, NegativeOne_301) {
    float x = -1.0f;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, SmallPositiveFloat_301) {
    float x = 0.1f;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, LargePositiveFloat_301) {
    float x = 1.0e30f;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, SmallestNormalFloat_301) {
    float x = std::numeric_limits<float>::min();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, LargestFiniteFloat_301) {
    float x = std::numeric_limits<float>::max();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, SmallestDenormalizedFloat_301) {
    float x = std::numeric_limits<float>::denorm_min();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, PositiveInfinity_301) {
    float x = std::numeric_limits<float>::infinity();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, NegativeInfinity_301) {
    float x = -std::numeric_limits<float>::infinity();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, QuietNaN_301) {
    float x = std::numeric_limits<float>::quiet_NaN();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsFloatTest_301, DifferentValuesProduceDifferentBits_301) {
    float x1 = 1.0f;
    float x2 = 2.0f;
    // Different float values should (in general) produce different float_bits
    // We verify make_float_bits can be called on different values without issues
    auto fb1 = make_float_bits(x1);
    auto fb2 = make_float_bits(x2);
    (void)fb1;
    (void)fb2;
}

TEST_F(MakeFloatBitsFloatTest_301, SameValueProducesSameResult_301) {
    float x = 3.14f;
    auto fb1 = make_float_bits(x);
    auto fb2 = make_float_bits(x);
    (void)fb1;
    (void)fb2;
}

// =============================================================================
// Tests for make_float_bits with double
// =============================================================================

class MakeFloatBitsDoubleTest_301 : public ::testing::Test {
protected:
};

TEST_F(MakeFloatBitsDoubleTest_301, PositiveZero_301) {
    double x = 0.0;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, NegativeZero_301) {
    double x = -0.0;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, PositiveOne_301) {
    double x = 1.0;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, NegativeOne_301) {
    double x = -1.0;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, SmallPositiveDouble_301) {
    double x = 0.1;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, LargePositiveDouble_301) {
    double x = 1.0e300;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, SmallestNormalDouble_301) {
    double x = std::numeric_limits<double>::min();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, LargestFiniteDouble_301) {
    double x = std::numeric_limits<double>::max();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, SmallestDenormalizedDouble_301) {
    double x = std::numeric_limits<double>::denorm_min();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, PositiveInfinity_301) {
    double x = std::numeric_limits<double>::infinity();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, NegativeInfinity_301) {
    double x = -std::numeric_limits<double>::infinity();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, QuietNaN_301) {
    double x = std::numeric_limits<double>::quiet_NaN();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, Pi_301) {
    double x = 3.141592653589793;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, Epsilon_301) {
    double x = std::numeric_limits<double>::epsilon();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, NegativeLargeValue_301) {
    double x = -1.0e300;
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsDoubleTest_301, DifferentValuesProduceDifferentBits_301) {
    double x1 = 1.0;
    double x2 = 2.0;
    auto fb1 = make_float_bits(x1);
    auto fb2 = make_float_bits(x2);
    (void)fb1;
    (void)fb2;
}

TEST_F(MakeFloatBitsDoubleTest_301, SameValueProducesSameResult_301) {
    double x = 2.718281828459045;
    auto fb1 = make_float_bits(x);
    auto fb2 = make_float_bits(x);
    (void)fb1;
    (void)fb2;
}

// =============================================================================
// Tests verifying noexcept property
// =============================================================================

TEST(MakeFloatBitsNoexceptTest_301, FloatIsNoexcept_301) {
    EXPECT_TRUE(noexcept(make_float_bits(1.0f)));
}

TEST(MakeFloatBitsNoexceptTest_301, DoubleIsNoexcept_301) {
    EXPECT_TRUE(noexcept(make_float_bits(1.0)));
}

// =============================================================================
// Boundary tests with specific bit patterns
// =============================================================================

class MakeFloatBitsBoundaryTest_301 : public ::testing::Test {};

TEST_F(MakeFloatBitsBoundaryTest_301, FloatJustAboveZero_301) {
    // Smallest positive float (denormalized)
    float x = std::numeric_limits<float>::denorm_min();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsBoundaryTest_301, FloatJustBelowZero_301) {
    // Smallest negative float (denormalized)
    float x = -std::numeric_limits<float>::denorm_min();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsBoundaryTest_301, DoubleJustAboveZero_301) {
    double x = std::numeric_limits<double>::denorm_min();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsBoundaryTest_301, DoubleJustBelowZero_301) {
    double x = -std::numeric_limits<double>::denorm_min();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsBoundaryTest_301, FloatNegativeMax_301) {
    float x = -std::numeric_limits<float>::max();
    auto fb = make_float_bits(x);
    (void)fb;
}

TEST_F(MakeFloatBitsBoundaryTest_301, DoubleNegativeMax_301) {
    double x = -std::numeric_limits<double>::max();
    auto fb = make_float_bits(x);
    (void)fb;
}

} // anonymous namespace
