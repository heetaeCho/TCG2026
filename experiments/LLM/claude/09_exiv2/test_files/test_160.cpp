#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <cmath>
#include <limits>
#include <sstream>

using namespace Exiv2;

// ============================================================================
// Tests for ValueType<float>
// ============================================================================

class ValueTypeFloatTest_160 : public ::testing::Test {
 protected:
  using FloatValue = ValueType<float>;
};

TEST_F(ValueTypeFloatTest_160, DefaultConstructor_160) {
  FloatValue v;
  EXPECT_EQ(v.count(), 0u);
  EXPECT_EQ(v.size(), 0u);
}

TEST_F(ValueTypeFloatTest_160, ConstructWithValue_160) {
  FloatValue v(3.14f, TypeId::tiffFloat);
  EXPECT_EQ(v.count(), 1u);
  EXPECT_FLOAT_EQ(v.toFloat(0), 3.14f);
}

TEST_F(ValueTypeFloatTest_160, ToUint32Normal_160) {
  FloatValue v(42.7f, TypeId::tiffFloat);
  uint32_t result = v.toUint32(0);
  EXPECT_EQ(result, 42u);
}

TEST_F(ValueTypeFloatTest_160, ToUint32Zero_160) {
  FloatValue v(0.0f, TypeId::tiffFloat);
  EXPECT_EQ(v.toUint32(0), 0u);
}

TEST_F(ValueTypeFloatTest_160, ToUint32Truncation_160) {
  FloatValue v(99.99f, TypeId::tiffFloat);
  uint32_t result = v.toUint32(0);
  EXPECT_EQ(result, 99u);
}

TEST_F(ValueTypeFloatTest_160, ToInt64Normal_160) {
  FloatValue v(123.456f, TypeId::tiffFloat);
  int64_t result = v.toInt64(0);
  EXPECT_EQ(result, 123);
}

TEST_F(ValueTypeFloatTest_160, ToInt64Negative_160) {
  FloatValue v(-42.5f, TypeId::tiffFloat);
  int64_t result = v.toInt64(0);
  EXPECT_EQ(result, -42);
}

TEST_F(ValueTypeFloatTest_160, ToRational_160) {
  FloatValue v(0.5f, TypeId::tiffFloat);
  Rational r = v.toRational(0);
  // Check the rational approximates the float
  EXPECT_NEAR(static_cast<float>(r.first) / r.second, 0.5f, 0.001f);
}

TEST_F(ValueTypeFloatTest_160, ReadFromString_160) {
  FloatValue v;
  v.read("1.5 2.5 3.5");
  EXPECT_EQ(v.count(), 3u);
  EXPECT_FLOAT_EQ(v.toFloat(0), 1.5f);
  EXPECT_FLOAT_EQ(v.toFloat(1), 2.5f);
  EXPECT_FLOAT_EQ(v.toFloat(2), 3.5f);
}

TEST_F(ValueTypeFloatTest_160, WriteToStream_160) {
  FloatValue v(1.5f, TypeId::tiffFloat);
  std::ostringstream os;
  v.write(os);
  EXPECT_FALSE(os.str().empty());
}

TEST_F(ValueTypeFloatTest_160, ToString_160) {
  FloatValue v(3.14f, TypeId::tiffFloat);
  std::string s = v.toString(0);
  EXPECT_FALSE(s.empty());
}

TEST_F(ValueTypeFloatTest_160, CopyAndClone_160) {
  FloatValue v(7.0f, TypeId::tiffFloat);
  auto cloned = v.clone();
  EXPECT_EQ(cloned->count(), 1u);
  EXPECT_FLOAT_EQ(cloned->toFloat(0), 7.0f);
}

TEST_F(ValueTypeFloatTest_160, CopyConstructor_160) {
  FloatValue v(5.0f, TypeId::tiffFloat);
  FloatValue v2(v);
  EXPECT_EQ(v2.count(), 1u);
  EXPECT_FLOAT_EQ(v2.toFloat(0), 5.0f);
}

