#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <stdexcept>
#include <sstream>

using namespace Exiv2;

// Type aliases for convenience
using RationalValue = ValueType<Rational>;
using URationalValue = ValueType<URational>;
using FloatValue = ValueType<float>;
using DoubleValue = ValueType<double>;
using UInt16Value = ValueType<uint16_t>;
using Int32Value = ValueType<int32_t>;
using UInt32Value = ValueType<uint32_t>;

// ===========================================================================
// Tests for ValueType<Rational>::toFloat (the primary focus from partial code)
// ===========================================================================

class RationalToFloatTest_166 : public ::testing::Test {
protected:
    void SetUp() override {
        rv_ = std::make_unique<RationalValue>();
    }
    std::unique_ptr<RationalValue> rv_;
};

TEST_F(RationalToFloatTest_166, NormalRationalToFloat_166) {
    rv_->value_.push_back(Rational(1, 2));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 0.5f);
}

TEST_F(RationalToFloatTest_166, NegativeNumeratorToFloat_166) {
    rv_->value_.push_back(Rational(-3, 4));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, -0.75f);
}

TEST_F(RationalToFloatTest_166, NegativeDenominatorToFloat_166) {
    rv_->value_.push_back(Rational(3, -4));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, -0.75f);
}

TEST_F(RationalToFloatTest_166, BothNegativeToFloat_166) {
    rv_->value_.push_back(Rational(-5, -2));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 2.5f);
}

TEST_F(RationalToFloatTest_166, ZeroDenominatorReturnsZeroAndNotOk_166) {
    rv_->value_.push_back(Rational(5, 0));
    float result = rv_->toFloat(0);
    EXPECT_FALSE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(RationalToFloatTest_166, ZeroNumeratorToFloat_166) {
    rv_->value_.push_back(Rational(0, 5));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(RationalToFloatTest_166, BothZeroToFloat_166) {
    rv_->value_.push_back(Rational(0, 0));
    float result = rv_->toFloat(0);
    EXPECT_FALSE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(RationalToFloatTest_166, MultipleValuesSelectCorrectIndex_166) {
    rv_->value_.push_back(Rational(1, 3));
    rv_->value_.push_back(Rational(2, 5));
    rv_->value_.push_back(Rational(7, 8));

    float result0 = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result0, static_cast<float>(1) / 3);

    float result1 = rv_->toFloat(1);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result1, static_cast<float>(2) / 5);

    float result2 = rv_->toFloat(2);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result2, static_cast<float>(7) / 8);
}

TEST_F(RationalToFloatTest_166, OutOfRangeIndexThrows_166) {
    rv_->value_.push_back(Rational(1, 2));
    EXPECT_THROW(rv_->toFloat(1), std::out_of_range);
}

TEST_F(RationalToFloatTest_166, EmptyValueThrows_166) {
    EXPECT_THROW(rv_->toFloat(0), std::out_of_range);
}

TEST_F(RationalToFloatTest_166, LargeValuesToFloat_166) {
    rv_->value_.push_back(Rational(1000000, 1));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 1000000.0f);
}

TEST_F(RationalToFloatTest_166, WholeNumberRational_166) {
    rv_->value_.push_back(Rational(10, 1));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 10.0f);
}

TEST_F(RationalToFloatTest_166, OkResetsAfterZeroDenominator_166) {
    rv_->value_.push_back(Rational(1, 0));
    rv_->value_.push_back(Rational(1, 2));

    rv_->toFloat(0);
    EXPECT_FALSE(rv_->ok());

    rv_->toFloat(1);
    EXPECT_TRUE(rv_->ok());
}

// ===========================================================================
// Tests for ValueType<URational>::toFloat
// ===========================================================================

class URationalToFloatTest_166 : public ::testing::Test {
protected:
    void SetUp() override {
        urv_ = std::make_unique<URationalValue>();
    }
    std::unique_ptr<URationalValue> urv_;
};

TEST_F(URationalToFloatTest_166, NormalURationalToFloat_166) {
    urv_->value_.push_back(URational(3, 4));
    float result = urv_->toFloat(0);
    EXPECT_TRUE(urv_->ok());
    EXPECT_FLOAT_EQ(result, 0.75f);
}

TEST_F(URationalToFloatTest_166, ZeroDenominatorURational_166) {
    urv_->value_.push_back(URational(5, 0));
    float result = urv_->toFloat(0);
    EXPECT_FALSE(urv_->ok());
    EXPECT_FLOAT_EQ(result, 0.0f);
}

TEST_F(URationalToFloatTest_166, ZeroNumeratorURational_166) {
    urv_->value_.push_back(URational(0, 10));
    float result = urv_->toFloat(0);
    EXPECT_TRUE(urv_->ok());
    EXPECT_FLOAT_EQ(result, 0.0f);
}

// ===========================================================================
// Tests for ValueType<T>::count()
// ===========================================================================

