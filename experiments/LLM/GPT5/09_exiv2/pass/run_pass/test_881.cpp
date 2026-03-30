// File: test_timevalue_write_881.cpp
// TEST_ID: 881

#include <gtest/gtest.h>

#include <cstdint>
#include <sstream>
#include <string>

#include "exiv2/value.hpp"

namespace {

using Exiv2::TimeValue;

class TimeValueTest_881 : public ::testing::Test {};

TEST_F(TimeValueTest_881, WriteFormatsPositiveTimezone_881) {
  const TimeValue tv(/*hour=*/1, /*minute=*/2, /*second=*/3, /*tzHour=*/9, /*tzMinute=*/30);

  std::ostringstream oss;
  std::ostream& ret = tv.write(oss);

  EXPECT_EQ(&ret, static_cast<std::ostream*>(&oss));
  EXPECT_EQ(oss.str(), "01:02:03+09:30");
}

TEST_F(TimeValueTest_881, WriteFormatsZeroTimezone_881) {
  const TimeValue tv(/*hour=*/0, /*minute=*/0, /*second=*/0, /*tzHour=*/0, /*tzMinute=*/0);

  std::ostringstream oss;
  tv.write(oss);

  EXPECT_EQ(oss.str(), "00:00:00+00:00");
}

TEST_F(TimeValueTest_881, WriteUsesMinusWhenTzHourNegative_881) {
  const TimeValue tv(/*hour=*/12, /*minute=*/34, /*second=*/56, /*tzHour=*/-5, /*tzMinute=*/0);

  std::ostringstream oss;
  tv.write(oss);

  EXPECT_EQ(oss.str(), "12:34:56-05:00");
}

TEST_F(TimeValueTest_881, WriteUsesMinusWhenTzMinuteNegative_881) {
  const TimeValue tv(/*hour=*/7, /*minute=*/8, /*second=*/9, /*tzHour=*/0, /*tzMinute=*/-45);

  std::ostringstream oss;
  tv.write(oss);

  EXPECT_EQ(oss.str(), "07:08:09-00:45");
}

TEST_F(TimeValueTest_881, WriteUsesMinusAndAbsoluteValuesWhenBothNegative_881) {
  const TimeValue tv(/*hour=*/23, /*minute=*/59, /*second=*/58, /*tzHour=*/-9, /*tzMinute=*/-30);

  std::ostringstream oss;
  tv.write(oss);

  EXPECT_EQ(oss.str(), "23:59:58-09:30");
}

TEST_F(TimeValueTest_881, WriteUsesMinusWhenTzHourNegativeEvenIfTzMinutePositive_881) {
  const TimeValue tv(/*hour=*/10, /*minute=*/11, /*second=*/12, /*tzHour=*/-1, /*tzMinute=*/15);

  std::ostringstream oss;
  tv.write(oss);

  EXPECT_EQ(oss.str(), "10:11:12-01:15");
}

TEST_F(TimeValueTest_881, SetTimeAffectsWriteOutput_881) {
  TimeValue tv;  // default construct, then setTime

  TimeValue::Time t{};
  t.hour = 3;
  t.minute = 4;
  t.second = 5;
  t.tzHour = 2;
  t.tzMinute = 0;

  tv.setTime(t);

  std::ostringstream oss;
  tv.write(oss);

  EXPECT_EQ(oss.str(), "03:04:05+02:00");
}

TEST_F(TimeValueTest_881, WriteDoesNotThrowForRepresentativeValues_881) {
  const TimeValue tv(/*hour=*/99, /*minute=*/99, /*second=*/99, /*tzHour=*/-12, /*tzMinute=*/-59);

  std::ostringstream oss;
  EXPECT_NO_THROW(tv.write(oss));
}

}  // namespace