TEST_F(ValueTypeFloatTest_160, AssignmentOperator_160) {
  FloatValue v1(10.0f, TypeId::tiffFloat);
  FloatValue v2;
  v2 = v1;
  EXPECT_EQ(v2.count(), 1u);
  EXPECT_FLOAT_EQ(v2.toFloat(0), 10.0f);
}

TEST_F(ValueTypeFloatTest_160, MultipleValues_160) {
  FloatValue v;
  v.read("1.0 2.0 3.0");
  EXPECT_EQ(v.count(), 3u);
  EXPECT_EQ(v.toUint32(0), 1u);
  EXPECT_EQ(v.toUint32(1), 2u);
  EXPECT_EQ(v.toUint32(2), 3u);
}

TEST_F(ValueTypeFloatTest_160, DataAreaInitiallyEmpty_160) {
  FloatValue v;
  EXPECT_EQ(v.sizeDataArea(), 0u);
}

TEST_F(ValueTypeFloatTest_160, SetDataArea_160) {
  FloatValue v;
  byte data[] = {0x01, 0x02, 0x03, 0x04};
  int rc = v.setDataArea(data, sizeof(data));
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(v.sizeDataArea(), sizeof(data));
  DataBuf buf = v.dataArea();
  EXPECT_EQ(buf.size(), sizeof(data));
}

TEST_F(ValueTypeFloatTest_160, ReadFromBinary_160) {
  float val = 2.5f;
  byte buf[sizeof(float)];
  std::memcpy(buf, &val, sizeof(float));
  FloatValue v;
  v.read(buf, sizeof(buf), littleEndian);
  EXPECT_EQ(v.count(), 1u);
  EXPECT_FLOAT_EQ(v.toFloat(0), 2.5f);
}

TEST_F(ValueTypeFloatTest_160, CopyToBuffer_160) {
  FloatValue v(1.0f, TypeId::tiffFloat);
  byte buf[sizeof(float)];
  size_t copied = v.copy(buf, littleEndian);
  EXPECT_EQ(copied, sizeof(float));
}

TEST_F(ValueTypeFloatTest_160, NegativeFloatToUint32_160) {
  FloatValue v(-1.0f, TypeId::tiffFloat);
  // Behavior for negative float to uint32 — just ensure no crash
  v.toUint32(0);
}

TEST_F(ValueTypeFloatTest_160, LargeFloatToUint32_160) {
  FloatValue v(1.0e10f, TypeId::tiffFloat);
  // Just ensure it doesn't crash for large values
  v.toUint32(0);
}

// ============================================================================
// Tests for ValueType<double>
// ============================================================================

class ValueTypeDoubleTest_160 : public ::testing::Test {
 protected:
  using DoubleValue = ValueType<double>;
};

TEST_F(ValueTypeDoubleTest_160, DefaultConstructor_160) {
  DoubleValue v;
  EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeDoubleTest_160, ConstructWithValue_160) {
  DoubleValue v(3.14, TypeId::tiffDouble);
  EXPECT_EQ(v.count(), 1u);
  EXPECT_DOUBLE_EQ(v.toFloat(0), static_cast<float>(3.14));
}

TEST_F(ValueTypeDoubleTest_160, ToUint32Normal_160) {
  DoubleValue v(42.7, TypeId::tiffDouble);
  EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeDoubleTest_160, ToInt64Normal_160) {
  DoubleValue v(-100.9, TypeId::tiffDouble);
  EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeDoubleTest_160, ToRational_160) {
  DoubleValue v(0.25, TypeId::tiffDouble);
  Rational r = v.toRational(0);
  EXPECT_NEAR(static_cast<double>(r.first) / r.second, 0.25, 0.001);
}

TEST_F(ValueTypeDoubleTest_160, ReadFromString_160) {
  DoubleValue v;
  v.read("10.5 20.5");
  EXPECT_EQ(v.count(), 2u);
}

// ============================================================================
// Tests for ValueType<Rational>
// ============================================================================

class ValueTypeRationalTest_160 : public ::testing::Test {
 protected:
  using RationalValue = ValueType<Rational>;
};

