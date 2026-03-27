// SetCurrentFile_test_337.cc
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/status.h"
#include "leveldb/env.h"

// The function under test:
#include "db/filename.h"   // for DescriptorFileName / TempFileName / CurrentFileName
#include "db/filename.cc"  // or the header that declares SetCurrentFile

using ::testing::_;
using ::testing::Return;

namespace leveldb {

class MockEnv_337 : public Env {
 public:
  MOCK_METHOD(Status, RenameFile, (const std::string& src, const std::string& target), (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));

  // Unused virtuals can remain with default (base) behavior; we don’t stub them.
  // If your build requires explicit overrides for pure virtuals, add trivial stubs returning Status::OK().
};

// ---------- Tests ----------

class SetCurrentFileTest_337 : public ::testing::Test {
 protected:
  std::string dbname_ = "testdb";
  uint64_t number_ = 123;

  // Helpers to compute observable file names used in interactions
  std::string Tmp() const { return TempFileName(dbname_, number_); }
  std::string Current() const { return CurrentFileName(dbname_); }
};

// Normal operation: Write path assumed OK (black box), rename succeeds -> OK, no cleanup.
TEST_F(SetCurrentFileTest_337, RenameSuccess_337) {
  MockEnv_337 env;

  // Expect the tmp file to be renamed to CURRENT exactly once
  EXPECT_CALL(env, RenameFile(Tmp(), Current()))
      .WillOnce(Return(Status::OK()));

  // No cleanup should be triggered on success
  EXPECT_CALL(env, RemoveFile(_)).Times(0);

  Status s = SetCurrentFile(&env, dbname_, number_);
  EXPECT_TRUE(s.ok());
}

// Error case: Write path assumed OK, but rename fails -> returns that error and cleans up tmp.
TEST_F(SetCurrentFileTest_337, RenameFails_CleansUpTmp_337) {
  MockEnv_337 env;

  // Make RenameFile fail with an IOError (or any non-OK)
  Status rename_err = Status::IOError("rename failed");
  EXPECT_CALL(env, RenameFile(Tmp(), Current()))
      .WillOnce(Return(rename_err));

  // On failure, the tmp file should be removed exactly once
  EXPECT_CALL(env, RemoveFile(Tmp()))
      .Times(1)
      .WillOnce(Return(Status::OK()));

  Status s = SetCurrentFile(&env, dbname_, number_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

// Boundary-ish observable behavior: even if cleanup itself fails, SetCurrentFile still returns the original error.
TEST_F(SetCurrentFileTest_337, RenameFails_CleanupAlsoFails_StillReturnsOriginalError_337) {
  MockEnv_337 env;

  Status rename_err = Status::IOError("rename failed");
  EXPECT_CALL(env, RenameFile(Tmp(), Current()))
      .WillOnce(Return(rename_err));

  // Cleanup attempt may fail; behavior is still to return the rename error.
  EXPECT_CALL(env, RemoveFile(Tmp()))
      .Times(1)
      .WillOnce(Return(Status::IOError("remove tmp failed")));

  Status s = SetCurrentFile(&env, dbname_, number_);
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
}

}  // namespace leveldb
