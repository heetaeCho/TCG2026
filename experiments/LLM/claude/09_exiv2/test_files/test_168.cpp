#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<T>::toRational
// ============================================================

class ValueTypeToRationalTest_168 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test toRational for uint16_t value type with a single value
TEST_F(ValueTypeToRationalTest_168, ToRational_UShortSingleValue_168) {
    UShortValue val;
    val.value_.push_back(42);
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 42);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational for uint32_t (ULongValue) with a single value
TEST_F(ValueTypeToRationalTest_168, ToRational_ULongSingleValue_168) {
    ULongValue val;
    val.value_.push_back(100);
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 100);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational for int16_t (ShortValue) with negative value
TEST_F(ValueTypeToRationalTest_168, ToRational_ShortNegativeValue_168) {
    ShortValue val;
    val.value_.push_back(-5);
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, -5);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational for int32_t (LongValue) with zero value
TEST_F(ValueTypeToRationalTest_168, ToRational_LongZeroValue_168) {
    LongValue val;
    val.value_.push_back(0);
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 0);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational for multiple values, accessing index > 0
TEST_F(ValueTypeToRationalTest_168, ToRational_MultipleValues_AccessSecond_168) {
    UShortValue val;
    val.value_.push_back(10);
    val.value_.push_back(20);
    val.value_.push_back(30);
    Rational r = val.toRational(1);
    EXPECT_EQ(r.first, 20);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational for multiple values, accessing last element
TEST_F(ValueTypeToRationalTest_168, ToRational_MultipleValues_AccessLast_168) {
    LongValue val;
    val.value_.push_back(1);
    val.value_.push_back(2);
    val.value_.push_back(3);
    Rational r = val.toRational(2);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational out of bounds throws (via std::vector::at)
TEST_F(ValueTypeToRationalTest_168, ToRational_OutOfBounds_Throws_168) {
    UShortValue val;
    val.value_.push_back(42);
    EXPECT_THROW(val.toRational(1), std::out_of_range);
}

// Test toRational on empty value list throws
TEST_F(ValueTypeToRationalTest_168, ToRational_EmptyValue_Throws_168) {
    UShortValue val;
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

// ============================================================
// Tests for Rational specialization: ValueType<Rational>::toRational
// ============================================================

TEST_F(ValueTypeToRationalTest_168, ToRational_RationalType_ReturnsSameRational_168) {
    RationalValue val;
    val.value_.push_back(Rational(3, 7));
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 7);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeToRationalTest_168, ToRational_RationalType_NegativeNumerator_168) {
    RationalValue val;
    val.value_.push_back(Rational(-10, 3));
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, -10);
    EXPECT_EQ(r.second, 3);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeToRationalTest_168, ToRational_RationalType_MultipleValues_168) {
    RationalValue val;
    val.value_.push_back(Rational(1, 2));
    val.value_.push_back(Rational(3, 4));
    Rational r0 = val.toRational(0);
    Rational r1 = val.toRational(1);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 2);
    EXPECT_EQ(r1.first, 3);
    EXPECT_EQ(r1.second, 4);
}

// ============================================================
// Tests for URational specialization: ValueType<URational>::toRational
// ============================================================

TEST_F(ValueTypeToRationalTest_168, ToRational_URationalType_ReturnsRational_168) {
    URationalValue val;
    val.value_.push_back(URational(5, 10));
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 10);
    EXPECT_TRUE(val.ok());
}

// ============================================================
// Tests for float specialization: ValueType<float>::toRational
// ============================================================

TEST_F(ValueTypeToRationalTest_168, ToRational_FloatType_ReturnsApproximation_168) {
    FloatValue val;
    val.value_.push_back(0.5f);
    Rational r = val.toRational(0);
    // The result should approximate 0.5 as a rational
    EXPECT_TRUE(val.ok());
    // Check the rational approximates 0.5
    if (r.second != 0) {
        float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(approx, 0.5f, 0.001f);
    }
}

