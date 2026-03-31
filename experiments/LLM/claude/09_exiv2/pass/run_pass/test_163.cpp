#include <gtest/gtest.h>
#include <exiv2/value.hpp>
#include <sstream>
#include <cstring>

using namespace Exiv2;

// ============================================================
// Tests for ValueType<URational>::toInt64 specialization
// ============================================================

class URationalValueTest_163 : public ::testing::Test {
 protected:
  using URationalValue = ValueType<URational>;
};

TEST_F(URationalValueTest_163, ToInt64_SimpleDivision_163) {
  URationalValue val(URational(10, 2), unsignedRational);
  EXPECT_EQ(val.toInt64(0), 5);
}

TEST_F(URationalValueTest_163, ToInt64_ZeroDenominator_163) {
  URationalValue val(URational(10, 0), unsignedRational);
  // Division by zero should return 0 or handle gracefully
  // The behavior depends on implementation, but we test it doesn't crash
  int64_t result = val.toInt64(0);
  (void)result;  // Just ensuring no crash
}

TEST_F(URationalValueTest_163, ToInt64_ZeroNumerator_163) {
  URationalValue val(URational(0, 5), unsignedRational);
  EXPECT_EQ(val.toInt64(0), 0);
}

TEST_F(URationalValueTest_163, ToInt64_OneToOne_163) {
  URationalValue val(URational(1, 1), unsignedRational);
  EXPECT_EQ(val.toInt64(0), 1);
}

TEST_F(URationalValueTest_163, ToInt64_LargeValues_163) {
  URationalValue val(URational(1000000, 1), unsignedRational);
  EXPECT_EQ(val.toInt64(0), 1000000);
}

TEST_F(URationalValueTest_163, ToInt64_FractionalResult_163) {
  URationalValue val(URational(7, 3), unsignedRational);
  // Integer division: 7/3 = 2 (truncated)
  EXPECT_EQ(val.toInt64(0), 2);
}

TEST_F(URationalValueTest_163, ToInt64_NumeratorLessThanDenominator_163) {
  URationalValue val(URational(1, 3), unsignedRational);
  EXPECT_EQ(val.toInt64(0), 0);
}

TEST_F(URationalValueTest_163, ToInt64_MaxUint32Values_163) {
  URationalValue val(URational(0xFFFFFFFF, 1), unsignedRational);
  EXPECT_EQ(val.toInt64(0), static_cast<int64_t>(0xFFFFFFFF));
}

// ============================================================
// Tests for ValueType<Rational>::toInt64 specialization
// ============================================================

class RationalValueTest_163 : public ::testing::Test {
 protected:
  using RationalValue = ValueType<Rational>;
};

TEST_F(RationalValueTest_163, ToInt64_PositiveDivision_163) {
  ValueType<Rational> val(Rational(10, 2), signedRational);
  EXPECT_EQ(val.toInt64(0), 5);
}

TEST_F(RationalValueTest_163, ToInt64_NegativeNumerator_163) {
  ValueType<Rational> val(Rational(-10, 2), signedRational);
  EXPECT_EQ(val.toInt64(0), -5);
}

TEST_F(RationalValueTest_163, ToInt64_NegativeDenominator_163) {
  ValueType<Rational> val(Rational(10, -2), signedRational);
  EXPECT_EQ(val.toInt64(0), -5);
}

TEST_F(RationalValueTest_163, ToInt64_BothNegative_163) {
  ValueType<Rational> val(Rational(-10, -2), signedRational);
  EXPECT_EQ(val.toInt64(0), 5);
}

TEST_F(RationalValueTest_163, ToInt64_ZeroNumerator_163) {
  ValueType<Rational> val(Rational(0, 5), signedRational);
  EXPECT_EQ(val.toInt64(0), 0);
}

TEST_F(RationalValueTest_163, ToInt64_ZeroDenominator_163) {
  ValueType<Rational> val(Rational(10, 0), signedRational);
  int64_t result = val.toInt64(0);
  (void)result;  // Just ensuring no crash
}

// ============================================================
// Tests for ValueType<double> toInt64 specialization
// ============================================================

class DoubleValueTest_163 : public ::testing::Test {
 protected:
  using DoubleValue = ValueType<double>;
};

TEST_F(DoubleValueTest_163, ToInt64_WholeNumber_163) {
  ValueType<double> val(42.0, tiffDouble);
  EXPECT_EQ(val.toInt64(0), 42);
}

