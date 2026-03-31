#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <cmath>
#include <limits>
#include <sstream>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<float>
// ============================================================================

class ValueTypeFloatTest_159 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ValueTypeFloatTest_159, DefaultConstructor_159) {
    ValueType<float> v;
    EXPECT_EQ(v.count(), 0u);
    EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeFloatTest_159, ConstructWithValue_159) {
    ValueType<float> v(3.14f, TypeId::tiffFloat);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

TEST_F(ValueTypeFloatTest_159, ToInt64_NormalValue_159) {
    ValueType<float> v(42.7f, TypeId::tiffFloat);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 42);
}

TEST_F(ValueTypeFloatTest_159, ToInt64_NegativeValue_159) {
    ValueType<float> v(-99.9f, TypeId::tiffFloat);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, -99);
}

TEST_F(ValueTypeFloatTest_159, ToInt64_Zero_159) {
    ValueType<float> v(0.0f, TypeId::tiffFloat);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 0);
}

TEST_F(ValueTypeFloatTest_159, ToInt64_LargePositive_159) {
    ValueType<float> v(1.0e10f, TypeId::tiffFloat);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, static_cast<int64_t>(1.0e10f));
}

TEST_F(ValueTypeFloatTest_159, ToInt64_SmallFraction_159) {
    ValueType<float> v(0.001f, TypeId::tiffFloat);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 0);
}

TEST_F(ValueTypeFloatTest_159, ToUint32_NormalValue_159) {
    ValueType<float> v(42.7f, TypeId::tiffFloat);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 42u);
}

TEST_F(ValueTypeFloatTest_159, ToFloat_159) {
    ValueType<float> v(2.5f, TypeId::tiffFloat);
    EXPECT_FLOAT_EQ(v.toFloat(0), 2.5f);
}

TEST_F(ValueTypeFloatTest_159, ToRational_159) {
    ValueType<float> v(0.5f, TypeId::tiffFloat);
    Rational r = v.toRational(0);
    // The rational should approximate 0.5
    EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.5, 0.001);
}

TEST_F(ValueTypeFloatTest_159, Count_MultipleValues_159) {
    ValueType<float> v;
    v.value_.push_back(1.0f);
    v.value_.push_back(2.0f);
    v.value_.push_back(3.0f);
    EXPECT_EQ(v.count(), 3u);
}

TEST_F(ValueTypeFloatTest_159, ToInt64_MultipleValues_159) {
    ValueType<float> v;
    v.value_.push_back(10.5f);
    v.value_.push_back(20.9f);
    v.value_.push_back(30.1f);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

TEST_F(ValueTypeFloatTest_159, ToString_159) {
    ValueType<float> v(1.5f, TypeId::tiffFloat);
    std::string s = v.toString(0);
    EXPECT_FALSE(s.empty());
}

TEST_F(ValueTypeFloatTest_159, Write_159) {
    ValueType<float> v(1.5f, TypeId::tiffFloat);
    std::ostringstream os;
    v.write(os);
    EXPECT_FALSE(os.str().empty());
}

TEST_F(ValueTypeFloatTest_159, Clone_159) {
    ValueType<float> v(7.5f, TypeId::tiffFloat);
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
    EXPECT_FLOAT_EQ(cloned->toFloat(0), 7.5f);
}

TEST_F(ValueTypeFloatTest_159, ReadFromString_159) {
    ValueType<float> v;
    v.read("3.14");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_NEAR(v.toFloat(0), 3.14f, 0.01f);
}

TEST_F(ValueTypeFloatTest_159, ReadMultipleFromString_159) {
    ValueType<float> v;
    v.read("1.0 2.0 3.0");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_FLOAT_EQ(v.toFloat(0), 1.0f);
    EXPECT_FLOAT_EQ(v.toFloat(1), 2.0f);
    EXPECT_FLOAT_EQ(v.toFloat(2), 3.0f);
}

TEST_F(ValueTypeFloatTest_159, DataArea_Empty_159) {
    ValueType<float> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeFloatTest_159, SetDataArea_159) {
    ValueType<float> v;
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    int result = v.setDataArea(data, sizeof(data));
    EXPECT_EQ(result, 0);
    EXPECT_EQ(v.sizeDataArea(), sizeof(data));
}

TEST_F(ValueTypeFloatTest_159, CopyBytes_159) {
    ValueType<float> v(1.0f, TypeId::tiffFloat);
    byte buf[4];
    size_t copied = v.copy(buf, littleEndian);
    EXPECT_EQ(copied, sizeof(float));
}

// ============================================================================
// Tests for ValueType<double>
// ============================================================================

class ValueTypeDoubleTest_159 : public ::testing::Test {};

TEST_F(ValueTypeDoubleTest_159, DefaultConstructor_159) {
    ValueType<double> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_159, ToInt64_NormalValue_159) {
    ValueType<double> v(42.7, TypeId::tiffDouble);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 42);
}

