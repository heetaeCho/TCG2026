#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cstdint>
#include <sstream>
#include <stdexcept>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================

class ValueTypeUShortTest_156 : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(ValueTypeUShortTest_156, DefaultConstructor_156) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.typeId(), getType<uint16_t>());
}

TEST_F(ValueTypeUShortTest_156, ConstructWithSingleValue_156) {
    ValueType<uint16_t> v(42, getType<uint16_t>());
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeUShortTest_156, ToUint32ReturnsCorrectValue_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(100);
    v.value_.push_back(200);
    v.value_.push_back(300);
    EXPECT_EQ(v.toUint32(0), 100u);
    EXPECT_EQ(v.toUint32(1), 200u);
    EXPECT_EQ(v.toUint32(2), 300u);
}

TEST_F(ValueTypeUShortTest_156, ToUint32OutOfRangeThrows_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    EXPECT_THROW(v.toUint32(1), std::out_of_range);
}

TEST_F(ValueTypeUShortTest_156, ToUint32EmptyThrows_156) {
    ValueType<uint16_t> v;
    EXPECT_THROW(v.toUint32(0), std::out_of_range);
}

TEST_F(ValueTypeUShortTest_156, CountReturnsNumberOfElements_156) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    v.value_.push_back(1);
    EXPECT_EQ(v.count(), 1u);
    v.value_.push_back(2);
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeUShortTest_156, ToInt64ReturnsCorrectValue_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(65535);
    EXPECT_EQ(v.toInt64(0), 65535);
}

TEST_F(ValueTypeUShortTest_156, ToFloatReturnsCorrectValue_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(123);
    EXPECT_FLOAT_EQ(v.toFloat(0), 123.0f);
}

TEST_F(ValueTypeUShortTest_156, ToStringReturnsCorrectValue_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    EXPECT_EQ(v.toString(0), "42");
}

TEST_F(ValueTypeUShortTest_156, CopyConstructor_156) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(10);
    v1.value_.push_back(20);
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toUint32(0), 10u);
    EXPECT_EQ(v2.toUint32(1), 20u);
}

TEST_F(ValueTypeUShortTest_156, AssignmentOperator_156) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(10);
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toUint32(0), 10u);
}

TEST_F(ValueTypeUShortTest_156, Clone_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(99);
    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->toUint32(0), 99u);
}

TEST_F(ValueTypeUShortTest_156, WriteToStream_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_156, ReadFromString_156) {
    ValueType<uint16_t> v;
    int ret = v.read("100 200 300");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toUint32(0), 100u);
    EXPECT_EQ(v.toUint32(1), 200u);
    EXPECT_EQ(v.toUint32(2), 300u);
}

TEST_F(ValueTypeUShortTest_156, SizeReturnsCorrectBytes_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    // Each uint16_t is 2 bytes
    EXPECT_EQ(v.size(), 4u);
}

TEST_F(ValueTypeUShortTest_156, OkAfterToUint32_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(5);
    v.toUint32(0);
    EXPECT_TRUE(v.ok());
}

// ============================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================

class ValueTypeULongTest_156 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_156, DefaultConstructor_156) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_156, ToUint32_156) {
    ValueType<uint32_t> v;
    v.value_.push_back(0xFFFFFFFF);
    EXPECT_EQ(v.toUint32(0), 0xFFFFFFFF);
}

TEST_F(ValueTypeULongTest_156, ToInt64_156) {
    ValueType<uint32_t> v;
    v.value_.push_back(0xFFFFFFFF);
    EXPECT_EQ(v.toInt64(0), static_cast<int64_t>(0xFFFFFFFF));
}

TEST_F(ValueTypeULongTest_156, ReadFromBuffer_156) {
    ValueType<uint32_t> v;
    uint32_t data[] = {0x01020304, 0x05060708};
    int ret = v.read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.count(), 2u);
}

// ============================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================

class ValueTypeShortTest_156 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_156, NegativeValueToUint32_156) {
    ValueType<int16_t> v;
    v.value_.push_back(-1);
    // static_cast<uint32_t>(-1) wraps around
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, static_cast<uint32_t>(static_cast<int16_t>(-1)));
}

