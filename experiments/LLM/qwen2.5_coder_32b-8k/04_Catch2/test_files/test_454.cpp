#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_session.hpp"



using namespace Catch;

using namespace Clara;



class SessionTest_454 : public ::testing::Test {

protected:

    Session session;

};



TEST_F(SessionTest_454, DefaultConstructorInitializesCliParser_454) {

    const Parser& cli = session.cli();

    EXPECT_EQ(&cli, &session.cli()); // Ensure consistent reference to the CLI parser

}



TEST_F(SessionTest_454, ApplyCommandLineWithValidArgsReturnsZero_454) {

    int argc = 1;

    const char* argv[] = {"program"};

    int result = session.applyCommandLine(argc, argv);

    EXPECT_EQ(result, 0); // Assuming valid args return 0

}



TEST_F(SessionTest_454, ApplyCommandLineWithInvalidArgsReturnsNonZero_454) {

    int argc = 2;

    const char* argv[] = {"program", "--invalid-arg"};

    int result = session.applyCommandLine(argc, argv);

    EXPECT_NE(result, 0); // Assuming invalid args return non-zero

}



TEST_F(SessionTest_454, UseConfigDataSetsConfigData_454) {

    ConfigData configData;

    session.useConfigData(configData);

    // No direct way to verify, but ensure no exceptions are thrown and function executes

}



TEST_F(SessionTest_454, RunWithoutPreviousConfigurationReturnsNonZero_454) {

    int result = session.run();

    EXPECT_NE(result, 0); // Assuming run without configuration fails

}



TEST_F(SessionTest_454, ShowHelpDoesNotThrowException_454) {

    EXPECT_NO_THROW(session.showHelp());

}



TEST_F(SessionTest_454, LibIdentifyDoesNotThrowException_454) {

    EXPECT_NO_THROW(session.libIdentify());

}



TEST_F(SessionTest_454, SetNewCliParserAndGetItBack_454) {

    Parser newParser;

    session.cli(newParser);

    const Parser& retrievedParser = session.cli();

    EXPECT_EQ(&newParser, &retrievedParser); // Ensure the same parser is returned

}



TEST_F(SessionTest_454, ConfigDataCanBeSetAndGet_454) {

    ConfigData configData;

    session.useConfigData(configData);

    ConfigData& retrievedConfigData = session.configData();

    EXPECT_EQ(&configData, &retrievedConfigData); // Ensure the same config data is returned

}



TEST_F(SessionTest_454, ConfigCanBeRetrieved_454) {

    Config& config = session.config();

    // No direct way to verify, but ensure no exceptions are thrown and function executes

}
