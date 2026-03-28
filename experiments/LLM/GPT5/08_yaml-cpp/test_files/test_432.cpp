// File: ./TestProjects/yaml-cpp/test/fptostring_test_432.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <limits>
#include <string>

#include "yaml-cpp/yaml.h"  // Provides YAML::FpToString(float, size_t)

namespace {

class FpToStringTest_432 : public ::testing::Test {};

}  // namespace

TEST_F(FpToStringTest_432, ReturnsStringForZero_432) {
  const std::string s = YAML::FpToString(0.0f, 0);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, ReturnsStringForNegativeZero_432) {
  const float neg_zero = -0.0f;
  ASSERT_EQ(std::signbit(neg_zero), true);

  const std::string s = YAML::FpToString(neg_zero, 0);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, ReturnsStringForPositiveValue_432) {
  const std::string s = YAML::FpToString(1.0f, 3);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, ReturnsStringForNegativeValue_432) {
  const std::string s = YAML::FpToString(-1.25f, 4);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, DeterministicForSameInputs_432) {
  const float v = 123.456f;
  const size_t precision = 5;

  const std::string a = YAML::FpToString(v, precision);
  const std::string b = YAML::FpToString(v, precision);

  EXPECT_EQ(a, b);
  EXPECT_FALSE(a.empty());
}

TEST_F(FpToStringTest_432, HandlesLargePrecision_432) {
  // Boundary-ish check: large precision should still return a string.
  // We don't assume any particular formatting rules.
  const std::string s = YAML::FpToString(3.1415926f, 100);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, HandlesMaxFloat_432) {
  const float v = std::numeric_limits<float>::max();
  const std::string s = YAML::FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, HandlesMinPositiveNormalFloat_432) {
  const float v = std::numeric_limits<float>::min();  // Smallest positive *normal*
  const std::string s = YAML::FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, HandlesDenormMin_432) {
  const float v = std::numeric_limits<float>::denorm_min();
  const std::string s = YAML::FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, HandlesInfinity_432) {
  const float v = std::numeric_limits<float>::infinity();
  const std::string s = YAML::FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, HandlesNegativeInfinity_432) {
  const float v = -std::numeric_limits<float>::infinity();
  const std::string s = YAML::FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, HandlesNaN_432) {
  const float v = std::numeric_limits<float>::quiet_NaN();
  ASSERT_TRUE(std::isnan(v));

  const std::string s = YAML::FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_432, PrecisionAffectsOrAtLeastIsAccepted_432) {
  // We don't require that precision changes the output (implementation-defined),
  // but we do verify the API accepts different precision values and returns strings.
  const float v = 1.234567f;

  const std::string p0 = YAML::FpToString(v, 0);
  const std::string p1 = YAML::FpToString(v, 1);
  const std::string p6 = YAML::FpToString(v, 6);

  EXPECT_FALSE(p0.empty());
  EXPECT_FALSE(p1.empty());
  EXPECT_FALSE(p6.empty());

  // "Observable" behavior: determinism per (v, precision).
  EXPECT_EQ(p0, YAML::FpToString(v, 0));
  EXPECT_EQ(p1, YAML::FpToString(v, 1));
  EXPECT_EQ(p6, YAML::FpToString(v, 6));
}

TEST_F(FpToStringTest_432, DoesNotThrowForTypicalInputs_432) {
  // If the implementation throws, that's observable and would fail this test.
  EXPECT_NO_THROW((void)YAML::FpToString(42.0f, 2));
  EXPECT_NO_THROW((void)YAML::FpToString(-42.0f, 2));
  EXPECT_NO_THROW((void)YAML::FpToString(0.0f, 2));
}