// File: test_datevalue_toint64_870.cpp
//
// Unit tests for Exiv2::DateValue::toInt64(size_t)
// Constraints: treat implementation as black box; test only via public interface / observable behavior.

#include <gtest/gtest.h>

#include <ctime>
#include <cstdint>
#include <limits>
#include <string>

#include <exiv2/value.hpp>
#include <exiv2/error.hpp>

namespace {

// Compute the same kind of epoch-seconds value that std::mktime would produce for a local-midnight date.
// (Used only to form an expected value through standard library behavior.)
int64_t MktimeLocalMidnight(int year, int month, int day) {
  std::tm tms{};
  tms.tm_year = year - 1900;
  tms.tm_mon = month - 1;
  tms.tm_mday = day;
  const std::time_t tt = std::mktime(&tms);
  return static_cast<int64_t>(tt);
}

// Helper to create a date-like Value and populate it via read().
// We intentionally go through the public Value factory to avoid relying on DateValue constructors.
Exiv2::Value::UniquePtr MakeDateValueViaFactoryAndRead(const std::string& s) {
  // Exiv2 type id names can vary slightly across versions; "date" is the canonical one in Exiv2.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::date);
  EXPECT_TRUE(v.get() != nullptr);
  // read() may throw Exiv2::Error for malformed strings in some versions/configs.
  v->read(s);
  return v;
}

}  // namespace

class DateValueTest_870 : public ::testing::Test {};

TEST_F(DateValueTest_870, ToInt64_IgnoresIndexParameter_870) {
  auto v = MakeDateValueViaFactoryAndRead("2000:01:02");

  const int64_t a = v->toInt64(0);
  const int64_t b = v->toInt64(1);
  const int64_t c = v->toInt64(std::numeric_limits<size_t>::max());

  EXPECT_EQ(a, b);
  EXPECT_EQ(a, c);
}

TEST_F(DateValueTest_870, ToInt64_StableAcrossRepeatedCalls_870) {
  auto v = MakeDateValueViaFactoryAndRead("2010:12:31");

  const int64_t first = v->toInt64(0);
  const int64_t second = v->toInt64(0);
  const int64_t third = v->toInt64(0);

  EXPECT_EQ(first, second);
  EXPECT_EQ(first, third);
}

TEST_F(DateValueTest_870, ToInt64_MatchesStdMktimeForTypicalDate_870) {
  auto v = MakeDateValueViaFactoryAndRead("2020:01:15");

  const int64_t expected = MktimeLocalMidnight(2020, 1, 15);
  const int64_t actual = v->toInt64(0);

  // If the platform cannot represent the time, std::mktime returns -1; in that case,
  // the observable expectation is that the function also reports failure as -1.
  if (expected == -1) {
    EXPECT_EQ(actual, -1);
  } else {
    EXPECT_EQ(actual, expected);
  }
}

TEST_F(DateValueTest_870, ToInt64_HandlesLeapDay_870) {
  auto v = MakeDateValueViaFactoryAndRead("2000:02:29");

  const int64_t expected = MktimeLocalMidnight(2000, 2, 29);
  const int64_t actual = v->toInt64(0);

  if (expected == -1) {
    EXPECT_EQ(actual, -1);
  } else {
    EXPECT_EQ(actual, expected);
  }
}

TEST_F(DateValueTest_870, ToInt64_MalformedReadThrowsOrResultsInNonCrash_870) {
  // Exceptional/error case (observable): read() may throw for malformed input.
  // If it does not throw (implementation-dependent), calling toInt64 should still be safe.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::date);
  ASSERT_TRUE(v.get() != nullptr);

  bool threw = false;
  try {
    v->read("not-a-date");
  } catch (const Exiv2::Error&) {
    threw = true;
  }

  if (!threw) {
    // Observable safety: should not crash; value should be deterministic across calls.
    const int64_t a = v->toInt64(0);
    const int64_t b = v->toInt64(0);
    EXPECT_EQ(a, b);
  } else {
    SUCCEED();
  }
}