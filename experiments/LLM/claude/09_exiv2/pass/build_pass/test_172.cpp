#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cmath>
#include <limits>
#include <sstream>

using namespace Exiv2;

// Type aliases for convenience
using DoubleValue = ValueType<double>;
using FloatValue = ValueType<float>;
using RationalValue = ValueType<Rational>;
using URationalValue = ValueType<URational>;
using UShortValue = ValueType<uint16_t>;
using ULongValue = ValueType<uint32_t>;
using ShortValue = ValueType<int16_t>;
using LongValue = ValueType<int32_t>;

// ============================================================
// Tests for ValueType<double>::toRational (the specific partial code)
// ============================================================

class ValueTypeDoubleToRationalTest_172 : public ::testing::Test {
protected:
    DoubleValue dv;
    
    ValueTypeDoubleToRationalTest_172() : dv() {}
};

TEST_F(ValueTypeDoubleToRationalTest_172, PositiveIntegerValue_172) {
    dv.value_.push_back(5.0);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    // 5.0 should convert to a rational that evaluates to 5
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, 5.0, 0.01);
}

TEST_F(ValueTypeDoubleToRationalTest_172, ZeroValue_172) {
    dv.value_.push_back(0.0);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_EQ(r.first, 0);
}

TEST_F(ValueTypeDoubleToRationalTest_172, NegativeValue_172) {
    dv.value_.push_back(-3.5);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, -3.5, 0.01);
}

TEST_F(ValueTypeDoubleToRationalTest_172, FractionalValue_172) {
    dv.value_.push_back(0.5);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, 0.5, 0.01);
}

TEST_F(ValueTypeDoubleToRationalTest_172, SmallFractionValue_172) {
    dv.value_.push_back(0.001);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, 0.001, 0.01);
}

TEST_F(ValueTypeDoubleToRationalTest_172, LargeValue_172) {
    dv.value_.push_back(100000.0);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, 100000.0, 1.0);
}

TEST_F(ValueTypeDoubleToRationalTest_172, MultipleValuesSecondElement_172) {
    dv.value_.push_back(1.0);
    dv.value_.push_back(2.5);
    dv.value_.push_back(3.0);
    Rational r = dv.toRational(1);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, 2.5, 0.01);
}

TEST_F(ValueTypeDoubleToRationalTest_172, OutOfRangeIndex_172) {
    dv.value_.push_back(1.0);
    EXPECT_THROW(dv.toRational(5), std::out_of_range);
}

TEST_F(ValueTypeDoubleToRationalTest_172, OneThirdApproximation_172) {
    dv.value_.push_back(1.0 / 3.0);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, 1.0 / 3.0, 0.01);
}

TEST_F(ValueTypeDoubleToRationalTest_172, PiApproximation_172) {
    dv.value_.push_back(3.14159265);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, 3.14159265, 0.01);
}

// ============================================================
// Tests for ValueType<float>::toRational
// ============================================================

class ValueTypeFloatToRationalTest_172 : public ::testing::Test {
protected:
    FloatValue fv;
    ValueTypeFloatToRationalTest_172() : fv() {}
};

