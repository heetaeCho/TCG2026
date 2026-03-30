// File: db/c_version_test.cc
#include "gtest/gtest.h"

#include "leveldb/c.h"   // declares leveldb_major_version()
#include "leveldb/db.h"  // exposes leveldb::kMajorVersion

// Verifies that the C API function reports the same major version
// as the public C++ constant.
TEST(LevelDBVersionTest_285, ReturnsSameAsPublicConstant_285) {
  EXPECT_EQ(leveldb_major_version(), leveldb::kMajorVersion);
}

// Basic sanity: version should be a non-negative integer.
TEST(LevelDBVersionTest_285, IsNonNegative_285) {
  EXPECT_GE(leveldb_major_version(), 0);
}
