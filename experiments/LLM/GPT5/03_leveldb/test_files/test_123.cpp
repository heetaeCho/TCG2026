// EnvWrapper_NowMicros_test_123.cc
#include <cstdint>
#include <limits>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/env.h"

using ::testing::Return;
using ::testing::StrictMock;

namespace leveldb {

// Minimal mock of Env that only cares about NowMicros() for these tests.
// We rely on Env providing default (non-pure) virtuals for other methods.
class MockEnvForNowMicros : public Env {
 public:
  MOCK_METHOD(uint64_t, NowMicros, (), (override));
};

// ---- Tests ----

class EnvWrapperTest_123 : public ::testing::Test {
 protected:
  StrictMock<MockEnvForNowMicros> mock_;
  EnvWrapper wrapper_{&mock_};
};

// Normal operation: single call is forwarded and return value is propagated.
TEST_F(EnvWrapperTest_123, NowMicros_ForwardsAndReturnsValue_123) {
  EXPECT_CALL(mock_, NowMicros())
      .Times(1)
      .WillOnce(Return(42ULL));

  const uint64_t micros = wrapper_.NowMicros();
  EXPECT_EQ(42ULL, micros);
}

// Boundary condition: very large (max) uint64_t value is propagated intact.
TEST_F(EnvWrapperTest_123, NowMicros_PropagatesMaxUint64_123) {
  const uint64_t kMax = std::numeric_limits<uint64_t>::max();
  EXPECT_CALL(mock_, NowMicros())
      .Times(1)
      .WillOnce(Return(kMax));

  EXPECT_EQ(kMax, wrapper_.NowMicros());
}

// Interaction verification: multiple calls are each delegated to target.
TEST_F(EnvWrapperTest_123, NowMicros_MultipleCallsEachDelegated_123) {
  EXPECT_CALL(mock_, NowMicros())
      .WillOnce(Return(100ULL))
      .WillOnce(Return(200ULL))
      .WillOnce(Return(300ULL));

  EXPECT_EQ(100ULL, wrapper_.NowMicros());
  EXPECT_EQ(200ULL, wrapper_.NowMicros());
  EXPECT_EQ(300ULL, wrapper_.NowMicros());
}

}  // namespace leveldb
