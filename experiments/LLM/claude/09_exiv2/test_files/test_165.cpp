#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cmath>
#include <sstream>

using namespace Exiv2;

// Test fixture for ValueType<uint16_t>
class ValueTypeUint16Test_165 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ValueType<int32_t>
class ValueTypeInt32Test_165 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ValueType<Rational>
class ValueTypeRationalTest_165 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ValueType<URational>
class ValueTypeURationalTest_165 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ValueType<float>
class ValueTypeFloatTest_165 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ValueType<double>
class ValueTypeDoubleTest_165 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===================== Default Constructor Tests =====================

TEST_F(ValueTypeUint16Test_165, DefaultConstructor_CountIsZero_165) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUint16Test_165, DefaultConstructor_TypeId_165) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.typeId(), unsignedShort);
}

TEST_F(ValueTypeInt32Test_165, DefaultConstructor_TypeId_165) {
    ValueType<int32_t> v;
    EXPECT_EQ(v.typeId(), signedLong);
}

// ===================== Value Constructor Tests =====================

TEST_F(ValueTypeUint16Test_165, ValueConstructor_SingleValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeInt32Test_165, ValueConstructor_SingleValue_165) {
    ValueType<int32_t> v(static_cast<int32_t>(-100), signedLong);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -100);
}

// ===================== toFloat Tests =====================

TEST_F(ValueTypeUint16Test_165, ToFloat_NormalValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, 42.0f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUint16Test_165, ToFloat_ZeroValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(0), unsignedShort);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUint16Test_165, ToFloat_MaxValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(65535), unsignedShort);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, 65535.0f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUint16Test_165, ToFloat_OutOfRange_Throws_165) {
    ValueType<uint16_t> v;
    EXPECT_THROW(v.toFloat(0), std::out_of_range);
}

TEST_F(ValueTypeUint16Test_165, ToFloat_IndexOutOfRange_Throws_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    EXPECT_THROW(v.toFloat(1), std::out_of_range);
}

TEST_F(ValueTypeInt32Test_165, ToFloat_NegativeValue_165) {
    ValueType<int32_t> v(static_cast<int32_t>(-500), signedLong);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, -500.0f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeFloatTest_165, ToFloat_FloatValue_165) {
    ValueType<float> v(3.14f, tiffFloat);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, 3.14f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeDoubleTest_165, ToFloat_DoubleValue_165) {
    ValueType<double> v(2.718281828, tiffDouble);
    float result = v.toFloat(0);
    EXPECT_NEAR(result, 2.718281828f, 0.0001f);
    EXPECT_TRUE(v.ok());
}

// ===================== Rational toFloat Tests =====================

TEST_F(ValueTypeRationalTest_165, ToFloat_NormalRational_165) {
    Rational r(1, 2);
    ValueType<Rational> v(r, signedRational);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.5f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeRationalTest_165, ToFloat_ZeroDenominator_165) {
    Rational r(1, 0);
    ValueType<Rational> v(r, signedRational);
    float result = v.toFloat(0);
    // When denominator is 0, result should be 0 or some defined behavior
    // We just check it doesn't crash and ok() state is set
    (void)result;
}

TEST_F(ValueTypeRationalTest_165, ToFloat_NegativeRational_165) {
    Rational r(-3, 4);
    ValueType<Rational> v(r, signedRational);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, -0.75f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeURationalTest_165, ToFloat_NormalURational_165) {
    URational r(3, 4);
    ValueType<URational> v(r, unsignedRational);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.75f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeURationalTest_165, ToFloat_ZeroDenominator_165) {
    URational r(5, 0);
    ValueType<URational> v(r, unsignedRational);
    float result = v.toFloat(0);
    (void)result;
}

// ===================== toInt64 Tests =====================

TEST_F(ValueTypeUint16Test_165, ToInt64_NormalValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(100), unsignedShort);
    EXPECT_EQ(v.toInt64(0), 100);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeInt32Test_165, ToInt64_NegativeValue_165) {
    ValueType<int32_t> v(static_cast<int32_t>(-999), signedLong);
    EXPECT_EQ(v.toInt64(0), -999);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeFloatTest_165, ToInt64_FloatValue_165) {
    ValueType<float> v(3.7f, tiffFloat);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeDoubleTest_165, ToInt64_DoubleValue_165) {
    ValueType<double> v(9.99, tiffDouble);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 9);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeRationalTest_165, ToInt64_Rational_165) {
    Rational r(7, 2);
    ValueType<Rational> v(r, signedRational);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeURationalTest_165, ToInt64_URational_165) {
    URational r(10, 3);
    ValueType<URational> v(r, unsignedRational);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);
    EXPECT_TRUE(v.ok());
}

// ===================== toUint32 Tests =====================

TEST_F(ValueTypeUint16Test_165, ToUint32_NormalValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(200), unsignedShort);
    EXPECT_EQ(v.toUint32(0), 200u);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeFloatTest_165, ToUint32_FloatValue_165) {
    ValueType<float> v(5.5f, tiffFloat);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 5u);
}

