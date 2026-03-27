#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "build.h"



using ::testing::Test;



class CommandRunnerResultTest_88 : public Test {

protected:

    CommandRunner::Result success_result;

    CommandRunner::Result failure_result;



    CommandRunnerResultTest_88() 

        : success_result({nullptr, ExitSuccess, "Output from success", true}),

          failure_result({nullptr, ExitFailure, "Output from failure", false}) {}

};



TEST_F(CommandRunnerResultTest_88, SuccessReturnsTrue_88) {

    EXPECT_TRUE(success_result.success());

}



TEST_F(CommandRunnerResultTest_88, FailureReturnsFalse_88) {

    EXPECT_FALSE(failure_result.success());

}



TEST_F(CommandRunnerResultTest_88, EdgeSetCorrectly_88) {

    Edge mock_edge;

    CommandRunner::Result custom_result = {&mock_edge, ExitSuccess, "Edge set", true};

    EXPECT_EQ(custom_result.edge, &mock_edge);

}



TEST_F(CommandRunnerResultTest_88, OutputSetCorrectly_88) {

    std::string expected_output = "Expected output";

    CommandRunner::Result custom_result = {nullptr, ExitFailure, expected_output, false};

    EXPECT_EQ(custom_result.output, expected_output);

}



TEST_F(CommandRunnerResultTest_88, StatusSetCorrectly_88) {

    CommandRunner::Result custom_result = {nullptr, ExitInterrupted, "Interrupted output", false};

    EXPECT_EQ(custom_result.status, ExitInterrupted);

}
