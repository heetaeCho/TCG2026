// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

namespace {

using Exiv2::TimeValue;

class TimeValueTest_880 : public ::testing::Test {};

TEST_F(TimeValueTest_880, DefaultConstructedSizeIs11_880) {
  const TimeValue v;
  EXPECT_EQ(11u, v.size());
}

TEST_F(TimeValueTest_880, ParameterConstructedSizeIs11_880) {
  // Use a representative valid-looking time + timezone offset.
  const TimeValue v(/*hour*/ 12, /*minute*/ 34, /*second*/ 56, /*tzHour*/ 9, /*tzMinute*/ 0);
  EXPECT_EQ(11u, v.size());
}

TEST_F(TimeValueTest_880, SizeIsStableAcrossCalls_880) {
  const TimeValue v;
  const auto s1 = v.size();
  const auto s2 = v.size();
  const auto s3 = v.size();
  EXPECT_EQ(s1, s2);
  EXPECT_EQ(s2, s3);
  EXPECT_EQ(11u, s1);
}

TEST_F(TimeValueTest_880, SizeWorksViaConstReference_880) {
  TimeValue v;
  const TimeValue& cv = v;
  EXPECT_EQ(11u, cv.size());
}

}  // namespace