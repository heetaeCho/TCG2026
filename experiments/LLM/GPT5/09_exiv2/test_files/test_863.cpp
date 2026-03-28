// TEST_ID 863
// Unit tests for Exiv2::DateValue::read(const std::string&)
//
// These tests treat DateValue as a black box and validate only observable behavior
// through the public interface: return codes and (for successful parses) getDate().

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include "exiv2/value.hpp"
#include "exiv2/error.hpp"

namespace {

class DateValueReadStringTest_863 : public ::testing::Test {
 protected:
  Exiv2::DateValue dv_;
};

// -------------------------
// Success cases
// -------------------------

TEST_F(DateValueReadStringTest_863, ReadCompactYYYYMMDD_Succeeds_863) {
  const int rc = dv_.read(std::string("20260206"));
  EXPECT_EQ(0, rc);

  const auto& d = dv_.getDate();
  EXPECT_EQ(2026, d.year);
  EXPECT_EQ(2, d.month);
  EXPECT_EQ(6, d.day);
}

TEST_F(DateValueReadStringTest_863, ReadDashedYYYY_MM_DD_Succeeds_863) {
  const int rc = dv_.read(std::string("2026-02-06"));
  EXPECT_EQ(0, rc);

  const auto& d = dv_.getDate();
  EXPECT_EQ(2026, d.year);
  EXPECT_EQ(2, d.month);
  EXPECT_EQ(6, d.day);
}

TEST_F(DateValueReadStringTest_863, ReadAllZerosYear_Succeeds_863) {
  const int rc = dv_.read(std::string("00000101"));
  EXPECT_EQ(0, rc);

  const auto& d = dv_.getDate();
  EXPECT_EQ(0, d.year);
  EXPECT_EQ(1, d.month);
  EXPECT_EQ(1, d.day);
}

// -------------------------
// Error / exceptional cases
// -------------------------

TEST_F(DateValueReadStringTest_863, TooShortString_Fails_863) {
  EXPECT_EQ(1, dv_.read(std::string("2026020")));  // 7 chars
  EXPECT_EQ(1, dv_.read(std::string("")));         // empty
}

TEST_F(DateValueReadStringTest_863, WrongSeparatorFormat_Fails_863) {
  EXPECT_EQ(1, dv_.read(std::string("2026/02/06")));
  EXPECT_EQ(1, dv_.read(std::string("2026.02.06")));
}

TEST_F(DateValueReadStringTest_863, NonDigitInYear_Fails_863) {
  EXPECT_EQ(1, dv_.read(std::string("20A6-02-06")));
  EXPECT_EQ(1, dv_.read(std::string("20A60206")));
}

TEST_F(DateValueReadStringTest_863, NonDigitInMonth_Fails_863) {
  EXPECT_EQ(1, dv_.read(std::string("2026-0A-06")));
  EXPECT_EQ(1, dv_.read(std::string("20260A06")));
}

TEST_F(DateValueReadStringTest_863, NonDigitInDay_Fails_863) {
  EXPECT_EQ(1, dv_.read(std::string("2026-02-0A")));
  EXPECT_EQ(1, dv_.read(std::string("2026020A")));
}

TEST_F(DateValueReadStringTest_863, MonthOutOfRange_Fails_863) {
  EXPECT_EQ(1, dv_.read(std::string("2026-13-01")));
  EXPECT_EQ(1, dv_.read(std::string("20261301")));
}

TEST_F(DateValueReadStringTest_863, DayOutOfRange_Fails_863) {
  EXPECT_EQ(1, dv_.read(std::string("2026-12-32")));
  EXPECT_EQ(1, dv_.read(std::string("20261232")));
}

// -------------------------
// External interaction (logging) - best effort
// -------------------------
//
// DateValue::read may emit a warning via Exiv2 logging when encountering unsupported formats.
// If warnings are suppressed at build time, this is not observable and the test is skipped.

#ifndef SUPPRESS_WARNINGS
namespace {
static int g_log_calls_863 = 0;

static void CountingLogHandler_863(int /*level*/, const char* /*s*/) {
  ++g_log_calls_863;
}
}  // namespace

TEST_F(DateValueReadStringTest_863, EmitsWarningOnInvalidInput_863) {
  g_log_calls_863 = 0;

  // Best-effort: use Exiv2's logging hook if available in this build.
  // Handler signature is expected to match Exiv2::LogMsg::Handler.
  Exiv2::LogMsg::setHandler(&CountingLogHandler_863);
  Exiv2::LogMsg::setLevel(Exiv2::LogMsg::warn);

  EXPECT_EQ(1, dv_.read(std::string("bad-date")));

  // At least one warning should be emitted for invalid input, if logging is active.
  EXPECT_GE(g_log_calls_863, 1);
}
#else
TEST_F(DateValueReadStringTest_863, WarningEmissionNotObservableWhenSuppressed_863) {
  GTEST_SKIP() << "SUPPRESS_WARNINGS is defined; warning emission is not observable.";
}
#endif

}  // namespace