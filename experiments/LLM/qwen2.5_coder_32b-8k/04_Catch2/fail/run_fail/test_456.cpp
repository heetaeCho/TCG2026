#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_session.hpp"



using namespace Catch;



class SessionTest_456 : public ::testing::Test {

protected:

    Session session;

};



TEST_F(SessionTest_456, ConfigData_ReturnsValidReference_456) {

    ConfigData& config = session.configData();

    EXPECT_EQ(&config, &session.configData());

}



TEST_F(SessionTest_456, ApplyCommandLine_ValidArgs_ReturnsZero_456) {

    const char* args[] = {"test_program", "--help"};

    int result = session.applyCommandLine(2, args);

    EXPECT_EQ(result, 0); // Assuming valid args return 0

}



TEST_F(SessionTest_456, ApplyCommandLine_InvalidArgs_ReturnsNonZero_456) {

    const char* args[] = {"test_program", "--invalid_option"};

    int result = session.applyCommandLine(2, args);

    EXPECT_NE(result, 0); // Assuming invalid args return non-zero

}



TEST_F(SessionTest_456, ShowHelp_DoesNotThrowException_456) {

    EXPECT_NO_THROW(session.showHelp());

}



TEST_F(SessionTest_456, LibIdentify_DoesNotThrowException_456) {

    EXPECT_NO_THROW(session.libIdentify());

}



TEST_F(SessionTest_456, Run_DefaultConfig_ReturnsZero_456) {

    int result = session.run();

    EXPECT_EQ(result, 0); // Assuming default run returns 0

}



TEST_F(SessionTest_456, UseConfigData_ValidConfig_NoException_456) {

    ConfigData config;

    EXPECT_NO_THROW(session.useConfigData(config));

}



TEST_F(SessionTest_456, Cli_SetAndGet_ReturnsSameParser_456) {

    Clara::Parser parser;

    session.cli(parser);

    EXPECT_EQ(&parser, &session.cli());

}



TEST_F(SessionTest_456, RunWithArgs_ValidArgs_ReturnsZero_456) {

    const char* args[] = {"test_program", "--help"};

    int result = session.run(2, args);

    EXPECT_EQ(result, 0); // Assuming valid args return 0

}



TEST_F(SessionTest_456, RunWithArgs_InvalidArgs_ReturnsNonZero_456) {

    const char* args[] = {"test_program", "--invalid_option"};

    int result = session.run(2, args);

    EXPECT_NE(result, 0); // Assuming invalid args return non-zero

}
