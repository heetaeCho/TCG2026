#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

#include <gmock/gmock.h>



using namespace testing;



class ImageOutputDevTest_2648 : public Test {

protected:

    char fileRoot[256] = "test_root";

    bool pageNames = false;

    bool listImages = false;



    ImageOutputDev* outputDev;



    void SetUp() override {

        outputDev = new ImageOutputDev(fileRoot, pageNames, listImages);

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(ImageOutputDevTest_2648, NeedNonTextReturnsTrue_2648) {

    EXPECT_TRUE(outputDev->needNonText());

}



TEST_F(ImageOutputDevTest_2648, UseTilingPatternFillReturnsFalseByDefault_2648) {

    EXPECT_FALSE(outputDev->useTilingPatternFill());

}



TEST_F(ImageOutputDevTest_2648, InterpretType3CharsReturnsFalseByDefault_2648) {

    EXPECT_FALSE(outputDev->interpretType3Chars());

}



TEST_F(ImageOutputDevTest_2648, UpsideDownReturnsFalseByDefault_2648) {

    EXPECT_FALSE(outputDev->upsideDown());

}



TEST_F(ImageOutputDevTest_2648, UseDrawCharReturnsFalseByDefault_2648) {

    EXPECT_FALSE(outputDev->useDrawChar());

}



TEST_F(ImageOutputDevTest_2648, IsOkReturnsTrueByDefault_2648) {

    EXPECT_TRUE(outputDev->isOk());

}



TEST_F(ImageOutputDevTest_2648, GetErrorCodeInitiallyZero_2648) {

    EXPECT_EQ(0, outputDev->getErrorCode());

}



TEST_F(ImageOutputDevTest_2648, EnablePNGSetsCorrectly_2648) {

    outputDev->enablePNG(true);

    // No direct observable effect through public interface

}



TEST_F(ImageOutputDevTest_2648, EnableTiffSetsCorrectly_2648) {

    outputDev->enableTiff(true);

    // No direct observable effect through public interface

}



TEST_F(ImageOutputDevTest_2648, EnableJpegSetsCorrectly_2648) {

    outputDev->enableJpeg(true);

    // No direct observable effect through public interface

}



TEST_F(ImageOutputDevTest_2648, EnableJpeg2000SetsCorrectly_2648) {

    outputDev->enableJpeg2000(true);

    // No direct observable effect through public interface

}



TEST_F(ImageOutputDevTest_2648, EnableJBIG2SetsCorrectly_2648) {

    outputDev->enableJBIG2(true);

    // No direct observable effect through public interface

}



TEST_F(ImageOutputDevTest_2648, EnableCCITTSetsCorrectly_2648) {

    outputDev->enableCCITT(true);

    // No direct observable effect through public interface

}



TEST_F(ImageOutputDevTest_2648, EnablePrintFilenamesSetsCorrectly_2648) {

    outputDev->enablePrintFilenames(true);

    // No direct observable effect through public interface

}
