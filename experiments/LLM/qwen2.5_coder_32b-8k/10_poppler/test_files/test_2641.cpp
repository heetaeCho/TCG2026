#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"



class ImageOutputDevTest_2641 : public ::testing::Test {

protected:

    ImageOutputDev* imageOutputDev;



    void SetUp() override {

        imageOutputDev = new ImageOutputDev(nullptr, false, false);

    }



    void TearDown() override {

        delete imageOutputDev;

    }

};



TEST_F(ImageOutputDevTest_2641, EnableJBig2True_2641) {

    imageOutputDev->enableJBig2(true);

    // Since we cannot access private members directly, we can only test observable behavior.

    // Here, we assume that enabling JBIG2 should not cause any exceptions or errors.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2641, EnableJBig2False_2641) {

    imageOutputDev->enableJBig2(false);

    // Similarly, disabling JBIG2 should also not cause any issues.

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2641, DefaultState_2641) {

    // Check the default state of enableJBig2 after initialization.

    // Since we cannot directly access private members, we assume that the default is false.

    imageOutputDev->enableJBig2(false); // Set to known state

    imageOutputDev->enableJBig2(true);

    imageOutputDev->enableJBig2(false);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2641, MultipleEnableCalls_2641) {

    // Test multiple calls to enableJBig2 with different values.

    imageOutputDev->enableJBig2(true);

    imageOutputDev->enableJBig2(false);

    imageOutputDev->enableJBig2(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}



TEST_F(ImageOutputDevTest_2641, ErrorCodeCheck_2641) {

    // Check if enabling JBIG2 affects the error code.

    imageOutputDev->enableJBig2(true);

    EXPECT_EQ(imageOutputDev->getErrorCode(), 0); // Assuming no errors

    imageOutputDev->enableJBig2(false);

    EXPECT_EQ(imageOutputDev->getErrorCode(), 0); // Assuming no errors

}



TEST_F(ImageOutputDevTest_2641, EnableOtherFormats_2641) {

    // Ensure enabling other formats does not interfere with JBIG2.

    imageOutputDev->enablePNG(true);

    imageOutputDev->enableTiff(true);

    imageOutputDev->enableJpeg(true);

    imageOutputDev->enableJpeg2000(true);

    imageOutputDev->enableCCITT(true);

    imageOutputDev->enablePrintFilenames(true);

    imageOutputDev->enableJBig2(true);

    EXPECT_TRUE(imageOutputDev->isOk());

}
