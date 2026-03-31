#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <stdexcept>

using namespace Exiv2;

// Type aliases for convenience
using URationalValue = ValueType<URational>;
using RationalValue = ValueType<Rational>;

class ValueTypeURationalToFloat_167 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test normal URational toFloat with valid denominator
TEST_F(ValueTypeURationalToFloat_167, NormalURational_ReturnsCorrectFloat_167) {
    URationalValue val(URational(1, 2), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.5f);
    EXPECT_TRUE(val.ok());
}

// Test URational toFloat with denominator of zero
TEST_F(ValueTypeURationalToFloat_167, ZeroDenominator_ReturnsZeroAndSetsOkFalse_167) {
    URationalValue val(URational(5, 0), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
    EXPECT_FALSE(val.ok());
}

// Test URational toFloat with numerator of zero
TEST_F(ValueTypeURationalToFloat_167, ZeroNumerator_ReturnsZero_167) {
    URationalValue val(URational(0, 100), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
    EXPECT_TRUE(val.ok());
}

// Test URational toFloat with equal numerator and denominator
TEST_F(ValueTypeURationalToFloat_167, EqualNumeratorDenominator_ReturnsOne_167) {
    URationalValue val(URational(7, 7), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 1.0f);
    EXPECT_TRUE(val.ok());
}

// Test URational toFloat with large values
TEST_F(ValueTypeURationalToFloat_167, LargeValues_ReturnsCorrectFloat_167) {
    URationalValue val(URational(1000000, 3), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 1000000.0f / 3.0f, 1.0f);
    EXPECT_TRUE(val.ok());
}

// Test URational toFloat accessing out of bounds index throws
TEST_F(ValueTypeURationalToFloat_167, OutOfBoundsIndex_Throws_167) {
    URationalValue val(URational(1, 2), unsignedRational);
    EXPECT_THROW(val.toFloat(1), std::out_of_range);
}

// Test URational toFloat with multiple values, accessing second element
TEST_F(ValueTypeURationalToFloat_167, MultipleValues_AccessSecondElement_167) {
    URationalValue val(URational(1, 4), unsignedRational);
    val.value_.push_back(URational(3, 4));
    
    float result0 = val.toFloat(0);
    EXPECT_FLOAT_EQ(result0, 0.25f);
    EXPECT_TRUE(val.ok());
    
    float result1 = val.toFloat(1);
    EXPECT_FLOAT_EQ(result1, 0.75f);
    EXPECT_TRUE(val.ok());
}

// Test URational toFloat with denominator of 1
TEST_F(ValueTypeURationalToFloat_167, DenominatorOne_ReturnsNumeratorAsFloat_167) {
    URationalValue val(URational(42, 1), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 42.0f);
    EXPECT_TRUE(val.ok());
}

// Test URational toFloat where numerator > denominator
TEST_F(ValueTypeURationalToFloat_167, NumeratorGreaterThanDenominator_167) {
    URationalValue val(URational(10, 3), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 10.0f / 3.0f, 0.0001f);
    EXPECT_TRUE(val.ok());
}

// Test that ok_ is properly set after zero denominator, then valid call
TEST_F(ValueTypeURationalToFloat_167, OkResetAfterZeroDenominator_167) {
    URationalValue val(URational(5, 0), unsignedRational);
    val.value_.push_back(URational(5, 2));
    
    // First call with zero denominator
    float result0 = val.toFloat(0);
    EXPECT_FLOAT_EQ(result0, 0.0f);
    EXPECT_FALSE(val.ok());
    
    // Second call with valid denominator should set ok_ to true
    float result1 = val.toFloat(1);
    EXPECT_FLOAT_EQ(result1, 2.5f);
    EXPECT_TRUE(val.ok());
}

// Test URational toFloat with max uint32_t values
TEST_F(ValueTypeURationalToFloat_167, MaxUint32Values_167) {
    uint32_t maxVal = std::numeric_limits<uint32_t>::max();
    URationalValue val(URational(maxVal, maxVal), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 1.0f);
    EXPECT_TRUE(val.ok());
}

// Test URational toFloat with numerator 1 and large denominator
TEST_F(ValueTypeURationalToFloat_167, SmallFraction_167) {
    URationalValue val(URational(1, 1000000), unsignedRational);
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 1.0f / 1000000.0f, 1e-10f);
    EXPECT_TRUE(val.ok());
}

// Test Rational (signed) toFloat for comparison/context
class ValueTypeRationalToFloat_167 : public ::testing::Test {};

TEST_F(ValueTypeRationalToFloat_167, NegativeNumerator_ReturnsNegativeFloat_167) {
    RationalValue val(Rational(-1, 2), signedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, -0.5f);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeRationalToFloat_167, ZeroDenominator_ReturnsZeroAndOkFalse_167) {
    RationalValue val(Rational(5, 0), signedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
    EXPECT_FALSE(val.ok());
}

TEST_F(ValueTypeRationalToFloat_167, BothNegative_ReturnsPositive_167) {
    RationalValue val(Rational(-3, -4), signedRational);
    float result = val.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.75f);
    EXPECT_TRUE(val.ok());
}

// Test empty value list - toFloat should throw on access
TEST_F(ValueTypeURationalToFloat_167, EmptyValueList_Throws_167) {
    URationalValue val;
    EXPECT_THROW(val.toFloat(0), std::out_of_range);
}

// Test toFloat with default constructor and manually pushed values
TEST_F(ValueTypeURationalToFloat_167, DefaultConstructorWithPushedValues_167) {
    URationalValue val;
    val.value_.push_back(URational(22, 7));
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 22.0f / 7.0f, 0.001f);
    EXPECT_TRUE(val.ok());
}
