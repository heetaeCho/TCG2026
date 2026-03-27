// EnvWrapper_NewRandomAccessFile_test_107.cc

#include "leveldb/env.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;

namespace leveldb {

// Minimal mock for Env focusing only on NewRandomAccessFile.
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewRandomAccessFile,
              (const std::string& fname, RandomAccessFile** result), (override));
};

// Concrete RandomAccessFile to hand out via the out-parameter.
// Keep behavior minimal — tests never call Read; they only check pointer identity.
class DummyRandomAccessFile : public RandomAccessFile {
 public:
  ~DummyRandomAccessFile() override = default;

  // Provide a trivial implementation to satisfy the interface without
  // asserting or depending on internal behavior.
  Status Read(uint64_t, size_t, Slice*, char*) override { return Status(); }
};

// ---------- Tests ----------

class EnvWrapperTest_107 : public ::testing::Test {
 protected:
  MockEnv mock_;
  EnvWrapper wrapper_{&mock_};
};

// Normal operation: forwards call, propagates returned Status, and sets out pointer.
TEST_F(EnvWrapperTest_107, NewRandomAccessFile_ForwardsAndSetsPointer_107) {
  auto* file = new DummyRandomAccessFile();

  // Expect the wrapper to forward the exact filename and the out-parameter address.
  EXPECT_CALL(mock_, NewRandomAccessFile("data.sst", _))
      .WillOnce(DoAll(SetArgPointee<1>(file), Return(Status())));

  RandomAccessFile* out = nullptr;
  Status s = wrapper_.NewRandomAccessFile("data.sst", &out);

  // Observable effects: status and out-parameter are set as provided by target Env.
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, file);

  // Cleanup owned test object.
  delete file;
}

// Boundary condition: empty filename should still be forwarded exactly as-is.
TEST_F(EnvWrapperTest_107, NewRandomAccessFile_EmptyFilename_IsForwarded_107) {
  auto* file = new DummyRandomAccessFile();

  EXPECT_CALL(mock_, NewRandomAccessFile("", _))
      .WillOnce(DoAll(SetArgPointee<1>(file), Return(Status())));

  RandomAccessFile* out = nullptr;
  Status s = wrapper_.NewRandomAccessFile("", &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, file);

  delete file;
}

// Error path: non-OK status is propagated; if target doesn't set the pointer, it remains unchanged.
TEST_F(EnvWrapperTest_107, NewRandomAccessFile_PropagatesErrorAndLeavesPointerWhenUnset_107) {
  // Create a representative non-OK status. In LevelDB this could be NotFound/IOError;
  // we avoid relying on a specific code — only that !ok().
  Status error_status = Status::NotFound("missing");

  EXPECT_CALL(mock_, NewRandomAccessFile("missing.sst", _))
      .WillOnce(Return(error_status));

  RandomAccessFile* out = reinterpret_cast<RandomAccessFile*>(0xDEADBEEF);  // sentinel
  Status s = wrapper_.NewRandomAccessFile("missing.sst", &out);

  EXPECT_FALSE(s.ok());
  // Since the mock didn't set the out-parameter, it should remain as the prior value.
  EXPECT_EQ(out, reinterpret_cast<RandomAccessFile*>(0xDEADBEEF));
}

// Verifies the exact out-parameter identity from target Env is what caller observes.
TEST_F(EnvWrapperTest_107, NewRandomAccessFile_PassesThroughExactPointer_107) {
  auto* file = new DummyRandomAccessFile();

  EXPECT_CALL(mock_, NewRandomAccessFile("table-000123.sst", _))
      .WillOnce(DoAll(SetArgPointee<1>(file), Return(Status())));

  RandomAccessFile* out = nullptr;
  Status s = wrapper_.NewRandomAccessFile("table-000123.sst", &out);

  EXPECT_TRUE(s.ok());
  // Strict identity check — not just non-null.
  EXPECT_TRUE(out != nullptr);
  EXPECT_EQ(out, file);

  delete file;
}

}  // namespace leveldb
