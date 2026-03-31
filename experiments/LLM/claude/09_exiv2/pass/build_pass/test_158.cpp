#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cmath>
#include <limits>
#include <sstream>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<double>
// ============================================================

class ValueTypeDoubleTest_158 : public ::testing::Test {
protected:
    using DoubleValue = ValueType<double>;
};

TEST_F(ValueTypeDoubleTest_158, DefaultConstructor_158) {
    DoubleValue v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeDoubleTest_158, ConstructWithValue_158) {
    DoubleValue v(3.14, TypeId::tiffDouble);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_.size(), 1u);
    EXPECT_DOUBLE_EQ(v.value_[0], 3.14);
}

TEST_F(ValueTypeDoubleTest_158, CopyConstructor_158) {
    DoubleValue v1(2.718, TypeId::tiffDouble);
    DoubleValue v2(v1);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_DOUBLE_EQ(v2.value_[0], 2.718);
}

TEST_F(ValueTypeDoubleTest_158, AssignmentOperator_158) {
    DoubleValue v1(1.0, TypeId::tiffDouble);
    DoubleValue v2(2.0, TypeId::tiffDouble);
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_DOUBLE_EQ(v2.value_[0], 1.0);
}

TEST_F(ValueTypeDoubleTest_158, ToInt64_Positive_158) {
    DoubleValue v(42.7, TypeId::tiffDouble);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeDoubleTest_158, ToInt64_Negative_158) {
    DoubleValue v(-42.7, TypeId::tiffDouble);
    EXPECT_EQ(v.toInt64(0), -42);
}

TEST_F(ValueTypeDoubleTest_158, ToUint32_Positive_158) {
    DoubleValue v(42.9, TypeId::tiffDouble);
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeDoubleTest_158, ToUint32_Zero_158) {
    DoubleValue v(0.0, TypeId::tiffDouble);
    EXPECT_EQ(v.toUint32(0), 0u);
}

TEST_F(ValueTypeDoubleTest_158, ToFloat_158) {
    DoubleValue v(3.14, TypeId::tiffDouble);
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

TEST_F(ValueTypeDoubleTest_158, ToRational_158) {
    DoubleValue v(0.5, TypeId::tiffDouble);
    Rational r = v.toRational(0);
    // Check that the rational approximates the value
    EXPECT_NE(r.second, 0);
    double ratio = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(ratio, 0.5, 0.001);
}

TEST_F(ValueTypeDoubleTest_158, ToString_158) {
    DoubleValue v(1.5, TypeId::tiffDouble);
    std::string s = v.toString(0);
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTypeDoubleTest_158, WriteToStream_158) {
    DoubleValue v(2.5, TypeId::tiffDouble);
    std::ostringstream os;
    v.write(os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ValueTypeDoubleTest_158, ReadFromString_158) {
    DoubleValue v;
    v.read("1.5 2.5 3.5");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_DOUBLE_EQ(v.value_[0], 1.5);
    EXPECT_DOUBLE_EQ(v.value_[1], 2.5);
    EXPECT_DOUBLE_EQ(v.value_[2], 3.5);
}

TEST_F(ValueTypeDoubleTest_158, ReadFromBuf_158) {
    double val = 2.5;
    byte buf[sizeof(double)];
    std::memcpy(buf, &val, sizeof(double));
    DoubleValue v;
    v.read(buf, sizeof(double), littleEndian);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeDoubleTest_158, CopyToBuf_158) {
    DoubleValue v(5.0, TypeId::tiffDouble);
    byte buf[sizeof(double)];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, sizeof(double));
}

TEST_F(ValueTypeDoubleTest_158, Clone_158) {
    DoubleValue v(7.0, TypeId::tiffDouble);
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
}

TEST_F(ValueTypeDoubleTest_158, DataAreaInitiallyEmpty_158) {
    DoubleValue v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeDoubleTest_158, SetDataArea_158) {
    DoubleValue v;
    byte data[] = {0x01, 0x02, 0x03};
    v.setDataArea(data, 3);
    EXPECT_EQ(v.sizeDataArea(), 3u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 3u);
}

TEST_F(ValueTypeDoubleTest_158, MultipleValues_ToInt64_158) {
    DoubleValue v;
    v.read("10.1 20.2 30.3");
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeDoubleTest_158, MultipleValues_ToUint32_158) {
    DoubleValue v;
    v.read("10.9 20.1 30.5");
    EXPECT_EQ(v.toUint32(0), 10u);
    EXPECT_EQ(v.toUint32(1), 20u);
    EXPECT_EQ(v.toUint32(2), 30u);
}

// ============================================================
// Tests for ValueType<float>
// ============================================================

class ValueTypeFloatTest_158 : public ::testing::Test {
protected:
    using FloatValue = ValueType<float>;
};

TEST_F(ValueTypeFloatTest_158, DefaultConstructor_158) {
    FloatValue v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_158, ConstructWithValue_158) {
    FloatValue v(1.5f, TypeId::tiffFloat);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.value_[0], 1.5f);
}

