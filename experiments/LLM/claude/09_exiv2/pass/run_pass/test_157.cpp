#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cmath>
#include <limits>
#include <sstream>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<double>::toInt64
// ============================================================================

class ValueTypeDoubleTest_157 : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(ValueTypeDoubleTest_157, ToInt64_PositiveDouble_157) {
    DoubleValue val(3.7);
    EXPECT_EQ(3, val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_NegativeDouble_157) {
    DoubleValue val(-3.7);
    EXPECT_EQ(-3, val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_Zero_157) {
    DoubleValue val(0.0);
    EXPECT_EQ(0, val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_ExactInteger_157) {
    DoubleValue val(42.0);
    EXPECT_EQ(42, val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_NegativeExactInteger_157) {
    DoubleValue val(-42.0);
    EXPECT_EQ(-42, val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_SmallPositive_157) {
    DoubleValue val(0.1);
    EXPECT_EQ(0, val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_SmallNegative_157) {
    DoubleValue val(-0.1);
    EXPECT_EQ(0, val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_LargeDouble_157) {
    DoubleValue val(1e15);
    EXPECT_EQ(static_cast<int64_t>(1e15), val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_NegativeLargeDouble_157) {
    DoubleValue val(-1e15);
    EXPECT_EQ(static_cast<int64_t>(-1e15), val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_HalfValue_157) {
    DoubleValue val(0.5);
    EXPECT_EQ(0, val.toInt64(0));
}

TEST_F(ValueTypeDoubleTest_157, ToInt64_NegativeHalfValue_157) {
    DoubleValue val(-0.5);
    EXPECT_EQ(0, val.toInt64(0));
}

// ============================================================================
// Tests for ValueType<double>::toUint32
// ============================================================================

TEST_F(ValueTypeDoubleTest_157, ToUint32_PositiveDouble_157) {
    DoubleValue val(3.7);
    EXPECT_EQ(3u, val.toUint32(0));
}

TEST_F(ValueTypeDoubleTest_157, ToUint32_Zero_157) {
    DoubleValue val(0.0);
    EXPECT_EQ(0u, val.toUint32(0));
}

TEST_F(ValueTypeDoubleTest_157, ToUint32_ExactInteger_157) {
    DoubleValue val(100.0);
    EXPECT_EQ(100u, val.toUint32(0));
}

// ============================================================================
// Tests for ValueType<float>
// ============================================================================

class ValueTypeFloatTest_157 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_157, ToInt64_PositiveFloat_157) {
    FloatValue val(3.7f);
    EXPECT_EQ(3, val.toInt64(0));
}

TEST_F(ValueTypeFloatTest_157, ToInt64_NegativeFloat_157) {
    FloatValue val(-3.7f);
    EXPECT_EQ(-3, val.toInt64(0));
}

TEST_F(ValueTypeFloatTest_157, ToInt64_Zero_157) {
    FloatValue val(0.0f);
    EXPECT_EQ(0, val.toInt64(0));
}

TEST_F(ValueTypeFloatTest_157, ToUint32_PositiveFloat_157) {
    FloatValue val(5.9f);
    EXPECT_EQ(5u, val.toUint32(0));
}

TEST_F(ValueTypeFloatTest_157, ToUint32_Zero_157) {
    FloatValue val(0.0f);
    EXPECT_EQ(0u, val.toUint32(0));
}

TEST_F(ValueTypeFloatTest_157, ToFloat_Exact_157) {
    FloatValue val(3.14f);
    EXPECT_FLOAT_EQ(3.14f, val.toFloat(0));
}

TEST_F(ValueTypeFloatTest_157, ToRational_157) {
    FloatValue val(0.5f);
    Rational r = val.toRational(0);
    // The rational should approximate 0.5
    EXPECT_NEAR(0.5, static_cast<double>(r.first) / r.second, 1e-5);
}

// ============================================================================
// Tests for ValueType<Rational>
// ============================================================================

class ValueTypeRationalTest_157 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_157, ToInt64_SimpleRational_157) {
    Rational r(10, 3);
    RationalValue val(r);
    EXPECT_EQ(3, val.toInt64(0));
}

TEST_F(ValueTypeRationalTest_157, ToInt64_NegativeRational_157) {
    Rational r(-10, 3);
    RationalValue val(r);
    EXPECT_EQ(-3, val.toInt64(0));
}

TEST_F(ValueTypeRationalTest_157, ToInt64_ZeroNumerator_157) {
    Rational r(0, 1);
    RationalValue val(r);
    EXPECT_EQ(0, val.toInt64(0));
}

TEST_F(ValueTypeRationalTest_157, ToInt64_ExactDivision_157) {
    Rational r(10, 2);
    RationalValue val(r);
    EXPECT_EQ(5, val.toInt64(0));
}

TEST_F(ValueTypeRationalTest_157, ToUint32_SimpleRational_157) {
    Rational r(10, 3);
    RationalValue val(r);
    EXPECT_EQ(3u, val.toUint32(0));
}

TEST_F(ValueTypeRationalTest_157, ToFloat_SimpleRational_157) {
    Rational r(1, 2);
    RationalValue val(r);
    EXPECT_FLOAT_EQ(0.5f, val.toFloat(0));
}

TEST_F(ValueTypeRationalTest_157, ToFloat_ZeroDenominator_157) {
    Rational r(1, 0);
    RationalValue val(r);
    // Division by zero - typically returns 0 or inf; just check no crash
    float result = val.toFloat(0);
    (void)result;
}

TEST_F(ValueTypeRationalTest_157, ToRational_Identity_157) {
    Rational r(3, 7);
    RationalValue val(r);
    Rational result = val.toRational(0);
    EXPECT_EQ(r.first, result.first);
    EXPECT_EQ(r.second, result.second);
}

// ============================================================================
// Tests for ValueType<URational>
// ============================================================================

class ValueTypeURationalTest_157 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_157, ToInt64_SimpleURational_157) {
    URational r(10, 3);
    URationalValue val(r);
    EXPECT_EQ(3, val.toInt64(0));
}

TEST_F(ValueTypeURationalTest_157, ToInt64_ExactDivision_157) {
    URational r(10, 2);
    URationalValue val(r);
    EXPECT_EQ(5, val.toInt64(0));
}

TEST_F(ValueTypeURationalTest_157, ToUint32_SimpleURational_157) {
    URational r(10, 3);
    URationalValue val(r);
    EXPECT_EQ(3u, val.toUint32(0));
}

TEST_F(ValueTypeURationalTest_157, ToFloat_SimpleURational_157) {
    URational r(1, 4);
    URationalValue val(r);
    EXPECT_FLOAT_EQ(0.25f, val.toFloat(0));
}

TEST_F(ValueTypeURationalTest_157, ToRational_SimpleURational_157) {
    URational r(3, 7);
    URationalValue val(r);
    Rational result = val.toRational(0);
    EXPECT_EQ(3, result.first);
    EXPECT_EQ(7, result.second);
}

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_157 : public ::testing::Test {};

TEST_F(ValueTypeUShortTest_157, DefaultConstructor_EmptyCount_157) {
    UShortValue val;
    EXPECT_EQ(0u, val.count());
}

TEST_F(ValueTypeUShortTest_157, ConstructWithValue_157) {
    UShortValue val(static_cast<uint16_t>(42));
    EXPECT_EQ(1u, val.count());
    EXPECT_EQ(42, val.toInt64(0));
}

TEST_F(ValueTypeUShortTest_157, ReadFromString_157) {
    UShortValue val;
    val.read("10 20 30");
    EXPECT_EQ(3u, val.count());
    EXPECT_EQ(10, val.toInt64(0));
    EXPECT_EQ(20, val.toInt64(1));
    EXPECT_EQ(30, val.toInt64(2));
}

TEST_F(ValueTypeUShortTest_157, ToFloat_157) {
    UShortValue val(static_cast<uint16_t>(42));
    EXPECT_FLOAT_EQ(42.0f, val.toFloat(0));
}

TEST_F(ValueTypeUShortTest_157, ToRational_157) {
    UShortValue val(static_cast<uint16_t>(5));
    Rational r = val.toRational(0);
    EXPECT_EQ(5, r.first);
    EXPECT_EQ(1, r.second);
}

TEST_F(ValueTypeUShortTest_157, ToString_157) {
    UShortValue val(static_cast<uint16_t>(123));
    EXPECT_EQ("123", val.toString(0));
}

TEST_F(ValueTypeUShortTest_157, Write_157) {
    UShortValue val(static_cast<uint16_t>(99));
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ("99", os.str());
}

TEST_F(ValueTypeUShortTest_157, CopyAssignment_157) {
    UShortValue val1(static_cast<uint16_t>(10));
    UShortValue val2(static_cast<uint16_t>(20));
    val2 = val1;
    EXPECT_EQ(10, val2.toInt64(0));
}

TEST_F(ValueTypeUShortTest_157, Clone_157) {
    UShortValue val(static_cast<uint16_t>(77));
    auto cloned = val.clone();
    EXPECT_EQ(77, cloned->toInt64(0));
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_157 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_157, ConstructWithValue_157) {
    ULongValue val(static_cast<uint32_t>(100000));
    EXPECT_EQ(1u, val.count());
    EXPECT_EQ(100000, val.toInt64(0));
}

TEST_F(ValueTypeULongTest_157, ReadFromString_157) {
    ULongValue val;
    val.read("1000 2000");
    EXPECT_EQ(2u, val.count());
    EXPECT_EQ(1000, val.toInt64(0));
    EXPECT_EQ(2000, val.toInt64(1));
}

TEST_F(ValueTypeULongTest_157, ToUint32_157) {
    ULongValue val(static_cast<uint32_t>(12345));
    EXPECT_EQ(12345u, val.toUint32(0));
}

// ============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================================

class ValueTypeShortTest_157 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_157, ConstructWithNegativeValue_157) {
    ShortValue val(static_cast<int16_t>(-42));
    EXPECT_EQ(-42, val.toInt64(0));
}

TEST_F(ValueTypeShortTest_157, ReadFromString_157) {
    ShortValue val;
    val.read("-10 20 -30");
    EXPECT_EQ(3u, val.count());
    EXPECT_EQ(-10, val.toInt64(0));
    EXPECT_EQ(20, val.toInt64(1));
    EXPECT_EQ(-30, val.toInt64(2));
}

// ============================================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================================

class ValueTypeLongTest_157 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_157, ConstructWithValue_157) {
    LongValue val(static_cast<int32_t>(-100000));
    EXPECT_EQ(-100000, val.toInt64(0));
}

TEST_F(ValueTypeLongTest_157, ReadFromString_157) {
    LongValue val;
    val.read("-1000 2000");
    EXPECT_EQ(2u, val.count());
    EXPECT_EQ(-1000, val.toInt64(0));
    EXPECT_EQ(2000, val.toInt64(1));
}

// ============================================================================
// Tests for DataArea functionality
// ============================================================================

class ValueTypeDataAreaTest_157 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_157, InitialDataAreaSizeZero_157) {
    UShortValue val;
    EXPECT_EQ(0u, val.sizeDataArea());
}

TEST_F(ValueTypeDataAreaTest_157, SetAndGetDataArea_157) {
    UShortValue val;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    val.setDataArea(data, 4);
    EXPECT_EQ(4u, val.sizeDataArea());
    DataBuf buf = val.dataArea();
    EXPECT_EQ(4u, buf.size());
}

// ============================================================================
// Tests for read from byte buffer
// ============================================================================

class ValueTypeReadBufTest_157 : public ::testing::Test {};

TEST_F(ValueTypeReadBufTest_157, ReadUShortFromBuffer_LittleEndian_157) {
    UShortValue val;
    byte buf[] = {0x01, 0x00, 0x02, 0x00};
    val.read(buf, 4, littleEndian);
    EXPECT_EQ(2u, val.count());
    EXPECT_EQ(1, val.toInt64(0));
    EXPECT_EQ(2, val.toInt64(1));
}

TEST_F(ValueTypeReadBufTest_157, ReadUShortFromBuffer_BigEndian_157) {
    UShortValue val;
    byte buf[] = {0x00, 0x01, 0x00, 0x02};
    val.read(buf, 4, bigEndian);
    EXPECT_EQ(2u, val.count());
    EXPECT_EQ(1, val.toInt64(0));
    EXPECT_EQ(2, val.toInt64(1));
}

// ============================================================================
// Tests for copy to byte buffer
// ============================================================================

class ValueTypeCopyTest_157 : public ::testing::Test {};

TEST_F(ValueTypeCopyTest_157, CopyUShort_LittleEndian_157) {
    UShortValue val;
    val.read("1 2");
    byte buf[4] = {};
    size_t sz = val.copy(buf, littleEndian);
    EXPECT_EQ(4u, sz);
    EXPECT_EQ(0x01, buf[0]);
    EXPECT_EQ(0x00, buf[1]);
    EXPECT_EQ(0x02, buf[2]);
    EXPECT_EQ(0x00, buf[3]);
}

TEST_F(ValueTypeCopyTest_157, CopyUShort_BigEndian_157) {
    UShortValue val;
    val.read("1 2");
    byte buf[4] = {};
    size_t sz = val.copy(buf, bigEndian);
    EXPECT_EQ(4u, sz);
    EXPECT_EQ(0x00, buf[0]);
    EXPECT_EQ(0x01, buf[1]);
    EXPECT_EQ(0x00, buf[2]);
    EXPECT_EQ(0x02, buf[3]);
}

// ============================================================================
// Tests for size()
// ============================================================================

class ValueTypeSizeTest_157 : public ::testing::Test {};

TEST_F(ValueTypeSizeTest_157, SizeUShort_157) {
    UShortValue val;
    val.read("1 2 3");
    // Each uint16_t is 2 bytes, 3 values = 6 bytes
    EXPECT_EQ(6u, val.size());
}

TEST_F(ValueTypeSizeTest_157, SizeULong_157) {
    ULongValue val;
    val.read("1 2");
    // Each uint32_t is 4 bytes, 2 values = 8 bytes
    EXPECT_EQ(8u, val.size());
}

TEST_F(ValueTypeSizeTest_157, SizeRational_157) {
    RationalValue val;
    val.read("1/2 3/4");
    // Each Rational is 8 bytes (two int32_t), 2 values = 16 bytes
    EXPECT_EQ(16u, val.size());
}

// ============================================================================
// Tests for multiple values in write
// ============================================================================

class ValueTypeWriteTest_157 : public ::testing::Test {};

TEST_F(ValueTypeWriteTest_157, WriteMultipleUShort_157) {
    UShortValue val;
    val.read("10 20 30");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ("10 20 30", os.str());
}

TEST_F(ValueTypeWriteTest_157, WriteMultipleRational_157) {
    RationalValue val;
    val.read("1/2 3/4");
    std::ostringstream os;
    val.write(os);
    EXPECT_EQ("1/2 3/4", os.str());
}

// ============================================================================
// Tests for toRational specializations for double
// ============================================================================

class ValueTypeDoubleToRationalTest_157 : public ::testing::Test {};

TEST_F(ValueTypeDoubleToRationalTest_157, ToRational_Half_157) {
    DoubleValue val(0.5);
    Rational r = val.toRational(0);
    // The rational should approximate 0.5
    EXPECT_NEAR(0.5, static_cast<double>(r.first) / r.second, 1e-5);
}

TEST_F(ValueTypeDoubleToRationalTest_157, ToRational_Zero_157) {
    DoubleValue val(0.0);
    Rational r = val.toRational(0);
    EXPECT_EQ(0, r.first);
}

TEST_F(ValueTypeDoubleToRationalTest_157, ToFloat_157) {
    DoubleValue val(3.14);
    EXPECT_NEAR(3.14, val.toFloat(0), 0.001);
}

// ============================================================================
// Tests for value_ direct access
// ============================================================================

class ValueTypeDirectAccessTest_157 : public ::testing::Test {};

TEST_F(ValueTypeDirectAccessTest_157, ValueListAccess_157) {
    UShortValue val;
    val.read("5 10 15");
    EXPECT_EQ(3u, val.value_.size());
    EXPECT_EQ(5, val.value_[0]);
    EXPECT_EQ(10, val.value_[1]);
    EXPECT_EQ(15, val.value_[2]);
}

TEST_F(ValueTypeDirectAccessTest_157, ValueListModify_157) {
    UShortValue val;
    val.read("5");
    val.value_.push_back(99);
    EXPECT_EQ(2u, val.count());
    EXPECT_EQ(99, val.toInt64(1));
}

// ============================================================================
// Tests for Rational read from string
// ============================================================================

class ValueTypeRationalReadTest_157 : public ::testing::Test {};

TEST_F(ValueTypeRationalReadTest_157, ReadRational_157) {
    RationalValue val;
    val.read("1/2");
    EXPECT_EQ(1u, val.count());
    EXPECT_FLOAT_EQ(0.5f, val.toFloat(0));
}

TEST_F(ValueTypeRationalReadTest_157, ReadMultipleRationals_157) {
    RationalValue val;
    val.read("1/2 3/4 5/6");
    EXPECT_EQ(3u, val.count());
    EXPECT_FLOAT_EQ(0.5f, val.toFloat(0));
    EXPECT_FLOAT_EQ(0.75f, val.toFloat(1));
    EXPECT_NEAR(5.0f / 6.0f, val.toFloat(2), 0.001f);
}

TEST_F(ValueTypeRationalReadTest_157, ReadURational_157) {
    URationalValue val;
    val.read("1/4");
    EXPECT_EQ(1u, val.count());
    EXPECT_FLOAT_EQ(0.25f, val.toFloat(0));
}

// ============================================================================
// Tests for toString with n
// ============================================================================

class ValueTypeToStringTest_157 : public ::testing::Test {};

TEST_F(ValueTypeToStringTest_157, ToStringFirstElement_157) {
    UShortValue val;
    val.read("10 20 30");
    EXPECT_EQ("10", val.toString(0));
    EXPECT_EQ("20", val.toString(1));
    EXPECT_EQ("30", val.toString(2));
}

TEST_F(ValueTypeToStringTest_157, ToStringRational_157) {
    RationalValue val;
    val.read("3/7");
    EXPECT_EQ("3/7", val.toString(0));
}

// ============================================================================
// Edge case: reading from buffer with type constructor
// ============================================================================

class ValueTypeBufConstructorTest_157 : public ::testing::Test {};

TEST_F(ValueTypeBufConstructorTest_157, ConstructFromBuffer_157) {
    byte buf[] = {0x01, 0x00, 0x02, 0x00};
    ValueType<uint16_t> val(buf, 4, littleEndian, unsignedShort);
    EXPECT_EQ(2u, val.count());
    EXPECT_EQ(1, val.toInt64(0));
    EXPECT_EQ(2, val.toInt64(1));
}

// ============================================================================
// Test CopyConstructor
// ============================================================================

class ValueTypeCopyConstructorTest_157 : public ::testing::Test {};

TEST_F(ValueTypeCopyConstructorTest_157, CopyConstructor_157) {
    UShortValue val1;
    val1.read("1 2 3");
    UShortValue val2(val1);
    EXPECT_EQ(3u, val2.count());
    EXPECT_EQ(1, val2.toInt64(0));
    EXPECT_EQ(2, val2.toInt64(1));
    EXPECT_EQ(3, val2.toInt64(2));
}
