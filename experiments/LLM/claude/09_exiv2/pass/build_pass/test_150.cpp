#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cstring>
#include <sstream>
#include <vector>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_150 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_150, DefaultConstructor_EmptyValue_150) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_150, ConstructWithSingleValue_150) {
    ValueType<uint16_t> v(42, unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_150, ReadFromBuffer_150) {
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

TEST_F(ValueTypeUShortTest_150, ReadFromString_150) {
    ValueType<uint16_t> v;
    int rc = v.read("100 200 300");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeUShortTest_150, CopyToBuffer_150) {
    ValueType<uint16_t> v;
    v.read("1000 2000");

    byte buf[4] = {};
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 4u);

    uint16_t val0 = getUShort(buf, bigEndian);
    uint16_t val1 = getUShort(buf + 2, bigEndian);
    EXPECT_EQ(val0, 1000u);
    EXPECT_EQ(val1, 2000u);
}

TEST_F(ValueTypeUShortTest_150, Size_150) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.size(), 6u); // 3 * sizeof(uint16_t)
}

TEST_F(ValueTypeUShortTest_150, ToString_150) {
    ValueType<uint16_t> v;
    v.read("42 99");
    EXPECT_EQ(v.toString(0), "42");
    EXPECT_EQ(v.toString(1), "99");
}

TEST_F(ValueTypeUShortTest_150, ToFloat_150) {
    ValueType<uint16_t> v;
    v.read("123");
    EXPECT_FLOAT_EQ(v.toFloat(0), 123.0f);
}

TEST_F(ValueTypeUShortTest_150, ToRational_150) {
    ValueType<uint16_t> v;
    v.read("50");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 50);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_150, ToUint32_150) {
    ValueType<uint16_t> v;
    v.read("65535");
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_150, WriteToStream_150) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_150, CopyConstructor_150) {
    ValueType<uint16_t> v1;
    v1.read("5 10 15");
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 3u);
    EXPECT_EQ(v2.toInt64(0), 5);
    EXPECT_EQ(v2.toInt64(1), 10);
    EXPECT_EQ(v2.toInt64(2), 15);
}

TEST_F(ValueTypeUShortTest_150, AssignmentOperator_150) {
    ValueType<uint16_t> v1;
    v1.read("7 14");
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 7);
    EXPECT_EQ(v2.toInt64(1), 14);
}

TEST_F(ValueTypeUShortTest_150, Clone_150) {
    ValueType<uint16_t> v;
    v.read("42");
    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_150, DataAreaEmpty_150) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_150, SetDataArea_150) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int rc = v.setDataArea(data, 4);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_150 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_150, DefaultConstructor_150) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeULongTest_150, ReadFromString_150) {
    ValueType<uint32_t> v;
    v.read("100000 200000");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 100000);
    EXPECT_EQ(v.toInt64(1), 200000);
}

TEST_F(ValueTypeULongTest_150, ReadFromBuffer_150) {
    byte buf[8];
    ul2Data(buf, 0x12345678, littleEndian);
    ul2Data(buf + 4, 0xAABBCCDD, littleEndian);

    ValueType<uint32_t> v;
    int rc = v.read(buf, 8, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toUint32(0), 0x12345678u);
    EXPECT_EQ(v.toUint32(1), 0xAABBCCDDu);
}

TEST_F(ValueTypeULongTest_150, CopyToBuffer_150) {
    ValueType<uint32_t> v;
    v.read("305419896"); // 0x12345678
    byte buf[4] = {};
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 4u);
    uint32_t val = getULong(buf, bigEndian);
    EXPECT_EQ(val, 305419896u);
}

TEST_F(ValueTypeULongTest_150, Size_150) {
    ValueType<uint32_t> v;
    v.read("1 2 3 4");
    EXPECT_EQ(v.size(), 16u); // 4 * sizeof(uint32_t)
}

TEST_F(ValueTypeULongTest_150, ToFloat_150) {
    ValueType<uint32_t> v;
    v.read("12345");
    EXPECT_FLOAT_EQ(v.toFloat(0), 12345.0f);
}

// ============================================================================
// Tests for ValueType<int16_t> (SShortValue)
// ============================================================================

class ValueTypeSShortTest_150 : public ::testing::Test {};

TEST_F(ValueTypeSShortTest_150, ReadNegativeValues_150) {
    ValueType<int16_t> v;
    v.read("-100 200 -300");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), -300);
}