TEST_F(DoubleValueTest_163, ToInt64_FractionalTruncation_163) {
  ValueType<double> val(42.9, tiffDouble);
  EXPECT_EQ(val.toInt64(0), 42);
}

TEST_F(DoubleValueTest_163, ToInt64_Negative_163) {
  ValueType<double> val(-5.5, tiffDouble);
  EXPECT_EQ(val.toInt64(0), -5);
}

TEST_F(DoubleValueTest_163, ToInt64_Zero_163) {
  ValueType<double> val(0.0, tiffDouble);
  EXPECT_EQ(val.toInt64(0), 0);
}

// ============================================================
// Tests for ValueType<float> toInt64 specialization
// ============================================================

class FloatValueTest_163 : public ::testing::Test {
 protected:
  using FloatValue = ValueType<float>;
};

TEST_F(FloatValueTest_163, ToInt64_WholeNumber_163) {
  ValueType<float> val(42.0f, tiffFloat);
  EXPECT_EQ(val.toInt64(0), 42);
}

TEST_F(FloatValueTest_163, ToInt64_Negative_163) {
  ValueType<float> val(-10.7f, tiffFloat);
  EXPECT_EQ(val.toInt64(0), -10);
}

TEST_F(FloatValueTest_163, ToInt64_Zero_163) {
  ValueType<float> val(0.0f, tiffFloat);
  EXPECT_EQ(val.toInt64(0), 0);
}

// ============================================================
// Tests for toUint32 specializations
// ============================================================

TEST_F(URationalValueTest_163, ToUint32_SimpleDivision_163) {
  URationalValue val(URational(20, 4), unsignedRational);
  EXPECT_EQ(val.toUint32(0), 5u);
}

TEST_F(URationalValueTest_163, ToUint32_ZeroNumerator_163) {
  URationalValue val(URational(0, 10), unsignedRational);
  EXPECT_EQ(val.toUint32(0), 0u);
}

TEST_F(RationalValueTest_163, ToUint32_PositiveDivision_163) {
  ValueType<Rational> val(Rational(15, 3), signedRational);
  EXPECT_EQ(val.toUint32(0), 5u);
}

TEST_F(DoubleValueTest_163, ToUint32_WholeNumber_163) {
  ValueType<double> val(100.0, tiffDouble);
  EXPECT_EQ(val.toUint32(0), 100u);
}

TEST_F(FloatValueTest_163, ToUint32_WholeNumber_163) {
  ValueType<float> val(100.0f, tiffFloat);
  EXPECT_EQ(val.toUint32(0), 100u);
}

// ============================================================
// Tests for toFloat specializations
// ============================================================

TEST_F(URationalValueTest_163, ToFloat_SimpleDivision_163) {
  URationalValue val(URational(1, 2), unsignedRational);
  EXPECT_FLOAT_EQ(val.toFloat(0), 0.5f);
}

TEST_F(RationalValueTest_163, ToFloat_SimpleDivision_163) {
  ValueType<Rational> val(Rational(1, 4), signedRational);
  EXPECT_FLOAT_EQ(val.toFloat(0), 0.25f);
}

TEST_F(RationalValueTest_163, ToFloat_Negative_163) {
  ValueType<Rational> val(Rational(-1, 2), signedRational);
  EXPECT_FLOAT_EQ(val.toFloat(0), -0.5f);
}

// ============================================================
// Tests for toRational specializations
// ============================================================

TEST_F(URationalValueTest_163, ToRational_Identity_163) {
  URationalValue val(URational(3, 7), unsignedRational);
  Rational r = val.toRational(0);
  EXPECT_EQ(r.first, 3);
  EXPECT_EQ(r.second, 7);
}

TEST_F(RationalValueTest_163, ToRational_Identity_163) {
  ValueType<Rational> val(Rational(-3, 7), signedRational);
  Rational r = val.toRational(0);
  EXPECT_EQ(r.first, -3);
  EXPECT_EQ(r.second, 7);
}

TEST_F(FloatValueTest_163, ToRational_FromFloat_163) {
  ValueType<float> val(0.5f, tiffFloat);
  Rational r = val.toRational(0);
  // The rational should approximate 0.5
  if (r.second != 0) {
    float approx = static_cast<float>(r.first) / static_cast<float>(r.second);
    EXPECT_NEAR(approx, 0.5f, 0.001f);
  }
}

