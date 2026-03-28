#include <gtest/gtest.h>
#include "./TestProjects/poppler/poppler/PSOutputDev.h"

class PSOutputDevTest_1315 : public ::testing::Test {
protected:
    PSOutputDev* psOutputDev;

    void SetUp() override {
        psOutputDev = new PSOutputDev("test.ps", nullptr, nullptr, 0, PSOutMode::eps, 100, 100, true, false, 0, 0, 0, 0, PSForceRasterize::noForce, true, nullptr, nullptr, PSLevel::level2);
    }

    void TearDown() override {
        delete psOutputDev;
    }
};

TEST_F(PSOutputDevTest_1315, SetUncompressPreloadedImages_NormalOperation_1315) {
    // Check the default value of uncompressPreloadedImages (should be false).
    ASSERT_FALSE(psOutputDev->uncompressPreloadedImages);
    
    // Set it to true and verify.
    psOutputDev->setUncompressPreloadedImages(true);
    ASSERT_TRUE(psOutputDev->uncompressPreloadedImages);

    // Set it back to false and verify.
    psOutputDev->setUncompressPreloadedImages(false);
    ASSERT_FALSE(psOutputDev->uncompressPreloadedImages);
}

TEST_F(PSOutputDevTest_1315, SetUncompressPreloadedImages_ValidBoundary_1315) {
    // Test boundary cases: Setting values as true or false repeatedly.
    for (int i = 0; i < 10; ++i) {
        psOutputDev->setUncompressPreloadedImages(i % 2 == 0);
        bool expected = (i % 2 == 0);
        ASSERT_EQ(psOutputDev->uncompressPreloadedImages, expected);
    }
}

TEST_F(PSOutputDevTest_1315, SetUncompressPreloadedImages_ErrorHandling_1315) {
    // Assuming this function cannot throw or return errors, we test for unexpected behaviors.
    try {
        psOutputDev->setUncompressPreloadedImages(true);
        ASSERT_NO_THROW(psOutputDev->setUncompressPreloadedImages(false));
    } catch (const std::exception& e) {
        FAIL() << "Exception occurred: " << e.what();
    }
}