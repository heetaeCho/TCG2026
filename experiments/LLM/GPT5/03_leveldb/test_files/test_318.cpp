// db_open_test_318.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace leveldb {

// Minimal mock for Env focusing only on the externally observable call in DB::Open
class MockEnvForOpen318 : public Env {
 public:
  MOCK_METHOD(Status, NewWritableFile,
              (const std::string& fname, WritableFile** result), (override));
  // Everything else can inherit default behavior from Env
};

// A tiny fixture that wires the Options.env to our mock.
class DBOpenTest_318 : public ::testing::Test {
 protected:
  Options MakeOptionsWithMockEnv(MockEnvForOpen318* mock_env) {
    Options opt;
    opt.env = mock_env;  // external collaborator we control
    // Other options remain defaults; we do not assume or assert internal effects.
    return opt;
  }
};

// [Behavior] When creating the log/MemTable step fails (Env::NewWritableFile returns error),
// DB::Open should fail and leave *dbptr as nullptr.
TEST_F(DBOpenTest_318, OpenFailsIfLogFileCreationFails_318) {
  MockEnvForOpen318 mock_env;
  Options opt = MakeOptionsWithMockEnv(&mock_env);

  // Make NewWritableFile fail with an I/O error. We do not assert the filename.
  EXPECT_CALL(mock_env, NewWritableFile(_, _))
      .WillOnce(Return(Status::IOError("inject io error", "")));

  DB* dbptr = nullptr;
  Status s = DB::Open(opt, "tmp_test_db_318_fail", &dbptr);

  EXPECT_FALSE(s.ok()) << "Open should propagate the failure from Env::NewWritableFile";
  EXPECT_EQ(dbptr, nullptr) << "On failure, DB::Open must not hand out a DB instance";
}

// [Behavior] If the log file creation fails, Env::NewWritableFile should be attempted exactly once
// (based on the provided code path), and *dbptr must remain nullptr.
TEST_F(DBOpenTest_318, NewWritableFileCalledOnceOnCreationFailure_318) {
  MockEnvForOpen318 mock_env;
  Options opt = MakeOptionsWithMockEnv(&mock_env);

  EXPECT_CALL(mock_env, NewWritableFile(_, _))
      .Times(1)
      .WillOnce(Return(Status::IOError("once only", "")));

  DB* dbptr = nullptr;
  Status s = DB::Open(opt, "tmp_test_db_318_once", &dbptr);

  EXPECT_FALSE(s.ok());
  EXPECT_EQ(dbptr, nullptr);
}

// [Behavior] On success, DB::Open must set *dbptr to a non-null pointer.
// We do not verify internals; we only confirm observable success and cleanup.
// To avoid coupling to WritableFile internals, we simulate success by letting
// NewWritableFile succeed while returning a nullptr file handle is *not* acceptable;
// return a non-error Status and a non-null dummy pointer if your WritableFile
// interface is available in your tree. If not, this test can be disabled.
class DummyWritableFile318 : public WritableFile {
 public:
  // Provide no-ops that satisfy the abstract interface of WritableFile in your tree.
  // If your WritableFile differs, adapt these methods accordingly.
  Status Append(const Slice&) override { return Status::OK(); }
  Status Close() override { return Status::OK(); }
  Status Flush() override { return Status::OK(); }
  Status Sync() override { return Status::OK(); }
  ~DummyWritableFile318() override = default;
};

TEST_F(DBOpenTest_318, OpenSuccessSetsDbPtr_318) {
  MockEnvForOpen318 mock_env;
  Options opt = MakeOptionsWithMockEnv(&mock_env);

  // Allocate a dummy file object to satisfy the constructor path shown in db_impl.cc.
  // Ownership is transferred to the DBImpl path; we don't delete it here.
  auto* dummy_file = new DummyWritableFile318();

  EXPECT_CALL(mock_env, NewWritableFile(_, _))
      .WillOnce(DoAll(SetArgPointee<1>(dummy_file), Return(Status::OK())));

  DB* dbptr = nullptr;
  Status s = DB::Open(opt, "tmp_test_db_318_ok", &dbptr);

  ASSERT_TRUE(s.ok()) << "Open should succeed when NewWritableFile succeeds";
  ASSERT_NE(dbptr, nullptr) << "On success, DB::Open must set *dbptr";

  // Clean up through the public interface (black-box).
  delete dbptr;  // DB has a virtual destructor
}

}  // namespace leveldb
