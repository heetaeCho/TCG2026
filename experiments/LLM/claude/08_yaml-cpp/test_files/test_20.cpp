#include <gtest/gtest.h>
#include "yaml-cpp/emittermanip.h"

// Test that FloatPrecision returns a _Precision with the expected float precision value
TEST(FloatPrecisionTest_20, ReturnsCorrectFloatPrecision_20) {
  YAML::_Precision p = YAML::FloatPrecision(5);
  // _Precision should store the float precision as the first member
  // and -1 for the double precision (not set)
  EXPECT_EQ(p.floatPrecision, 5);
  EXPECT_EQ(p.doublePrecision, -1);
}

// Test FloatPrecision with zero precision
TEST(FloatPrecisionTest_20, ZeroPrecision_20) {
  YAML::_Precision p = YAML::FloatPrecision(0);
  EXPECT_EQ(p.floatPrecision, 0);
  EXPECT_EQ(p.doublePrecision, -1);
}

// Test FloatPrecision with a typical precision value
TEST(FloatPrecisionTest_20, TypicalPrecisionValue_20) {
  YAML::_Precision p = YAML::FloatPrecision(6);
  EXPECT_EQ(p.floatPrecision, 6);
  EXPECT_EQ(p.doublePrecision, -1);
}

// Test FloatPrecision with maximum reasonable float precision
TEST(FloatPrecisionTest_20, HighPrecisionValue_20) {
  YAML::_Precision p = YAML::FloatPrecision(std::numeric_limits<float>::max_digits10);
  EXPECT_EQ(p.floatPrecision, std::numeric_limits<float>::max_digits10);
  EXPECT_EQ(p.doublePrecision, -1);
}

// Test FloatPrecision with negative precision
TEST(FloatPrecisionTest_20, NegativePrecision_20) {
  YAML::_Precision p = YAML::FloatPrecision(-1);
  EXPECT_EQ(p.floatPrecision, -1);
  EXPECT_EQ(p.doublePrecision, -1);
}

// Test FloatPrecision with precision of 1
TEST(FloatPrecisionTest_20, PrecisionOne_20) {
  YAML::_Precision p = YAML::FloatPrecision(1);
  EXPECT_EQ(p.floatPrecision, 1);
  EXPECT_EQ(p.doublePrecision, -1);
}

// Test that DoublePrecision works if available (complementary to FloatPrecision)
TEST(DoublePrecisionTest_20, ReturnsCorrectDoublePrecision_20) {
  YAML::_Precision p = YAML::DoublePrecision(10);
  EXPECT_EQ(p.floatPrecision, -1);
  EXPECT_EQ(p.doublePrecision, 10);
}

// Test that FloatPrecision and DoublePrecision produce different results
TEST(PrecisionTest_20, FloatAndDoubleDiffer_20) {
  YAML::_Precision fp = YAML::FloatPrecision(5);
  YAML::_Precision dp = YAML::DoublePrecision(5);
  EXPECT_EQ(fp.floatPrecision, 5);
  EXPECT_EQ(fp.doublePrecision, -1);
  EXPECT_EQ(dp.floatPrecision, -1);
  EXPECT_EQ(dp.doublePrecision, 5);
}

// Test FloatPrecision with large integer value
TEST(FloatPrecisionTest_20, LargeValue_20) {
  YAML::_Precision p = YAML::FloatPrecision(100);
  EXPECT_EQ(p.floatPrecision, 100);
  EXPECT_EQ(p.doublePrecision, -1);
}
