// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_toRational_762.cpp

#include <gtest/gtest.h>

#include <limits>
#include <memory>

#include "exiv2/exif.hpp"
#include "exiv2/value.hpp"

namespace {

class TrackingValue : public Exiv2::Value {
 public:
  explicit TrackingValue(const Exiv2::Rational& ret)
      : Exiv2::Value(Exiv2::invalidTypeId), ret_(ret) {}

  TrackingValue(const TrackingValue& rhs) = default;
  ~TrackingValue() override = default;

  Exiv2::Rational toRational(size_t n) const override {
    ++call_count_;
    last_n_ = n;
    return ret_;
  }

  int callCount() const { return call_count_; }
  size_t lastN() const { return last_n_; }

 private:
  // Exiv2::Value::clone() uses the private virtual clone_(). If Exifdatum clones
  // the incoming Value, we must preserve the dynamic type to keep our override.
  const Exiv2::Value* clone_() override { return new TrackingValue(*this); }

  Exiv2::Rational ret_;
  mutable int call_count_{0};
  mutable size_t last_n_{0};
};

static void ExpectRationalEq(const Exiv2::Rational& r, long num, long den) {
  // In Exiv2, Rational is typically a std::pair (num, den).
  EXPECT_EQ(r.first, num);
  EXPECT_EQ(r.second, den);
}

class ExifdatumToRationalTest_762 : public ::testing::Test {
 protected:
  // Use a commonly valid Exif key string; tests do not depend on tag semantics.
  Exiv2::ExifKey key_{"Exif.Image.Make"};
};

}  // namespace

TEST_F(ExifdatumToRationalTest_762, NullValueReturnsMinusOne_762) {
  Exiv2::Exifdatum datum(key_, nullptr);

  const Exiv2::Rational r0 = datum.toRational(0);
  ExpectRationalEq(r0, -1, 1);

  const Exiv2::Rational r123 = datum.toRational(123);
  ExpectRationalEq(r123, -1, 1);
}

TEST_F(ExifdatumToRationalTest_762, NonNullValueIsForwardedAndReturnPropagates_762) {
  const Exiv2::Rational expected{3, 4};
  TrackingValue v(expected);

  Exiv2::Exifdatum datum(key_, &v);

  const Exiv2::Rational out = datum.toRational(5);
  ExpectRationalEq(out, expected.first, expected.second);

  // Verify the external collaborator (Value) was called with the same index.
  EXPECT_EQ(v.callCount(), 1);
  EXPECT_EQ(v.lastN(), 5u);
}

TEST_F(ExifdatumToRationalTest_762, MultipleCallsForwardEachIndex_762) {
  const Exiv2::Rational expected{7, 9};
  TrackingValue v(expected);

  Exiv2::Exifdatum datum(key_, &v);

  (void)datum.toRational(0);
  EXPECT_EQ(v.callCount(), 1);
  EXPECT_EQ(v.lastN(), 0u);

  (void)datum.toRational(1);
  EXPECT_EQ(v.callCount(), 2);
  EXPECT_EQ(v.lastN(), 1u);
}

TEST_F(ExifdatumToRationalTest_762, BoundaryMaxIndexIsForwarded_762) {
  const Exiv2::Rational expected{11, 13};
  TrackingValue v(expected);

  Exiv2::Exifdatum datum(key_, &v);

  const size_t n = std::numeric_limits<size_t>::max();
  const Exiv2::Rational out = datum.toRational(n);

  ExpectRationalEq(out, expected.first, expected.second);
  EXPECT_EQ(v.callCount(), 1);
  EXPECT_EQ(v.lastN(), n);
}