TEST_F(ValueTypeFloatTest_158, ToInt64_158) {
    FloatValue v(42.7f, TypeId::tiffFloat);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeFloatTest_158, ToUint32_158) {
    FloatValue v(42.9f, TypeId::tiffFloat);
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeFloatTest_158, ToFloat_158) {
    FloatValue v(3.14f, TypeId::tiffFloat);
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

TEST_F(ValueTypeFloatTest_158, ToRational_158) {
    FloatValue v(0.25f, TypeId::tiffFloat);
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    float ratio = static_cast<float>(r.first) / r.second;
    EXPECT_NEAR(ratio, 0.25f, 0.001f);
}

TEST_F(ValueTypeFloatTest_158, ReadFromString_158) {
    FloatValue v;
    v.read("1.0 2.0");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_FLOAT_EQ(v.value_[0], 1.0f);
    EXPECT_FLOAT_EQ(v.value_[1], 2.0f);
}

TEST_F(ValueTypeFloatTest_158, ToInt64_Negative_158) {
    FloatValue v(-10.5f, TypeId::tiffFloat);
    EXPECT_EQ(v.toInt64(0), -10);
}

// ============================================================
// Tests for ValueType<Rational>
// ============================================================

class ValueTypeRationalTest_158 : public ::testing::Test {
protected:
    using RationalValue = ValueType<Rational>;
};

TEST_F(ValueTypeRationalTest_158, DefaultConstructor_158) {
    RationalValue v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_158, ConstructWithValue_158) {
    Rational r(1, 2);
    RationalValue v(r, TypeId::signedRational);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0].first, 1);
    EXPECT_EQ(v.value_[0].second, 2);
}

TEST_F(ValueTypeRationalTest_158, ToInt64_158) {
    Rational r(10, 3);
    RationalValue v(r, TypeId::signedRational);
    EXPECT_EQ(v.toInt64(0), 3);  // 10/3 = 3
}

TEST_F(ValueTypeRationalTest_158, ToUint32_158) {
    Rational r(7, 2);
    RationalValue v(r, TypeId::signedRational);
    EXPECT_EQ(v.toUint32(0), 3u);  // 7/2 = 3
}

TEST_F(ValueTypeRationalTest_158, ToFloat_158) {
    Rational r(1, 4);
    RationalValue v(r, TypeId::signedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_158, ToRational_158) {
    Rational r(3, 7);
    RationalValue v(r, TypeId::signedRational);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

TEST_F(ValueTypeRationalTest_158, ZeroDenominator_ToFloat_158) {
    Rational r(1, 0);
    RationalValue v(r, TypeId::signedRational);
    // Should handle zero denominator gracefully
    float f = v.toFloat(0);
    (void)f;  // Just check it doesn't crash
}

TEST_F(ValueTypeRationalTest_158, ZeroDenominator_ToInt64_158) {
    Rational r(1, 0);
    RationalValue v(r, TypeId::signedRational);
    // Should handle zero denominator gracefully
    int64_t i = v.toInt64(0);
    (void)i;
}

TEST_F(ValueTypeRationalTest_158, NegativeRational_158) {
    Rational r(-5, 2);
    RationalValue v(r, TypeId::signedRational);
    EXPECT_EQ(v.toInt64(0), -2);  // -5/2 = -2
    EXPECT_FLOAT_EQ(v.toFloat(0), -2.5f);
}

TEST_F(ValueTypeRationalTest_158, ReadFromString_158) {
    RationalValue v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.value_[0].first, 1);
    EXPECT_EQ(v.value_[0].second, 2);
    EXPECT_EQ(v.value_[1].first, 3);
    EXPECT_EQ(v.value_[1].second, 4);
}

TEST_F(ValueTypeRationalTest_158, CopyAndSize_158) {
    Rational r(1, 2);
    RationalValue v(r, TypeId::signedRational);
    EXPECT_EQ(v.size(), 8u);  // Rational is two int32_t = 8 bytes
    byte buf[8];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 8u);
}

// ============================================================
// Tests for ValueType<URational>
// ============================================================

class ValueTypeURationalTest_158 : public ::testing::Test {
protected:
    using URationalValue = ValueType<URational>;
};

