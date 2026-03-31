#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_151 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_151, DefaultConstructor_CountIsZero_151) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUShortTest_151, DefaultConstructor_SizeIsZero_151) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_151, ConstructWithSingleValue_151) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_151, ReadFromString_SingleValue_151) {
    ValueType<uint16_t> v;
    int result = v.read("100");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 100);
}

TEST_F(ValueTypeUShortTest_151, ReadFromString_MultipleValues_151) {
    ValueType<uint16_t> v;
    int result = v.read("10 20 30");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeUShortTest_151, ReadFromBuffer_151) {
    ValueType<uint16_t> v;
    uint16_t data[] = {0x0001, 0x0002, 0x0003};
    // Read as little endian
    int result = v.read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 3u);
}

TEST_F(ValueTypeUShortTest_151, ToStringValidIndex_151) {
    ValueType<uint16_t> v;
    v.read("42");
    std::string s = v.toString(0);
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeUShortTest_151, ToFloat_151) {
    ValueType<uint16_t> v;
    v.read("42");
    float f = v.toFloat(0);
    EXPECT_FLOAT_EQ(f, 42.0f);
}

TEST_F(ValueTypeUShortTest_151, ToUint32_151) {
    ValueType<uint16_t> v;
    v.read("42");
    uint32_t u = v.toUint32(0);
    EXPECT_EQ(u, 42u);
}

TEST_F(ValueTypeUShortTest_151, ToRational_151) {
    ValueType<uint16_t> v;
    v.read("42");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_151, WriteToOstream_151) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTypeUShortTest_151, CopyToBuffer_151) {
    ValueType<uint16_t> v;
    v.read("10 20");
    byte buf[4];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
}

TEST_F(ValueTypeUShortTest_151, CopyConstructor_151) {
    ValueType<uint16_t> v1;
    v1.read("1 2 3");
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 3u);
    EXPECT_EQ(v2.toInt64(0), 1);
    EXPECT_EQ(v2.toInt64(1), 2);
    EXPECT_EQ(v2.toInt64(2), 3);
}

TEST_F(ValueTypeUShortTest_151, AssignmentOperator_151) {
    ValueType<uint16_t> v1;
    v1.read("5 10 15");
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 3u);
    EXPECT_EQ(v2.toInt64(0), 5);
    EXPECT_EQ(v2.toInt64(1), 10);
    EXPECT_EQ(v2.toInt64(2), 15);
}

TEST_F(ValueTypeUShortTest_151, Clone_151) {
    ValueType<uint16_t> v;
    v.read("7 14");
    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toInt64(0), 7);
    EXPECT_EQ(cloned->toInt64(1), 14);
}

TEST_F(ValueTypeUShortTest_151, SizeDataArea_InitiallyZero_151) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_151, SetDataArea_151) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 4u);
}

TEST_F(ValueTypeUShortTest_151, ReadReplacesExistingValues_151) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    v.read("4 5");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 4);
    EXPECT_EQ(v.toInt64(1), 5);
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_151 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_151, DefaultConstruction_151) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeULongTest_151, ReadFromString_151) {
    ValueType<uint32_t> v;
    v.read("100000 200000");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 100000);
    EXPECT_EQ(v.toInt64(1), 200000);
}

TEST_F(ValueTypeULongTest_151, SizeCalculation_151) {
    ValueType<uint32_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.size(), 12u); // 3 * 4 bytes
}

TEST_F(ValueTypeULongTest_151, ToFloat_151) {
    ValueType<uint32_t> v;
    v.read("123456");
    EXPECT_FLOAT_EQ(v.toFloat(0), 123456.0f);
}

// ============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================================

class ValueTypeShortTest_151 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_151, NegativeValues_151) {
    ValueType<int16_t> v;
    v.read("-10 -20 30");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -10);
    EXPECT_EQ(v.toInt64(1), -20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeShortTest_151, ZeroValue_151) {
    ValueType<int16_t> v;
    v.read("0");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 0);
}

