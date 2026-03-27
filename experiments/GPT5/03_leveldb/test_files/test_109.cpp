// File: envwrapper_newappendablefile_test_109.cc
#include "leveldb/env.h"
#include "leveldb/status.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::DoAll;
using ::testing::Eq;
using ::testing::Return;
using ::testing::SetArgPointee;
using ::testing::StrictMock;

namespace leveldb {

class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewAppendableFile,
              (const std::string& fname, WritableFile** result), (override));
  // We declare only what we need for these tests; the rest of Env stays a black box.
};

class DummyWritableFile : public WritableFile {
 public:
  ~DummyWritableFile() override = default;
};

class EnvWrapperTest_109 : public ::testing::Test {
 protected:
  StrictMock<MockEnv> mock_target_;
  EnvWrapper wrapper_{&mock_target_};
};

// [Normal] Forwards call with the same filename and returns Status from target.
// Also verifies the output pointer is exactly what target set.
TEST_F(EnvWrapperTest_109, NewAppendableFile_ForwardsAndSetsOutput_OK_109) {
  const std::string fname = "append.log";
  DummyWritableFile* created = new DummyWritableFile();  // deleted below
  WritableFile* out = nullptr;

  EXPECT_CALL(mock_target_, NewAppendableFile(Eq(fname), _))
      .WillOnce(DoAll(SetArgPointee<1>(created), Return(Status::OK())));

  Status s = wrapper_.NewAppendableFile(fname, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, created);

  // Clean up what the target "created"
  delete created;
}

// [Error path] Propagates failure Status from target and leaves output unchanged
// (observable here as remaining nullptr since target didn't set it).
TEST_F(EnvWrapperTest_109, NewAppendableFile_PropagatesFailure_109) {
  const std::string fname = "missing/dir/append.log";
  WritableFile* out = nullptr;

  EXPECT_CALL(mock_target_, NewAppendableFile(Eq(fname), _))
      .WillOnce(Return(Status::IOError("cannot open for append")));

  Status s = wrapper_.NewAppendableFile(fname, &out);

  EXPECT_FALSE(s.ok());
  EXPECT_EQ(out, nullptr);
}

// [Boundary] Forwards even when caller passes a null double-pointer.
// Verifies the exact nullptr is forwarded and the returned Status is propagated.
TEST_F(EnvWrapperTest_109, NewAppendableFile_ForwardsNullOutputPointer_109) {
  const std::string fname = "just_check_forwarding";

  EXPECT_CALL(mock_target_, NewAppendableFile(Eq(fname), nullptr))
      .WillOnce(Return(Status::OK()));

  // Intentionally pass nullptr for the WritableFile** parameter.
  Status s = wrapper_.NewAppendableFile(fname, /*r=*/nullptr);

  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