TEST_F(ValueTypeFloatToRationalTest_172, PositiveFloatToRational_172) {
    fv.value_.push_back(2.5f);
    Rational r = fv.toRational(0);
    EXPECT_TRUE(fv.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / r.second;
    EXPECT_NEAR(result, 2.5f, 0.01f);
}

TEST_F(ValueTypeFloatToRationalTest_172, ZeroFloatToRational_172) {
    fv.value_.push_back(0.0f);
    Rational r = fv.toRational(0);
    EXPECT_TRUE(fv.ok());
    EXPECT_EQ(r.first, 0);
}

TEST_F(ValueTypeFloatToRationalTest_172, NegativeFloatToRational_172) {
    fv.value_.push_back(-1.5f);
    Rational r = fv.toRational(0);
    EXPECT_TRUE(fv.ok());
    EXPECT_NE(r.second, 0);
    float result = static_cast<float>(r.first) / r.second;
    EXPECT_NEAR(result, -1.5f, 0.01f);
}

// ============================================================
// Tests for ValueType<Rational>::toRational
// ============================================================

class ValueTypeRationalToRationalTest_172 : public ::testing::Test {
protected:
    RationalValue rv;
    ValueTypeRationalToRationalTest_172() : rv() {}
};

TEST_F(ValueTypeRationalToRationalTest_172, SimpleRational_172) {
    rv.value_.push_back(Rational(1, 2));
    Rational r = rv.toRational(0);
    EXPECT_TRUE(rv.ok());
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

TEST_F(ValueTypeRationalToRationalTest_172, NegativeRational_172) {
    rv.value_.push_back(Rational(-3, 4));
    Rational r = rv.toRational(0);
    EXPECT_TRUE(rv.ok());
    EXPECT_EQ(r.first, -3);
    EXPECT_EQ(r.second, 4);
}

TEST_F(ValueTypeRationalToRationalTest_172, ZeroNumerator_172) {
    rv.value_.push_back(Rational(0, 1));
    Rational r = rv.toRational(0);
    EXPECT_TRUE(rv.ok());
    EXPECT_EQ(r.first, 0);
}

// ============================================================
// Tests for ValueType<URational>::toRational
// ============================================================

class ValueTypeURationalToRationalTest_172 : public ::testing::Test {
protected:
    URationalValue urv;
    ValueTypeURationalToRationalTest_172() : urv() {}
};

TEST_F(ValueTypeURationalToRationalTest_172, SimpleURational_172) {
    urv.value_.push_back(URational(3, 4));
    Rational r = urv.toRational(0);
    EXPECT_TRUE(urv.ok());
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 4);
}

TEST_F(ValueTypeURationalToRationalTest_172, URationalZeroNumerator_172) {
    urv.value_.push_back(URational(0, 10));
    Rational r = urv.toRational(0);
    EXPECT_TRUE(urv.ok());
    EXPECT_EQ(r.first, 0);
}

// ============================================================
// Tests for ValueType general operations
// ============================================================

class ValueTypeGeneralTest_172 : public ::testing::Test {};

TEST_F(ValueTypeGeneralTest_172, DoubleValueCount_172) {
    DoubleValue dv;
    EXPECT_EQ(dv.count(), 0u);
    dv.value_.push_back(1.0);
    dv.value_.push_back(2.0);
    EXPECT_EQ(dv.count(), 2u);
}

TEST_F(ValueTypeGeneralTest_172, FloatValueCount_172) {
    FloatValue fv;
    EXPECT_EQ(fv.count(), 0u);
    fv.value_.push_back(1.0f);
    EXPECT_EQ(fv.count(), 1u);
}

TEST_F(ValueTypeGeneralTest_172, RationalValueCount_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 2));
    rv.value_.push_back(Rational(3, 4));
    rv.value_.push_back(Rational(5, 6));
    EXPECT_EQ(rv.count(), 3u);
}

TEST_F(ValueTypeGeneralTest_172, DoubleToInt64_172) {
    DoubleValue dv;
    dv.value_.push_back(42.7);
    int64_t val = dv.toInt64(0);
    EXPECT_EQ(val, 42);
}

TEST_F(ValueTypeGeneralTest_172, DoubleToUint32_172) {
    DoubleValue dv;
    dv.value_.push_back(42.7);
    uint32_t val = dv.toUint32(0);
    EXPECT_EQ(val, 42u);
}

TEST_F(ValueTypeGeneralTest_172, DoubleToFloat_172) {
    DoubleValue dv;
    dv.value_.push_back(3.14);
    float val = dv.toFloat(0);
    EXPECT_NEAR(val, 3.14f, 0.001f);
}

TEST_F(ValueTypeGeneralTest_172, FloatToInt64_172) {
    FloatValue fv;
    fv.value_.push_back(7.9f);
    int64_t val = fv.toInt64(0);
    EXPECT_EQ(val, 7);
}

TEST_F(ValueTypeGeneralTest_172, FloatToUint32_172) {
    FloatValue fv;
    fv.value_.push_back(7.9f);
    uint32_t val = fv.toUint32(0);
    EXPECT_EQ(val, 7u);
}

TEST_F(ValueTypeGeneralTest_172, FloatToFloat_172) {
    FloatValue fv;
    fv.value_.push_back(2.5f);
    float val = fv.toFloat(0);
    EXPECT_FLOAT_EQ(val, 2.5f);
}

TEST_F(ValueTypeGeneralTest_172, RationalToInt64_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(7, 2));
    int64_t val = rv.toInt64(0);
    EXPECT_EQ(val, 3);  // integer division: 7/2 = 3
}

TEST_F(ValueTypeGeneralTest_172, RationalToUint32_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(10, 3));
    uint32_t val = rv.toUint32(0);
    EXPECT_EQ(val, 3u);  // integer division: 10/3 = 3
}

TEST_F(ValueTypeGeneralTest_172, RationalToFloat_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 4));
    float val = rv.toFloat(0);
    EXPECT_NEAR(val, 0.25f, 0.001f);
}

