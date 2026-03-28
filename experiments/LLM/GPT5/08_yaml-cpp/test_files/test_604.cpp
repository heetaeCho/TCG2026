// TEST_ID: 604
// File: yaml-cpp/node/convert_inner_encode_test_604.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>

#include "yaml-cpp/node/convert.h"

namespace {

class InnerEncodeTest_604 : public ::testing::Test {
 protected:
  template <typename T>
  static std::string EncodeToString(T value, int precision = 17, const std::string& prefix = "") {
    static_assert(std::is_floating_point<T>::value, "EncodeToString is for floating point types only.");
    std::stringstream ss;
    ss << prefix;
    ss.precision(precision);
    YAML::conversion::inner_encode<T>(value, ss);
    return ss.str();
  }

  template <typename T>
  static std::string EncodeOnly(T value, int precision = 17) {
    return EncodeToString<T>(value, precision, "");
  }
};

TEST_F(InnerEncodeTest_604, EncodesNaNAsDotNan_604) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  EXPECT_EQ(EncodeOnly(nan), ".nan");
}

TEST_F(InnerEncodeTest_604, EncodesNegativeNaNAsDotNan_604) {
  // The interface only exposes the output string; this verifies negative NaN is treated as NaN.
  const double neg_nan = -std::numeric_limits<double>::quiet_NaN();
  EXPECT_EQ(EncodeOnly(neg_nan), ".nan");
}

TEST_F(InnerEncodeTest_604, EncodesPositiveInfinityAsDotInf_604) {
  const double inf = std::numeric_limits<double>::infinity();
  EXPECT_EQ(EncodeOnly(inf), ".inf");
}

TEST_F(InnerEncodeTest_604, EncodesNegativeInfinityAsMinusDotInf_604) {
  const double neg_inf = -std::numeric_limits<double>::infinity();
  EXPECT_EQ(EncodeOnly(neg_inf), "-.inf");
}

TEST_F(InnerEncodeTest_604, AppendsEncodingToExistingStreamContents_604) {
  const double inf = std::numeric_limits<double>::infinity();
  EXPECT_EQ(EncodeToString(inf, /*precision=*/17, /*prefix=*/"prefix:"), "prefix:.inf");

  const double nan = std::numeric_limits<double>::quiet_NaN();
  EXPECT_EQ(EncodeToString(nan, /*precision=*/17, /*prefix=*/"p="), "p=.nan");
}

TEST_F(InnerEncodeTest_604, EncodesFiniteDoubleToParseableNumber_604) {
  const double v = 1234.25;
  const std::string s = EncodeOnly(v, /*precision=*/17);

  // Should not collide with the special spellings.
  EXPECT_NE(s, ".nan");
  EXPECT_NE(s, ".inf");
  EXPECT_NE(s, "-.inf");
  ASSERT_FALSE(s.empty());

  // Must be parseable as a double (observable behavior: produced textual number).
  double parsed = 0.0;
  EXPECT_NO_THROW(parsed = std::stod(s));
  EXPECT_DOUBLE_EQ(parsed, v);
}

TEST_F(InnerEncodeTest_604, EncodesFiniteFloatToParseableNumber_604) {
  const float v = -0.75f;
  const std::string s = EncodeOnly(v, /*precision=*/9);

  EXPECT_NE(s, ".nan");
  EXPECT_NE(s, ".inf");
  EXPECT_NE(s, "-.inf");
  ASSERT_FALSE(s.empty());

  float parsed = 0.0f;
  EXPECT_NO_THROW(parsed = std::stof(s));
  EXPECT_FLOAT_EQ(parsed, v);
}

TEST_F(InnerEncodeTest_604, EncodesFiniteLongDoubleToParseableNumber_604) {
  const long double v = static_cast<long double>(1.0L) / static_cast<long double>(3.0L);
  const std::string s = EncodeOnly(v, /*precision=*/21);

  EXPECT_NE(s, ".nan");
  EXPECT_NE(s, ".inf");
  EXPECT_NE(s, "-.inf");
  ASSERT_FALSE(s.empty());

  long double parsed = 0.0L;
  EXPECT_NO_THROW(parsed = std::stold(s));
  EXPECT_EQ(parsed, v);
}

TEST_F(InnerEncodeTest_604, EncodesNegativeFiniteDoubleToParseableNumber_604) {
  const double v = -98765.125;
  const std::string s = EncodeOnly(v, /*precision=*/17);

  EXPECT_NE(s, ".nan");
  EXPECT_NE(s, ".inf");
  EXPECT_NE(s, "-.inf");
  ASSERT_FALSE(s.empty());

  double parsed = 0.0;
  EXPECT_NO_THROW(parsed = std::stod(s));
  EXPECT_DOUBLE_EQ(parsed, v);
}

}  // namespace