TEST_F(ValueTypeRationalTest_160, DefaultConstructor_160) {
  RationalValue v;
  EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeRationalTest_160, ConstructWithValue_160) {
  Rational r(1, 2);
  RationalValue v(r, TypeId::signedRational);
  EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeRationalTest_160, ToFloat_160) {
  Rational r(1, 4);
  RationalValue v(r, TypeId::signedRational);
  EXPECT_FLOAT_EQ(v.toFloat(0), 0.25f);
}

TEST_F(ValueTypeRationalTest_160, ToInt64_160) {
  Rational r(7, 2);
  RationalValue v(r, TypeId::signedRational);
  int64_t result = v.toInt64(0);
  EXPECT_EQ(result, 3);
}

TEST_F(ValueTypeRationalTest_160, ToUint32_160) {
  Rational r(10, 3);
  RationalValue v(r, TypeId::signedRational);
  uint32_t result = v.toUint32(0);
  EXPECT_EQ(result, 3u);
}

TEST_F(ValueTypeRationalTest_160, ToRational_160) {
  Rational r(3, 7);
  RationalValue v(r, TypeId::signedRational);
  Rational result = v.toRational(0);
  EXPECT_EQ(result.first, 3);
  EXPECT_EQ(result.second, 7);
}

TEST_F(ValueTypeRationalTest_160, ZeroDenominator_160) {
  Rational r(1, 0);
  RationalValue v(r, TypeId::signedRational);
  // Just ensure it doesn't crash
  v.toFloat(0);
  v.toInt64(0);
  v.toUint32(0);
}

TEST_F(ValueTypeRationalTest_160, NegativeRational_160) {
  Rational r(-5, 2);
  RationalValue v(r, TypeId::signedRational);
  EXPECT_FLOAT_EQ(v.toFloat(0), -2.5f);
  EXPECT_EQ(v.toInt64(0), -2);
}

TEST_F(ValueTypeRationalTest_160, ReadFromString_160) {
  RationalValue v;
  v.read("1/2 3/4");
  EXPECT_EQ(v.count(), 2u);
  EXPECT_FLOAT_EQ(v.toFloat(0), 0.5f);
  EXPECT_FLOAT_EQ(v.toFloat(1), 0.75f);
}

TEST_F(ValueTypeRationalTest_160, Clone_160) {
  Rational r(5, 3);
  RationalValue v(r, TypeId::signedRational);
  auto cloned = v.clone();
  EXPECT_EQ(cloned->count(), 1u);
  EXPECT_FLOAT_EQ(cloned->toFloat(0), 5.0f / 3.0f);
}

// ============================================================================
// Tests for ValueType<URational>
// ============================================================================

class ValueTypeURationalTest_160 : public ::testing::Test {
 protected:
  using URationalValue = ValueType<URational>;
};

TEST_F(ValueTypeURationalTest_160, DefaultConstructor_160) {
  URationalValue v;
  EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeURationalTest_160, ConstructWithValue_160) {
  URational r(3, 4);
  URationalValue v(r, TypeId::unsignedRational);
  EXPECT_EQ(v.count(), 1u);
}

TEST_F(ValueTypeURationalTest_160, ToFloat_160) {
  URational r(1, 8);
  URationalValue v(r, TypeId::unsignedRational);
  EXPECT_FLOAT_EQ(v.toFloat(0), 0.125f);
}

TEST_F(ValueTypeURationalTest_160, ToInt64_160) {
  URational r(9, 2);
  URationalValue v(r, TypeId::unsignedRational);
  EXPECT_EQ(v.toInt64(0), 4);
}

TEST_F(ValueTypeURationalTest_160, ToUint32_160) {
  URational r(15, 4);
  URationalValue v(r, TypeId::unsignedRational);
  EXPECT_EQ(v.toUint32(0), 3u);
}

TEST_F(ValueTypeURationalTest_160, ToRational_160) {
  URational r(7, 3);
  URationalValue v(r, TypeId::unsignedRational);
  Rational result = v.toRational(0);
  EXPECT_EQ(result.first, 7);
  EXPECT_EQ(result.second, 3);
}

