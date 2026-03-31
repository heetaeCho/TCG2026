#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>
#include <vector>

using namespace Exiv2;

// =============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// =============================================================================

class ValueTypeUShortTest_175 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(ValueTypeUShortTest_175, DefaultConstructor_175) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_175, ConstructorWithValue_175) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42));
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_175, ReadFromString_175) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
    EXPECT_EQ(v.toInt64(2), 3);
}

TEST_F(ValueTypeUShortTest_175, ReadFromBuffer_175) {
    byte buf[4];
    // Little endian: 0x0001 = 1, 0x0002 = 2
    buf[0] = 0x01; buf[1] = 0x00;
    buf[2] = 0x02; buf[3] = 0x00;
    ValueType<uint16_t> v;
    v.read(buf, 4, littleEndian);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeUShortTest_175, CopyToBuffer_175) {
    ValueType<uint16_t> v;
    v.read("100 200");
    byte buf[4];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
}

TEST_F(ValueTypeUShortTest_175, ToString_175) {
    ValueType<uint16_t> v;
    v.read("42");
    EXPECT_EQ(v.toString(0), "42");
}

TEST_F(ValueTypeUShortTest_175, ToFloat_175) {
    ValueType<uint16_t> v;
    v.read("55");
    EXPECT_FLOAT_EQ(v.toFloat(0), 55.0f);
}

TEST_F(ValueTypeUShortTest_175, ToRational_175) {
    ValueType<uint16_t> v;
    v.read("7");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_175, ToUint32_175) {
    ValueType<uint16_t> v;
    v.read("65535");
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_175, WriteToStream_175) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_175, CloneTest_175) {
    ValueType<uint16_t> v;
    v.read("99");
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toInt64(0), 99);
}

TEST_F(ValueTypeUShortTest_175, CopyConstructor_175) {
    ValueType<uint16_t> v1;
    v1.read("11 22");
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 11);
    EXPECT_EQ(v2.toInt64(1), 22);
}

TEST_F(ValueTypeUShortTest_175, AssignmentOperator_175) {
    ValueType<uint16_t> v1;
    v1.read("5 10");
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 5);
    EXPECT_EQ(v2.toInt64(1), 10);
}

TEST_F(ValueTypeUShortTest_175, SizeTest_175) {
    ValueType<uint16_t> v;
    v.read("1 2 3 4");
    EXPECT_EQ(v.size(), 8u); // 4 * sizeof(uint16_t) = 8
}

// =============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// =============================================================================

class ValueTypeULongTest_175 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_175, DefaultConstructor_175) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_175, ReadFromString_175) {
    ValueType<uint32_t> v;
    v.read("100000 200000");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 100000);
    EXPECT_EQ(v.toInt64(1), 200000);
}

TEST_F(ValueTypeULongTest_175, ToFloat_175) {
    ValueType<uint32_t> v;
    v.read("12345");
    EXPECT_FLOAT_EQ(v.toFloat(0), 12345.0f);
}

TEST_F(ValueTypeULongTest_175, SizeTest_175) {
    ValueType<uint32_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.size(), 12u); // 3 * sizeof(uint32_t) = 12
}

// =============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// =============================================================================

class ValueTypeShortTest_175 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_175, NegativeValues_175) {
    ValueType<int16_t> v;
    v.read("-100 -200");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), -200);
}

TEST_F(ValueTypeShortTest_175, ToStringNegative_175) {
    ValueType<int16_t> v;
    v.read("-42");
    EXPECT_EQ(v.toString(0), "-42");
}

// =============================================================================
// Tests for ValueType<Rational> (RationalValue)
// =============================================================================

class ValueTypeRationalTest_175 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_175, DefaultConstructor_175) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_175, ReadFromString_175) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeRationalTest_175, ToFloat_175) {
    ValueType<Rational> v;
    v.read("1/2");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_175, ToInt64_175) {
    ValueType<Rational> v;
    v.read("7/2");
    EXPECT_EQ(v.toInt64(0), 3); // 7/2 = 3 (integer division)
}

TEST_F(ValueTypeRationalTest_175, ToUint32_175) {
    ValueType<Rational> v;
    v.read("10/3");
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeRationalTest_175, ToRational_175) {
    ValueType<Rational> v;
    v.read("3/7");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_175, ZeroDenominator_175) {
    ValueType<Rational> v;
    v.read("5/0");
    EXPECT_EQ(v.count(), 1u);
    // toFloat with zero denominator should handle gracefully
    float f = v.toFloat(0);
    // The behavior depends on implementation, but it shouldn't crash
    (void)f;
}

TEST_F(ValueTypeRationalTest_175, SizeTest_175) {
    ValueType<Rational> v;
    v.read("1/2 3/4 5/6");
    EXPECT_EQ(v.size(), 24u); // 3 * sizeof(Rational) = 3 * 8 = 24
}

