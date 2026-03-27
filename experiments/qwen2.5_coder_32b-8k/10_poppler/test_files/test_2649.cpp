#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock dependencies if needed

class MockGfxState : public GfxState {

public:

    MOCK_METHOD(void, setFillPattern, (const Pattern*), (override));

};



class MockStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(void, reset, (), (override));

};



class MockObject : public Object {

public:

    MOCK_METHOD(void, free, (), (override));

};



class MockGfx : public Gfx {

public:

    MOCK_METHOD(void, setPatternFill, (const Pattern*), (override));

};



class MockCatalog : public Catalog {

public:

    MOCK_METHOD(void, getOutputIntents, (std::vector<OutputIntent*>&), (override));

};



class MockGfxTilingPattern : public GfxTilingPattern {

public:

    MOCK_METHOD(double, getStepX, (), (const override));

    MOCK_METHOD(double, getStepY, (), (const override));

};



class MockImgWriter : public ImgWriter {

public:

    MOCK_METHOD(bool, writeImage, (FILE*, const unsigned char*, int, int), (override));

};



// Include the header file for ImageOutputDev

#include "TestProjects/poppler/utils/ImageOutputDev.h"



using ::testing::Return;

using ::testing::_;



class ImageOutputDevTest_2649 : public ::testing::Test {

protected:

    MockGfxState mock_state;

    MockStream mock_stream;

    MockObject mock_ref;

    MockGfx mock_gfx;

    MockCatalog mock_catalog;

    MockGfxTilingPattern mock_tpat;

    MockImgWriter mock_img_writer;



    ImageOutputDev image_output_dev{"fileRoot", true, false};



    void SetUp() override {

        // Initialize if needed

    }



    void TearDown() override {

        // Clean up if needed

    }

};



TEST_F(ImageOutputDevTest_2649, UpsideDown_ReturnsTrue_2649) {

    EXPECT_TRUE(image_output_dev.upsideDown());

}



TEST_F(ImageOutputDevTest_2649, EnablePNG_EnableAndCheck_2649) {

    image_output_dev.enablePNG(true);

    // Since there's no direct observable behavior for enable functions,

    // we assume internal state change which affects isOk() or getErrorCode()

    EXPECT_TRUE(image_output_dev.isOk());

}



TEST_F(ImageOutputDevTest_2649, EnableTiff_EnableAndCheck_2649) {

    image_output_dev.enableTiff(true);

    EXPECT_TRUE(image_output_dev.isOk());

}



TEST_F(ImageOutputDevTest_2649, EnableJpeg_EnableAndCheck_2649) {

    image_output_dev.enableJpeg(true);

    EXPECT_TRUE(image_output_dev.isOk());

}



TEST_F(ImageOutputDevTest_2649, EnableJpeg2000_EnableAndCheck_2649) {

    image_output_dev.enableJpeg2000(true);

    EXPECT_TRUE(image_output_dev.isOk());

}



TEST_F(ImageOutputDevTest_2649, EnableJBIG2_EnableAndCheck_2649) {

    image_output_dev.enableJBIG2(true);

    EXPECT_TRUE(image_output_dev.isOk());

}



TEST_F(ImageOutputDevTest_2649, EnableCCITT_EnableAndCheck_2649) {

    image_output_dev.enableCCITT(true);

    EXPECT_TRUE(image_output_dev.isOk());

}



TEST_F(ImageOutputDevTest_2649, EnablePrintFilenames_EnableAndCheck_2649) {

    image_output_dev.enablePrintFilenames(true);

    EXPECT_TRUE(image_output_dev.isOk());

}



TEST_F(ImageOutputDevTest_2649, GetErrorCode_DefaultIsZero_2649) {

    EXPECT_EQ(image_output_dev.getErrorCode(), 0);

}



TEST_F(ImageOutputDevTest_2649, IsOk_ReturnsTrueInitially_2649) {

    EXPECT_TRUE(image_output_dev.isOk());

}
