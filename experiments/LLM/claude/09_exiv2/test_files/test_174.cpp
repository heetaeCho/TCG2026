#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_174 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_174, DefaultConstructor_174) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_174, SingleValueConstructor_174) {
    uint16_t val = 42;
    ValueType<uint16_t> v(val, unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeUShortTest_174, ReadFromBuffer_174) {
    // Two uint16_t values in little-endian: 0x0100 = 256, 0x0200 = 512
    byte buf[] = {0x00, 0x01, 0x00, 0x02};
    ValueType<uint16_t> v;
    int rc = v.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeUShortTest_174, ReadFromBufferBigEndian_174) {
    byte buf[] = {0x00, 0x01, 0x00, 0x02};
    ValueType<uint16_t> v;
    int rc = v.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeUShortTest_174, ReadFromString_174) {
    ValueType<uint16_t> v;
    int rc = v.read("100 200 300");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeUShortTest_174, ToStringNormal_174) {
    ValueType<uint16_t> v;
    v.read("42");
    std::string s = v.toString(0);
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeUShortTest_174, ToFloat_174) {
    ValueType<uint16_t> v;
    v.read("123");
    float f = v.toFloat(0);
    EXPECT_FLOAT_EQ(f, 123.0f);
}

TEST_F(ValueTypeUShortTest_174, ToRational_174) {
    ValueType<uint16_t> v;
    v.read("5");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_174, CopyToBuffer_174) {
    ValueType<uint16_t> v;
    v.read("1 2");
    byte buf[4];
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 4u);
    // Verify big-endian: value 1 => 0x00 0x01, value 2 => 0x00 0x02
    EXPECT_EQ(buf[0], 0x00);
    EXPECT_EQ(buf[1], 0x01);
    EXPECT_EQ(buf[2], 0x00);
    EXPECT_EQ(buf[3], 0x02);
}

TEST_F(ValueTypeUShortTest_174, WriteToStream_174) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_174, CloneTest_174) {
    ValueType<uint16_t> v;
    v.read("7 8 9");
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->toInt64(0), 7);
    EXPECT_EQ(cloned->toInt64(1), 8);
    EXPECT_EQ(cloned->toInt64(2), 9);
}

TEST_F(ValueTypeUShortTest_174, CopyConstructor_174) {
    ValueType<uint16_t> v;
    v.read("11 22");
    ValueType<uint16_t> v2(v);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 11);
    EXPECT_EQ(v2.toInt64(1), 22);
}

TEST_F(ValueTypeUShortTest_174, AssignmentOperator_174) {
    ValueType<uint16_t> v;
    v.read("55 66");
    ValueType<uint16_t> v2;
    v2 = v;
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 55);
    EXPECT_EQ(v2.toInt64(1), 66);
}

TEST_F(ValueTypeUShortTest_174, SizeMatchesCount_174) {
    ValueType<uint16_t> v;
    v.read("1 2 3 4 5");
    EXPECT_EQ(v.count(), 5u);
    EXPECT_EQ(v.size(), 5u * 2u); // uint16_t is 2 bytes each
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_174 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_174, DefaultConstructor_174) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeULongTest_174, ReadFromString_174) {
    ValueType<uint32_t> v;
    v.read("1000000 2000000");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1000000);
    EXPECT_EQ(v.toInt64(1), 2000000);
}

TEST_F(ValueTypeULongTest_174, ToUint32_174) {
    ValueType<uint32_t> v;
    v.read("4294967295");  // UINT32_MAX
    EXPECT_EQ(v.toUint32(0), 4294967295u);
}

TEST_F(ValueTypeULongTest_174, Size_174) {
    ValueType<uint32_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.size(), 3u * 4u); // uint32_t is 4 bytes each
}

// ============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================================

class ValueTypeShortTest_174 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_174, NegativeValues_174) {
    ValueType<int16_t> v;
    v.read("-100 -200 300");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), -200);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeShortTest_174, ToFloat_174) {
    ValueType<int16_t> v;
    v.read("-50");
    EXPECT_FLOAT_EQ(v.toFloat(0), -50.0f);
}

// ============================================================================
// Tests for ValueType<Rational>
// ============================================================================

class ValueTypeRationalTest_174 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_174, DefaultConstructor_174) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_174, ReadFromString_174) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeRationalTest_174, ToFloat_174) {
    ValueType<Rational> v;
    v.read("1/2");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_174, ToInt64_174) {
    ValueType<Rational> v;
    v.read("10/3");
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3); // floor(10/3) = 3
}

TEST_F(ValueTypeRationalTest_174, ToUint32_174) {
    ValueType<Rational> v;
    v.read("7/2");
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u); // floor(7/2) = 3
}

