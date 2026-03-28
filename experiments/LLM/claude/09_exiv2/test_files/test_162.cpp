#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<Rational>
// ============================================================

class ValueTypeRationalTest_162 : public ::testing::Test {
protected:
    using RationalValue = ValueType<Rational>;
};

TEST_F(ValueTypeRationalTest_162, DefaultConstructor_162) {
    RationalValue val;
    EXPECT_EQ(val.count(), 0u);
    EXPECT_EQ(val.size(), 0u);
}

TEST_F(ValueTypeRationalTest_162, ConstructWithSingleValue_162) {
    Rational r(1, 2);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.value_.size(), 1u);
    EXPECT_EQ(val.value_[0].first, 1);
    EXPECT_EQ(val.value_[0].second, 2);
}

TEST_F(ValueTypeRationalTest_162, ToUint32_NormalCase_162) {
    Rational r(10, 2);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toUint32(0), 5u);
}

TEST_F(ValueTypeRationalTest_162, ToUint32_ZeroDenominator_162) {
    Rational r(10, 0);
    RationalValue val(r, signedRational);
    // Division by zero case - behavior depends on implementation
    // Just verify it doesn't crash and returns some value
    val.toUint32(0);
}

TEST_F(ValueTypeRationalTest_162, ToUint32_ZeroNumerator_162) {
    Rational r(0, 5);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toUint32(0), 0u);
}

TEST_F(ValueTypeRationalTest_162, ToUint32_NegativeRational_162) {
    Rational r(-10, 2);
    RationalValue val(r, signedRational);
    // Negative value cast to uint32 - implementation defined but should not crash
    val.toUint32(0);
}

TEST_F(ValueTypeRationalTest_162, ToInt64_NormalCase_162) {
    Rational r(10, 2);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toInt64(0), 5);
}

TEST_F(ValueTypeRationalTest_162, ToInt64_NegativeRational_162) {
    Rational r(-10, 2);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toInt64(0), -5);
}

TEST_F(ValueTypeRationalTest_162, ToFloat_NormalCase_162) {
    Rational r(1, 4);
    RationalValue val(r, signedRational);
    EXPECT_FLOAT_EQ(val.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_162, ToRational_ReturnsSameRational_162) {
    Rational r(3, 7);
    RationalValue val(r, signedRational);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

TEST_F(ValueTypeRationalTest_162, Count_MultipleValues_162) {
    RationalValue val;
    val.value_.push_back(Rational(1, 2));
    val.value_.push_back(Rational(3, 4));
    val.value_.push_back(Rational(5, 6));
    EXPECT_EQ(val.count(), 3u);
}

TEST_F(ValueTypeRationalTest_162, ToUint32_MultipleValues_SecondElement_162) {
    RationalValue val;
    val.value_.push_back(Rational(10, 2));
    val.value_.push_back(Rational(20, 4));
    EXPECT_EQ(val.toUint32(0), 5u);
    EXPECT_EQ(val.toUint32(1), 5u);
}

TEST_F(ValueTypeRationalTest_162, ToString_NormalCase_162) {
    Rational r(1, 2);
    RationalValue val(r, signedRational);
    std::string str = val.toString(0);
    EXPECT_EQ(str, "1/2");
}

TEST_F(ValueTypeRationalTest_162, Write_OutputStream_162) {
    Rational r(3, 4);
    RationalValue val(r, signedRational);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "3/4");
}

TEST_F(ValueTypeRationalTest_162, CopyConstructor_162) {
    Rational r(7, 8);
    RationalValue val(r, signedRational);
    RationalValue copy(val);
    EXPECT_EQ(copy.count(), 1u);
    EXPECT_EQ(copy.toUint32(0), val.toUint32(0));
}

TEST_F(ValueTypeRationalTest_162, AssignmentOperator_162) {
    Rational r1(1, 2);
    Rational r2(3, 4);
    RationalValue val1(r1, signedRational);
    RationalValue val2(r2, signedRational);
    val1 = val2;
    EXPECT_EQ(val1.count(), 1u);
    EXPECT_EQ(val1.value_[0].first, 3);
    EXPECT_EQ(val1.value_[0].second, 4);
}

TEST_F(ValueTypeRationalTest_162, Clone_162) {
    Rational r(5, 6);
    RationalValue val(r, signedRational);
    auto cloned = val.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toUint32(0), val.toUint32(0));
}

