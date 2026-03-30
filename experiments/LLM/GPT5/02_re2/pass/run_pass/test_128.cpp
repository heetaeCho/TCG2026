// File: prog_bytemap_range_test_128.cc

#include <gtest/gtest.h>
#include "re2/prog.h"

namespace {

using re2::Prog;

// Test fixture kept minimal since we only need construction.
class ProgBytemapRangeTest_128 : public ::testing::Test {
protected:
  Prog prog_;  // Fresh instance for each test
};

// [Normal operation] A freshly constructed Prog exposes bytemap_range()
// via its public getter.
TEST_F(ProgBytemapRangeTest_128, DefaultValue_128) {
  // Observable behavior: constructor + getter.
  // We assert the initial value is 0 based on the public construction behavior.
  // (No internal state is accessed.)
  EXPECT_EQ(0, prog_.bytemap_range());
}

// [Stability/idempotence] Repeated calls to the getter should be consistent
// (getter must not mutate internal state).
TEST_F(ProgBytemapRangeTest_128, RepeatedCallsConsistent_128) {
  const int first = prog_.bytemap_range();
  const int second = prog_.bytemap_range();
  const int third = prog_.bytemap_range();
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

}  // namespace
