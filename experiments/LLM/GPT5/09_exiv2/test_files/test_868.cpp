// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_datevalue_size_868.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>

#include "exiv2/value.hpp"

namespace {

class DateValueTest_868 : public ::testing::Test {};

TEST_F(DateValueTest_868, Size_DefaultConstructed_IsEight_868) {
  const Exiv2::DateValue v;
  EXPECT_EQ(static_cast<size_t>(8), v.size());
}

TEST_F(DateValueTest_868, Size_DateConstructed_IsEight_868) {
  const Exiv2::DateValue v(2026, 2, 6);
  EXPECT_EQ(static_cast<size_t>(8), v.size());
}

TEST_F(DateValueTest_868, Size_MultipleInstances_AllReturnEight_868) {
  const Exiv2::DateValue a;
  const Exiv2::DateValue b(1970, 1, 1);
  const Exiv2::DateValue c(9999, 12, 31);

  EXPECT_EQ(static_cast<size_t>(8), a.size());
  EXPECT_EQ(static_cast<size_t>(8), b.size());
  EXPECT_EQ(static_cast<size_t>(8), c.size());
}

TEST_F(DateValueTest_868, Size_CanBeCalledThroughConstReference_868) {
  const Exiv2::DateValue v(2000, 2, 29);
  const Exiv2::DateValue& ref = v;

  EXPECT_EQ(static_cast<size_t>(8), ref.size());
}

TEST_F(DateValueTest_868, Size_ReturnTypeIsSizeT_868) {
  const Exiv2::DateValue v;
  const size_t s = v.size();
  EXPECT_EQ(static_cast<size_t>(8), s);
}

}  // namespace