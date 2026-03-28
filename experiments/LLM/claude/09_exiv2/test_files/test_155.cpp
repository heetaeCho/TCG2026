#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cmath>
#include <sstream>
#include <stdexcept>

using namespace Exiv2;

// =============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// =============================================================================

class ValueTypeUShortTest_155 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

TEST_F(ValueTypeUShortTest_155, DefaultConstructor_155) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.typeId(), unsignedShort);
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_155, ConstructorWithValue_155) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42));
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_155, ToInt64Normal_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(100);
    v.value_.push_back(200);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUShortTest_155, ToInt64OutOfRange_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    EXPECT_THROW(v.toInt64(5), std::out_of_range);
}

TEST_F(ValueTypeUShortTest_155, ToUint32Normal_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(65535);
    EXPECT_EQ(v.toUint32(0), 65535u);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUShortTest_155, ToFloatNormal_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    EXPECT_FLOAT_EQ(v.toFloat(0), 42.0f);
}

TEST_F(ValueTypeUShortTest_155, ToRationalNormal_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(7);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 7);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_155, CountMultipleValues_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    v.value_.push_back(3);
    EXPECT_EQ(v.count(), 3u);
}

TEST_F(ValueTypeUShortTest_155, ToStringNormal_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    std::string s = v.toString(0);
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeUShortTest_155, WriteToStream_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_155, CloneTest_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(99);
    auto c = v.clone();
    ASSERT_NE(c, nullptr);
    EXPECT_EQ(c->toInt64(0), 99);
    EXPECT_EQ(c->count(), 1u);
}

TEST_F(ValueTypeUShortTest_155, CopyToBuffer_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(0x1234);
    byte buf[2] = {0};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
}

TEST_F(ValueTypeUShortTest_155, ReadFromBuffer_155) {
    ValueType<uint16_t> v;
    byte buf[4] = {0x01, 0x00, 0x02, 0x00}; // two uint16_t in little endian: 1, 2
    int rc = v.read(buf, 4, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeUShortTest_155, ReadFromString_155) {
    ValueType<uint16_t> v;
    int rc = v.read("10 20 30");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeUShortTest_155, SizeCorrect_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    EXPECT_EQ(v.size(), 4u); // 2 * sizeof(uint16_t)
}

TEST_F(ValueTypeUShortTest_155, DataAreaInitiallyEmpty_155) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

TEST_F(ValueTypeUShortTest_155, SetDataArea_155) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB, 0xCC};
    int rc = v.setDataArea(data, 3);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 3u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 3u);
}

TEST_F(ValueTypeUShortTest_155, CopyConstructor_155) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(5);
    v1.value_.push_back(10);
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 5);
    EXPECT_EQ(v2.toInt64(1), 10);
}

TEST_F(ValueTypeUShortTest_155, AssignmentOperator_155) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(5);
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 5);
}

// =============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// =============================================================================

class ValueTypeULongTest_155 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_155, DefaultConstructor_155) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.typeId(), unsignedLong);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_155, ToInt64_155) {
    ValueType<uint32_t> v;
    v.value_.push_back(4000000000u);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 4000000000LL);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeULongTest_155, ToUint32_155) {
    ValueType<uint32_t> v;
    v.value_.push_back(123456u);
    EXPECT_EQ(v.toUint32(0), 123456u);
}

TEST_F(ValueTypeULongTest_155, ReadFromString_155) {
    ValueType<uint32_t> v;
    v.read("100 200 300");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), 300);
}

// =============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// =============================================================================

class ValueTypeShortTest_155 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_155, NegativeValue_155) {
    ValueType<int16_t> v;
    v.value_.push_back(-100);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeShortTest_155, ZeroValue_155) {
    ValueType<int16_t> v;
    v.value_.push_back(0);
    EXPECT_EQ(v.toInt64(0), 0);
}

TEST_F(ValueTypeShortTest_155, MaxMinValues_155) {
    ValueType<int16_t> v;
    v.value_.push_back(32767);
    v.value_.push_back(-32768);
    EXPECT_EQ(v.toInt64(0), 32767);
    EXPECT_EQ(v.toInt64(1), -32768);
}

