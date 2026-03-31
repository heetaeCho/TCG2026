#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================

class ValueTypeUShortTest_2154 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_2154, DefaultConstructor_2154) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.typeId(), unsignedShort);
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_2154, ConstructFromSingleValue_2154) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    EXPECT_EQ(v.typeId(), unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_2154, ConstructFromBuffer_2154) {
    byte buf[4];
    us2Data(buf, 0x0102, littleEndian);
    us2Data(buf + 2, 0x0304, littleEndian);
    ValueType<uint16_t> v(buf, 4, littleEndian, unsignedShort);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 0x0102);
    EXPECT_EQ(v.toInt64(1), 0x0304);
}

TEST_F(ValueTypeUShortTest_2154, CopyConstructor_2154) {
    ValueType<uint16_t> v1(static_cast<uint16_t>(99), unsignedShort);
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 99);
}

TEST_F(ValueTypeUShortTest_2154, AssignmentOperator_2154) {
    ValueType<uint16_t> v1(static_cast<uint16_t>(55), unsignedShort);
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 55);
}

TEST_F(ValueTypeUShortTest_2154, ReadFromString_2154) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeUShortTest_2154, CopyToBuffer_2154) {
    ValueType<uint16_t> v;
    v.read("256 512");
    byte buf[4];
    memset(buf, 0, 4);
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(getUShort(buf, littleEndian), 256);
    EXPECT_EQ(getUShort(buf + 2, littleEndian), 512);
}

TEST_F(ValueTypeUShortTest_2154, Size_2154) {
    ValueType<uint16_t> v;
    v.read("1 2 3");
    EXPECT_EQ(v.size(), 6u); // 3 * 2 bytes
}

TEST_F(ValueTypeUShortTest_2154, ToString_2154) {
    ValueType<uint16_t> v;
    v.read("42");
    std::string s = v.toString(0);
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeUShortTest_2154, ToFloat_2154) {
    ValueType<uint16_t> v(static_cast<uint16_t>(100), unsignedShort);
    EXPECT_FLOAT_EQ(v.toFloat(0), 100.0f);
}

TEST_F(ValueTypeUShortTest_2154, ToRational_2154) {
    ValueType<uint16_t> v(static_cast<uint16_t>(7), unsignedShort);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_2154, ToUint32_2154) {
    ValueType<uint16_t> v(static_cast<uint16_t>(65535), unsignedShort);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_2154, WriteToOstream_2154) {
    ValueType<uint16_t> v;
    v.read("10 20");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_2154, Clone_2154) {
    ValueType<uint16_t> v(static_cast<uint16_t>(77), unsignedShort);
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toInt64(0), 77);
}

TEST_F(ValueTypeUShortTest_2154, EmptyCount_2154) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_2154, DataAreaInitiallyEmpty_2154) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_2154, SetDataArea_2154) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

// ============================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================

class ValueTypeULongTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_2154, DefaultConstructor_2154) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.typeId(), unsignedLong);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_2154, ConstructFromValue_2154) {
    ValueType<uint32_t> v(static_cast<uint32_t>(123456), unsignedLong);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 123456);
}

TEST_F(ValueTypeULongTest_2154, ReadFromBuffer_2154) {
    byte buf[8];
    ul2Data(buf, 1000, bigEndian);
    ul2Data(buf + 4, 2000, bigEndian);
    ValueType<uint32_t> v(buf, 8, bigEndian, unsignedLong);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1000);
    EXPECT_EQ(v.toInt64(1), 2000);
}

TEST_F(ValueTypeULongTest_2154, ReadFromString_2154) {
    ValueType<uint32_t> v;
    v.read("100 200 300 400");
    EXPECT_EQ(v.count(), 4u);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeULongTest_2154, Size_2154) {
    ValueType<uint32_t> v;
    v.read("1 2");
    EXPECT_EQ(v.size(), 8u); // 2 * 4 bytes
}

TEST_F(ValueTypeULongTest_2154, CopyToBuffer_2154) {
    ValueType<uint32_t> v;
    v.read("42");
    byte buf[4];
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 4u);
    EXPECT_EQ(getULong(buf, bigEndian), 42u);
}