TEST_F(ValueTypeURationalTest_160, ZeroDenominator_160) {
  URational r(1, 0);
  URationalValue v(r, TypeId::unsignedRational);
  // Just ensure it doesn't crash
  v.toFloat(0);
  v.toInt64(0);
  v.toUint32(0);
}

TEST_F(ValueTypeURationalTest_160, ReadFromString_160) {
  URationalValue v;
  v.read("5/6 7/8");
  EXPECT_EQ(v.count(), 2u);
}

// ============================================================================
// Tests for ValueType<uint16_t> (UShortValue)
// ============================================================================

class ValueTypeUShortTest_160 : public ::testing::Test {
 protected:
  using UShortValue = ValueType<uint16_t>;
};

TEST_F(ValueTypeUShortTest_160, DefaultConstructor_160) {
  UShortValue v;
  EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeUShortTest_160, ConstructWithValue_160) {
  UShortValue v(static_cast<uint16_t>(42), TypeId::unsignedShort);
  EXPECT_EQ(v.count(), 1u);
  EXPECT_EQ(v.toUint32(0), 42u);
}

TEST_F(ValueTypeUShortTest_160, ToInt64_160) {
  UShortValue v(static_cast<uint16_t>(1000), TypeId::unsignedShort);
  EXPECT_EQ(v.toInt64(0), 1000);
}

TEST_F(ValueTypeUShortTest_160, ToFloat_160) {
  UShortValue v(static_cast<uint16_t>(255), TypeId::unsignedShort);
  EXPECT_FLOAT_EQ(v.toFloat(0), 255.0f);
}

TEST_F(ValueTypeUShortTest_160, ToRational_160) {
  UShortValue v(static_cast<uint16_t>(10), TypeId::unsignedShort);
  Rational r = v.toRational(0);
  EXPECT_NEAR(static_cast<float>(r.first) / r.second, 10.0f, 0.001f);
}

TEST_F(ValueTypeUShortTest_160, ReadFromString_160) {
  UShortValue v;
  v.read("100 200 300");
  EXPECT_EQ(v.count(), 3u);
  EXPECT_EQ(v.toUint32(0), 100u);
  EXPECT_EQ(v.toUint32(1), 200u);
  EXPECT_EQ(v.toUint32(2), 300u);
}

TEST_F(ValueTypeUShortTest_160, ReadFromBinary_160) {
  uint16_t vals[] = {10, 20};
  byte buf[sizeof(vals)];
  std::memcpy(buf, vals, sizeof(vals));
  UShortValue v;
  v.read(buf, sizeof(buf), littleEndian);
  EXPECT_EQ(v.count(), 2u);
}

TEST_F(ValueTypeUShortTest_160, CopyToBuffer_160) {
  UShortValue v(static_cast<uint16_t>(42), TypeId::unsignedShort);
  byte buf[sizeof(uint16_t)];
  size_t copied = v.copy(buf, littleEndian);
  EXPECT_EQ(copied, sizeof(uint16_t));
}

TEST_F(ValueTypeUShortTest_160, Size_160) {
  UShortValue v;
  v.read("1 2 3");
  EXPECT_EQ(v.size(), 3u * sizeof(uint16_t));
}

TEST_F(ValueTypeUShortTest_160, ToString_160) {
  UShortValue v(static_cast<uint16_t>(42), TypeId::unsignedShort);
  std::string s = v.toString(0);
  EXPECT_EQ(s, "42");
}

TEST_F(ValueTypeUShortTest_160, MaxValue_160) {
  UShortValue v(static_cast<uint16_t>(65535), TypeId::unsignedShort);
  EXPECT_EQ(v.toUint32(0), 65535u);
  EXPECT_EQ(v.toInt64(0), 65535);
}

// ============================================================================
// Tests for ValueType<int16_t> (SShortValue)
// ============================================================================

class ValueTypeSShortTest_160 : public ::testing::Test {
 protected:
  using SShortValue = ValueType<int16_t>;
};