// =============================================================================
// Tests for ValueType<int32_t> (LongValue)
// =============================================================================

class ValueTypeLongTest_155 : public ::testing::Test {};

TEST_F(ValueTypeLongTest_155, NegativeValue_155) {
    ValueType<int32_t> v;
    v.value_.push_back(-2000000000);
    EXPECT_EQ(v.toInt64(0), -2000000000LL);
}

TEST_F(ValueTypeLongTest_155, ToFloat_155) {
    ValueType<int32_t> v;
    v.value_.push_back(42);
    EXPECT_FLOAT_EQ(v.toFloat(0), 42.0f);
}

// =============================================================================
// Tests for ValueType<Rational>
// =============================================================================

class ValueTypeRationalTest_155 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_155, DefaultConstructor_155) {
    ValueType<Rational> v;
    EXPECT_EQ(v.typeId(), signedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_155, ToInt64_155) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(10, 3));
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3); // 10/3 = 3
}

TEST_F(ValueTypeRationalTest_155, ToInt64ZeroDenominator_155) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(10, 0));
    v.toInt64(0);
    EXPECT_FALSE(v.ok());
}

TEST_F(ValueTypeRationalTest_155, ToFloat_155) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 2));
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_155, ToFloatZeroDenominator_155) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 0));
    v.toFloat(0);
    EXPECT_FALSE(v.ok());
}

TEST_F(ValueTypeRationalTest_155, ToRational_155) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(3, 7));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_155, NegativeRational_155) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(-5, 2));
    EXPECT_EQ(v.toInt64(0), -2); // -5/2 = -2
    EXPECT_FLOAT_EQ(v.toFloat(0), -2.5f);
}

TEST_F(ValueTypeRationalTest_155, ToUint32ZeroDenominator_155) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(5, 0));
    v.toUint32(0);
    EXPECT_FALSE(v.ok());
}

TEST_F(ValueTypeRationalTest_155, ReadFromString_155) {
    ValueType<Rational> v;
    int rc = v.read("1/2 3/4");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    Rational r0 = v.toRational(0);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 2);
    Rational r1 = v.toRational(1);
    EXPECT_EQ(r1.first, 3);
    EXPECT_EQ(r1.second, 4);
}

// =============================================================================
// Tests for ValueType<URational>
// =============================================================================

class ValueTypeURationalTest_155 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_155, DefaultConstructor_155) {
    ValueType<URational> v;
    EXPECT_EQ(v.typeId(), unsignedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeURationalTest_155, ToInt64_155) {
    ValueType<URational> v;
    v.value_.push_back(URational(10, 3));
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeURationalTest_155, ToInt64ZeroDenominator_155) {
    ValueType<URational> v;
    v.value_.push_back(URational(10, 0));
    v.toInt64(0);
    EXPECT_FALSE(v.ok());
}

TEST_F(ValueTypeURationalTest_155, ToFloat_155) {
    ValueType<URational> v;
    v.value_.push_back(URational(3, 4));
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.75f);
}

TEST_F(ValueTypeURationalTest_155, ToRational_155) {
    ValueType<URational> v;
    v.value_.push_back(URational(5, 8));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 8);
}

TEST_F(ValueTypeURationalTest_155, ToUint32_155) {
    ValueType<URational> v;
    v.value_.push_back(URational(22, 7));
    EXPECT_EQ(v.toUint32(0), 3u);
}

// =============================================================================
// Tests for ValueType<float>
// =============================================================================

class ValueTypeFloatTest_155 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_155, DefaultConstructor_155) {
    ValueType<float> v;
    EXPECT_EQ(v.typeId(), tiffFloat);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_155, ToInt64Normal_155) {
    ValueType<float> v;
    v.value_.push_back(3.7f);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3); // truncation
}

TEST_F(ValueTypeFloatTest_155, ToInt64Negative_155) {
    ValueType<float> v;
    v.value_.push_back(-3.7f);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, -3);
}

TEST_F(ValueTypeFloatTest_155, ToUint32_155) {
    ValueType<float> v;
    v.value_.push_back(42.9f);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 42u);
}

TEST_F(ValueTypeFloatTest_155, ToFloat_155) {
    ValueType<float> v;
    v.value_.push_back(1.5f);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
}

