// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_datevalue_torational_873.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include "exiv2/value.hpp"

namespace {

// Test seam: override only the *virtual dependency* DateValue::toInt64(size_t)
// so we can observe DateValue::toRational(size_t) behavior without relying on
// Date parsing/formatting or internal state.
class TestableDateValue final : public Exiv2::DateValue {
public:
  explicit TestableDateValue(int64_t v = 0) : value_(v) {}

  void setInt64(int64_t v) { value_ = v; }

  int64_t toInt64(size_t /*n*/) override { return value_; }

private:
  int64_t value_;
};

class DateValueToRationalTest_873 : public ::testing::Test {};

TEST_F(DateValueToRationalTest_873, InRangePositive_ReturnsValueOverOne_873) {
  TestableDateValue dv(42);

  const Exiv2::Rational r = dv.toRational(0);

  EXPECT_TRUE(dv.ok());
  EXPECT_EQ(r.first, 42);
  EXPECT_EQ(r.second, 1);
}

TEST_F(DateValueToRationalTest_873, InRangeNegative_ReturnsValueOverOne_873) {
  TestableDateValue dv(-7);

  const Exiv2::Rational r = dv.toRational(0);

  EXPECT_TRUE(dv.ok());
  EXPECT_EQ(r.first, -7);
  EXPECT_EQ(r.second, 1);
}

TEST_F(DateValueToRationalTest_873, Boundary_Int32Min_ReturnsMinOverOne_873) {
  TestableDateValue dv(std::numeric_limits<int32_t>::min());

  const Exiv2::Rational r = dv.toRational(0);

  EXPECT_TRUE(dv.ok());
  EXPECT_EQ(r.first, std::numeric_limits<int32_t>::min());
  EXPECT_EQ(r.second, 1);
}

TEST_F(DateValueToRationalTest_873, Boundary_Int32Max_ReturnsMaxOverOne_873) {
  TestableDateValue dv(std::numeric_limits<int32_t>::max());

  const Exiv2::Rational r = dv.toRational(0);

  EXPECT_TRUE(dv.ok());
  EXPECT_EQ(r.first, std::numeric_limits<int32_t>::max());
  EXPECT_EQ(r.second, 1);
}

TEST_F(DateValueToRationalTest_873, BelowInt32Min_SetsOkFalseAndReturnsZeroOne_873) {
  const int64_t belowMin =
      static_cast<int64_t>(std::numeric_limits<int32_t>::min()) - 1LL;
  TestableDateValue dv(belowMin);

  const Exiv2::Rational r = dv.toRational(0);

  EXPECT_FALSE(dv.ok());
  EXPECT_EQ(r.first, 0);
  EXPECT_EQ(r.second, 1);
}

TEST_F(DateValueToRationalTest_873, AboveInt32Max_SetsOkFalseAndReturnsZeroOne_873) {
  const int64_t aboveMax =
      static_cast<int64_t>(std::numeric_limits<int32_t>::max()) + 1LL;
  TestableDateValue dv(aboveMax);

  const Exiv2::Rational r = dv.toRational(0);

  EXPECT_FALSE(dv.ok());
  EXPECT_EQ(r.first, 0);
  EXPECT_EQ(r.second, 1);
}

}  // namespace