// =============================================================================
// Tests for ValueType<URational> (URationalValue)
// =============================================================================

class ValueTypeURationalTest_175 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_175, ReadFromString_175) {
    ValueType<URational> v;
    v.read("1/100 2/100");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeURationalTest_175, ToFloat_175) {
    ValueType<URational> v;
    v.read("1/4");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeURationalTest_175, ToInt64_175) {
    ValueType<URational> v;
    v.read("9/2");
    EXPECT_EQ(v.toInt64(0), 4);
}

TEST_F(ValueTypeURationalTest_175, ToUint32_175) {
    ValueType<URational> v;
    v.read("15/4");
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeURationalTest_175, ToRational_175) {
    ValueType<URational> v;
    v.read("5/8");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 8);
}

// =============================================================================
// Tests for ValueType<float> (FloatValue)
// =============================================================================

class ValueTypeFloatTest_175 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_175, ReadFromString_175) {
    ValueType<float> v;
    v.read("3.14 2.71");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_NEAR(v.toFloat(0), 3.14f, 0.01f);
    EXPECT_NEAR(v.toFloat(1), 2.71f, 0.01f);
}

TEST_F(ValueTypeFloatTest_175, ToInt64_175) {
    ValueType<float> v;
    v.read("3.7");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeFloatTest_175, ToUint32_175) {
    ValueType<float> v;
    v.read("42.9");
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeFloatTest_175, ToRational_175) {
    ValueType<float> v;
    v.read("0.5");
    Rational r = v.toRational(0);
    // Should represent 0.5 as a rational
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<float>(r.first) / r.second, 0.5f, 0.001f);
    }
}

TEST_F(ValueTypeFloatTest_175, SizeTest_175) {
    ValueType<float> v;
    v.read("1.0 2.0");
    EXPECT_EQ(v.size(), 8u); // 2 * sizeof(float) = 8
}

// =============================================================================
// Tests for ValueType<double> (DoubleValue)
// =============================================================================

class ValueTypeDoubleTest_175 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_175, ReadFromString_175) {
    ValueType<double> v;
    v.read("1.23456789 9.87654321");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeDoubleTest_175, ToInt64_175) {
    ValueType<double> v;
    v.read("99.9");
    EXPECT_EQ(v.toInt64(0), 99);
}

TEST_F(ValueTypeDoubleTest_175, ToUint32_175) {
    ValueType<double> v;
    v.read("255.1");
    EXPECT_EQ(v.toUint32(0), 255u);
}

TEST_F(ValueTypeDoubleTest_175, ToRational_175) {
    ValueType<double> v;
    v.read("0.25");
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.25, 0.001);
    }
}

TEST_F(ValueTypeDoubleTest_175, SizeTest_175) {
    ValueType<double> v;
    v.read("1.0 2.0 3.0");
    EXPECT_EQ(v.size(), 24u); // 3 * sizeof(double) = 24
}

// =============================================================================
// Tests for setDataArea / sizeDataArea / dataArea
// =============================================================================

class ValueTypeDataAreaTest_175 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_175, SetDataArea_NormalCase_175) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int ret = v.setDataArea(data, 4);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
}

TEST_F(ValueTypeDataAreaTest_175, SetDataArea_EmptyClears_175) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02};
    v.setDataArea(data, 2);
    EXPECT_EQ(v.sizeDataArea(), 2u);

    // Setting with length 0 should clear
    int ret = v.setDataArea(nullptr, 0);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeDataAreaTest_175, DataAreaReturnsCorrectData_175) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB, 0xCC};
    v.setDataArea(data, 3);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 3u);
    EXPECT_EQ(buf.data()[0], 0xAA);
    EXPECT_EQ(buf.data()[1], 0xBB);
    EXPECT_EQ(buf.data()[2], 0xCC);
}

TEST_F(ValueTypeDataAreaTest_175, InitialSizeDataAreaIsZero_175) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeDataAreaTest_175, SetDataAreaOverwrite_175) {
    ValueType<uint32_t> v;
    byte data1[] = {0x01, 0x02};
    byte data2[] = {0x03, 0x04, 0x05, 0x06, 0x07};
    v.setDataArea(data1, 2);
    EXPECT_EQ(v.sizeDataArea(), 2u);
    v.setDataArea(data2, 5);
    EXPECT_EQ(v.sizeDataArea(), 5u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.data()[0], 0x03);
}

// =============================================================================
// Tests for boundary conditions
// =============================================================================