TEST(ValueTypeCountTest_166, EmptyValueHasZeroCount_166) {
    RationalValue rv;
    EXPECT_EQ(rv.count(), 0u);
}

TEST(ValueTypeCountTest_166, SingleValueCount_166) {
    RationalValue rv(Rational(1, 2), TypeId::signedRational);
    EXPECT_EQ(rv.count(), 1u);
}

TEST(ValueTypeCountTest_166, MultipleValuesCount_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 2));
    rv.value_.push_back(Rational(3, 4));
    rv.value_.push_back(Rational(5, 6));
    EXPECT_EQ(rv.count(), 3u);
}

// ===========================================================================
// Tests for ValueType<Rational>::toInt64
// ===========================================================================

TEST(RationalToInt64Test_166, NormalRationalToInt64_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(7, 2));
    int64_t result = rv.toInt64(0);
    EXPECT_EQ(result, 3);  // 7/2 = 3 (integer division or truncation)
}

TEST(RationalToInt64Test_166, ZeroDenominatorToInt64_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(5, 0));
    int64_t result = rv.toInt64(0);
    EXPECT_FALSE(rv.ok());
    EXPECT_EQ(result, 0);
}

// ===========================================================================
// Tests for ValueType<Rational>::toUint32
// ===========================================================================

TEST(RationalToUint32Test_166, NormalRationalToUint32_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(9, 3));
    uint32_t result = rv.toUint32(0);
    EXPECT_EQ(result, 3u);
}

// ===========================================================================
// Tests for ValueType<Rational>::toRational
// ===========================================================================

TEST(RationalToRationalTest_166, ReturnsExactRational_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(3, 7));
    Rational result = rv.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

// ===========================================================================
// Tests for ValueType<URational>::toRational
// ===========================================================================

TEST(URationalToRationalTest_166, ReturnsConvertedRational_166) {
    URationalValue urv;
    urv.value_.push_back(URational(5, 9));
    Rational result = urv.toRational(0);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 9);
}

// ===========================================================================
// Tests for ValueType<float>::toFloat
// ===========================================================================

TEST(FloatToFloatTest_166, NormalFloatToFloat_166) {
    FloatValue fv;
    fv.value_.push_back(3.14f);
    float result = fv.toFloat(0);
    EXPECT_FLOAT_EQ(result, 3.14f);
}

// ===========================================================================
// Tests for ValueType<float>::toRational
// ===========================================================================

TEST(FloatToRationalTest_166, FloatToRationalConversion_166) {
    FloatValue fv;
    fv.value_.push_back(0.5f);
    Rational result = fv.toRational(0);
    // The result should approximate 0.5
    EXPECT_NE(result.second, 0);
    float approx = static_cast<float>(result.first) / result.second;
    EXPECT_NEAR(approx, 0.5f, 0.001f);
}

// ===========================================================================
// Tests for ValueType<double>::toRational
// ===========================================================================

TEST(DoubleToRationalTest_166, DoubleToRationalConversion_166) {
    DoubleValue dv;
    dv.value_.push_back(0.25);
    Rational result = dv.toRational(0);
    EXPECT_NE(result.second, 0);
    double approx = static_cast<double>(result.first) / result.second;
    EXPECT_NEAR(approx, 0.25, 0.001);
}

// ===========================================================================
// Tests for ValueType<double>::toFloat
// ===========================================================================

TEST(DoubleToFloatTest_166, NormalDoubleToFloat_166) {
    DoubleValue dv;
    dv.value_.push_back(2.718281828);
    float result = dv.toFloat(0);
    EXPECT_NEAR(result, 2.718281828f, 0.0001f);
}

// ===========================================================================
// Tests for ValueType<double>::toInt64
// ===========================================================================

TEST(DoubleToInt64Test_166, NormalDoubleToInt64_166) {
    DoubleValue dv;
    dv.value_.push_back(42.9);
    int64_t result = dv.toInt64(0);
    EXPECT_EQ(result, 42);
}

// ===========================================================================
// Tests for ValueType<float>::toInt64
// ===========================================================================

TEST(FloatToInt64Test_166, NormalFloatToInt64_166) {
    FloatValue fv;
    fv.value_.push_back(99.1f);
    int64_t result = fv.toInt64(0);
    EXPECT_EQ(result, 99);
}

// ===========================================================================
// Tests for ValueType copy constructor and assignment
// ===========================================================================

TEST(RationalCopyTest_166, CopyConstructor_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 3));
    rv.value_.push_back(Rational(2, 5));

    RationalValue rv2(rv);
    EXPECT_EQ(rv2.count(), 2u);
    EXPECT_FLOAT_EQ(rv2.toFloat(0), static_cast<float>(1) / 3);
    EXPECT_FLOAT_EQ(rv2.toFloat(1), static_cast<float>(2) / 5);
}