TEST_F(ValueTypeShortTest_156, ToInt64NegativeValue_156) {
    ValueType<int16_t> v;
    v.value_.push_back(-100);
    EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeShortTest_156, ToRational_156) {
    ValueType<int16_t> v;
    v.value_.push_back(42);
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    // The rational should represent 42
    if (r.second != 0) {
        EXPECT_FLOAT_EQ(static_cast<float>(r.first) / r.second, 42.0f);
    }
}

// ============================================================
// Tests for ValueType<Rational>
// ============================================================

class ValueTypeRationalTest_156 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_156, ToFloat_156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 2));
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_156, ToFloat_ZeroDenominator_156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 0));
    // Division by zero - behavior may vary, just ensure no crash
    float result = v.toFloat(0);
    (void)result;  // Just checking it doesn't crash
}

TEST_F(ValueTypeRationalTest_156, ToInt64_156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(10, 3));
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);  // 10/3 = 3 (integer division)
}

TEST_F(ValueTypeRationalTest_156, ToUint32_156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(7, 2));
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u);  // 7/2 = 3 (integer division)
}

TEST_F(ValueTypeRationalTest_156, ToRational_156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(3, 7));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_156, Count_156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 2));
    v.value_.push_back(Rational(3, 4));
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeRationalTest_156, OutOfRangeThrows_156) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 2));
    EXPECT_THROW(v.toUint32(5), std::out_of_range);
}

// ============================================================
// Tests for ValueType<URational>
// ============================================================

class ValueTypeURationalTest_156 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_156, ToFloat_156) {
    ValueType<URational> v;
    v.value_.push_back(URational(3, 4));
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.75f);
}

TEST_F(ValueTypeURationalTest_156, ToInt64_156) {
    ValueType<URational> v;
    v.value_.push_back(URational(9, 2));
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 4);  // 9/2 = 4
}

TEST_F(ValueTypeURationalTest_156, ToUint32_156) {
    ValueType<URational> v;
    v.value_.push_back(URational(100, 10));
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 10u);
}

TEST_F(ValueTypeURationalTest_156, ToRational_156) {
    ValueType<URational> v;
    v.value_.push_back(URational(5, 3));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 3);
}

// ============================================================
// Tests for ValueType<float>
// ============================================================

class ValueTypeFloatTest_156 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_156, ToUint32_156) {
    ValueType<float> v;
    v.value_.push_back(3.7f);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u);  // truncation expected
}

TEST_F(ValueTypeFloatTest_156, ToInt64_156) {
    ValueType<float> v;
    v.value_.push_back(-2.5f);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, -2);
}

TEST_F(ValueTypeFloatTest_156, ToFloat_156) {
    ValueType<float> v;
    v.value_.push_back(1.5f);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
}

TEST_F(ValueTypeFloatTest_156, ToRational_156) {
    ValueType<float> v;
    v.value_.push_back(0.5f);
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.5, 0.001);
    }
}

TEST_F(ValueTypeFloatTest_156, ZeroValue_156) {
    ValueType<float> v;
    v.value_.push_back(0.0f);
    EXPECT_EQ(v.toUint32(0), 0u);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.0f);
}

// ============================================================
// Tests for ValueType<double>
// ============================================================

class ValueTypeDoubleTest_156 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_156, ToUint32_156) {
    ValueType<double> v;
    v.value_.push_back(255.9);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 255u);
}

TEST_F(ValueTypeDoubleTest_156, ToInt64_156) {
    ValueType<double> v;
    v.value_.push_back(-99.1);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, -99);
}

TEST_F(ValueTypeDoubleTest_156, ToFloat_156) {
    ValueType<double> v;
    v.value_.push_back(3.14159);
    EXPECT_NEAR(v.toFloat(0), 3.14159f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_156, ToRational_156) {
    ValueType<double> v;
    v.value_.push_back(0.25);
    Rational r = v.toRational(0);
    EXPECT_NE(r.second, 0);
    if (r.second != 0) {
        EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.25, 0.001);
    }
}

// ============================================================
// Tests for DataArea functionality
// ============================================================

class ValueTypeDataAreaTest_156 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_156, DefaultSizeDataAreaIsZero_156) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeDataAreaTest_156, SetAndGetDataArea_156) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int ret = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 4u);
}

