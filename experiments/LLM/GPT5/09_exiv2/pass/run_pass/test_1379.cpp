// =================================================================================================
// Copyright
// =================================================================================================
//
// Unit tests for Exiv2::Internal::printDegrees (tags_int.cpp)
// Test ID: 1379
//
// Constraints honored:
// - Treat implementation as black box (assert only via observable ostream output & formatting side-effects)
// - No private/internal state access
// - No re-implementation of logic
//
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {
// Forward declaration to match the implementation under test (defined in src/tags_int.cpp).
std::ostream& printDegrees(std::ostream& os, const Value& value, const ExifData*);
}  // namespace Internal
}  // namespace Exiv2

namespace {

// Helper: create a signed-rational Value and read three rationals from a string.
// (Uses public Exiv2 Value factory + read parsing; no internal assumptions.)
Exiv2::Value::UniquePtr makeSignedRationalValue(const std::string& text) {
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedRational);
  EXPECT_NE(v.get(), nullptr);
  EXPECT_NO_THROW(v->read(text));
  return v;
}

std::string valueStreamString(const Exiv2::Value& v) {
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

}  // namespace

TEST(PrintDegreesTest_1379, FormatsValidThreeRationalsWithIntegerSeconds_1379) {
  // deg.second == 1, min.second > 0, sec.second > 0, and no fractional-minutes conversion needed.
  auto v = makeSignedRationalValue("12/1 34/1 56/1");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.str(), "12 deg 34' 56\"");
}

TEST(PrintDegreesTest_1379, FormatsValidThreeRationalsWithFractionalSecondsShowsTwoDecimals_1379) {
  // sec.second > 1 => fixed with precision 2.
  auto v = makeSignedRationalValue("12/1 34/1 123/10");  // 12.30"
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.str(), "12 deg 34' 12.30\"");
}

TEST(PrintDegreesTest_1379, NonThreeCountPrintsValueInParentheses_1379) {
  // count != 3 => "(<value>)"
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::signedRational);
  ASSERT_NE(v.get(), nullptr);
  ASSERT_NO_THROW(v->read("1/1 2/1"));  // only 2 components

  const std::string inner = valueStreamString(*v);

  std::ostringstream os;
  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST(PrintDegreesTest_1379, InvalidDegreeDenominatorPrintsValueInParentheses_1379) {
  // deg.second != 1 => "(<value>)"
  auto v = makeSignedRationalValue("12/2 34/1 56/1");
  ASSERT_NE(v.get(), nullptr);

  const std::string inner = valueStreamString(*v);

  std::ostringstream os;
  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST(PrintDegreesTest_1379, InvalidMinuteOrSecondDenominatorPrintsValueInParentheses_1379) {
  // min.second <= 0 OR sec.second <= 0 => "(<value>)"
  // Here: sec.second == 0.
  auto v = makeSignedRationalValue("12/1 34/1 56/0");
  ASSERT_NE(v.get(), nullptr);

  const std::string inner = valueStreamString(*v);

  std::ostringstream os;
  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST(PrintDegreesTest_1379, FractionalMinutesMayConvertToSecondsWhenSecondsZero_1379) {
  // When min has remainder (fractional minutes) and sec == 0/1, implementation may convert remainder
  // into seconds and proceed with printing degrees format.
  auto v = makeSignedRationalValue("1/1 1/2 0/1");  // min = 0.5 => expected 30.00" after conversion
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.str(), "1 deg 0' 30.00\"");
}

TEST(PrintDegreesTest_1379, FractionalMinutesWithNonZeroSecondsFallsBackToParenthesizedValue_1379) {
  // If minutes are fractional but seconds are not exactly 0/1, falls back to "(<value>)".
  auto v = makeSignedRationalValue("1/1 1/2 1/1");
  ASSERT_NE(v.get(), nullptr);

  const std::string inner = valueStreamString(*v);

  std::ostringstream os;
  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST(PrintDegreesTest_1379, FractionalMinutesWithHugeRemainderMayFallBackToParenthesizedValue_1379) {
  // Boundary-style case: fractional minutes remainder too large to convert (observable via fallback).
  // Choose denom so remainder (denom-1) is > max_int32/60.
  const int32_t denom = static_cast<int32_t>(std::numeric_limits<int32_t>::max() / 60) + 2;  // > max/60
  const int32_t numer = static_cast<int32_t>(2LL * denom - 1);  // remainder denom-1 (fits in int32)
  std::ostringstream input;
  input << "1/1 " << numer << "/" << denom << " 0/1";

  auto v = makeSignedRationalValue(input.str());
  ASSERT_NE(v.get(), nullptr);

  const std::string inner = valueStreamString(*v);

  std::ostringstream os;
  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.str(), "(" + inner + ")");
}

TEST(PrintDegreesTest_1379, RestoresStreamFormattingFlagsAndPrecisionAfterPrinting_1379) {
  // Observable side-effect: stream flags/precision should be restored.
  auto v = makeSignedRationalValue("12/1 34/1 123/10");
  ASSERT_NE(v.get(), nullptr);

  std::ostringstream os;
  os << std::scientific;
  os << std::setprecision(7);

  const std::ios::fmtflags beforeFlags = os.flags();
  const std::streamsize beforePrec = os.precision();

  Exiv2::Internal::printDegrees(os, *v, nullptr);

  EXPECT_EQ(os.flags(), beforeFlags);
  EXPECT_EQ(os.precision(), beforePrec);

  // Also verify continued streaming uses the original formatting mode.
  os << " " << 1234.0;
  const std::string out = os.str();
  // In scientific with precision 7, 1234.0 should contain an 'e'/'E' exponent marker.
  EXPECT_TRUE(out.find('e') != std::string::npos || out.find('E') != std::string::npos);
}