// ============================================================
// Tests for ValueType<int16_t> (SShortValue)
// ============================================================

class ValueTypeSShortTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeSShortTest_2154, DefaultConstructor_2154) {
    ValueType<int16_t> v;
    EXPECT_EQ(v.typeId(), signedShort);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeSShortTest_2154, NegativeValue_2154) {
    ValueType<int16_t> v(static_cast<int16_t>(-100), signedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeSShortTest_2154, ReadFromString_2154) {
    ValueType<int16_t> v;
    v.read("-10 0 10");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -10);
    EXPECT_EQ(v.toInt64(1), 0);
    EXPECT_EQ(v.toInt64(2), 10);
}

// ============================================================
// Tests for ValueType<Rational> (RationalValue)
// ============================================================

class ValueTypeRationalTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_2154, DefaultConstructor_2154) {
    ValueType<Rational> v;
    EXPECT_EQ(v.typeId(), signedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_2154, ConstructFromValue_2154) {
    Rational r(1, 3);
    ValueType<Rational> v(r, signedRational);
    EXPECT_EQ(v.count(), 1u);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 3);
}

TEST_F(ValueTypeRationalTest_2154, ToFloat_2154) {
    Rational r(1, 4);
    ValueType<Rational> v(r, signedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_2154, ToInt64_2154) {
    Rational r(7, 2);
    ValueType<Rational> v(r, signedRational);
    // 7/2 = 3 (integer truncation)
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeRationalTest_2154, ToUint32_2154) {
    Rational r(10, 3);
    ValueType<Rational> v(r, signedRational);
    EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeRationalTest_2154, ReadFromString_2154) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.count(), 2u);
    Rational r0 = v.toRational(0);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 2);
    Rational r1 = v.toRational(1);
    EXPECT_EQ(r1.first, 3);
    EXPECT_EQ(r1.second, 4);
}

TEST_F(ValueTypeRationalTest_2154, ReadFromBuffer_2154) {
    byte buf[8];
    l2Data(buf, 5, littleEndian);
    l2Data(buf + 4, 10, littleEndian);
    ValueType<Rational> v(buf, 8, littleEndian, signedRational);
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 10);
}

TEST_F(ValueTypeRationalTest_2154, ZeroDenominator_ToFloat_2154) {
    Rational r(1, 0);
    ValueType<Rational> v(r, signedRational);
    // Division by zero scenario - float should be inf or some defined behavior
    float f = v.toFloat(0);
    // Just check it doesn't crash; behavior depends on implementation
    (void)f;
}

TEST_F(ValueTypeRationalTest_2154, Size_2154) {
    ValueType<Rational> v;
    v.read("1/2 3/4");
    EXPECT_EQ(v.size(), 16u); // 2 * 8 bytes
}

TEST_F(ValueTypeRationalTest_2154, Clone_2154) {
    Rational r(3, 7);
    ValueType<Rational> v(r, signedRational);
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toRational(0).first, 3);
    EXPECT_EQ(cloned->toRational(0).second, 7);
}

// ============================================================
// Tests for ValueType<URational> (URationalValue)
// ============================================================

class ValueTypeURationalTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_2154, DefaultConstructor_2154) {
    ValueType<URational> v;
    EXPECT_EQ(v.typeId(), unsignedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeURationalTest_2154, ConstructFromValue_2154) {
    URational r(3, 5);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_EQ(v.count(), 1u);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 5);
}

TEST_F(ValueTypeURationalTest_2154, ToFloat_2154) {
    URational r(1, 8);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.125f);
}

TEST_F(ValueTypeURationalTest_2154, ToInt64_2154) {
    URational r(15, 4);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeURationalTest_2154, ToUint32_2154) {
    URational r(20, 3);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_EQ(v.toUint32(0), 6u);
}

// ============================================================
// Tests for ValueType<float> (FloatValue)
// ============================================================

class ValueTypeFloatTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_2154, DefaultConstructor_2154) {
    ValueType<float> v;
    EXPECT_EQ(v.typeId(), tiffFloat);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_2154, ConstructFromValue_2154) {
    ValueType<float> v(3.14f, tiffFloat);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

TEST_F(ValueTypeFloatTest_2154, ToInt64_2154) {
    ValueType<float> v(3.7f, tiffFloat);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);
}