TEST_F(DoubleValueTest_163, ToRational_FromDouble_163) {
  ValueType<double> val(0.25, tiffDouble);
  Rational r = val.toRational(0);
  if (r.second != 0) {
    double approx = static_cast<double>(r.first) / static_cast<double>(r.second);
    EXPECT_NEAR(approx, 0.25, 0.001);
  }
}

// ============================================================
// Tests for count, size, read, copy, write, toString
// ============================================================

TEST_F(URationalValueTest_163, Count_SingleValue_163) {
  URationalValue val(URational(1, 2), unsignedRational);
  EXPECT_EQ(val.count(), 1u);
}

TEST_F(URationalValueTest_163, Count_MultipleValues_163) {
  URationalValue val(URational(1, 2), unsignedRational);
  val.value_.push_back(URational(3, 4));
  val.value_.push_back(URational(5, 6));
  EXPECT_EQ(val.count(), 3u);
}

TEST_F(URationalValueTest_163, Size_SingleValue_163) {
  URationalValue val(URational(1, 2), unsignedRational);
  // URational is a pair of uint32_t, so 8 bytes
  EXPECT_EQ(val.size(), 8u);
}

TEST_F(URationalValueTest_163, ToString_163) {
  URationalValue val(URational(1, 2), unsignedRational);
  std::string s = val.toString(0);
  EXPECT_EQ(s, "1/2");
}

TEST_F(RationalValueTest_163, ToString_Negative_163) {
  ValueType<Rational> val(Rational(-1, 2), signedRational);
  std::string s = val.toString(0);
  EXPECT_EQ(s, "-1/2");
}

TEST_F(URationalValueTest_163, Write_163) {
  URationalValue val(URational(1, 2), unsignedRational);
  std::ostringstream os;
  val.write(os);
  EXPECT_EQ(os.str(), "1/2");
}

TEST_F(URationalValueTest_163, ReadFromString_163) {
  URationalValue val;
  val.read("3/4");
  EXPECT_EQ(val.count(), 1u);
  EXPECT_EQ(val.toInt64(0), 0);  // 3/4 truncated to 0
  EXPECT_FLOAT_EQ(val.toFloat(0), 0.75f);
}

TEST_F(URationalValueTest_163, ReadFromBuffer_163) {
  // URational in little-endian: numerator(4 bytes) + denominator(4 bytes)
  byte buf[8];
  std::memset(buf, 0, sizeof(buf));
  // Write 10/1 in little endian
  buf[0] = 10; buf[1] = 0; buf[2] = 0; buf[3] = 0;
  buf[4] = 1;  buf[5] = 0; buf[6] = 0; buf[7] = 0;
  URationalValue val;
  val.read(buf, 8, littleEndian);
  EXPECT_EQ(val.count(), 1u);
  EXPECT_EQ(val.toInt64(0), 10);
}

TEST_F(URationalValueTest_163, CopyToBuffer_163) {
  URationalValue val(URational(10, 1), unsignedRational);
  byte buf[8];
  std::memset(buf, 0, sizeof(buf));
  size_t copied = val.copy(buf, littleEndian);
  EXPECT_EQ(copied, 8u);
  // Read back
  URationalValue val2;
  val2.read(buf, 8, littleEndian);
  EXPECT_EQ(val2.toInt64(0), 10);
}

// ============================================================
// Tests for clone
// ============================================================

TEST_F(URationalValueTest_163, Clone_163) {
  URationalValue val(URational(5, 3), unsignedRational);
  auto cloned = val.clone();
  ASSERT_NE(cloned, nullptr);
  EXPECT_EQ(cloned->toInt64(0), 1);  // 5/3 = 1
  EXPECT_EQ(cloned->count(), 1u);
}

// ============================================================
// Tests for setDataArea / sizeDataArea / dataArea
// ============================================================

TEST_F(URationalValueTest_163, DataAreaInitiallyEmpty_163) {
  URationalValue val(URational(1, 1), unsignedRational);
  EXPECT_EQ(val.sizeDataArea(), 0u);
}

TEST_F(URationalValueTest_163, SetDataArea_163) {
  URationalValue val(URational(1, 1), unsignedRational);
  byte data[] = {0x01, 0x02, 0x03, 0x04};
  int rc = val.setDataArea(data, sizeof(data));
  EXPECT_EQ(rc, 0);
  EXPECT_EQ(val.sizeDataArea(), 4u);
  DataBuf retrieved = val.dataArea();
  EXPECT_EQ(retrieved.size(), 4u);
}

