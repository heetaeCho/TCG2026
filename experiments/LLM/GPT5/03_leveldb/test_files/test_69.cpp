// File: version_numfiles_test_69.cc
#include <gtest/gtest.h>

// Include the header under test.
#include "db/version_set.h"

namespace {

using leveldb::Version;

// A simple fixture in case future setup/teardown is needed.
class VersionNumFilesTest_69 : public ::testing::Test {};

//
// Normal operation: default-constructed object should report a count.
// We do NOT assume any internal mechanics, only that the return value is a valid non-negative count.
//

TEST_F(VersionNumFilesTest_69, DefaultLevel0HasNonNegativeCount_69) {
  Version v;
  const int count = v.NumFiles(0);
  // Observable expectation: count is a size, so it should be >= 0.
  EXPECT_GE(count, 0);
}

TEST_F(VersionNumFilesTest_69, DefaultAllValidLevelsReturnNonNegative_69) {
  Version v;
  for (int level = 0; level <= 6; ++level) {
    EXPECT_GE(v.NumFiles(level), 0) << "Level " << level << " should return a non-negative count";
  }
}

//
// Boundary conditions: lowest and highest valid levels (0 and 6) should be callable and consistent.
//

TEST_F(VersionNumFilesTest_69, BoundaryLevel0IsCallableAndStable_69) {
  Version v;
  const int first = v.NumFiles(0);
  const int second = v.NumFiles(0);
  EXPECT_EQ(first, second);  // Repeated calls should be stable for the same observable state.
  EXPECT_GE(first, 0);
}

TEST_F(VersionNumFilesTest_69, BoundaryLevel6IsCallableAndStable_69) {
  Version v;
  const int first = v.NumFiles(6);
  const int second = v.NumFiles(6);
  EXPECT_EQ(first, second);
  EXPECT_GE(first, 0);
}

//
// Idempotence under no observable state change: multiple calls without any other interactions
// should not change the reported value.
//

TEST_F(VersionNumFilesTest_69, RepeatedCallsDoNotChangeResult_69) {
  Version v;
  const int a = v.NumFiles(3);
  const int b = v.NumFiles(3);
  const int c = v.NumFiles(3);
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
  EXPECT_GE(a, 0);
}

}  // namespace
