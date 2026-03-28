#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_output_redirect.hpp"



using namespace Catch::Detail;



class OutputRedirectTest_542 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(OutputRedirectTest_542, MakeOutputRedirect_ActualTrue_ReturnsFileRedirect_542) {

#if defined( CATCH_CONFIG_NEW_CAPTURE )

    auto redirect = makeOutputRedirect(true);

    EXPECT_TRUE(dynamic_cast<FileRedirect*>(redirect.get()) != nullptr);

#else

    auto redirect = makeOutputRedirect(true);

    EXPECT_TRUE(dynamic_cast<StreamRedirect*>(redirect.get()) != nullptr);

#endif

}



TEST_F(OutputRedirectTest_542, MakeOutputRedirect_ActualFalse_ReturnsNoopRedirect_542) {

    auto redirect = makeOutputRedirect(false);

    EXPECT_TRUE(dynamic_cast<NoopRedirect*>(redirect.get()) != nullptr);

}
