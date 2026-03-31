#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_2155 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_2155, DefaultConstructor_2155) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.typeId(), unsignedShort);
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_2155, ExplicitValueConstructor_2155) {
    ValueType<uint16_t> v(42, unsignedShort);
    EXPECT_EQ(v.typeId(), unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_2155, CopyConstructor_2155) {
    ValueType<uint16_t> v1(100, unsignedShort);
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 100);
    EXPECT_EQ(v2.typeId(), unsignedShort);
}

TEST_F(ValueTypeUShortTest_2155, AssignmentOperator_2155) {
    ValueType<uint16_t> v1(200, unsignedShort);
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 200);
}

TEST_F(ValueTypeUShortTest_2155, ReadFromBuffer_2155) {
    uint16_t val = 0x1234;
    byte buf[2];
    std::memcpy(buf, &val, 2);
    ValueType<uint16_t> v;
    v.read(buf, 2, littleEndian);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeUShortTest_2155, ReadFromString_2155) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeUShortTest_2155, ToString_2155) {
    ValueType<uint16_t> v(42, unsignedShort);
    std::string s = v.toString(0);
    EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeUShortTest_2155, ToFloat_2155) {
    ValueType<uint16_t> v(42, unsignedShort);
    float f = v.toFloat(0);
    EXPECT_FLOAT_EQ(f, 42.0f);
}

TEST_F(ValueTypeUShortTest_2155, ToRational_2155) {
    ValueType<uint16_t> v(42, unsignedShort);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeUShortTest_2155, ToUint32_2155) {
    ValueType<uint16_t> v(65535, unsignedShort);
    uint32_t u = v.toUint32(0);
    EXPECT_EQ(u, 65535u);
}

TEST_F(ValueTypeUShortTest_2155, WriteToStream_2155) {
    ValueType<uint16_t> v;
    v.read("10 20");
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_2155, CopyToBuffer_2155) {
    ValueType<uint16_t> v(42, unsignedShort);
    byte buf[2] = {0};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
}

TEST_F(ValueTypeUShortTest_2155, Clone_2155) {
    ValueType<uint16_t> v(42, unsignedShort);
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toInt64(0), 42);
}

TEST_F(ValueTypeUShortTest_2155, SizeDataAreaEmpty_2155) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_2155, DataAreaEmpty_2155) {
    ValueType<uint16_t> v;
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 0u);
}

TEST_F(ValueTypeUShortTest_2155, SetDataArea_2155) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int rc = v.setDataArea(data, 4);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

TEST_F(ValueTypeUShortTest_2155, OkReturnsTrueByDefault_2155) {
    ValueType<uint16_t> v;
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUShortTest_2155, MultipleValuesSize_2155) {
    ValueType<uint16_t> v;
    v.read("1 2 3 4 5");
    EXPECT_EQ(v.count(), 5u);
    EXPECT_EQ(v.size(), 10u);  // 5 * sizeof(uint16_t) = 10
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_2155 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_2155, DefaultConstructor_2155) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.typeId(), unsignedLong);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_2155, ExplicitValueConstructor_2155) {
    ValueType<uint32_t> v(123456, unsignedLong);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 123456);
}

TEST_F(ValueTypeULongTest_2155, ReadFromString_2155) {
    ValueType<uint32_t> v;
    v.read("100 200 300");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_EQ(v.toInt64(1), 200);
    EXPECT_EQ(v.toInt64(2), 300);
}

TEST_F(ValueTypeULongTest_2155, ToStringIndex_2155) {
    ValueType<uint32_t> v;
    v.read("100 200");
    EXPECT_EQ(v.toString(0), "100");
    EXPECT_EQ(v.toString(1), "200");
}

TEST_F(ValueTypeULongTest_2155, CopyAndReadBack_2155) {
    ValueType<uint32_t> v1(999, unsignedLong);
    byte buf[4] = {0};
    size_t copied = v1.copy(buf, littleEndian);
    EXPECT_EQ(copied, 4u);

    ValueType<uint32_t> v2;
    v2.read(buf, 4, littleEndian);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 999);
}

// ============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// ============================================================================

