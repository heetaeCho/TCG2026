#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<URational>::toUint32 (the explicit specialization)
// and related ValueType functionality
// ============================================================

class ValueTypeURationalTest_164 : public ::testing::Test {
protected:
    using URationalValue = ValueType<URational>;
};

// --- Normal operation tests ---

TEST_F(ValueTypeURationalTest_164, ToUint32_SimpleRational_164) {
    URational r(10, 2);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toUint32(0), 5u);
}

TEST_F(ValueTypeURationalTest_164, ToUint32_WholeNumber_164) {
    URational r(42, 1);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toUint32(0), 42u);
}

TEST_F(ValueTypeURationalTest_164, ToUint32_Zero_164) {
    URational r(0, 1);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toUint32(0), 0u);
}

TEST_F(ValueTypeURationalTest_164, ToUint32_LargeValues_164) {
    URational r(1000000, 1);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toUint32(0), 1000000u);
}

TEST_F(ValueTypeURationalTest_164, ToUint32_FractionalTruncation_164) {
    URational r(7, 2);  // 3.5
    URationalValue val(r, unsignedRational);
    // Integer conversion should truncate or round
    uint32_t result = val.toUint32(0);
    EXPECT_TRUE(result == 3u || result == 4u);  // depends on implementation
}

TEST_F(ValueTypeURationalTest_164, ToUint32_MultipleValues_164) {
    URationalValue val(unsignedRational);
    val.value_.push_back(URational(10, 2));
    val.value_.push_back(URational(20, 4));
    val.value_.push_back(URational(99, 3));
    EXPECT_EQ(val.toUint32(0), 5u);
    EXPECT_EQ(val.toUint32(1), 5u);
    EXPECT_EQ(val.toUint32(2), 33u);
}

TEST_F(ValueTypeURationalTest_164, ToUint32_DenominatorOne_164) {
    URational r(255, 1);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toUint32(0), 255u);
}

// --- Boundary condition tests ---

TEST_F(ValueTypeURationalTest_164, ToUint32_ZeroDenominator_164) {
    URational r(10, 0);
    URationalValue val(r, unsignedRational);
    // Division by zero case - should handle gracefully
    // Just ensure it doesn't crash; the actual return value is implementation-defined
    EXPECT_NO_THROW(val.toUint32(0));
}

TEST_F(ValueTypeURationalTest_164, ToUint32_BothZero_164) {
    URational r(0, 0);
    URationalValue val(r, unsignedRational);
    EXPECT_NO_THROW(val.toUint32(0));
}

TEST_F(ValueTypeURationalTest_164, ToUint32_MaxUint32Numerator_164) {
    URational r(UINT32_MAX, 1);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toUint32(0), UINT32_MAX);
}

TEST_F(ValueTypeURationalTest_164, ToUint32_LargeNumeratorLargeDenominator_164) {
    URational r(UINT32_MAX, UINT32_MAX);
    URationalValue val(r, unsignedRational);
    EXPECT_EQ(val.toUint32(0), 1u);
}

// --- Exception / error cases ---

TEST_F(ValueTypeURationalTest_164, ToUint32_OutOfRangeIndex_164) {
    URational r(10, 1);
    URationalValue val(r, unsignedRational);
    // Accessing index beyond count should throw
    EXPECT_THROW(val.toUint32(1), std::out_of_range);
}

TEST_F(ValueTypeURationalTest_164, ToUint32_EmptyValue_164) {
    URationalValue val(unsignedRational);
    // No values, index 0 should throw
    EXPECT_THROW(val.toUint32(0), std::out_of_range);
}

// ============================================================
// Tests for other ValueType methods (count, size, read, copy, etc.)
// ============================================================

class ValueTypeIntegralTest_164 : public ::testing::Test {
protected:
    using UShortValue = ValueType<uint16_t>;
    using ULongValue = ValueType<uint32_t>;
};

TEST_F(ValueTypeIntegralTest_164, DefaultConstructor_EmptyCount_164) {
    UShortValue val;
    EXPECT_EQ(val.count(), 0u);
}

TEST_F(ValueTypeIntegralTest_164, SingleValueConstructor_CountIsOne_164) {
    UShortValue val(uint16_t(42), unsignedShort);
    EXPECT_EQ(val.count(), 1u);
}

TEST_F(ValueTypeIntegralTest_164, ReadFromString_164) {
    UShortValue val;
    val.read("1 2 3 4 5");
    EXPECT_EQ(val.count(), 5u);
    EXPECT_EQ(val.toUint32(0), 1u);
    EXPECT_EQ(val.toUint32(4), 5u);
}