TEST_F(ValueTypeSShortTest_150, ToFloat_150) {
    ValueType<int16_t> v;
    v.read("-50");
    EXPECT_FLOAT_EQ(v.toFloat(0), -50.0f);
}

TEST_F(ValueTypeSShortTest_150, ToString_150) {
    ValueType<int16_t> v;
    v.read("-32768");
    EXPECT_EQ(v.toString(0), "-32768");
}

// ============================================================================
// Tests for ValueType<Rational> (RationalValue)
// ============================================================================

class ValueTypeRationalTest_150 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_150, DefaultConstructor_150) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_150, ReadFromString_150) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeRationalTest_150, ToFloat_150) {
    ValueType<Rational> v;
    v.read("1/2");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_150, ToInt64_150) {
    ValueType<Rational> v;
    v.read("10/3");
    EXPECT_EQ(v.toInt64(0), 3); // truncated
}

TEST_F(ValueTypeRationalTest_150, ToUint32_150) {
    ValueType<Rational> v;
    v.read("7/2");
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeRationalTest_150, ToRational_150) {
    ValueType<Rational> v;
    v.read("3/7");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_150, ZeroDenominator_ToFloat_150) {
    ValueType<Rational> v;
    v.read("1/0");
    // Should handle gracefully; behavior may vary but should not crash
    float f = v.toFloat(0);
    (void)f; // just ensure it doesn't crash
}

TEST_F(ValueTypeRationalTest_150, NegativeRational_150) {
    ValueType<Rational> v;
    v.read("-5/3");
    EXPECT_EQ(v.toInt64(0), -1);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, -5);
    EXPECT_EQ(r.second, 3);
}

TEST_F(ValueTypeRationalTest_150, CopyToBuffer_150) {
    ValueType<Rational> v;
    v.read("1/2");
    byte buf[8] = {};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 8u);
}

TEST_F(ValueTypeRationalTest_150, Size_150) {
    ValueType<Rational> v;
    v.read("1/2 3/4 5/6");
    EXPECT_EQ(v.size(), 24u); // 3 * 8 bytes
}

// ============================================================================
// Tests for ValueType<URational> (URationalValue)
// ============================================================================

class ValueTypeURationalTest_150 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_150, ReadFromString_150) {
    ValueType<URational> v;
    v.read("10/3");
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeURationalTest_150, ToFloat_150) {
    ValueType<URational> v;
    v.read("7/2");
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.5f);
}

TEST_F(ValueTypeURationalTest_150, ToRational_150) {
    ValueType<URational> v;
    v.read("100/7");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 100);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeURationalTest_150, ToInt64_150) {
    ValueType<URational> v;
    v.read("10/3");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeURationalTest_150, ToUint32_150) {
    ValueType<URational> v;
    v.read("15/4");
    EXPECT_EQ(v.toUint32(0), 3u);
}

// ============================================================================
// Tests for ValueType<float> (FloatValue)
// ============================================================================

class ValueTypeFloatTest_150 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_150, DefaultConstructor_150) {
    ValueType<float> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_150, ReadFromString_150) {
    ValueType<float> v;
    v.read("3.14 2.71");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_NEAR(v.toFloat(0), 3.14f, 0.01f);
    EXPECT_NEAR(v.toFloat(1), 2.71f, 0.01f);
}

TEST_F(ValueTypeFloatTest_150, ToInt64_150) {
    ValueType<float> v;
    v.read("3.7");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeFloatTest_150, ToUint32_150) {
    ValueType<float> v;
    v.read("3.7");
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeFloatTest_150, ToRational_150) {
    ValueType<float> v;
    v.read("0.5");
    Rational r = v.toRational(0);
    // Should approximate 0.5 as a rational
    EXPECT_NE(r.second, 0);
    EXPECT_NEAR(static_cast<float>(r.first) / r.second, 0.5f, 0.001f);
}

TEST_F(ValueTypeFloatTest_150, NegativeFloat_150) {
    ValueType<float> v;
    v.read("-2.5");
    EXPECT_FLOAT_EQ(v.toFloat(0), -2.5f);
    EXPECT_EQ(v.toInt64(0), -2);
}