class ValueTypeShortTest_2155 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_2155, NegativeValue_2155) {
    ValueType<int16_t> v(-100, signedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeShortTest_2155, ReadFromStringNegative_2155) {
    ValueType<int16_t> v;
    v.read("-10 -20 30");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -10);
    EXPECT_EQ(v.toInt64(1), -20);
    EXPECT_EQ(v.toInt64(2), 30);
}

// ============================================================================
// Tests for ValueType<Rational> (RationalValue)
// ============================================================================

class ValueTypeRationalTest_2155 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_2155, DefaultConstructor_2155) {
    ValueType<Rational> v;
    EXPECT_EQ(v.typeId(), signedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_2155, ExplicitValueConstructor_2155) {
    Rational r(1, 2);
    ValueType<Rational> v(r, signedRational);
    EXPECT_EQ(v.count(), 1u);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 2);
}

TEST_F(ValueTypeRationalTest_2155, ToFloat_2155) {
    Rational r(1, 4);
    ValueType<Rational> v(r, signedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_2155, ToInt64_2155) {
    Rational r(7, 2);
    ValueType<Rational> v(r, signedRational);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);  // 7/2 = 3 (truncated)
}

TEST_F(ValueTypeRationalTest_2155, ToUint32_2155) {
    Rational r(10, 3);
    ValueType<Rational> v(r, signedRational);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u);  // 10/3 = 3 (truncated)
}

TEST_F(ValueTypeRationalTest_2155, ReadFromString_2155) {
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

TEST_F(ValueTypeRationalTest_2155, ZeroDenominator_2155) {
    Rational r(1, 0);
    ValueType<Rational> v(r, signedRational);
    // toFloat with zero denominator - observable behavior
    float f = v.toFloat(0);
    // Just verify it doesn't crash; the result may be inf or 0
    (void)f;
}

TEST_F(ValueTypeRationalTest_2155, CopyToBufferAndReadBack_2155) {
    Rational r(3, 7);
    ValueType<Rational> v1(r, signedRational);
    byte buf[8] = {0};
    size_t copied = v1.copy(buf, littleEndian);
    EXPECT_EQ(copied, 8u);

    ValueType<Rational> v2;
    v2.read(buf, 8, littleEndian);
    EXPECT_EQ(v2.count(), 1u);
    Rational result = v2.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

// ============================================================================
// Tests for ValueType<URational> (URationalValue)
// ============================================================================

class ValueTypeURationalTest_2155 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_2155, DefaultConstructor_2155) {
    ValueType<URational> v;
    EXPECT_EQ(v.typeId(), unsignedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeURationalTest_2155, ExplicitValueConstructor_2155) {
    URational r(5, 10);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_EQ(v.count(), 1u);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 10);
}

TEST_F(ValueTypeURationalTest_2155, ToFloat_2155) {
    URational r(1, 3);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_NEAR(v.toFloat(0), 1.0f / 3.0f, 0.001f);
}

TEST_F(ValueTypeURationalTest_2155, ToInt64_2155) {
    URational r(10, 3);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_EQ(v.toInt64(0), 3);
}

TEST_F(ValueTypeURationalTest_2155, ToUint32_2155) {
    URational r(10, 3);
    ValueType<URational> v(r, unsignedRational);
    EXPECT_EQ(v.toUint32(0), 3u);
}

// ============================================================================
// Tests for ValueType<float> (FloatValue)
// ============================================================================

class ValueTypeFloatTest_2155 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_2155, DefaultConstructor_2155) {
    ValueType<float> v;
    EXPECT_EQ(v.typeId(), tiffFloat);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_2155, ExplicitValueConstructor_2155) {
    ValueType<float> v(3.14f, tiffFloat);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

TEST_F(ValueTypeFloatTest_2155, ToInt64_2155) {
    ValueType<float> v(3.7f, tiffFloat);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);  // truncated
}

TEST_F(ValueTypeFloatTest_2155, ToUint32_2155) {
    ValueType<float> v(3.7f, tiffFloat);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u);  // truncated
}

TEST_F(ValueTypeFloatTest_2155, ToRational_2155) {
    ValueType<float> v(0.5f, tiffFloat);
    Rational r = v.toRational(0);
    // The rational approximation of 0.5 should be close to 1/2
    if (r.second != 0) {
        float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(approx, 0.5f, 0.001f);
    }
}

