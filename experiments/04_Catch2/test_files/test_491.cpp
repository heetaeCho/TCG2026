#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_output_redirect.hpp"



using namespace Catch;

using ::testing::Test;



class OutputRedirectTest_491 : public Test {

protected:

    OutputRedirect outputRedirect;

};



TEST_F(OutputRedirectTest_491, ActivateSetsRedirectActiveToTrue_491) {

    EXPECT_FALSE(outputRedirect.isActive());

    outputRedirect.activate();

    EXPECT_TRUE(outputRedirect.isActive());

}



TEST_F(OutputRedirectTest_491, ActivateThrowsAssertionIfAlreadyActive_491) {

    outputRedirect.activate();

    EXPECT_DEATH({ outputRedirect.activate(); }, "redirect is already active");

}



TEST_F(OutputRedirectTest_491, IsActiveReturnsFalseInitially_491) {

    EXPECT_FALSE(outputRedirect.isActive());

}



TEST_F(OutputRedirectTest_491, DeactivateResetsRedirectActiveToFalse_491) {

    outputRedirect.activate();

    outputRedirect.deactivate();

    EXPECT_FALSE(outputRedirect.isActive());

}



TEST_F(OutputRedirectTest_491, GetStdoutReturnsEmptyStringInitially_491) {

    EXPECT_EQ(outputRedirect.getStdout(), "");

}



TEST_F(OutputRedirectTest_491, GetStderrReturnsEmptyStringInitially_491) {

    EXPECT_EQ(outputRedirect.getStderr(), "");

}



TEST_F(OutputRedirectTest_491, ClearBuffersDoesNotThrowWhenInactive_491) {

    EXPECT_NO_THROW(outputRedirect.clearBuffers());

}



// Assuming some output is generated and captured when active

// This test case assumes that activateImpl and deactivateImpl work as expected internally.

// Since we cannot modify internal behavior, this test remains a boundary check.

TEST_F(OutputRedirectTest_491, ClearBuffersResetsOutputBuffersWhenActive_491) {

    outputRedirect.activate();

    // Simulate some output generation here if possible

    outputRedirect.clearBuffers();

    EXPECT_EQ(outputRedirect.getStdout(), "");

    EXPECT_EQ(outputRedirect.getStderr(), "");

}
