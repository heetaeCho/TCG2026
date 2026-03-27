// File: env_wrapper_getchildren_test.cc

#include "leveldb/env.h"
#include "leveldb/status.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::NotNull;
using ::testing::Return;

namespace leveldb {

// A forwarding Env that delegates everything to a base Env,
// except GetChildren which is mocked so we can verify delegation.
class MockGetChildrenEnv : public Env {
 public:
  explicit MockGetChildrenEnv(Env* base) : base_(base) {}

  // --- Mocked target of our tests ---
  MOCK_METHOD(Status, GetChildren,
              (const std::string& dir, std::vector<std::string>* r),
              (override));

  // --- Forward everything else to base_ (not used by these tests) ---
  Status NewSequentialFile(const std::string& f, SequentialFile** r) override {
    return base_->NewSequentialFile(f, r);
  }
  Status NewRandomAccessFile(const std::string& f,
                             RandomAccessFile** r) override {
    return base_->NewRandomAccessFile(f, r);
  }
  Status NewWritableFile(const std::string& f, WritableFile** r) override {
    return base_->NewWritableFile(f, r);
  }
  Status NewAppendableFile(const std::string& f, WritableFile** r) override {
    return base_->NewAppendableFile(f, r);
  }
  bool FileExists(const std::string& f) override {
    return base_->FileExists(f);
  }
  Status RemoveFile(const std::string& f) override {
    return base_->RemoveFile(f);
  }
  Status CreateDir(const std::string& d) override { return base_->CreateDir(d); }
  Status RemoveDir(const std::string& d) override { return base_->RemoveDir(d); }
  Status GetFileSize(const std::string& f, uint64_t* s) override {
    return base_->GetFileSize(f, s);
  }
  Status RenameFile(const std::string& s, const std::string& t) override {
    return base_->RenameFile(s, t);
  }
  Status LockFile(const std::string& f, FileLock** l) override {
    return base_->LockFile(f, l);
  }
  Status UnlockFile(FileLock* l) override { return base_->UnlockFile(l); }
  void Schedule(void (*f)(void*), void* a) override {
    base_->Schedule(f, a);
  }
  void StartThread(void (*f)(void*), void* a) override {
    base_->StartThread(f, a);
  }
  Status GetTestDirectory(std::string* path) override {
    return base_->GetTestDirectory(path);
  }
  Status NewLogger(const std::string& fname, Logger** result) override {
    return base_->NewLogger(fname, result);
  }
  uint64_t NowMicros() override { return base_->NowMicros(); }
  void SleepForMicroseconds(int micros) override {
    base_->SleepForMicroseconds(micros);
  }

 private:
  Env* base_;
};

// Test fixture
class EnvWrapperGetChildrenTest_451 : public ::testing::Test {
 protected:
  Env* base_ = Env::Default();                  // real base (unused paths)
  MockGetChildrenEnv mock_target_{base_};       // collaborator to verify calls
  EnvWrapper wrapper_{&mock_target_};           // system under test
};

// Normal operation: forwards args and returns OK; vector populated by target.
TEST_F(EnvWrapperGetChildrenTest_451, ForwardsCallAndPropagatesSuccess_451) {
  const std::string dir = "/tmp/some_dir";
  std::vector<std::string> out;

  EXPECT_CALL(mock_target_, GetChildren(dir, NotNull()))
      .WillOnce(DoAll(
          Invoke([&](const std::string& d, std::vector<std::string>* r) {
            EXPECT_EQ(d, dir);  // argument forwarded exactly
            r->assign({"a.txt", "b.log", "subdir"});
            return Status::OK();
          }),
          Return(Status::OK())));

  Status s = wrapper_.GetChildren(dir, &out);

  EXPECT_TRUE(s.ok());
  ASSERT_EQ(out.size(), 3u);
  EXPECT_EQ(out[0], "a.txt");
  EXPECT_EQ(out[1], "b.log");
  EXPECT_EQ(out[2], "subdir");
}

// Error propagation: underlying returns error; wrapper returns same error.
TEST_F(EnvWrapperGetChildrenTest_451, ReturnsErrorFromTarget_451) {
  const std::string dir = "/no/such/dir";
  std::vector<std::string> out = {"preserve"};

  Status underlying_err = Status::IOError("cannot list directory");

  EXPECT_CALL(mock_target_, GetChildren(dir, NotNull()))
      .WillOnce(Return(underlying_err));

  Status s = wrapper_.GetChildren(dir, &out);

  EXPECT_FALSE(s.ok());
  EXPECT_EQ(s.ToString(), underlying_err.ToString());  // same error text
  // Our mock didn't touch 'out', so its content should remain as-is.
  ASSERT_EQ(out.size(), 1u);
  EXPECT_EQ(out[0], "preserve");
}

// Boundary: empty directory string is forwarded as-is and handled by target.
TEST_F(EnvWrapperGetChildrenTest_451, EmptyDirArgumentIsForwarded_451) {
  const std::string dir = "";  // boundary input
  std::vector<std::string> out;

  EXPECT_CALL(mock_target_, GetChildren(dir, NotNull()))
      .WillOnce(DoAll(
          Invoke([&](const std::string& d, std::vector<std::string>* r) {
            EXPECT_TRUE(d.empty());
            r->clear();
            return Status::OK();
          }),
          Return(Status::OK())));

  Status s = wrapper_.GetChildren(dir, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_TRUE(out.empty());
}

// Larger output: ensures wrapper surfaces exactly what target writes.
TEST_F(EnvWrapperGetChildrenTest_451, PopulatesLargeListFromTarget_451) {
  const std::string dir = "/var/log";
  std::vector<std::string> out;

  std::vector<std::string> many(100);
  for (size_t i = 0; i < many.size(); ++i) many[i] = "f" + std::to_string(i);

  EXPECT_CALL(mock_target_, GetChildren(dir, NotNull()))
      .WillOnce(DoAll(
          Invoke([&](const std::string& d, std::vector<std::string>* r) {
            *r = many;
            return Status::OK();
          }),
          Return(Status::OK())));

  Status s = wrapper_.GetChildren(dir, &out);

  EXPECT_TRUE(s.ok());
  EXPECT_EQ(out, many);  // exactly what the target provided
}

}  // namespace leveldb