TEST(RationalCopyTest_166, AssignmentOperator_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(4, 5));

    RationalValue rv2;
    rv2 = rv;
    EXPECT_EQ(rv2.count(), 1u);
    EXPECT_FLOAT_EQ(rv2.toFloat(0), 0.8f);
}

// ===========================================================================
// Tests for ValueType write
// ===========================================================================

TEST(RationalWriteTest_166, WriteToStream_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 2));
    std::ostringstream os;
    rv.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

// ===========================================================================
// Tests for ValueType toString
// ===========================================================================

TEST(RationalToStringTest_166, ToStringNormal_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(1, 2));
    std::string result = rv.toString(0);
    EXPECT_FALSE(result.empty());
}

// ===========================================================================
// Tests for ValueType clone
// ===========================================================================

TEST(RationalCloneTest_166, ClonePreservesValues_166) {
    RationalValue rv;
    rv.value_.push_back(Rational(3, 7));
    auto cloned = rv.clone();
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_FLOAT_EQ(cloned->toFloat(0), static_cast<float>(3) / 7);
}

// ===========================================================================
// Tests for ValueType dataArea
// ===========================================================================

TEST(RationalDataAreaTest_166, DefaultDataAreaEmpty_166) {
    RationalValue rv;
    EXPECT_EQ(rv.sizeDataArea(), 0u);
}

TEST(RationalDataAreaTest_166, SetAndGetDataArea_166) {
    RationalValue rv;
    const byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = rv.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(rv.sizeDataArea(), sizeof(data));
    DataBuf buf = rv.dataArea();
    EXPECT_EQ(buf.size(), sizeof(data));
}

// ===========================================================================
// Tests for ValueType<T> with integer types
// ===========================================================================

TEST(UInt16ValueTest_166, ToFloatFromUInt16_166) {
    UInt16Value uv;
    uv.value_.push_back(42);
    float result = uv.toFloat(0);
    EXPECT_FLOAT_EQ(result, 42.0f);
}

TEST(Int32ValueTest_166, ToFloatFromInt32_166) {
    Int32Value iv;
    iv.value_.push_back(-100);
    float result = iv.toFloat(0);
    EXPECT_FLOAT_EQ(result, -100.0f);
}

TEST(UInt32ValueTest_166, ToRationalFromUInt32_166) {
    UInt32Value uv;
    uv.value_.push_back(5);
    Rational r = uv.toRational(0);
    EXPECT_EQ(r.first, 5);
    EXPECT_EQ(r.second, 1);
}

// ===========================================================================
// Tests for Value::create factory
// ===========================================================================

TEST(ValueCreateTest_166, CreateSignedRational_166) {
    auto val = Value::create(TypeId::signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), TypeId::signedRational);
}

TEST(ValueCreateTest_166, CreateUnsignedRational_166) {
    auto val = Value::create(TypeId::unsignedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), TypeId::unsignedRational);
}

// ===========================================================================
// Tests for read from string
// ===========================================================================

TEST(RationalReadStringTest_166, ReadRationalFromString_166) {
    RationalValue rv;
    int result = rv.read("1/2");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(rv.count(), 1u);
    EXPECT_FLOAT_EQ(rv.toFloat(0), 0.5f);
}

TEST(RationalReadStringTest_166, ReadMultipleRationalsFromString_166) {
    RationalValue rv;
    int result = rv.read("1/2 3/4");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(rv.count(), 2u);
    EXPECT_FLOAT_EQ(rv.toFloat(0), 0.5f);
    EXPECT_FLOAT_EQ(rv.toFloat(1), 0.75f);
}

// ===========================================================================
// Tests for ValueType constructor with initial value
// ===========================================================================

TEST(RationalConstructorTest_166, ConstructWithValue_166) {
    RationalValue rv(Rational(5, 8), TypeId::signedRational);
    EXPECT_EQ(rv.count(), 1u);
    EXPECT_FLOAT_EQ(rv.toFloat(0), static_cast<float>(5) / 8);
    EXPECT_EQ(rv.typeId(), TypeId::signedRational);
}

// ===========================================================================
// Edge case: Rational with denominator of 1
// ===========================================================================

TEST_F(RationalToFloatTest_166, DenominatorOne_166) {
    rv_->value_.push_back(Rational(42, 1));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 42.0f);
}

// ===========================================================================
// Edge case: Rational with very large numerator and denominator
// ===========================================================================

TEST_F(RationalToFloatTest_166, LargeNumeratorAndDenominator_166) {
    rv_->value_.push_back(Rational(1000000, 1000000));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, 1.0f);
}

// ===========================================================================
// Edge case: Rational -1/1
// ===========================================================================

TEST_F(RationalToFloatTest_166, NegativeOne_166) {
    rv_->value_.push_back(Rational(-1, 1));
    float result = rv_->toFloat(0);
    EXPECT_TRUE(rv_->ok());
    EXPECT_FLOAT_EQ(result, -1.0f);
}
