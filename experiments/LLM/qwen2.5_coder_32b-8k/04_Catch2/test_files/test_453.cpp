#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_session.hpp"

#include "catch_config.hpp"



using namespace Catch;



class SessionTest : public ::testing::Test {

protected:

    Session session;

};



TEST_F(SessionTest_453, RunReturnsZeroWhenNoWaitForKeypress_453) {

    ConfigData configData;

    configData.waitForKeypress = WaitForKeypress::Never;

    session.useConfigData(configData);

    

    EXPECT_EQ(session.run(), 0);

}



TEST_F(SessionTest_453, RunWaitsBeforeStartIfConfigured_453) {

    ConfigData configData;

    configData.waitForKeypress = WaitForKeypress::BeforeStart;

    session.useConfigData(configData);



    EXPECT_EQ(session.run(), 0); // This test assumes runInternal always returns 0 for simplicity

}



TEST_F(SessionTest_453, RunWaitsBeforeExitIfConfigured_453) {

    ConfigData configData;

    configData.waitForKeypress = WaitForKeypress::BeforeExit;

    session.useConfigData(configData);



    EXPECT_EQ(session.run(), 0); // This test assumes runInternal always returns 0 for simplicity

}



TEST_F(SessionTest_453, RunWaitsBothStartAndEndIfConfigured_453) {

    ConfigData configData;

    configData.waitForKeypress = WaitForKeypress::BeforeStartAndExit;

    session.useConfigData(configData);



    EXPECT_EQ(session.run(), 0); // This test assumes runInternal always returns 0 for simplicity

}



TEST_F(SessionTest_453, RunUsesProvidedCommandLineArguments_453) {

    int argc = 1;

    const char* argv[] = {"test_program"};



    EXPECT_EQ(session.applyCommandLine(argc, argv), 0);

}