TEST_F(ValueTypeURationalTest_158, DefaultConstructor_158) {
    URationalValue v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeURationalTest_158, ConstructWithValue_158) {
    URational r(3, 4);
    URationalValue v(r, TypeId::unsignedRational);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeURationalTest_158, ToInt64_158) {
    URational r(10, 3);
    URationalValue v(r, TypeId::unsignedRational);
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeURationalTest_158, ToUint32_158) {
    URational r(10, 3);
    URationalValue v(r, TypeId::unsignedRational);
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeURationalTest_158, ToFloat_158) {
    URational r(1, 8);
    URationalValue v(r, TypeId::unsignedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.125f);
}

TEST_F(ValueTypeURationalTest_158, ToRational_158) {
    URational r(5, 9);
    URationalValue v(r, TypeId::unsignedRational);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 9);
}

TEST_F(ValueTypeURationalTest_158, ZeroDenominator_158) {
    URational r(1, 0);
    URationalValue v(r, TypeId::unsignedRational);
    // Should handle gracefully
    float f = v.toFloat(0);
    (void)f;
}

// ============================================================
// Tests for ValueType<uint16_t> (unsigned short)
// ============================================================

class ValueTypeUint16Test_158 : public ::testing::Test {
protected:
    using Uint16Value = ValueType<uint16_t>;
};

TEST_F(ValueTypeUint16Test_158, DefaultConstructor_158) {
    Uint16Value v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUint16Test_158, ConstructWithValue_158) {
    Uint16Value v(42, TypeId::unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 42);
}

TEST_F(ValueTypeUint16Test_158, ToInt64_158) {
    Uint16Value v(1000, TypeId::unsignedShort);
    EXPECT_EQ(v.toInt64(0), 1000);
}

TEST_F(ValueTypeUint16Test_158, ToUint32_158) {
    Uint16Value v(65535, TypeId::unsignedShort);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUint16Test_158, ToFloat_158) {
    Uint16Value v(100, TypeId::unsignedShort);
    EXPECT_FLOAT_EQ(v.toFloat(0), 100.0f);
}

TEST_F(ValueTypeUint16Test_158, ToRational_158) {
    Uint16Value v(5, TypeId::unsignedShort);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUint16Test_158, ReadFromString_158) {
    Uint16Value v;
    v.read("10 20 30");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.value_[0], 10);
    EXPECT_EQ(v.value_[1], 20);
    EXPECT_EQ(v.value_[2], 30);
}

TEST_F(ValueTypeUint16Test_158, ReadFromBuf_158) {
    uint16_t val = 0x1234;
    byte buf[2];
    std::memcpy(buf, &val, 2);
    Uint16Value v;
    v.read(buf, 2, littleEndian);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeUint16Test_158, Size_158) {
    Uint16Value v;
    v.read("10 20 30");
    EXPECT_EQ(v.size(), 6u);  // 3 * sizeof(uint16_t)
}

TEST_F(ValueTypeUint16Test_158, Write_158) {
    Uint16Value v(42, TypeId::unsignedShort);
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "42");
}

TEST_F(ValueTypeUint16Test_158, MultipleValuesWrite_158) {
    Uint16Value v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for ValueType<int16_t> (signed short)
// ============================================================

class ValueTypeInt16Test_158 : public ::testing::Test {
protected:
    using Int16Value = ValueType<int16_t>;
};

TEST_F(ValueTypeInt16Test_158, NegativeValue_158) {
    Int16Value v(-100, TypeId::signedShort);
    EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeInt16Test_158, ToFloat_Negative_158) {
    Int16Value v(-50, TypeId::signedShort);
    EXPECT_FLOAT_EQ(v.toFloat(0), -50.0f);
}

// ============================================================
// Tests for ValueType<uint32_t>
// ============================================================

class ValueTypeUint32Test_158 : public ::testing::Test {
protected:
    using Uint32Value = ValueType<uint32_t>;
};

TEST_F(ValueTypeUint32Test_158, DefaultConstructor_158) {
    Uint32Value v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUint32Test_158, ConstructWithValue_158) {
    Uint32Value v(123456u, TypeId::unsignedLong);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.value_[0], 123456u);
}

TEST_F(ValueTypeUint32Test_158, ToInt64_158) {
    Uint32Value v(4000000000u, TypeId::unsignedLong);
    EXPECT_EQ(v.toInt64(0), 4000000000LL);
}

TEST_F(ValueTypeUint32Test_158, ToUint32_158) {
    Uint32Value v(4294967295u, TypeId::unsignedLong);
    EXPECT_EQ(v.toUint32(0), 4294967295u);
}