TEST_F(ValueTypeFloatTest_2154, ToUint32_2154) {
    ValueType<float> v(5.9f, tiffFloat);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 5u);
}

TEST_F(ValueTypeFloatTest_2154, ToRational_2154) {
    ValueType<float> v(0.5f, tiffFloat);
    Rational r = v.toRational(0);
    // Verify the rational approximation is close to 0.5
    if (r.second != 0) {
        float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(approx, 0.5f, 0.001f);
    }
}

TEST_F(ValueTypeFloatTest_2154, ReadFromString_2154) {
    ValueType<float> v;
    v.read("1.5 2.5 3.5");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
    EXPECT_FLOAT_EQ(v.toFloat(1), 2.5f);
    EXPECT_FLOAT_EQ(v.toFloat(2), 3.5f);
}

TEST_F(ValueTypeFloatTest_2154, Size_2154) {
    ValueType<float> v;
    v.read("1.0 2.0");
    EXPECT_EQ(v.size(), 8u); // 2 * 4 bytes
}

// ============================================================
// Tests for ValueType<double> (DoubleValue)
// ============================================================

class ValueTypeDoubleTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_2154, DefaultConstructor_2154) {
    ValueType<double> v;
    EXPECT_EQ(v.typeId(), tiffDouble);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_2154, ConstructFromValue_2154) {
    ValueType<double> v(2.71828, tiffDouble);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 2.71828f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_2154, ToInt64_2154) {
    ValueType<double> v(9.99, tiffDouble);
    EXPECT_EQ(v.toInt64(0), 9);
}

TEST_F(ValueTypeDoubleTest_2154, ToUint32_2154) {
    ValueType<double> v(100.1, tiffDouble);
    EXPECT_EQ(v.toUint32(0), 100u);
}

TEST_F(ValueTypeDoubleTest_2154, ToRational_2154) {
    ValueType<double> v(0.25, tiffDouble);
    Rational r = v.toRational(0);
    if (r.second != 0) {
        double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(approx, 0.25, 0.001);
    }
}

TEST_F(ValueTypeDoubleTest_2154, Size_2154) {
    ValueType<double> v;
    v.read("1.0 2.0 3.0");
    EXPECT_EQ(v.size(), 24u); // 3 * 8 bytes
}

// ============================================================
// Tests for ValueType<int32_t> (SLongValue)
// ============================================================

class ValueTypeSLongTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeSLongTest_2154, DefaultConstructor_2154) {
    ValueType<int32_t> v;
    EXPECT_EQ(v.typeId(), signedLong);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeSLongTest_2154, NegativeValue_2154) {
    ValueType<int32_t> v(static_cast<int32_t>(-999), signedLong);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -999);
}

TEST_F(ValueTypeSLongTest_2154, ReadFromString_2154) {
    ValueType<int32_t> v;
    v.read("-100 0 100");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), 0);
    EXPECT_EQ(v.toInt64(2), 100);
}

// ============================================================
// Tests for Value::create static factory
// ============================================================

class ValueCreateTest_2154 : public ::testing::Test {};

TEST_F(ValueCreateTest_2154, CreateUnsignedShort_2154) {
    auto v = Value::create(unsignedShort);
    EXPECT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}

TEST_F(ValueCreateTest_2154, CreateUnsignedLong_2154) {
    auto v = Value::create(unsignedLong);
    EXPECT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedLong);
}

TEST_F(ValueCreateTest_2154, CreateSignedRational_2154) {
    auto v = Value::create(signedRational);
    EXPECT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), signedRational);
}

TEST_F(ValueCreateTest_2154, CreateUnsignedRational_2154) {
    auto v = Value::create(unsignedRational);
    EXPECT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedRational);
}

// ============================================================
// Tests for byte order handling
// ============================================================

class ValueTypeByteOrderTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeByteOrderTest_2154, LittleEndianRead_2154) {
    byte buf[2] = {0x01, 0x00}; // 1 in little endian
    ValueType<uint16_t> v(buf, 2, littleEndian, unsignedShort);
    EXPECT_EQ(v.toInt64(0), 1);
}