TEST_F(ValueTypeFloatTest_150, Size_150) {
    ValueType<float> v;
    v.read("1.0 2.0 3.0");
    EXPECT_EQ(v.size(), 12u); // 3 * sizeof(float)
}

// ============================================================================
// Tests for ValueType<double> (DoubleValue)
// ============================================================================

class ValueTypeDoubleTest_150 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_150, ReadFromString_150) {
    ValueType<double> v;
    v.read("3.14159265358979");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 3.14159f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_150, ToInt64_150) {
    ValueType<double> v;
    v.read("9.99");
    EXPECT_EQ(v.toInt64(0), 9);
}

TEST_F(ValueTypeDoubleTest_150, ToUint32_150) {
    ValueType<double> v;
    v.read("9.99");
    EXPECT_EQ(v.toUint32(0), 9u);
}

TEST_F(ValueTypeDoubleTest_150, ToRational_150) {
    ValueType<double> v;
    v.read("0.25");
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.25, 0.001);
}

TEST_F(ValueTypeDoubleTest_150, Size_150) {
    ValueType<double> v;
    v.read("1.0 2.0");
    EXPECT_EQ(v.size(), 16u); // 2 * sizeof(double)
}

// ============================================================================
// Boundary and edge case tests
// ============================================================================

class ValueTypeBoundaryTest_150 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_150, EmptyStringRead_UShort_150) {
    ValueType<uint16_t> v;
    v.read("");
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_150, SingleElementRead_150) {
    ValueType<uint32_t> v;
    v.read("42");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeBoundaryTest_150, LargeCount_150) {
    std::string str;
    for (int i = 0; i < 100; ++i) {
        if (i > 0) str += " ";
        str += std::to_string(i);
    }
    ValueType<uint16_t> v;
    v.read(str);
    EXPECT_EQ(v.count(), 100u);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_EQ(v.toInt64(99), 99);
}

TEST_F(ValueTypeBoundaryTest_150, ReadOverwritesPreviousData_150) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    v.read("10 20");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
}

TEST_F(ValueTypeBoundaryTest_150, ReadBufferOverwritesPreviousData_150) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);

    byte buf[2];
    us2Data(buf, 42, littleEndian);
    v.read(buf, 2, littleEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeBoundaryTest_150, CopyEmpty_150) {
    ValueType<uint16_t> v;
    byte buf[1] = {0xFF};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

TEST_F(ValueTypeBoundaryTest_150, DataAreaInitiallyEmpty_150) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

TEST_F(ValueTypeBoundaryTest_150, SetDataAreaAndRetrieve_150) {
    ValueType<uint32_t> v;
    byte data[] = {0xAA, 0xBB, 0xCC};
    v.setDataArea(data, 3);
    EXPECT_EQ(v.sizeDataArea(), 3u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 3u);
    EXPECT_EQ(db.data()[0], 0xAA);
    EXPECT_EQ(db.data()[1], 0xBB);
    EXPECT_EQ(db.data()[2], 0xCC);
}

TEST_F(ValueTypeBoundaryTest_150, WriteToOstream_150) {
    ValueType<uint16_t> v;
    v.read("5 10 15");
    std::ostringstream os;
    v.write(os);
    std::string s = os.str();
    EXPECT_NE(s.find("5"), std::string::npos);
    EXPECT_NE(s.find("10"), std::string::npos);
    EXPECT_NE(s.find("15"), std::string::npos);
}

TEST_F(ValueTypeBoundaryTest_150, ConstructFromBuffer_150) {
    byte buf[4];
    us2Data(buf, 100, bigEndian);
    us2Data(buf + 2, 200, bigEndian);
    ValueType<uint16_t> v(buf, 4, bigEndian, unsignedShort);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
}

// ============================================================================
// Tests for ValueType<int32_t> (SLongValue)
// ============================================================================

class ValueTypeSLongTest_150 : public ::testing::Test {};

TEST_F(ValueTypeSLongTest_150, ReadNegativeValues_150) {
    ValueType<int32_t> v;
    v.read("-1000000 2000000");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), -1000000);
    EXPECT_EQ(v.toInt64(1), 2000000);
}

TEST_F(ValueTypeSLongTest_150, ToString_150) {
    ValueType<int32_t> v;
    v.read("-999");
    EXPECT_EQ(v.toString(0), "-999");
}

TEST_F(ValueTypeSLongTest_150, Size_150) {
    ValueType<int32_t> v;
    v.read("1 2");
    EXPECT_EQ(v.size(), 8u);
}