TEST_F(ValueTypeDataAreaTest_156, EmptyDataArea_156) {
    ValueType<uint32_t> v;
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// ============================================================
// Tests for Value::create factory method
// ============================================================

class ValueCreateTest_156 : public ::testing::Test {};

TEST_F(ValueCreateTest_156, CreateUShortValue_156) {
    auto v = Value::create(unsignedShort);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}

TEST_F(ValueCreateTest_156, CreateULongValue_156) {
    auto v = Value::create(unsignedLong);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedLong);
}

TEST_F(ValueCreateTest_156, CreateURationalValue_156) {
    auto v = Value::create(unsignedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedRational);
}

TEST_F(ValueCreateTest_156, CreateSignedRationalValue_156) {
    auto v = Value::create(signedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), signedRational);
}

// ============================================================
// Tests for reading from byte buffer
// ============================================================

class ValueTypeReadBufferTest_156 : public ::testing::Test {};

TEST_F(ValueTypeReadBufferTest_156, ReadUShortLittleEndian_156) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x00, 0x02, 0x00};
    int ret = v.read(data, sizeof(data), littleEndian);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toUint32(0), 1u);
    EXPECT_EQ(v.toUint32(1), 2u);
}

TEST_F(ValueTypeReadBufferTest_156, ReadUShortBigEndian_156) {
    ValueType<uint16_t> v;
    byte data[] = {0x00, 0x01, 0x00, 0x02};
    int ret = v.read(data, sizeof(data), bigEndian);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toUint32(0), 1u);
    EXPECT_EQ(v.toUint32(1), 2u);
}

TEST_F(ValueTypeReadBufferTest_156, ReadEmptyBuffer_156) {
    ValueType<uint16_t> v;
    int ret = v.read(nullptr, 0, littleEndian);
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.count(), 0u);
}

// ============================================================
// Tests for copy to byte buffer
// ============================================================

class ValueTypeCopyTest_156 : public ::testing::Test {};

TEST_F(ValueTypeCopyTest_156, CopyUShortValues_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    byte buf[4] = {0};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);
}

TEST_F(ValueTypeCopyTest_156, CopyEmptyValue_156) {
    ValueType<uint16_t> v;
    byte buf[1] = {0};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 0u);
}

// ============================================================
// Tests for multiple elements read from string
// ============================================================

class ValueTypeReadStringTest_156 : public ::testing::Test {};

TEST_F(ValueTypeReadStringTest_156, ReadSingleValue_156) {
    ValueType<uint16_t> v;
    int ret = v.read("42");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeReadStringTest_156, ReadMultipleValues_156) {
    ValueType<int32_t> v;
    int ret = v.read("10 20 30");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeReadStringTest_156, ReadRationalFromString_156) {
    ValueType<Rational> v;
    int ret = v.read("1/2 3/4");
    EXPECT_EQ(ret, 0);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
    EXPECT_FLOAT_EQ(v.toFloat(1), 0.75f);
}

// ============================================================
// Boundary tests
// ============================================================

class ValueTypeBoundaryTest_156 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_156, MaxUint16Value_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(65535);
    EXPECT_EQ(v.toUint32(0), 65535u);
    EXPECT_EQ(v.toInt64(0), 65535);
}

TEST_F(ValueTypeBoundaryTest_156, MinInt16Value_156) {
    ValueType<int16_t> v;
    v.value_.push_back(-32768);
    EXPECT_EQ(v.toInt64(0), -32768);
}

TEST_F(ValueTypeBoundaryTest_156, ZeroValue_156) {
    ValueType<uint32_t> v;
    v.value_.push_back(0);
    EXPECT_EQ(v.toUint32(0), 0u);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.0f);
}

TEST_F(ValueTypeBoundaryTest_156, LargeNumberOfElements_156) {
    ValueType<uint16_t> v;
    for (uint16_t i = 0; i < 1000; ++i) {
        v.value_.push_back(i);
    }
    EXPECT_EQ(v.count(), 1000u);
    EXPECT_EQ(v.toUint32(0), 0u);
    EXPECT_EQ(v.toUint32(999), 999u);
}

TEST_F(ValueTypeBoundaryTest_156, SingleElementAccess_156) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    EXPECT_EQ(v.toUint32(0), 42u);
    EXPECT_THROW(v.toUint32(1), std::out_of_range);
}
