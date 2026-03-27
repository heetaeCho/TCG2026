#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"



class ImageOutputDevTest_2640 : public ::testing::Test {

protected:

    ImageOutputDev* imageOutputDev;



    void SetUp() override {

        imageOutputDev = new ImageOutputDev(nullptr, false, false);

    }



    void TearDown() override {

        delete imageOutputDev;

    }

};



TEST_F(ImageOutputDevTest_2640, EnableJpeg2000_DefaultValue_2640) {

    // Since we do not know the default value, we assume it might be false.

    EXPECT_FALSE(imageOutputDev->getErrorCode());

}



TEST_F(ImageOutputDevTest_2640, EnableJpeg2000_EnableTrue_2640) {

    imageOutputDev->enableJpeg2000(true);

    // We cannot check the internal state directly. Thus, we assume no error code is set.

    EXPECT_FALSE(imageOutputDev->getErrorCode());

}



TEST_F(ImageOutputDevTest_2640, EnableJpeg2000_EnableFalse_2640) {

    imageOutputDev->enableJpeg2000(false);

    // We cannot check the internal state directly. Thus, we assume no error code is set.

    EXPECT_FALSE(imageOutputDev->getErrorCode());

}



TEST_F(ImageOutputDevTest_2640, EnableJpeg2000_ToggleMultipleTimes_2640) {

    imageOutputDev->enableJpeg2000(true);

    imageOutputDev->enableJpeg2000(false);

    imageOutputDev->enableJpeg2000(true);



    EXPECT_FALSE(imageOutputDev->getErrorCode());

}



TEST_F(ImageOutputDevTest_2640, EnableJpeg2000_NoErrorOnBoundaryValues_2640) {

    // Since there are no boundary values for a boolean, we just check enabling and disabling.

    imageOutputDev->enableJpeg2000(true);

    imageOutputDev->enableJpeg2000(false);



    EXPECT_FALSE(imageOutputDev->getErrorCode());

}