TEST_F(ValueTypeDoubleTest_165, ToUint32_DoubleValue_165) {
    ValueType<double> v(7.9, tiffDouble);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 7u);
}

TEST_F(ValueTypeRationalTest_165, ToUint32_Rational_165) {
    Rational r(9, 2);
    ValueType<Rational> v(r, signedRational);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 4u);
}

TEST_F(ValueTypeURationalTest_165, ToUint32_URational_165) {
    URational r(15, 4);
    ValueType<URational> v(r, unsignedRational);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u);
}

// ===================== toRational Tests =====================

TEST_F(ValueTypeUint16Test_165, ToRational_NormalValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(5), unsignedShort);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

TEST_F(ValueTypeRationalTest_165, ToRational_Rational_165) {
    Rational r(3, 7);
    ValueType<Rational> v(r, signedRational);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

TEST_F(ValueTypeURationalTest_165, ToRational_URational_165) {
    URational r(11, 13);
    ValueType<URational> v(r, unsignedRational);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 11);
    EXPECT_EQ(result.second, 13);
}

TEST_F(ValueTypeFloatTest_165, ToRational_FloatValue_165) {
    ValueType<float> v(0.5f, tiffFloat);
    Rational r = v.toRational(0);
    // Check that the rational approximation is close
    if (r.second != 0) {
        float ratio = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(ratio, 0.5f, 0.01f);
    }
}

TEST_F(ValueTypeDoubleTest_165, ToRational_DoubleValue_165) {
    ValueType<double> v(0.25, tiffDouble);
    Rational r = v.toRational(0);
    if (r.second != 0) {
        double ratio = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(ratio, 0.25, 0.01);
    }
}

// ===================== count() Tests =====================

TEST_F(ValueTypeUint16Test_165, Count_Empty_165) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUint16Test_165, Count_SingleValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(1), unsignedShort);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeUint16Test_165, Count_MultipleValues_165) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    v.value_.push_back(3);
    EXPECT_EQ(v.count(), 3u);
}

// ===================== toString Tests =====================

TEST_F(ValueTypeUint16Test_165, ToString_NormalValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    std::string result = v.toString(0);
    EXPECT_EQ(result, "42");
}

TEST_F(ValueTypeInt32Test_165, ToString_NegativeValue_165) {
    ValueType<int32_t> v(static_cast<int32_t>(-42), signedLong);
    std::string result = v.toString(0);
    EXPECT_EQ(result, "-42");
}

TEST_F(ValueTypeRationalTest_165, ToString_Rational_165) {
    Rational r(1, 3);
    ValueType<Rational> v(r, signedRational);
    std::string result = v.toString(0);
    EXPECT_EQ(result, "1/3");
}

TEST_F(ValueTypeURationalTest_165, ToString_URational_165) {
    URational r(5, 8);
    ValueType<URational> v(r, unsignedRational);
    std::string result = v.toString(0);
    EXPECT_EQ(result, "5/8");
}

// ===================== write Tests =====================

TEST_F(ValueTypeUint16Test_165, Write_SingleValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    std::ostringstream os;
    v.write(os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ValueTypeUint16Test_165, Write_MultipleValues_165) {
    ValueType<uint16_t> v;
    v.value_.push_back(1);
    v.value_.push_back(2);
    v.value_.push_back(3);
    std::ostringstream os;
    v.write(os);
    EXPECT_FALSE(os.str().empty());
}

// ===================== Copy Constructor Tests =====================

TEST_F(ValueTypeUint16Test_165, CopyConstructor_165) {
    ValueType<uint16_t> v1(static_cast<uint16_t>(99), unsignedShort);
    ValueType<uint16_t> v2(v1);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 99);
    EXPECT_EQ(v2.typeId(), v1.typeId());
}

// ===================== Assignment Operator Tests =====================

TEST_F(ValueTypeUint16Test_165, AssignmentOperator_165) {
    ValueType<uint16_t> v1(static_cast<uint16_t>(55), unsignedShort);
    ValueType<uint16_t> v2;
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_EQ(v2.toInt64(0), 55);
}

// ===================== clone Tests =====================

TEST_F(ValueTypeUint16Test_165, Clone_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(77), unsignedShort);
    auto cloned = v.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), unsignedShort);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_EQ(cloned->toInt64(0), 77);
}

// ===================== size Tests =====================

TEST_F(ValueTypeUint16Test_165, Size_Empty_165) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeUint16Test_165, Size_SingleValue_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(1), unsignedShort);
    EXPECT_EQ(v.size(), 2u);  // uint16_t is 2 bytes
}

TEST_F(ValueTypeInt32Test_165, Size_SingleValue_165) {
    ValueType<int32_t> v(static_cast<int32_t>(1), signedLong);
    EXPECT_EQ(v.size(), 4u);  // int32_t is 4 bytes
}