TEST_F(ValueTypeRationalTest_174, ToRational_174) {
    ValueType<Rational> v;
    v.read("3/7");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_174, ZeroDenominator_174) {
    ValueType<Rational> v;
    v.read("5/0");
    EXPECT_EQ(v.count(), 1u);
    // toFloat with zero denominator
    float f = v.toFloat(0);
    // Result may be inf or some special value, just ensure no crash
    (void)f;
}

TEST_F(ValueTypeRationalTest_174, SingleValueConstructor_174) {
    Rational r(3, 5);
    ValueType<Rational> v(r, signedRational);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toRational(0).first, 3);
    EXPECT_EQ(v.toRational(0).second, 5);
}

TEST_F(ValueTypeRationalTest_174, CopyToBuffer_174) {
    ValueType<Rational> v;
    v.read("1/2");
    byte buf[8]; // Rational is 8 bytes (two int32_t)
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 8u);
}

TEST_F(ValueTypeRationalTest_174, Size_174) {
    ValueType<Rational> v;
    v.read("1/2 3/4 5/6");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.size(), 3u * 8u); // Each rational is 8 bytes
}

// ============================================================================
// Tests for ValueType<URational>
// ============================================================================

class ValueTypeURationalTest_174 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_174, ReadFromString_174) {
    ValueType<URational> v;
    v.read("10/3 7/2");
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeURationalTest_174, ToFloat_174) {
    ValueType<URational> v;
    v.read("3/4");
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.75f);
}

TEST_F(ValueTypeURationalTest_174, ToRational_174) {
    ValueType<URational> v;
    v.read("5/8");
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 8);
}

TEST_F(ValueTypeURationalTest_174, ToInt64_174) {
    ValueType<URational> v;
    v.read("10/3");
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeURationalTest_174, ToUint32_174) {
    ValueType<URational> v;
    v.read("10/3");
    EXPECT_EQ(v.toUint32(0), 3u);
}

// ============================================================================
// Tests for ValueType<float>
// ============================================================================

class ValueTypeFloatTest_174 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_174, DefaultConstructor_174) {
    ValueType<float> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_174, ReadFromString_174) {
    ValueType<float> v;
    v.read("1.5 2.5 3.5");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
    EXPECT_FLOAT_EQ(v.toFloat(1), 2.5f);
    EXPECT_FLOAT_EQ(v.toFloat(2), 3.5f);
}

TEST_F(ValueTypeFloatTest_174, ToInt64_174) {
    ValueType<float> v;
    v.read("3.7");
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3); // truncation
}

TEST_F(ValueTypeFloatTest_174, ToUint32_174) {
    ValueType<float> v;
    v.read("5.9");
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 5u);
}

TEST_F(ValueTypeFloatTest_174, ToRational_174) {
    ValueType<float> v;
    v.read("0.5");
    Rational r = v.toRational(0);
    // Check that the rational approximates 0.5
    if (r.second != 0) {
        float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(approx, 0.5f, 0.001f);
    }
}

TEST_F(ValueTypeFloatTest_174, NegativeFloat_174) {
    ValueType<float> v;
    v.read("-2.5");
    EXPECT_FLOAT_EQ(v.toFloat(0), -2.5f);
}

TEST_F(ValueTypeFloatTest_174, Size_174) {
    ValueType<float> v;
    v.read("1.0 2.0");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.size(), 2u * 4u); // float is 4 bytes
}

// ============================================================================
// Tests for ValueType<double>
// ============================================================================

class ValueTypeDoubleTest_174 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_174, ReadFromString_174) {
    ValueType<double> v;
    v.read("1.23456789 9.87654321");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_NEAR(v.toFloat(0), 1.23456789f, 0.0001f);
}

TEST_F(ValueTypeDoubleTest_174, ToInt64_174) {
    ValueType<double> v;
    v.read("7.99");
    EXPECT_EQ(v.toInt64(0), 7);
}

TEST_F(ValueTypeDoubleTest_174, ToUint32_174) {
    ValueType<double> v;
    v.read("10.1");
    EXPECT_EQ(v.toUint32(0), 10u);
}

TEST_F(ValueTypeDoubleTest_174, ToRational_174) {
    ValueType<double> v;
    v.read("0.25");
    Rational r = v.toRational(0);
    if (r.second != 0) {
        double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(approx, 0.25, 0.001);
    }
}

TEST_F(ValueTypeDoubleTest_174, Size_174) {
    ValueType<double> v;
    v.read("1.0 2.0 3.0");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.size(), 3u * 8u); // double is 8 bytes
}

// ============================================================================
// Tests for DataArea functionality
// ============================================================================

class ValueTypeDataAreaTest_174 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_174, NoDataAreaByDefault_174) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

TEST_F(ValueTypeDataAreaTest_174, SetDataArea_174) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int rc = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

