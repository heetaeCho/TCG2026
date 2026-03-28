// File: envwrapper_startthread_test_120.cc

#include "leveldb/env.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Eq;
using ::testing::InSequence;

namespace {

// Free functions to use as thread entry points in tests.
void NoopEntry(void*) {}
void AnotherEntry(void*) {}

class MockEnv : public leveldb::Env {
public:
  MOCK_METHOD(void, StartThread, (void (*)(void*), void*), (override));
};

class EnvWrapperStartThreadTest_120 : public ::testing::Test {
protected:
  MockEnv mock_env_;
  leveldb::EnvWrapper wrapper_{&mock_env_};
};

// [Normal operation] Forwards the exact function pointer and argument.
TEST_F(EnvWrapperStartThreadTest_120, ForwardsFunctionAndArg_120) {
  int payload = 123;
  void* arg = &payload;

  EXPECT_CALL(mock_env_, StartThread(Eq(&NoopEntry), Eq(arg)));

  wrapper_.StartThread(&NoopEntry, arg);
}

// [Boundary] Forwards when argument pointer is nullptr.
TEST_F(EnvWrapperStartThreadTest_120, ForwardsNullArg_120) {
  EXPECT_CALL(mock_env_, StartThread(Eq(&NoopEntry), Eq(nullptr)));

  wrapper_.StartThread(&NoopEntry, nullptr);
}

// [Boundary] Forwards when function pointer is nullptr (no execution; just delegation).
TEST_F(EnvWrapperStartThreadTest_120, ForwardsNullFunctionPointer_120) {
  int x = 0;
  void* arg = &x;

  EXPECT_CALL(mock_env_, StartThread(Eq(nullptr), Eq(arg)));

  wrapper_.StartThread(nullptr, arg);
}

// [Normal operation] Multiple calls are each forwarded with their respective parameters.
TEST_F(EnvWrapperStartThreadTest_120, ForwardsMultipleCallsWithCorrectParams_120) {
  int a = 1, b = 2;
  void* arg_a = &a;
  void* arg_b = &b;

  InSequence seq;  // Ensure call order is preserved.
  EXPECT_CALL(mock_env_, StartThread(Eq(&NoopEntry), Eq(arg_a)));
  EXPECT_CALL(mock_env_, StartThread(Eq(&AnotherEntry), Eq(arg_b)));

  wrapper_.StartThread(&NoopEntry, arg_a);
  wrapper_.StartThread(&AnotherEntry, arg_b);
}

}  // namespace