TEST_F(ValueTypeRationalTest_162, ReadFromString_162) {
    RationalValue val;
    val.read("1/2 3/4 5/6");
    EXPECT_EQ(val.count(), 3u);
    EXPECT_EQ(val.value_[0], Rational(1, 2));
    EXPECT_EQ(val.value_[1], Rational(3, 4));
    EXPECT_EQ(val.value_[2], Rational(5, 6));
}

TEST_F(ValueTypeRationalTest_162, DataArea_Empty_162) {
    RationalValue val;
    EXPECT_EQ(val.sizeDataArea(), 0u);
}

TEST_F(ValueTypeRationalTest_162, SetDataArea_162) {
    RationalValue val;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    val.setDataArea(data, sizeof(data));
    EXPECT_EQ(val.sizeDataArea(), 4u);
    DataBuf buf = val.dataArea();
    EXPECT_EQ(buf.size(), 4u);
}

TEST_F(ValueTypeRationalTest_162, ReadFromBuffer_BigEndian_162) {
    // A Rational is two int32_t values. Let's create buffer for 1/2
    byte buf[8];
    // Big endian: numerator = 1
    buf[0] = 0; buf[1] = 0; buf[2] = 0; buf[3] = 1;
    // Big endian: denominator = 2
    buf[4] = 0; buf[5] = 0; buf[6] = 0; buf[7] = 2;
    
    RationalValue val;
    val.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.value_[0].first, 1);
    EXPECT_EQ(val.value_[0].second, 2);
}

TEST_F(ValueTypeRationalTest_162, ReadFromBuffer_LittleEndian_162) {
    byte buf[8];
    // Little endian: numerator = 1
    buf[0] = 1; buf[1] = 0; buf[2] = 0; buf[3] = 0;
    // Little endian: denominator = 2
    buf[4] = 2; buf[5] = 0; buf[6] = 0; buf[7] = 0;
    
    RationalValue val;
    val.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.value_[0].first, 1);
    EXPECT_EQ(val.value_[0].second, 2);
}

TEST_F(ValueTypeRationalTest_162, CopyToBuffer_BigEndian_162) {
    Rational r(1, 2);
    RationalValue val(r, signedRational);
    byte buf[8] = {};
    size_t copied = val.copy(buf, bigEndian);
    EXPECT_EQ(copied, 8u);
    // Verify big endian encoding
    EXPECT_EQ(buf[0], 0); EXPECT_EQ(buf[1], 0); EXPECT_EQ(buf[2], 0); EXPECT_EQ(buf[3], 1);
    EXPECT_EQ(buf[4], 0); EXPECT_EQ(buf[5], 0); EXPECT_EQ(buf[6], 0); EXPECT_EQ(buf[7], 2);
}

TEST_F(ValueTypeRationalTest_162, Size_SingleRational_162) {
    Rational r(1, 2);
    RationalValue val(r, signedRational);
    // Rational is two int32_t = 8 bytes
    EXPECT_EQ(val.size(), 8u);
}

TEST_F(ValueTypeRationalTest_162, Size_MultipleRationals_162) {
    RationalValue val;
    val.value_.push_back(Rational(1, 2));
    val.value_.push_back(Rational(3, 4));
    EXPECT_EQ(val.size(), 16u);
}

TEST_F(ValueTypeRationalTest_162, ToUint32_WholeNumber_162) {
    Rational r(42, 1);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toUint32(0), 42u);
}

TEST_F(ValueTypeRationalTest_162, ToUint32_FractionalResult_162) {
    Rational r(7, 3);
    RationalValue val(r, signedRational);
    // 7/3 = 2.333... truncated to 2
    EXPECT_EQ(val.toUint32(0), 2u);
}

TEST_F(ValueTypeRationalTest_162, ToInt64_WholeNumber_162) {
    Rational r(42, 1);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toInt64(0), 42);
}

TEST_F(ValueTypeRationalTest_162, ToFloat_ZeroDenominator_162) {
    Rational r(1, 0);
    RationalValue val(r, signedRational);
    // Should handle gracefully
    val.toFloat(0);
}

// ============================================================
// Tests for ValueType<URational>
// ============================================================

class ValueTypeURationalTest_162 : public ::testing::Test {
protected:
    using URationalValue = ValueType<URational>;
};

