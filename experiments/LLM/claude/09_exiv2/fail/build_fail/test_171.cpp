#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cmath>
#include <limits>
#include <sstream>

using namespace Exiv2;

// Test fixture for ValueType<float>::toRational
class ValueTypeFloatToRational_171 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for general ValueType operations
class ValueTypeGeneral_171 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Tests for ValueType<float>::toRational ---

TEST_F(ValueTypeFloatToRational_171, PositiveFloat_171) {
    ValueType<float> v(0.5f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    // Check that the rational approximates 0.5
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 0.5f, 1e-4f);
}

TEST_F(ValueTypeFloatToRational_171, NegativeFloat_171) {
    ValueType<float> v(-0.25f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, -0.25f, 1e-4f);
}

TEST_F(ValueTypeFloatToRational_171, ZeroFloat_171) {
    ValueType<float> v(0.0f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_EQ(r.first, 0);
}

TEST_F(ValueTypeFloatToRational_171, OneFloat_171) {
    ValueType<float> v(1.0f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 1.0f, 1e-4f);
}

TEST_F(ValueTypeFloatToRational_171, LargeFloat_171) {
    ValueType<float> v(1000.0f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 1000.0f, 1e-1f);
}

TEST_F(ValueTypeFloatToRational_171, SmallFloat_171) {
    ValueType<float> v(0.001f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 0.001f, 1e-4f);
}

TEST_F(ValueTypeFloatToRational_171, MultipleValuesFirstElement_171) {
    ValueType<float> v(floatId);
    v.value_.push_back(3.14f);
    v.value_.push_back(2.71f);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 3.14f, 1e-3f);
}

TEST_F(ValueTypeFloatToRational_171, MultipleValuesSecondElement_171) {
    ValueType<float> v(floatId);
    v.value_.push_back(3.14f);
    v.value_.push_back(2.71f);
    Rational r = v.toRational(1);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 2.71f, 1e-3f);
}

TEST_F(ValueTypeFloatToRational_171, OutOfBoundsIndex_171) {
    ValueType<float> v(1.0f, floatId);
    EXPECT_THROW(v.toRational(5), std::out_of_range);
}

TEST_F(ValueTypeFloatToRational_171, NegativeOneFloat_171) {
    ValueType<float> v(-1.0f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, -1.0f, 1e-4f);
}

TEST_F(ValueTypeFloatToRational_171, OkFlagSetToTrue_171) {
    ValueType<float> v(0.5f, floatId);
    // First call to set ok_ to true
    v.toRational(0);
    EXPECT_TRUE(v.ok());
}

// --- Tests for ValueType<double>::toRational ---