TEST_F(ValueTypeGeneralTest_172, URationalToInt64_172) {
    URationalValue urv;
    urv.value_.push_back(URational(9, 2));
    int64_t val = urv.toInt64(0);
    EXPECT_EQ(val, 4);  // 9/2 = 4
}

TEST_F(ValueTypeGeneralTest_172, URationalToUint32_172) {
    URationalValue urv;
    urv.value_.push_back(URational(9, 2));
    uint32_t val = urv.toUint32(0);
    EXPECT_EQ(val, 4u);
}

TEST_F(ValueTypeGeneralTest_172, URationalToFloat_172) {
    URationalValue urv;
    urv.value_.push_back(URational(3, 4));
    float val = urv.toFloat(0);
    EXPECT_NEAR(val, 0.75f, 0.001f);
}

// ============================================================
// Tests for ValueType toString
// ============================================================

TEST_F(ValueTypeGeneralTest_172, DoubleToString_172) {
    DoubleValue dv;
    dv.value_.push_back(1.5);
    std::string s = dv.toString(0);
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTypeGeneralTest_172, RationalToString_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 3));
    std::string s = rv.toString(0);
    EXPECT_FALSE(s.empty());
    // Rational typically represented as "1/3"
    EXPECT_NE(s.find('/'), std::string::npos);
}

// ============================================================
// Tests for ValueType write
// ============================================================

TEST_F(ValueTypeGeneralTest_172, DoubleWrite_172) {
    DoubleValue dv;
    dv.value_.push_back(4.2);
    std::ostringstream os;
    dv.write(os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ValueTypeGeneralTest_172, RationalWrite_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(5, 7));
    std::ostringstream os;
    rv.write(os);
    EXPECT_FALSE(os.str().empty());
}

// ============================================================
// Tests for ValueType clone
// ============================================================

TEST_F(ValueTypeGeneralTest_172, DoubleClone_172) {
    DoubleValue dv;
    dv.value_.push_back(9.9);
    auto cloned = dv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_NEAR(cloned->toFloat(0), 9.9f, 0.1f);
}

TEST_F(ValueTypeGeneralTest_172, RationalClone_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(2, 3));
    auto cloned = rv.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
}

// ============================================================
// Tests for ValueType copy constructor and assignment
// ============================================================

TEST_F(ValueTypeGeneralTest_172, DoubleCopyConstructor_172) {
    DoubleValue dv;
    dv.value_.push_back(1.1);
    dv.value_.push_back(2.2);
    DoubleValue dv2(dv);
    EXPECT_EQ(dv2.count(), 2u);
    EXPECT_NEAR(dv2.toFloat(0), 1.1f, 0.01f);
    EXPECT_NEAR(dv2.toFloat(1), 2.2f, 0.01f);
}

TEST_F(ValueTypeGeneralTest_172, DoubleAssignment_172) {
    DoubleValue dv;
    dv.value_.push_back(5.5);
    DoubleValue dv2;
    dv2 = dv;
    EXPECT_EQ(dv2.count(), 1u);
    EXPECT_NEAR(dv2.toFloat(0), 5.5f, 0.01f);
}

// ============================================================
// Tests for ValueType size
// ============================================================

TEST_F(ValueTypeGeneralTest_172, DoubleSize_172) {
    DoubleValue dv;
    EXPECT_EQ(dv.size(), 0u);
    dv.value_.push_back(1.0);
    EXPECT_EQ(dv.size(), sizeof(double));
}

TEST_F(ValueTypeGeneralTest_172, FloatSize_172) {
    FloatValue fv;
    fv.value_.push_back(1.0f);
    EXPECT_EQ(fv.size(), sizeof(float));
}

TEST_F(ValueTypeGeneralTest_172, RationalSize_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 2));
    // Rational is a pair of int32_t, so size should be 8
    EXPECT_EQ(rv.size(), 8u);
}

// ============================================================
// Tests for ValueType dataArea
// ============================================================

TEST_F(ValueTypeGeneralTest_172, DataAreaInitiallyEmpty_172) {
    DoubleValue dv;
    EXPECT_EQ(dv.sizeDataArea(), 0u);
    DataBuf buf = dv.dataArea();
    EXPECT_EQ(buf.size(), 0u);
}

TEST_F(ValueTypeGeneralTest_172, SetDataArea_172) {
    DoubleValue dv;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = dv.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.sizeDataArea(), sizeof(data));
    DataBuf buf = dv.dataArea();
    EXPECT_EQ(buf.size(), sizeof(data));
}

// ============================================================
// Tests for Value::create factory
// ============================================================

TEST_F(ValueTypeGeneralTest_172, CreateDoubleValue_172) {
    auto val = Value::create(tiffDouble);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), tiffDouble);
}

