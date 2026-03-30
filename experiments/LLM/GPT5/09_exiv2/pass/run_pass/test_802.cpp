// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_datavalue_toRational_802.cpp

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstddef>
#include <stdexcept>

namespace {

class DataValueTest_802 : public ::testing::Test {
 protected:
  // Pick a concrete, commonly-available Exiv2 TypeId.
  // The specific type is not important for these black-box tests of toRational().
  static constexpr Exiv2::TypeId kTypeId = Exiv2::unsignedLong;
};

TEST_F(DataValueTest_802, ToRationalReturnsNumeratorAndDenominatorOne_802) {
  Exiv2::DataValue dv(kTypeId);

  dv.value_.push_back(42);

  const Exiv2::Rational r = dv.toRational(0);

  EXPECT_EQ(r.first, 42);
  EXPECT_EQ(r.second, 1);
  EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToRationalReadsCorrectElementForNonZeroIndex_802) {
  Exiv2::DataValue dv(kTypeId);

  dv.value_.push_back(10);
  dv.value_.push_back(20);
  dv.value_.push_back(30);

  const Exiv2::Rational r = dv.toRational(2);

  EXPECT_EQ(r.first, 30);
  EXPECT_EQ(r.second, 1);
  EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToRationalOnLastValidIndexWorks_802) {
  Exiv2::DataValue dv(kTypeId);

  dv.value_.push_back(7);
  dv.value_.push_back(8);

  const Exiv2::Rational r = dv.toRational(dv.value_.size() - 1);

  EXPECT_EQ(r.first, 8);
  EXPECT_EQ(r.second, 1);
  EXPECT_TRUE(dv.ok());
}

TEST_F(DataValueTest_802, ToRationalThrowsOutOfRangeWhenIndexTooLarge_802) {
  Exiv2::DataValue dv(kTypeId);

  dv.value_.push_back(1);

  EXPECT_THROW((void)dv.toRational(1), std::out_of_range);
}

TEST_F(DataValueTest_802, ToRationalThrowsOutOfRangeWhenEmpty_802) {
  Exiv2::DataValue dv(kTypeId);

  EXPECT_THROW((void)dv.toRational(0), std::out_of_range);
}

}  // namespace