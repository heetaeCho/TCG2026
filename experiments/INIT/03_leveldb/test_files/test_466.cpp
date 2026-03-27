// File: env_deletefile_test.cc
#include "leveldb/env.h"
#include "leveldb/status.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Exactly;
using ::testing::Return;

namespace leveldb {
namespace {

// Minimal concrete Env test double.
// - We MOCK only RemoveFile to observe calls/return values.
// - All other virtuals are trivially implemented to make the class concrete.
//   These stubs are *not* used by the tests and do not simulate the behavior
//   of DeleteFile itself.
class TestEnv : public Env {
 public:
  // Observe/drive RemoveFile
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));

  // ---- Required concrete overrides (not used by these tests) ----
  Status NewSequentialFile(const std::string&, SequentialFile**) override {
    return Status::OK();
  }
  Status NewRandomAccessFile(const std::string&, RandomAccessFile**) override {
    return Status::OK();
  }
  Status NewWritableFile(const std::string&, WritableFile**) override {
    return Status::OK();
  }
  Status NewAppendableFile(const std::string&, WritableFile**) override {
    return Status::OK();
  }
  bool FileExists(const std::string&) override { return false; }

  Status GetChildren(const std::string&, std::vector<std::string>* result) override {
    if (result) result->clear();
    return Status::OK();
  }

  Status CreateDir(const std::string&) override { return Status::OK(); }
  Status RemoveDir(const std::string&) override { return Status::OK(); }
  Status DeleteDir(const std::string&) override { return Status::OK(); }

  Status GetFileSize(const std::string&, uint64_t* sz) override {
    if (sz) *sz = 0;
    return Status::OK();
  }

  Status RenameFile(const std::string&, const std::string&) override {
    return Status::OK();
  }

  Status LockFile(const std::string&, FileLock**) override { return Status::OK(); }
  Status UnlockFile(FileLock*) override { return Status::OK(); }

  void Schedule(void (*)(void*), void*) override {}
  void StartThread(void (*)(void*), void*) override {}

  Status GetTestDirectory(std::string* path) override {
    if (path) *path = ".";
    return Status::OK();
  }

  Status NewLogger(const std::string&, Logger**) override { return Status::OK(); }

  uint64_t NowMicros() override { return 0; }
  void SleepForMicroseconds(int) override {}

  // The strange duplicate signature in the provided header:
  Status GetChildren(const std::string&, int* /*result*/) override {
    // Stub (not used)
    return Status::OK();
  }
};

// --------------------------- Tests ---------------------------

// Normal operation: forwards filename and propagates OK status.
TEST(EnvDeleteFile_466, DelegatesAndReturnsOK_466) {
  TestEnv env;

  const std::string fname = "data/abc.txt";
  EXPECT_CALL(env, RemoveFile(fname))
      .Times(Exactly(1))
      .WillOnce(Return(Status::OK()));

  Status s = env.DeleteFile(fname);
  EXPECT_TRUE(s.ok());
}

// Error propagation: returns exactly what RemoveFile returns (error).
TEST(EnvDeleteFile_466, PropagatesErrorFromRemoveFile_466) {
  TestEnv env;

  const std::string fname = "data/missing.txt";
  // Use a concrete non-OK status to ensure propagation.
  Status injected = Status::IOError("remove failed");
  EXPECT_CALL(env, RemoveFile(fname))
      .Times(Exactly(1))
      .WillOnce(Return(injected));

  Status s = env.DeleteFile(fname);
  EXPECT_FALSE(s.ok());
  // Optional: if Status has ToString(), check it carries through.
  // EXPECT_THAT(s.ToString(), ::testing::HasSubstr("remove failed"));
}

// Boundary case: empty filename is forwarded unchanged to RemoveFile.
TEST(EnvDeleteFile_466, ForwardsEmptyFilename_466) {
  TestEnv env;

  const std::string empty;
  EXPECT_CALL(env, RemoveFile(empty))
      .Times(Exactly(1))
      .WillOnce(Return(Status::OK()));

  Status s = env.DeleteFile(empty);
  EXPECT_TRUE(s.ok());
}

}  // namespace
}  // namespace leveldb
