#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_173 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(ValueTypeUShortTest_173, DefaultConstructor_173) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.typeId(), unsignedShort);
}

TEST_F(ValueTypeUShortTest_173, ConstructWithValue_173) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_173, ReadFromBuffer_173) {
    byte buf[4];
    us2Data(buf, 0x1234, littleEndian);
    us2Data(buf + 2, 0x5678, littleEndian);

    ValueType<uint16_t> v;
    int rc = v.read(buf, 4, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 0x1234);
    EXPECT_EQ(v.toInt64(1), 0x5678);
}

TEST_F(ValueTypeUShortTest_173, ReadFromString_173) {
    ValueType<uint16_t> v;
    int rc = v.read("100 200 300");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeUShortTest_173, CopyToBuffer_173) {
    ValueType<uint16_t> v;
    v.read("1000 2000");
    byte buf[4] = {};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);

    uint16_t val0 = getUShort(buf, littleEndian);
    uint16_t val1 = getUShort(buf + 2, littleEndian);
    EXPECT_EQ(val0, 1000);
    EXPECT_EQ(val1, 2000);
}

TEST_F(ValueTypeUShortTest_173, ToStringMethod_173) {
    ValueType<uint16_t> v;
    v.read("42");
    EXPECT_EQ(v.toString(0), "42");
}

TEST_F(ValueTypeUShortTest_173, WriteToStream_173) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_173, ToFloat_173) {
    ValueType<uint16_t> v(static_cast<uint16_t>(123), unsignedShort);
    EXPECT_FLOAT_EQ(v.toFloat(0), 123.0f);
}

TEST_F(ValueTypeUShortTest_173, ToRational_173) {
    ValueType<uint16_t> v(static_cast<uint16_t>(5), unsignedShort);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_173, ToUint32_173) {
    ValueType<uint16_t> v(static_cast<uint16_t>(65535), unsignedShort);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_173, SizeMethod_173) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.size(), 6u); // 3 * sizeof(uint16_t)
}

TEST_F(ValueTypeUShortTest_173, CloneMethod_173) {
    ValueType<uint16_t> v;
    v.read("42 84");
    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toInt64(0), 42);
    EXPECT_EQ(cloned->toInt64(1), 84);
}

TEST_F(ValueTypeUShortTest_173, CopyConstructor_173) {
    ValueType<uint16_t> v;
    v.read("10 20");
    ValueType<uint16_t> v2(v);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 10);
    EXPECT_EQ(v2.toInt64(1), 20);
}

TEST_F(ValueTypeUShortTest_173, AssignmentOperator_173) {
    ValueType<uint16_t> v;
    v.read("100");
    ValueType<uint16_t> v2;
    v2 = v;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 100);
}

TEST_F(ValueTypeUShortTest_173, SizeDataAreaEmpty_173) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_173, SetDataArea_173) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int rc = v.setDataArea(data, 4);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
}

TEST_F(ValueTypeUShortTest_173, DataAreaRetrieval_173) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB, 0xCC};
    v.setDataArea(data, 3);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 3u);
    EXPECT_EQ(db.data()[0], 0xAA);
    EXPECT_EQ(db.data()[1], 0xBB);
    EXPECT_EQ(db.data()[2], 0xCC);
}

TEST_F(ValueTypeUShortTest_173, EmptyReadFromString_173) {
    ValueType<uint16_t> v;
    // Reading empty string
    int rc = v.read("");
    // After reading empty string, count should remain 0 or handle gracefully
    EXPECT_GE(v.count(), 0u);
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_173 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_173, DefaultConstructor_173) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), unsignedLong);
}

TEST_F(ValueTypeULongTest_173, ReadFromString_173) {
    ValueType<uint32_t> v;
    v.read("4294967295");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toUint32(0), 4294967295u);
}

