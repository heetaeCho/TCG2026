// File: test_types_parseRational_1160.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include "types.hpp"  // Exiv2::Rational, Exiv2::parseRational

namespace {

class ParseRationalTest_1160 : public ::testing::Test {};

TEST_F(ParseRationalTest_1160, ParsesFractionString_1160) {
  bool ok = false;
  const Exiv2::Rational r = Exiv2::parseRational("1/2", ok);

  ASSERT_TRUE(ok);
  EXPECT_EQ(r, Exiv2::Rational(1, 2));
}

TEST_F(ParseRationalTest_1160, ParsesNegativeFractionString_1160) {
  bool ok = false;
  const Exiv2::Rational r = Exiv2::parseRational("-3/4", ok);

  ASSERT_TRUE(ok);
  EXPECT_EQ(r, Exiv2::Rational(-3, 4));
}

TEST_F(ParseRationalTest_1160, ParsesIntegerStringAsDenominatorOne_1160) {
  bool ok = false;
  const Exiv2::Rational r = Exiv2::parseRational("42", ok);

  ASSERT_TRUE(ok);
  EXPECT_EQ(r, Exiv2::Rational(42, 1));
}

TEST_F(ParseRationalTest_1160, ParsesBooleanTrueAsOneOverOne_1160) {
  bool ok = false;
  const Exiv2::Rational r = Exiv2::parseRational("true", ok);

  ASSERT_TRUE(ok);
  EXPECT_EQ(r, Exiv2::Rational(1, 1));
}

TEST_F(ParseRationalTest_1160, ParsesBooleanFalseAsZeroOverOne_1160) {
  bool ok = false;
  const Exiv2::Rational r = Exiv2::parseRational("false", ok);

  ASSERT_TRUE(ok);
  EXPECT_EQ(r, Exiv2::Rational(0, 1));
}

TEST_F(ParseRationalTest_1160, ParsesFloatStringSetsOkTrue_1160) {
  // The exact Rational produced by floatToRationalCast is implementation-defined from this interface,
  // so only assert observable success.
  bool ok = false;
  (void)Exiv2::parseRational("0.5", ok);

  EXPECT_TRUE(ok);
}

TEST_F(ParseRationalTest_1160, InvalidStringSetsOkFalse_1160) {
  bool ok = true;  // ensure it is overwritten/updated by the function
  (void)Exiv2::parseRational("not-a-number", ok);

  EXPECT_FALSE(ok);
}

TEST_F(ParseRationalTest_1160, EmptyStringSetsOkFalse_1160) {
  bool ok = true;
  (void)Exiv2::parseRational("", ok);

  EXPECT_FALSE(ok);
}

TEST_F(ParseRationalTest_1160, LargeIntegerStringParsesAsDenominatorOne_1160) {
  // Boundary-ish: large magnitude that still fits in typical long ranges.
  const long v = 2000000000L;

  bool ok = false;
  const Exiv2::Rational r = Exiv2::parseRational(std::to_string(v), ok);

  ASSERT_TRUE(ok);
  EXPECT_EQ(r, Exiv2::Rational(v, 1));
}

}  // namespace