TEST_F(ValueTypeGeneralTest_172, CreateFloatValue_172) {
    auto val = Value::create(tiffFloat);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), tiffFloat);
}

TEST_F(ValueTypeGeneralTest_172, CreateRationalValue_172) {
    auto val = Value::create(signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), signedRational);
}

TEST_F(ValueTypeGeneralTest_172, CreateURationalValue_172) {
    auto val = Value::create(unsignedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), unsignedRational);
}

// ============================================================
// Tests for ok() after various operations
// ============================================================

TEST_F(ValueTypeGeneralTest_172, OkAfterToRationalDouble_172) {
    DoubleValue dv;
    dv.value_.push_back(1.234);
    dv.toRational(0);
    EXPECT_TRUE(dv.ok());
}

TEST_F(ValueTypeGeneralTest_172, OkAfterToRationalFloat_172) {
    FloatValue fv;
    fv.value_.push_back(1.234f);
    fv.toRational(0);
    EXPECT_TRUE(fv.ok());
}

TEST_F(ValueTypeGeneralTest_172, OkAfterToRationalRational_172) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 2));
    rv.toRational(0);
    EXPECT_TRUE(rv.ok());
}

// ============================================================
// Tests for reading from string
// ============================================================

TEST_F(ValueTypeGeneralTest_172, DoubleReadFromString_172) {
    DoubleValue dv;
    int result = dv.read("3.14");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_NEAR(dv.toFloat(0), 3.14f, 0.01f);
}

TEST_F(ValueTypeGeneralTest_172, DoubleReadMultipleFromString_172) {
    DoubleValue dv;
    int result = dv.read("1.0 2.0 3.0");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(dv.count(), 3u);
}

TEST_F(ValueTypeGeneralTest_172, RationalReadFromString_172) {
    RationalValue rv;
    int result = rv.read("1/2");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(rv.count(), 1u);
    Rational r = rv.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

TEST_F(ValueTypeGeneralTest_172, URationalReadFromString_172) {
    URationalValue urv;
    int result = urv.read("3/4");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(urv.count(), 1u);
}

// ============================================================
// Boundary tests for double toRational
// ============================================================

TEST_F(ValueTypeDoubleToRationalTest_172, VerySmallPositiveValue_172) {
    dv.value_.push_back(0.0001);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    if (r.second != 0) {
        double result = static_cast<double>(r.first) / r.second;
        EXPECT_NEAR(result, 0.0001, 0.01);
    }
}

TEST_F(ValueTypeDoubleToRationalTest_172, NegativeOneValue_172) {
    dv.value_.push_back(-1.0);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, -1.0, 0.01);
}

TEST_F(ValueTypeDoubleToRationalTest_172, OneValue_172) {
    dv.value_.push_back(1.0);
    Rational r = dv.toRational(0);
    EXPECT_TRUE(dv.ok());
    EXPECT_NE(r.second, 0);
    double result = static_cast<double>(r.first) / r.second;
    EXPECT_NEAR(result, 1.0, 0.001);
}

// ============================================================
// Tests for ValueType constructed with value
// ============================================================

TEST_F(ValueTypeGeneralTest_172, ConstructWithValue_172) {
    DoubleValue dv(3.14, tiffDouble);
    EXPECT_EQ(dv.count(), 1u);
    EXPECT_NEAR(dv.toFloat(0), 3.14f, 0.01f);
    EXPECT_EQ(dv.typeId(), tiffDouble);
}

TEST_F(ValueTypeGeneralTest_172, RationalConstructWithValue_172) {
    RationalValue rv(Rational(5, 8), signedRational);
    EXPECT_EQ(rv.count(), 1u);
    Rational r = rv.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 8);
}

// ============================================================
// Tests for empty ValueType
// ============================================================

TEST_F(ValueTypeGeneralTest_172, EmptyDoubleValueCount_172) {
    DoubleValue dv;
    EXPECT_EQ(dv.count(), 0u);
    EXPECT_EQ(dv.size(), 0u);
}

TEST_F(ValueTypeGeneralTest_172, EmptyDoubleValueToRationalThrows_172) {
    DoubleValue dv;
    EXPECT_THROW(dv.toRational(0), std::out_of_range);
}

TEST_F(ValueTypeGeneralTest_172, EmptyDoubleValueToFloatThrows_172) {
    DoubleValue dv;
    EXPECT_THROW(dv.toFloat(0), std::out_of_range);
}

TEST_F(ValueTypeGeneralTest_172, EmptyDoubleValueToInt64Throws_172) {
    DoubleValue dv;
    EXPECT_THROW(dv.toInt64(0), std::out_of_range);
}
