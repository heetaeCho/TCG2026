#include "gtest/gtest.h"
#include "jobserver.h"

// Test fixture for Jobserver::Config
class JobserverConfigTest_28 : public ::testing::Test {
protected:
    Jobserver::Config config;
};

// Test that default-constructed Config has no mode set
TEST_F(JobserverConfigTest_28, DefaultModeIsNone_28) {
    EXPECT_EQ(config.mode, Jobserver::Config::kModeNone);
}

// Test that HasMode returns false when mode is kModeNone (default)
TEST_F(JobserverConfigTest_28, HasModeReturnsFalseWhenModeNone_28) {
    config.mode = Jobserver::Config::kModeNone;
    EXPECT_FALSE(config.HasMode());
}

// Test that HasMode returns true when mode is kModePipe
TEST_F(JobserverConfigTest_28, HasModeReturnsTrueWhenModePipe_28) {
    config.mode = Jobserver::Config::kModePipe;
    EXPECT_TRUE(config.HasMode());
}

// Test that HasMode returns true when mode is kModePosixFifo
TEST_F(JobserverConfigTest_28, HasModeReturnsTrueWhenModePosixFifo_28) {
    config.mode = Jobserver::Config::kModePosixFifo;
    EXPECT_TRUE(config.HasMode());
}

// Test that HasMode returns true when mode is kModeWin32Semaphore
TEST_F(JobserverConfigTest_28, HasModeReturnsTrueWhenModeWin32Semaphore_28) {
    config.mode = Jobserver::Config::kModeWin32Semaphore;
    EXPECT_TRUE(config.HasMode());
}

// Test that HasMode returns true when mode is kModeDefault
TEST_F(JobserverConfigTest_28, HasModeReturnsTrueWhenModeDefault_28) {
    config.mode = Jobserver::Config::kModeDefault;
    EXPECT_TRUE(config.HasMode());
}

// Test that default path is empty
TEST_F(JobserverConfigTest_28, DefaultPathIsEmpty_28) {
    EXPECT_TRUE(config.path.empty());
}

// Test that path can be set and retrieved
TEST_F(JobserverConfigTest_28, PathCanBeSet_28) {
    config.path = "/tmp/jobserver.fifo";
    EXPECT_EQ(config.path, "/tmp/jobserver.fifo");
}

// Test that kModeDefault equals kModePosixFifo
TEST_F(JobserverConfigTest_28, ModeDefaultEqualsPosixFifo_28) {
    EXPECT_EQ(Jobserver::Config::kModeDefault, Jobserver::Config::kModePosixFifo);
}

// Test that kModeNone has value 0
TEST_F(JobserverConfigTest_28, ModeNoneValueIsZero_28) {
    EXPECT_EQ(Jobserver::Config::kModeNone, 0);
}

// Test mode transition: setting mode from None to Pipe changes HasMode result
TEST_F(JobserverConfigTest_28, ModeTransitionNoneToPipe_28) {
    EXPECT_FALSE(config.HasMode());
    config.mode = Jobserver::Config::kModePipe;
    EXPECT_TRUE(config.HasMode());
}

// Test mode transition: setting mode back to None changes HasMode result
TEST_F(JobserverConfigTest_28, ModeTransitionPipeToNone_28) {
    config.mode = Jobserver::Config::kModePipe;
    EXPECT_TRUE(config.HasMode());
    config.mode = Jobserver::Config::kModeNone;
    EXPECT_FALSE(config.HasMode());
}

// Test that setting path does not affect HasMode
TEST_F(JobserverConfigTest_28, SettingPathDoesNotAffectHasMode_28) {
    config.path = "/some/path";
    EXPECT_FALSE(config.HasMode());
}

// Test enum values are distinct (except kModeDefault which aliases kModePosixFifo)
TEST_F(JobserverConfigTest_28, EnumValuesAreDistinct_28) {
    EXPECT_NE(Jobserver::Config::kModeNone, Jobserver::Config::kModePipe);
    EXPECT_NE(Jobserver::Config::kModeNone, Jobserver::Config::kModePosixFifo);
    EXPECT_NE(Jobserver::Config::kModeNone, Jobserver::Config::kModeWin32Semaphore);
    EXPECT_NE(Jobserver::Config::kModePipe, Jobserver::Config::kModePosixFifo);
    EXPECT_NE(Jobserver::Config::kModePipe, Jobserver::Config::kModeWin32Semaphore);
    EXPECT_NE(Jobserver::Config::kModePosixFifo, Jobserver::Config::kModeWin32Semaphore);
}
