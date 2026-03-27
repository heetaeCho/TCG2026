// File: test_minoltamn_int_printMinoltaSonyRotation_1034.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

// Declaration lives in minoltamn_int.cpp (Internal namespace)
namespace Exiv2 {
namespace Internal {
std::ostream& printMinoltaSonyRotation(std::ostream& os, const Value& value, const ExifData* metadata);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class PrintMinoltaSonyRotationTest_1034 : public ::testing::Test {
protected:
  static Exiv2::Value::UniquePtr makeUShortValueFromNumber(uint32_t n) {
    // Exiv2 values typically parse numeric content via read(std::string).
    auto v = Exiv2::Value::create(Exiv2::unsignedShort);
    // If parsing fails in some environments, tests will fail clearly rather than guessing behavior.
    const int rc = v->read(std::to_string(n));
    EXPECT_EQ(0, rc);
    return v;
  }

  static std::string render(const Exiv2::Value& v, const Exiv2::ExifData* md) {
    std::ostringstream os;
    Exiv2::Internal::printMinoltaSonyRotation(os, v, md);
    return os.str();
  }
};

TEST_F(PrintMinoltaSonyRotationTest_1034, ReturnsSameStreamReference_1034) {
  auto v = makeUShortValueFromNumber(0);

  std::ostringstream os;
  std::ostream* const before = &os;

  std::ostream& ret = Exiv2::Internal::printMinoltaSonyRotation(os, *v, nullptr);
  std::ostream* const after = &ret;

  EXPECT_EQ(before, after);
}

TEST_F(PrintMinoltaSonyRotationTest_1034, Value0PrintsHorizontalNormal_1034) {
  auto v = makeUShortValueFromNumber(0);

  const std::string outNullMd = render(*v, nullptr);
  EXPECT_NE(std::string::npos, outNullMd.find("Horizontal")) << outNullMd;

  Exiv2::ExifData md;
  const std::string outWithMd = render(*v, &md);
  EXPECT_NE(std::string::npos, outWithMd.find("Horizontal")) << outWithMd;
}

TEST_F(PrintMinoltaSonyRotationTest_1034, Value1PrintsRotate90CW_1034) {
  auto v = makeUShortValueFromNumber(1);

  const std::string out = render(*v, nullptr);
  EXPECT_NE(std::string::npos, out.find("Rotate")) << out;
  EXPECT_NE(std::string::npos, out.find("90")) << out;
  EXPECT_NE(std::string::npos, out.find("CW")) << out;
}

TEST_F(PrintMinoltaSonyRotationTest_1034, Value2PrintsRotate270CW_1034) {
  auto v = makeUShortValueFromNumber(2);

  const std::string out = render(*v, nullptr);
  EXPECT_NE(std::string::npos, out.find("Rotate")) << out;
  EXPECT_NE(std::string::npos, out.find("270")) << out;
  EXPECT_NE(std::string::npos, out.find("CW")) << out;
}

TEST_F(PrintMinoltaSonyRotationTest_1034, OutOfRangeValueFallsBackToNumericOrAtLeastIncludesNumber_1034) {
  // Boundary/error-ish case: not covered by the known TagDetails (0..2).
  auto v = makeUShortValueFromNumber(3);

  const std::string out = render(*v, nullptr);

  // Black-box expectation: unknown values should still produce some output,
  // commonly including the numeric value itself.
  EXPECT_FALSE(out.empty());
  EXPECT_NE(std::string::npos, out.find("3")) << out;
}

TEST_F(PrintMinoltaSonyRotationTest_1034, LargeValueDoesNotCrashAndProducesOutput_1034) {
  // Boundary: a large (but still parseable) value.
  auto v = makeUShortValueFromNumber(65535);

  const std::string out = render(*v, nullptr);
  EXPECT_FALSE(out.empty());
}

}  // namespace