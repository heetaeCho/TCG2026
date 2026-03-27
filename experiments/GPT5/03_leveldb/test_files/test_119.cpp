// File: envwrapper_schedule_test_119.cc
#include "leveldb/env.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Eq;
using ::testing::InSequence;

namespace leveldb {

// Minimal mock that only verifies the external interaction we care about.
class MockEnvForSchedule : public Env {
 public:
  MOCK_METHOD(void, Schedule, (void (*function)(void*), void* arg), (override));
  // Other virtuals are not exercised by these tests and can remain unmocked.
};

// A simple no-op function to use as a function pointer in expectations.
static void NoOpTask_119(void*) {}

class EnvWrapperScheduleTest_119 : public ::testing::Test {
 protected:
  MockEnvForSchedule mock_env_;
  EnvWrapper wrapper_{&mock_env_};
};

// [Normal] Forwards function pointer and argument as-is to the target Env.
TEST_F(EnvWrapperScheduleTest_119, ForwardsFunctionAndArg_119) {
  int payload = 42;
  EXPECT_CALL(mock_env_, Schedule(Eq(&NoOpTask_119), Eq(&payload))).Times(1);

  wrapper_.Schedule(&NoOpTask_119, &payload);
}

// [Boundary] Forwards nullptr argument without alteration.
TEST_F(EnvWrapperScheduleTest_119, ForwardsNullArgument_119) {
  EXPECT_CALL(mock_env_, Schedule(Eq(&NoOpTask_119), Eq(nullptr))).Times(1);

  wrapper_.Schedule(&NoOpTask_119, nullptr);
}

// [Boundary] Forwards nullptr function pointer (wrapper must not invoke it).
TEST_F(EnvWrapperScheduleTest_119, ForwardsNullFunctionPointer_119) {
  // We only verify delegation; we do NOT call the function pointer.
  EXPECT_CALL(mock_env_, Schedule(Eq(nullptr), Eq(nullptr))).Times(1);

  wrapper_.Schedule(nullptr, nullptr);
}

// [Behavioral] Multiple calls are each delegated with the correct pairing and order.
TEST_F(EnvWrapperScheduleTest_119, ForwardsMultipleCallsInOrder_119) {
  int a = 1, b = 2;
  InSequence seq;  // ensure order is preserved
  EXPECT_CALL(mock_env_, Schedule(Eq(&NoOpTask_119), Eq(&a))).Times(1);
  EXPECT_CALL(mock_env_, Schedule(Eq(&NoOpTask_119), Eq(&b))).Times(1);

  wrapper_.Schedule(&NoOpTask_119, &a);
  wrapper_.Schedule(&NoOpTask_119, &b);
}

}  // namespace leveldb
