// TEST_ID: 88

#include "gtest/gtest.h"
#include "build.h"
#include "exit_status.h"

// We assume CommandRunner and CommandRunner::Result are defined in global namespace
// as per the provided partial code.

class CommandRunnerResultTest_88 : public ::testing::Test {
protected:
    CommandRunner::Result result_;
};

// Normal operation: default constructed result should NOT be successful.
TEST_F(CommandRunnerResultTest_88, DefaultIsNotSuccess_88) {
    // By interface, status defaults to ExitFailure.
    EXPECT_EQ(result_.status, ExitFailure);
    EXPECT_FALSE(result_.success());
}

// Normal operation: success() returns true when status == ExitSuccess.
TEST_F(CommandRunnerResultTest_88, SuccessWhenStatusExitSuccess_88) {
    result_.status = ExitSuccess;

    EXPECT_TRUE(result_.success());
}

// Normal operation: success() returns false when status == ExitFailure.
TEST_F(CommandRunnerResultTest_88, FailureWhenStatusExitFailure_88) {
    result_.status = ExitFailure;

    EXPECT_FALSE(result_.success());
}

// Normal operation: success() returns false when status == ExitInterrupted.
TEST_F(CommandRunnerResultTest_88, FailureWhenStatusExitInterrupted_88) {
    result_.status = ExitInterrupted;

    EXPECT_FALSE(result_.success());
}

// Boundary / robustness: success() returns false when status has an unknown enum value.
TEST_F(CommandRunnerResultTest_88, FailureWhenStatusUnknownEnumValue_88) {
    // Cast an out-of-range integer to ExitStatus to simulate an unknown status.
    result_.status = static_cast<ExitStatus>(999);

    EXPECT_FALSE(result_.success());
}

// State change behavior: success() reflects changes to status over time.
TEST_F(CommandRunnerResultTest_88, StatusChangeReflectsInSuccess_88) {
    // Start as failure.
    result_.status = ExitFailure;
    EXPECT_FALSE(result_.success());

    // Change to success.
    result_.status = ExitSuccess;
    EXPECT_TRUE(result_.success());

    // Change to interrupted.
    result_.status = ExitInterrupted;
    EXPECT_FALSE(result_.success());
}
