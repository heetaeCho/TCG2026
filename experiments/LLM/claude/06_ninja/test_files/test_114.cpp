#include <gtest/gtest.h>
#include <cstdint>

// Declaration from metrics.h
int64_t GetTimeMillis();

TEST(GetTimeMillisTest_114, ReturnsNonNegativeValue_114) {
  int64_t time = GetTimeMillis();
  EXPECT_GE(time, 0);
}

TEST(GetTimeMillisTest_114, ReturnsMonotonicallyNonDecreasingValues_114) {
  int64_t time1 = GetTimeMillis();
  int64_t time2 = GetTimeMillis();
  EXPECT_GE(time2, time1);
}

TEST(GetTimeMillisTest_114, ConsecutiveCallsReturnReasonableValues_114) {
  int64_t time1 = GetTimeMillis();
  // Small busy wait to ensure some time passes
  volatile int dummy = 0;
  for (int i = 0; i < 1000000; ++i) {
    dummy += i;
  }
  int64_t time2 = GetTimeMillis();
  // time2 should be >= time1 (monotonically non-decreasing)
  EXPECT_GE(time2, time1);
  // The difference should be reasonable (less than 60 seconds for a busy loop)
  EXPECT_LT(time2 - time1, 60000);
}

TEST(GetTimeMillisTest_114, ReturnValueIsInMilliseconds_114) {
  // The returned value should be in milliseconds. For any modern system,
  // the current time in millis since some epoch should be a large positive number,
  // or at least non-negative if measured from process start.
  int64_t time = GetTimeMillis();
  EXPECT_GE(time, 0);
}

TEST(GetTimeMillisTest_114, MultipleCallsWithinShortTimeAreClose_114) {
  int64_t time1 = GetTimeMillis();
  int64_t time2 = GetTimeMillis();
  int64_t time3 = GetTimeMillis();
  
  // All three calls made in quick succession should return values
  // that are very close to each other (within 1 second)
  EXPECT_LE(time3 - time1, 1000);
  EXPECT_GE(time2, time1);
  EXPECT_GE(time3, time2);
}

TEST(GetTimeMillisTest_114, ReturnTypeIs64Bit_114) {
  // Verify the return fits in int64_t (implicit by compilation, but let's
  // check it's a sensible value)
  int64_t time = GetTimeMillis();
  // Should not overflow or be a weird negative sentinel
  EXPECT_GE(time, 0);
  // Should be representable and not at the boundary of int64_t
  EXPECT_LT(time, INT64_MAX);
}