TEST_F(ValueTypeURationalTest_162, DefaultConstructor_162) {
    URationalValue val;
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(ValueTypeURationalTest_162, ToUint32_NormalCase_162) {
    URational r(10, 2);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toUint32(0), 5u);
}

TEST_F(ValueTypeURationalTest_162, ToInt64_NormalCase_162) {
    URational r(10, 2);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toInt64(0), 5);
}

TEST_F(ValueTypeURationalTest_162, ToFloat_NormalCase_162) {
    URational r(1, 4);
    URationalValue val(r, unsignedRational);
    EXPECT_FLOAT_EQ(val.toFloat(0), 0.25f);
}

TEST_F(ValueTypeURationalTest_162, ToRational_NormalCase_162) {
    URational r(3, 7);
    URationalValue val(r, unsignedRational);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

// ============================================================
// Tests for ValueType<float>
// ============================================================

class ValueTypeFloatTest_162 : public ::testing::Test {
protected:
    using FloatValue = ValueType<float>;
};

TEST_F(ValueTypeFloatTest_162, DefaultConstructor_162) {
    FloatValue val;
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(ValueTypeFloatTest_162, ConstructWithValue_162) {
    FloatValue val(3.14f, tiffFloat);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_FLOAT_EQ(val.toFloat(0), 3.14f);
}

TEST_F(ValueTypeFloatTest_162, ToUint32_NormalCase_162) {
    FloatValue val(42.7f, tiffFloat);
    EXPECT_EQ(val.toUint32(0), 42u);
}

TEST_F(ValueTypeFloatTest_162, ToInt64_NormalCase_162) {
    FloatValue val(-42.7f, tiffFloat);
    EXPECT_EQ(val.toInt64(0), -42);
}

TEST_F(ValueTypeFloatTest_162, ToRational_NormalCase_162) {
    FloatValue val(0.5f, tiffFloat);
    Rational r = val.toRational(0);
    // Should produce a rational close to 0.5
    if (r.second != 0) {
        float result = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(result, 0.5f, 0.001f);
    }
}

// ============================================================
// Tests for ValueType<double>
// ============================================================

class ValueTypeDoubleTest_162 : public ::testing::Test {
protected:
    using DoubleValue = ValueType<double>;
};

TEST_F(ValueTypeDoubleTest_162, DefaultConstructor_162) {
    DoubleValue val;
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_162, ConstructWithValue_162) {
    DoubleValue val(3.14159, tiffDouble);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_NEAR(val.toFloat(0), 3.14159f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_162, ToUint32_NormalCase_162) {
    DoubleValue val(99.9, tiffDouble);
    EXPECT_EQ(val.toUint32(0), 99u);
}

TEST_F(ValueTypeDoubleTest_162, ToInt64_NormalCase_162) {
    DoubleValue val(-99.9, tiffDouble);
    EXPECT_EQ(val.toInt64(0), -99);
}

TEST_F(ValueTypeDoubleTest_162, ToRational_NormalCase_162) {
    DoubleValue val(0.25, tiffDouble);
    Rational r = val.toRational(0);
    if (r.second != 0) {
        double result = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(result, 0.25, 0.001);
    }
}

// ============================================================
// Tests for ValueType with integer types (e.g., uint16_t)
// ============================================================

class ValueTypeUint16Test_162 : public ::testing::Test {
protected:
    using UShortValue = ValueType<uint16_t>;
};

TEST_F(ValueTypeUint16Test_162, DefaultConstructor_162) {
    UShortValue val;
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(ValueTypeUint16Test_162, ConstructWithValue_162) {
    UShortValue val(static_cast<uint16_t>(42), unsignedShort);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.toUint32(0), 42u);
}

TEST_F(ValueTypeUint16Test_162, ToInt64_162) {
    UShortValue val(static_cast<uint16_t>(1000), unsignedShort);
    EXPECT_EQ(val.toInt64(0), 1000);
}

TEST_F(ValueTypeUint16Test_162, ToFloat_162) {
    UShortValue val(static_cast<uint16_t>(255), unsignedShort);
    EXPECT_FLOAT_EQ(val.toFloat(0), 255.0f);
}

TEST_F(ValueTypeUint16Test_162, ReadFromString_162) {
    UShortValue val;
    val.read("10 20 30");
    EXPECT_EQ(val.count(), 3u);
    EXPECT_EQ(val.toUint32(0), 10u);
    EXPECT_EQ(val.toUint32(1), 20u);
    EXPECT_EQ(val.toUint32(2), 30u);
}

TEST_F(ValueTypeUint16Test_162, Write_MultipleValues_162) {
    UShortValue val;
    val.value_.push_back(10);
    val.value_.push_back(20);
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ(os.str(), "10 20");
}

TEST_F(ValueTypeUint16Test_162, Size_162) {
    UShortValue val;
    val.value_.push_back(1);
    val.value_.push_back(2);
    EXPECT_EQ(val.size(), 4u); // 2 * sizeof(uint16_t) = 4
}

TEST_F(ValueTypeUint16Test_162, CopyToBuffer_162) {
    UShortValue val(static_cast<uint16_t>(256), unsignedShort);
    byte buf[2] = {};
    size_t copied = val.copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    // Big endian: 256 = 0x0100
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// ============================================================
// Tests for ValueType<int32_t> (signed long)
// ============================================================

class ValueTypeInt32Test_162 : public ::testing::Test {
protected:
    using LongValue = ValueType<int32_t>;
};

TEST_F(ValueTypeInt32Test_162, ConstructWithValue_162) {
    LongValue val(static_cast<int32_t>(-100), signedLong);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.toInt64(0), -100);
}

TEST_F(ValueTypeInt32Test_162, ToRational_162) {
    LongValue val(static_cast<int32_t>(42), signedLong);
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeInt32Test_162, ToString_162) {
    LongValue val(static_cast<int32_t>(-50), signedLong);
    EXPECT_EQ(val.toString(0), "-50");
}

// ============================================================
// Tests for boundary conditions on index parameter
// ============================================================

class ValueTypeBoundaryTest_162 : public ::testing::Test {
protected:
    using RationalValue = ValueType<Rational>;
};

TEST_F(ValueTypeBoundaryTest_162, MultipleValuesAccessByIndex_162) {
    RationalValue val;
    val.value_.push_back(Rational(1, 1));
    val.value_.push_back(Rational(2, 1));
    val.value_.push_back(Rational(3, 1));
    EXPECT_EQ(val.toUint32(0), 1u);
    EXPECT_EQ(val.toUint32(1), 2u);
    EXPECT_EQ(val.toUint32(2), 3u);
}

TEST_F(ValueTypeBoundaryTest_162, ToStringMultipleValues_162) {
    RationalValue val;
    val.value_.push_back(Rational(1, 2));
    val.value_.push_back(Rational(3, 4));
    EXPECT_EQ(val.toString(0), "1/2");
    EXPECT_EQ(val.toString(1), "3/4");
}

TEST_F(ValueTypeBoundaryTest_162, ToUint32_LargeRational_162) {
    Rational r(1000000, 1);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toUint32(0), 1000000u);
}

TEST_F(ValueTypeBoundaryTest_162, ToUint32_UnitRational_162) {
    Rational r(1, 1);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toUint32(0), 1u);
}

TEST_F(ValueTypeBoundaryTest_162, EmptyValueCount_162) {
    RationalValue val;
    EXPECT_EQ(val.count(), 0u);
    EXPECT_EQ(val.size(), 0u);
}

// ============================================================
// Test for read/write roundtrip with buffer
// ============================================================

TEST(ValueTypeRoundtripTest_162, RationalRoundtrip_BigEndian_162) {
    using RationalValue = ValueType<Rational>;
    
    Rational r(123, 456);
    RationalValue original(r, signedRational);
    
    byte buf[8];
    size_t written = original.copy(buf, bigEndian);
    EXPECT_EQ(written, 8u);
    
    RationalValue restored;
    restored.read(buf, written, bigEndian);
    EXPECT_EQ(restored.count(), 1u);
    EXPECT_EQ(restored.value_[0].first, 123);
    EXPECT_EQ(restored.value_[0].second, 456);
}

TEST(ValueTypeRoundtripTest_162, RationalRoundtrip_LittleEndian_162) {
    using RationalValue = ValueType<Rational>;
    
    Rational r(-42, 100);
    RationalValue original(r, signedRational);
    
    byte buf[8];
    size_t written = original.copy(buf, littleEndian);
    EXPECT_EQ(written, 8u);
    
    RationalValue restored;
    restored.read(buf, written, littleEndian);
    EXPECT_EQ(restored.count(), 1u);
    EXPECT_EQ(restored.value_[0].first, -42);
    EXPECT_EQ(restored.value_[0].second, 100);
}
