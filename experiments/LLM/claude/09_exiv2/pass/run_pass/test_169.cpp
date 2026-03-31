#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cmath>

using namespace Exiv2;

// Type aliases for convenience
using RationalValue = ValueType<Rational>;
using URationalValue = ValueType<URational>;
using UShortValue = ValueType<uint16_t>;
using ULongValue = ValueType<uint32_t>;
using ShortValue = ValueType<int16_t>;
using LongValue = ValueType<int32_t>;
using FloatValue = ValueType<float>;
using DoubleValue = ValueType<double>;

// ===================== RationalValue toRational tests =====================

class ValueTypeRationalTest_169 : public ::testing::Test {
protected:
    void SetUp() override {}
};

TEST_F(ValueTypeRationalTest_169, ToRationalReturnsCorrectValue_169) {
    Rational r{3, 4};
    RationalValue val(r, TypeId::signedRational);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 4);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeRationalTest_169, ToRationalWithMultipleValues_169) {
    RationalValue val;
    val.value_.push_back({1, 2});
    val.value_.push_back({3, 5});
    val.value_.push_back({7, 11});

    Rational r0 = val.toRational(0);
    EXPECT_EQ(r0.first, 1);
    EXPECT_EQ(r0.second, 2);

    Rational r1 = val.toRational(1);
    EXPECT_EQ(r1.first, 3);
    EXPECT_EQ(r1.second, 5);

    Rational r2 = val.toRational(2);
    EXPECT_EQ(r2.first, 7);
    EXPECT_EQ(r2.second, 11);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeRationalTest_169, ToRationalOutOfRangeThrows_169) {
    RationalValue val;
    val.value_.push_back({1, 2});
    EXPECT_THROW(val.toRational(1), std::out_of_range);
}

TEST_F(ValueTypeRationalTest_169, ToRationalEmptyThrows_169) {
    RationalValue val;
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

TEST_F(ValueTypeRationalTest_169, ToRationalZeroDenominator_169) {
    RationalValue val;
    val.value_.push_back({5, 0});
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 5);
    EXPECT_EQ(result.second, 0);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeRationalTest_169, ToRationalNegativeValues_169) {
    RationalValue val;
    val.value_.push_back({-3, 4});
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, -3);
    EXPECT_EQ(result.second, 4);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeRationalTest_169, ToRationalBothNegative_169) {
    RationalValue val;
    val.value_.push_back({-7, -3});
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, -7);
    EXPECT_EQ(result.second, -3);
}

// ===================== URationalValue toRational tests =====================

class ValueTypeURationalTest_169 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_169, ToRationalReturnsCorrectValue_169) {
    URationalValue val;
    val.value_.push_back({3, 4});
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 4);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeURationalTest_169, ToRationalMultipleValues_169) {
    URationalValue val;
    val.value_.push_back({10, 3});
    val.value_.push_back({22, 7});
    
    Rational r0 = val.toRational(0);
    EXPECT_EQ(r0.first, 10);
    EXPECT_EQ(r0.second, 3);

    Rational r1 = val.toRational(1);
    EXPECT_EQ(r1.first, 22);
    EXPECT_EQ(r1.second, 7);
}

TEST_F(ValueTypeURationalTest_169, ToRationalOutOfRange_169) {
    URationalValue val;
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

// ===================== FloatValue toRational tests =====================

class ValueTypeFloatTest_169 : public ::testing::Test {};

TEST_F(ValueTypeFloatTest_169, ToRationalFromFloat_169) {
    FloatValue val;
    val.value_.push_back(0.5f);
    Rational result = val.toRational(0);
    // The result should approximate 0.5
    if (result.second != 0) {
        float approx = static_cast<float>(result.first) / static_cast<float>(result.second);
        EXPECT_NEAR(approx, 0.5f, 0.001f);
    }
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeFloatTest_169, ToRationalFromFloatZero_169) {
    FloatValue val;
    val.value_.push_back(0.0f);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 0);
}

TEST_F(ValueTypeFloatTest_169, ToRationalFromFloatNegative_169) {
    FloatValue val;
    val.value_.push_back(-1.5f);
    Rational result = val.toRational(0);
    if (result.second != 0) {
        float approx = static_cast<float>(result.first) / static_cast<float>(result.second);
        EXPECT_NEAR(approx, -1.5f, 0.001f);
    }
}

