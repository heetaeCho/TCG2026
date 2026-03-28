// File: yaml-cpp/test/emittermanip_doubleprecision_test.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>

#include <limits>
#include <string>

namespace {

static std::string EmitWithPrecision(const YAML::_Precision& p, double value) {
  YAML::Emitter out;
  out << p << value;
  return std::string(out.c_str());
}

}  // namespace

// TEST_ID = 21

TEST(DoublePrecisionTest_21, ReturnTypeIsPrecisionManipulator_21) {
  // Compile-time check only: the inline function must return YAML::_Precision.
  static_assert(std::is_same_v<decltype(YAML::DoublePrecision(3)), YAML::_Precision>,
                "YAML::DoublePrecision(n) must return YAML::_Precision");
  SUCCEED();
}

TEST(DoublePrecisionTest_21, MatchesDirectPrecisionConstruction_NormalValue_21) {
  const int n = 6;

  const auto via_helper = YAML::DoublePrecision(n);
  const YAML::_Precision direct(-1, n);

  // Observable behavior: applying the returned manipulator to the emitter
  // should behave identically to applying an explicitly-constructed YAML::_Precision(-1, n).
  EXPECT_EQ(EmitWithPrecision(via_helper, 1.23456789), EmitWithPrecision(direct, 1.23456789));
}

TEST(DoublePrecisionTest_21, MatchesDirectPrecisionConstruction_Zero_21) {
  const int n = 0;

  const auto via_helper = YAML::DoublePrecision(n);
  const YAML::_Precision direct(-1, n);

  EXPECT_EQ(EmitWithPrecision(via_helper, 123.456), EmitWithPrecision(direct, 123.456));
}

TEST(DoublePrecisionTest_21, MatchesDirectPrecisionConstruction_One_21) {
  const int n = 1;

  const auto via_helper = YAML::DoublePrecision(n);
  const YAML::_Precision direct(-1, n);

  EXPECT_EQ(EmitWithPrecision(via_helper, 123.456), EmitWithPrecision(direct, 123.456));
}

TEST(DoublePrecisionTest_21, MatchesDirectPrecisionConstruction_LargePrecision_21) {
  const int n = 50;

  const auto via_helper = YAML::DoublePrecision(n);
  const YAML::_Precision direct(-1, n);

  EXPECT_EQ(EmitWithPrecision(via_helper, 1.0 / 3.0), EmitWithPrecision(direct, 1.0 / 3.0));
}

TEST(DoublePrecisionTest_21, MatchesDirectPrecisionConstruction_NegativePrecision_21) {
  const int n = -7;

  const auto via_helper = YAML::DoublePrecision(n);
  const YAML::_Precision direct(-1, n);

  // Error/edge case: negative values are permitted by the signature; verify the helper
  // still maps to the same observable manipulator behavior as direct construction.
  EXPECT_EQ(EmitWithPrecision(via_helper, 42.42), EmitWithPrecision(direct, 42.42));
}

TEST(DoublePrecisionTest_21, DoesNotCrashWhenUsedMultipleTimes_21) {
  const auto p2 = YAML::DoublePrecision(2);
  const auto p8 = YAML::DoublePrecision(8);

  YAML::Emitter out;
  EXPECT_NO_THROW({
    out << p2 << 1.2345;
    out << p8 << 1.2345;
    out << p2 << 1.2345;
  });

  // Basic sanity: emitter produced some output.
  EXPECT_FALSE(std::string(out.c_str()).empty());
}
