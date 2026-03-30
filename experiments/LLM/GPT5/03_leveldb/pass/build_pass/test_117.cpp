// EnvWrapper_LockFile_test_117.cc

#include "leveldb/env.h"
#include "leveldb/status.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace leveldb {

// ---- Test doubles ---------------------------------------------------------

// Minimal concrete FileLock we can hand out in tests.
class DummyFileLock : public FileLock {
 public:
  ~DummyFileLock() override = default;
};

// A Google Mock Env. We mock every Env method so the class is concrete,
// but tests here only set expectations on LockFile.
class MockEnv : public Env {
 public:
  ~MockEnv() override = default;

  // File APIs
  MOCK_METHOD(Status, NewSequentialFile,
              (const std::string& fname, SequentialFile** result), (override));
  MOCK_METHOD(Status, NewRandomAccessFile,
              (const std::string& fname, RandomAccessFile** result), (override));
  MOCK_METHOD(Status, NewWritableFile,
              (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(Status, NewAppendableFile,
              (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(bool, FileExists, (const std::string& fname), (override));
  MOCK_METHOD(Status, GetChildren,
              (const std::string& dir, std::vector<std::string>* result),
              (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, GetFileSize,
              (const std::string& fname, uint64_t* file_size), (override));
  MOCK_METHOD(Status, RenameFile,
              (const std::string& src, const std::string& target), (override));
  MOCK_METHOD(Status, LockFile,
              (const std::string& fname, FileLock** lock), (override));
  MOCK_METHOD(Status, UnlockFile, (FileLock* lock), (override));

  // Threading / scheduling
  MOCK_METHOD(void, Schedule, (void (*function)(void*), void* arg), (override));
  MOCK_METHOD(void, StartThread, (void (*function)(void*), void* arg),
              (override));

  // Misc
  MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));
  MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result),
              (override));
  MOCK_METHOD(uint64_t, NowMicros, (), (override));
  MOCK_METHOD(void, SleepForMicroseconds, (int micros), (override));
};

// ---- Test fixture ---------------------------------------------------------

class EnvWrapperLockFileTest_117 : public ::testing::Test {
 protected:
  MockEnv mock_;
  EnvWrapper wrapper_{&mock_};
};

// ---- Tests ----------------------------------------------------------------

// Verifies: EnvWrapper forwards the filename, sets the out-parameter exactly
// as provided by the target, and returns the same Status.
TEST_F(EnvWrapperLockFileTest_117, LockFile_ForwardsAndReturnsOK_117) {
  DummyFileLock* expected = new DummyFileLock;  // will be owned by the test
  FileLock* out = nullptr;

  EXPECT_CALL(mock_, LockFile("db/LOCK", _))
      .WillOnce(DoAll(SetArgPointee<1>(expected), Return(Status::OK())));

  Status s = wrapper_.LockFile("db/LOCK", &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, expected);

  delete expected;
}

// Verifies: an error returned by the target is propagated unchanged, and
// the out-parameter value set by the target is preserved.
TEST_F(EnvWrapperLockFileTest_117, LockFile_PropagatesErrorAndOutParam_117) {
  DummyFileLock* from_target = new DummyFileLock;
  FileLock* out = nullptr;

  // Simulate an I/O error while still setting a (possibly partial) lock ptr.
  EXPECT_CALL(mock_, LockFile("path/to/lock", _))
      .WillOnce(DoAll(SetArgPointee<1>(from_target),
                      Return(Status::IOError("fail-to-lock"))));

  Status s = wrapper_.LockFile("path/to/lock", &out);

  EXPECT_FALSE(s.ok());         // We don't assert the specific category here.
  EXPECT_EQ(out, from_target);  // Whatever target sets must pass through.

  delete from_target;
}

// Verifies: if the target does not modify the out-parameter, EnvWrapper does
// not change it either; the pointer remains whatever the caller had.
TEST_F(EnvWrapperLockFileTest_117, LockFile_DoesNotTouchOutParamIfTargetDoesNot_117) {
  // Sentinel initial value to detect unintended writes.
  DummyFileLock sentinel;
  FileLock* out = &sentinel;

  EXPECT_CALL(mock_, LockFile("any", _))
      .WillOnce(Return(Status::IOError("no-change")));

  Status s = wrapper_.LockFile("any", &out);

  EXPECT_FALSE(s.ok());
  EXPECT_EQ(out, &sentinel);  // Unchanged since target didn't set it.
}

// Verifies: boundary case with an empty filename still forwards to target and
// returns whatever the target returns.
TEST_F(EnvWrapperLockFileTest_117, LockFile_EmptyFilename_IsForwarded_117) {
  FileLock* out = nullptr;

  EXPECT_CALL(mock_, LockFile("", _))
      .WillOnce(Return(Status::NotFound("empty filename")));

  Status s = wrapper_.LockFile("", &out);

  EXPECT_FALSE(s.ok());
  EXPECT_EQ(out, nullptr);  // Target didn't set it in this scenario.
}

}  // namespace leveldb