TEST_F(ValueTypeToRationalTest_168, ToRational_FloatType_Zero_168) {
    FloatValue val;
    val.value_.push_back(0.0f);
    Rational r = val.toRational(0);
    EXPECT_TRUE(val.ok());
    EXPECT_EQ(r.first, 0);
}

TEST_F(ValueTypeToRationalTest_168, ToRational_FloatType_NegativeValue_168) {
    FloatValue val;
    val.value_.push_back(-2.5f);
    Rational r = val.toRational(0);
    EXPECT_TRUE(val.ok());
    if (r.second != 0) {
        float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
        EXPECT_NEAR(approx, -2.5f, 0.01f);
    }
}

// ============================================================
// Tests for double specialization: ValueType<double>::toRational
// ============================================================

TEST_F(ValueTypeToRationalTest_168, ToRational_DoubleType_ReturnsApproximation_168) {
    DoubleValue val;
    val.value_.push_back(0.25);
    Rational r = val.toRational(0);
    EXPECT_TRUE(val.ok());
    if (r.second != 0) {
        double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(approx, 0.25, 0.001);
    }
}

TEST_F(ValueTypeToRationalTest_168, ToRational_DoubleType_IntegerValue_168) {
    DoubleValue val;
    val.value_.push_back(7.0);
    Rational r = val.toRational(0);
    EXPECT_TRUE(val.ok());
    if (r.second != 0) {
        double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
        EXPECT_NEAR(approx, 7.0, 0.001);
    }
}

// ============================================================
// Tests for ValueType general operations
// ============================================================

class ValueTypeGeneralTest_168 : public ::testing::Test {};

// Test count() returns number of elements
TEST_F(ValueTypeGeneralTest_168, Count_ReturnsNumberOfElements_168) {
    UShortValue val;
    EXPECT_EQ(val.count(), 0u);
    val.value_.push_back(1);
    EXPECT_EQ(val.count(), 1u);
    val.value_.push_back(2);
    val.value_.push_back(3);
    EXPECT_EQ(val.count(), 3u);
}

// Test typeId returns correct type
TEST_F(ValueTypeGeneralTest_168, TypeId_ReturnsCorrectType_168) {
    UShortValue ushortVal;
    EXPECT_EQ(ushortVal.typeId(), unsignedShort);

    ULongValue ulongVal;
    EXPECT_EQ(ulongVal.typeId(), unsignedLong);

    RationalValue ratVal;
    EXPECT_EQ(ratVal.typeId(), unsignedRational);

    ShortValue shortVal;
    EXPECT_EQ(shortVal.typeId(), signedShort);

    LongValue longVal;
    EXPECT_EQ(longVal.typeId(), signedLong);
}

// Test clone produces a copy
TEST_F(ValueTypeGeneralTest_168, Clone_ProducesCopy_168) {
    UShortValue val;
    val.value_.push_back(10);
    val.value_.push_back(20);
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 2u);
    EXPECT_EQ(cloned->toInt64(0), 10);
    EXPECT_EQ(cloned->toInt64(1), 20);
}

// Test copy constructor
TEST_F(ValueTypeGeneralTest_168, CopyConstructor_CopiesValues_168) {
    UShortValue val;
    val.value_.push_back(7);
    val.value_.push_back(14);
    UShortValue copy(val);
    EXPECT_EQ(copy.count(), 2u);
    EXPECT_EQ(copy.toInt64(0), 7);
    EXPECT_EQ(copy.toInt64(1), 14);
}

// Test assignment operator
TEST_F(ValueTypeGeneralTest_168, AssignmentOperator_CopiesValues_168) {
    UShortValue val1;
    val1.value_.push_back(100);
    UShortValue val2;
    val2 = val1;
    EXPECT_EQ(val2.count(), 1u);
    EXPECT_EQ(val2.toInt64(0), 100);
}