TEST_F(ValueTypeSShortTest_160, NegativeValue_160) {
  SShortValue v(static_cast<int16_t>(-100), TypeId::signedShort);
  EXPECT_EQ(v.toInt64(0), -100);
}

TEST_F(ValueTypeSShortTest_160, PositiveValue_160) {
  SShortValue v(static_cast<int16_t>(500), TypeId::signedShort);
  EXPECT_EQ(v.toUint32(0), 500u);
}

// ============================================================================
// Tests for ValueType<uint32_t> (ULongValue)
// ============================================================================

class ValueTypeULongTest_160 : public ::testing::Test {
 protected:
  using ULongValue = ValueType<uint32_t>;
};

TEST_F(ValueTypeULongTest_160, DefaultConstructor_160) {
  ULongValue v;
  EXPECT_EQ(v.count(), 0u);
}

TEST_F(ValueTypeULongTest_160, ConstructWithValue_160) {
  ULongValue v(123456u, TypeId::unsignedLong);
  EXPECT_EQ(v.count(), 1u);
  EXPECT_EQ(v.toUint32(0), 123456u);
}

TEST_F(ValueTypeULongTest_160, ToInt64_160) {
  ULongValue v(4000000000u, TypeId::unsignedLong);
  EXPECT_EQ(v.toInt64(0), 4000000000LL);
}

TEST_F(ValueTypeULongTest_160, ReadFromString_160) {
  ULongValue v;
  v.read("1000000 2000000");
  EXPECT_EQ(v.count(), 2u);
  EXPECT_EQ(v.toUint32(0), 1000000u);
  EXPECT_EQ(v.toUint32(1), 2000000u);
}

// ============================================================================
// Tests for ValueType<int32_t> (SLongValue)
// ============================================================================

class ValueTypeSLongTest_160 : public ::testing::Test {
 protected:
  using SLongValue = ValueType<int32_t>;
};

TEST_F(ValueTypeSLongTest_160, NegativeValue_160) {
  SLongValue v(-999999, TypeId::signedLong);
  EXPECT_EQ(v.toInt64(0), -999999);
}

TEST_F(ValueTypeSLongTest_160, PositiveValue_160) {
  SLongValue v(999999, TypeId::signedLong);
  EXPECT_EQ(v.toUint32(0), 999999u);
}

// ============================================================================
// Edge case: Boundary index access for multi-value types
// ============================================================================

TEST(ValueTypeBoundaryTest_160, AccessLastElement_160) {
  ValueType<float> v;
  v.read("1.0 2.0 3.0 4.0 5.0");
  EXPECT_EQ(v.count(), 5u);
  EXPECT_FLOAT_EQ(v.toFloat(4), 5.0f);
}

TEST(ValueTypeBoundaryTest_160, OutOfRangeAccess_160) {
  ValueType<float> v(1.0f, TypeId::tiffFloat);
  // Accessing out of range should throw
  EXPECT_THROW(v.toFloat(1), std::out_of_range);
}

TEST(ValueTypeBoundaryTest_160, OutOfRangeToUint32_160) {
  ValueType<float> v(1.0f, TypeId::tiffFloat);
  EXPECT_THROW(v.toUint32(5), std::out_of_range);
}

TEST(ValueTypeBoundaryTest_160, OutOfRangeToInt64_160) {
  ValueType<float> v(1.0f, TypeId::tiffFloat);
  EXPECT_THROW(v.toInt64(5), std::out_of_range);
}

TEST(ValueTypeBoundaryTest_160, OutOfRangeToString_160) {
  ValueType<uint16_t> v(static_cast<uint16_t>(10), TypeId::unsignedShort);
  EXPECT_THROW(v.toString(2), std::out_of_range);
}

TEST(ValueTypeBoundaryTest_160, EmptyValueAccess_160) {
  ValueType<float> v;
  EXPECT_THROW(v.toFloat(0), std::out_of_range);
}

// ============================================================================
// Write and stream tests
// ============================================================================