TEST_F(ValueTypeFloatTest_169, ToRationalOutOfRange_169) {
    FloatValue val;
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

// ===================== DoubleValue toRational tests =====================

class ValueTypeDoubleTest_169 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_169, ToRationalFromDouble_169) {
    DoubleValue val;
    val.value_.push_back(0.25);
    Rational result = val.toRational(0);
    if (result.second != 0) {
        double approx = static_cast<double>(result.first) / static_cast<double>(result.second);
        EXPECT_NEAR(approx, 0.25, 0.001);
    }
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeDoubleTest_169, ToRationalFromDoubleInteger_169) {
    DoubleValue val;
    val.value_.push_back(5.0);
    Rational result = val.toRational(0);
    if (result.second != 0) {
        double approx = static_cast<double>(result.first) / static_cast<double>(result.second);
        EXPECT_NEAR(approx, 5.0, 0.001);
    }
}

TEST_F(ValueTypeDoubleTest_169, ToRationalOutOfRange_169) {
    DoubleValue val;
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

// ===================== Integer types toRational tests =====================

class ValueTypeIntegerTest_169 : public ::testing::Test {};

TEST_F(ValueTypeIntegerTest_169, UShortToRational_169) {
    UShortValue val;
    val.value_.push_back(42);
    Rational result = val.toRational(0);
    // For integer types, rational should be val/1
    EXPECT_EQ(result.first, 42);
    EXPECT_EQ(result.second, 1);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeIntegerTest_169, LongToRational_169) {
    LongValue val;
    val.value_.push_back(-100);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, -100);
    EXPECT_EQ(result.second, 1);
}

TEST_F(ValueTypeIntegerTest_169, ULongToRational_169) {
    ULongValue val;
    val.value_.push_back(0);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 0);
    EXPECT_EQ(result.second, 1);
}

TEST_F(ValueTypeIntegerTest_169, ShortToRational_169) {
    ShortValue val;
    val.value_.push_back(1);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 1);
    EXPECT_EQ(result.second, 1);
}

TEST_F(ValueTypeIntegerTest_169, IntegerToRationalOutOfRange_169) {
    UShortValue val;
    EXPECT_THROW(val.toRational(0), std::out_of_range);
}

// ===================== General ValueType tests =====================

class ValueTypeGeneralTest_169 : public ::testing::Test {};

TEST_F(ValueTypeGeneralTest_169, CountReturnsCorrectSize_169) {
    RationalValue val;
    EXPECT_EQ(val.count(), 0u);
    val.value_.push_back({1, 2});
    EXPECT_EQ(val.count(), 1u);
    val.value_.push_back({3, 4});
    EXPECT_EQ(val.count(), 2u);
}

TEST_F(ValueTypeGeneralTest_169, TypeIdIsCorrect_169) {
    RationalValue val;
    EXPECT_EQ(val.typeId(), getType<Rational>());
}

TEST_F(ValueTypeGeneralTest_169, URationalTypeId_169) {
    URationalValue val;
    EXPECT_EQ(val.typeId(), getType<URational>());
}

TEST_F(ValueTypeGeneralTest_169, CopyConstructor_169) {
    RationalValue val;
    val.value_.push_back({5, 6});
    val.value_.push_back({7, 8});

    RationalValue copy(val);
    EXPECT_EQ(copy.count(), 2u);
    Rational r0 = copy.toRational(0);
    EXPECT_EQ(r0.first, 5);
    EXPECT_EQ(r0.second, 6);
    Rational r1 = copy.toRational(1);
    EXPECT_EQ(r1.first, 7);
    EXPECT_EQ(r1.second, 8);
}

TEST_F(ValueTypeGeneralTest_169, AssignmentOperator_169) {
    RationalValue val1;
    val1.value_.push_back({1, 2});

    RationalValue val2;
    val2.value_.push_back({3, 4});
    val2.value_.push_back({5, 6});

    val1 = val2;
    EXPECT_EQ(val1.count(), 2u);
    Rational r = val1.toRational(0);
    EXPECT_EQ(r.first, 3);
    EXPECT_EQ(r.second, 4);
}

TEST_F(ValueTypeGeneralTest_169, CloneProducesCopy_169) {
    RationalValue val;
    val.value_.push_back({9, 10});
    auto cloned = val.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    Rational r = cloned->toRational(0);
    EXPECT_EQ(r.first, 9);
    EXPECT_EQ(r.second, 10);
}