// ============================================================
// Tests for ValueType<int32_t>
// ============================================================

class ValueTypeInt32Test_158 : public ::testing::Test {
protected:
    using Int32Value = ValueType<int32_t>;
};

TEST_F(ValueTypeInt32Test_158, NegativeValue_158) {
    Int32Value v(-100000, TypeId::signedLong);
    EXPECT_EQ(v.toInt64(0), -100000);
}

// ============================================================
// Boundary and edge case tests
// ============================================================

class ValueTypeBoundaryTest_158 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_158, DoubleMaxValue_ToUint32_158) {
    ValueType<double> v(static_cast<double>(std::numeric_limits<uint32_t>::max()), TypeId::tiffDouble);
    // Just verify it doesn't crash
    uint32_t result = v.toUint32(0);
    (void)result;
}

TEST_F(ValueTypeBoundaryTest_158, DoubleNegativeValue_ToUint32_158) {
    ValueType<double> v(-1.0, TypeId::tiffDouble);
    // Behavior for negative to unsigned is implementation-defined; just check no crash
    uint32_t result = v.toUint32(0);
    (void)result;
}

TEST_F(ValueTypeBoundaryTest_158, DoubleZero_ToInt64_158) {
    ValueType<double> v(0.0, TypeId::tiffDouble);
    EXPECT_EQ(v.toInt64(0), 0);
}

TEST_F(ValueTypeBoundaryTest_158, FloatMaxValue_ToUint32_158) {
    ValueType<float> v(std::numeric_limits<float>::max(), TypeId::tiffFloat);
    uint32_t result = v.toUint32(0);
    (void)result;
}

TEST_F(ValueTypeBoundaryTest_158, EmptyReadString_158) {
    ValueType<double> v;
    v.read("");
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_158, SingleValueCount_158) {
    ValueType<double> v(1.0, TypeId::tiffDouble);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeBoundaryTest_158, DataAreaEmpty_158) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

TEST_F(ValueTypeBoundaryTest_158, SetAndRetrieveDataArea_158) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    v.setDataArea(data, 4);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

TEST_F(ValueTypeBoundaryTest_158, RationalLargeNumerator_158) {
    Rational r(1000000, 1);
    ValueType<Rational> v(r, TypeId::signedRational);
    EXPECT_EQ(v.toInt64(0), 1000000);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1000000.0f);
}

TEST_F(ValueTypeBoundaryTest_158, URationalZeroNumerator_158) {
    URational r(0, 100);
    ValueType<URational> v(r, TypeId::unsignedRational);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.0f);
}

TEST_F(ValueTypeBoundaryTest_158, DoubleToRationalInteger_158) {
    ValueType<double> v(5.0, TypeId::tiffDouble);
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    double ratio = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(ratio, 5.0, 0.001);
}

TEST_F(ValueTypeBoundaryTest_158, FloatToRationalNegative_158) {
    ValueType<float> v(-0.5f, TypeId::tiffFloat);
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    float ratio = static_cast<float>(r.first) / r.second;
    EXPECT_NEAR(ratio, -0.5f, 0.001f);
}

// Test clone preserves multiple values
TEST_F(ValueTypeBoundaryTest_158, ClonePreservesValues_158) {
    ValueType<double> v;
    v.read("1.1 2.2 3.3");
    auto cloned = v.clone();
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_FLOAT_EQ(cloned->toFloat(0), 1.1f);
    EXPECT_FLOAT_EQ(cloned->toFloat(1), 2.2f);
    EXPECT_FLOAT_EQ(cloned->toFloat(2), 3.3f);
}

// Test copy and read round-trip
TEST_F(ValueTypeBoundaryTest_158, CopyReadRoundTrip_Uint16_158) {
    ValueType<uint16_t> v1;
    v1.read("100 200 300");
    
    byte buf[6];
    size_t copied = v1.copy(buf, littleEndian);
    EXPECT_EQ(copied, 6u);
    
    ValueType<uint16_t> v2;
    v2.read(buf, 6, littleEndian);
    EXPECT_EQ(v2.count(), 3u);
    EXPECT_EQ(v2.value_[0], 100);
    EXPECT_EQ(v2.value_[1], 200);
    EXPECT_EQ(v2.value_[2], 300);
}

TEST_F(ValueTypeBoundaryTest_158, ToString_DoubleMultipleValues_158) {
    ValueType<double> v;
    v.read("1.5 2.5");
    std::string s0 = v.toString(0);
    std::string s1 = v.toString(1);
    EXPECT_FALSE(s0.empty());
    EXPECT_FALSE(s1.empty());
}