TEST(ValueTypeWriteTest_160, WriteMultipleFloats_160) {
  ValueType<float> v;
  v.read("1.5 2.5 3.5");
  std::ostringstream os;
  v.write(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

TEST(ValueTypeWriteTest_160, WriteMultipleRationals_160) {
  ValueType<Rational> v;
  v.read("1/2 3/4");
  std::ostringstream os;
  v.write(os);
  std::string output = os.str();
  EXPECT_FALSE(output.empty());
}

// ============================================================================
// DataArea tests
// ============================================================================

TEST(ValueTypeDataAreaTest_160, SetAndGetDataArea_160) {
  ValueType<uint16_t> v(static_cast<uint16_t>(1), TypeId::unsignedShort);
  byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
  EXPECT_EQ(v.sizeDataArea(), 0u);
  int rc = v.setDataArea(data, sizeof(data));
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(v.sizeDataArea(), sizeof(data));
  DataBuf buf = v.dataArea();
  EXPECT_EQ(buf.size(), sizeof(data));
}

TEST(ValueTypeDataAreaTest_160, ClonePreservesDataArea_160) {
  ValueType<uint16_t> v(static_cast<uint16_t>(1), TypeId::unsignedShort);
  byte data[] = {0x01, 0x02};
  v.setDataArea(data, sizeof(data));
  auto cloned = v.clone();
  EXPECT_EQ(cloned->sizeDataArea(), sizeof(data));
}

// ============================================================================
// Copy constructor and assignment for Rational
// ============================================================================

TEST(ValueTypeCopyTest_160, RationalCopyConstructor_160) {
  Rational r(3, 5);
  ValueType<Rational> v(r, TypeId::signedRational);
  ValueType<Rational> v2(v);
  EXPECT_EQ(v2.count(), 1u);
  Rational result = v2.toRational(0);
  EXPECT_EQ(result.first, 3);
  EXPECT_EQ(result.second, 5);
}

TEST(ValueTypeCopyTest_160, RationalAssignment_160) {
  Rational r(7, 11);
  ValueType<Rational> v(r, TypeId::signedRational);
  ValueType<Rational> v2;
  v2 = v;
  EXPECT_EQ(v2.count(), 1u);
  Rational result = v2.toRational(0);
  EXPECT_EQ(result.first, 7);
  EXPECT_EQ(result.second, 11);
}

// ============================================================================
// Special float values
// ============================================================================

TEST(ValueTypeSpecialFloat_160, PositiveInfToUint32_160) {
  float inf = std::numeric_limits<float>::infinity();
  ValueType<float> v(inf, TypeId::tiffFloat);
  // Just ensure no crash
  v.toUint32(0);
}

TEST(ValueTypeSpecialFloat_160, NaNToUint32_160) {
  float nan_val = std::numeric_limits<float>::quiet_NaN();
  ValueType<float> v(nan_val, TypeId::tiffFloat);
  // Just ensure no crash
  v.toUint32(0);
}

TEST(ValueTypeSpecialFloat_160, NegativeInfToInt64_160) {
  float neg_inf = -std::numeric_limits<float>::infinity();
  ValueType<float> v(neg_inf, TypeId::tiffFloat);
  // Just ensure no crash
  v.toInt64(0);
}

// ============================================================================
// Size calculations
// ============================================================================

TEST(ValueTypeSizeTest_160, FloatSize_160) {
  ValueType<float> v;
  v.read("1.0 2.0 3.0");
  EXPECT_EQ(v.size(), 3u * sizeof(float));
}

TEST(ValueTypeSizeTest_160, DoubleSize_160) {
  ValueType<double> v;
  v.read("1.0 2.0");
  EXPECT_EQ(v.size(), 2u * sizeof(double));
}

TEST(ValueTypeSizeTest_160, RationalSize_160) {
  ValueType<Rational> v;
  v.read("1/2 3/4");
  EXPECT_EQ(v.count(), 2u);
  // Each Rational is two int32_t = 8 bytes
  EXPECT_EQ(v.size(), 2u * 8u);
}

TEST(ValueTypeSizeTest_160, EmptySize_160) {
  ValueType<float> v;
  EXPECT_EQ(v.size(), 0u);
  EXPECT_EQ(v.count(), 0u);
}
