#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_session.hpp"

#include "catch2/internal/catch_clara.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Ref;



class MockParser : public Clara::Parser {

public:

    MOCK_CONST_METHOD0(getHelpColumns, std::vector<Detail::HelpColumns>());

    MOCK_METHOD1(writeToStream, void(std::ostream&));

    MOCK_CONST_METHOD0(validate, Detail::Result());

    MOCK_METHOD2(parse, Detail::InternalParseResult(const std::string&, Detail::TokenStream));

};



class SessionTest : public ::testing::Test {

protected:

    Session session;

    MockParser mockParser;

};



TEST_F(SessionTest_SetCli_455, SetAndGetParser_455) {

    session.cli(mockParser);

    EXPECT_EQ(&mockParser, &session.cli());

}



TEST_F(SessionTest_ApplyCommandLine_455, ValidCommandLine_455) {

    int argc = 1;

    const char* argv[] = {"test"};

    EXPECT_CALL(mockParser, parse("test", _)).WillOnce(::testing::Return(Detail::InternalParseResult{}));

    session.cli(mockParser);

    int result = session.applyCommandLine(argc, argv);

    EXPECT_EQ(result, 0); // Assuming valid command line returns 0

}



TEST_F(SessionTest_ApplyCommandLine_455, InvalidCommandLine_455) {

    int argc = 1;

    const char* argv[] = {"test"};

    Detail::InternalParseResult invalidResult;

    invalidResult.m_error = "Invalid argument";

    EXPECT_CALL(mockParser, parse("test", _)).WillOnce(::testing::Return(invalidResult));

    session.cli(mockParser);

    int result = session.applyCommandLine(argc, argv);

    EXPECT_NE(result, 0); // Assuming invalid command line returns non-zero

}



TEST_F(SessionTest_UseConfigData_455, ConfigDataIsSet_455) {

    ConfigData configData;

    session.useConfigData(configData);

    EXPECT_EQ(&configData, &session.configData());

}



TEST_F(SessionTest_Run_455, RunReturnsZeroOnSuccess_455) {

    EXPECT_CALL(mockParser, validate()).WillOnce(::testing::Return(Detail::Result{}));

    session.cli(mockParser);

    int result = session.run();

    EXPECT_EQ(result, 0); // Assuming successful run returns 0

}



TEST_F(SessionTest_ShowHelp_455, ShowHelpInvokesWriteToStream_455) {

    testing::internal::CaptureStdout();

    EXPECT_CALL(mockParser, writeToStream(_));

    session.cli(mockParser);

    session.showHelp();

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());

}
