#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_output_redirect.hpp"



using namespace Catch;



class OutputRedirectTest : public ::testing::Test {

protected:

    OutputRedirect* outputRedirect;



    void SetUp() override {

        outputRedirect = new OutputRedirect();

    }



    void TearDown() override {

        delete outputRedirect;

    }

};



TEST_F(OutputRedirectTest_490, IsActiveInitiallyFalse_490) {

    EXPECT_FALSE(outputRedirect->isActive());

}



TEST_F(OutputRedirectTest_490, ActivateSetsActiveTrue_490) {

    outputRedirect->activate();

    EXPECT_TRUE(outputRedirect->isActive());

}



TEST_F(OutputRedirectTest_490, DeactivateSetsActiveFalse_490) {

    outputRedirect->activate();

    outputRedirect->deactivate();

    EXPECT_FALSE(outputRedirect->isActive());

}



TEST_F(OutputRedirectTest_490, GetStdoutInitiallyEmpty_490) {

    EXPECT_EQ(outputRedirect->getStdout(), "");

}



TEST_F(OutputRedirectTest_490, GetStderrInitiallyEmpty_490) {

    EXPECT_EQ(outputRedirect->getStderr(), "");

}



TEST_F(OutputRedirectTest_490, ClearBuffersDoesNotThrow_490) {

    EXPECT_NO_THROW(outputRedirect->clearBuffers());

}
