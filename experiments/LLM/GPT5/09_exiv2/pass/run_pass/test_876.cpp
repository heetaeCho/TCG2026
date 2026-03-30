// File: test_timevalue_settime_876.cpp
// TEST_ID: 876

#include <gtest/gtest.h>

#include <cstdint>

#include "exiv2/value.hpp"

namespace {

class TimeValueTest_876 : public ::testing::Test {
 protected:
  using Time = Exiv2::TimeValue::Time;
};

TEST_F(TimeValueTest_876, SetTimeUpdatesGetTime_876) {
  Exiv2::TimeValue v;

  Time t{};
  t.hour = 12;
  t.minute = 34;
  t.second = 56;
  t.tzHour = 9;
  t.tzMinute = 0;

  v.setTime(t);

  const Time& out = v.getTime();
  EXPECT_EQ(out.hour, 12);
  EXPECT_EQ(out.minute, 34);
  EXPECT_EQ(out.second, 56);
  EXPECT_EQ(out.tzHour, 9);
  EXPECT_EQ(out.tzMinute, 0);
}

TEST_F(TimeValueTest_876, SetTimeOverwritesPreviousValue_876) {
  Exiv2::TimeValue v;

  Time t1{};
  t1.hour = 1;
  t1.minute = 2;
  t1.second = 3;
  t1.tzHour = 4;
  t1.tzMinute = 5;
  v.setTime(t1);

  Time t2{};
  t2.hour = 23;
  t2.minute = 59;
  t2.second = 58;
  t2.tzHour = -5;
  t2.tzMinute = -30;
  v.setTime(t2);

  const Time& out = v.getTime();
  EXPECT_EQ(out.hour, 23);
  EXPECT_EQ(out.minute, 59);
  EXPECT_EQ(out.second, 58);
  EXPECT_EQ(out.tzHour, -5);
  EXPECT_EQ(out.tzMinute, -30);
}

TEST_F(TimeValueTest_876, SetTimeAcceptsBoundaryInt32Values_876) {
  Exiv2::TimeValue v;

  Time t{};
  t.hour = INT32_MIN;
  t.minute = INT32_MAX;
  t.second = INT32_MIN;
  t.tzHour = INT32_MAX;
  t.tzMinute = INT32_MIN;

  v.setTime(t);

  const Time& out = v.getTime();
  EXPECT_EQ(out.hour, INT32_MIN);
  EXPECT_EQ(out.minute, INT32_MAX);
  EXPECT_EQ(out.second, INT32_MIN);
  EXPECT_EQ(out.tzHour, INT32_MAX);
  EXPECT_EQ(out.tzMinute, INT32_MIN);
}

TEST_F(TimeValueTest_876, ClonePreservesTimeAtMomentOfCloning_876) {
  Exiv2::TimeValue v;

  Time t{};
  t.hour = 10;
  t.minute = 20;
  t.second = 30;
  t.tzHour = 1;
  t.tzMinute = 45;
  v.setTime(t);

  auto cloned = v.clone();
  ASSERT_TRUE(static_cast<bool>(cloned));

  const Time& out = cloned->getTime();
  EXPECT_EQ(out.hour, 10);
  EXPECT_EQ(out.minute, 20);
  EXPECT_EQ(out.second, 30);
  EXPECT_EQ(out.tzHour, 1);
  EXPECT_EQ(out.tzMinute, 45);
}

}  // namespace