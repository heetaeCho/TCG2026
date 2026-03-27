// File: env_do_write_string_to_file_test_468.cc

#include <string>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "leveldb/env.h"

// Include the .cc to access the internal-static helper under test.
#include "util/env.cc"

using ::testing::_;
using ::testing::DoAll;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace leveldb {

// ---- Mocks ----
class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewWritableFile, (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));

  // The rest of Env virtuals are not used in these tests; leave them unmocked.
};

// ---- Tests ----

class DoWriteStringToFileTest_468 : public ::testing::Test {
 protected:
  MockEnv env_;
  const std::string fname_ = "tmp-file.dat";
  const Slice data_ = Slice("hello", 5);
};

// NewWritableFile fails -> should return that error, not call RemoveFile, and never call file methods.
TEST_F(DoWriteStringToFileTest_468, NewWritableFileFails_468) {
  EXPECT_CALL(env_, NewWritableFile(fname_, _))
      .WillOnce(Return(Status::IOError("open failed")));
  // No file created -> no RemoveFile.
  EXPECT_CALL(env_, RemoveFile(_)).Times(0);

  Status s = DoWriteStringToFile(&env_, data_, fname_, /*should_sync=*/true);
  EXPECT_TRUE(s.IsIOError());
}

// Append fails -> RemoveFile should be called; Sync/Close must not be invoked.
TEST_F(DoWriteStringToFileTest_468, AppendFailsTriggersCleanup_468) {
  auto* wf = new ::testing::StrictMock<MockWritableFile>();
  EXPECT_CALL(env_, NewWritableFile(fname_, _))
      .WillOnce(DoAll(SetArgPointee<1>(wf), Return(Status::OK())));

  EXPECT_CALL(*wf, Append(data_)).WillOnce(Return(Status::IOError("append failed")));
  // Sync/Close should not be called if append fails.
  EXPECT_CALL(*wf, Sync()).Times(0);
  EXPECT_CALL(*wf, Close()).Times(0);

  EXPECT_CALL(env_, RemoveFile(fname_)).Times(1);

  Status s = DoWriteStringToFile(&env_, data_, fname_, /*should_sync=*/true);
  EXPECT_TRUE(s.IsIOError());
}

// Happy path with should_sync = true: Append -> Sync -> Close; RemoveFile not called; returns OK.
TEST_F(DoWriteStringToFileTest_468, SuccessPath_WithSync_468) {
  auto* wf = new ::testing::StrictMock<MockWritableFile>();
  EXPECT_CALL(env_, NewWritableFile(fname_, _))
      .WillOnce(DoAll(SetArgPointee<1>(wf), Return(Status::OK())));

  {
    InSequence seq;
    EXPECT_CALL(*wf, Append(data_)).WillOnce(Return(Status::OK()));
    EXPECT_CALL(*wf, Sync()).WillOnce(Return(Status::OK()));
    EXPECT_CALL(*wf, Close()).WillOnce(Return(Status::OK()));
  }
  EXPECT_CALL(env_, RemoveFile(_)).Times(0);

  Status s = DoWriteStringToFile(&env_, data_, fname_, /*should_sync=*/true);
  EXPECT_TRUE(s.ok());
}

// Happy path with should_sync = false: Append -> Close (no Sync); RemoveFile not called; returns OK.
TEST_F(DoWriteStringToFileTest_468, SuccessPath_NoSync_468) {
  auto* wf = new ::testing::StrictMock<MockWritableFile>();
  EXPECT_CALL(env_, NewWritableFile(fname_, _))
      .WillOnce(DoAll(SetArgPointee<1>(wf), Return(Status::OK())));

  {
    InSequence seq;
    EXPECT_CALL(*wf, Append(data_)).WillOnce(Return(Status::OK()));
    // No Sync when should_sync is false
    EXPECT_CALL(*wf, Sync()).Times(0);
    EXPECT_CALL(*wf, Close()).WillOnce(Return(Status::OK()));
  }
  EXPECT_CALL(env_, RemoveFile(_)).Times(0);

  Status s = DoWriteStringToFile(&env_, data_, fname_, /*should_sync=*/false);
  EXPECT_TRUE(s.ok());
}

// Sync fails -> Close should NOT be called; RemoveFile should be called; returns error.
TEST_F(DoWriteStringToFileTest_468, SyncFailsTriggersCleanup_NoClose_468) {
  auto* wf = new ::testing::StrictMock<MockWritableFile>();
  EXPECT_CALL(env_, NewWritableFile(fname_, _))
      .WillOnce(DoAll(SetArgPointee<1>(wf), Return(Status::OK())));

  {
    InSequence seq;
    EXPECT_CALL(*wf, Append(data_)).WillOnce(Return(Status::OK()));
    EXPECT_CALL(*wf, Sync()).WillOnce(Return(Status::IOError("sync failed")));
  }
  EXPECT_CALL(*wf, Close()).Times(0);
  EXPECT_CALL(env_, RemoveFile(fname_)).Times(1);

  Status s = DoWriteStringToFile(&env_, data_, fname_, /*should_sync=*/true);
  EXPECT_TRUE(s.IsIOError());
}

// Close fails -> RemoveFile should be called; returns error.
TEST_F(DoWriteStringToFileTest_468, CloseFailsTriggersCleanup_468) {
  auto* wf = new ::testing::StrictMock<MockWritableFile>();
  EXPECT_CALL(env_, NewWritableFile(fname_, _))
      .WillOnce(DoAll(SetArgPointee<1>(wf), Return(Status::OK())));

  {
    InSequence seq;
    EXPECT_CALL(*wf, Append(data_)).WillOnce(Return(Status::OK()));
    // should_sync = false -> no Sync call
    EXPECT_CALL(*wf, Close()).WillOnce(Return(Status::IOError("close failed")));
  }
  EXPECT_CALL(env_, RemoveFile(fname_)).Times(1);

  Status s = DoWriteStringToFile(&env_, data_, fname_, /*should_sync=*/false);
  EXPECT_TRUE(s.IsIOError());
}

}  // namespace leveldb
