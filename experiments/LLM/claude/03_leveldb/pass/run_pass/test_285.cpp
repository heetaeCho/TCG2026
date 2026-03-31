#include "gtest/gtest.h"

// Include necessary headers
extern "C" {
#include "leveldb/c.h"
}
#include "leveldb/db.h"

// Declaration of the function under test
extern "C" int leveldb_major_version();

TEST(LevelDBMajorVersionTest_285, ReturnsMajorVersion_285) {
  int version = leveldb_major_version();
  EXPECT_EQ(version, leveldb::kMajorVersion);
}

TEST(LevelDBMajorVersionTest_285, ReturnsExpectedValue_285) {
  int version = leveldb_major_version();
  EXPECT_EQ(version, 1);
}

TEST(LevelDBMajorVersionTest_285, ReturnsPositiveValue_285) {
  int version = leveldb_major_version();
  EXPECT_GT(version, 0);
}

TEST(LevelDBMajorVersionTest_285, ConsistentAcrossMultipleCalls_285) {
  int version1 = leveldb_major_version();
  int version2 = leveldb_major_version();
  EXPECT_EQ(version1, version2);
}

TEST(LevelDBMajorVersionTest_285, IsNotZero_285) {
  int version = leveldb_major_version();
  EXPECT_NE(version, 0);
}

TEST(LevelDBMajorVersionTest_285, MatchesKnownConstant_285) {
  // kMajorVersion is known to be 1
  EXPECT_EQ(leveldb_major_version(), 1);
}