TEST_F(ValueTypeGeneralTest_169, OkFlagSetAfterToRational_169) {
    RationalValue val;
    val.value_.push_back({1, 1});
    val.toRational(0);
    EXPECT_TRUE(val.ok());
}

TEST_F(ValueTypeGeneralTest_169, WriteToStream_169) {
    RationalValue val;
    val.value_.push_back({1, 2});
    std::ostringstream os;
    val.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTypeGeneralTest_169, ToStringNotEmpty_169) {
    RationalValue val;
    val.value_.push_back({3, 4});
    std::string s = val.toString(0);
    EXPECT_FALSE(s.empty());
}

// ===================== toInt64 tests =====================

class ValueTypeToInt64Test_169 : public ::testing::Test {};

TEST_F(ValueTypeToInt64Test_169, RationalToInt64_169) {
    RationalValue val;
    val.value_.push_back({10, 3});
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 3); // 10/3 = 3
}

TEST_F(ValueTypeToInt64Test_169, RationalToInt64ZeroDenom_169) {
    RationalValue val;
    val.value_.push_back({10, 0});
    // Behavior with zero denominator - just verify it doesn't crash
    // The result is implementation defined
    val.toInt64(0);
}

TEST_F(ValueTypeToInt64Test_169, UShortToInt64_169) {
    UShortValue val;
    val.value_.push_back(255);
    EXPECT_EQ(val.toInt64(0), 255);
}

TEST_F(ValueTypeToInt64Test_169, LongToInt64_169) {
    LongValue val;
    val.value_.push_back(-42);
    EXPECT_EQ(val.toInt64(0), -42);
}

TEST_F(ValueTypeToInt64Test_169, DoubleToInt64_169) {
    DoubleValue val;
    val.value_.push_back(3.9);
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, 3);
}

TEST_F(ValueTypeToInt64Test_169, FloatToInt64_169) {
    FloatValue val;
    val.value_.push_back(-2.7f);
    int64_t result = val.toInt64(0);
    EXPECT_EQ(result, -2);
}

// ===================== toUint32 tests =====================

class ValueTypeToUint32Test_169 : public ::testing::Test {};

TEST_F(ValueTypeToUint32Test_169, UShortToUint32_169) {
    UShortValue val;
    val.value_.push_back(100);
    EXPECT_EQ(val.toUint32(0), 100u);
}

TEST_F(ValueTypeToUint32Test_169, URationalToUint32_169) {
    URationalValue val;
    val.value_.push_back({15, 4});
    uint32_t result = val.toUint32(0);
    EXPECT_EQ(result, 3u); // 15/4 = 3
}

// ===================== toFloat tests =====================

class ValueTypeToFloatTest_169 : public ::testing::Test {};

TEST_F(ValueTypeToFloatTest_169, RationalToFloat_169) {
    RationalValue val;
    val.value_.push_back({1, 2});
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 0.5f, 0.001f);
}

TEST_F(ValueTypeToFloatTest_169, URationalToFloat_169) {
    URationalValue val;
    val.value_.push_back({3, 4});
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 0.75f, 0.001f);
}

TEST_F(ValueTypeToFloatTest_169, UShortToFloat_169) {
    UShortValue val;
    val.value_.push_back(7);
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 7.0f, 0.001f);
}

TEST_F(ValueTypeToFloatTest_169, FloatToFloat_169) {
    FloatValue val;
    val.value_.push_back(3.14f);
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 3.14f, 0.001f);
}

TEST_F(ValueTypeToFloatTest_169, DoubleToFloat_169) {
    DoubleValue val;
    val.value_.push_back(2.718);
    float result = val.toFloat(0);
    EXPECT_NEAR(result, 2.718f, 0.01f);
}

// ===================== DataArea tests =====================

class ValueTypeDataAreaTest_169 : public ::testing::Test {};

TEST_F(ValueTypeDataAreaTest_169, InitialDataAreaSizeIsZero_169) {
    RationalValue val;
    EXPECT_EQ(val.sizeDataArea(), 0u);
}

TEST_F(ValueTypeDataAreaTest_169, SetAndRetrieveDataArea_169) {
    RationalValue val;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = val.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.sizeDataArea(), sizeof(data));
    
    DataBuf buf = val.dataArea();
    EXPECT_EQ(buf.size(), sizeof(data));
}

// ===================== Read from string tests =====================

class ValueTypeReadTest_169 : public ::testing::Test {};