// ============================================================================
// Tests for ValueType<Rational> (RationalValue)
// ============================================================================

class ValueTypeRationalTest_151 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_151, DefaultConstruction_151) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_151, ReadFromString_151) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeRationalTest_151, ToFloat_151) {
    ValueType<Rational> v;
    v.read("1/2");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_151, ToInt64_151) {
    ValueType<Rational> v;
    v.read("10/2");
    EXPECT_EQ(v.toInt64(0), 5);
}

TEST_F(ValueTypeRationalTest_151, ToUint32_151) {
    ValueType<Rational> v;
    v.read("10/2");
    EXPECT_EQ(v.toUint32(0), 5u);
}

TEST_F(ValueTypeRationalTest_151, ToRational_ReturnsOriginal_151) {
    ValueType<Rational> v;
    v.read("3/7");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_151, ZeroDenominator_151) {
    ValueType<Rational> v;
    v.read("1/0");
    EXPECT_EQ(v.count(), 1u);
    // toFloat with zero denominator
    float f = v.toFloat(0);
    // Behavior with zero denominator - just check it doesn't crash
    (void)f;
}

TEST_F(ValueTypeRationalTest_151, SizeCalculation_151) {
    ValueType<Rational> v;
    v.read("1/2 3/4 5/6");
    // Each Rational is 8 bytes (two int32_t)
    EXPECT_EQ(v.size(), 24u);
}

TEST_F(ValueTypeRationalTest_151, CopyToBuffer_151) {
    ValueType<Rational> v;
    v.read("1/2");
    byte buf[8];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 8u);
}

// ============================================================================
// Tests for ValueType<URational> (URationalValue)
// ============================================================================

class ValueTypeURationalTest_151 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_151, ReadFromString_151) {
    ValueType<URational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeURationalTest_151, ToFloat_151) {
    ValueType<URational> v;
    v.read("3/4");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.75f);
}

TEST_F(ValueTypeURationalTest_151, ToInt64_151) {
    ValueType<URational> v;
    v.read("10/3");
    int64_t i = v.toInt64(0);
    EXPECT_EQ(i, 3); // truncated integer division
}

TEST_F(ValueTypeURationalTest_151, ToRational_151) {
    ValueType<URational> v;
    v.read("5/8");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 8);
}

// ============================================================================
// Tests for ValueType<float> (FloatValue)
// ============================================================================

class ValueTypeFloatTest_151 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_151, DefaultConstruction_151) {
    ValueType<float> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_151, ReadFromString_151) {
    ValueType<float> v;
    v.read("3.14 2.71");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_NEAR(v.toFloat(0), 3.14f, 0.01f);
    EXPECT_NEAR(v.toFloat(1), 2.71f, 0.01f);
}

TEST_F(ValueTypeFloatTest_151, ToInt64_Truncation_151) {
    ValueType<float> v;
    v.read("3.99");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeFloatTest_151, ToUint32_Truncation_151) {
    ValueType<float> v;
    v.read("3.99");
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeFloatTest_151, ToRational_151) {
    ValueType<float> v;
    v.read("0.5");
    Rational r = v.toRational(0);
    // Check that the rational approximates 0.5
    EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.5, 0.001);
}

TEST_F(ValueTypeFloatTest_151, SizeCalculation_151) {
    ValueType<float> v;
    v.read("1.0 2.0 3.0");
    EXPECT_EQ(v.size(), 12u); // 3 * 4 bytes
}

// ============================================================================
// Tests for ValueType<double> (DoubleValue)
// ============================================================================

class ValueTypeDoubleTest_151 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_151, DefaultConstruction_151) {
    ValueType<double> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_151, ReadFromString_151) {
    ValueType<double> v;
    v.read("3.141592653589793");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 3.14159f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_151, ToInt64_Truncation_151) {
    ValueType<double> v;
    v.read("9.99");
    EXPECT_EQ(v.toInt64(0), 9);
}

