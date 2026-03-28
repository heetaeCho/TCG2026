#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// =============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// =============================================================================

class ValueTypeUShortTest_154 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeUShortTest_154, DefaultConstructor_154) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.typeId(), unsignedShort);
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUShortTest_154, ConstructorWithValue_154) {
    ValueType<uint16_t> v(42, unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toString(0), "42");
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUShortTest_154, ToStringValidIndex_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(100);
    v.value_.push_back(200);
    EXPECT_EQ(v.toString(0), "100");
    EXPECT_EQ(v.toString(1), "200");
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUShortTest_154, ToStringOutOfRange_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(100);
    EXPECT_THROW(v.toString(5), std::out_of_range);
}

TEST_F(ValueTypeUShortTest_154, ToStringEmptyValue_154) {
    ValueType<uint16_t> v;
    EXPECT_THROW(v.toString(0), std::out_of_range);
}

TEST_F(ValueTypeUShortTest_154, CountReturnsCorrectSize_154) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
    v.value_.push_back(1);
    v.value_.push_back(2);
    v.value_.push_back(3);
    EXPECT_EQ(v.count(), 3u);
}

TEST_F(ValueTypeUShortTest_154, ToInt64ValidIndex_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(12345);
    EXPECT_EQ(v.toInt64(0), 12345);
}

TEST_F(ValueTypeUShortTest_154, ToUint32ValidIndex_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(65535);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeUShortTest_154, ToFloatValidIndex_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(500);
    EXPECT_FLOAT_EQ(v.toFloat(0), 500.0f);
}

TEST_F(ValueTypeUShortTest_154, CopyAssignment_154) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(10);
    v1.value_.push_back(20);

    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 2u);
    EXPECT_EQ(v2.toString(0), "10");
    EXPECT_EQ(v2.toString(1), "20");
}

TEST_F(ValueTypeUShortTest_154, CopyConstructor_154) {
    ValueType<uint16_t> v1;
    v1.value_.push_back(55);
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toString(0), "55");
}

TEST_F(ValueTypeUShortTest_154, Clone_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(77);
    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toString(0), "77");
}

TEST_F(ValueTypeUShortTest_154, WriteToStream_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    std::ostringstream os;
    v.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(ValueTypeUShortTest_154, ReadFromByteBuffer_154) {
    ValueType<uint16_t> v;
    uint16_t data[] = {0x0001, 0x0002};
    // Read in little endian
    int rc = v.read(reinterpret_cast<const byte*>(data), sizeof(data), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeUShortTest_154, ReadFromString_154) {
    ValueType<uint16_t> v;
    int rc = v.read("100 200 300");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toString(0), "100");
    EXPECT_EQ(v.toString(1), "200");
    EXPECT_EQ(v.toString(2), "300");
}

TEST_F(ValueTypeUShortTest_154, SizeDataAreaEmpty_154) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUShortTest_154, SetDataArea_154) {
    ValueType<uint16_t> v;
    byte data[] = {0x01, 0x02, 0x03};
    int rc = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), sizeof(data));
}

TEST_F(ValueTypeUShortTest_154, DataAreaAfterSet_154) {
    ValueType<uint16_t> v;
    byte data[] = {0xAA, 0xBB};
    v.setDataArea(data, sizeof(data));
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), sizeof(data));
}

TEST_F(ValueTypeUShortTest_154, ToRational_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
}

// =============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// =============================================================================

class ValueTypeULongTest_154 : public ::testing::Test {};

TEST_F(ValueTypeULongTest_154, DefaultConstructor_154) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.typeId(), unsignedLong);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_154, ToStringValidIndex_154) {
    ValueType<uint32_t> v;
    v.value_.push_back(4294967295u);
    EXPECT_EQ(v.toString(0), "4294967295");
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeULongTest_154, ReadFromString_154) {
    ValueType<uint32_t> v;
    int rc = v.read("1000000 2000000");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeULongTest_154, ToInt64_154) {
    ValueType<uint32_t> v;
    v.value_.push_back(123456789);
    EXPECT_EQ(v.toInt64(0), 123456789);
}

// =============================================================================
// Tests for ValueType<int16_t> (ShortValue)
// =============================================================================

class ValueTypeShortTest_154 : public ::testing::Test {};

TEST_F(ValueTypeShortTest_154, NegativeValue_154) {
    ValueType<int16_t> v;
    v.value_.push_back(-100);
    EXPECT_EQ(v.toString(0), "-100");
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeShortTest_154, ToInt64Negative_154) {
    ValueType<int16_t> v;
    v.value_.push_back(-32768);
    EXPECT_EQ(v.toInt64(0), -32768);
}

