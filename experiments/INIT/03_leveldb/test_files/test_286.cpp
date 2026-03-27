// File: db/c_minor_version_test_286.cc

#include <gtest/gtest.h>
#include "leveldb/db.h"  // for leveldb::kMinorVersion

// Forward declaration of the function under test.
// We don't assume any C linkage unless the real header specifies it.
int leveldb_minor_version();

class LeveldbMinorVersionTest_286 : public ::testing::Test {};

// Verifies the function returns exactly the value exposed by the public header.
TEST_F(LeveldbMinorVersionTest_286, ReturnsHeaderConstant_286) {
  EXPECT_EQ(leveldb::kMinorVersion, leveldb_minor_version())
      << "leveldb_minor_version() must match leveldb::kMinorVersion exposed by the public header";
}

// Verifies repeated calls are stable (observable behavior: no variability).
TEST_F(LeveldbMinorVersionTest_286, IdempotentAcrossCalls_286) {
  const int first = leveldb_minor_version();
  const int second = leveldb_minor_version();
  const int third = leveldb_minor_version();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  // Also ensure it continues to match the header constant.
  EXPECT_EQ(leveldb::kMinorVersion, first);
}

// A very light boundary-style check: version numbers should be non-negative.
// (This asserts only on an observable property without assuming internals.)
TEST_F(LeveldbMinorVersionTest_286, NonNegativeVersion_286) {
  EXPECT_GE(leveldb_minor_version(), 0);
}
