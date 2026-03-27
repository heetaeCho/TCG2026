// File: ./TestProjects/yaml-cpp/test/fptostring_test_433.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <limits>
#include <string>

#include "yaml-cpp/yaml.h"  // Provides YAML::FpToString(double, size_t)

namespace {

using ::YAML::FpToString;

class FpToStringTest_433 : public ::testing::Test {};

TEST_F(FpToStringTest_433, ReturnsNonEmptyForZero_433) {
  const std::string s = FpToString(0.0, 0);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_433, DeterministicForSameInputs_433) {
  const double v = 123.456;
  const size_t p = 6;
  const std::string a = FpToString(v, p);
  const std::string b = FpToString(v, p);
  EXPECT_EQ(a, b);
}

TEST_F(FpToStringTest_433, DifferentPrecisionUsuallyChangesOutput_433) {
  // We don't assume the exact formatting rules, only that precision is an input
  // that can affect output. Use a value with fractional part so it's likely.
  const double v = 1.23456789;

  const std::string s0 = FpToString(v, 0);
  const std::string s2 = FpToString(v, 2);
  const std::string s8 = FpToString(v, 8);

  EXPECT_FALSE(s0.empty());
  EXPECT_FALSE(s2.empty());
  EXPECT_FALSE(s8.empty());

  // At least one pair should differ for a value with many fractional digits.
  EXPECT_TRUE((s0 != s2) || (s2 != s8) || (s0 != s8));
}

TEST_F(FpToStringTest_433, HandlesNegativeZeroDistinctlyOrAtLeastValid_433) {
  // Some formatters emit "-0" or "-0.0..." for -0.0; others normalize to "0".
  // We only require it returns a valid, non-empty string and is deterministic.
  const double neg_zero = -0.0;
  const std::string s1 = FpToString(neg_zero, 3);
  const std::string s2 = FpToString(neg_zero, 3);
  EXPECT_FALSE(s1.empty());
  EXPECT_EQ(s1, s2);
}

TEST_F(FpToStringTest_433, HandlesLargeMagnitudeFiniteValues_433) {
  const double v = std::numeric_limits<double>::max();
  const std::string s = FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_433, HandlesSmallPositiveFiniteValues_433) {
  const double v = std::numeric_limits<double>::min();  // smallest positive normal
  const std::string s = FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_433, HandlesDenormalValues_433) {
  const double v = std::numeric_limits<double>::denorm_min();
  const std::string s = FpToString(v, 6);
  EXPECT_FALSE(s.empty());
}

TEST_F(FpToStringTest_433, HandlesInfinityWithoutThrowing_433) {
  const double inf = std::numeric_limits<double>::infinity();
  EXPECT_NO_THROW({
    const std::string s = FpToString(inf, 6);
    EXPECT_FALSE(s.empty());
  });

  const double ninf = -std::numeric_limits<double>::infinity();
  EXPECT_NO_THROW({
    const std::string s = FpToString(ninf, 6);
    EXPECT_FALSE(s.empty());
  });
}

TEST_F(FpToStringTest_433, HandlesNaNWithoutThrowing_433) {
  const double nan = std::numeric_limits<double>::quiet_NaN();
  EXPECT_NO_THROW({
    const std::string s = FpToString(nan, 6);
    EXPECT_FALSE(s.empty());
  });
}

TEST_F(FpToStringTest_433, PrecisionBoundaryZeroAndOne_433) {
  const double v = 42.5;

  const std::string s0 = FpToString(v, 0);
  const std::string s1 = FpToString(v, 1);

  EXPECT_FALSE(s0.empty());
  EXPECT_FALSE(s1.empty());
  EXPECT_NE(s0, FpToString(v, 0));  // re-check deterministic via fresh call
  EXPECT_EQ(s1, FpToString(v, 1));
}

TEST_F(FpToStringTest_433, AcceptsVeryLargePrecisionValue_433) {
  // Boundary / stress: ensure the API accepts large precision without crashing.
  // We do not assert size or exact format; only that it returns a string.
  const double v = 3.141592653589793;
  const size_t p = 200;

  EXPECT_NO_THROW({
    const std::string s = FpToString(v, p);
    EXPECT_FALSE(s.empty());
  });
}

}  // namespace