// =============================================================================
// Tests for ValueType<Rational>
// =============================================================================

class ValueTypeRationalTest_154 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_154, DefaultConstructor_154) {
    ValueType<Rational> v;
    EXPECT_EQ(v.typeId(), signedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_154, ToStringValidIndex_154) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 3));
    std::string s = v.toString(0);
    EXPECT_FALSE(s.empty());
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeRationalTest_154, ToInt64_154) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(10, 2));
    EXPECT_EQ(v.toInt64(0), 5);
}

TEST_F(ValueTypeRationalTest_154, ToUint32_154) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(20, 4));
    EXPECT_EQ(v.toUint32(0), 5u);
}

TEST_F(ValueTypeRationalTest_154, ToFloat_154) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 4));
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_154, ToRational_154) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(3, 7));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
}

TEST_F(ValueTypeRationalTest_154, ZeroDenominator_154) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(1, 0));
    // toFloat with zero denominator - should not crash
    float f = v.toFloat(0);
    // Behavior is implementation-defined but should not crash
    (void)f;
}

TEST_F(ValueTypeRationalTest_154, ReadFromString_154) {
    ValueType<Rational> v;
    int rc = v.read("1/2 3/4");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeRationalTest_154, NegativeRational_154) {
    ValueType<Rational> v;
    v.value_.push_back(Rational(-5, 3));
    int64_t val = v.toInt64(0);
    EXPECT_EQ(val, -1);
}

// =============================================================================
// Tests for ValueType<URational>
// =============================================================================

class ValueTypeURationalTest_154 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_154, DefaultConstructor_154) {
    ValueType<URational> v;
    EXPECT_EQ(v.typeId(), unsignedRational);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeURationalTest_154, ToFloat_154) {
    ValueType<URational> v;
    v.value_.push_back(URational(3, 4));
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.75f);
}

TEST_F(ValueTypeURationalTest_154, ToRational_154) {
    ValueType<URational> v;
    v.value_.push_back(URational(5, 10));
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 10);
}

TEST_F(ValueTypeURationalTest_154, ToInt64_154) {
    ValueType<URational> v;
    v.value_.push_back(URational(100, 10));
    EXPECT_EQ(v.toInt64(0), 10);
}

TEST_F(ValueTypeURationalTest_154, ToUint32_154) {
    ValueType<URational> v;
    v.value_.push_back(URational(100, 10));
    EXPECT_EQ(v.toUint32(0), 10u);
}

// =============================================================================
// Tests for ValueType<float>
// =============================================================================

class ValueTypeFloatTest_154 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_154, DefaultConstructor_154) {
    ValueType<float> v;
    EXPECT_EQ(v.typeId(), tiffFloat);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeFloatTest_154, ToStringValidIndex_154) {
    ValueType<float> v;
    v.value_.push_back(3.14f);
    std::string s = v.toString(0);
    EXPECT_FALSE(s.empty());
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeFloatTest_154, ToInt64_154) {
    ValueType<float> v;
    v.value_.push_back(42.7f);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeFloatTest_154, ToUint32_154) {
    ValueType<float> v;
    v.value_.push_back(42.7f);
    EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeFloatTest_154, ToFloat_154) {
    ValueType<float> v;
    v.value_.push_back(1.5f);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
}

TEST_F(ValueTypeFloatTest_154, ToRational_154) {
    ValueType<float> v;
    v.value_.push_back(0.5f);
    Rational r = v.toRational(0);
    // The rational should approximate 0.5
    if (r.second != 0) {
        float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(approx, 0.5f, 0.001f);
    }
}

// =============================================================================
// Tests for ValueType<double>
// =============================================================================

class ValueTypeDoubleTest_154 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_154, DefaultConstructor_154) {
    ValueType<double> v;
    EXPECT_EQ(v.typeId(), tiffDouble);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_154, ToInt64_154) {
    ValueType<double> v;
    v.value_.push_back(99.9);
    EXPECT_EQ(v.toInt64(0), 99);
}

TEST_F(ValueTypeDoubleTest_154, ToUint32_154) {
    ValueType<double> v;
    v.value_.push_back(255.1);
    EXPECT_EQ(v.toUint32(0), 255u);
}

TEST_F(ValueTypeDoubleTest_154, ToFloat_154) {
    ValueType<double> v;
    v.value_.push_back(2.5);
    EXPECT_FLOAT_EQ(v.toFloat(0), 2.5f);
}