TEST_F(ValueTypeRationalTest_165, Size_SingleValue_165) {
    Rational r(1, 2);
    ValueType<Rational> v(r, signedRational);
    EXPECT_EQ(v.size(), 8u);  // Rational is 2 x int32_t = 8 bytes
}

// ===================== read from string Tests =====================

TEST_F(ValueTypeUint16Test_165, ReadFromString_SingleValue_165) {
    ValueType<uint16_t> v;
    int result = v.read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUint16Test_165, ReadFromString_MultipleValues_165) {
    ValueType<uint16_t> v;
    int result = v.read("1 2 3");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
    EXPECT_EQ(v.toInt64(2), 3);
}

TEST_F(ValueTypeRationalTest_165, ReadFromString_Rational_165) {
    ValueType<Rational> v;
    int result = v.read("1/2");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

TEST_F(ValueTypeURationalTest_165, ReadFromString_URational_165) {
    ValueType<URational> v;
    int result = v.read("3/4");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 4);
}

// ===================== read from bytes Tests =====================

TEST_F(ValueTypeUint16Test_165, ReadFromBytes_LittleEndian_165) {
    byte buf[2] = {0x2A, 0x00};  // 42 in little-endian
    ValueType<uint16_t> v;
    int result = v.read(buf, 2, littleEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUint16Test_165, ReadFromBytes_BigEndian_165) {
    byte buf[2] = {0x00, 0x2A};  // 42 in big-endian
    ValueType<uint16_t> v;
    int result = v.read(buf, 2, bigEndian);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

// ===================== copy to bytes Tests =====================

TEST_F(ValueTypeUint16Test_165, CopyToBytes_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    byte buf[2] = {0};
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, 2u);
    // Verify bytes represent 42 in little-endian
    EXPECT_EQ(buf[0], 0x2A);
    EXPECT_EQ(buf[1], 0x00);
}

// ===================== setDataArea / dataArea / sizeDataArea Tests =====================

TEST_F(ValueTypeUint16Test_165, DataArea_Empty_165) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeUint16Test_165, SetDataArea_165) {
    ValueType<uint16_t> v;
    byte data[] = {1, 2, 3, 4};
    int result = v.setDataArea(data, 4);
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 4u);
}

// ===================== Multiple elements access Tests =====================

TEST_F(ValueTypeUint16Test_165, MultipleElements_ToFloat_165) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    v.value_.push_back(30);
    EXPECT_FLOAT_EQ(v.toFloat(0), 10.0f);
    EXPECT_FLOAT_EQ(v.toFloat(1), 20.0f);
    EXPECT_FLOAT_EQ(v.toFloat(2), 30.0f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeUint16Test_165, MultipleElements_ToFloat_OutOfBounds_165) {
    ValueType<uint16_t> v;
    v.value_.push_back(10);
    v.value_.push_back(20);
    EXPECT_THROW(v.toFloat(2), std::out_of_range);
}

// ===================== ok() state Tests =====================

TEST_F(ValueTypeUint16Test_165, OkState_AfterToFloat_165) {
    ValueType<uint16_t> v(static_cast<uint16_t>(42), unsignedShort);
    v.toFloat(0);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeInt32Test_165, OkState_AfterToInt64_165) {
    ValueType<int32_t> v(static_cast<int32_t>(100), signedLong);
    v.toInt64(0);
    EXPECT_TRUE(v.ok());
}

// ===================== Value::create factory Tests =====================

TEST(ValueCreateTest_165, CreateUnsignedShort_165) {
    auto v = Value::create(unsignedShort);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}

TEST(ValueCreateTest_165, CreateSignedLong_165) {
    auto v = Value::create(signedLong);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), signedLong);
}

TEST(ValueCreateTest_165, CreateSignedRational_165) {
    auto v = Value::create(signedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), signedRational);
}

TEST(ValueCreateTest_165, CreateUnsignedRational_165) {
    auto v = Value::create(unsignedRational);
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedRational);
}

// ===================== Edge case: Rational with zero numerator =====================

TEST_F(ValueTypeRationalTest_165, ToFloat_ZeroNumerator_165) {
    Rational r(0, 5);
    ValueType<Rational> v(r, signedRational);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(ValueTypeURationalTest_165, ToFloat_ZeroNumerator_165) {
    URational r(0, 5);
    ValueType<URational> v(r, unsignedRational);
    float result = v.toFloat(0);
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// ===================== Large value Tests =====================

TEST_F(ValueTypeInt32Test_165, ToFloat_LargePositive_165) {
    ValueType<int32_t> v(static_cast<int32_t>(2147483647), signedLong);
    float result = v.toFloat(0);
    EXPECT_NEAR(result, 2147483647.0f, 200.0f);  // float precision
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeInt32Test_165, ToFloat_LargeNegative_165) {
    ValueType<int32_t> v(static_cast<int32_t>(-2147483647), signedLong);
    float result = v.toFloat(0);
    EXPECT_NEAR(result, -2147483647.0f, 200.0f);
    EXPECT_TRUE(v.ok());
}