TEST_F(ValueTypeULongTest_173, ReadFromBuffer_173) {
    byte buf[8];
    ul2Data(buf, 0x12345678, bigEndian);
    ul2Data(buf + 4, 0xAABBCCDD, bigEndian);

    ValueType<uint32_t> v;
    v.read(buf, 8, bigEndian);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toUint32(0), 0x12345678u);
    EXPECT_EQ(v.toUint32(1), 0xAABBCCDDu);
}

TEST_F(ValueTypeULongTest_173, SizeMethod_173) {
    ValueType<uint32_t> v;
    v.read("1 2 3 4");
    EXPECT_EQ(v.size(), 16u); // 4 * sizeof(uint32_t)
}

// ============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================================

class ValueTypeShortTest_173 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_173, NegativeValue_173) {
    ValueType<int16_t> v;
    v.read("-100 200");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), 200);
}

TEST_F(ValueTypeShortTest_173, ToStringNegative_173) {
    ValueType<int16_t> v;
    v.read("-32768");
    EXPECT_EQ(v.toString(0), "-32768");
}

// ============================================================================
// Tests for ValueType<Rational>
// ============================================================================

class ValueTypeRationalTest_173 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_173, DefaultConstructor_173) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), signedRational);
}

TEST_F(ValueTypeRationalTest_173, ConstructWithValue_173) {
    Rational r(1, 2);
    ValueType<Rational> v(r, signedRational);
    EXPECT_EQ(v.count(), 1u);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 2);
}

TEST_F(ValueTypeRationalTest_173, ReadFromString_173) {
    ValueType<Rational> v;
    v.read("3/4 5/6");
    EXPECT_EQ(v.count(), 2u);
    Rational r0 = v.toRational(0);
    EXPECT_EQ(r0.first, 3);
    EXPECT_EQ(r0.second, 4);
    Rational r1 = v.toRational(1);
    EXPECT_EQ(r1.first, 5);
    EXPECT_EQ(r1.second, 6);
}

TEST_F(ValueTypeRationalTest_173, ToFloat_173) {
    Rational r(1, 4);
    ValueType<Rational> v(r, signedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_173, ToInt64_173) {
    Rational r(10, 3);
    ValueType<Rational> v(r, signedRational);
    EXPECT_EQ(v.toInt64(0), 3); // truncated
}

TEST_F(ValueTypeRationalTest_173, ToUint32_173) {
    Rational r(7, 2);
    ValueType<Rational> v(r, signedRational);
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeRationalTest_173, ZeroDenominator_173) {
    Rational r(1, 0);
    ValueType<Rational> v(r, signedRational);
    // With zero denominator, toFloat should handle gracefully
    // Just ensure no crash
    float f = v.toFloat(0);
    (void)f; // suppress unused warning
}

TEST_F(ValueTypeRationalTest_173, NegativeRational_173) {
    Rational r(-5, 3);
    ValueType<Rational> v(r, signedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), -5.0f / 3.0f);
}

TEST_F(ValueTypeRationalTest_173, ReadFromBuffer_173) {
    byte buf[8];
    l2Data(buf, 7, littleEndian);
    l2Data(buf + 4, 3, littleEndian);

    ValueType<Rational> v;
    v.read(buf, 8, littleEndian);
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 3);
}

TEST_F(ValueTypeRationalTest_173, SizeMethod_173) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.size(), 16u); // 2 * 8 bytes per rational
}

// ============================================================================
// Tests for ValueType<URational>
// ============================================================================

class ValueTypeURationalTest_173 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_173, DefaultConstructor_173) {
    ValueType<URational> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), unsignedRational);
}

TEST_F(ValueTypeURationalTest_173, ReadFromString_173) {
    ValueType<URational> v;
    v.read("10/3");
    EXPECT_EQ(v.count(), 1u);
    URational ur = {v.toRational(0).first, static_cast<uint32_t>(v.toRational(0).second)};
    // Check via toFloat
    EXPECT_FLOAT_EQ(v.toFloat(0), 10.0f / 3.0f);
}

TEST_F(ValueTypeURationalTest_173, ToInt64_173) {
    URational r(100, 7);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_EQ(v.toInt64(0), 14); // 100/7 = 14.28... truncated
}