// Test toInt64 for basic integer types
TEST_F(ValueTypeGeneralTest_168, ToInt64_UShort_168) {
    UShortValue val;
    val.value_.push_back(255);
    EXPECT_EQ(val.toInt64(0), 255);
    EXPECT_TRUE(val.ok());
}

// Test toUint32 for basic integer types
TEST_F(ValueTypeGeneralTest_168, ToUint32_ULong_168) {
    ULongValue val;
    val.value_.push_back(4294967295u);
    EXPECT_EQ(val.toUint32(0), 4294967295u);
    EXPECT_TRUE(val.ok());
}

// Test toFloat for integer type
TEST_F(ValueTypeGeneralTest_168, ToFloat_UShort_168) {
    UShortValue val;
    val.value_.push_back(50);
    EXPECT_FLOAT_EQ(val.toFloat(0), 50.0f);
    EXPECT_TRUE(val.ok());
}

// Test toFloat for Rational type
TEST_F(ValueTypeGeneralTest_168, ToFloat_RationalType_168) {
    RationalValue val;
    val.value_.push_back(Rational(1, 3));
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 1.0f / 3.0f, 0.0001f);
    EXPECT_TRUE(val.ok());
}

// Test toFloat for URational type
TEST_F(ValueTypeGeneralTest_168, ToFloat_URationalType_168) {
    URationalValue val;
    val.value_.push_back(URational(3, 4));
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 0.75f, 0.0001f);
    EXPECT_TRUE(val.ok());
}

// Test toString for integer type
TEST_F(ValueTypeGeneralTest_168, ToString_UShort_168) {
    UShortValue val;
    val.value_.push_back(42);
    std::string s = val.toString(0);
    EXPECT_EQ(s, "42");
}

// Test toString for Rational type
TEST_F(ValueTypeGeneralTest_168, ToString_Rational_168) {
    RationalValue val;
    val.value_.push_back(Rational(1, 2));
    std::string s = val.toString(0);
    EXPECT_EQ(s, "1/2");
}

// Test write to ostream
TEST_F(ValueTypeGeneralTest_168, Write_MultipleValues_168) {
    UShortValue val;
    val.value_.push_back(1);
    val.value_.push_back(2);
    val.value_.push_back(3);
    std::ostringstream os;
    val.write(os);
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Test read from string for integer type
TEST_F(ValueTypeGeneralTest_168, ReadFromString_UShort_168) {
    UShortValue val;
    int rc = val.read("10 20 30");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val.count(), 3u);
    EXPECT_EQ(val.toInt64(0), 10);
    EXPECT_EQ(val.toInt64(1), 20);
    EXPECT_EQ(val.toInt64(2), 30);
}

// Test read from string for Rational type
TEST_F(ValueTypeGeneralTest_168, ReadFromString_Rational_168) {
    RationalValue val;
    int rc = val.read("1/2 3/4");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val.count(), 2u);
    Rational r0 = val.toRational(0);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 2);
    Rational r1 = val.toRational(1);
    EXPECT_EQ(r1.first, 3);
    EXPECT_EQ(r1.second, 4);
}

// Test setDataArea and dataArea
TEST_F(ValueTypeGeneralTest_168, SetDataArea_And_DataArea_168) {
    UShortValue val;
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    int rc = val.setDataArea(data, sizeof(data));
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val.sizeDataArea(), sizeof(data));
    DataBuf buf = val.dataArea();
    EXPECT_EQ(buf.size(), sizeof(data));
    EXPECT_EQ(std::memcmp(buf.c_data(), data, sizeof(data)), 0);
}

// Test sizeDataArea when no data area set
TEST_F(ValueTypeGeneralTest_168, SizeDataArea_NoData_168) {
    UShortValue val;
    EXPECT_EQ(val.sizeDataArea(), 0u);
}

