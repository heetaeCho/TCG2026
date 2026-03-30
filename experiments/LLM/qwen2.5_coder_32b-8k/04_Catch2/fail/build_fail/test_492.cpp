#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_output_redirect.hpp"



using namespace Catch;

using namespace testing;



class OutputRedirectTest_492 : public ::testing::Test {

protected:

    OutputRedirect* outputRedirect;



    void SetUp() override {

        outputRedirect = new OutputRedirect();

    }



    void TearDown() override {

        delete outputRedirect;

    }

};



TEST_F(OutputRedirectTest_492, ActivateSetsActiveFlagToTrue_492) {

    outputRedirect->activate();

    EXPECT_TRUE(outputRedirect->isActive());

}



TEST_F(OutputRedirectTest_492, DeactivateSetsActiveFlagToFalse_492) {

    outputRedirect->activate();

    outputRedirect->deactivate();

    EXPECT_FALSE(outputRedirect->isActive());

}



TEST_F(OutputRedirectTest_492, DoubleDeactivateThrowsAssertionFailure_492) {

    outputRedirect->activate();

    outputRedirect->deactivate();

    ASSERT_DEATH({ outputRedirect->deactivate(); }, "redirect is not active");

}



TEST_F(OutputRedirectTest_492, GetStdoutReturnsEmptyStringInitially_492) {

    EXPECT_EQ(outputRedirect->getStdout(), "");

}



TEST_F(OutputRedirectTest_492, GetStderrReturnsEmptyStringInitially_492) {

    EXPECT_EQ(outputRedirect->getStderr(), "");

}



TEST_F(OutputRedirectTest_492, ClearBuffersDoesNotThrowWhenInactive_492) {

    outputRedirect->clearBuffers();

    SUCCEED(); // If clearBuffers does not throw, the test succeeds

}



TEST_F(OutputRedirectTest_492, IsActiveReturnsFalseInitially_492) {

    EXPECT_FALSE(outputRedirect->isActive());

}