TEST_F(ValueTypeDoubleTest_154, ToRational_154) {
    ValueType<double> v;
    v.value_.push_back(0.25);
    Rational r = v.toRational(0);
    if (r.second != 0) {
        double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(approx, 0.25, 0.001);
    }
}

// =============================================================================
// Tests for Value::create factory
// =============================================================================

class ValueCreateTest_154 : public ::testing::Test {};

TEST_F(ValueCreateTest_154, CreateUnsignedShort_154) {
    auto v = Value::create(unsignedShort);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}

TEST_F(ValueCreateTest_154, CreateSignedRational_154) {
    auto v = Value::create(signedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), signedRational);
}

TEST_F(ValueCreateTest_154, CreateUnsignedRational_154) {
    auto v = Value::create(unsignedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedRational);
}

TEST_F(ValueCreateTest_154, CreateUnsignedLong_154) {
    auto v = Value::create(unsignedLong);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedLong);
}

// =============================================================================
// Tests for Value base class behavior
// =============================================================================

class ValueBaseTest_154 : public ::testing::Test {};

TEST_F(ValueBaseTest_154, OkInitiallyTrue_154) {
    ValueType<uint16_t> v;
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueBaseTest_154, ToStringDefaultNoArg_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(42);
    std::string s = v.toString();
    EXPECT_EQ(s, "42");
}

TEST_F(ValueBaseTest_154, TypeId_154) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.typeId(), unsignedShort);
}

// =============================================================================
// Tests for read/copy round-trip with byte buffer
// =============================================================================

class ValueTypeRoundTripTest_154 : public ::testing::Test {};

TEST_F(ValueTypeRoundTripTest_154, UShortReadCopyRoundTrip_154) {
    ValueType<uint16_t> v;
    byte input[4];
    // Little endian: 0x0100 = 256, 0x0200 = 512
    input[0] = 0x00; input[1] = 0x01;
    input[2] = 0x00; input[3] = 0x02;
    
    int rc = v.read(input, sizeof(input), bigEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 2u);
    
    byte output[4] = {};
    size_t copied = v.copy(output, bigEndian);
    EXPECT_EQ(copied, sizeof(input));
    EXPECT_EQ(memcmp(input, output, sizeof(input)), 0);
}

TEST_F(ValueTypeRoundTripTest_154, UShortSize_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    EXPECT_EQ(v.size(), 4u); // 2 * sizeof(uint16_t) = 4
}

TEST_F(ValueTypeRoundTripTest_154, ULongSize_154) {
    ValueType<uint32_t> v;
    v.value_.push_back(1);
    EXPECT_EQ(v.size(), 4u); // 1 * sizeof(uint32_t) = 4
}

// =============================================================================
// Multiple values in toString
// =============================================================================

class ValueTypeMultipleValuesTest_154 : public ::testing::Test {};

TEST_F(ValueTypeMultipleValuesTest_154, MultipleUShortValues_154) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    v.value_.push_back(30);
    
    EXPECT_EQ(v.toString(0), "10");
    EXPECT_EQ(v.toString(1), "20");
    EXPECT_EQ(v.toString(2), "30");
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeMultipleValuesTest_154, ReadFromStringMultiple_154) {
    ValueType<uint32_t> v;
    v.read("1 2 3 4 5");
    EXPECT_EQ(v.count(), 5u);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(v.toInt64(i), static_cast<int64_t>(i + 1));
    }
}

// =============================================================================
// Boundary tests
// =============================================================================

class ValueTypeBoundaryTest_154 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_154, ReadZeroLengthBuffer_154) {
    ValueType<uint16_t> v;
    byte dummy = 0;
    int rc = v.read(&dummy, 0, littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_154, SingleValueReadFromString_154) {
    ValueType<uint16_t> v;
    int rc = v.read("65535");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeBoundaryTest_154, EmptyStringRead_154) {
    ValueType<uint16_t> v;
    int rc = v.read("");
    EXPECT_EQ(rc, 0);
    // Could have 0 values or handle differently
}

TEST_F(ValueTypeBoundaryTest_154, DataAreaEmptyByDefault_154) {
    ValueType<uint32_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

// =============================================================================
// Constructor with byte buffer
// =============================================================================

class ValueTypeByteConstructorTest_154 : public ::testing::Test {};

TEST_F(ValueTypeByteConstructorTest_154, ConstructFromBuffer_154) {
    byte input[4];
    input[0] = 0x00; input[1] = 0x01;
    input[2] = 0x00; input[3] = 0x02;
    
    ValueType<uint16_t> v(input, sizeof(input), bigEndian, unsignedShort);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toUint32(0), 1u);
    EXPECT_EQ(v.toUint32(1), 2u);
}
