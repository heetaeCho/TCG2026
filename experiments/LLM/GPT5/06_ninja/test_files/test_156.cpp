// File: get_processor_count_test_156.cc

#include "gtest/gtest.h"

#include "util.h"  // Declares GetProcessorCount

#if !defined(_WIN32)
#include <unistd.h>  // sysconf
#endif

// Basic test suite name includes TEST_ID as requested.
TEST(GetProcessorCountTest_156, ReturnsPositiveValue_156) {
  int count = GetProcessorCount();
  // We expect at least one logical processor to be reported.
  EXPECT_GE(count, 1);
}

TEST(GetProcessorCountTest_156, ReturnsConsistentValueAcrossCalls_156) {
  int first = GetProcessorCount();
  int second = GetProcessorCount();

  // Under normal circumstances (no hotplug / cgroup changes between calls),
  // the function should report a stable value.
  EXPECT_EQ(first, second);
}

#if !defined(_WIN32)
// For POSIX-like platforms, verify the result does not exceed the number of
// online processors reported by the system.
TEST(GetProcessorCountTest_156, DoesNotExceedOnlineProcessors_156) {
  long online = sysconf(_SC_NPROCESSORS_ONLN);
  // Ensure the environment reports something reasonable.
  ASSERT_GT(online, 0);

  int count = GetProcessorCount();

  EXPECT_GE(count, 1);
  EXPECT_LE(count, online);
}
#endif  // !defined(_WIN32)
