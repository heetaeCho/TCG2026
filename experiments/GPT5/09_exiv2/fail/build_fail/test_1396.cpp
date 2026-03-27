// File: test_tags_int_print0x829d_test.cpp
// Unit tests for Exiv2::Internal::print0x829d
//
// TEST_ID: 1396

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>

namespace Exiv2 {
namespace Internal {

// The function under test lives in src/tags_int.cpp. It may not be declared in a public header,
// so we declare it here for testing and link against the real implementation.
std::ostream& print0x829d(std::ostream& os, const Exiv2::Value& value, const Exiv2::ExifData*);

}  // namespace Internal
}  // namespace Exiv2

namespace {

using ::testing::StartsWith;

class Print0x829dTest_1396 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeRationalValue(Exiv2::TypeId type, const std::string& text) {
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(type);
    EXPECT_NE(v.get(), nullptr);
    v->read(text);
    return v;
  }

  static std::string FormatExpectedF(float x) {
    // Match the observable formatting intent (two significant digits, default float formatting)
    // without depending on Exiv2 internals.
    std::ostringstream oss;
    oss << 'F' << std::setprecision(2) << std::defaultfloat << x;
    return oss.str();
  }
};

TEST_F(Print0x829dTest_1396, PrintsFNumberForNonZeroDenominator_1396) {
  // Arrange: a rational value with non-zero denominator
  auto v = MakeRationalValue(Exiv2::unsignedRational, "5/2");  // 2.5

  std::ostringstream os;

  // Act
  Exiv2::Internal::print0x829d(os, *v, /*ExifData*/ nullptr);

  // Assert
  const std::string expected = FormatExpectedF(2.5f);
  EXPECT_EQ(os.str(), expected);
}

TEST_F(Print0x829dTest_1396, RoundsToTwoSignificantDigits_1396) {
  // Arrange: 8/3 = 2.666..., should round with two significant digits
  auto v = MakeRationalValue(Exiv2::unsignedRational, "8/3");

  std::ostringstream os;

  // Act
  Exiv2::Internal::print0x829d(os, *v, /*ExifData*/ nullptr);

  // Assert: compare against equivalent iostream formatting behavior.
  const std::string expected = FormatExpectedF(8.0f / 3.0f);
  EXPECT_EQ(os.str(), expected);
}

TEST_F(Print0x829dTest_1396, PrintsParenthesizedValueWhenDenominatorIsZero_1396) {
  // Arrange: denominator 0 (if parsing accepts it)
  auto v = MakeRationalValue(Exiv2::unsignedRational, "1/0");

  std::ostringstream os;

  // Act
  Exiv2::Internal::print0x829d(os, *v, /*ExifData*/ nullptr);

  // Assert: output is "(" + streamed value + ")"
  const std::string valueText = v->toString();
  EXPECT_EQ(os.str(), "(" + valueText + ")");
  EXPECT_THAT(os.str(), StartsWith("("));
  EXPECT_TRUE(!os.str().empty() && os.str().back() == ')');
}

TEST_F(Print0x829dTest_1396, SupportsSignedRationalValues_1396) {
  // Arrange: signed rational -1/2 = -0.5
  auto v = MakeRationalValue(Exiv2::signedRational, "-1/2");

  std::ostringstream os;

  // Act
  Exiv2::Internal::print0x829d(os, *v, /*ExifData*/ nullptr);

  // Assert
  const std::string expected = FormatExpectedF(-0.5f);
  EXPECT_EQ(os.str(), expected);
}

TEST_F(Print0x829dTest_1396, ExifDataPointerDoesNotAffectOutput_1396) {
  // Arrange
  auto v = MakeRationalValue(Exiv2::unsignedRational, "10/4");  // 2.5
  Exiv2::ExifData exif;

  std::ostringstream osNull;
  std::ostringstream osNonNull;

  // Act
  Exiv2::Internal::print0x829d(osNull, *v, /*ExifData*/ nullptr);
  Exiv2::Internal::print0x829d(osNonNull, *v, &exif);

  // Assert
  EXPECT_EQ(osNull.str(), osNonNull.str());
}

}  // namespace