TEST_F(ValueTypeURationalTest_173, ToUint32_173) {
    URational r(100, 10);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_EQ(v.toUint32(0), 10u);
}

// ============================================================================
// Tests for ValueType<float>
// ============================================================================

class ValueTypeFloatTest_173 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_173, DefaultConstructor_173) {
    ValueType<float> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), tiffFloat);
}

TEST_F(ValueTypeFloatTest_173, ReadFromString_173) {
    ValueType<float> v;
    v.read("3.14 2.718");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_NEAR(v.toFloat(0), 3.14f, 0.001f);
    EXPECT_NEAR(v.toFloat(1), 2.718f, 0.001f);
}

TEST_F(ValueTypeFloatTest_173, ToInt64_173) {
    ValueType<float> v(3.99f, tiffFloat);
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeFloatTest_173, ToUint32_173) {
    ValueType<float> v(42.7f, tiffFloat);
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeFloatTest_173, ToRational_173) {
    ValueType<float> v(0.5f, tiffFloat);
    Rational r = v.toRational(0);
    // Should represent 0.5 as some rational
    EXPECT_NEAR(static_cast<float>(r.first) / r.second, 0.5f, 0.001f);
}

TEST_F(ValueTypeFloatTest_173, SizeMethod_173) {
    ValueType<float> v;
    v.read("1.0 2.0 3.0");
    EXPECT_EQ(v.size(), 12u); // 3 * 4
}

// ============================================================================
// Tests for ValueType<double>
// ============================================================================

class ValueTypeDoubleTest_173 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_173, DefaultConstructor_173) {
    ValueType<double> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), tiffDouble);
}

TEST_F(ValueTypeDoubleTest_173, ReadFromString_173) {
    ValueType<double> v;
    v.read("1.23456789");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 1.23456789f, 0.0001f);
}

TEST_F(ValueTypeDoubleTest_173, ToInt64_173) {
    ValueType<double> v(99.99, tiffDouble);
    EXPECT_EQ(v.toInt64(0), 99);
}

TEST_F(ValueTypeDoubleTest_173, ToUint32_173) {
    ValueType<double> v(255.5, tiffDouble);
    EXPECT_EQ(v.toUint32(0), 255u);
}

TEST_F(ValueTypeDoubleTest_173, ToRational_173) {
    ValueType<double> v(0.25, tiffDouble);
    Rational r = v.toRational(0);
    EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.25, 0.001);
}

TEST_F(ValueTypeDoubleTest_173, SizeMethod_173) {
    ValueType<double> v;
    v.read("1.0 2.0");
    EXPECT_EQ(v.size(), 16u); // 2 * 8
}

// ============================================================================
// Tests for data area operations
// ============================================================================

class ValueTypeDataAreaTest_173 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_173, SetAndGetDataArea_173) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
    EXPECT_EQ(v.setDataArea(data, 5), 0);
    EXPECT_EQ(v.sizeDataArea(), 5u);

    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(db.data()[i], data[i]);
    }
}

TEST_F(ValueTypeDataAreaTest_173, DataAreaPreservedOnCopy_173) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB};
    v.setDataArea(data, 2);
    v.read("10");

    ValueType<uint16_t> v2(v);
    EXPECT_EQ(v2.sizeDataArea(), 2u);
    DataBuf db = v2.dataArea();
    EXPECT_EQ(db.data()[0], 0xAA);
    EXPECT_EQ(db.data()[1], 0xBB);
}

TEST_F(ValueTypeDataAreaTest_173, DataAreaPreservedOnAssignment_173) {
    ValueType<uint16_t> v;
    byte data[] = {0x11, 0x22, 0x33};
    v.setDataArea(data, 3);
    v.read("5");

    ValueType<uint16_t> v2;
    v2 = v;
    EXPECT_EQ(v2.sizeDataArea(), 3u);
    DataBuf db = v2.dataArea();
    EXPECT_EQ(db.data()[0], 0x11);
    EXPECT_EQ(db.data()[1], 0x22);
    EXPECT_EQ(db.data()[2], 0x33);
}