TEST_F(ValueTypeFloatTest_155, ToRational_155) {
    ValueType<float> v;
    v.value_.push_back(0.5f);
    Rational r = v.toRational(0);
    // The rational should approximate 0.5
    if (r.second != 0) {
        float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(approx, 0.5f, 0.01f);
    }
}

TEST_F(ValueTypeFloatTest_155, ConstructorWithValue_155) {
    ValueType<float> v(1.23f);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.23f);
}

// =============================================================================
// Tests for ValueType<double>
// =============================================================================

class ValueTypeDoubleTest_155 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_155, DefaultConstructor_155) {
    ValueType<double> v;
    EXPECT_EQ(v.typeId(), tiffDouble);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_155, ToInt64_155) {
    ValueType<double> v;
    v.value_.push_back(99.9);
    EXPECT_EQ(v.toInt64(0), 99);
}

TEST_F(ValueTypeDoubleTest_155, ToUint32_155) {
    ValueType<double> v;
    v.value_.push_back(55.1);
    EXPECT_EQ(v.toUint32(0), 55u);
}

TEST_F(ValueTypeDoubleTest_155, ToFloat_155) {
    ValueType<double> v;
    v.value_.push_back(3.14);
    EXPECT_NEAR(v.toFloat(0), 3.14f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_155, ToRational_155) {
    ValueType<double> v;
    v.value_.push_back(0.25);
    Rational r = v.toRational(0);
    if (r.second != 0) {
        double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(approx, 0.25, 0.01);
    }
}

TEST_F(ValueTypeDoubleTest_155, NegativeToInt64_155) {
    ValueType<double> v;
    v.value_.push_back(-99.9);
    EXPECT_EQ(v.toInt64(0), -99);
}

// =============================================================================
// Tests for boundary / edge cases
// =============================================================================

class ValueTypeBoundaryTest_155 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_155, EmptyValueToInt64Throws_155) {
    ValueType<uint16_t> v;
    EXPECT_THROW(v.toInt64(0), std::out_of_range);
}

TEST_F(ValueTypeBoundaryTest_155, EmptyValueToUint32Throws_155) {
    ValueType<uint32_t> v;
    EXPECT_THROW(v.toUint32(0), std::out_of_range);
}

TEST_F(ValueTypeBoundaryTest_155, EmptyValueToFloatThrows_155) {
    ValueType<float> v;
    EXPECT_THROW(v.toFloat(0), std::out_of_range);
}

TEST_F(ValueTypeBoundaryTest_155, EmptyValueToRationalThrows_155) {
    ValueType<int32_t> v;
    EXPECT_THROW(v.toRational(0), std::out_of_range);
}

TEST_F(ValueTypeBoundaryTest_155, SingleElementAccessAtZero_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    EXPECT_EQ(v.toInt64(0), 42);
    EXPECT_THROW(v.toInt64(1), std::out_of_range);
}

TEST_F(ValueTypeBoundaryTest_155, OkFlagAfterValidConversion_155) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.toInt64(0);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeBoundaryTest_155, LargeNumberOfElements_155) {
    ValueType<uint16_t> v;
    for (uint16_t i = 0; i < 1000; ++i) {
        v.value_.push_back(i);
    }
    EXPECT_EQ(v.count(), 1000u);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_EQ(v.toInt64(999), 999);
    EXPECT_THROW(v.toInt64(1000), std::out_of_range);
}

// =============================================================================
// Tests for Value::create factory
// =============================================================================

class ValueCreateTest_155 : public ::testing::Test {};

TEST_F(ValueCreateTest_155, CreateUnsignedShort_155) {
    auto v = Value::create(unsignedShort);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}

TEST_F(ValueCreateTest_155, CreateUnsignedLong_155) {
    auto v = Value::create(unsignedLong);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedLong);
}

TEST_F(ValueCreateTest_155, CreateSignedRational_155) {
    auto v = Value::create(signedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), signedRational);
}

TEST_F(ValueCreateTest_155, CreateUnsignedRational_155) {
    auto v = Value::create(unsignedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedRational);
}