TEST_F(ValueTypeDoubleTest_151, ToUint32_Truncation_151) {
    ValueType<double> v;
    v.read("9.99");
    EXPECT_EQ(v.toUint32(0), 9u);
}

TEST_F(ValueTypeDoubleTest_151, ToRational_151) {
    ValueType<double> v;
    v.read("0.25");
    Rational r = v.toRational(0);
    EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.25, 0.001);
}

TEST_F(ValueTypeDoubleTest_151, SizeCalculation_151) {
    ValueType<double> v;
    v.read("1.0 2.0");
    EXPECT_EQ(v.size(), 16u); // 2 * 8 bytes
}

// ============================================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================================

class ValueTypeLongTest_151 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_151, NegativeValues_151) {
    ValueType<int32_t> v;
    v.read("-1000000 2000000");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), -1000000);
    EXPECT_EQ(v.toInt64(1), 2000000);
}

TEST_F(ValueTypeLongTest_151, ToStringMultipleValues_151) {
    ValueType<int32_t> v;
    v.read("100 200 300");
    EXPECT_EQ(v.toString(0), "100");
    EXPECT_EQ(v.toString(1), "200");
    EXPECT_EQ(v.toString(2), "300");
}

// ============================================================================
// Boundary and Edge Case Tests
// ============================================================================

class ValueTypeBoundaryTest_151 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_151, EmptyStringRead_151) {
    ValueType<uint16_t> v;
    v.read("");
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_151, SingleValueCount_151) {
    ValueType<uint16_t> v;
    v.read("1");
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeBoundaryTest_151, LargeNumberOfValues_151) {
    ValueType<uint16_t> v;
    std::string s;
    for (int i = 0; i < 100; i++) {
        if (i > 0) s += " ";
        s += std::to_string(i);
    }
    v.read(s);
    EXPECT_EQ(v.count(), 100u);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_EQ(v.toInt64(99), 99);
}

TEST_F(ValueTypeBoundaryTest_151, ReadBufferZeroLength_151) {
    ValueType<uint16_t> v;
    byte buf[1] = {0};
    int result = v.read(buf, 0, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_151, DataAreaEmptyInitially_151) {
    ValueType<uint32_t> v;
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(ValueTypeBoundaryTest_151, ReadFromBufferBigEndian_151) {
    ValueType<uint16_t> v;
    // 0x0001 in big endian
    byte data[] = {0x00, 0x01, 0x00, 0x02};
    v.read(data, sizeof(data), bigEndian);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeBoundaryTest_151, ReadFromBufferLittleEndian_151) {
    ValueType<uint16_t> v;
    // 0x0100 in little endian = 1, 0x0200 = 2
    byte data[] = {0x01, 0x00, 0x02, 0x00};
    v.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeBoundaryTest_151, CopyAndVerifyByteOrder_151) {
    ValueType<uint16_t> v;
    v.read("256"); // 0x0100
    byte buf[2];

    v.copy(buf, bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);

    v.copy(buf, littleEndian);
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
}

// ============================================================================
// Tests for ValueType value_ direct access (public member)
// ============================================================================

class ValueTypeDirectAccessTest_151 : public ::testing::Test {};

TEST_F(ValueTypeDirectAccessTest_151, DirectValueAccess_151) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
}

TEST_F(ValueTypeDirectAccessTest_151, ClearValues_151) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    v.value_.clear();
    EXPECT_EQ(v.count(), 0u);
}

// ============================================================================
// Write / toString tests
// ============================================================================

class ValueTypeOutputTest_151 : public ::testing::Test {};

TEST_F(ValueTypeOutputTest_151, WriteEmptyValue_151) {
    ValueType<uint16_t> v;
    std::ostringstream os;
    v.write(os);
    EXPECT_TRUE(os.str().empty());
}

