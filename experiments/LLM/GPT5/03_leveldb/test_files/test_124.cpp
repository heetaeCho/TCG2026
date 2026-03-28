// EnvWrapper_SleepForMicroseconds_test_124.cc
#include <climits>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/env.h"

using ::testing::StrictMock;
using ::testing::Exactly;

namespace leveldb {

// Minimal mock for Env that only mocks the method under test.
// Other Env methods are virtual (not pure) per the provided header,
// so we don't need to override them.
class MockEnv_124 : public Env {
 public:
  MOCK_METHOD(void, SleepForMicroseconds, (int micros), (override));
};

class EnvWrapperSleepTest_124 : public ::testing::Test {
 protected:
  StrictMock<MockEnv_124> mock_env_;
  EnvWrapper wrapper_{&mock_env_};  // Exercise wrapper as a black box
};

// Normal operation: forwards a positive value to target Env.
TEST_F(EnvWrapperSleepTest_124, ForwardsPositiveMicros_124) {
  const int micros = 1500;
  EXPECT_CALL(mock_env_, SleepForMicroseconds(micros)).Times(Exactly(1));
  wrapper_.SleepForMicroseconds(micros);
}

// Boundary: forwards zero without alteration.
TEST_F(EnvWrapperSleepTest_124, ForwardsZeroMicros_124) {
  const int micros = 0;
  EXPECT_CALL(mock_env_, SleepForMicroseconds(micros)).Times(Exactly(1));
  wrapper_.SleepForMicroseconds(micros);
}

// Boundary/Exceptional input (as observable): negative value is still forwarded.
// We do NOT assert internal handling; only that the exact value is passed through.
TEST_F(EnvWrapperSleepTest_124, ForwardsNegativeMicros_124) {
  const int micros = -1;
  EXPECT_CALL(mock_env_, SleepForMicroseconds(micros)).Times(Exactly(1));
  wrapper_.SleepForMicroseconds(micros);
}

// Boundary (upper range): forwards INT_MAX.
TEST_F(EnvWrapperSleepTest_124, ForwardsIntMaxMicros_124) {
  const int micros = INT_MAX;
  EXPECT_CALL(mock_env_, SleepForMicroseconds(micros)).Times(Exactly(1));
  wrapper_.SleepForMicroseconds(micros);
}

}  // namespace leveldb