TEST_F(ValueTypeIntegralTest_164, CopyConstructor_164) {
    UShortValue val1(uint16_t(99), unsignedShort);
    UShortValue val2(val1);
    EXPECT_EQ(val2.count(), 1u);
    EXPECT_EQ(val2.toUint32(0), 99u);
}

TEST_F(ValueTypeIntegralTest_164, AssignmentOperator_164) {
    UShortValue val1(uint16_t(55), unsignedShort);
    UShortValue val2;
    val2 = val1;
    EXPECT_EQ(val2.count(), 1u);
    EXPECT_EQ(val2.toUint32(0), 55u);
}

TEST_F(ValueTypeIntegralTest_164, Clone_164) {
    UShortValue val(uint16_t(77), unsignedShort);
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toUint32(0), 77u);
}

TEST_F(ValueTypeIntegralTest_164, WriteToOstream_164) {
    UShortValue val;
    val.value_.push_back(10);
    val.value_.push_back(20);
    std::ostringstream os;
    val.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
    // Should contain "10" and "20" in some form
    EXPECT_NE(result.find("10"), std::string::npos);
    EXPECT_NE(result.find("20"), std::string::npos);
}

TEST_F(ValueTypeIntegralTest_164, ToString_164) {
    UShortValue val(uint16_t(123), unsignedShort);
    std::string s = val.toString(0);
    EXPECT_EQ(s, "123");
}

TEST_F(ValueTypeIntegralTest_164, Size_SingleUShort_164) {
    UShortValue val(uint16_t(1), unsignedShort);
    EXPECT_EQ(val.size(), 2u);  // uint16_t is 2 bytes
}

TEST_F(ValueTypeIntegralTest_164, Size_SingleULong_164) {
    ULongValue val(uint32_t(1), unsignedLong);
    EXPECT_EQ(val.size(), 4u);  // uint32_t is 4 bytes
}

TEST_F(ValueTypeIntegralTest_164, ReadFromBuffer_UShort_164) {
    byte buf[4];
    // Little-endian 0x0001 = 1, 0x0002 = 2
    buf[0] = 0x01; buf[1] = 0x00;
    buf[2] = 0x02; buf[3] = 0x00;
    UShortValue val;
    val.read(buf, 4, littleEndian);
    EXPECT_EQ(val.count(), 2u);
    EXPECT_EQ(val.toUint32(0), 1u);
    EXPECT_EQ(val.toUint32(1), 2u);
}

TEST_F(ValueTypeIntegralTest_164, ReadFromBuffer_BigEndian_164) {
    byte buf[4];
    buf[0] = 0x00; buf[1] = 0x01;
    buf[2] = 0x00; buf[3] = 0x02;
    UShortValue val;
    val.read(buf, 4, bigEndian);
    EXPECT_EQ(val.count(), 2u);
    EXPECT_EQ(val.toUint32(0), 1u);
    EXPECT_EQ(val.toUint32(1), 2u);
}

TEST_F(ValueTypeIntegralTest_164, CopyToBuffer_164) {
    UShortValue val;
    val.value_.push_back(1);
    val.value_.push_back(2);
    byte buf[4];
    std::memset(buf, 0, 4);
    size_t copied = val.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    // Verify the buffer content
    UShortValue val2;
    val2.read(buf, 4, littleEndian);
    EXPECT_EQ(val2.toUint32(0), 1u);
    EXPECT_EQ(val2.toUint32(1), 2u);
}

// ============================================================
// Tests for ValueType<Rational> specializations
// ============================================================

class ValueTypeRationalTest_164 : public ::testing::Test {
protected:
    using RationalValue = ValueType<Rational>;
};

TEST_F(ValueTypeRationalTest_164, ToInt64_SimplePositive_164) {
    Rational r(10, 2);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toInt64(0), 5);
}

TEST_F(ValueTypeRationalTest_164, ToInt64_Negative_164) {
    Rational r(-10, 2);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toInt64(0), -5);
}

TEST_F(ValueTypeRationalTest_164, ToUint32_PositiveRational_164) {
    Rational r(20, 4);
    RationalValue val(r, signedRational);
    EXPECT_EQ(val.toUint32(0), 5u);
}