// ============================================================================
// Tests verifying byte order handling
// ============================================================================

class ValueTypeByteOrderTest_150 : public ::testing::Test {};

TEST_F(ValueTypeByteOrderTest_150, BigEndianReadWrite_150) {
    ValueType<uint16_t> v;
    byte inBuf[2];
    us2Data(inBuf, 0x0102, bigEndian);
    v.read(inBuf, 2, bigEndian);
    EXPECT_EQ(v.toInt64(0), 0x0102);

    byte outBuf[2] = {};
    v.copy(outBuf, bigEndian);
    EXPECT_EQ(outBuf[0], 0x01);
    EXPECT_EQ(outBuf[1], 0x02);
}

TEST_F(ValueTypeByteOrderTest_150, LittleEndianReadWrite_150) {
    ValueType<uint16_t> v;
    byte inBuf[2];
    us2Data(inBuf, 0x0102, littleEndian);
    v.read(inBuf, 2, littleEndian);
    EXPECT_EQ(v.toInt64(0), 0x0102);

    byte outBuf[2] = {};
    v.copy(outBuf, littleEndian);
    EXPECT_EQ(outBuf[0], 0x02);
    EXPECT_EQ(outBuf[1], 0x01);
}

TEST_F(ValueTypeByteOrderTest_150, CrossByteOrderCopy_150) {
    ValueType<uint16_t> v;
    byte inBuf[2];
    us2Data(inBuf, 0xABCD, bigEndian);
    v.read(inBuf, 2, bigEndian);

    byte outBuf[2] = {};
    v.copy(outBuf, littleEndian);
    uint16_t result = getUShort(outBuf, littleEndian);
    EXPECT_EQ(result, 0xABCD);
}

// ============================================================================
// Rational special cases
// ============================================================================

class ValueTypeRationalEdgeCases_150 : public ::testing::Test {};

TEST_F(ValueTypeRationalEdgeCases_150, MultipleRationalsWrite_150) {
    ValueType<Rational> v;
    v.read("1/2 3/4 5/6");
    std::ostringstream os;
    v.write(os);
    std::string s = os.str();
    EXPECT_NE(s.find("1/2"), std::string::npos);
    EXPECT_NE(s.find("3/4"), std::string::npos);
    EXPECT_NE(s.find("5/6"), std::string::npos);
}

TEST_F(ValueTypeRationalEdgeCases_150, ClonePreservesValues_150) {
    ValueType<Rational> v;
    v.read("7/11");
    auto c = v.clone();
    ASSERT_NE(c, nullptr);
    Rational r = c->toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 11);
}

TEST_F(ValueTypeRationalEdgeCases_150, CopyConstructorPreservesDataArea_150) {
    ValueType<Rational> v;
    v.read("1/1");
    byte data[] = {0x01, 0x02};
    v.setDataArea(data, 2);

    ValueType<Rational> v2(v);
    EXPECT_EQ(v2.sizeDataArea(), 2u);
    DataBuf db = v2.dataArea();
    EXPECT_EQ(db.data()[0], 0x01);
    EXPECT_EQ(db.data()[1], 0x02);
}

TEST_F(ValueTypeRationalEdgeCases_150, AssignmentPreservesDataArea_150) {
    ValueType<Rational> v;
    v.read("1/1");
    byte data[] = {0xAB, 0xCD};
    v.setDataArea(data, 2);

    ValueType<Rational> v2;
    v2 = v;
    EXPECT_EQ(v2.sizeDataArea(), 2u);
    EXPECT_EQ(v2.count(), 1u);
}

// ============================================================================
// Public ValueList access tests
// ============================================================================

class ValueTypeValueListTest_150 : public ::testing::Test {};

TEST_F(ValueTypeValueListTest_150, DirectValueListAccess_150) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    ASSERT_EQ(v.value_.size(), 3u);
    EXPECT_EQ(v.value_[0], 10);
    EXPECT_EQ(v.value_[1], 20);
    EXPECT_EQ(v.value_[2], 30);
}

TEST_F(ValueTypeValueListTest_150, ModifyValueListDirectly_150) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    v.value_.push_back(40);
    EXPECT_EQ(v.count(), 4u);
    EXPECT_EQ(v.toInt64(3), 40);
}