TEST_F(ValueTypeDataAreaTest_174, SetDataAreaEmpty_174) {
    ValueType<uint16_t> v;
    int rc = v.setDataArea(nullptr, 0);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeDataAreaTest_174, DataAreaPreservedOnCopy_174) {
    ValueType<uint16_t> v;
    v.read("10");
    byte data[] = {0xAA, 0xBB};
    v.setDataArea(data, sizeof(data));

    ValueType<uint16_t> v2(v);
    EXPECT_EQ(v2.sizeDataArea(), 2u);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 10);
}

TEST_F(ValueTypeDataAreaTest_174, DataAreaPreservedOnAssignment_174) {
    ValueType<uint16_t> v;
    v.read("20");
    byte data[] = {0xCC, 0xDD, 0xEE};
    v.setDataArea(data, sizeof(data));

    ValueType<uint16_t> v2;
    v2 = v;
    EXPECT_EQ(v2.sizeDataArea(), 3u);
    EXPECT_EQ(v2.count(), 1u);
}

// ============================================================================
// Tests for ValueType<int32_t> (LongValue)
// ============================================================================

class ValueTypeLongTest_174 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_174, NegativeValues_174) {
    ValueType<int32_t> v;
    v.read("-1000 2000 -3000");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -1000);
    EXPECT_EQ(v.toInt64(1), 2000);
    EXPECT_EQ(v.toInt64(2), -3000);
}

TEST_F(ValueTypeLongTest_174, ToString_174) {
    ValueType<int32_t> v;
    v.read("-42");
    EXPECT_EQ(v.toString(0), "-42");
}

TEST_F(ValueTypeLongTest_174, ReadFromBuffer_174) {
    // int32_t value 1 in big-endian
    byte buf[] = {0x00, 0x00, 0x00, 0x01};
    ValueType<int32_t> v;
    v.read(buf, sizeof(buf), bigEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 1);
}

// ============================================================================
// Boundary / Edge case tests
// ============================================================================

class ValueTypeBoundaryTest_174 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_174, EmptyStringRead_174) {
    ValueType<uint16_t> v;
    int rc = v.read("");
    // After reading empty string, count should be 0
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_174, SingleElement_174) {
    ValueType<uint16_t> v;
    v.read("65535");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeBoundaryTest_174, ReadOverwritesPreviousData_174) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.count(), 3u);
    v.read("4 5");
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 4);
    EXPECT_EQ(v.toInt64(1), 5);
}

TEST_F(ValueTypeBoundaryTest_174, BufferReadZeroLength_174) {
    ValueType<uint16_t> v;
    byte buf[] = {0x00};
    int rc = v.read(buf, 0, littleEndian);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_174, WriteToStreamMultipleValues_174) {
    ValueType<uint32_t> v;
    v.read("100 200 300");
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    // Output should contain all three values
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("200"), std::string::npos);
    EXPECT_NE(output.find("300"), std::string::npos);
}

TEST_F(ValueTypeBoundaryTest_174, ValueListDirectAccess_174) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.value_.size(), 3u);
    EXPECT_EQ(v.value_[0], 10);
    EXPECT_EQ(v.value_[1], 20);
    EXPECT_EQ(v.value_[2], 30);
}

TEST_F(ValueTypeBoundaryTest_174, ValueListModification_174) {
    ValueType<uint16_t> v;
    v.read("10");
    v.value_.push_back(20);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(1), 20);
}

// ============================================================================
// Tests for BufferConstructor
// ============================================================================

class ValueTypeBufferConstructorTest_174 : public ::testing::Test {};

TEST_F(ValueTypeBufferConstructorTest_174, ConstructFromBuffer_174) {
    byte buf[] = {0x00, 0x0A, 0x00, 0x14}; // big-endian: 10, 20
    ValueType<uint16_t> v(buf, sizeof(buf), bigEndian, unsignedShort);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
}

// ============================================================================
// Clone tests
// ============================================================================

class ValueTypeCloneTest_174 : public ::testing::Test {};

TEST_F(ValueTypeCloneTest_174, ClonePreservesValues_174) {
    ValueType<Rational> v;
    v.read("1/3 2/5");
    auto cloned = v.clone();
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toRational(0).first, 1);
    EXPECT_EQ(cloned->toRational(0).second, 3);
    EXPECT_EQ(cloned->toRational(1).first, 2);
    EXPECT_EQ(cloned->toRational(1).second, 5);
}

TEST_F(ValueTypeCloneTest_174, ClonePreservesDataArea_174) {
    ValueType<uint16_t> v;
    v.read("5");
    byte data[] = {0x01, 0x02, 0x03};
    v.setDataArea(data, sizeof(data));
    auto cloned = v.clone();
    EXPECT_EQ(cloned->sizeDataArea(), 3u);
}

TEST_F(ValueTypeCloneTest_174, CloneIsIndependent_174) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    auto cloned = v.clone();
    // Modify original
    v.read("99");
    // Clone should be unchanged
    EXPECT_EQ(cloned->count(), 3u);
    EXPECT_EQ(cloned->toInt64(0), 1);
}
