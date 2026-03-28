#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_session.hpp"



using namespace Catch;



class SessionTest : public ::testing::Test {

protected:

    Session session;

};



TEST_F(SessionTest_449, ShowHelpPrintsCorrectOutput_449) {

    testing::internal::CaptureStdout();

    session.showHelp();

    std::string output = testing::internal::GetCapturedStdout();



    EXPECT_THAT(output, ::testing::StartsWith("\nCatch2 v"));

    EXPECT_THAT(output, ::testing::EndsWith("For more detailed usage please see the project docs\n\n"));

}



TEST_F(SessionTest_449, ApplyCommandLineWithNoArgumentsReturnsZero_449) {

    int argc = 1;

    const char* argv[] = {"program_name"};

    int result = session.applyCommandLine(argc, argv);

    EXPECT_EQ(result, 0);

}



TEST_F(SessionTest_449, ApplyCommandLineWithValidArgumentsReturnsZero_449) {

    int argc = 3;

    const char* argv[] = {"program_name", "--help", "-l"};

    int result = session.applyCommandLine(argc, argv);

    EXPECT_EQ(result, 0);

}



TEST_F(SessionTest_449, RunWithoutConfigDataReturnsNonZero_449) {

    int result = session.run();

    EXPECT_NE(result, 0); // Assuming run without configuration will not succeed

}



TEST_F(SessionTest_449, ConfigDataCanBeSetAndRetrieved_449) {

    ConfigData configData;

    session.useConfigData(configData);

    ConfigData& retrievedConfigData = session.configData();

    EXPECT_EQ(&retrievedConfigData, &configData); // Check if the same reference is returned

}



TEST_F(SessionTest_449, CliCanBeSetAndGet_449) {

    Clara::Parser parser;

    session.cli(parser);

    const Clara::Parser& retrievedParser = session.cli();

    EXPECT_EQ(&retrievedParser, &parser); // Check if the same reference is returned

}
