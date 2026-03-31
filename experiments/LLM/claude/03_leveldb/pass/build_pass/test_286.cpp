#include "gtest/gtest.h"

// Include the necessary headers
#include "leveldb/c.h"
#include "leveldb/db.h"

TEST(LevelDBMinorVersionTest_286, ReturnsExpectedMinorVersion_286) {
  int minor_version = leveldb_minor_version();
  EXPECT_EQ(minor_version, 23);
}

TEST(LevelDBMinorVersionTest_286, ReturnsNonNegativeValue_286) {
  int minor_version = leveldb_minor_version();
  EXPECT_GE(minor_version, 0);
}

TEST(LevelDBMinorVersionTest_286, ConsistentAcrossMultipleCalls_286) {
  int first_call = leveldb_minor_version();
  int second_call = leveldb_minor_version();
  EXPECT_EQ(first_call, second_call);
}

TEST(LevelDBMinorVersionTest_286, MatchesKMinorVersion_286) {
  int minor_version = leveldb_minor_version();
  EXPECT_EQ(minor_version, leveldb::kMinorVersion);
}