TEST_F(ValueTypeOutputTest_151, WriteSingleValue_151) {
    ValueType<uint16_t> v;
    v.read("42");
    std::ostringstream os;
    v.write(os);
    EXPECT_EQ(os.str(), "42");
}

TEST_F(ValueTypeOutputTest_151, WriteMultipleValues_151) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    // Should contain all three values
    EXPECT_NE(output.find("1"), std::string::npos);
    EXPECT_NE(output.find("2"), std::string::npos);
    EXPECT_NE(output.find("3"), std::string::npos);
}

TEST_F(ValueTypeOutputTest_151, ToStringOutOfRange_151) {
    ValueType<uint16_t> v;
    v.read("42");
    // Accessing index beyond count - behavior may vary
    // Just verify index 0 works
    EXPECT_EQ(v.toString(0), "42");
}

TEST_F(ValueTypeOutputTest_151, RationalToString_151) {
    ValueType<Rational> v;
    v.read("3/7");
    std::string s = v.toString(0);
    EXPECT_EQ(s, "3/7");
}

TEST_F(ValueTypeOutputTest_151, URationalToString_151) {
    ValueType<URational> v;
    v.read("5/8");
    std::string s = v.toString(0);
    EXPECT_EQ(s, "5/8");
}

// ============================================================================
// SetDataArea tests
// ============================================================================

class ValueTypeDataAreaTest_151 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_151, SetAndGetDataArea_151) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    EXPECT_EQ(v.setDataArea(data, sizeof(data)), 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.data()[0], 0xAA);
    EXPECT_EQ(buf.data()[1], 0xBB);
    EXPECT_EQ(buf.data()[2], 0xCC);
    EXPECT_EQ(buf.data()[3], 0xDD);
}

TEST_F(ValueTypeDataAreaTest_151, SetDataAreaReplacesOld_151) {
    ValueType<uint16_t> v;
    byte data1[] = {0x01, 0x02};
    v.setDataArea(data1, sizeof(data1));
    EXPECT_EQ(v.sizeDataArea(), 2u);

    byte data2[] = {0x03, 0x04, 0x05};
    v.setDataArea(data2, sizeof(data2));
    EXPECT_EQ(v.sizeDataArea(), 3u);
}

TEST_F(ValueTypeDataAreaTest_151, DataAreaPreservedOnCopy_151) {
    ValueType<uint16_t> v1;
    v1.read("10");
    byte data[] = {0xFF, 0xFE};
    v1.setDataArea(data, sizeof(data));

    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.sizeDataArea(), 2u);
    DataBuf buf = v2.dataArea();
    EXPECT_EQ(buf.data()[0], 0xFF);
    EXPECT_EQ(buf.data()[1], 0xFE);
}

TEST_F(ValueTypeDataAreaTest_151, DataAreaPreservedOnAssignment_151) {
    ValueType<uint16_t> v1;
    v1.read("10");
    byte data[] = {0xAB, 0xCD};
    v1.setDataArea(data, sizeof(data));

    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.sizeDataArea(), 2u);
    DataBuf buf = v2.dataArea();
    EXPECT_EQ(buf.data()[0], 0xAB);
    EXPECT_EQ(buf.data()[1], 0xCD);
}

// ============================================================================
// Constructor with buffer tests
// ============================================================================

class ValueTypeBufferConstructorTest_151 : public ::testing::Test {};

TEST_F(ValueTypeBufferConstructorTest_151, ConstructFromBuffer_UShort_151) {
    byte data[] = {0x01, 0x00, 0x02, 0x00};
    ValueType<uint16_t> v(data, sizeof(data), littleEndian, unsignedShort);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeBufferConstructorTest_151, ConstructFromBuffer_ULong_151) {
    byte data[] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00};
    ValueType<uint32_t> v(data, sizeof(data), littleEndian, unsignedLong);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}