// Test toInt64 for Rational type
TEST_F(ValueTypeGeneralTest_168, ToInt64_RationalType_168) {
    RationalValue val;
    val.value_.push_back(Rational(10, 3));
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 3); // 10/3 = 3.33... truncated to 3
    EXPECT_TRUE(val.ok());
}

// Test toInt64 for float type
TEST_F(ValueTypeGeneralTest_168, ToInt64_FloatType_168) {
    FloatValue val;
    val.value_.push_back(3.7f);
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 3);
    EXPECT_TRUE(val.ok());
}

// Test toInt64 for double type
TEST_F(ValueTypeGeneralTest_168, ToInt64_DoubleType_168) {
    DoubleValue val;
    val.value_.push_back(7.9);
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 7);
    EXPECT_TRUE(val.ok());
}

// Test toUint32 for Rational type
TEST_F(ValueTypeGeneralTest_168, ToUint32_RationalType_168) {
    RationalValue val;
    val.value_.push_back(Rational(20, 4));
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(result, 5u);
    EXPECT_TRUE(val.ok());
}

// Test explicit constructor with initial value
TEST_F(ValueTypeGeneralTest_168, ExplicitConstructorWithValue_168) {
    uint16_t initVal = 99;
    ValueType<uint16_t> val(initVal, unsignedShort);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.toInt64(0), 99);
}

// Test Value::create factory method
TEST_F(ValueTypeGeneralTest_168, ValueCreate_UShort_168) {
    auto val = Value::create(unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedShort);
}

TEST_F(ValueTypeGeneralTest_168, ValueCreate_SignedRational_168) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedRational);
}

// Test ok() is true after successful toRational call
TEST_F(ValueTypeToRationalTest_168, OkAfterSuccessfulToRational_168) {
    LongValue val;
    val.value_.push_back(50);
    val.toRational(0);
    EXPECT_TRUE(val.ok());
}

// Test with large values
TEST_F(ValueTypeToRationalTest_168, ToRational_LargeValue_168) {
    LongValue val;
    val.value_.push_back(2147483647); // INT32_MAX
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 2147483647);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test toRational for negative LongValue
TEST_F(ValueTypeToRationalTest_168, ToRational_LongNegativeLarge_168) {
    LongValue val;
    val.value_.push_back(-2147483647);
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, -2147483647);
    EXPECT_EQ(r.second, 1);
    EXPECT_TRUE(val.ok());
}

// Test Rational with zero denominator
TEST_F(ValueTypeToRationalTest_168, ToFloat_RationalZeroDenominator_168) {
    RationalValue val;
    val.value_.push_back(Rational(1, 0));
    // Behavior depends on implementation, but we can at least call it
    // The toRational should still return the same rational
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 0);
}

// Test read from byte buffer
TEST_F(ValueTypeGeneralTest_168, ReadFromBuffer_UShort_168) {
    UShortValue val;
    // Two uint16 values in little endian: 0x0001 and 0x0002
    byte buf[] = {0x01, 0x00, 0x02, 0x00};
    int rc = val.read(buf, sizeof(buf), littleEndian);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(val.count(), 2u);
    EXPECT_EQ(val.toInt64(0), 1);
    EXPECT_EQ(val.toInt64(1), 2);
}

// Test size() returns correct byte size
TEST_F(ValueTypeGeneralTest_168, Size_UShort_168) {
    UShortValue val;
    val.value_.push_back(1);
    val.value_.push_back(2);
    // Each uint16 is 2 bytes
    EXPECT_EQ(val.size(), 4u);
}

TEST_F(ValueTypeGeneralTest_168, Size_ULong_168) {
    ULongValue val;
    val.value_.push_back(1);
    // Each uint32 is 4 bytes
    EXPECT_EQ(val.size(), 4u);
}

TEST_F(ValueTypeGeneralTest_168, Size_Rational_168) {
    RationalValue val;
    val.value_.push_back(Rational(1, 2));
    // Each rational is 8 bytes (two int32)
    EXPECT_EQ(val.size(), 8u);
}
