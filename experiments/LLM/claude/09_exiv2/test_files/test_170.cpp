#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// Test fixture for ValueType<URational> toRational tests
class ValueTypeURationalToRationalTest_170 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test that toRational returns correct values for a single URational element
TEST_F(ValueTypeURationalToRationalTest_170, SingleElement_ReturnsCorrectRational_170) {
    URational ur(1, 2);
    ValueType<URational> val(ur, unsignedRational);
    
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
    EXPECT_TRUE(val.ok());
}

// Test toRational with zero numerator
TEST_F(ValueTypeURationalToRationalTest_170, ZeroNumerator_ReturnsZeroRational_170) {
    URational ur(0, 5);
    ValueType<URational> val(ur, unsignedRational);
    
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 5);
    EXPECT_TRUE(val.ok());
}

// Test toRational with zero denominator
TEST_F(ValueTypeURationalToRationalTest_170, ZeroDenominator_ReturnsRationalWithZeroDenom_170) {
    URational ur(3, 0);
    ValueType<URational> val(ur, unsignedRational);
    
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 0);
    EXPECT_TRUE(val.ok());
}

// Test toRational with multiple elements, accessing different indices
TEST_F(ValueTypeURationalToRationalTest_170, MultipleElements_AccessByIndex_170) {
    ValueType<URational> val;
    val.value_.push_back(URational(1, 3));
    val.value_.push_back(URational(5, 7));
    val.value_.push_back(URational(11, 13));
    
    Rational r0 = val.toRational(0);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 3);
    EXPECT_TRUE(val.ok());
    
    Rational r1 = val.toRational(1);
    EXPECT_EQ(r1.first, 5);
    EXPECT_EQ(r1.second, 7);
    EXPECT_TRUE(val.ok());
    
    Rational r2 = val.toRational(2);
    EXPECT_EQ(r2.first, 11);
    EXPECT_EQ(r2.second, 13);
    EXPECT_TRUE(val.ok());
}

// Test toRational with out-of-range index throws exception
TEST_F(ValueTypeURationalToRationalTest_170, OutOfRangeIndex_ThrowsException_170) {
    URational ur(1, 2);
    ValueType<URational> val(ur, unsignedRational);
    
    EXPECT_THROW(val.toRational(1), std::out_of_range);
}

// Test toRational with empty value list throws exception
TEST_F(ValueTypeURationalToRationalTest_170, EmptyValueList_ThrowsException_170) {
    ValueType<URational> val;
    
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

// Test toRational with large URational values
TEST_F(ValueTypeURationalToRationalTest_170, LargeValues_ReturnsCorrectRational_170) {
    URational ur(4294967295u, 4294967295u);
    ValueType<URational> val(ur, unsignedRational);
    
    Rational r = val.toRational(0);
    // The unsigned values should be converted/assigned to the signed Rational type
    EXPECT_EQ(static_cast<uint32_t>(r.first), 4294967295u);
    EXPECT_EQ(static_cast<uint32_t>(r.second), 4294967295u);
    EXPECT_TRUE(val.ok());
}

// Test that ok_ is set to true after calling toRational
TEST_F(ValueTypeURationalToRationalTest_170, OkFlagSetToTrue_170) {
    URational ur(10, 20);
    ValueType<URational> val(ur, unsignedRational);
    
    val.toRational(0);
    EXPECT_TRUE(val.ok());
}

// Test toRational with URational where numerator equals denominator
TEST_F(ValueTypeURationalToRationalTest_170, NumeratorEqualsDenominator_170) {
    URational ur(42, 42);
    ValueType<URational> val(ur, unsignedRational);
    
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 42);
    EXPECT_TRUE(val.ok());
}

// Test toRational with unit rational (1/1)
TEST_F(ValueTypeURationalToRationalTest_170, UnitRational_170) {
    URational ur(1, 1);
    ValueType<URational> val(ur, unsignedRational);
    
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational after copy construction
TEST_F(ValueTypeURationalToRationalTest_170, CopyConstruction_PreservesValues_170) {
    ValueType<URational> val;
    val.value_.push_back(URational(3, 4));
    val.value_.push_back(URational(7, 8));
    
    ValueType<URational> val2(val);
    
    Rational r0 = val2.toRational(0);
    EXPECT_EQ(r0.first, 3);
    EXPECT_EQ(r0.second, 4);
    
    Rational r1 = val2.toRational(1);
    EXPECT_EQ(r1.first, 7);
    EXPECT_EQ(r1.second, 8);
    EXPECT_TRUE(val2.ok());
}

// Test toRational after assignment
TEST_F(ValueTypeURationalToRationalTest_170, Assignment_PreservesValues_170) {
    ValueType<URational> val;
    val.value_.push_back(URational(100, 200));
    
    ValueType<URational> val2;
    val2 = val;
    
    Rational r = val2.toRational(0);
    EXPECT_EQ(r.first, 100);
    EXPECT_EQ(r.second, 200);
    EXPECT_TRUE(val2.ok());
}

// Test count returns correct number of elements
TEST_F(ValueTypeURationalToRationalTest_170, CountMatchesElements_170) {
    ValueType<URational> val;
    EXPECT_EQ(val.count(), 0u);
    
    val.value_.push_back(URational(1, 2));
    EXPECT_EQ(val.count(), 1u);
    
    val.value_.push_back(URational(3, 4));
    EXPECT_EQ(val.count(), 2u);
}

// Test toFloat for URational
TEST_F(ValueTypeURationalToRationalTest_170, ToFloat_ReturnsCorrectValue_170) {
    URational ur(1, 4);
    ValueType<URational> val(ur, unsignedRational);
    
    float f = val.toFloat(0);
    EXPECT_FLOAT_EQ(f, 0.25f);
}

// Test toInt64 for URational
TEST_F(ValueTypeURationalToRationalTest_170, ToInt64_ReturnsCorrectValue_170) {
    URational ur(10, 3);
    ValueType<URational> val(ur, unsignedRational);
    
    int64_t i = val.toInt64(0);
    EXPECT_EQ(i, 3);
}

// Test toUint32 for URational
TEST_F(ValueTypeURationalToRationalTest_170, ToUint32_ReturnsCorrectValue_170) {
    URational ur(10, 3);
    ValueType<URational> val(ur, unsignedRational);
    
    uint32_t u = val.toUint32(0);
    EXPECT_EQ(u, 3u);
}

// Test both zero numerator and denominator
TEST_F(ValueTypeURationalToRationalTest_170, BothZero_170) {
    URational ur(0, 0);
    ValueType<URational> val(ur, unsignedRational);
    
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 0);
    EXPECT_TRUE(val.ok());
}

// Test typeId returns correct type
TEST_F(ValueTypeURationalToRationalTest_170, TypeIdIsCorrect_170) {
    ValueType<URational> val;
    EXPECT_EQ(val.typeId(), unsignedRational);
}

// Test clone preserves toRational behavior
TEST_F(ValueTypeURationalToRationalTest_170, ClonePreserves_ToRational_170) {
    ValueType<URational> val;
    val.value_.push_back(URational(55, 100));
    
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    
    Rational r = cloned->toRational(0);
    EXPECT_EQ(r.first, 55);
    EXPECT_EQ(r.second, 100);
}
