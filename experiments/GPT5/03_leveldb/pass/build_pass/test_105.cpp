// File: env_wrapper_target_test_105.cc
#include "leveldb/env.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace leveldb {

// A Google Mock for Env so we can pass a non-null Env* into EnvWrapper
// (We do not invoke any of these; they’re here only to satisfy the abstract interface.)
class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile,
              (const std::string& f, SequentialFile** r), (override));
  MOCK_METHOD(Status, NewRandomAccessFile,
              (const std::string& f, RandomAccessFile** r), (override));
  MOCK_METHOD(Status, NewWritableFile,
              (const std::string& f, WritableFile** r), (override));
  MOCK_METHOD(Status, NewAppendableFile,
              (const std::string& f, WritableFile** r), (override));
  MOCK_METHOD(bool, FileExists, (const std::string& f), (override));
  MOCK_METHOD(Status, GetChildren,
              (const std::string& dir, std::vector<std::string>* r), (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& f), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& d), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& d), (override));
  MOCK_METHOD(Status, GetFileSize, (const std::string& f, uint64_t* s), (override));
  MOCK_METHOD(Status, RenameFile, (const std::string& s, const std::string& t), (override));
  MOCK_METHOD(Status, LockFile, (const std::string& f, FileLock** l), (override));
  MOCK_METHOD(Status, UnlockFile, (FileLock* l), (override));
  MOCK_METHOD(void, Schedule, (void (*f)(void*), void* a), (override));
  MOCK_METHOD(void, StartThread, (void (*f)(void*), void* a), (override));
  MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));
  MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result), (override));
  MOCK_METHOD(uint64_t, NowMicros, (), (override));
  MOCK_METHOD(void, SleepForMicroseconds, (int micros), (override));
};

class EnvWrapperTest_105 : public ::testing::Test {};

TEST_F(EnvWrapperTest_105, TargetReturnsSamePointer_105) {
  ::testing::StrictMock<MockEnv> mock_env;
  EnvWrapper wrapper(&mock_env);

  // Observable behavior: target() should return the exact pointer given to ctor.
  EXPECT_EQ(wrapper.target(), &mock_env);
}

TEST_F(EnvWrapperTest_105, TargetReturnsNullWhenConstructedWithNull_105) {
  EnvWrapper wrapper(nullptr);

  // Boundary case: constructed with nullptr -> target() yields nullptr.
  EXPECT_EQ(wrapper.target(), nullptr);
}

TEST_F(EnvWrapperTest_105, TargetWorksThroughConstQualifier_105) {
  ::testing::StrictMock<MockEnv> mock_env;
  EnvWrapper wrapper(&mock_env);
  const EnvWrapper& cwrapper = wrapper;

  // Ensure calling the const-qualified accessor preserves the same observable result.
  EXPECT_EQ(cwrapper.target(), &mock_env);
}

TEST_F(EnvWrapperTest_105, DifferentInstancesHoldDifferentTargets_105) {
  ::testing::StrictMock<MockEnv> env_a;
  ::testing::StrictMock<MockEnv> env_b;

  EnvWrapper wrap_a(&env_a);
  EnvWrapper wrap_b(&env_b);

  // Sanity/identity check across multiple instances.
  EXPECT_EQ(wrap_a.target(), &env_a);
  EXPECT_EQ(wrap_b.target(), &env_b);
  EXPECT_NE(wrap_a.target(), wrap_b.target());
}

}  // namespace leveldb
