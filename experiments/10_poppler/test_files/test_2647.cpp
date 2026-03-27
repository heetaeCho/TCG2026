#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

#include <gmock/gmock.h>



using namespace testing;



class ImageOutputDevMock : public ImageOutputDev {

public:

    MOCK_METHOD(bool, interpretType3Chars, (), (override));

};



class ImageOutputDevTest_2647 : public ::testing::Test {

protected:

    ImageOutputDev *outputDev;



    void SetUp() override {

        outputDev = new ImageOutputDev(nullptr, false, false);

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(ImageOutputDevTest_2647, InterpretType3Chars_ReturnsFalse_2647) {

    EXPECT_FALSE(outputDev->interpretType3Chars());

}



TEST_F(ImageOutputDevTest_2647, EnablePNG_SetTrueAndGetErrorCode_2647) {

    outputDev->enablePNG(true);

    EXPECT_EQ(outputDev->getErrorCode(), 0); // Assuming no error code is set for this operation

}



TEST_F(ImageOutputDevTest_2647, EnableTiff_SetFalseAndGetErrorCode_2647) {

    outputDev->enableTiff(false);

    EXPECT_EQ(outputDev->getErrorCode(), 0); // Assuming no error code is set for this operation

}



TEST_F(ImageOutputDevTest_2647, EnableJpeg_SetTrueAndGetErrorCode_2647) {

    outputDev->enableJpeg(true);

    EXPECT_EQ(outputDev->getErrorCode(), 0); // Assuming no error code is set for this operation

}



TEST_F(ImageOutputDevTest_2647, EnableJpeg2000_SetFalseAndGetErrorCode_2647) {

    outputDev->enableJpeg2000(false);

    EXPECT_EQ(outputDev->getErrorCode(), 0); // Assuming no error code is set for this operation

}



TEST_F(ImageOutputDevTest_2647, EnableJBIG2_SetTrueAndGetErrorCode_2647) {

    outputDev->enableJBIG2(true);

    EXPECT_EQ(outputDev->getErrorCode(), 0); // Assuming no error code is set for this operation

}



TEST_F(ImageOutputDevTest_2647, EnableCCITT_SetFalseAndGetErrorCode_2647) {

    outputDev->enableCCITT(false);

    EXPECT_EQ(outputDev->getErrorCode(), 0); // Assuming no error code is set for this operation

}



TEST_F(ImageOutputDevTest_2647, EnablePrintFilenames_SetTrueAndGetErrorCode_2647) {

    outputDev->enablePrintFilenames(true);

    EXPECT_EQ(outputDev->getErrorCode(), 0); // Assuming no error code is set for this operation

}



TEST_F(ImageOutputDevTest_2647, IsOk_ReturnsTrueInitially_2647) {

    EXPECT_TRUE(outputDev->isOk());

}
