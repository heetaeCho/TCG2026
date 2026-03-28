// TEST_ID: 22
// File: test/emitter_precision_test_22.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/yaml.h>
#include <yaml-cpp/emittermanip.h>

#include <iomanip>
#include <limits>
#include <sstream>
#include <string>

namespace {

template <typename T>
std::string StdFormatWithPrecision(int n, T value) {
  std::ostringstream oss;
  oss << std::setprecision(n) << value;
  return oss.str();
}

template <typename T>
std::string YamlEmitScalarWithPrecision(int n, T value) {
  YAML::Emitter out;
  out << YAML::Precision(n) << value;
  return std::string(out.c_str());
}

}  // namespace

TEST(PrecisionTest_22, EmitsDoubleWithRequestedPrecision_22) {
  const int n = 3;
  const double v = 1.23456789;

  const std::string expected = StdFormatWithPrecision(n, v);
  const std::string actual = YamlEmitScalarWithPrecision(n, v);

  EXPECT_EQ(actual, expected);
}

TEST(PrecisionTest_22, EmitsFloatWithRequestedPrecision_22) {
  const int n = 5;
  const float v = 1.2345678f;

  const std::string expected = StdFormatWithPrecision(n, v);
  const std::string actual = YamlEmitScalarWithPrecision(n, v);

  EXPECT_EQ(actual, expected);
}

TEST(PrecisionTest_22, PrecisionZeroIsHandled_22) {
  const int n = 0;
  const double v = 1234.567;

  const std::string expected = StdFormatWithPrecision(n, v);
  const std::string actual = YamlEmitScalarWithPrecision(n, v);

  EXPECT_EQ(actual, expected);
}

TEST(PrecisionTest_22, LargePrecisionIsHandled_22) {
  const int n = 50;
  const double v = 1.0 / 3.0;

  const std::string expected = StdFormatWithPrecision(n, v);
  const std::string actual = YamlEmitScalarWithPrecision(n, v);

  EXPECT_EQ(actual, expected);
}

TEST(PrecisionTest_22, ConstructAndUseDoesNotThrowForNegativePrecision_22) {
  // Behavior for negative precision is library/implementation dependent; this test
  // only verifies it is safe/observable through the public interface (no throw).
  EXPECT_NO_THROW({
    YAML::Emitter out;
    out << YAML::Precision(-1) << 1.2345;
    (void)out.c_str();
  });
}

TEST(PrecisionTest_22, WorksWithExtremeValues_22) {
  const int n = 10;

  {
    const double v = std::numeric_limits<double>::max();
    const std::string expected = StdFormatWithPrecision(n, v);
    const std::string actual = YamlEmitScalarWithPrecision(n, v);
    EXPECT_EQ(actual, expected);
  }

  {
    const double v = std::numeric_limits<double>::min();
    const std::string expected = StdFormatWithPrecision(n, v);
    const std::string actual = YamlEmitScalarWithPrecision(n, v);
    EXPECT_EQ(actual, expected);
  }
}