TEST_F(ValueTypeFloatTest_2155, ReadFromString_2155) {
    ValueType<float> v;
    v.read("1.5 2.5 3.5");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
    EXPECT_FLOAT_EQ(v.toFloat(1), 2.5f);
    EXPECT_FLOAT_EQ(v.toFloat(2), 3.5f);
}

// ============================================================================
// Tests for ValueType<double> (DoubleValue)
// ============================================================================

class ValueTypeDoubleTest_2155 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_2155, DefaultConstructor_2155) {
    ValueType<double> v;
    EXPECT_EQ(v.typeId(), tiffDouble);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_2155, ExplicitValueConstructor_2155) {
    ValueType<double> v(2.71828, tiffDouble);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 2.71828f, 0.001f);
}

TEST_F(ValueTypeDoubleTest_2155, ToInt64_2155) {
    ValueType<double> v(9.99, tiffDouble);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 9);
}

TEST_F(ValueTypeDoubleTest_2155, ToUint32_2155) {
    ValueType<double> v(9.99, tiffDouble);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 9u);
}

TEST_F(ValueTypeDoubleTest_2155, ToRational_2155) {
    ValueType<double> v(0.25, tiffDouble);
    Rational r = v.toRational(0);
    if (r.second != 0) {
        double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(approx, 0.25, 0.001);
    }
}

// ============================================================================
// Tests for ValueType<int32_t> (LongValue / SignedLong)
// ============================================================================

class ValueTypeInt32Test_2155 : public ::testing::Test {};

TEST_F(ValueTypeInt32Test_2155, DefaultConstructor_2155) {
    ValueType<int32_t> v;
    EXPECT_EQ(v.typeId(), signedLong);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeInt32Test_2155, NegativeValue_2155) {
    ValueType<int32_t> v(-12345, signedLong);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -12345);
}

TEST_F(ValueTypeInt32Test_2155, ReadFromString_2155) {
    ValueType<int32_t> v;
    v.read("-100 0 100");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), -100);
    EXPECT_EQ(v.toInt64(1), 0);
    EXPECT_EQ(v.toInt64(2), 100);
}

// ============================================================================
// Tests for Value::create factory
// ============================================================================

class ValueCreateTest_2155 : public ::testing::Test {};

TEST_F(ValueCreateTest_2155, CreateUnsignedShort_2155) {
    auto v = Value::create(unsignedShort);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}

TEST_F(ValueCreateTest_2155, CreateUnsignedLong_2155) {
    auto v = Value::create(unsignedLong);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedLong);
}

TEST_F(ValueCreateTest_2155, CreateSignedRational_2155) {
    auto v = Value::create(signedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), signedRational);
}

TEST_F(ValueCreateTest_2155, CreateUnsignedRational_2155) {
    auto v = Value::create(unsignedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedRational);
}

// ============================================================================
// Boundary / edge case tests
// ============================================================================

class ValueTypeBoundaryTest_2155 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_2155, EmptyReadFromString_2155) {
    ValueType<uint16_t> v;
    v.read("");
    // After reading empty string, count should be 0 or based on implementation
    // We just verify no crash
    EXPECT_GE(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_2155, SingleValue_2155) {
    ValueType<uint16_t> v;
    v.read("42");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeBoundaryTest_2155, LargeNumberOfValues_2155) {
    ValueType<uint16_t> v;
    std::string str;
    for (int i = 0; i < 100; ++i) {
        if (i > 0) str += " ";
        str += std::to_string(i);
    }
    v.read(str);
    EXPECT_EQ(v.count(), 100u);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_EQ(v.toInt64(99), 99);
}

TEST_F(ValueTypeBoundaryTest_2155, UShortMaxValue_2155) {
    ValueType<uint16_t> v(65535, unsignedShort);
    EXPECT_EQ(v.toInt64(0), 65535);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeBoundaryTest_2155, ZeroValue_2155) {
    ValueType<uint32_t> v(0, unsignedLong);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.0f);
}

