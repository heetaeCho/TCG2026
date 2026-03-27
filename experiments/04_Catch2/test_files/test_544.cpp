#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_output_redirect.hpp"



using namespace Catch;

using namespace testing;



class OutputRedirectTest_544 : public Test {

protected:

    NiceMock<OutputRedirect> redirectImpl;

};



TEST_F(OutputRedirectTest_544, IsActiveInitiallyFalse_544) {

    EXPECT_FALSE(redirectImpl.isActive());

}



TEST_F(OutputRedirectTest_544, ActivateSetsActiveTrue_544) {

    redirectImpl.activate();

    EXPECT_TRUE(redirectImpl.isActive());

}



TEST_F(OutputRedirectTest_544, DeactivateSetsActiveFalse_544) {

    redirectImpl.activate();

    redirectImpl.deactivate();

    EXPECT_FALSE(redirectImpl.isActive());

}



TEST_F(OutputRedirectTest_544, ScopedDeactivateSetsActiveFalse_544) {

    RedirectGuard guard = scopedDeactivate(redirectImpl);

    EXPECT_FALSE(redirectImpl.isActive());

}



TEST_F(OutputRedirectTest_544, GetStdoutInitiallyEmpty_544) {

    EXPECT_EQ(redirectImpl.getStdout(), "");

}



TEST_F(OutputRedirectTest_544, GetStderrInitiallyEmpty_544) {

    EXPECT_EQ(redirectImpl.getStderr(), "");

}



TEST_F(OutputRedirectTest_544, ClearBuffersDoesNotThrow_544) {

    EXPECT_NO_THROW(redirectImpl.clearBuffers());

}