TEST_F(ValueTypeRationalTest_164, ToFloat_164) {
    Rational r(1, 4);
    RationalValue val(r, signedRational);
    EXPECT_FLOAT_EQ(val.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_164, ToRational_Identity_164) {
    Rational r(3, 7);
    RationalValue val(r, signedRational);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

// ============================================================
// Tests for ValueType<float> specializations
// ============================================================

class ValueTypeFloatTest_164 : public ::testing::Test {
protected:
    using FloatValue = ValueType<float>;
};

TEST_F(ValueTypeFloatTest_164, ToInt64_164) {
    FloatValue val(3.7f, tiffFloat);
    int64_t result = val.toInt64(0);
    // Should truncate or round
    EXPECT_TRUE(result == 3 || result == 4);
}

TEST_F(ValueTypeFloatTest_164, ToUint32_164) {
    FloatValue val(5.9f, tiffFloat);
    uint32_t result = val.toUint32(0);
    EXPECT_TRUE(result == 5u || result == 6u);
}

TEST_F(ValueTypeFloatTest_164, ToFloat_Identity_164) {
    FloatValue val(2.5f, tiffFloat);
    EXPECT_FLOAT_EQ(val.toFloat(0), 2.5f);
}

TEST_F(ValueTypeFloatTest_164, ToRational_164) {
    FloatValue val(0.5f, tiffFloat);
    Rational r = val.toRational(0);
    // The rational should represent 0.5
    if (r.second != 0) {
        float ratio = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(ratio, 0.5f, 0.001f);
    }
}

// ============================================================
// Tests for ValueType<double> specializations
// ============================================================

class ValueTypeDoubleTest_164 : public ::testing::Test {
protected:
    using DoubleValue = ValueType<double>;
};

TEST_F(ValueTypeDoubleTest_164, ToInt64_164) {
    DoubleValue val(7.2, tiffDouble);
    int64_t result = val.toInt64(0);
    EXPECT_TRUE(result == 7 || result == 8);
}

TEST_F(ValueTypeDoubleTest_164, ToUint32_164) {
    DoubleValue val(12.8, tiffDouble);
    uint32_t result = val.toUint32(0);
    EXPECT_TRUE(result == 12u || result == 13u);
}

TEST_F(ValueTypeDoubleTest_164, ToFloat_164) {
    DoubleValue val(3.14, tiffDouble);
    EXPECT_NEAR(val.toFloat(0), 3.14f, 0.01f);
}

TEST_F(ValueTypeDoubleTest_164, ToRational_164) {
    DoubleValue val(0.25, tiffDouble);
    Rational r = val.toRational(0);
    if (r.second != 0) {
        double ratio = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(ratio, 0.25, 0.001);
    }
}

// ============================================================
// Tests for DataArea functionality
// ============================================================

TEST(ValueTypeDataAreaTest_164, SetAndGetDataArea_164) {
    ValueType<uint16_t> val;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = val.setDataArea(data, 4);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.sizeDataArea(), 4u);
    DataBuf buf = val.dataArea();
    EXPECT_EQ(buf.size(), 4u);
}

TEST(ValueTypeDataAreaTest_164, EmptyDataArea_164) {
    ValueType<uint16_t> val;
    EXPECT_EQ(val.sizeDataArea(), 0u);
}

// ============================================================
// Tests for URational toInt64
// ============================================================

TEST(ValueTypeURationalToInt64Test_164, SimpleConversion_164) {
    ValueType<URational> val(URational(100, 10), unsignedRational);
    EXPECT_EQ(val.toInt64(0), 10);
}

TEST(ValueTypeURationalToInt64Test_164, ZeroNumerator_164) {
    ValueType<URational> val(URational(0, 5), unsignedRational);
    EXPECT_EQ(val.toInt64(0), 0);
}

// ============================================================
// URational toFloat
// ============================================================

TEST(ValueTypeURationalToFloatTest_164, SimpleConversion_164) {
    ValueType<URational> val(URational(1, 4), unsignedRational);
    EXPECT_FLOAT_EQ(val.toFloat(0), 0.25f);
}

TEST(ValueTypeURationalToFloatTest_164, WholeNumber_164) {
    ValueType<URational> val(URational(8, 1), unsignedRational);
    EXPECT_FLOAT_EQ(val.toFloat(0), 8.0f);
}

// ============================================================
// URational toRational
// ============================================================

TEST(ValueTypeURationalToRationalTest_164, Conversion_164) {
    ValueType<URational> val(URational(3, 5), unsignedRational);
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 5);
}

// ============================================================
// Multiple element access and string operations
// ============================================================

TEST(ValueTypeURationalStringTest_164, ReadFromString_164) {
    ValueType<URational> val;
    val.read("3/4 5/6");
    EXPECT_EQ(val.count(), 2u);
}

TEST(ValueTypeURationalStringTest_164, ToString_164) {
    ValueType<URational> val(URational(3, 4), unsignedRational);
    std::string s = val.toString(0);
    EXPECT_EQ(s, "3/4");
}

TEST(ValueTypeRationalStringTest_164, ToString_164) {
    ValueType<Rational> val(Rational(-3, 4), signedRational);
    std::string s = val.toString(0);
    EXPECT_EQ(s, "-3/4");
}
