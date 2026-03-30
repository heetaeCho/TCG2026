// File: db/filename_lock_unittest.cc
#include <gtest/gtest.h>
#include <string>

// Forward declare the function under test (no re-implementation).
namespace leveldb {
std::string LockFileName(const std::string& dbname);
}

class LockFileNameTest_332 : public ::testing::Test {};

// [Normal] Simple DB name -> "<dbname>/LOCK"
TEST_F(LockFileNameTest_332, AppendsLockToSimpleDbName_332) {
  EXPECT_EQ("testdb/LOCK", leveldb::LockFileName("testdb"));
}

// [Boundary] Empty DB name -> "/LOCK"
TEST_F(LockFileNameTest_332, EmptyDbName_YieldsSlashLock_332) {
  EXPECT_EQ("/LOCK", leveldb::LockFileName(""));
}

// [Normal] Path-like DB name preserves components -> "<path>/LOCK"
TEST_F(LockFileNameTest_332, PreservesPathComponents_332) {
  EXPECT_EQ("/var/tmp/mydb/LOCK", leveldb::LockFileName("/var/tmp/mydb"));
}

// [Boundary] Trailing slash in DB name -> "<dbname>//LOCK" (double slash is observable)
TEST_F(LockFileNameTest_332, TrailingSlash_ResultsInDoubleSlashBeforeLock_332) {
  EXPECT_EQ("path/to/db//LOCK", leveldb::LockFileName("path/to/db/"));
}

// [Edge] Non-ASCII DB name is handled as a regular string -> "<dbname>/LOCK"
TEST_F(LockFileNameTest_332, SupportsNonAsciiDbName_332) {
  const std::string kName = u8"데이터베이스";
  EXPECT_EQ(kName + "/LOCK", leveldb::LockFileName(kName));
}