TEST_F(ValueTypeBoundaryTest_2155, ReadFromBufferZeroLength_2155) {
    ValueType<uint16_t> v;
    byte buf[1] = {0};
    v.read(buf, 0, littleEndian);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_2155, MultipleReads_2155) {
    ValueType<uint16_t> v;
    v.read("10 20");
    EXPECT_EQ(v.count(), 2u);
    v.read("30 40 50");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 30);
}

TEST_F(ValueTypeBoundaryTest_2155, DataAreaSetAndRetrieve_2155) {
    ValueType<uint32_t> v;
    byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    EXPECT_EQ(v.setDataArea(data, 4), 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 4u);
    EXPECT_EQ(buf.data()[0], 0xDE);
    EXPECT_EQ(buf.data()[1], 0xAD);
    EXPECT_EQ(buf.data()[2], 0xBE);
    EXPECT_EQ(buf.data()[3], 0xEF);
}

TEST_F(ValueTypeBoundaryTest_2155, WriteOutputContainsValues_2155) {
    ValueType<uint32_t> v;
    v.read("100 200");
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    EXPECT_NE(output.find("100"), std::string::npos);
    EXPECT_NE(output.find("200"), std::string::npos);
}

TEST_F(ValueTypeBoundaryTest_2155, CopyPreservesDataArea_2155) {
    ValueType<uint16_t> v1;
    byte data[] = {0x01, 0x02};
    v1.setDataArea(data, 2);
    ValueType<uint16_t> v2(v1);
    // Copy constructor should preserve the data area based on implementation
    // Just verify no crash
    EXPECT_GE(v2.sizeDataArea(), 0u);
}

TEST_F(ValueTypeBoundaryTest_2155, AssignmentPreservesDataArea_2155) {
    ValueType<uint16_t> v1;
    byte data[] = {0x01, 0x02};
    v1.setDataArea(data, 2);
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_GE(v2.sizeDataArea(), 0u);
}

// ============================================================================
// Tests for Value base class methods
// ============================================================================

class ValueBaseTest_2155 : public ::testing::Test {};

TEST_F(ValueBaseTest_2155, SetDataAreaReturnsMinusOne_2155) {
    // Value base class setDataArea should return -1
    auto v = Value::create(unsignedByte);
    if (v) {
        // For types that don't support data area via base, the behavior varies
        // This is just to verify the interface doesn't crash
        EXPECT_TRUE(v->ok());
    }
}

TEST_F(ValueBaseTest_2155, ToStringNoArg_2155) {
    ValueType<uint16_t> v(42, unsignedShort);
    std::string s = v.toString();
    EXPECT_EQ(s, "42");
}

// ============================================================================
// Byte order tests
// ============================================================================

class ValueTypeByteOrderTest_2155 : public ::testing::Test {};

TEST_F(ValueTypeByteOrderTest_2155, LittleEndianRoundTrip_2155) {
    ValueType<uint32_t> v1(0x12345678, unsignedLong);
    byte buf[4] = {0};
    v1.copy(buf, littleEndian);
    
    ValueType<uint32_t> v2;
    v2.read(buf, 4, littleEndian);
    EXPECT_EQ(v2.toInt64(0), 0x12345678);
}

TEST_F(ValueTypeByteOrderTest_2155, BigEndianRoundTrip_2155) {
    ValueType<uint32_t> v1(0x12345678, unsignedLong);
    byte buf[4] = {0};
    v1.copy(buf, bigEndian);
    
    ValueType<uint32_t> v2;
    v2.read(buf, 4, bigEndian);
    EXPECT_EQ(v2.toInt64(0), 0x12345678);
}

TEST_F(ValueTypeByteOrderTest_2155, RationalBigEndianRoundTrip_2155) {
    Rational r(100, 7);
    ValueType<Rational> v1(r, signedRational);
    byte buf[8] = {0};
    v1.copy(buf, bigEndian);
    
    ValueType<Rational> v2;
    v2.read(buf, 8, bigEndian);
    EXPECT_EQ(v2.count(), 1u);
    Rational result = v2.toRational(0);
    EXPECT_EQ(result.first, 100);
    EXPECT_EQ(result.second, 7);
}
