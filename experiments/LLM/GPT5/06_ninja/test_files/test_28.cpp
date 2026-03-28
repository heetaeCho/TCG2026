// File: jobserver_config_has_mode_test_28.cc

#include "gtest/gtest.h"
#include "jobserver.h"

// Fixture for Jobserver::Config related tests.
class JobserverConfigTest_28 : public ::testing::Test {
 protected:
  Jobserver::Config config_;
};

// Verifies that a default-constructed Config reports no mode.
TEST_F(JobserverConfigTest_28, DefaultConstructedConfig_HasModeFalse_28) {
  // By interface, Config has a default-initialized mode (expected kModeNone).
  // We only check the observable behavior of HasMode().
  EXPECT_FALSE(config_.HasMode());
}

// Verifies that HasMode() is true when mode is set to kModePipe.
TEST_F(JobserverConfigTest_28, HasModeTrueWhenModeIsPipe_28) {
  config_.mode = Jobserver::Config::kModePipe;
  EXPECT_TRUE(config_.HasMode());
}

// Verifies that HasMode() is true when mode is set to kModePosixFifo.
TEST_F(JobserverConfigTest_28, HasModeTrueWhenModeIsPosixFifo_28) {
  config_.mode = Jobserver::Config::kModePosixFifo;
  EXPECT_TRUE(config_.HasMode());
}

// Verifies that HasMode() is true when mode is set to kModeWin32Semaphore.
TEST_F(JobserverConfigTest_28, HasModeTrueWhenModeIsWin32Semaphore_28) {
  config_.mode = Jobserver::Config::kModeWin32Semaphore;
  EXPECT_TRUE(config_.HasMode());
}

// Verifies that HasMode() is true when mode is set to kModeDefault.
TEST_F(JobserverConfigTest_28, HasModeTrueWhenModeIsDefault_28) {
  config_.mode = Jobserver::Config::kModeDefault;
  EXPECT_TRUE(config_.HasMode());
}
