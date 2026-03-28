#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_session.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_unique_ptr.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_textflow.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_istream.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_context.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_config.hpp"

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch;

using ::testing::Return;

using ::testing::_;



class MockIStream : public IStream {

public:

    MOCK_METHOD(std::ostream &, stream, (), (override));

    MOCK_METHOD(bool, isConsole, (), (const, override));

};



class MockConfig : public Config {

public:

    MockConfig() = default;

    ~MockConfig() override = default;

};



class SessionTest : public ::testing::Test {

protected:

    Session session;

    NiceMock<MockIStream> mockErrStream;

    NiceMock<MockConfig> mockConfig;



    void SetUp() override {

        // Setup any common state before tests (if needed)

    }

};



TEST_F(SessionTest, ApplyCommandLine_NoErrors_ReturnsZero_451) {

    int argc = 1;

    const char* argv[] = {"program"};

    EXPECT_CALL(mockErrStream, stream()).Times(0); // Ensure no error message is printed

    EXPECT_EQ(session.applyCommandLine(argc, argv), 0);

}



TEST_F(SessionTest, ApplyCommandLine_HelpFlag_ReturnsZero_451) {

    int argc = 2;

    const char* argv[] = {"program", "-?"};

    session.useConfigData(ConfigData{.showHelp = true});

    EXPECT_CALL(mockErrStream, stream()).Times(0); // Ensure no error message is printed

    EXPECT_EQ(session.applyCommandLine(argc, argv), 0);

}



TEST_F(SessionTest, ApplyCommandLine_InvalidInput_ReturnsUnspecifiedErrorExitCode_451) {

    int argc = 2;

    const char* argv[] = {"program", "--invalid-flag"};

    auto mockParser = Clara::Detail::ParserBase{};

    EXPECT_CALL(mockParser, parse(_,_)).WillOnce(Return(Clara::Detail::BasicResult<>::logicError("Invalid option")));

    session.cli(mockParser);

    EXPECT_CALL(mockErrStream, stream()).Times(1); // Ensure error message is printed

    EXPECT_EQ(session.applyCommandLine(argc, argv), UnspecifiedErrorExitCode);

}



TEST_F(SessionTest, ApplyCommandLine_LibIdentifyFlag_ReturnsZero_451) {

    int argc = 2;

    const char* argv[] = {"program", "--lib-identify"};

    session.useConfigData(ConfigData{.libIdentify = true});

    EXPECT_CALL(mockErrStream, stream()).Times(0); // Ensure no error message is printed

    EXPECT_EQ(session.applyCommandLine(argc, argv), 0);

}



TEST_F(SessionTest, ApplyCommandLine_StartupException_ReturnsUnspecifiedErrorExitCode_451) {

    session.m_startupExceptions = true;

    int argc = 1;

    const char* argv[] = {"program"};

    EXPECT_CALL(mockErrStream, stream()).Times(0); // Ensure no error message is printed

    EXPECT_EQ(session.applyCommandLine(argc, argv), UnspecifiedErrorExitCode);

}
