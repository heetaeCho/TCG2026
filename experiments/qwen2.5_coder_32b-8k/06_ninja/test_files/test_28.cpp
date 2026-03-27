#include <gtest/gtest.h>

#include "jobserver.h"



class JobserverConfigTest : public ::testing::Test {

protected:

    Jobserver::Config config;

};



TEST_F(JobserverConfigTest_HasMode_ReturnsFalse_When_ModeIsNone_28) {

    // Arrange

    config.mode = Jobserver::Config::kModeNone;



    // Act & Assert

    EXPECT_FALSE(config.HasMode());

}



TEST_F(JobserverConfigTest_HasMode_ReturnsTrue_When_ModeIsPipe_28) {

    // Arrange

    config.mode = Jobserver::Config::kModePipe;



    // Act & Assert

    EXPECT_TRUE(config.HasMode());

}



TEST_F(JobserverConfigTest_HasMode_ReturnsTrue_When_ModeIsPosixFifo_28) {

    // Arrange

    config.mode = Jobserver::Config::kModePosixFifo;



    // Act & Assert

    EXPECT_TRUE(config.HasMode());

}



TEST_F(JobserverConfigTest_HasMode_ReturnsTrue_When_ModeIsWin32Semaphore_28) {

    // Arrange

    config.mode = Jobserver::Config::kModeWin32Semaphore;



    // Act & Assert

    EXPECT_TRUE(config.HasMode());

}



TEST_F(JobserverConfigTest_HasMode_ReturnsTrue_When_ModeIsDefault_28) {

    // Arrange

    config.mode = Jobserver::Config::kModeDefault;



    // Act & Assert

    EXPECT_TRUE(config.HasMode());

}
