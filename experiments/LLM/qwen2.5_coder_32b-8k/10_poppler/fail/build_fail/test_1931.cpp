#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CairoOutputDev.cc"

#include "Stream.h"

#include "GfxState.h"

#include "Error.h"



using namespace testing;



class MockImageStream : public ImageStream {

public:

    MOCK_METHOD(bool, rewind, (), (override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(bool, getPixel, (unsigned char*), (override));

    MOCK_METHOD(unsigned char*, getLine, (), (override));

    MOCK_METHOD(void, skipLine, (), (override));

};



class MockGfxImageColorMap : public GfxImageColorMap {

public:

    using GfxImageColorMap::GfxImageColorMap;

    MOCK_METHOD(void, getRGBLine, (unsigned char* in, unsigned int* out, int length), (override));

    MOCK_METHOD(int, getNumPixelComps, (), (const, override));

};



class RescaleDrawImageTest : public Test {

protected:

    MockImageStream mockImgStr;

    MockGfxImageColorMap mockColorMap;

    GfxRGB* lookup = nullptr;

    int maskColors[4] = {0, 255, 0, 255};

    int width = 10;

    RescaleDrawImage rescaleDrawImage;



    void SetUp() override {

        rescaleDrawImage.lookup = lookup;

        rescaleDrawImage.current_row = 0;

        rescaleDrawImage.imageError = false;

        rescaleDrawImage.fromRGBA = false;

        ON_CALL(mockImgStr, getLine()).WillByDefault(Return(new unsigned char[width * 4]));

    }



    void TearDown() override {

        delete[] mockImgStr.getLine();

    }

};



TEST_F(RescaleDrawImageTest_1931, GetRow_NormalOperation_1931) {

    EXPECT_CALL(mockColorMap, getNumPixelComps()).WillOnce(Return(3));

    EXPECT_CALL(mockColorMap, getRGBLine(_, _, width)).Times(1);



    uint32_t row_data[width];

    rescaleDrawImage.imgStr = &mockImgStr;

    rescaleDrawImage.colorMap = &mockColorMap;

    rescaleDrawImage.width = width;



    rescaleDrawImage.getRow(0, row_data);

}



TEST_F(RescaleDrawImageTest_1931, GetRow_BoundaryCondition_RowNumLessThanCurrentRow_1931) {

    uint32_t row_data[width];

    rescaleDrawImage.current_row = 5;



    rescaleDrawImage.getRow(4, row_data);

}



TEST_F(RescaleDrawImageTest_1931, GetRow_ErrorCase_ImageStreamReturnsNull_1931) {

    EXPECT_CALL(mockColorMap, getNumPixelComps()).WillOnce(Return(3));

    EXPECT_CALL(mockImgStr, getLine())

        .Times(1)

        .WillOnce(Return(nullptr));



    uint32_t row_data[width];

    rescaleDrawImage.imgStr = &mockImgStr;

    rescaleDrawImage.colorMap = &mockColorMap;

    rescaleDrawImage.width = width;



    rescaleDrawImage.getRow(0, row_data);

}



TEST_F(RescaleDrawImageTest_1931, GetRow_ErrorCase_ImageStreamReturnsNull_MultipleRows_1931) {

    EXPECT_CALL(mockColorMap, getNumPixelComps()).WillOnce(Return(3));

    EXPECT_CALL(mockImgStr, getLine())

        .Times(2)

        .WillOnce(Return(nullptr))

        .WillRepeatedly(Return(new unsigned char[width * 4]));



    uint32_t row_data[width];

    rescaleDrawImage.imgStr = &mockImgStr;

    rescaleDrawImage.colorMap = &mockColorMap;

    rescaleDrawImage.width = width;



    rescaleDrawImage.getRow(0, row_data);

    rescaleDrawImage.getRow(1, row_data);

}



TEST_F(RescaleDrawImageTest_1931, GetRow_MaskColors_OpaquePixel_1931) {

    EXPECT_CALL(mockColorMap, getNumPixelComps()).WillOnce(Return(3));

    EXPECT_CALL(mockColorMap, getRGBLine(_, _, width)).Times(1);



    uint32_t row_data[width];

    unsigned char* img_line = new unsigned char[width * 4];

    for (int i = 0; i < width * 3; i += 3) {

        img_line[i] = 255;

        img_line[i + 1] = 0;

        img_line[i + 2] = 0;

    }

    ON_CALL(mockImgStr, getLine()).WillByDefault(Return(img_line));



    rescaleDrawImage.imgStr = &mockImgStr;

    rescaleDrawImage.colorMap = &mockColorMap;

    rescaleDrawImage.width = width;

    rescaleDrawImage.maskColors = maskColors;



    rescaleDrawImage.getRow(0, row_data);



    for (int i = 0; i < width; ++i) {

        EXPECT_EQ(row_data[i] & 0xff000000, 0xff000000);

    }

}



TEST_F(RescaleDrawImageTest_1931, GetRow_MaskColors_TransparentPixel_1931) {

    EXPECT_CALL(mockColorMap, getNumPixelComps()).WillOnce(Return(3));

    EXPECT_CALL(mockColorMap, getRGBLine(_, _, width)).Times(1);



    uint32_t row_data[width];

    unsigned char* img_line = new unsigned char[width * 4];

    for (int i = 0; i < width * 3; i += 3) {

        img_line[i] = 10;

        img_line[i + 1] = 256;

        img_line[i + 2] = -1;

    }

    ON_CALL(mockImgStr, getLine()).WillByDefault(Return(img_line));



    rescaleDrawImage.imgStr = &mockImgStr;

    rescaleDrawImage.colorMap = &mockColorMap;

    rescaleDrawImage.width = width;

    rescaleDrawImage.maskColors = maskColors;



    rescaleDrawImage.getRow(0, row_data);



    for (int i = 0; i < width; ++i) {

        EXPECT_EQ(row_data[i] & 0xff000000, 0);

    }

}
