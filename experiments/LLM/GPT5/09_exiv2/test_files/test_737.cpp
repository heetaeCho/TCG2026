// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_operator_assign_rational_737.cpp

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>

namespace {

// TEST_ID = 737
class ExifdatumTest_737 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // Pick a stable, well-known Exif key string.
    return Exiv2::ExifKey("Exif.Photo.FocalLength");
  }

  static Exiv2::Exifdatum MakeDatum() {
    Exiv2::ExifKey key = MakeKey();
    // Constructor takes (key, Value*). Passing nullptr is part of the public API surface.
    return Exiv2::Exifdatum(key, /*pValue=*/nullptr);
  }
};

TEST_F(ExifdatumTest_737, AssignRationalReturnsSelfReference_737) {
  Exiv2::Exifdatum d = MakeDatum();

  Exiv2::Rational r(1, 2);
  Exiv2::Exifdatum& ret = (d = r);

  EXPECT_EQ(&ret, &d);
}

TEST_F(ExifdatumTest_737, AssignRationalSetsValueObservableViaToRational_737) {
  Exiv2::Exifdatum d = MakeDatum();

  const Exiv2::Rational r(3, 4);
  d = r;

  // Observable behavior via public API.
  EXPECT_GE(d.count(), 1u);
  EXPECT_EQ(d.toRational(0).first, r.first);
  EXPECT_EQ(d.toRational(0).second, r.second);
}

TEST_F(ExifdatumTest_737, AssignRationalOverwritesPreviousValue_737) {
  Exiv2::Exifdatum d = MakeDatum();

  const Exiv2::Rational r1(5, 6);
  const Exiv2::Rational r2(7, 8);

  d = r1;
  EXPECT_EQ(d.toRational(0).first, r1.first);
  EXPECT_EQ(d.toRational(0).second, r1.second);

  d = r2;
  EXPECT_EQ(d.toRational(0).first, r2.first);
  EXPECT_EQ(d.toRational(0).second, r2.second);
}

TEST_F(ExifdatumTest_737, AssignRationalAllowsChainingAndKeepsFinalValue_737) {
  Exiv2::Exifdatum d = MakeDatum();

  const Exiv2::Rational r1(9, 10);
  const Exiv2::Rational r2(11, 12);

  (d = r1) = r2;  // chaining relies only on operator= return type

  EXPECT_EQ(d.toRational(0).first, r2.first);
  EXPECT_EQ(d.toRational(0).second, r2.second);
}

TEST_F(ExifdatumTest_737, AssignRationalHandlesNegativeNumeratorBoundary_737) {
  Exiv2::Exifdatum d = MakeDatum();

  const Exiv2::Rational r(-1, 3);
  d = r;

  EXPECT_EQ(d.toRational(0).first, r.first);
  EXPECT_EQ(d.toRational(0).second, r.second);
}

TEST_F(ExifdatumTest_737, AssignRationalHandlesLargeMagnitudeBoundary_737) {
  Exiv2::Exifdatum d = MakeDatum();

  // Use large (but safe) 32-bit values, since Exiv2::Rational is typically a pair of int32_t.
  const Exiv2::Rational r(2147483000, 2147482999);
  d = r;

  EXPECT_EQ(d.toRational(0).first, r.first);
  EXPECT_EQ(d.toRational(0).second, r.second);
}

TEST_F(ExifdatumTest_737, ToRationalOutOfRangeIndexIsObservableError_737) {
  Exiv2::Exifdatum d = MakeDatum();

  d = Exiv2::Rational(1, 2);

  // If the datum holds a single rational value, requesting the next index should be an error.
  // We only assert that *some* exception is raised (implementation-defined).
  EXPECT_ANY_THROW((void)d.toRational(1));
}

}  // namespace