// ============================================================
// Tests for integer types (e.g., uint16_t / int32_t)
// ============================================================

class UShortValueTest_163 : public ::testing::Test {};

TEST_F(UShortValueTest_163, ToInt64_163) {
  ValueType<uint16_t> val(static_cast<uint16_t>(42), unsignedShort);
  EXPECT_EQ(val.toInt64(0), 42);
}

TEST_F(UShortValueTest_163, ToUint32_163) {
  ValueType<uint16_t> val(static_cast<uint16_t>(65535), unsignedShort);
  EXPECT_EQ(val.toUint32(0), 65535u);
}

TEST_F(UShortValueTest_163, Count_163) {
  ValueType<uint16_t> val(static_cast<uint16_t>(1), unsignedShort);
  EXPECT_EQ(val.count(), 1u);
}

TEST_F(UShortValueTest_163, MultipleValues_163) {
  ValueType<uint16_t> val(static_cast<uint16_t>(1), unsignedShort);
  val.value_.push_back(2);
  val.value_.push_back(3);
  EXPECT_EQ(val.count(), 3u);
  EXPECT_EQ(val.toInt64(0), 1);
  EXPECT_EQ(val.toInt64(1), 2);
  EXPECT_EQ(val.toInt64(2), 3);
}

class Int32ValueTest_163 : public ::testing::Test {};

TEST_F(Int32ValueTest_163, ToInt64_Negative_163) {
  ValueType<int32_t> val(static_cast<int32_t>(-100), signedLong);
  EXPECT_EQ(val.toInt64(0), -100);
}

TEST_F(Int32ValueTest_163, ToFloat_163) {
  ValueType<int32_t> val(static_cast<int32_t>(42), signedLong);
  EXPECT_FLOAT_EQ(val.toFloat(0), 42.0f);
}

TEST_F(Int32ValueTest_163, ToRational_163) {
  ValueType<int32_t> val(static_cast<int32_t>(5), signedLong);
  Rational r = val.toRational(0);
  EXPECT_EQ(r.first, 5);
  EXPECT_EQ(r.second, 1);
}

// ============================================================
// Boundary test: accessing out-of-range index
// ============================================================

TEST_F(URationalValueTest_163, ToInt64_OutOfRange_163) {
  URationalValue val(URational(1, 1), unsignedRational);
  // Accessing index 1 when only 1 element exists (index 0)
  // This may throw or return a default value
  EXPECT_ANY_THROW(val.toInt64(1));
}

TEST_F(URationalValueTest_163, ToString_OutOfRange_163) {
  URationalValue val(URational(1, 1), unsignedRational);
  EXPECT_ANY_THROW(val.toString(5));
}

// ============================================================
// Test copy constructor and assignment operator
// ============================================================

TEST_F(URationalValueTest_163, CopyConstructor_163) {
  URationalValue val(URational(7, 3), unsignedRational);
  URationalValue copy(val);
  EXPECT_EQ(copy.count(), 1u);
  EXPECT_EQ(copy.toInt64(0), val.toInt64(0));
}

TEST_F(URationalValueTest_163, AssignmentOperator_163) {
  URationalValue val(URational(7, 3), unsignedRational);
  URationalValue other(URational(1, 1), unsignedRational);
  other = val;
  EXPECT_EQ(other.count(), 1u);
  EXPECT_EQ(other.toInt64(0), val.toInt64(0));
}

// ============================================================
// Test default constructor
// ============================================================

TEST_F(URationalValueTest_163, DefaultConstructor_163) {
  URationalValue val;
  EXPECT_EQ(val.count(), 0u);
  EXPECT_EQ(val.size(), 0u);
}

// ============================================================
// Test reading multiple values from string
// ============================================================

TEST_F(URationalValueTest_163, ReadMultipleFromString_163) {
  URationalValue val;
  val.read("1/2 3/4 5/6");
  EXPECT_EQ(val.count(), 3u);
  EXPECT_FLOAT_EQ(val.toFloat(0), 0.5f);
  EXPECT_FLOAT_EQ(val.toFloat(1), 0.75f);
}

TEST_F(URationalValueTest_163, WriteMultiple_163) {
  URationalValue val;
  val.read("1/2 3/4");
  std::ostringstream os;
  val.write(os);
  std::string s = os.str();
  EXPECT_NE(s.find("1/2"), std::string::npos);
  EXPECT_NE(s.find("3/4"), std::string::npos);
}
