// File: test_timevalue_read_string_875.cpp
#include <gtest/gtest.h>

#include <atomic>
#include <cstdint>
#include <cstring>
#include <string>

#include <exiv2/value.hpp>
#include <exiv2/error.hpp>

namespace {

// Best-effort log capture for “external interaction” verification.
// In Exiv2, LogMsg::setHandler typically accepts a function pointer like:
//   void handler(int level, const char* msg);
std::atomic<int> g_lastLogLevel{-1};
std::string g_lastLogMsg;

void TestLogHandler(int level, const char* s) {
  g_lastLogLevel.store(level);
  g_lastLogMsg = (s ? s : "");
}

void ResetLogCapture() {
  g_lastLogLevel.store(-1);
  g_lastLogMsg.clear();
}

class TimeValueTest_875 : public ::testing::Test {
 protected:
  void SetUp() override {
    ResetLogCapture();
#ifndef SUPPRESS_WARNINGS
    // If Exiv2 routes warnings through LogMsg, capture them.
    // If the build suppresses warnings, we still run all return-value assertions.
    Exiv2::LogMsg::setHandler(&TestLogHandler);
    Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);
#endif
  }

  void TearDown() override {
    ResetLogCapture();
  }

  static void ExpectNoWarningIfEnabled() {
#ifndef SUPPRESS_WARNINGS
    EXPECT_EQ(g_lastLogLevel.load(), -1);
    EXPECT_TRUE(g_lastLogMsg.empty());
#endif
  }

  static void ExpectWarningIfEnabled() {
#ifndef SUPPRESS_WARNINGS
    EXPECT_NE(g_lastLogLevel.load(), -1);
#endif
  }
};

}  // namespace

TEST_F(TimeValueTest_875, ReadRejectsTooShortString_875) {
  Exiv2::TimeValue v;
  const int rc = v.read(std::string{""});
  EXPECT_NE(rc, 0);
  ExpectWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadRejectsNonDigitNonAllowedCharacters_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("1a");
  EXPECT_NE(rc, 0);
  ExpectWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadParsesHourOnlyDefaultsMinuteSecondAndTimezone_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("09");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 9);
  EXPECT_EQ(t.minute, 0);
  EXPECT_EQ(t.second, 0);
  EXPECT_EQ(t.tzHour, 0);
  EXPECT_EQ(t.tzMinute, 0);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadAcceptsZuluSuffixWithoutTimezoneParsing_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12Z");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 12);
  EXPECT_EQ(t.minute, 0);
  EXPECT_EQ(t.second, 0);
  EXPECT_EQ(t.tzHour, 0);
  EXPECT_EQ(t.tzMinute, 0);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadParsesHHMMWithoutColons_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("1234");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 12);
  EXPECT_EQ(t.minute, 34);
  EXPECT_EQ(t.second, 0);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadParsesHHMMWithColon_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:34");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 12);
  EXPECT_EQ(t.minute, 34);
  EXPECT_EQ(t.second, 0);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadParsesHHMMSSWithoutColons_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("123456");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 12);
  EXPECT_EQ(t.minute, 34);
  EXPECT_EQ(t.second, 56);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadParsesHHMMSSWithColons_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:34:56");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 12);
  EXPECT_EQ(t.minute, 34);
  EXPECT_EQ(t.second, 56);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadAcceptsSecond60Boundary_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:34:60");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 12);
  EXPECT_EQ(t.minute, 34);
  EXPECT_EQ(t.second, 60);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadRejectsHourOutOfRangeLow_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("-1");
  EXPECT_NE(rc, 0);
  ExpectWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadRejectsHourOutOfRangeHigh_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("24");
  EXPECT_NE(rc, 0);
  ExpectWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadRejectsMinuteOutOfRange_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:60");
  EXPECT_NE(rc, 0);
  ExpectWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadRejectsSecondOutOfRange_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:34:61");
  EXPECT_NE(rc, 0);
  ExpectWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadParsesTimezoneWithoutColon_Positive_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:34+0530");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 12);
  EXPECT_EQ(t.minute, 34);
  EXPECT_EQ(t.tzHour, 5);
  EXPECT_EQ(t.tzMinute, 30);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadParsesTimezoneWithColon_Negative_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:34-05:30");
  EXPECT_EQ(rc, 0);

  const auto& t = v.getTime();
  EXPECT_EQ(t.hour, 12);
  EXPECT_EQ(t.minute, 34);
  EXPECT_EQ(t.tzHour, -5);
  EXPECT_EQ(t.tzMinute, -30);

  ExpectNoWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadRejectsTimezoneHourOutOfRange_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:00+2400");
  EXPECT_NE(rc, 0);
  ExpectWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadRejectsTimezoneMinuteOutOfRange_875) {
  Exiv2::TimeValue v;
  const int rc = v.read("12:00+2360");
  EXPECT_NE(rc, 0);
  ExpectWarningIfEnabled();
}

TEST_F(TimeValueTest_875, ReadThrowsOnDanglingPlusTimezoneMarker_875) {
  Exiv2::TimeValue v;
  EXPECT_ANY_THROW((void)v.read("12+"));
}

TEST_F(TimeValueTest_875, ReadThrowsOnDanglingMinusTimezoneMarker_875) {
  Exiv2::TimeValue v;
  EXPECT_ANY_THROW((void)v.read("12-"));
}

TEST_F(TimeValueTest_875, ReadThrowsWhenSecondsExpectedButMissingDueToTrailingTimezoneMarker_875) {
  Exiv2::TimeValue v;
  // With this shape, the interface may throw due to malformed input.
  EXPECT_ANY_THROW((void)v.read("12:00+"));
}