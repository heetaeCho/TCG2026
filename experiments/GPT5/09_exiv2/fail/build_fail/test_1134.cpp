// SPDX-License-Identifier: GPL-2.0-or-later
// TestProjects/exiv2/tests/test_types_fromStreamToRational_1134.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <string>

// NOTE:
// The function under test is a `static` (internal linkage) abbreviated function template
// defined in ./TestProjects/exiv2/src/types.cpp. To test it as a black box via its
// provided interface, we include the implementation file so the definition is available
// in this translation unit.
#include "TestProjects/exiv2/src/types.cpp"

namespace {

using Exiv2::Rational;

class FromStreamToRationalTest_1134 : public ::testing::Test {
 protected:
  static Rational Sentinel() { return Rational{111, 222}; }
};

TEST_F(FromStreamToRationalTest_1134, ParsesIntegerFractionWithSlash_1134) {
  std::istringstream is("3/4");
  Rational r = Sentinel();

  std::istream& ret = Exiv2::fromStreamToRational(is, r);

  EXPECT_EQ(&ret, &is);
  EXPECT_TRUE(is.good());
  EXPECT_EQ(r.first, 3);
  EXPECT_EQ(r.second, 4);
}

TEST_F(FromStreamToRationalTest_1134, ParsesIntegerFractionWithWhitespaceAroundSlash_1134) {
  std::istringstream is("  5   /   6  ");
  Rational r = Sentinel();

  Exiv2::fromStreamToRational(is, r);

  EXPECT_TRUE(is.good());
  EXPECT_EQ(r.first, 5);
  EXPECT_EQ(r.second, 6);
}

TEST_F(FromStreamToRationalTest_1134, FailsWhenSeparatorIsNotSlashAndDoesNotModifyOutput_1134) {
  std::istringstream is("7:8");
  Rational r = Sentinel();

  Exiv2::fromStreamToRational(is, r);

  EXPECT_TRUE(is.fail());
  EXPECT_EQ(r.first, Sentinel().first);
  EXPECT_EQ(r.second, Sentinel().second);
}

TEST_F(FromStreamToRationalTest_1134, FailsWhenDenominatorMissingAndDoesNotModifyOutput_1134) {
  std::istringstream is("9/");
  Rational r = Sentinel();

  Exiv2::fromStreamToRational(is, r);

  EXPECT_TRUE(is.fail());
  EXPECT_EQ(r.first, Sentinel().first);
  EXPECT_EQ(r.second, Sentinel().second);
}

TEST_F(FromStreamToRationalTest_1134, ParsesMinAndMaxInt32Values_1134) {
  const int32_t kMin = (std::numeric_limits<int32_t>::min)();
  const int32_t kMax = (std::numeric_limits<int32_t>::max)();

  {
    std::ostringstream oss;
    oss << kMin << "/" << kMax;
    std::istringstream is(oss.str());
    Rational r = Sentinel();

    Exiv2::fromStreamToRational(is, r);

    EXPECT_TRUE(is.good());
    EXPECT_EQ(r.first, kMin);
    EXPECT_EQ(r.second, kMax);
  }

  {
    std::ostringstream oss;
    oss << kMax << "/" << 1;
    std::istringstream is(oss.str());
    Rational r = Sentinel();

    Exiv2::fromStreamToRational(is, r);

    EXPECT_TRUE(is.good());
    EXPECT_EQ(r.first, kMax);
    EXPECT_EQ(r.second, 1);
  }
}

TEST_F(FromStreamToRationalTest_1134, ParsesFloatModeWhenLeadingTokenIsLowercaseF_1134) {
  std::istringstream is("f 4");
  Rational r = Sentinel();

  Exiv2::fromStreamToRational(is, r);

  EXPECT_TRUE(is.good());

  // Black-box expectation: result equals what the implementation computes and then
  // converts via the public conversion function.
  const float input = 4.0F;
  const float computed = 2.0F * std::log2(input);
  const Rational expected = Exiv2::floatToRationalCast(computed);

  EXPECT_EQ(r.first, expected.first);
  EXPECT_EQ(r.second, expected.second);
}

TEST_F(FromStreamToRationalTest_1134, ParsesFloatModeWhenLeadingTokenIsUppercaseF_1134) {
  std::istringstream is("F 1");
  Rational r = Sentinel();

  Exiv2::fromStreamToRational(is, r);

  EXPECT_TRUE(is.good());

  const float input = 1.0F;
  const float computed = 2.0F * std::log2(input);
  const Rational expected = Exiv2::floatToRationalCast(computed);

  EXPECT_EQ(r.first, expected.first);
  EXPECT_EQ(r.second, expected.second);
}

TEST_F(FromStreamToRationalTest_1134, FloatModeFailsOnMissingFloatAndDoesNotModifyOutput_1134) {
  std::istringstream is("f");
  Rational r = Sentinel();

  Exiv2::fromStreamToRational(is, r);

  EXPECT_TRUE(is.fail());
  EXPECT_EQ(r.first, Sentinel().first);
  EXPECT_EQ(r.second, Sentinel().second);
}

}  // namespace