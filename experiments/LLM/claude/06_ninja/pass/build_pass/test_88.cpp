#include "gtest/gtest.h"
#include "build.h"
#include "exit_status.h"

// Test that success() returns true when status is ExitSuccess
TEST(CommandRunnerResultTest_88, SuccessReturnsTrueWhenExitSuccess_88) {
    CommandRunner::Result result;
    result.status = ExitSuccess;
    EXPECT_TRUE(result.success());
}

// Test that success() returns false when status is ExitFailure
TEST(CommandRunnerResultTest_88, SuccessReturnsFalseWhenExitFailure_88) {
    CommandRunner::Result result;
    result.status = ExitFailure;
    EXPECT_FALSE(result.success());
}

// Test that success() returns false when status is ExitInterrupted
TEST(CommandRunnerResultTest_88, SuccessReturnsFalseWhenExitInterrupted_88) {
    CommandRunner::Result result;
    result.status = ExitInterrupted;
    EXPECT_FALSE(result.success());
}

// Test default-constructed Result has ExitFailure status (edge=nullptr, status=ExitFailure)
TEST(CommandRunnerResultTest_88, DefaultConstructedResultIsFailure_88) {
    CommandRunner::Result result;
    EXPECT_FALSE(result.success());
    EXPECT_EQ(result.status, ExitFailure);
}

// Test default-constructed Result has nullptr edge
TEST(CommandRunnerResultTest_88, DefaultConstructedResultHasNullEdge_88) {
    CommandRunner::Result result;
    EXPECT_EQ(result.edge, nullptr);
}

// Test default-constructed Result has empty output
TEST(CommandRunnerResultTest_88, DefaultConstructedResultHasEmptyOutput_88) {
    CommandRunner::Result result;
    EXPECT_TRUE(result.output.empty());
}

// Test that output can be set and does not affect success()
TEST(CommandRunnerResultTest_88, OutputDoesNotAffectSuccess_88) {
    CommandRunner::Result result;
    result.status = ExitSuccess;
    result.output = "some output text";
    EXPECT_TRUE(result.success());
    EXPECT_EQ(result.output, "some output text");
}

// Test that setting status back and forth works correctly
TEST(CommandRunnerResultTest_88, StatusToggleBehavior_88) {
    CommandRunner::Result result;
    result.status = ExitSuccess;
    EXPECT_TRUE(result.success());

    result.status = ExitFailure;
    EXPECT_FALSE(result.success());

    result.status = ExitSuccess;
    EXPECT_TRUE(result.success());

    result.status = ExitInterrupted;
    EXPECT_FALSE(result.success());
}

// Test that only ExitSuccess (0) yields true from success()
TEST(CommandRunnerResultTest_88, OnlyExitSuccessIsSuccess_88) {
    CommandRunner::Result result;

    result.status = ExitSuccess;
    EXPECT_TRUE(result.success());

    result.status = ExitFailure;
    EXPECT_FALSE(result.success());

    result.status = ExitInterrupted;
    EXPECT_FALSE(result.success());
}
