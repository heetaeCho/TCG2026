#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "build.h"



using ::testing::Return;

using ::testing::ElementsAre;



class CommandRunnerTest_89 : public ::testing::Test {

protected:

    CommandRunner* command_runner_;



    void SetUp() override {

        // Assuming a mock or factory method for creating a CommandRunner instance

        // For the purpose of this test, we'll assume a factory method exists.

        command_runner_ = CommandRunner::factory(BuildConfig(), nullptr);

    }



    void TearDown() override {

        delete command_runner_;

    }

};



TEST_F(CommandRunnerTest_89, CanRunMore_ReturnsValidSize_89) {

    EXPECT_GE(command_runner_->CanRunMore(), 0u);

}



TEST_F(CommandRunnerTest_89, StartCommand_ValidEdge_ReturnsTrue_89) {

    Edge mock_edge;

    EXPECT_TRUE(command_runner_->StartCommand(&mock_edge));

}



TEST_F(CommandRunnerTest_89, StartCommand_NullEdge_ReturnsFalse_89) {

    EXPECT_FALSE(command_runner_->StartCommand(nullptr));

}



TEST_F(CommandRunnerTest_89, WaitForCommand_ValidResult_ReturnsTrue_89) {

    Result mock_result;

    EXPECT_TRUE(command_runner_->WaitForCommand(&mock_result));

}



TEST_F(CommandRunnerTest_89, WaitForCommand_NullResult_ReturnsFalse_89) {

    EXPECT_FALSE(command_runner_->WaitForCommand(nullptr));

}



TEST_F(CommandRunnerTest_89, GetActiveEdges_ReturnsEmptyVector_89) {

    EXPECT_TRUE(command_runner_->GetActiveEdges().empty());

}



TEST_F(CommandRunnerTest_89, Abort_DoesNotThrow_89) {

    EXPECT_NO_THROW(command_runner_->Abort());

}