// =============================================================================
// Tests for read from binary buffer with different byte orders
// =============================================================================

class ValueTypeByteOrderTest_155 : public ::testing::Test {};

TEST_F(ValueTypeByteOrderTest_155, ReadLittleEndian_155) {
    ValueType<uint16_t> v;
    byte buf[] = {0x34, 0x12}; // 0x1234 in little endian
    v.read(buf, 2, littleEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 0x1234);
}

TEST_F(ValueTypeByteOrderTest_155, ReadBigEndian_155) {
    ValueType<uint16_t> v;
    byte buf[] = {0x12, 0x34}; // 0x1234 in big endian
    v.read(buf, 2, bigEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 0x1234);
}

TEST_F(ValueTypeByteOrderTest_155, ReadUint32LittleEndian_155) {
    ValueType<uint32_t> v;
    byte buf[] = {0x78, 0x56, 0x34, 0x12}; // 0x12345678 LE
    v.read(buf, 4, littleEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 0x12345678);
}

TEST_F(ValueTypeByteOrderTest_155, ReadUint32BigEndian_155) {
    ValueType<uint32_t> v;
    byte buf[] = {0x12, 0x34, 0x56, 0x78}; // 0x12345678 BE
    v.read(buf, 4, bigEndian);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 0x12345678);
}

// =============================================================================
// Tests for copy and write roundtrip
// =============================================================================

class ValueTypeRoundtripTest_155 : public ::testing::Test {};

TEST_F(ValueTypeRoundtripTest_155, CopyAndReadBackUShort_155) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(0x1234);
    v1.value_.push_back(0x5678);

    byte buf[4] = {};
    size_t sz = v1.copy(buf, littleEndian);
    EXPECT_EQ(sz, 4u);

    ValueType<uint16_t> v2;
    v2.read(buf, 4, littleEndian);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toInt64(0), 0x1234);
    EXPECT_EQ(v2.toInt64(1), 0x5678);
}

TEST_F(ValueTypeRoundtripTest_155, CopyAndReadBackULong_155) {
    ValueType<uint32_t> v1;
    v1.value_.push_back(0xDEADBEEF);

    byte buf[4] = {};
    size_t sz = v1.copy(buf, bigEndian);
    EXPECT_EQ(sz, 4u);

    ValueType<uint32_t> v2;
    v2.read(buf, 4, bigEndian);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toUint32(0), 0xDEADBEEF);
}

// =============================================================================
// Tests for toString
// =============================================================================

class ValueTypeToStringTest_155 : public ::testing::Test {};

TEST_F(ValueTypeToStringTest_155, RationalToString_155) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 3));
    std::string s = v.toString(0);
    EXPECT_EQ(s, "1/3");
}

TEST_F(ValueTypeToStringTest_155, URationalToString_155) {
    ValueType<URational> v;
    v.value_.push_back(URational(7, 11));
    std::string s = v.toString(0);
    EXPECT_EQ(s, "7/11");
}

TEST_F(ValueTypeToStringTest_155, IntToString_155) {
    ValueType<int32_t> v;
    v.value_.push_back(-42);
    std::string s = v.toString(0);
    EXPECT_EQ(s, "-42");
}

// =============================================================================
// Tests for data area operations
// =============================================================================

class ValueTypeDataAreaTest_155 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_155, SetAndGetDataArea_155) {
    ValueType<uint16_t> v;
    byte data[] = {1, 2, 3, 4, 5};
    int rc = v.setDataArea(data, 5);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 5u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 5u);
    EXPECT_EQ(db.data()[0], 1);
    EXPECT_EQ(db.data()[4], 5);
}

TEST_F(ValueTypeDataAreaTest_155, OverwriteDataArea_155) {
    ValueType<uint16_t> v;
    byte data1[] = {0xAA, 0xBB};
    v.setDataArea(data1, 2);
    EXPECT_EQ(v.sizeDataArea(), 2u);

    byte data2[] = {0xCC, 0xDD, 0xEE};
    v.setDataArea(data2, 3);
    EXPECT_EQ(v.sizeDataArea(), 3u);
}

TEST_F(ValueTypeDataAreaTest_155, EmptyDataArea_155) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 0u);
}
