// File: test_timevalue_2174.cpp
// TEST_ID: 2174

#include <gtest/gtest.h>

#include <exiv2/value.hpp>
#include <sstream>
#include <string>
#include <vector>

namespace {

using Exiv2::ByteOrder;
using Exiv2::TimeValue;

// Some Exiv2 builds expose byte as Exiv2::byte; keep it simple and compatible.
using ByteVec = std::vector<Exiv2::byte>;

class TimeValueTest_2174 : public ::testing::Test {};

static void ExpectTimeEq2174(const TimeValue::Time& t,
                            int32_t hour,
                            int32_t minute,
                            int32_t second,
                            int32_t tzHour,
                            int32_t tzMinute) {
  EXPECT_EQ(t.hour, hour);
  EXPECT_EQ(t.minute, minute);
  EXPECT_EQ(t.second, second);
  EXPECT_EQ(t.tzHour, tzHour);
  EXPECT_EQ(t.tzMinute, tzMinute);
}

TEST_F(TimeValueTest_2174, ParamCtorStoresGivenTime_2174) {
  const int32_t h = 12, m = 34, s = 56, tzh = 9, tzm = 0;
  TimeValue tv(h, m, s, tzh, tzm);

  const TimeValue::Time& got = tv.getTime();
  ExpectTimeEq2174(got, h, m, s, tzh, tzm);
}

TEST_F(TimeValueTest_2174, SetTimeUpdatesGetTime_2174) {
  TimeValue tv(1, 2, 3, 0, 0);

  TimeValue::Time src{};
  src.hour = 23;
  src.minute = 59;
  src.second = 58;
  src.tzHour = -5;
  src.tzMinute = 30;

  tv.setTime(src);

  const TimeValue::Time& got = tv.getTime();
  ExpectTimeEq2174(got, 23, 59, 58, -5, 30);
}

TEST_F(TimeValueTest_2174, CloneProducesIndependentCopyWithSameTime_2174) {
  TimeValue tv(7, 8, 9, 1, 15);

  Exiv2::Value::UniquePtr clonedBase = tv.clone();
  ASSERT_NE(clonedBase.get(), nullptr);

  auto* cloned = dynamic_cast<TimeValue*>(clonedBase.get());
  ASSERT_NE(cloned, nullptr);

  // Should carry over observable state.
  const TimeValue::Time& t1 = tv.getTime();
  const TimeValue::Time& t2 = cloned->getTime();
  ExpectTimeEq2174(t2, t1.hour, t1.minute, t1.second, t1.tzHour, t1.tzMinute);

  // Mutating original should not affect clone (independence).
  TimeValue::Time src{};
  src.hour = 10;
  src.minute = 20;
  src.second = 30;
  src.tzHour = 0;
  src.tzMinute = 0;
  tv.setTime(src);

  const TimeValue::Time& t2_after = cloned->getTime();
  ExpectTimeEq2174(t2_after, t2.hour, t2.minute, t2.second, t2.tzHour, t2.tzMinute);
}

TEST_F(TimeValueTest_2174, SizeAndCopyAreSelfConsistent_2174) {
  TimeValue tv(4, 5, 6, 2, 0);

  const size_t sz = tv.size();
  EXPECT_GT(sz, 0u);

  const TimeValue::Time before = tv.getTime();

  ByteVec buf(sz);
  const size_t copied = tv.copy(buf.data(), Exiv2::littleEndian);

  // Black-box friendly consistency checks:
  EXPECT_LE(copied, sz);
  EXPECT_GT(copied, 0u);

  const TimeValue::Time after = tv.getTime();
  ExpectTimeEq2174(after, before.hour, before.minute, before.second, before.tzHour, before.tzMinute);
}

TEST_F(TimeValueTest_2174, CountIsNonZeroAndStable_2174) {
  TimeValue tv(0, 0, 0, 0, 0);

  const size_t c1 = tv.count();
  const size_t c2 = tv.count();

  EXPECT_GE(c1, 1u);
  EXPECT_EQ(c1, c2);
}

TEST_F(TimeValueTest_2174, WriteProducesSomeOutput_2174) {
  TimeValue tv(11, 22, 33, 9, 0);

  std::ostringstream oss;
  tv.write(oss);

  // Avoid assuming formatting; just require that something is written.
  EXPECT_FALSE(oss.str().empty());
}

TEST_F(TimeValueTest_2174, ReadFromStringMalformedIndicatesFailureOrNotOk_2174) {
  TimeValue tv(1, 1, 1, 0, 0);

  const int rc = tv.read(std::string("not-a-time"));
  // Observable error handling: either return code signals failure, or ok() flips false.
  EXPECT_TRUE(rc != 0 || !tv.ok());
}

TEST_F(TimeValueTest_2174, ReadFromStringEmptyBoundaryIndicatesFailureOrNotOk_2174) {
  TimeValue tv(1, 1, 1, 0, 0);

  const int rc = tv.read(std::string());
  EXPECT_TRUE(rc != 0 || !tv.ok());
}

TEST_F(TimeValueTest_2174, ReadFromBufferTooShortBoundaryIndicatesFailureOrNotOk_2174) {
  TimeValue tv(1, 2, 3, 0, 0);

  // Provide a clearly undersized buffer; do not assume required size/format.
  ByteVec tiny(1, static_cast<Exiv2::byte>(0));
  const int rc = tv.read(tiny.data(), tiny.size(), Exiv2::littleEndian);

  EXPECT_TRUE(rc != 0 || !tv.ok());
}

TEST_F(TimeValueTest_2174, ReadFromStringIfSucceedsThenGetTimeIsUsable_2174) {
  TimeValue tv(0, 0, 0, 0, 0);

  // Use a plausible time string; do not assert exact parsing rules.
  const std::string candidate = "12:34:56+09:00";
  const int rc = tv.read(candidate);

  if (rc == 0 && tv.ok()) {
    // Only assert that getTime is accessible and values are in typical ranges.
    // (Avoid enforcing format-specific behavior.)
    const TimeValue::Time& t = tv.getTime();
    EXPECT_GE(t.hour, 0);
    EXPECT_LE(t.hour, 23);
    EXPECT_GE(t.minute, 0);
    EXPECT_LE(t.minute, 59);
    EXPECT_GE(t.second, 0);
    EXPECT_LE(t.second, 60);  // allow leap second
    EXPECT_GE(t.tzMinute, -59);
    EXPECT_LE(t.tzMinute, 59);
  }
}

}  // namespace