TEST_F(ValueTypeDoubleTest_159, ToInt64_NegativeValue_159) {
    ValueType<double> v(-99.9, TypeId::tiffDouble);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, -99);
}

TEST_F(ValueTypeDoubleTest_159, ToUint32_NormalValue_159) {
    ValueType<double> v(42.7, TypeId::tiffDouble);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 42u);
}

TEST_F(ValueTypeDoubleTest_159, ToFloat_159) {
    ValueType<double> v(2.5, TypeId::tiffDouble);
    EXPECT_FLOAT_EQ(v.toFloat(0), 2.5f);
}

TEST_F(ValueTypeDoubleTest_159, ToRational_159) {
    ValueType<double> v(0.5, TypeId::tiffDouble);
    Rational r = v.toRational(0);
    EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.5, 0.001);
}

TEST_F(ValueTypeDoubleTest_159, ToInt64_Zero_159) {
    ValueType<double> v(0.0, TypeId::tiffDouble);
    EXPECT_EQ(v.toInt64(0), 0);
}

TEST_F(ValueTypeDoubleTest_159, Clone_159) {
    ValueType<double> v(3.14, TypeId::tiffDouble);
    auto cloned = v.clone();
    EXPECT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->count(), 1u);
}

// ============================================================================
// Tests for ValueType<Rational>
// ============================================================================

class ValueTypeRationalTest_159 : public ::testing::Test {};

TEST_F(ValueTypeRationalTest_159, DefaultConstructor_159) {
    ValueType<Rational> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_159, ConstructWithValue_159) {
    Rational r(1, 2);
    ValueType<Rational> v(r, TypeId::signedRational);
    EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeRationalTest_159, ToInt64_SimpleRational_159) {
    Rational r(10, 3);
    ValueType<Rational> v(r, TypeId::signedRational);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);
}

TEST_F(ValueTypeRationalTest_159, ToInt64_NegativeRational_159) {
    Rational r(-10, 3);
    ValueType<Rational> v(r, TypeId::signedRational);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, -3);
}

TEST_F(ValueTypeRationalTest_159, ToUint32_SimpleRational_159) {
    Rational r(10, 3);
    ValueType<Rational> v(r, TypeId::signedRational);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u);
}

TEST_F(ValueTypeRationalTest_159, ToFloat_Rational_159) {
    Rational r(1, 2);
    ValueType<Rational> v(r, TypeId::signedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
}

TEST_F(ValueTypeRationalTest_159, ToRational_159) {
    Rational r(3, 7);
    ValueType<Rational> v(r, TypeId::signedRational);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

TEST_F(ValueTypeRationalTest_159, ToInt64_ZeroDenominator_159) {
    Rational r(5, 0);
    ValueType<Rational> v(r, TypeId::signedRational);
    // Division by zero behavior - just check it doesn't crash
    // The result is implementation-defined
    EXPECT_NO_THROW(v.toInt64(0));
}

TEST_F(ValueTypeRationalTest_159, ToFloat_ZeroDenominator_159) {
    Rational r(5, 0);
    ValueType<Rational> v(r, TypeId::signedRational);
    EXPECT_NO_THROW(v.toFloat(0));
}

TEST_F(ValueTypeRationalTest_159, ToString_159) {
    Rational r(1, 2);
    ValueType<Rational> v(r, TypeId::signedRational);
    std::string s = v.toString(0);
    EXPECT_FALSE(s.empty());
    EXPECT_NE(s.find("/"), std::string::npos);
}

// ============================================================================
// Tests for ValueType<URational>
// ============================================================================

class ValueTypeURationalTest_159 : public ::testing::Test {};

TEST_F(ValueTypeURationalTest_159, DefaultConstructor_159) {
    ValueType<URational> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeURationalTest_159, ToInt64_159) {
    URational r(10, 3);
    ValueType<URational> v(r, TypeId::unsignedRational);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 3);
}

TEST_F(ValueTypeURationalTest_159, ToUint32_159) {
    URational r(10, 3);
    ValueType<URational> v(r, TypeId::unsignedRational);
    uint32_t result = v.toUint32(0);
    EXPECT_EQ(result, 3u);
}

TEST_F(ValueTypeURationalTest_159, ToFloat_URational_159) {
    URational r(1, 4);
    ValueType<URational> v(r, TypeId::unsignedRational);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeURationalTest_159, ToRational_URational_159) {
    URational r(3, 7);
    ValueType<URational> v(r, TypeId::unsignedRational);
    Rational result = v.toRational(0);
    EXPECT_EQ(result.first, 3);
    EXPECT_EQ(result.second, 7);
}

// ============================================================================
// Tests for ValueType<uint16_t> (unsigned short)
// ============================================================================

class ValueTypeUint16Test_159 : public ::testing::Test {};

TEST_F(ValueTypeUint16Test_159, DefaultConstructor_159) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUint16Test_159, ConstructWithValue_159) {
    ValueType<uint16_t> v(42, TypeId::unsignedShort);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 42);
}

