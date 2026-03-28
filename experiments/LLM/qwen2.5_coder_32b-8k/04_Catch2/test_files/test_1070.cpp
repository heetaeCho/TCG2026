#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/catch_session.hpp"



using namespace Catch;

using namespace testing;



class MockIStream : public IStream {

public:

    MOCK_METHOD(std::ostream&, stream, (), (override));

    MOCK_METHOD(bool, isConsole, (), (const override));

};



class SessionTest : public Test {

protected:

    MockIStream mockStream;

};



TEST_F(SessionTest, ConstructorDoesNotThrowOnFirstInstantiation_1070) {

    EXPECT_NO_THROW(Session());

}



TEST_F(SessionTest, ConstructorThrowsOnSecondInstantiation_1070) {

    Session firstSession; // First instantiation

    EXPECT_THROW(Session(), std::exception);

}



TEST_F(SessionTest, StartupExceptionsAreReportedCorrectly_1070) {

    IMutableRegistryHub* mockMutableRegistryHub = new NiceMock<IMutableRegistryHub>();

    IRegistryHub* mockRegistryHub = new NiceMock<IRegistryHub>();



    ON_CALL(*mockRegistryHub, getStartupExceptionRegistry())

        .WillByDefault(ReturnRef(mockMutableRegistryHub->getStartupExceptionRegistry()));



    EXPECT_CALL(mockStream, stream()).Times(2);

    EXPECT_CALL(mockStream, isConsole()).WillOnce(Return(true));



    Session session;

}



TEST_F(SessionTest, ShowHelpDoesNotThrow_1070) {

    Session session;

    EXPECT_NO_THROW(session.showHelp());

}



TEST_F(SessionTest, LibIdentifyDoesNotThrow_1070) {

    Session session;

    EXPECT_NO_THROW(session.libIdentify());

}



TEST_F(SessionTest, ApplyCommandLineWithValidArgumentsReturnsZero_1070) {

    Session session;

    int argc = 1;

    const char* argv[] = {"program"};

    EXPECT_EQ(session.applyCommandLine(argc, argv), 0);

}



TEST_F(SessionTest, UseConfigDataDoesNotThrow_1070) {

    Session session;

    ConfigData configData;

    EXPECT_NO_THROW(session.useConfigData(configData));

}



TEST_F(SessionTest, RunWithoutExceptionsReturnsZero_1070) {

    Session session;

    EXPECT_EQ(session.run(), 0);

}



TEST_F(SessionTest, CliCanBeSetAndGetCorrectly_1070) {

    Session session;

    Clara::Parser newParser;

    session.cli(newParser);

    EXPECT_EQ(&session.cli(), &newParser);

}



TEST_F(SessionTest, ConfigDataCanBeSetAndGetCorrectly_1070) {

    Session session;

    ConfigData configData;

    session.useConfigData(configData);

    EXPECT_EQ(&session.configData(), &configData);

}



TEST_F(SessionTest, ConfigCanBeRetrievedAfterUseConfigData_1070) {

    Session session;

    ConfigData configData;

    session.useConfigData(configData);

    EXPECT_NE(&session.config(), nullptr);

}
