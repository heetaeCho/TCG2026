// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 851
//
// Unit tests for Exiv2::XmpArrayValue::toRational(size_t)
// File under test: ./TestProjects/exiv2/src/value.cpp (partial snippet provided)

#include <gtest/gtest.h>

#include <cstddef>
#include <stdexcept>
#include <string>

#include "exiv2/value.hpp"
#include "exiv2/types.hpp"

namespace {

class XmpArrayValueTest_851 : public ::testing::Test {
 protected:
  static Exiv2::XmpArrayValue MakeValue() {
    // Avoid assuming any particular valid TypeId enumerator exists/should be used here.
    // The constructor takes a TypeId; we only rely on observable behavior via public APIs.
    return Exiv2::XmpArrayValue(static_cast<Exiv2::TypeId>(0));
  }

  // Reads buf into value, asserting read doesn't throw (it returns int; we don't assume meaning).
  static void ReadNoThrow(Exiv2::XmpArrayValue& v, const std::string& buf) {
    EXPECT_NO_THROW((void)v.read(buf));
  }
};

TEST_F(XmpArrayValueTest_851, DefaultCountIsZeroAndToRationalThrowsOutOfRange_851) {
  auto v = MakeValue();

  EXPECT_EQ(v.count(), 0u);

  // Implementation uses value_.at(n); observable behavior should be std::out_of_range.
  EXPECT_THROW((void)v.toRational(0), std::out_of_range);
}

TEST_F(XmpArrayValueTest_851, ReadSingleRational_AllowsToRationalAtIndexZero_851) {
  auto v = MakeValue();

  // Common rational text form; we don't infer parsing logic beyond public outcomes.
  ReadNoThrow(v, "1/2");

  // For "normal operation", require at least one element after reading a simple rational.
  ASSERT_GE(v.count(), 1u);

  EXPECT_NO_THROW({
    const Exiv2::Rational r = v.toRational(0);
    // Compare to an expected Rational value, using braced init to work with pair/struct.
    EXPECT_EQ(r, (Exiv2::Rational{1, 2}));
  });

  // If parsing succeeded, ok() should remain true.
  EXPECT_TRUE(v.ok());
}

TEST_F(XmpArrayValueTest_851, ReadMultipleRationals_ToRationalSecondElementIfPresent_851) {
  auto v = MakeValue();

  // Try a common delimiter form for arrays.
  ReadNoThrow(v, "1/2,3/4");

  // If the implementation treats this as an array, we can verify element access.
  if (v.count() < 2u) {
    GTEST_SKIP() << "XmpArrayValue::read did not produce >=2 elements for input '1/2,3/4'";
  }

  EXPECT_NO_THROW({
    const Exiv2::Rational r0 = v.toRational(0);
    const Exiv2::Rational r1 = v.toRational(1);
    EXPECT_EQ(r0, (Exiv2::Rational{1, 2}));
    EXPECT_EQ(r1, (Exiv2::Rational{3, 4}));
  });
  EXPECT_TRUE(v.ok());
}

TEST_F(XmpArrayValueTest_851, ToRationalOutOfBoundsThrowsOutOfRange_851) {
  auto v = MakeValue();
  ReadNoThrow(v, "1/2");

  ASSERT_GE(v.count(), 1u);

  // Boundary: exactly at count() is out of bounds.
  EXPECT_THROW((void)v.toRational(v.count()), std::out_of_range);

  // Also test a larger out-of-range index.
  EXPECT_THROW((void)v.toRational(v.count() + 10u), std::out_of_range);
}

TEST_F(XmpArrayValueTest_851, InvalidRationalInput_ResultsInNotOkOrThrows_851) {
  auto v = MakeValue();

  // Use a clearly non-rational token.
  ReadNoThrow(v, "not_a_rational");

  if (v.count() == 0u) {
    // If read produced no elements, accessing index 0 must be out-of-range.
    EXPECT_THROW((void)v.toRational(0), std::out_of_range);
    return;
  }

  // If an element exists, toRational may either throw or mark ok() false (parseRational uses ok_).
  bool threw = false;
  try {
    (void)v.toRational(0);
  } catch (...) {
    threw = true;
  }

  if (!threw) {
    EXPECT_FALSE(v.ok()) << "Expected ok() to become false after attempting to parse invalid rational";
  }
}

TEST_F(XmpArrayValueTest_851, LargeRationalDoesNotThrowAndKeepsOkWhenParsable_851) {
  auto v = MakeValue();

  // Boundary-ish: large magnitude values.
  ReadNoThrow(v, "1000000000/1");

  ASSERT_GE(v.count(), 1u);

  EXPECT_NO_THROW({
    const Exiv2::Rational r = v.toRational(0);
    EXPECT_EQ(r, (Exiv2::Rational{1000000000, 1}));
  });
  EXPECT_TRUE(v.ok());
}

}  // namespace