TEST_F(ValueTypeUint16Test_159, ToFloat_159) {
    ValueType<uint16_t> v(42, TypeId::unsignedShort);
    EXPECT_FLOAT_EQ(v.toFloat(0), 42.0f);
}

TEST_F(ValueTypeUint16Test_159, ToRational_159) {
    ValueType<uint16_t> v(5, TypeId::unsignedShort);
    Rational r = v.toRational(0);
    EXPECT_NEAR(static_cast<double>(r.first) / r.second, 5.0, 0.001);
}

TEST_F(ValueTypeUint16Test_159, ReadFromBytes_159) {
    byte buf[4] = {0x01, 0x00, 0x02, 0x00};
    ValueType<uint16_t> v;
    v.read(buf, 4, littleEndian);
    EXPECT_EQ(v.count(), 2u);
    EXPECT_EQ(v.toInt64(0), 1);
    EXPECT_EQ(v.toInt64(1), 2);
}

TEST_F(ValueTypeUint16Test_159, CopyAndVerify_159) {
    ValueType<uint16_t> v(0x1234, TypeId::unsignedShort);
    byte buf[2] = {0, 0};
    size_t copied = v.copy(buf, bigEndian);
    EXPECT_EQ(copied, 2u);
    EXPECT_EQ(buf[0], 0x12);
    EXPECT_EQ(buf[1], 0x34);
}

TEST_F(ValueTypeUint16Test_159, ReadFromString_159) {
    ValueType<uint16_t> v;
    v.read("100");
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), 100);
}

TEST_F(ValueTypeUint16Test_159, ReadMultipleFromString_159) {
    ValueType<uint16_t> v;
    v.read("10 20 30");
    EXPECT_EQ(v.count(), 3u);
    EXPECT_EQ(v.toInt64(0), 10);
    EXPECT_EQ(v.toInt64(1), 20);
    EXPECT_EQ(v.toInt64(2), 30);
}

// ============================================================================
// Tests for ValueType<int32_t> (signed long)
// ============================================================================

class ValueTypeInt32Test_159 : public ::testing::Test {};

TEST_F(ValueTypeInt32Test_159, ConstructWithValue_159) {
    ValueType<int32_t> v(-100, TypeId::signedLong);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeInt32Test_159, ToFloat_159) {
    ValueType<int32_t> v(-100, TypeId::signedLong);
    EXPECT_FLOAT_EQ(v.toFloat(0), -100.0f);
}

TEST_F(ValueTypeInt32Test_159, ToUint32_159) {
    ValueType<int32_t> v(100, TypeId::signedLong);
    EXPECT_EQ(v.toUint32(0), 100u);
}

// ============================================================================
// Tests for CopyConstructor and Assignment
// ============================================================================

class ValueTypeCopyTest_159 : public ::testing::Test {};

TEST_F(ValueTypeCopyTest_159, CopyConstructor_Float_159) {
    ValueType<float> original(3.14f, TypeId::tiffFloat);
    ValueType<float> copy(original);
    EXPECT_EQ(copy.count(), 1u);
    EXPECT_FLOAT_EQ(copy.toFloat(0), 3.14f);
}

TEST_F(ValueTypeCopyTest_159, AssignmentOperator_Float_159) {
    ValueType<float> original(3.14f, TypeId::tiffFloat);
    ValueType<float> other;
    other = original;
    EXPECT_EQ(other.count(), 1u);
    EXPECT_FLOAT_EQ(other.toFloat(0), 3.14f);
}

TEST_F(ValueTypeCopyTest_159, CopyConstructor_Rational_159) {
    Rational r(1, 2);
    ValueType<Rational> original(r, TypeId::signedRational);
    ValueType<Rational> copy(original);
    EXPECT_EQ(copy.count(), 1u);
    EXPECT_FLOAT_EQ(copy.toFloat(0), 0.5f);
}

// ============================================================================
// Tests for boundary conditions and edge cases
// ============================================================================

class ValueTypeBoundaryTest_159 : public ::testing::Test {};

TEST_F(ValueTypeBoundaryTest_159, FloatMaxValue_159) {
    ValueType<float> v(std::numeric_limits<float>::max(), TypeId::tiffFloat);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), std::numeric_limits<float>::max());
}

