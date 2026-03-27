#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_session.hpp"



using namespace Catch;



class MockConfigData {

public:

    MOCK_CONST_METHOD0(someMethod, void());

};



class SessionTest : public ::testing::Test {

protected:

    Session session;

};



TEST_F(SessionTest_424, RunWithNoExceptions_ReturnsResultOfApplyCommandLineAndRun_424) {

    int argc = 1;

    const char* argv[] = {"program"};



    EXPECT_CALL(*static_cast<const ConfigData*>(&session.configData()), someMethod()).Times(0);



    // Mock applyCommandLine and run to control return values

    auto originalApplyCommandLine = &Session::applyCommandLine;

    auto originalRun = &Session::run;



    int mockApplyCommandLineReturn = 0;

    int mockRunReturn = 42;



    session.applyCommandLine = [&mockApplyCommandLineReturn](int, const char* const*) { return mockApplyCommandLineReturn; };

    session.run = [&mockRunReturn]() { return mockRunReturn; };



    EXPECT_EQ(session.run(argc, argv), mockRunReturn);



    // Restore original functions

    session.applyCommandLine = originalApplyCommandLine;

    session.run = originalRun;

}



TEST_F(SessionTest_424, RunWithStartupExceptions_Returns1_424) {

    int argc = 1;

    const char* argv[] = {"program"};

    session.m_startupExceptions = true;



    EXPECT_EQ(session.run(argc, argv), 1);

}



TEST_F(SessionTest_424, ApplyCommandLineNonZero_ReturnsApplyCommandLineResult_424) {

    int argc = 1;

    const char* argv[] = {"program"};



    auto originalApplyCommandLine = &Session::applyCommandLine;

    int mockApplyCommandLineReturn = 1;



    session.applyCommandLine = [&mockApplyCommandLineReturn](int, const char* const*) { return mockApplyCommandLineReturn; };



    EXPECT_EQ(session.run(argc, argv), mockApplyCommandLineReturn);



    // Restore original function

    session.applyCommandLine = originalApplyCommandLine;

}



TEST_F(SessionTest_424, ShowHelp_CallsShowHelp_424) {

    EXPECT_CALL(*static_cast<const ConfigData*>(&session.configData()), someMethod()).Times(0);

    testing::StrictMock<testing::NiceMock<class MockConfigData>> mockConfigData;



    session.showHelp();

}



TEST_F(SessionTest_424, LibIdentify_CallsLibIdentify_424) {

    EXPECT_CALL(*static_cast<const ConfigData*>(&session.configData()), someMethod()).Times(0);

    testing::StrictMock<testing::NiceMock<class MockConfigData>> mockConfigData;



    session.libIdentify();

}



TEST_F(SessionTest_424, UseConfigData_SetsConfigData_424) {

    ConfigData configData;

    EXPECT_CALL(*static_cast<const ConfigData*>(&session.configData()), someMethod()).Times(0);

    testing::StrictMock<testing::NiceMock<class MockConfigData>> mockConfigData;



    session.useConfigData(configData);



    // This test assumes that the internal state is correctly set, which we cannot directly verify.

}



TEST_F(SessionTest_424, Cli_Getter_ReturnsCliParserReference_424) {

    const Clara::Parser& parser = session.cli();

    EXPECT_CALL(*static_cast<const ConfigData*>(&session.configData()), someMethod()).Times(0);

    testing::StrictMock<testing::NiceMock<class MockConfigData>> mockConfigData;



    EXPECT_EQ(&parser, &session.m_cli);

}



TEST_F(SessionTest_424, Cli_Setter_SetsCliParser_424) {

    Clara::Parser newParser;

    EXPECT_CALL(*static_cast<const ConfigData*>(&session.configData()), someMethod()).Times(0);

    testing::StrictMock<testing::NiceMock<class MockConfigData>> mockConfigData;



    session.cli(newParser);



    // This test assumes that the internal state is correctly set, which we cannot directly verify.

}



TEST_F(SessionTest_424, ConfigData_ReturnsConfigDataReference_424) {

    ConfigData& configData = session.configData();

    EXPECT_CALL(*static_cast<const ConfigData*>(&session.configData()), someMethod()).Times(0);

    testing::StrictMock<testing::NiceMock<class MockConfigData>> mockConfigData;



    EXPECT_EQ(&configData, &session.m_configData);

}



TEST_F(SessionTest_424, Config_ReturnsConfigReference_424) {

    Config& config = session.config();

    EXPECT_CALL(*static_cast<const ConfigData*>(&session.configData()), someMethod()).Times(0);

    testing::StrictMock<testing::NiceMock<class MockConfigData>> mockConfigData;



    // This test assumes that the internal state is correctly set, which we cannot directly verify.

}
