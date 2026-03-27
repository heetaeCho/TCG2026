// File: db/destroydb_test.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/status.h"
#include "db/filename.h"     // For FileType enum; we do not call ParseFileName directly
#include <string>
#include <vector>

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::HasSubstr;

namespace leveldb {

// ----- Minimal stand-ins used by Env interface -----
struct FileLock { virtual ~FileLock() = default; };

// ----- Mock Env used to observe interactions -----
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, GetChildren,
              (const std::string& dir, std::vector<std::string>* result),
              (override));

  MOCK_METHOD(Status, RemoveFile,
              (const std::string& fname),
              (override));

  MOCK_METHOD(Status, RemoveDir,
              (const std::string& dirname),
              (override));

  MOCK_METHOD(Status, LockFile,
              (const std::string& fname, FileLock** lock),
              (override));

  MOCK_METHOD(Status, UnlockFile,
              (FileLock* lock),
              (override));
};

// ---------- Test Fixture ----------
class DestroyDBTest_319 : public ::testing::Test {
 protected:
  Options opts_;
  StrictMock<MockEnv> env_;  // strict to ensure only expected calls happen

  void SetUp() override {
    opts_.env = &env_;
  }
};

// ============ TESTS ============

// 1) Boundary / early-exit: GetChildren() is non-OK -> DestroyDB returns OK and does nothing else.
TEST_F(DestroyDBTest_319, EarlyReturnWhenGetChildrenFails_319) {
  const std::string db = "/tmp/testdb_early_319";

  // Simulate failure listing directory
  EXPECT_CALL(env_, GetChildren(db, _))
      .WillOnce(Return(Status::IOError("list failed")));

  // No locking or deletions should be attempted
  // (StrictMock ensures no unexpected calls occur)

  Status s = DestroyDB(db, opts_);
  EXPECT_TRUE(s.ok()) << "DestroyDB should return OK when directory listing fails";
}

// 2) Error: LockFile() fails -> function returns that error and performs no deletions.
TEST_F(DestroyDBTest_319, ReturnsLockErrorWhenCannotLock_319) {
  const std::string db = "/tmp/testdb_lockerr_319";

  // Directory exists with some files (exact names don't matter for this path)
  std::vector<std::string> files = {"anyfile", "000001.log", "LOCK"};
  EXPECT_CALL(env_, GetChildren(db, _))
      .WillOnce(DoAll(SetArgPointee<1>(files), Return(Status::OK())));

  // Fail to acquire DB lock
  EXPECT_CALL(env_, LockFile(db + "/LOCK", _))
      .WillOnce(Return(Status::IOError("lock failed")));

  // No unlock/remove calls should occur due to StrictMock

  Status s = DestroyDB(db, opts_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// 3) Happy path: lock succeeds, we unlock, remove the lock file, and attempt to remove the directory.
TEST_F(DestroyDBTest_319, SuccessUnlocksRemovesLockAndDir_319) {
  const std::string db = "/tmp/testdb_ok_319";

  // Provide a mix of names; per-file deletions inside the loop depend on ParseFileName.
  // We don't assert those here; we only assert the mandatory lock/dir behavior.
  std::vector<std::string> files = {"000001.log", "LOCK", "CURRENT", "random"};
  EXPECT_CALL(env_, GetChildren(db, _))
      .WillOnce(DoAll(SetArgPointee<1>(files), Return(Status::OK())));

  // Lock succeeds; provide a dummy FileLock*
  auto* fl = new FileLock();
  EXPECT_CALL(env_, LockFile(db + "/LOCK", _))
      .WillOnce(DoAll(SetArgPointee<1>(fl), Return(Status::OK())));

  EXPECT_CALL(env_, UnlockFile(fl))
      .WillOnce(Return(Status::OK()));

  // After unlock, DestroyDB removes the lock file by full path
  EXPECT_CALL(env_, RemoveFile(db + "/LOCK"))
      .WillOnce(Return(Status::OK()));

  // Finally, it attempts to remove the directory
  EXPECT_CALL(env_, RemoveDir(db))
      .WillOnce(Return(Status::OK()));

  Status s = DestroyDB(db, opts_);
  EXPECT_TRUE(s.ok());
}

// 4) Propagates first per-file deletion error (from the internal loop) while still performing unlock/cleanup.
TEST_F(DestroyDBTest_319, PerFileDeleteErrorIsReturned_319) {
  const std::string db = "/tmp/testdb_fileerr_319";

  // Use names that LevelDB typically parses into non-lock file types so loop attempts RemoveFile(db/<name>)
  // Note: We still do not assert ParseFileName behavior; we only set expectations permissively.
  std::vector<std::string> files = {"000001.log", "000003.sst", "LOCK"};
  EXPECT_CALL(env_, GetChildren(db, _))
      .WillOnce(DoAll(SetArgPointee<1>(files), Return(Status::OK())));

  auto* fl = new FileLock();
  EXPECT_CALL(env_, LockFile(db + "/LOCK", _))
      .WillOnce(DoAll(SetArgPointee<1>(fl), Return(Status::OK())));

  // We cannot know exactly which names ParseFileName will accept.
  // Set broad expectations:
  // - At least one RemoveFile call for a file under the DB directory returns an error
  // - After the loop, DestroyDB must still Unlock, Remove lock file, Remove dir
  // Implement using gmock matchers and sequencing.
  {
    // Allow any number of RemoveFile calls for db/<something>, with the *first such call* returning error,
    // and any subsequent ones returning OK. We still match the mandatory lock file remove separately below.
    testing::Sequence seq;

    // A catch-all for "some" data-file removal attempt that errors
    EXPECT_CALL(env_, RemoveFile(testing::StartsWith(db + "/")))
        .InSequence(seq)
        .WillOnce(Return(Status::IOError("data remove failed")));

    // Any further file removals (data files) can succeed (optional)
    EXPECT_CALL(env_, RemoveFile(testing::StartsWith(db + "/")))
        .InSequence(seq)
        .WillRepeatedly(Return(Status::OK()));
  }

  EXPECT_CALL(env_, UnlockFile(fl))
      .WillOnce(Return(Status::OK()));

  // The specific removal of the lock file path must occur; match the exact path.
  EXPECT_CALL(env_, RemoveFile(db + "/LOCK"))
      .WillOnce(Return(Status::OK()));

  EXPECT_CALL(env_, RemoveDir(db))
      .WillOnce(Return(Status::OK()));

  Status s = DestroyDB(db, opts_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

}  // namespace leveldb