TEST_F(ValueTypeBoundaryTest_159, FloatMinValue_159) {
    ValueType<float> v(std::numeric_limits<float>::lowest(), TypeId::tiffFloat);
    EXPECT_EQ(v.count(), 1u);
    EXPECT_FLOAT_EQ(v.toFloat(0), std::numeric_limits<float>::lowest());
}

TEST_F(ValueTypeBoundaryTest_159, FloatNegativeZero_159) {
    ValueType<float> v(-0.0f, TypeId::tiffFloat);
    EXPECT_EQ(v.toInt64(0), 0);
}

TEST_F(ValueTypeBoundaryTest_159, RationalZeroNumerator_159) {
    Rational r(0, 5);
    ValueType<Rational> v(r, TypeId::signedRational);
    EXPECT_EQ(v.toInt64(0), 0);
    EXPECT_FLOAT_EQ(v.toFloat(0), 0.0f);
}

TEST_F(ValueTypeBoundaryTest_159, URationalLargeValues_159) {
    URational r(4000000000u, 2);
    ValueType<URational> v(r, TypeId::unsignedRational);
    int64_t result = v.toInt64(0);
    EXPECT_EQ(result, 2000000000);
}

TEST_F(ValueTypeBoundaryTest_159, Uint16MaxValue_159) {
    ValueType<uint16_t> v(65535, TypeId::unsignedShort);
    EXPECT_EQ(v.toInt64(0), 65535);
    EXPECT_EQ(v.toUint32(0), 65535u);
}

TEST_F(ValueTypeBoundaryTest_159, EmptyValueList_Size_159) {
    ValueType<float> v;
    EXPECT_EQ(v.size(), 0u);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_159, ReadEmptyBuffer_159) {
    ValueType<uint16_t> v;
    int result = v.read(nullptr, 0, littleEndian);
    EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeBoundaryTest_159, MultipleValuesSize_159) {
    ValueType<float> v;
    v.value_.push_back(1.0f);
    v.value_.push_back(2.0f);
    EXPECT_EQ(v.size(), 2 * sizeof(float));
}

TEST_F(ValueTypeBoundaryTest_159, DataAreaOperations_159) {
    ValueType<uint16_t> v;
    EXPECT_EQ(v.sizeDataArea(), 0u);
    
    byte data[] = {0xAA, 0xBB, 0xCC};
    v.setDataArea(data, 3);
    EXPECT_EQ(v.sizeDataArea(), 3u);
    
    DataBuf db = v.dataArea();
    EXPECT_EQ(db.size(), 3u);
}

// ============================================================================
// Tests for write output format
// ============================================================================

class ValueTypeWriteTest_159 : public ::testing::Test {};

TEST_F(ValueTypeWriteTest_159, WriteMultipleFloats_159) {
    ValueType<float> v;
    v.value_.push_back(1.0f);
    v.value_.push_back(2.0f);
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
}

TEST_F(ValueTypeWriteTest_159, WriteRational_159) {
    Rational r(3, 4);
    ValueType<Rational> v(r, TypeId::signedRational);
    std::ostringstream os;
    v.write(os);
    std::string output = os.str();
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("/"), std::string::npos);
}

TEST_F(ValueTypeWriteTest_159, WriteEmptyValue_159) {
    ValueType<float> v;
    std::ostringstream os;
    v.write(os);
    EXPECT_TRUE(os.str().empty());
}

// ============================================================================
// Tests for read from bytes with different byte orders
// ============================================================================

class ValueTypeByteOrderTest_159 : public ::testing::Test {};

TEST_F(ValueTypeByteOrderTest_159, Uint16_LittleEndian_159) {
    byte buf[] = {0x01, 0x00};
    ValueType<uint16_t> v;
    v.read(buf, 2, littleEndian);
    EXPECT_EQ(v.toInt64(0), 1);
}

TEST_F(ValueTypeByteOrderTest_159, Uint16_BigEndian_159) {
    byte buf[] = {0x00, 0x01};
    ValueType<uint16_t> v;
    v.read(buf, 2, bigEndian);
    EXPECT_EQ(v.toInt64(0), 1);
}

TEST_F(ValueTypeByteOrderTest_159, Int32_LittleEndian_159) {
    byte buf[] = {0x78, 0x56, 0x34, 0x12};
    ValueType<int32_t> v;
    v.read(buf, 4, littleEndian);
    EXPECT_EQ(v.toInt64(0), 0x12345678);
}

TEST_F(ValueTypeByteOrderTest_159, Int32_BigEndian_159) {
    byte buf[] = {0x12, 0x34, 0x56, 0x78};
    ValueType<int32_t> v;
    v.read(buf, 4, bigEndian);
    EXPECT_EQ(v.toInt64(0), 0x12345678);
}