TEST_F(ValueTypeReadTest_169, ReadRationalFromString_169) {
    RationalValue val;
    int result = val.read("1/2");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.count(), 1u);
    Rational r = val.toRational(0);
    EXPECT_EQ(r.first, 1);
    EXPECT_EQ(r.second, 2);
}

TEST_F(ValueTypeReadTest_169, ReadMultipleRationalsFromString_169) {
    RationalValue val;
    int result = val.read("1/2 3/4");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.count(), 2u);
}

TEST_F(ValueTypeReadTest_169, ReadUShortFromString_169) {
    UShortValue val;
    int result = val.read("42");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.toInt64(0), 42);
}

TEST_F(ValueTypeReadTest_169, ReadMultipleUShortsFromString_169) {
    UShortValue val;
    int result = val.read("10 20 30");
    EXPECT_EQ(result, 0);
    EXPECT_EQ(val.count(), 3u);
    EXPECT_EQ(val.toInt64(0), 10);
    EXPECT_EQ(val.toInt64(1), 20);
    EXPECT_EQ(val.toInt64(2), 30);
}

// ===================== Explicit TypeId constructor tests =====================

class ValueTypeConstructorTest_169 : public ::testing::Test {};

TEST_F(ValueTypeConstructorTest_169, ConstructWithValue_169) {
    Rational r{7, 13};
    RationalValue val(r, TypeId::signedRational);
    EXPECT_EQ(val.count(), 1u);
    EXPECT_EQ(val.typeId(), TypeId::signedRational);
    Rational result = val.toRational(0);
    EXPECT_EQ(result.first, 7);
    EXPECT_EQ(result.second, 13);
}

TEST_F(ValueTypeConstructorTest_169, DefaultConstructorEmptyValue_169) {
    RationalValue val;
    EXPECT_EQ(val.count(), 0u);
}

// ===================== Size tests =====================

class ValueTypeSizeTest_169 : public ::testing::Test {};

TEST_F(ValueTypeSizeTest_169, SizeEmptyValue_169) {
    RationalValue val;
    EXPECT_EQ(val.size(), 0u);
}

TEST_F(ValueTypeSizeTest_169, SizeWithOneRational_169) {
    RationalValue val;
    val.value_.push_back({1, 2});
    // Rational is two int32_t = 8 bytes
    EXPECT_EQ(val.size(), 8u);
}

TEST_F(ValueTypeSizeTest_169, SizeWithMultipleRationals_169) {
    RationalValue val;
    val.value_.push_back({1, 2});
    val.value_.push_back({3, 4});
    EXPECT_EQ(val.size(), 16u);
}

TEST_F(ValueTypeSizeTest_169, SizeUShort_169) {
    UShortValue val;
    val.value_.push_back(1);
    EXPECT_EQ(val.size(), 2u);
}

TEST_F(ValueTypeSizeTest_169, SizeULong_169) {
    ULongValue val;
    val.value_.push_back(1);
    EXPECT_EQ(val.size(), 4u);
}

// ===================== Boundary: Large index tests =====================

class ValueTypeBoundaryTest_169 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_169, LastElementAccessible_169) {
    RationalValue val;
    for (int i = 0; i < 100; ++i) {
        val.value_.push_back({i, i + 1});
    }
    EXPECT_EQ(val.count(), 100u);
    Rational r = val.toRational(99);
    EXPECT_EQ(r.first, 99);
    EXPECT_EQ(r.second, 100);
}

TEST_F(ValueTypeBoundaryTest_169, OneOverBoundaryThrows_169) {
    RationalValue val;
    for (int i = 0; i < 100; ++i) {
        val.value_.push_back({i, i + 1});
    }
    EXPECT_THROW(val.toRational(100), std::out_of_range);
}

// ===================== Value::create factory tests =====================

class ValueCreateTest_169 : public ::testing::Test {};

TEST_F(ValueCreateTest_169, CreateSignedRational_169) {
    auto val = Value::create(TypeId::signedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), TypeId::signedRational);
}

TEST_F(ValueCreateTest_169, CreateUnsignedRational_169) {
    auto val = Value::create(TypeId::unsignedRational);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), TypeId::unsignedRational);
}

TEST_F(ValueCreateTest_169, CreateUnsignedShort_169) {
    auto val = Value::create(TypeId::unsignedShort);
    ASSERT_NE(val, nullptr);
    EXPECT_EQ(val->typeId(), TypeId::unsignedShort);
}