TEST_F(ValueTypeGeneral_171, DoubleToRational_171) {
    ValueType<double> v(0.5, doubleId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(result, 0.5, 1e-4);
}

TEST_F(ValueTypeGeneral_171, DoubleToRationalNegative_171) {
    ValueType<double> v(-3.5, doubleId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(result, -3.5, 1e-4);
}

// --- Tests for ValueType<Rational>::toRational ---

TEST_F(ValueTypeGeneral_171, RationalToRational_171) {
    Rational rat = {1, 3};
    ValueType<Rational> v(rat, rationalId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 3);
}

TEST_F(ValueTypeGeneral_171, RationalToRationalNegative_171) {
    Rational rat = {-1, 4};
    ValueType<Rational> v(rat, rationalId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_EQ(r.first, -1);
    EXPECT_EQ(r.second, 4);
}

// --- Tests for ValueType<URational>::toRational ---

TEST_F(ValueTypeGeneral_171, URationalToRational_171) {
    URational urat = {1, 2};
    ValueType<URational> v(urat, unsignedRational);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

// --- Tests for toInt64, toUint32, toFloat ---

TEST_F(ValueTypeGeneral_171, FloatToInt64_171) {
    ValueType<float> v(42.7f, floatId);
    int64_t i = v.toInt64(0);
    EXPECT_EQ(i, 42);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeGeneral_171, FloatToUint32_171) {
    ValueType<float> v(42.7f, floatId);
    uint32_t u = v.toUint32(0);
    EXPECT_EQ(u, 42u);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeGeneral_171, DoubleToInt64_171) {
    ValueType<double> v(99.9, doubleId);
    int64_t i = v.toInt64(0);
    EXPECT_EQ(i, 99);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeGeneral_171, DoubleToUint32_171) {
    ValueType<double> v(99.9, doubleId);
    uint32_t u = v.toUint32(0);
    EXPECT_EQ(u, 99u);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeGeneral_171, RationalToInt64_171) {
    Rational rat = {10, 3};
    ValueType<Rational> v(rat, rationalId);
    int64_t i = v.toInt64(0);
    EXPECT_EQ(i, 3); // 10/3 = 3
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeGeneral_171, RationalToFloat_171) {
    Rational rat = {1, 4};
    ValueType<Rational> v(rat, rationalId);
    float f = v.toFloat(0);
    EXPECT_NEAR(f, 0.25f, 1e-5f);
    EXPECT_TRUE(v.ok());
}

TEST_F(ValueTypeGeneral_171, URationalToFloat_171) {
    URational urat = {3, 4};
    ValueType<URational> v(urat, unsignedRational);
    float f = v.toFloat(0);
    EXPECT_NEAR(f, 0.75f, 1e-5f);
    EXPECT_TRUE(v.ok());
}

// --- Tests for count, size ---

TEST_F(ValueTypeGeneral_171, CountSingleValue_171) {
    ValueType<float> v(1.0f, floatId);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeGeneral_171, CountMultipleValues_171) {
    ValueType<float> v(floatId);
    v.value_.push_back(1.0f);
    v.value_.push_back(2.0f);
    v.value_.push_back(3.0f);
    EXPECT_EQ(v.count(), 3u);
}

TEST_F(ValueTypeGeneral_171, CountEmpty_171) {
    ValueType<float> v(floatId);
    EXPECT_EQ(v.count(), 0u);
}

// --- Tests for toString ---

TEST_F(ValueTypeGeneral_171, ToStringFloat_171) {
    ValueType<float> v(1.5f, floatId);
    std::string s = v.toString(0);
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTypeGeneral_171, ToStringRational_171) {
    Rational rat = {1, 2};
    ValueType<Rational> v(rat, rationalId);
    std::string s = v.toString(0);
    EXPECT_FALSE(s.empty());
    // Rational should typically be "1/2"
    EXPECT_EQ(s, "1/2");
}

// --- Tests for write ---

TEST_F(ValueTypeGeneral_171, WriteFloat_171) {
    ValueType<float> v(3.14f, floatId);
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// --- Tests for clone ---

TEST_F(ValueTypeGeneral_171, CloneFloat_171) {
    ValueType<float> v(2.5f, floatId);
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->typeId(), floatId);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_NEAR(cloned->toFloat(0), 2.5f, 1e-5f);
}

// --- Tests for copy constructor and assignment ---

TEST_F(ValueTypeGeneral_171, CopyConstructor_171) {
    ValueType<float> v1(1.5f, floatId);
    ValueType<float> v2(v1);
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_NEAR(v2.toFloat(0), 1.5f, 1e-5f);
}

TEST_F(ValueTypeGeneral_171, AssignmentOperator_171) {
    ValueType<float> v1(1.5f, floatId);
    ValueType<float> v2(floatId);
    v2 = v1;
    EXPECT_EQ(v2.count(), 1u);
    EXPECT_NEAR(v2.toFloat(0), 1.5f, 1e-5f);
}

// --- Tests for setDataArea and dataArea ---

TEST_F(ValueTypeGeneral_171, DataAreaInitiallyEmpty_171) {
    ValueType<float> v(1.0f, floatId);
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeGeneral_171, SetDataAreaAndRetrieve_171) {
    ValueType<float> v(1.0f, floatId);
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int rc = v.setDataArea(data, 4);
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.sizeDataArea(), 4u);
    DataBuf buf = v.dataArea();
    EXPECT_EQ(buf.size(), 4u);
}

// --- Tests for typeId ---

TEST_F(ValueTypeGeneral_171, TypeIdFloat_171) {
    ValueType<float> v(floatId);
    EXPECT_EQ(v.typeId(), floatId);
}

TEST_F(ValueTypeGeneral_171, TypeIdRational_171) {
    Rational rat = {1, 2};
    ValueType<Rational> v(rat, rationalId);
    EXPECT_EQ(v.typeId(), rationalId);
}

// --- Tests for read from string ---

TEST_F(ValueTypeGeneral_171, ReadUShortFromString_171) {
    ValueType<uint16_t> v(unsignedShort);
    int rc = v.read("42");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeGeneral_171, ReadMultipleUShortFromString_171) {
    ValueType<uint16_t> v(unsignedShort);
    int rc = v.read("1 2 3");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
    EXPECT_EQ(v.toInt64(2), 3);
}

TEST_F(ValueTypeGeneral_171, ReadRationalFromString_171) {
    ValueType<Rational> v(rationalId);
    int rc = v.read("1/3");
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(v.count(), 1u);
    Rational r = v.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 3);
}

// --- Boundary: Very small float ---

TEST_F(ValueTypeFloatToRational_171, VerySmallFloat_171) {
    ValueType<float> v(1e-6f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
}

// --- Boundary: Pi approximation ---

TEST_F(ValueTypeFloatToRational_171, PiApproximation_171) {
    ValueType<float> v(3.14159f, floatId);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 3.14159f, 1e-2f);
}

// --- Test for integer types toRational ---

TEST_F(ValueTypeGeneral_171, UShortToRational_171) {
    ValueType<uint16_t> v(unsignedShort);
    v.value_.push_back(42);
    Rational r = v.toRational(0);
    EXPECT_TRUE(v.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(result, 42.0f, 1e-4f);
}

TEST_F(ValueTypeGeneral_171, UShortToFloat_171) {
    ValueType<uint16_t> v(unsignedShort);
    v.value_.push_back(100);
    float f = v.toFloat(0);
    EXPECT_NEAR(f, 100.0f, 1e-5f);
}

// --- Test for empty value access ---

TEST_F(ValueTypeGeneral_171, EmptyValueOutOfBounds_171) {
    ValueType<float> v(floatId);
    EXPECT_THROW(v.toRational(0), std::out_of_range);
}

TEST_F(ValueTypeGeneral_171, EmptyValueToFloatOutOfBounds_171) {
    ValueType<float> v(floatId);
    EXPECT_THROW(v.toFloat(0), std::out_of_range);
}

TEST_F(ValueTypeGeneral_171, EmptyValueToInt64OutOfBounds_171) {
    ValueType<float> v(floatId);
    EXPECT_THROW(v.toInt64(0), std::out_of_range);
}

// --- Test for Value::create factory ---

TEST_F(ValueTypeGeneral_171, CreateFloat_171) {
    auto v = Value::create(floatId);
    EXPECT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), floatId);
}

TEST_F(ValueTypeGeneral_171, CreateRational_171) {
    auto v = Value::create(rationalId);
    EXPECT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), rationalId);
}

TEST_F(ValueTypeGeneral_171, CreateUnsignedShort_171) {
    auto v = Value::create(unsignedShort);
    EXPECT_NE(v, nullptr);
    EXPECT_EQ(v->typeId(), unsignedShort);
}