TEST_F(ValueTypeByteOrderTest_2154, BigEndianRead_2154) {
    byte buf[2] = {0x00, 0x01}; // 1 in big endian
    ValueType<uint16_t> v(buf, 2, bigEndian, unsignedShort);
    EXPECT_EQ(v.toInt64(0), 1);
}

TEST_F(ValueTypeByteOrderTest_2154, LittleEndianCopy_2154) {
    ValueType<uint16_t> v(static_cast<uint16_t>(0x0102), unsignedShort);
    byte buf[2];
    v.copy(buf, littleEndian);
    EXPECT_EQ(buf[0], 0x02);
    EXPECT_EQ(buf[1], 0x01);
}

TEST_F(ValueTypeByteOrderTest_2154, BigEndianCopy_2154) {
    ValueType<uint16_t> v(static_cast<uint16_t>(0x0102), unsignedShort);
    byte buf[2];
    v.copy(buf, bigEndian);
    EXPECT_EQ(buf[0], 0x01);
    EXPECT_EQ(buf[1], 0x02);
}

// ============================================================
// Tests for multiple values and value_ access
// ============================================================

class ValueTypeMultipleValues_2154 : public ::testing::Test {};

TEST_F(ValueTypeMultipleValues_2154, DirectValueAccess_2154) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    v.value_.push_back(30);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeMultipleValues_2154, ValueListModification_2154) {
    ValueType<uint32_t> v;
    v.value_.push_back(100);
    EXPECT_EQ(v.count(), 1u);
    v.value_.push_back(200);
    EXPECT_EQ(v.count(), 2u);
    v.value_.clear();
    EXPECT_EQ(v.count(), 0u);
}

// ============================================================
// Tests for ok() method
// ============================================================

class ValueTypeOkTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeOkTest_2154, OkAfterConstruction_2154) {
    ValueType<uint16_t> v;
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeOkTest_2154, OkAfterRead_2154) {
    ValueType<uint16_t> v;
    v.read("10 20");
    EXPECT_TRUE(v.ok());
}

// ============================================================
// Edge case tests
// ============================================================

class ValueTypeEdgeCases_2154 : public ::testing::Test {};

TEST_F(ValueTypeEdgeCases_2154, SingleByteBufferForUShort_2154) {
    // Buffer size not a multiple of type size
    byte buf[1] = {0x01};
    ValueType<uint16_t> v(buf, 1, littleEndian, unsignedShort);
    // With only 1 byte, can't read a full uint16_t
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeEdgeCases_2154, EmptyStringRead_2154) {
    ValueType<uint16_t> v;
    v.read("");
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeEdgeCases_2154, ZeroLengthBuffer_2154) {
    byte buf[1] = {0};
    ValueType<uint16_t> v(buf, 0, littleEndian, unsignedShort);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeEdgeCases_2154, LargeValueUint32_2154) {
    ValueType<uint32_t> v(static_cast<uint32_t>(0xFFFFFFFF), unsignedLong);
    EXPECT_EQ(v.toUint32(0), 0xFFFFFFFF);
}

TEST_F(ValueTypeEdgeCases_2154, WriteToString_2154) {
    ValueType<uint16_t> v;
    v.read("42");
    std::string s = v.toString(0);
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeEdgeCases_2154, ToStringDefault_2154) {
    ValueType<uint16_t> v;
    v.read("42 43");
    std::string s = v.toString();
    EXPECT_FALSE(s.empty());
}

// ============================================================
// Data area tests
// ============================================================

class ValueTypeDataAreaTest_2154 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_2154, SetAndRetrieveDataArea_2154) {
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

TEST_F(ValueTypeDataAreaTest_2154, DataAreaPreservedOnCopy_2154) {
    ValueType<uint16_t> v1;
    byte data[] = {0x01, 0x02};
    v1.setDataArea(data, sizeof(data));
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.sizeDataArea(), 2u);
}

TEST_F(ValueTypeDataAreaTest_2154, DataAreaPreservedOnAssignment_2154) {
    ValueType<uint16_t> v1;
    byte data[] = {0x01, 0x02, 0x03};
    v1.setDataArea(data, sizeof(data));
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.sizeDataArea(), 3u);
}