class ValueTypeBoundaryTest_175 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_175, EmptyStringRead_175) {
    ValueType<uint16_t> v;
    v.read("");
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_175, SingleValueCount_175) {
    ValueType<uint16_t> v;
    v.read("1");
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeBoundaryTest_175, ReadFromBufferZeroLength_175) {
    ValueType<uint16_t> v;
    v.read(nullptr, 0, littleEndian);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_175, BigEndianReadWrite_175) {
    byte buf_in[4];
    // Big endian: 0x0100 = 256, 0x0200 = 512
    buf_in[0] = 0x01; buf_in[1] = 0x00;
    buf_in[2] = 0x02; buf_in[3] = 0x00;
    ValueType<uint16_t> v;
    v.read(buf_in, 4, bigEndian);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 256);
    EXPECT_EQ(v.toInt64(1), 512);

    byte buf_out[4];
    size_t copied = v.copy(buf_out, bigEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(buf_out[0], 0x01);
    EXPECT_EQ(buf_out[1], 0x00);
    EXPECT_EQ(buf_out[2], 0x02);
    EXPECT_EQ(buf_out[3], 0x00);
}

TEST_F(ValueTypeBoundaryTest_175, ConstructorWithBufferAndByteOrder_175) {
    byte buf[2] = {0x00, 0x01}; // big endian: 1
    ValueType<uint16_t> v(buf, 2, bigEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 1);
}

// =============================================================================
// Tests for value_ member access and modification
// =============================================================================

class ValueTypeDirectAccess_175 : public ::testing::Test {};

TEST_F(ValueTypeDirectAccess_175, DirectValueAccess_175) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.value_.size(), 3u);
    EXPECT_EQ(v.value_[0], 10);
    EXPECT_EQ(v.value_[1], 20);
    EXPECT_EQ(v.value_[2], 30);
}

TEST_F(ValueTypeDirectAccess_175, DirectValueModify_175) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

// =============================================================================
// Tests for write output format
// =============================================================================

class ValueTypeWriteTest_175 : public ::testing::Test {};

TEST_F(ValueTypeWriteTest_175, WriteMultipleValues_175) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    // Should contain all three values separated by spaces
    EXPECT_NE(result.find("1"), std::string::npos);
    EXPECT_NE(result.find("2"), std::string::npos);
    EXPECT_NE(result.find("3"), std::string::npos);
}

TEST_F(ValueTypeWriteTest_175, WriteRationalValues_175) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_NE(result.find("1/2"), std::string::npos);
    EXPECT_NE(result.find("3/4"), std::string::npos);
}

// =============================================================================
// Tests for toStringOutOfBounds
// =============================================================================

class ValueTypeOutOfBoundsTest_175 : public ::testing::Test {};

TEST_F(ValueTypeOutOfBoundsTest_175, ToStringOutOfBounds_175) {
    ValueType<uint16_t> v;
    v.read("42");
    // Accessing index 0 should work
    EXPECT_EQ(v.toString(0), "42");
    // Accessing beyond count - behavior may throw or return empty
    // We just ensure it doesn't crash for index 1
    try {
        std::string s = v.toString(1);
        // If it doesn't throw, it should return something (possibly empty)
        (void)s;
    } catch (...) {
        // Exception is also acceptable behavior
    }
}

TEST_F(ValueTypeOutOfBoundsTest_175, ToInt64OutOfBounds_175) {
    ValueType<uint16_t> v;
    v.read("42");
    try {
        int64_t val = v.toInt64(5);
        (void)val;
    } catch (...) {
        // Exception is acceptable
    }
}

// =============================================================================
// Tests for copy constructor preserving data area
// =============================================================================

class ValueTypeCopyDataArea_175 : public ::testing::Test {};

TEST_F(ValueTypeCopyDataArea_175, CopyPreservesDataArea_175) {
    ValueType<uint16_t> v1;
    v1.read("1 2");
    byte data[] = {0xDE, 0xAD};
    v1.setDataArea(data, 2);

    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.sizeDataArea(), 2u);
    DataBuf buf = v2.dataArea();
    EXPECT_EQ(buf.data()[0], 0xDE);
    EXPECT_EQ(buf.data()[1], 0xAD);
}

TEST_F(ValueTypeCopyDataArea_175, AssignmentPreservesDataArea_175) {
    ValueType<uint16_t> v1;
    byte data[] = {0xBE, 0xEF};
    v1.setDataArea(data, 2);

    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.sizeDataArea(), 2u);
    DataBuf buf = v2.dataArea();
    EXPECT_EQ(buf.data()[0], 0xBE);
    EXPECT_EQ(buf.data()[1], 0xEF);
}

// =============================================================================
// Tests for int32_t (LongValue)
// =============================================================================

class ValueTypeLongTest_175 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_175, NegativeInt32Values_175) {
    ValueType<int32_t> v;
    v.read("-1000 2000 -3000");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -1000);
    EXPECT_EQ(v.toInt64(1), 2000);
    EXPECT_EQ(v.toInt64(2), -3000);
}

TEST_F(ValueTypeLongTest_175, SizeTest_175) {
    ValueType<int32_t> v;
    v.read("1 2");
    EXPECT_EQ(v.size(), 8u); // 2 * sizeof(int32_t) = 8
}
