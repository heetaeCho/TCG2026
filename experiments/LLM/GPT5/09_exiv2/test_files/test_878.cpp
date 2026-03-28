// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 878
//
// Unit tests for Exiv2::TimeValue::getTime() const
// Constraints: treat implementation as a black box; test only observable behavior.

#include <gtest/gtest.h>

#include <type_traits>

#include "value.hpp"  // Exiv2::TimeValue

namespace {

class TimeValueTest_878 : public ::testing::Test {};

TEST_F(TimeValueTest_878, GetTimeReturnTypeIsConstReference_878) {
  using Exiv2::TimeValue;

  // Compile-time checks only: no assumptions about internal logic.
  static_assert(std::is_reference_v<decltype(std::declval<const TimeValue&>().getTime())>,
                "getTime() must return a reference");
  static_assert(std::is_const_v<std::remove_reference_t<decltype(std::declval<const TimeValue&>().getTime())>>,
                "getTime() must return a const reference");
}

TEST_F(TimeValueTest_878, GetTimeIsStableReferenceAcrossCalls_878) {
  Exiv2::TimeValue tv;

  const auto& t1 = tv.getTime();
  const auto& t2 = tv.getTime();

  // Observable behavior: returned reference should refer to the same subobject each call.
  EXPECT_EQ(&t1, &t2);
}

TEST_F(TimeValueTest_878, GetTimeReferenceDiffersBetweenDifferentInstances_878) {
  Exiv2::TimeValue a;
  Exiv2::TimeValue b;

  // Each instance should expose its own Time subobject; references should not alias across instances.
  EXPECT_NE(&a.getTime(), &b.getTime());
}

TEST_F(TimeValueTest_878, SetTimeDoesNotCauseAliasingWithSourceInstance_878) {
  Exiv2::TimeValue src;
  Exiv2::TimeValue dst;

  // Avoid constructing Time directly (unknown); use a value obtained through the public interface.
  dst.setTime(src.getTime());

  // Observable: dst's time reference should still belong to dst (not alias src's internal subobject).
  EXPECT_NE(&dst.getTime(), &src.getTime());

  // And it should be stable across repeated calls.
  const auto& d1 = dst.getTime();
  const auto& d2 = dst.getTime();
  EXPECT_EQ(&d1, &d2);
}

TEST_F(TimeValueTest_878, CloneProducesIndependentObjectWithValidGetTime_878) {
  Exiv2::TimeValue original;

  auto cloned = original.clone();
  ASSERT_TRUE(static_cast<bool>(cloned));

  // Should be safe to call getTime() on the clone.
  const auto& ct = cloned->getTime();
  (void)ct;

  // The clone is a different object; its Time subobject reference should not alias the original's.
  EXPECT_NE(&cloned->getTime(), &original.getTime());

  // Reference stability on the clone as well.
  const auto& c1 = cloned->getTime();
  const auto& c2 = cloned->getTime();
  EXPECT_EQ(&c1, &c2);
}

}  // namespace