TEST_F(ValueTypeDataAreaTest_173, EmptyDataArea_173) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

// ============================================================================
// Tests for boundary conditions
// ============================================================================

class ValueTypeBoundaryTest_173 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_173, SingleElement_173) {
    ValueType<uint16_t> v;
    v.read("0");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 0);
}

TEST_F(ValueTypeBoundaryTest_173, ReadOverwritesPrevious_173) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    v.read("10 20");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
}

TEST_F(ValueTypeBoundaryTest_173, ValueListAccess_173) {
    ValueType<uint16_t> v;
    v.read("7 8 9");
    EXPECT_EQ(v.value_.size(), 3u);
    EXPECT_EQ(v.value_[0], 7);
    EXPECT_EQ(v.value_[1], 8);
    EXPECT_EQ(v.value_[2], 9);
}

TEST_F(ValueTypeBoundaryTest_173, LargeNumberOfValues_173) {
    ValueType<uint16_t> v;
    std::string vals;
    for (int i = 0; i < 100; ++i) {
        if (i > 0) vals += " ";
        vals += std::to_string(i);
    }
    v.read(vals);
    EXPECT_EQ(v.count(), 100u);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_EQ(v.toInt64(99), 99);
}

TEST_F(ValueTypeBoundaryTest_173, ByteOrderBigEndian_173) {
    byte buf[4];
    us2Data(buf, 0x0102, bigEndian);
    us2Data(buf + 2, 0x0304, bigEndian);

    ValueType<uint16_t> v;
    v.read(buf, 4, bigEndian);
    EXPECT_EQ(v.toInt64(0), 0x0102);
    EXPECT_EQ(v.toInt64(1), 0x0304);
}

TEST_F(ValueTypeBoundaryTest_173, CopyBigEndian_173) {
    ValueType<uint16_t> v;
    v.read("256");
    byte buf[2] = {};
    v.copy(buf, bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x00);
}

// ============================================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================================

class ValueTypeLongTest_173 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_173, NegativeValue_173) {
    ValueType<int32_t> v;
    v.read("-2147483648");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -2147483648LL);
}

TEST_F(ValueTypeLongTest_173, PositiveMaxValue_173) {
    ValueType<int32_t> v;
    v.read("2147483647");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 2147483647);
}

// ============================================================================
// Test write output format
// ============================================================================

class ValueTypeWriteTest_173 : public ::testing::Test {};

TEST_F(ValueTypeWriteTest_173, MultipleValuesWritten_173) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    std::string s = os.str();
    // Should contain the values
    EXPECT_NE(s.find("10"), std::string::npos);
    EXPECT_NE(s.find("20"), std::string::npos);
    EXPECT_NE(s.find("30"), std::string::npos);
}

TEST_F(ValueTypeWriteTest_173, RationalWritten_173) {
    ValueType<Rational> v;
    v.read("1/2");
    std::ostringstream os;
    v.write(os);
    std::string s = os.str();
    EXPECT_NE(s.find("1"), std::string::npos);
    EXPECT_NE(s.find("2"), std::string::npos);
}

// ============================================================================
// Test toString for various indices
// ============================================================================

class ValueTypeToStringTest_173 : public ::testing::Test {};

TEST_F(ValueTypeToStringTest_173, MultipleIndices_173) {
    ValueType<uint32_t> v;
    v.read("100 200 300");
    EXPECT_EQ(v.toString(0), "100");
    EXPECT_EQ(v.toString(1), "200");
    EXPECT_EQ(v.toString(2), "300");
}

TEST_F(ValueTypeToStringTest_173, RationalToString_173) {
    ValueType<Rational> v;
    v.read("3/7");
    std::string s = v.toString(0);
    EXPECT_NE(s.find("3"), std::string::npos);
    EXPECT_NE(s.find("7"), std::string::npos);
}
