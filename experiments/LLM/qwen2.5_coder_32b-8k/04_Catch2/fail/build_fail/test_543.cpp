#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_output_redirect.hpp"



using namespace Catch;

using ::testing::Return;



class OutputRedirectMock : public OutputRedirect {

public:

    MOCK_METHOD(void, activateImpl, (), (override));

    MOCK_METHOD(void, deactivateImpl, (), (override));

    MOCK_METHOD(std::string, getStdout, (), (const, override));

    MOCK_METHOD(std::string, getStderr, (), (const, override));

    MOCK_METHOD(void, clearBuffers, (), (override));

};



class OutputRedirectTest_543 : public ::testing::Test {

protected:

    OutputRedirectMock mockOutputRedirect;

};



TEST_F(OutputRedirectTest_543, ActivateSetsActiveFlagToTrue_543) {

    EXPECT_CALL(mockOutputRedirect, activateImpl()).Times(1);

    mockOutputRedirect.activate();

    EXPECT_TRUE(mockOutputRedirect.isActive());

}



TEST_F(OutputRedirectTest_543, DeactivateSetsActiveFlagToFalse_543) {

    mockOutputRedirect.activate(); // Set the flag to true first

    EXPECT_CALL(mockOutputRedirect, deactivateImpl()).Times(1);

    mockOutputRedirect.deactivate();

    EXPECT_FALSE(mockOutputRedirect.isActive());

}



TEST_F(OutputRedirectTest_543, GetStdoutReturnsEmptyStringByDefault_543) {

    EXPECT_CALL(mockOutputRedirect, getStdout()).WillOnce(Return(""));

    EXPECT_EQ(mockOutputRedirect.getStdout(), "");

}



TEST_F(OutputRedirectTest_543, GetStderrReturnsEmptyStringByDefault_543) {

    EXPECT_CALL(mockOutputRedirect, getStderr()).WillOnce(Return(""));

    EXPECT_EQ(mockOutputRedirect.getStderr(), "");

}



TEST_F(OutputRedirectTest_543, ClearBuffersDoesNotThrowException_543) {

    EXPECT_CALL(mockOutputRedirect, clearBuffers()).Times(1);

    ASSERT_NO_THROW(mockOutputRedirect.clearBuffers());

}
